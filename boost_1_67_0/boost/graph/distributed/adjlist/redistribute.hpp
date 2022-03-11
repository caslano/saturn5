// Copyright (C) 2005-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

//
// Implements redistribution of vertices for a distributed adjacency
// list. This file should not be included by users. It will be
// included by the distributed adjacency list header.
//

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/pending/container_traits.hpp>

namespace boost { namespace detail { namespace parallel {

/* This structure contains a (vertex or edge) descriptor that is being
   moved from one processor to another. It contains the properties for
   that descriptor (if any).
 */
template<typename Descriptor, typename DescriptorProperty>
struct redistributed_descriptor : maybe_store_property<DescriptorProperty>
{
  typedef maybe_store_property<DescriptorProperty> inherited;

  redistributed_descriptor() { }

  redistributed_descriptor(const Descriptor& v, const DescriptorProperty& p)
    : inherited(p), descriptor(v) { }

  Descriptor descriptor;

private:
  friend class boost::serialization::access;

  template<typename Archiver>
  void serialize(Archiver& ar, unsigned int /*version*/)
  {
    ar & boost::serialization::base_object<inherited>(*this) 
       & unsafe_serialize(descriptor);
  }
};

/* Predicate that returns true if the target has migrated. */
template<typename VertexProcessorMap, typename Graph>
struct target_migrated_t
{
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  typedef typename graph_traits<Graph>::edge_descriptor Edge;

  target_migrated_t(VertexProcessorMap vertex_to_processor, const Graph& g)
    : vertex_to_processor(vertex_to_processor), g(g) { }

  bool operator()(Edge e) const
  {
    typedef global_descriptor<Vertex> DVertex;
    processor_id_type owner = get(edge_target_processor_id, g, e);
    return get(vertex_to_processor, DVertex(owner, target(e, g))) != owner;
  }

private:
  VertexProcessorMap vertex_to_processor;
  const Graph& g;
};

template<typename VertexProcessorMap, typename Graph>
inline target_migrated_t<VertexProcessorMap, Graph>
target_migrated(VertexProcessorMap vertex_to_processor, const Graph& g)
{ return target_migrated_t<VertexProcessorMap, Graph>(vertex_to_processor, g); }

/* Predicate that returns true if the source of an in-edge has migrated. */
template<typename VertexProcessorMap, typename Graph>
struct source_migrated_t
{
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  typedef typename graph_traits<Graph>::edge_descriptor Edge;

  source_migrated_t(VertexProcessorMap vertex_to_processor, const Graph& g)
    : vertex_to_processor(vertex_to_processor), g(g) { }

  bool operator()(stored_in_edge<Edge> e) const
  {
    return get(vertex_to_processor, DVertex(e.source_processor, source(e.e, g)))
      != e.source_processor;
  }

private:
  VertexProcessorMap vertex_to_processor;
  const Graph& g;
};

template<typename VertexProcessorMap, typename Graph>
inline source_migrated_t<VertexProcessorMap, Graph>
source_migrated(VertexProcessorMap vertex_to_processor, const Graph& g)
{ return source_migrated_t<VertexProcessorMap, Graph>(vertex_to_processor, g); }

/* Predicate that returns true if the target has migrated. */
template<typename VertexProcessorMap, typename Graph>
struct source_or_target_migrated_t
{
  typedef typename graph_traits<Graph>::edge_descriptor Edge;

  source_or_target_migrated_t(VertexProcessorMap vertex_to_processor,
                              const Graph& g)
    : vertex_to_processor(vertex_to_processor), g(g) { }

  bool operator()(Edge e) const
  {
    return get(vertex_to_processor, source(e, g)) != source(e, g).owner
      || get(vertex_to_processor, target(e, g)) != target(e, g).owner;
  }

private:
  VertexProcessorMap vertex_to_processor;
  const Graph& g;
};

template<typename VertexProcessorMap, typename Graph>
inline source_or_target_migrated_t<VertexProcessorMap, Graph>
source_or_target_migrated(VertexProcessorMap vertex_to_processor,
const Graph& g)
{
  typedef source_or_target_migrated_t<VertexProcessorMap, Graph> result_type;
  return result_type(vertex_to_processor, g);
}

} } // end of namespace detail::parallel

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template<typename VertexProcessorMap>
void
PBGL_DISTRIB_ADJLIST_TYPE
::request_in_neighbors(vertex_descriptor v,
                       VertexProcessorMap vertex_to_processor,
                       bidirectionalS)
{
  BGL_FORALL_INEDGES_T(v, e, *this, graph_type)
    request(vertex_to_processor, source(e, *this));
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template<typename VertexProcessorMap>
void
PBGL_DISTRIB_ADJLIST_TYPE
::remove_migrated_in_edges(vertex_descriptor v,
                           VertexProcessorMap vertex_to_processor,
                           bidirectionalS)
{
  graph_detail::erase_if(get(vertex_in_edges, base())[v.local],
                         source_migrated(vertex_to_processor, base()));
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template<typename VertexProcessorMap>
void
PBGL_DISTRIB_ADJLIST_TYPE
::redistribute(VertexProcessorMap vertex_to_processor)
{
  using boost::parallel::inplace_all_to_all;

  // When we have stable descriptors, we only move those descriptors
  // that actually need to be moved. Otherwise, we essentially have to
  // regenerate the entire graph.
  const bool has_stable_descriptors =
    is_same<typename config_type::vertex_list_selector, listS>::value
    || is_same<typename config_type::vertex_list_selector, setS>::value
    || is_same<typename config_type::vertex_list_selector, multisetS>::value;

  typedef detail::parallel::redistributed_descriptor<vertex_descriptor, 
                                                     vertex_property_type>
    redistributed_vertex;
  typedef detail::parallel::redistributed_descriptor<edge_descriptor, 
                                                     edge_property_type>
    redistributed_edge;

  vertex_iterator vi, vi_end;
  edge_iterator ei, ei_end;

  process_group_type pg = process_group();

  // Initial synchronization makes sure that we have all of our ducks
  // in a row. We don't want any outstanding add/remove messages
  // coming in mid-redistribution!
  synchronize(process_group_);

  // We cannot cope with eviction of ghost cells
  vertex_to_processor.set_max_ghost_cells(0);

  process_id_type p = num_processes(pg);

  // Send vertices and edges to the processor where they will
  // actually reside.  This requires O(|V| + |E|) communication
  std::vector<std::vector<redistributed_vertex> > redistributed_vertices(p);
  std::vector<std::vector<redistributed_edge> > redistributed_edges(p);

  // Build the sets of relocated vertices for each process and then do
  // an all-to-all transfer.
  for (boost::tie(vi, vi_end) = vertices(*this); vi != vi_end; ++vi) {
    if (!has_stable_descriptors
        || get(vertex_to_processor, *vi) != vi->owner) {
      redistributed_vertices[get(vertex_to_processor, *vi)]
        .push_back(redistributed_vertex(*vi, get(vertex_all_t(), base(),
                                                 vi->local)));
    }

    // When our descriptors are stable, we need to determine which
    // adjacent descriptors are stable to determine which edges will
    // be removed.
    if (has_stable_descriptors) {
      BGL_FORALL_OUTEDGES_T(*vi, e, *this, graph_type)
        request(vertex_to_processor, target(e, *this));
      request_in_neighbors(*vi, vertex_to_processor, directed_selector());
    }
  }

  inplace_all_to_all(pg, redistributed_vertices);

  // If we have stable descriptors, we need to know where our neighbor
  // vertices are moving.
  if (has_stable_descriptors)
    synchronize(vertex_to_processor);

  // Build the sets of relocated edges for each process and then do
  // an all-to-all transfer.
  for (boost::tie(ei, ei_end) = edges(*this); ei != ei_end; ++ei) {
    vertex_descriptor src = source(*ei, *this);
    vertex_descriptor tgt = target(*ei, *this);
    if (!has_stable_descriptors
        || get(vertex_to_processor, src) != src.owner
        || get(vertex_to_processor, tgt) != tgt.owner)
      redistributed_edges[get(vertex_to_processor, source(*ei, *this))]
        .push_back(redistributed_edge(*ei, split_edge_property(get(edge_all_t(), base(),
                                                                   ei->local))));
  }
  inplace_all_to_all(pg, redistributed_edges);

  // A mapping from old vertex descriptors to new vertex
  // descriptors. This is an STL map partly because I'm too lazy to
  // build a real property map (which is hard in the general case) but
  // also because it won't try to look in the graph itself, because
  // the keys are all vertex descriptors that have been invalidated.
  std::map<vertex_descriptor, vertex_descriptor> old_to_new_vertex_map;

  if (has_stable_descriptors) {
    // Clear out all vertices and edges that will have moved. There
    // are several stages to this.

    // First, eliminate all outgoing edges from the (local) vertices
    // that have been moved or whose targets have been moved.
    BGL_FORALL_VERTICES_T(v, *this, graph_type) {
      if (get(vertex_to_processor, v) != v.owner) {
        clear_out_edges(v.local, base());
        clear_in_edges_local(v, directed_selector());
      } else {
        remove_out_edge_if(v.local,
                           target_migrated(vertex_to_processor, base()),
                           base());
        remove_migrated_in_edges(v, vertex_to_processor, directed_selector());
      }
    }

    // Next, eliminate locally-stored edges that have migrated (for
    // undirected graphs).
    graph_detail::erase_if(local_edges_,
                           source_or_target_migrated(vertex_to_processor, *this));

    // Eliminate vertices that have migrated
    for (boost::tie(vi, vi_end) = vertices(*this); vi != vi_end; /* in loop */) {
      if (get(vertex_to_processor, *vi) != vi->owner)
        remove_vertex((*vi++).local, base());
      else {
        // Add the identity relation for vertices that have not migrated
        old_to_new_vertex_map[*vi] = *vi;
        ++vi;
      }
    }
  } else {
    // Clear out the local graph: the entire graph is in transit
    clear();
  }

  // Add the new vertices to the graph. When we do so, update the old
  // -> new vertex mapping both locally and for the owner of the "old"
  // vertex.
  {
    typedef std::pair<vertex_descriptor, vertex_descriptor> mapping_pair;
    std::vector<std::vector<mapping_pair> > mappings(p);

    for (process_id_type src = 0; src < p; ++src) {
      for (typename std::vector<redistributed_vertex>::iterator vi =
             redistributed_vertices[src].begin();
           vi != redistributed_vertices[src].end(); ++vi) {
        vertex_descriptor new_vertex =
            add_vertex(vi->get_property(), *this);
        old_to_new_vertex_map[vi->descriptor] = new_vertex;
        mappings[vi->descriptor.owner].push_back(mapping_pair(vi->descriptor,
                                                              new_vertex));
      }

      redistributed_vertices[src].clear();
    }

    inplace_all_to_all(pg, mappings);

    // Add the mappings we were sent into the old->new map.
    for (process_id_type src = 0; src < p; ++src)
      old_to_new_vertex_map.insert(mappings[src].begin(), mappings[src].end());
  }

  // Get old->new vertex mappings for all of the vertices we need to
  // know about.

  // TBD: An optimization here might involve sending the
  // request-response pairs without an explicit request step (for
  // bidirectional and undirected graphs). However, it may not matter
  // all that much given the cost of redistribution.
  {
    std::vector<std::vector<vertex_descriptor> > vertex_map_requests(p);
    std::vector<std::vector<vertex_descriptor> > vertex_map_responses(p);

    // We need to know about all of the vertices incident on edges
    // that have been relocated to this processor. Tell each processor
    // what each other processor needs to know.
    for (process_id_type src = 0; src < p; ++src)
      for (typename std::vector<redistributed_edge>::iterator ei =
             redistributed_edges[src].begin();
           ei != redistributed_edges[src].end(); ++ei) {
        vertex_descriptor need_vertex = target(ei->descriptor, *this);
        if (old_to_new_vertex_map.find(need_vertex)
            == old_to_new_vertex_map.end())
          {
            old_to_new_vertex_map[need_vertex] = need_vertex;
            vertex_map_requests[need_vertex.owner].push_back(need_vertex);
          }
      }
    inplace_all_to_all(pg,
                       vertex_map_requests,
                       vertex_map_responses);

    // Process the requests made for vertices we own. Then perform yet
    // another all-to-all swap. This one matches the requests we've
    // made to the responses we were given.
    for (process_id_type src = 0; src < p; ++src)
      for (typename std::vector<vertex_descriptor>::iterator vi =
             vertex_map_responses[src].begin();
           vi != vertex_map_responses[src].end(); ++vi)
        *vi = old_to_new_vertex_map[*vi];
    inplace_all_to_all(pg, vertex_map_responses);

    // Matching the requests to the responses, update the old->new
    // vertex map for all of the vertices we will need to know.
    for (process_id_type src = 0; src < p; ++src) {
      typedef typename std::vector<vertex_descriptor>::size_type size_type;
      for (size_type i = 0; i < vertex_map_requests[src].size(); ++i) {
        old_to_new_vertex_map[vertex_map_requests[src][i]] =
          vertex_map_responses[src][i];
      }
    }
  }

  // Add edges to the graph by mapping the source and target.
  for (process_id_type src = 0; src < p; ++src) {
    for (typename std::vector<redistributed_edge>::iterator ei =
           redistributed_edges[src].begin();
         ei != redistributed_edges[src].end(); ++ei) {
      add_edge(old_to_new_vertex_map[source(ei->descriptor, *this)],
               old_to_new_vertex_map[target(ei->descriptor, *this)],
               ei->get_property(),
               *this);
    }

    redistributed_edges[src].clear();
  }

  // Be sure that edge-addition messages are received now, completing
  // the graph.
  synchronize(process_group_);

  this->distribution().clear();

  detail::parallel::maybe_initialize_vertex_indices(vertices(base()), 
                                                    get(vertex_index, base()));
}

} // end namespace boost

/* redistribute.hpp
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
*/
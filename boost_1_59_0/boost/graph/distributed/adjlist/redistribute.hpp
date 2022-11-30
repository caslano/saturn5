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
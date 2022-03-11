// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

/**************************************************************************
 * This source file implements the variation on Dijkstra's algorithm      *
 * presented by Crauser et al. in:                                        *
 *                                                                        *
 *   Andreas Crauser, Kurt Mehlhorn, Ulrich Meyer, and Peter              *
 *   Sanders. A Parallelization of Dijkstra's Shortest Path               *
 *   Algorithm. In Lubos Brim, Jozef Gruska, and Jiri Zlatuska,          *
 *   editors, Mathematical Foundations of Computer Science (MFCS),        *
 *   volume 1450 of Lecture Notes in Computer Science, pages              *
 *   722--731, 1998. Springer.                                            *
 *                                                                        *
 * This implementation is, however, restricted to the distributed-memory  *
 * case, where the work is distributed by virtue of the vertices being    *
 * distributed. In a shared-memory (single address space) context, we     *
 * would want to add an explicit balancing step.                          *
 **************************************************************************/
#ifndef BOOST_GRAPH_CRAUSER_ET_AL_SHORTEST_PATHS_HPP
#define BOOST_GRAPH_CRAUSER_ET_AL_SHORTEST_PATHS_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/assert.hpp>
#include <boost/graph/distributed/detail/dijkstra_shortest_paths.hpp>
#include <boost/graph/parallel/algorithm.hpp>
#include <functional>
#include <boost/graph/iteration_macros.hpp>
#include <boost/property_map/property_map_iterator.hpp>
#include <boost/type_traits/is_same.hpp>
#include <algorithm>
#include <boost/property_map/parallel/caching_property_map.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/distributed/detail/remote_update_set.hpp>
#include <vector>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/parallel/container_traits.hpp>

#ifdef PBGL_ACCOUNTING
#  include <boost/graph/accounting.hpp>
#  include <numeric>
#endif // PBGL_ACCOUNTING

#ifdef MUTABLE_QUEUE
#    include <boost/pending/mutable_queue.hpp>
#endif

namespace boost { namespace graph { namespace distributed {

#ifdef PBGL_ACCOUNTING
struct crauser_et_al_shortest_paths_stats_t
{
  /* Total wall-clock time used by the algorithm.*/
  accounting::time_type execution_time;

  /* The number of vertices deleted in each superstep. */
  std::vector<std::size_t> deleted_vertices;

  template<typename OutputStream>
  void print(OutputStream& out)
  {
    double avg_deletions = std::accumulate(deleted_vertices.begin(),
                                           deleted_vertices.end(),
                                           0.0);
    avg_deletions /= deleted_vertices.size();

    out << "Problem = \"Single-Source Shortest Paths\"\n"
        << "Algorithm = \"Crauser et al\"\n"
        << "Function = crauser_et_al_shortest_paths\n"
        << "Wall clock time = " << accounting::print_time(execution_time)
        << "\nSupersteps = " << deleted_vertices.size() << "\n"
        << "Avg. deletions per superstep = " << avg_deletions << "\n";
  }
};

static crauser_et_al_shortest_paths_stats_t crauser_et_al_shortest_paths_stats;
#endif

namespace detail {

  /************************************************************************
   * Function objects that perform distance comparisons modified by the   *
   * minimum or maximum edge weights.                                     *
   ************************************************************************/
  template<typename Vertex, typename DistanceMap, typename MinInWeightMap,
           typename Combine, typename Compare>
  struct min_in_distance_compare
    : std::binary_function<Vertex, Vertex, bool>
  {
    min_in_distance_compare(DistanceMap d, MinInWeightMap m,
                            Combine combine, Compare compare)
      : distance_map(d), min_in_weight(m), combine(combine),
        compare(compare)
    {
    }

    bool operator()(const Vertex& x, const Vertex& y) const
    {
      return compare(combine(get(distance_map, x), -get(min_in_weight, x)),
                     combine(get(distance_map, y), -get(min_in_weight, y)));
    }

  private:
    DistanceMap distance_map;
    MinInWeightMap min_in_weight;
    Combine combine;
    Compare compare;
  };

  template<typename Vertex, typename DistanceMap, typename MinOutWeightMap,
           typename Combine, typename Compare>
  struct min_out_distance_compare
    : std::binary_function<Vertex, Vertex, bool>
  {
    min_out_distance_compare(DistanceMap d, MinOutWeightMap m,
                             Combine combine, Compare compare)
      : distance_map(d), min_out_weight(m), combine(combine),
        compare(compare)
    {
    }

    bool operator()(const Vertex& x, const Vertex& y) const
    {
      return compare(combine(get(distance_map, x), get(min_out_weight, x)),
                     combine(get(distance_map, y), get(min_out_weight, y)));
    }

  private:
    DistanceMap distance_map;
    MinOutWeightMap min_out_weight;
    Combine combine;
    Compare compare;
  };
  /************************************************************************/

  /************************************************************************
   * Dijkstra queue that implements Crauser et al.'s criteria. This queue *
   * actually stores three separate priority queues, to help expose all   *
   * vertices that can be processed in a single phase.                    *
   ************************************************************************/
  template<typename Graph, typename Combine,
           typename Compare, typename VertexIndexMap, typename DistanceMap,
           typename PredecessorMap, typename MinOutWeightMap,
           typename MinInWeightMap>
  class crauser_et_al_dijkstra_queue
    : public graph::detail::remote_update_set<
               crauser_et_al_dijkstra_queue<
                 Graph, Combine, Compare, VertexIndexMap, DistanceMap, 
                 PredecessorMap, MinOutWeightMap, MinInWeightMap>,
               typename boost::graph::parallel::process_group_type<Graph>::type,
               typename dijkstra_msg_value<DistanceMap, PredecessorMap>::type,
               typename property_map<Graph, vertex_owner_t>::const_type>
  {
    typedef typename graph_traits<Graph>::vertex_descriptor
      vertex_descriptor;
    typedef crauser_et_al_dijkstra_queue self_type;
    typedef dijkstra_msg_value<DistanceMap, PredecessorMap> msg_value_creator;
    typedef typename msg_value_creator::type msg_value_type;
    typedef typename graph_traits<Graph>::vertices_size_type
      vertices_size_type;
    typedef typename property_map<Graph, vertex_owner_t>::const_type
      OwnerPropertyMap;
    typedef typename boost::graph::parallel::process_group_type<Graph>::type
      process_group_type;
    typedef graph::detail::remote_update_set<self_type, process_group_type,
                                             msg_value_type, OwnerPropertyMap>
      inherited;

    // Priority queue for tentative distances
    typedef indirect_cmp<DistanceMap, Compare> dist_queue_compare_type;

    typedef typename property_traits<DistanceMap>::value_type distance_type;

#ifdef MUTABLE_QUEUE
    typedef mutable_queue<vertex_descriptor, std::vector<vertex_descriptor>, 
                          dist_queue_compare_type, VertexIndexMap> dist_queue_type;

#else
    typedef relaxed_heap<vertex_descriptor, dist_queue_compare_type,
                         VertexIndexMap> dist_queue_type;
#endif // MUTABLE_QUEUE

    // Priority queue for OUT criteria
    typedef min_out_distance_compare<vertex_descriptor, DistanceMap,
                                     MinOutWeightMap, Combine, Compare>
      out_queue_compare_type;

#ifdef MUTABLE_QUEUE
    typedef mutable_queue<vertex_descriptor, std::vector<vertex_descriptor>, 
                          out_queue_compare_type, VertexIndexMap> out_queue_type;

#else
    typedef relaxed_heap<vertex_descriptor, out_queue_compare_type,
                         VertexIndexMap> out_queue_type;
#endif // MUTABLE_QUEUE

    // Priority queue for IN criteria
    typedef min_in_distance_compare<vertex_descriptor, DistanceMap,
                                    MinInWeightMap, Combine, Compare>
      in_queue_compare_type;

#ifdef MUTABLE_QUEUE
    typedef mutable_queue<vertex_descriptor, std::vector<vertex_descriptor>, 
                          in_queue_compare_type, VertexIndexMap> in_queue_type;

#else
    typedef relaxed_heap<vertex_descriptor, in_queue_compare_type,
                         VertexIndexMap> in_queue_type;
#endif // MUTABLE_QUEUE

    typedef typename process_group_type::process_id_type process_id_type;

  public:
    typedef typename dist_queue_type::size_type  size_type;
    typedef typename dist_queue_type::value_type value_type;

    crauser_et_al_dijkstra_queue(const Graph& g,
                                 const Combine& combine,
                                 const Compare& compare,
                                 const VertexIndexMap& id,
                                 const DistanceMap& distance_map,
                                 const PredecessorMap& predecessor_map,
                                 const MinOutWeightMap& min_out_weight,
                                 const MinInWeightMap& min_in_weight)
      : inherited(boost::graph::parallel::process_group(g), get(vertex_owner, g)),
        dist_queue(num_vertices(g),
                   dist_queue_compare_type(distance_map, compare),
                   id),
        out_queue(num_vertices(g),
                  out_queue_compare_type(distance_map, min_out_weight,
                                         combine, compare),
                  id),
        in_queue(num_vertices(g),
                 in_queue_compare_type(distance_map, min_in_weight,
                                       combine, compare),
                 id),
        g(g),
        distance_map(distance_map),
        predecessor_map(predecessor_map),
        min_out_weight(min_out_weight),
        min_in_weight(min_in_weight),
        min_distance(0),
        min_out_distance(0)
#ifdef PBGL_ACCOUNTING
        , local_deletions(0)
#endif
    { }

    void push(const value_type& x)
    {
      msg_value_type msg_value =
        msg_value_creator::create(get(distance_map, x),
                                  predecessor_value(get(predecessor_map, x)));
      inherited::update(x, msg_value);
    }

    void update(const value_type& x) { push(x); }

    void pop()
    {
      // Remove from distance queue
      dist_queue.remove(top_vertex);

      // Remove from OUT queue
      out_queue.remove(top_vertex);

      // Remove from IN queue
      in_queue.remove(top_vertex);

#ifdef PBGL_ACCOUNTING
      ++local_deletions;
#endif
    }

    vertex_descriptor& top() { return top_vertex; }
    const vertex_descriptor& top() const { return top_vertex; }

    bool empty()
    {
      inherited::collect();

      // If there are no suitable messages, wait until we get something
      while (!has_suitable_vertex()) {
        if (do_synchronize()) return true;
      }
      // Return true only if nobody has any messages; false if we
      // have suitable messages
      return false;
    }

    bool do_synchronize()
    {
      using boost::parallel::all_reduce;
      using boost::parallel::minimum;

      inherited::synchronize();

      // TBD: could use combine here, but then we need to stop using
      // minimum<distance_type>() as the function object.
      distance_type local_distances[2];
      local_distances[0] =
        dist_queue.empty()? (std::numeric_limits<distance_type>::max)()
        : get(distance_map, dist_queue.top());

      local_distances[1] =
        out_queue.empty()? (std::numeric_limits<distance_type>::max)()
        : (get(distance_map, out_queue.top())
           + get(min_out_weight, out_queue.top()));

      distance_type distances[2];
      all_reduce(this->process_group, local_distances, local_distances + 2,
                 distances, minimum<distance_type>());
      min_distance = distances[0];
      min_out_distance = distances[1];

#ifdef PBGL_ACCOUNTING
      std::size_t deletions = 0;
      all_reduce(this->process_group, &local_deletions, &local_deletions + 1,
                 &deletions, std::plus<std::size_t>());
      if (process_id(this->process_group) == 0) {
        crauser_et_al_shortest_paths_stats.deleted_vertices.push_back(deletions);
      }
      local_deletions = 0;
      BOOST_ASSERT(deletions > 0);
#endif

      return min_distance == (std::numeric_limits<distance_type>::max)();
    }

  private:
    vertex_descriptor predecessor_value(vertex_descriptor v) const
    { return v; }

    vertex_descriptor
    predecessor_value(property_traits<dummy_property_map>::reference) const
    { return graph_traits<Graph>::null_vertex(); }

    bool has_suitable_vertex() const
    {
      if (!dist_queue.empty()) {
        top_vertex = dist_queue.top();
        if (get(distance_map, dist_queue.top()) <= min_out_distance)
          return true;
      }

      if (!in_queue.empty()) {
        top_vertex = in_queue.top();
        return (get(distance_map, top_vertex)
                - get(min_in_weight, top_vertex)) <= min_distance;
      }
      return false;
    }

  public:
    void
    receive_update(process_id_type source, vertex_descriptor vertex,
                   distance_type distance)
    {
      // Update the queue if the received distance is better than
      // the distance we know locally
      if (distance < get(distance_map, vertex)
          || (distance == get(distance_map, vertex)
              && source == process_id(this->process_group))) {
        // Update the local distance map
        put(distance_map, vertex, distance);

        bool is_in_queue = dist_queue.contains(vertex);

        if (!is_in_queue) {
          dist_queue.push(vertex);
          out_queue.push(vertex);
          in_queue.push(vertex);
        }
        else {
          dist_queue.update(vertex);
          out_queue.update(vertex);
          in_queue.update(vertex);
        }
      }
    }

    void
    receive_update(process_id_type source, vertex_descriptor vertex,
                   std::pair<distance_type, vertex_descriptor> p)
    {
      if (p.first <= get(distance_map, vertex)) {
        put(predecessor_map, vertex, p.second);
        receive_update(source, vertex, p.first);
      }
    }

  private:
    dist_queue_type           dist_queue;
    out_queue_type            out_queue;
    in_queue_type             in_queue;
    mutable value_type        top_vertex;
    const Graph&              g;
    DistanceMap               distance_map;
    PredecessorMap            predecessor_map;
    MinOutWeightMap           min_out_weight;
    MinInWeightMap            min_in_weight;
    distance_type             min_distance;
    distance_type             min_out_distance;
#ifdef PBGL_ACCOUNTING
    std::size_t               local_deletions;
#endif
  };
  /************************************************************************/

  /************************************************************************
   * Initialize the property map that contains the minimum incoming edge  *
   * weight for each vertex. There are separate implementations for       *
   * directed, bidirectional, and undirected graph.                       *
   ************************************************************************/
  template<typename Graph, typename MinInWeightMap, typename WeightMap,
           typename Inf, typename Compare>
  void
  initialize_min_in_weights(const Graph& g, MinInWeightMap min_in_weight,
                            WeightMap weight, Inf inf, Compare compare,
                            directed_tag, incidence_graph_tag)
  {
    // Send minimum weights off to the owners
    set_property_map_role(vertex_distance, min_in_weight);
    BGL_FORALL_VERTICES_T(v, g, Graph) {
      BGL_FORALL_OUTEDGES_T(v, e, g, Graph) {
        if (get(weight, e) < get(min_in_weight, target(e, g)))
          put(min_in_weight, target(e, g), get(weight, e));
      }
    }

    using boost::graph::parallel::process_group;
    synchronize(process_group(g));

    // Replace any infinities with zeros
    BGL_FORALL_VERTICES_T(v, g, Graph) {
      if (get(min_in_weight, v) == inf) put(min_in_weight, v, 0);
    }
  }

  template<typename Graph, typename MinInWeightMap, typename WeightMap,
           typename Inf, typename Compare>
  void
  initialize_min_in_weights(const Graph& g, MinInWeightMap min_in_weight,
                            WeightMap weight, Inf inf, Compare compare,
                            directed_tag, bidirectional_graph_tag)
  {
#if 0
    typename property_map<Graph, vertex_local_t>::const_type
      local = get(vertex_local, g);

    // This code assumes that the properties of the in-edges are
    // available locally. This is not necessarily the case, so don't
    // do this yet.
    set_property_map_role(vertex_distance, min_in_weight);
    BGL_FORALL_VERTICES_T(v, g, Graph) {
      if (in_edges(v, g).first != in_edges(v, g).second) {
        std::cerr << "weights(" << g.distribution().global(get(local, v))
                  << ") = ";
        BGL_FORALL_INEDGES_T(v, e, g, Graph) {
          std::cerr << get(weight, e) << ' ';
        }
        std::cerr << std::endl;
        put(min_in_weight, v,
            *std::min_element
            (make_property_map_iterator(weight, in_edges(v, g).first),
             make_property_map_iterator(weight, in_edges(v, g).second),
             compare));
      } else {
        put(min_in_weight, v, 0);
      }
      std::cerr << "miw(" << g.distribution().global(get(local, v)) << ") = "
                << get(min_in_weight, v) << std::endl;
    }
#else
    initialize_min_in_weights(g, min_in_weight, weight, inf, compare,
                              directed_tag(), incidence_graph_tag());
#endif
  }

  template<typename Graph, typename MinInWeightMap, typename WeightMap,
           typename Inf, typename Compare>
  inline void
  initialize_min_in_weights(const Graph&, MinInWeightMap, WeightMap, Inf,
                            Compare, undirected_tag, bidirectional_graph_tag)
  {
    // In weights are the same as out weights, so do nothing
  }
  /************************************************************************/


  /************************************************************************
   * Initialize the property map that contains the minimum outgoing edge  *
   * weight for each vertex.                                              *
   ************************************************************************/
  template<typename Graph, typename MinOutWeightMap, typename WeightMap,
           typename Compare>
  void
  initialize_min_out_weights(const Graph& g, MinOutWeightMap min_out_weight,
                             WeightMap weight, Compare compare)
  {
    typedef typename property_traits<WeightMap>::value_type weight_type;

    BGL_FORALL_VERTICES_T(v, g, Graph) {
      if (out_edges(v, g).first != out_edges(v, g).second) {
        put(min_out_weight, v,
            *std::min_element
            (make_property_map_iterator(weight, out_edges(v, g).first),
             make_property_map_iterator(weight, out_edges(v, g).second),
             compare));
        if (get(min_out_weight, v) < weight_type(0))
            boost::throw_exception(negative_edge());
      }
    }
  }

  /************************************************************************/

} // end namespace detail

template<typename DistributedGraph, typename DijkstraVisitor,
         typename PredecessorMap, typename DistanceMap, typename WeightMap,
         typename IndexMap, typename ColorMap, typename Compare,
         typename Combine, typename DistInf, typename DistZero>
void
crauser_et_al_shortest_paths
  (const DistributedGraph& g,
   typename graph_traits<DistributedGraph>::vertex_descriptor s,
   PredecessorMap predecessor, DistanceMap distance, WeightMap weight,
   IndexMap index_map, ColorMap color_map,
   Compare compare, Combine combine, DistInf inf, DistZero zero,
   DijkstraVisitor vis)
{

#ifdef PBGL_ACCOUNTING
  crauser_et_al_shortest_paths_stats.deleted_vertices.clear();
  crauser_et_al_shortest_paths_stats.execution_time = accounting::get_time();
#endif

  // Property map that stores the lowest edge weight outgoing from
  // each vertex. If a vertex has no out-edges, the stored weight
  // is zero.
  typedef typename property_traits<WeightMap>::value_type weight_type;
  typedef iterator_property_map<weight_type*, IndexMap> MinOutWeightMap;
  std::vector<weight_type> min_out_weights_vec(num_vertices(g), inf);
  MinOutWeightMap min_out_weight(&min_out_weights_vec.front(), index_map);
  detail::initialize_min_out_weights(g, min_out_weight, weight, compare);

  // Property map that stores the lowest edge weight incoming to
  // each vertex. For undirected graphs, this will just be a
  // shallow copy of the version for outgoing edges.
  typedef typename graph_traits<DistributedGraph>::directed_category
    directed_category;
  const bool is_undirected =
    is_same<directed_category, undirected_tag>::value;
  typedef MinOutWeightMap MinInWeightMap;
  std::vector<weight_type>
    min_in_weights_vec(is_undirected? 1 : num_vertices(g), inf);
  MinInWeightMap min_in_weight(&min_in_weights_vec.front(), index_map);
  typedef typename graph_traits<DistributedGraph>::traversal_category
    category;
  detail::initialize_min_in_weights(g, min_in_weight, weight, inf, compare,
                                    directed_category(), category());

  // Initialize local portion of property maps
  typename graph_traits<DistributedGraph>::vertex_iterator ui, ui_end;
  for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui) {
    put(distance, *ui, inf);
    put(predecessor, *ui, *ui);
  }
  put(distance, s, zero);

  // Dijkstra Queue
  typedef detail::crauser_et_al_dijkstra_queue
            <DistributedGraph, Combine, Compare, IndexMap, DistanceMap, 
             PredecessorMap, MinOutWeightMap, MinInWeightMap>
    Queue;

  Queue Q(g, combine, compare, index_map, distance, predecessor,
          min_out_weight, is_undirected? min_out_weight : min_in_weight);

  // Parallel Dijkstra visitor
  ::boost::detail::dijkstra_bfs_visitor<
      DijkstraVisitor, Queue, WeightMap,
      boost::parallel::caching_property_map<PredecessorMap>,
      boost::parallel::caching_property_map<DistanceMap>, Combine, Compare
    > bfs_vis(vis, Q, weight,
              boost::parallel::make_caching_property_map(predecessor),
              boost::parallel::make_caching_property_map(distance),
              combine, compare, zero);

  set_property_map_role(vertex_color, color_map);
  set_property_map_role(vertex_distance, distance);

  breadth_first_search(g, s, Q, bfs_vis, color_map);

#ifdef PBGL_ACCOUNTING
  crauser_et_al_shortest_paths_stats.execution_time =
    accounting::get_time() - crauser_et_al_shortest_paths_stats.execution_time;
#endif
}

template<typename DistributedGraph, typename PredecessorMap,
         typename DistanceMap, typename WeightMap>
void
crauser_et_al_shortest_paths
  (const DistributedGraph& g,
   typename graph_traits<DistributedGraph>::vertex_descriptor s,
   PredecessorMap predecessor, DistanceMap distance, WeightMap weight)
{
  typedef typename property_traits<DistanceMap>::value_type distance_type;

  std::vector<default_color_type> colors(num_vertices(g), white_color);

  crauser_et_al_shortest_paths(g, s, predecessor, distance, weight,
                               get(vertex_index, g),
                               make_iterator_property_map(&colors[0],
                                                          get(vertex_index, g)),
                               std::less<distance_type>(),
                               closed_plus<distance_type>(),
                               (std::numeric_limits<distance_type>::max)(),
                               distance_type(),
                               dijkstra_visitor<>());
}

template<typename DistributedGraph, typename PredecessorMap,
         typename DistanceMap>
void
crauser_et_al_shortest_paths
  (const DistributedGraph& g,
   typename graph_traits<DistributedGraph>::vertex_descriptor s,
   PredecessorMap predecessor, DistanceMap distance)
{
  crauser_et_al_shortest_paths(g, s, predecessor, distance,
                               get(edge_weight, g));
}

} // end namespace distributed

#ifdef PBGL_ACCOUNTING
using distributed::crauser_et_al_shortest_paths_stats;
#endif

using distributed::crauser_et_al_shortest_paths;


} } // end namespace boost::graph

#endif // BOOST_GRAPH_CRAUSER_ET_AL_SHORTEST_PATHS_HPP

/* crauser_et_al_shortest_paths.hpp
+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
*/
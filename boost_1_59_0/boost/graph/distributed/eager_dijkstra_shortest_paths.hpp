// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

/**************************************************************************
 * This source file implements a variation on distributed Dijkstra's      *
 * algorithm that can expose additional parallelism by permitting         *
 * vertices within a certain distance from the minimum to be processed,   *
 * even though they may not be at their final distance. This can          *
 * introduce looping, but the algorithm will still terminate so long as   *
 * there are no negative loops.                                           *
 **************************************************************************/
#ifndef BOOST_GRAPH_EAGER_DIJKSTRA_SHORTEST_PATHS_HPP
#define BOOST_GRAPH_EAGER_DIJKSTRA_SHORTEST_PATHS_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/assert.hpp>
#include <boost/graph/distributed/detail/dijkstra_shortest_paths.hpp>
#include <boost/property_map/parallel/caching_property_map.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/distributed/detail/remote_update_set.hpp>
#include <vector>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/parallel/container_traits.hpp>
#include <boost/pending/relaxed_heap.hpp>

#ifdef PBGL_ACCOUNTING
#  include <boost/graph/accounting.hpp>
#  include <numeric>
#endif // PBGL_ACCOUNTING

#ifdef MUTABLE_QUEUE
#  include <boost/pending/mutable_queue.hpp>
#endif

namespace boost { namespace graph { namespace distributed {

#ifdef PBGL_ACCOUNTING
struct eager_dijkstra_shortest_paths_stats_t
{
  /* The value of the lookahead parameter. */
  double lookahead;

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
        << "Algorithm = \"Eager Dijkstra\"\n"
        << "Function = eager_dijkstra_shortest_paths\n"
        << "(P) Lookahead = " << lookahead << "\n"
        << "Wall clock time = " << accounting::print_time(execution_time) 
        << "\nSupersteps = " << deleted_vertices.size() << "\n"
        << "Avg. deletions per superstep = " << avg_deletions << "\n";
  }
};

static eager_dijkstra_shortest_paths_stats_t eager_dijkstra_shortest_paths_stats;
#endif

namespace detail {

// Borrowed from BGL's dijkstra_shortest_paths
template <class UniformCostVisitor, class Queue,
          class WeightMap, class PredecessorMap, class DistanceMap,
          class BinaryFunction, class BinaryPredicate>
 struct parallel_dijkstra_bfs_visitor : bfs_visitor<>
{
  typedef typename property_traits<DistanceMap>::value_type distance_type;

  parallel_dijkstra_bfs_visitor(UniformCostVisitor vis, Queue& Q,
                                WeightMap w, PredecessorMap p, DistanceMap d,
                                BinaryFunction combine, BinaryPredicate compare,
                                distance_type zero)
    : m_vis(vis), m_Q(Q), m_weight(w), m_predecessor(p), m_distance(d),
      m_combine(combine), m_compare(compare), m_zero(zero)  { }

  template <class Vertex, class Graph>
  void initialize_vertex(Vertex u, Graph& g)
    { m_vis.initialize_vertex(u, g); }
  template <class Vertex, class Graph>
  void discover_vertex(Vertex u, Graph& g) { m_vis.discover_vertex(u, g); }
  template <class Vertex, class Graph>
  void examine_vertex(Vertex u, Graph& g) { m_vis.examine_vertex(u, g); }

  /* Since the eager formulation of Parallel Dijkstra's algorithm can
     loop, we may relax on *any* edge, not just those associated with
     white and gray targets. */
  template <class Edge, class Graph>
  void examine_edge(Edge e, Graph& g) {
    if (m_compare(get(m_weight, e), m_zero))
        boost::throw_exception(negative_edge());

    m_vis.examine_edge(e, g);

    boost::parallel::caching_property_map<PredecessorMap> c_pred(m_predecessor);
    boost::parallel::caching_property_map<DistanceMap> c_dist(m_distance);

    distance_type old_distance = get(c_dist, target(e, g));

    bool m_decreased = relax(e, g, m_weight, c_pred, c_dist,
                             m_combine, m_compare);

    /* On x86 Linux with optimization, we sometimes get into a
       horrible case where m_decreased is true but the distance hasn't
       actually changed. This occurs when the comparison inside
       relax() occurs with the 80-bit precision of the x87 floating
       point unit, but the difference is lost when the resulting
       values are written back to lower-precision memory (e.g., a
       double). With the eager Dijkstra's implementation, this results
       in looping. */
    if (m_decreased && old_distance != get(c_dist, target(e, g))) {
      m_Q.update(target(e, g));
      m_vis.edge_relaxed(e, g);
    } else
      m_vis.edge_not_relaxed(e, g);
  }
  template <class Vertex, class Graph>
  void finish_vertex(Vertex u, Graph& g) { m_vis.finish_vertex(u, g); }

  UniformCostVisitor m_vis;
  Queue& m_Q;
  WeightMap m_weight;
  PredecessorMap m_predecessor;
  DistanceMap m_distance;
  BinaryFunction m_combine;
  BinaryPredicate m_compare;
  distance_type m_zero;
};

  /**********************************************************************
   * Dijkstra queue that implements arbitrary "lookahead"               *
   **********************************************************************/
  template<typename Graph, typename Combine, typename Compare,
           typename VertexIndexMap, typename DistanceMap,
           typename PredecessorMap>
  class lookahead_dijkstra_queue
    : public graph::detail::remote_update_set<
               lookahead_dijkstra_queue<
                 Graph, Combine, Compare, VertexIndexMap, DistanceMap,
                 PredecessorMap>,
               typename boost::graph::parallel::process_group_type<Graph>::type,
               typename dijkstra_msg_value<DistanceMap, PredecessorMap>::type,
               typename property_map<Graph, vertex_owner_t>::const_type>
  {
    typedef typename graph_traits<Graph>::vertex_descriptor
      vertex_descriptor;
    typedef lookahead_dijkstra_queue self_type;
    typedef typename boost::graph::parallel::process_group_type<Graph>::type
      process_group_type;
    typedef dijkstra_msg_value<DistanceMap, PredecessorMap> msg_value_creator;
    typedef typename msg_value_creator::type msg_value_type;
    typedef typename property_map<Graph, vertex_owner_t>::const_type
      OwnerPropertyMap;

    typedef graph::detail::remote_update_set<self_type, process_group_type,
                                             msg_value_type, OwnerPropertyMap>
      inherited;

    // Priority queue for tentative distances
    typedef indirect_cmp<DistanceMap, Compare> queue_compare_type;

    typedef typename property_traits<DistanceMap>::value_type distance_type;

#ifdef MUTABLE_QUEUE
    typedef mutable_queue<vertex_descriptor, std::vector<vertex_descriptor>, 
                          queue_compare_type, VertexIndexMap> queue_type;

#else
    typedef relaxed_heap<vertex_descriptor, queue_compare_type, 
                         VertexIndexMap> queue_type;
#endif // MUTABLE_QUEUE

    typedef typename process_group_type::process_id_type process_id_type;

  public:
    typedef vertex_descriptor value_type;

    lookahead_dijkstra_queue(const Graph& g,
                             const Combine& combine,
                             const Compare& compare,
                             const VertexIndexMap& id,
                             const DistanceMap& distance_map,
                             const PredecessorMap& predecessor_map,
                             distance_type lookahead)
      : inherited(boost::graph::parallel::process_group(g), get(vertex_owner, g)),
        queue(num_vertices(g), queue_compare_type(distance_map, compare), id),
        distance_map(distance_map),
        predecessor_map(predecessor_map),
        min_distance(0),
        lookahead(lookahead)
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
      queue.pop(); 
#ifdef PBGL_ACCOUNTING
      ++local_deletions;
#endif
    }

    value_type&       top()       { return queue.top(); }
    const value_type& top() const { return queue.top(); }

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

  private:
    vertex_descriptor predecessor_value(vertex_descriptor v) const
    { return v; }

    vertex_descriptor
    predecessor_value(property_traits<dummy_property_map>::reference) const
    { return graph_traits<Graph>::null_vertex(); }

    bool has_suitable_vertex() const
    {
      return (!queue.empty() 
              && get(distance_map, queue.top()) <= min_distance + lookahead);
    }

    bool do_synchronize()
    {
      using boost::parallel::all_reduce;
      using boost::parallel::minimum;

      inherited::synchronize();

      // TBD: could use combine here, but then we need to stop using
      // minimum<distance_type>() as the function object.
      distance_type local_distance = 
        queue.empty()? (std::numeric_limits<distance_type>::max)()
        : get(distance_map, queue.top());

      all_reduce(this->process_group, &local_distance, &local_distance + 1,
                 &min_distance, minimum<distance_type>());

#ifdef PBGL_ACCOUNTING
      std::size_t deletions = 0;
      all_reduce(this->process_group, &local_deletions, &local_deletions + 1,
                 &deletions, std::plus<std::size_t>());
      if (process_id(this->process_group) == 0)
        eager_dijkstra_shortest_paths_stats.deleted_vertices
          .push_back(deletions);
      local_deletions = 0;
      BOOST_ASSERT(deletions > 0);
#endif

      return min_distance == (std::numeric_limits<distance_type>::max)();
    }
    
  public:
    void 
    receive_update(process_id_type source, vertex_descriptor vertex,
                   distance_type distance)
    {
      // Update the queue if the received distance is better than
      // the distance we know locally
      if (distance <= get(distance_map, vertex)) {

        // Update the local distance map
        put(distance_map, vertex, distance);

        bool is_in_queue = queue.contains(vertex);

        if (!is_in_queue) 
          queue.push(vertex);
        else 
          queue.update(vertex);
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
    queue_type     queue;
    DistanceMap    distance_map;
    PredecessorMap predecessor_map;
    distance_type  min_distance;
    distance_type  lookahead;
#ifdef PBGL_ACCOUNTING
    std::size_t    local_deletions;
#endif
  };
  /**********************************************************************/
} // end namespace detail

template<typename DistributedGraph, typename DijkstraVisitor,
         typename PredecessorMap, typename DistanceMap, typename WeightMap,
         typename IndexMap, typename ColorMap, typename Compare,
         typename Combine, typename DistInf, typename DistZero>
void
eager_dijkstra_shortest_paths
  (const DistributedGraph& g,
   typename graph_traits<DistributedGraph>::vertex_descriptor s,
   PredecessorMap predecessor, DistanceMap distance, 
   typename property_traits<DistanceMap>::value_type lookahead,
   WeightMap weight, IndexMap index_map, ColorMap color_map,
   Compare compare, Combine combine, DistInf inf, DistZero zero,
   DijkstraVisitor vis)
{
#ifdef PBGL_ACCOUNTING
  eager_dijkstra_shortest_paths_stats.deleted_vertices.clear();
  eager_dijkstra_shortest_paths_stats.lookahead = lookahead;
  eager_dijkstra_shortest_paths_stats.execution_time = accounting::get_time();
#endif

  // Initialize local portion of property maps
  typename graph_traits<DistributedGraph>::vertex_iterator ui, ui_end;
  for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui) {
    put(distance, *ui, inf);
    put(predecessor, *ui, *ui);
  }
  put(distance, s, zero);

  // Dijkstra Queue
  typedef detail::lookahead_dijkstra_queue
            <DistributedGraph, Combine, Compare, IndexMap, DistanceMap,
             PredecessorMap> Queue;

  Queue Q(g, combine, compare, index_map, distance, 
          predecessor, lookahead);

  // Parallel Dijkstra visitor
  detail::parallel_dijkstra_bfs_visitor
    <DijkstraVisitor, Queue, WeightMap, PredecessorMap, DistanceMap, Combine, 
     Compare> bfs_vis(vis, Q, weight, predecessor, distance, combine, compare,
                      zero);

  set_property_map_role(vertex_color, color_map);
  set_property_map_role(vertex_distance, distance);

  breadth_first_search(g, s, Q, bfs_vis, color_map);

#ifdef PBGL_ACCOUNTING
  eager_dijkstra_shortest_paths_stats.execution_time = 
    accounting::get_time() 
    - eager_dijkstra_shortest_paths_stats.execution_time;
#endif
}

template<typename DistributedGraph, typename DijkstraVisitor,
         typename PredecessorMap, typename DistanceMap, typename WeightMap>
void
eager_dijkstra_shortest_paths
  (const DistributedGraph& g,
   typename graph_traits<DistributedGraph>::vertex_descriptor s,
   PredecessorMap predecessor, DistanceMap distance, 
   typename property_traits<DistanceMap>::value_type lookahead,
   WeightMap weight)
{
  typedef typename property_traits<DistanceMap>::value_type distance_type;

  std::vector<default_color_type> colors(num_vertices(g), white_color);

  eager_dijkstra_shortest_paths(g, s, predecessor, distance, lookahead, weight,
                                get(vertex_index, g),
                                make_iterator_property_map(&colors[0],
                                                           get(vertex_index, 
                                                               g)),
                                std::less<distance_type>(),
                                closed_plus<distance_type>(),
                                distance_type(),
                                (std::numeric_limits<distance_type>::max)(),
                                dijkstra_visitor<>());
}

template<typename DistributedGraph, typename DijkstraVisitor,
         typename PredecessorMap, typename DistanceMap>
void
eager_dijkstra_shortest_paths
  (const DistributedGraph& g,
   typename graph_traits<DistributedGraph>::vertex_descriptor s,
   PredecessorMap predecessor, DistanceMap distance,
   typename property_traits<DistanceMap>::value_type lookahead)
{
  eager_dijkstra_shortest_paths(g, s, predecessor, distance, lookahead,
                               get(edge_weight, g));
}
} // end namespace distributed

#ifdef PBGL_ACCOUNTING
using distributed::eager_dijkstra_shortest_paths_stats;
#endif

using distributed::eager_dijkstra_shortest_paths;

} } // end namespace boost::graph

#endif // BOOST_GRAPH_EAGER_DIJKSTRA_SHORTEST_PATHS_HPP

/* eager_dijkstra_shortest_paths.hpp
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
*/
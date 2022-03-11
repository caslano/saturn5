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
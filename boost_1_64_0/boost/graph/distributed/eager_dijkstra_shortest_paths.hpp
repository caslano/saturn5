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
RdujV3O8COPXI2bt5OJ+XfHOudslNMF9gMMhbTzSFLR+1EBHMWu/O0LabpLm6uIvx+inkX7spF/LQCMtA4fdukYhphqGYiztj8/k3PMKpPipvie6l8jSu8ycMIEnxegbqt96Rg8vRb5f6weG6SHauAG6f4nip6WWE38c1c0cA1u/NH1wdsHMHH/YBJgmYaPw0y9hqbe+4xoWkMdxteuZPQPmJ+l+BOR5k/DPi1kzi3SSP3ptKh9h5IHpb5vQTr/Pd6XY7d1ernDtpPDts1HS/tvzl/te+b5Sz8ufSct/8dkWTy0/+/ZZmPZomPZuuPZluPZuuHbn2bdrw7T/wrYjP432yq94Ot/df2HCvu+6rUtp5Tlve7j2Zfj24qZqXrnriYSs8TMabrrxzt0X/bP6wcyz1+8L058Rpn8iXD9HuPbu2fdn/K+0a8P0i4Tt7/kaub7k5Lmu622HRXFfpP2r70l9f+7FuDA1MZauN+XlOBgJM+AXcI//XaXvu4GYshzv1HDV8HcerAWbwNowDdaB/dWeDpvDDNgCzoMt4XrYCm6ADeE22Ejb1421fV0PPgm7wD9pu/0I7AA/UP1Aqn2JNwV2gZVhV01/G0vrSMijJHnihg00/a9H+fQN34T14FtwIPwbTPPwDN/lNO1R2ps/2SYdOOvn6RGd6X7W/4/t0nD7WO+q4/yP2qf/6V7WP2cf619jD+uf0179b+xfXbJ39a/Thj3b9it7V59VG7bovtV51IEbMHtmlegfnYvfL9v+nz5x8vTsc9L+zwpt/yMLbf9nFWn/l1aZU2RdjT1L7MOlfyArTP/ApID59wccula35lslTLly1JsFTs43zzs/MSd7evOmiAPmcyG122Tqt7K4z5RYCBLQhkoU94r/rj/hQv8c+Sgzl4lzaPvRn9Z4t34/OXg2YQycl+L9Jpb2I7eG1mu6tDsD+gjEbsacy1X2+v2Q781YTb8/fC0JUxgh1zf5smztVzDu1U2/QqLE8YP1BH9j7Dwx4+9lxP079OgjdH6axmH2E9R5jgHri2+SMH24ropGN+GkV4atOm3Pgw7fOOdlnCvOOT7CGef2xEaDmEjvcVzIvdG0XyRxhL83Q8W9hrRf/edZr+dx9fRG7YyNBDFR3uPGoWVA099a4qlS7HkSYVtx7yLnSaHd7EG2gXh26vrdxxIwZzAnTvsYtB9C763OgePeIdN7hyzNLktBfVGry/givAH/lZXrcYmvIuXI93T/RF+U+CXGZN0roYvYJ0Y0cSx1HXLHOBJFzqza6rIvInd+SaieipbJmVW9fu5zpVljXXrfNP4mVrKWuTSxT45o6Vjieon4k7UP6oSE/Yptqbq6slxLtIz6z/uZnLdo/1SKrifQTOJ82zPRGuY46C5jHXdzPtWb6CBuORF/cpxyxniWEMZeQ6GgMD1jVsbknPTpuZMLsi1JYw7x9ZEwF0c86fjc+YP7COdFTloOSVp6yrOSpX1wVXVPj88kzEOewdyfsdSdl7JGRIo7kfzDHZeRcn1vuDzWc66i/XMpqm9yg8QRHzHMEe8qdHus7e7XAvp0ZmXnj2fL0IAyP1PSU0Ht7GYg9iij+9JW4suLCNpvU8OeJ+mJM7pJ74r9I1cna51L/Jg0e0x/3yGNnznL0l/2kbg3dSe5eks6u5b3XVN2eua0rALL7FswVtLRNyKcDk/napLfrsecvQmDzOR1Z6ObVChxtIwweSdlr6mpd9aK+xDajO7gdSG0bD4gaW1k6r4Gcs7Nrpf0nHYZdJqyV1b8uN0V8JdcTLmxtAzmEl8vOX9GxARavw87fnD+qOUm176WgHuZM5k4MjPyKHO6v0F3CZ8V8aLjQ6fTQ1g=
*/
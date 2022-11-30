// Copyright (C) 2007 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

/**************************************************************************
 * This source file implements the Delta-stepping algorithm:              *
 *                                                                        *
 *   Ulrich Meyer and Peter Sanders. Parallel Shortest Path for Arbitrary *
 *   Graphs. In Proceedings from the 6th International Euro-Par           *
 *   Conference on Parallel Processing, pages 461--470, 2000.             *
 *                                                                        * 
 *   Ulrich Meyer, Peter Sanders: [Delta]-stepping: A Parallelizable      *
 *   Shortest Path Algorithm. J. Algorithms 49(1): 114-152, 2003.         *
 *                                                                        *
 * There are several potential optimizations we could still perform for   *
 * this algorithm implementation:                                         *
 *                                                                        *
 *   - Implement "shortcuts", which bound the number of reinsertions      *
 *     in a single bucket (to one). The computation of shortcuts looks    *
 *     expensive in a distributed-memory setting, but it could be         *
 *     ammortized over many queries.                                      *
 *                                                                        *
 *   - The size of the "buckets" data structure can be bounded to         *
 *     max_edge_weight/delta buckets, if we treat the buckets as a        *
 *     circular array.                                                    *
 *                                                                        *
 *   - If we partition light/heavy edges ahead of time, we could improve  *
 *     relaxation performance by only iterating over the right portion    *
 *     of the out-edge list each time.                                    *
 *                                                                        *
 *   - Implement a more sophisticated algorithm for guessing "delta",     *
 *     based on the shortcut-finding algorithm.                           *
 **************************************************************************/
#ifndef BOOST_GRAPH_DELTA_STEPPING_SHORTEST_PATHS_HPP
#define BOOST_GRAPH_DELTA_STEPPING_SHORTEST_PATHS_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <limits>
#include <list>
#include <vector>
#include <boost/graph/parallel/container_traits.hpp>
#include <boost/graph/parallel/properties.hpp>
#include <boost/graph/distributed/detail/dijkstra_shortest_paths.hpp>
#include <utility> // for std::pair
#include <functional> // for std::logical_or
#include <boost/graph/parallel/algorithm.hpp> // for all_reduce
#include <cassert>
#include <algorithm> // for std::min, std::max
#include <boost/graph/parallel/simple_trigger.hpp>

#ifdef PBGL_DELTA_STEPPING_DEBUG
#  include <iostream> // for std::cerr
#endif

namespace boost { namespace graph { namespace distributed {

template<typename Graph, typename PredecessorMap, typename DistanceMap, 
         typename EdgeWeightMap>
class delta_stepping_impl {
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  typedef typename graph_traits<Graph>::degree_size_type Degree;
  typedef typename property_traits<EdgeWeightMap>::value_type Dist;
  typedef typename boost::graph::parallel::process_group_type<Graph>::type 
    ProcessGroup;

  typedef std::list<Vertex> Bucket;
  typedef typename Bucket::iterator BucketIterator;
  typedef typename std::vector<Bucket*>::size_type BucketIndex;

  typedef detail::dijkstra_msg_value<DistanceMap, PredecessorMap> MessageValue;

  enum { 
    // Relax a remote vertex. The message contains a pair<Vertex,
    // MessageValue>, the first part of which is the vertex whose
    // tentative distance is being relaxed and the second part
    // contains either the new distance (if there is no predecessor
    // map) or a pair with the distance and predecessor.
    msg_relax 
  };

public:
  delta_stepping_impl(const Graph& g,
                      PredecessorMap predecessor, 
                      DistanceMap distance, 
                      EdgeWeightMap weight,
                      Dist delta);

  delta_stepping_impl(const Graph& g,
                      PredecessorMap predecessor, 
                      DistanceMap distance, 
                      EdgeWeightMap weight);

  void run(Vertex s);

private:
  // Relax the edge (u, v), creating a new best path of distance x.
  void relax(Vertex u, Vertex v, Dist x);

  // Synchronize all of the processes, by receiving all messages that
  // have not yet been received.
  void synchronize();

  // Handle a relax message that contains only the target and
  // distance. This kind of message will be received when the
  // predecessor map is a dummy_property_map.
  void handle_relax_message(Vertex v, Dist x) { relax(v, v, x); }

  // Handle a relax message that contains the source (predecessor),
  // target, and distance. This kind of message will be received when
  // the predecessor map is not a dummy_property_map.
  void handle_relax_message(Vertex v, const std::pair<Dist, Vertex>& p)
  { relax(p.second, v, p.first); }
  
  // Setup triggers for msg_relax messages
  void setup_triggers();

  void handle_msg_relax(int /*source*/, int /*tag*/,
                        const std::pair<Vertex, typename MessageValue::type>& data,
                        trigger_receive_context)
  { handle_relax_message(data.first, data.second); }

  const Graph& g;
  PredecessorMap predecessor;
  DistanceMap distance;
  EdgeWeightMap weight;
  Dist delta;
  ProcessGroup pg;
  typename property_map<Graph, vertex_owner_t>::const_type owner;
  typename property_map<Graph, vertex_local_t>::const_type local;

  // A "property map" that contains the position of each vertex in
  // whatever bucket it resides in.
  std::vector<BucketIterator> position_in_bucket;

  // Bucket data structure. The ith bucket contains all local vertices
  // with (tentative) distance in the range [i*delta,
  // (i+1)*delta). 
  std::vector<Bucket*> buckets;

  // This "dummy" list is used only so that we can initialize the
  // position_in_bucket property map with non-singular iterators. This
  // won't matter for most implementations of the C++ Standard
  // Library, but it avoids undefined behavior and allows us to run
  // with library "debug modes".
  std::list<Vertex> dummy_list;

  // A "property map" that states which vertices have been deleted
  // from the bucket in this iteration.
  std::vector<bool> vertex_was_deleted;
};

template<typename Graph, typename PredecessorMap, typename DistanceMap, 
         typename EdgeWeightMap>
delta_stepping_impl<Graph, PredecessorMap, DistanceMap, EdgeWeightMap>::
delta_stepping_impl(const Graph& g,
                    PredecessorMap predecessor, 
                    DistanceMap distance, 
                    EdgeWeightMap weight,
                    Dist delta)
    : g(g),
      predecessor(predecessor),
      distance(distance),
      weight(weight),
      delta(delta),
      pg(boost::graph::parallel::process_group_adl(g), attach_distributed_object()),
      owner(get(vertex_owner, g)),
      local(get(vertex_local, g))
{
  setup_triggers();
}

template<typename Graph, typename PredecessorMap, typename DistanceMap, 
         typename EdgeWeightMap>
delta_stepping_impl<Graph, PredecessorMap, DistanceMap, EdgeWeightMap>::
delta_stepping_impl(const Graph& g,
                    PredecessorMap predecessor, 
                    DistanceMap distance, 
                    EdgeWeightMap weight)
    : g(g),
      predecessor(predecessor),
      distance(distance),
      weight(weight),
      pg(boost::graph::parallel::process_group_adl(g), attach_distributed_object()),
      owner(get(vertex_owner, g)),
      local(get(vertex_local, g))
{
  using boost::parallel::all_reduce;
  using boost::parallel::maximum;
  using std::max;

  // Compute the maximum edge weight and degree
  Dist max_edge_weight = 0;
  Degree max_degree = 0;
  BGL_FORALL_VERTICES_T(u, g, Graph) {
    max_degree = max BOOST_PREVENT_MACRO_SUBSTITUTION (max_degree, out_degree(u, g));
    BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
      max_edge_weight = max BOOST_PREVENT_MACRO_SUBSTITUTION (max_edge_weight, get(weight, e));
  }

  max_edge_weight = all_reduce(pg, max_edge_weight, maximum<Dist>());
  max_degree = all_reduce(pg, max_degree, maximum<Degree>());

  // Take a guess at delta, based on what works well for random
  // graphs.
  delta = max_edge_weight / max_degree;
  if (delta == 0)
    delta = 1;

  setup_triggers();
}

template<typename Graph, typename PredecessorMap, typename DistanceMap, 
         typename EdgeWeightMap>
void
delta_stepping_impl<Graph, PredecessorMap, DistanceMap, EdgeWeightMap>::
run(Vertex s)
{
  Dist inf = (std::numeric_limits<Dist>::max)();

  // None of the vertices are stored in the bucket.
  position_in_bucket.clear();
  position_in_bucket.resize(num_vertices(g), dummy_list.end());

  // None of the vertices have been deleted
  vertex_was_deleted.clear();
  vertex_was_deleted.resize(num_vertices(g), false);

  // No path from s to any other vertex, yet
  BGL_FORALL_VERTICES_T(v, g, Graph)
    put(distance, v, inf);

  // The distance to the starting node is zero
  if (get(owner, s) == process_id(pg))
    // Put "s" into its bucket (bucket 0)
    relax(s, s, 0);
  else
    // Note that we know the distance to s is zero
    cache(distance, s, 0);

  BucketIndex max_bucket = (std::numeric_limits<BucketIndex>::max)();
  BucketIndex current_bucket = 0;
  do {
    // Synchronize with all of the other processes.
    synchronize();

    // Find the next bucket that has something in it.
    while (current_bucket < buckets.size() 
           && (!buckets[current_bucket] || buckets[current_bucket]->empty()))
      ++current_bucket;
    if (current_bucket >= buckets.size())
      current_bucket = max_bucket;

#ifdef PBGL_DELTA_STEPPING_DEBUG
    std::cerr << "#" << process_id(pg) << ": lowest bucket is #" 
              << current_bucket << std::endl;
#endif
    // Find the smallest bucket (over all processes) that has vertices
    // that need to be processed.
    using boost::parallel::all_reduce;
    using boost::parallel::minimum;
    current_bucket = all_reduce(pg, current_bucket, minimum<BucketIndex>());

    if (current_bucket == max_bucket)
      // There are no non-empty buckets in any process; exit. 
      break;

#ifdef PBGL_DELTA_STEPPING_DEBUG
    if (process_id(pg) == 0)
      std::cerr << "Processing bucket #" << current_bucket << std::endl;
#endif

    // Contains the set of vertices that have been deleted in the
    // relaxation of "light" edges. Note that we keep track of which
    // vertices were deleted with the property map
    // "vertex_was_deleted".
    std::vector<Vertex> deleted_vertices;

    // Repeatedly relax light edges
    bool nonempty_bucket;
    do {
      // Someone has work to do in this bucket.

      if (current_bucket < buckets.size() && buckets[current_bucket]) {
        Bucket& bucket = *buckets[current_bucket];
        // For each element in the bucket
        while (!bucket.empty()) {
          Vertex u = bucket.front();

#ifdef PBGL_DELTA_STEPPING_DEBUG
          std::cerr << "#" << process_id(pg) << ": processing vertex " 
                    << get(vertex_global, g, u).second << "@" 
                    << get(vertex_global, g, u).first
                    << std::endl;
#endif

          // Remove u from the front of the bucket
          bucket.pop_front();
          
          // Insert u into the set of deleted vertices, if it hasn't
          // been done already.
          if (!vertex_was_deleted[get(local, u)]) {
            vertex_was_deleted[get(local, u)] = true;
            deleted_vertices.push_back(u);
          }

          // Relax each light edge. 
          Dist u_dist = get(distance, u);
          BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
            if (get(weight, e) <= delta) // light edge
              relax(u, target(e, g), u_dist + get(weight, e));
        }
      }

      // Synchronize with all of the other processes.
      synchronize();

      // Is the bucket empty now?
      nonempty_bucket = (current_bucket < buckets.size() 
                         && buckets[current_bucket]
                         && !buckets[current_bucket]->empty());
     } while (all_reduce(pg, nonempty_bucket, std::logical_or<bool>()));

    // Relax heavy edges for each of the vertices that we previously
    // deleted.
    for (typename std::vector<Vertex>::iterator iter = deleted_vertices.begin();
         iter != deleted_vertices.end(); ++iter) {
      // Relax each heavy edge. 
      Vertex u = *iter;
      Dist u_dist = get(distance, u);
      BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
        if (get(weight, e) > delta) // heavy edge
          relax(u, target(e, g), u_dist + get(weight, e)); 
    }

    // Go to the next bucket: the current bucket must already be empty.
    ++current_bucket;
  } while (true);

  // Delete all of the buckets.
  for (typename std::vector<Bucket*>::iterator iter = buckets.begin();
       iter != buckets.end(); ++iter) {
    if (*iter) {
      delete *iter;
      *iter = 0;
    }
  }
}

template<typename Graph, typename PredecessorMap, typename DistanceMap, 
         typename EdgeWeightMap>
void
delta_stepping_impl<Graph, PredecessorMap, DistanceMap, EdgeWeightMap>::
relax(Vertex u, Vertex v, Dist x) 
{
#ifdef PBGL_DELTA_STEPPING_DEBUG
  std::cerr << "#" << process_id(pg) << ": relax(" 
            << get(vertex_global, g, u).second << "@" 
            << get(vertex_global, g, u).first << ", " 
            << get(vertex_global, g, v).second << "@" 
            << get(vertex_global, g, v).first << ", "
            << x << ")" << std::endl;
#endif

  if (x < get(distance, v)) {
    // We're relaxing the edge to vertex v.
    if (get(owner, v) == process_id(pg)) {
      // Compute the new bucket index for v
      BucketIndex new_index = static_cast<BucketIndex>(x / delta);
      
      // Make sure there is enough room in the buckets data structure.
      if (new_index >= buckets.size()) buckets.resize(new_index + 1, 0);

      // Make sure that we have allocated the bucket itself.
      if (!buckets[new_index]) buckets[new_index] = new Bucket;

      if (get(distance, v) != (std::numeric_limits<Dist>::max)()
          && !vertex_was_deleted[get(local, v)]) {
        // We're moving v from an old bucket into a new one. Compute
        // the old index, then splice it in.
        BucketIndex old_index 
          = static_cast<BucketIndex>(get(distance, v) / delta);
        buckets[new_index]->splice(buckets[new_index]->end(),
                                   *buckets[old_index],
                                   position_in_bucket[get(local, v)]);
      } else {
        // We're inserting v into a bucket for the first time. Put it
        // at the end.
        buckets[new_index]->push_back(v);
      }

      // v is now at the last position in the new bucket
      position_in_bucket[get(local, v)] = buckets[new_index]->end();
      --position_in_bucket[get(local, v)];

      // Update predecessor and tentative distance information
      put(predecessor, v, u);
      put(distance, v, x);
    } else {
#ifdef PBGL_DELTA_STEPPING_DEBUG
      std::cerr << "#" << process_id(pg) << ": sending relax(" 
                << get(vertex_global, g, u).second << "@" 
                << get(vertex_global, g, u).first << ", " 
                << get(vertex_global, g, v).second << "@" 
                << get(vertex_global, g, v).first << ", "
            << x << ") to " << get(owner, v) << std::endl;
      
#endif
      // The vertex is remote: send a request to the vertex's owner
      send(pg, get(owner, v), msg_relax, 
           std::make_pair(v, MessageValue::create(x, u)));

      // Cache tentative distance information
      cache(distance, v, x);
    }
  }
}

template<typename Graph, typename PredecessorMap, typename DistanceMap, 
         typename EdgeWeightMap>
void
delta_stepping_impl<Graph, PredecessorMap, DistanceMap, EdgeWeightMap>::
synchronize()
{
  using boost::parallel::synchronize;

  // Synchronize at the process group level.
  synchronize(pg);

  // Receive any relaxation request messages.
//   typedef typename ProcessGroup::process_id_type process_id_type;
//   while (optional<std::pair<process_id_type, int> > stp = probe(pg)) {
//     // Receive the relaxation message
//     assert(stp->second == msg_relax);
//     std::pair<Vertex, typename MessageValue::type> data;
//     receive(pg, stp->first, stp->second, data);

//     // Turn it into a "relax" call
//     handle_relax_message(data.first, data.second);
//   }
}

template<typename Graph, typename PredecessorMap, typename DistanceMap, 
         typename EdgeWeightMap>
void 
delta_stepping_impl<Graph, PredecessorMap, DistanceMap, EdgeWeightMap>::
setup_triggers() 
{
  using boost::graph::parallel::simple_trigger;
        
  simple_trigger(pg, msg_relax, this, 
                 &delta_stepping_impl::handle_msg_relax);
}

template<typename Graph, typename PredecessorMap, typename DistanceMap, 
         typename EdgeWeightMap>
void 
delta_stepping_shortest_paths
  (const Graph& g,
   typename graph_traits<Graph>::vertex_descriptor s,
   PredecessorMap predecessor, DistanceMap distance, EdgeWeightMap weight,
   typename property_traits<EdgeWeightMap>::value_type delta)
{
  // The "distance" map needs to act like one, retrieving the default
  // value of infinity.
  set_property_map_role(vertex_distance, distance);

  // Construct the implementation object, which will perform all of
  // the actual work.
  delta_stepping_impl<Graph, PredecessorMap, DistanceMap, EdgeWeightMap>
    impl(g, predecessor, distance, weight, delta);

  // Run the delta-stepping algorithm. The results will show up in
  // "predecessor" and "weight".
  impl.run(s);
}

template<typename Graph, typename PredecessorMap, typename DistanceMap, 
         typename EdgeWeightMap>
void 
delta_stepping_shortest_paths
  (const Graph& g,
   typename graph_traits<Graph>::vertex_descriptor s,
   PredecessorMap predecessor, DistanceMap distance, EdgeWeightMap weight)
{
  // The "distance" map needs to act like one, retrieving the default
  // value of infinity.
  set_property_map_role(vertex_distance, distance);

  // Construct the implementation object, which will perform all of
  // the actual work.
  delta_stepping_impl<Graph, PredecessorMap, DistanceMap, EdgeWeightMap>
    impl(g, predecessor, distance, weight);

  // Run the delta-stepping algorithm. The results will show up in
  // "predecessor" and "weight".
  impl.run(s);
}
   
} } } // end namespace boost::graph::distributed

#endif // BOOST_GRAPH_DELTA_STEPPING_SHORTEST_PATHS_HPP

/* delta_stepping_shortest_paths.hpp
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
*/
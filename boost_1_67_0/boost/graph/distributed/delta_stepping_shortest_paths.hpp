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
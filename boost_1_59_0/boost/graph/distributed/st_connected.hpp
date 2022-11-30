// Copyright (C) 2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_ST_CONNECTED_HPP
#define BOOST_GRAPH_DISTRIBUTED_ST_CONNECTED_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/two_bit_color_map.hpp>
#include <boost/graph/distributed/queue.hpp>
#include <boost/pending/queue.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/parallel/container_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/parallel/algorithm.hpp>
#include <utility>
#include <boost/optional.hpp>

namespace boost { namespace graph { namespace distributed {

namespace detail {
  struct pair_and_or 
  {
    std::pair<bool, bool> 
    operator()(std::pair<bool, bool> x, std::pair<bool, bool> y) const
    {
      return std::pair<bool, bool>(x.first && y.first,
                                   x.second || y.second);
    }
  };

} // end namespace detail

template<typename DistributedGraph, typename ColorMap, typename OwnerMap>
bool 
st_connected(const DistributedGraph& g, 
             typename graph_traits<DistributedGraph>::vertex_descriptor s,
             typename graph_traits<DistributedGraph>::vertex_descriptor t,
             ColorMap color, OwnerMap owner)
{
  using boost::graph::parallel::process_group;
  using boost::graph::parallel::process_group_type;
  using boost::parallel::all_reduce;

  typedef typename property_traits<ColorMap>::value_type Color;
  typedef color_traits<Color> ColorTraits;
  typedef typename process_group_type<DistributedGraph>::type ProcessGroup;
  typedef typename ProcessGroup::process_id_type ProcessID;
  typedef typename graph_traits<DistributedGraph>::vertex_descriptor Vertex;

  // Set all vertices to white (unvisited)
  BGL_FORALL_VERTICES_T(v, g, DistributedGraph)
    put(color, v, ColorTraits::white());

  // "color" plays the role of a color map, with no synchronization.
  set_property_map_role(vertex_color, color);
  color.set_consistency_model(0);

  // Vertices found from the source are grey
  put(color, s, ColorTraits::gray());

  // Vertices found from the target are green
  put(color, t, ColorTraits::green());

  ProcessGroup pg = process_group(g);
  ProcessID rank = process_id(pg);

  // Build a local queue
  queue<Vertex> Q;
  if (get(owner, s) == rank) Q.push(s);
  if (get(owner, t) == rank) Q.push(t);

  queue<Vertex> other_Q;

  while (true) {
    bool found = false;

    // Process all vertices in the local queue
    while (!found && !Q.empty()) {
      Vertex u = Q.top(); Q.pop();
      Color u_color = get(color, u);

      BGL_FORALL_OUTEDGES_T(u, e, g, DistributedGraph) {
        Vertex v = target(e, g);
        Color v_color = get(color, v);
        if (v_color == ColorTraits::white()) {
          // We have not seen "v" before; mark it with the same color as u
          Color u_color = get(color, u);
          put(color, v, u_color);

          // Either push v into the local queue or send it off to its
          // owner.
          ProcessID v_owner = get(owner, v);
          if (v_owner == rank) 
            other_Q.push(v);
          else
            send(pg, v_owner, 0, 
                 std::make_pair(v, u_color == ColorTraits::gray()));
        } else if (v_color != ColorTraits::black() && u_color != v_color) {
          // Colors have collided. We're done!
          found = true;
          break;
        }
      }

      // u is done, so mark it black
      put(color, u, ColorTraits::black());
    }

    // Ensure that all transmitted messages have been received.
    synchronize(pg);

    // Move all of the send-to-self values into the local Q.
    other_Q.swap(Q);

    if (!found) {
      // Receive all messages
      while (optional<std::pair<ProcessID, int> > msg = probe(pg)) {
        std::pair<Vertex, bool> data;
        receive(pg, msg->first, msg->second, data);
        
        // Determine the colors of u and v, the source and target
        // vertices (v is local).
        Vertex v = data.first;
        Color v_color = get(color, v);
        Color u_color = data.second? ColorTraits::gray() : ColorTraits::green();
        if (v_color == ColorTraits::white()) {
          // v had no color before, so give it u's color and push it
          // into the queue.
          Q.push(v);
          put(color, v, u_color);
        } else if (v_color != ColorTraits::black() && u_color != v_color) {
          // Colors have collided. We're done!
          found = true;
          break;
        }
      }
    }

    // Check if either all queues are empty or 
    std::pair<bool, bool> results = all_reduce(pg, 
            boost::parallel::detail::make_untracked_pair(Q.empty(), found),
            detail::pair_and_or());

    // If someone found the answer, we're done!
    if (results.second)
      return true;

    // If all queues are empty, we're done.
    if (results.first)
      return false;
  }
}

template<typename DistributedGraph, typename ColorMap>
inline bool 
st_connected(const DistributedGraph& g, 
             typename graph_traits<DistributedGraph>::vertex_descriptor s,
             typename graph_traits<DistributedGraph>::vertex_descriptor t,
             ColorMap color)
{
  return st_connected(g, s, t, color, get(vertex_owner, g));
}

template<typename DistributedGraph>
inline bool 
st_connected(const DistributedGraph& g, 
             typename graph_traits<DistributedGraph>::vertex_descriptor s,
             typename graph_traits<DistributedGraph>::vertex_descriptor t)
{
  return st_connected(g, s, t, 
                      make_two_bit_color_map(num_vertices(g),
                                             get(vertex_index, g)));
}

} } } // end namespace boost::graph::distributed

#endif // BOOST_GRAPH_DISTRIBUTED_ST_CONNECTED_HPP

/* st_connected.hpp
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
*/
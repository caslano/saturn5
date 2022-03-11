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
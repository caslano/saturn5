// Copyright (C) 2005-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_FRUCHTERMAN_REINGOLD_HPP
#define BOOST_GRAPH_DISTRIBUTED_FRUCHTERMAN_REINGOLD_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/fruchterman_reingold.hpp>

namespace boost { namespace graph { namespace distributed {

class simple_tiling
{
 public:
  simple_tiling(int columns, int rows, bool flip = true) 
    : columns(columns), rows(rows), flip(flip)
  {
  }

  // Convert from a position (x, y) in the tiled display into a
  // processor ID number
  int operator()(int x, int y) const
  {
    return flip? (rows - y - 1) * columns + x : y * columns + x;
  }

  // Convert from a process ID to a position (x, y) in the tiled
  // display
  std::pair<int, int> operator()(int id)
  {
    int my_col = id % columns;
    int my_row = flip? rows - (id / columns) - 1 : id / columns;
    return std::make_pair(my_col, my_row);
  }

  int columns, rows;

 private:
  bool flip;
};

// Force pairs function object that does nothing
struct no_force_pairs
{
  template<typename Graph, typename ApplyForce>
  void operator()(const Graph&, const ApplyForce&)
  {
  }
};

// Computes force pairs in the distributed case.
template<typename PositionMap, typename DisplacementMap, typename LocalForces,
         typename NonLocalForces = no_force_pairs>
class distributed_force_pairs_proxy
{
 public:
  distributed_force_pairs_proxy(const PositionMap& position, 
                                const DisplacementMap& displacement,
                                const LocalForces& local_forces,
                                const NonLocalForces& nonlocal_forces = NonLocalForces())
    : position(position), displacement(displacement), 
      local_forces(local_forces), nonlocal_forces(nonlocal_forces)
  {
  }

  template<typename Graph, typename ApplyForce>
  void operator()(const Graph& g, ApplyForce apply_force)
  {
    // Flush remote displacements
    displacement.flush();

    // Receive updated positions for all of our neighbors
    synchronize(position);

    // Reset remote displacements 
    displacement.reset();

    // Compute local repulsive forces
    local_forces(g, apply_force);

    // Compute neighbor repulsive forces
    nonlocal_forces(g, apply_force);
  }

 protected:
  PositionMap position;
  DisplacementMap displacement;
  LocalForces local_forces;
  NonLocalForces nonlocal_forces;
};

template<typename PositionMap, typename DisplacementMap, typename LocalForces>
inline 
distributed_force_pairs_proxy<PositionMap, DisplacementMap, LocalForces>
make_distributed_force_pairs(const PositionMap& position, 
                             const DisplacementMap& displacement,
                             const LocalForces& local_forces)
{
  typedef 
    distributed_force_pairs_proxy<PositionMap, DisplacementMap, LocalForces>
    result_type;
  return result_type(position, displacement, local_forces);
}

template<typename PositionMap, typename DisplacementMap, typename LocalForces,
         typename NonLocalForces>
inline 
distributed_force_pairs_proxy<PositionMap, DisplacementMap, LocalForces,
                              NonLocalForces>
make_distributed_force_pairs(const PositionMap& position, 
                             const DisplacementMap& displacement,
                             const LocalForces& local_forces,
                             const NonLocalForces& nonlocal_forces)
{
  typedef 
    distributed_force_pairs_proxy<PositionMap, DisplacementMap, LocalForces,
                                  NonLocalForces>
      result_type;
  return result_type(position, displacement, local_forces, nonlocal_forces);
}

// Compute nonlocal force pairs based on the shared borders with
// adjacent tiles.
template<typename PositionMap>
class neighboring_tiles_force_pairs
{
 public:
  typedef typename property_traits<PositionMap>::value_type Point;
  typedef typename point_traits<Point>::component_type Dim;

  enum bucket_position { left, top, right, bottom, end_position };
  
  neighboring_tiles_force_pairs(PositionMap position, Point origin,
                                Point extent, simple_tiling tiling)
    : position(position), origin(origin), extent(extent), tiling(tiling)
  {
  }

  template<typename Graph, typename ApplyForce>
  void operator()(const Graph& g, ApplyForce apply_force)
  {
    // TBD: Do this some smarter way
    if (tiling.columns == 1 && tiling.rows == 1)
      return;

    typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
#ifndef BOOST_NO_STDC_NAMESPACE
    using std::sqrt;
#endif // BOOST_NO_STDC_NAMESPACE

    // TBD: num_vertices(g) should be the global number of vertices?
    Dim two_k = Dim(2) * sqrt(extent[0] * extent[1] / num_vertices(g));

    std::vector<vertex_descriptor> my_vertices[4];
    std::vector<vertex_descriptor> neighbor_vertices[4];
   
    // Compute cutoff positions
    Dim cutoffs[4];
    cutoffs[left] = origin[0] + two_k;
    cutoffs[top] = origin[1] + two_k;
    cutoffs[right] = origin[0] + extent[0] - two_k;
    cutoffs[bottom] = origin[1] + extent[1] - two_k;

    // Compute neighbors
    typename PositionMap::process_group_type pg = position.process_group();
    std::pair<int, int> my_tile = tiling(process_id(pg));
    int neighbors[4] = { -1, -1, -1, -1 } ;
    if (my_tile.first > 0)
      neighbors[left] = tiling(my_tile.first - 1, my_tile.second);
    if (my_tile.second > 0)
      neighbors[top] = tiling(my_tile.first, my_tile.second - 1);
    if (my_tile.first < tiling.columns - 1)
      neighbors[right] = tiling(my_tile.first + 1, my_tile.second);
    if (my_tile.second < tiling.rows - 1)
      neighbors[bottom] = tiling(my_tile.first, my_tile.second + 1);

    // Sort vertices along the edges into buckets
    BGL_FORALL_VERTICES_T(v, g, Graph) {
      if (position[v][0] <= cutoffs[left]) my_vertices[left].push_back(v); 
      if (position[v][1] <= cutoffs[top]) my_vertices[top].push_back(v); 
      if (position[v][0] >= cutoffs[right]) my_vertices[right].push_back(v); 
      if (position[v][1] >= cutoffs[bottom]) my_vertices[bottom].push_back(v); 
    }

    // Send vertices to neighbors, and gather our neighbors' vertices
    bucket_position pos;
    for (pos = left; pos < end_position; pos = bucket_position(pos + 1)) {
      if (neighbors[pos] != -1) {
        send(pg, neighbors[pos], 0, my_vertices[pos].size());
        if (!my_vertices[pos].empty())
          send(pg, neighbors[pos], 1, 
               &my_vertices[pos].front(), my_vertices[pos].size());
      }
    }

    // Pass messages around
    synchronize(pg);
    
    // Receive neighboring vertices
    for (pos = left; pos < end_position; pos = bucket_position(pos + 1)) {
      if (neighbors[pos] != -1) {
        std::size_t incoming_vertices;
        receive(pg, neighbors[pos], 0, incoming_vertices);

        if (incoming_vertices) {
          neighbor_vertices[pos].resize(incoming_vertices);
          receive(pg, neighbors[pos], 1, &neighbor_vertices[pos].front(),
                  incoming_vertices);
        }
      }
    }

    // For each neighboring vertex, we need to get its current position
    for (pos = left; pos < end_position; pos = bucket_position(pos + 1))
      for (typename std::vector<vertex_descriptor>::iterator i = 
             neighbor_vertices[pos].begin(); 
           i != neighbor_vertices[pos].end();
           ++i)
        request(position, *i);
    synchronize(position);

    // Apply forces in adjacent bins. This is O(n^2) in the worst
    // case. Oh well.
    for (pos = left; pos < end_position; pos = bucket_position(pos + 1)) {
      for (typename std::vector<vertex_descriptor>::iterator i = 
             my_vertices[pos].begin(); 
           i != my_vertices[pos].end();
           ++i)
        for (typename std::vector<vertex_descriptor>::iterator j = 
               neighbor_vertices[pos].begin(); 
             j != neighbor_vertices[pos].end();
             ++j)
          apply_force(*i, *j);
    }
  }

 protected:
  PositionMap position;
  Point origin;
  Point extent;
  simple_tiling tiling;
};

template<typename PositionMap>
inline neighboring_tiles_force_pairs<PositionMap>
make_neighboring_tiles_force_pairs
 (PositionMap position, 
  typename property_traits<PositionMap>::value_type origin,
  typename property_traits<PositionMap>::value_type extent,
  simple_tiling tiling)
{
  return neighboring_tiles_force_pairs<PositionMap>(position, origin, extent,
                                                    tiling);
}

template<typename DisplacementMap, typename Cooling>
class distributed_cooling_proxy
{
 public:
  typedef typename Cooling::result_type result_type;

  distributed_cooling_proxy(const DisplacementMap& displacement,
                            const Cooling& cooling)
    : displacement(displacement), cooling(cooling)
  {
  }

  result_type operator()()
  {
    // Accumulate displacements computed on each processor
    synchronize(displacement.data->process_group);

    // Allow the underlying cooling to occur
    return cooling();
  }

 protected:
  DisplacementMap displacement;
  Cooling cooling;
};

template<typename DisplacementMap, typename Cooling>
inline distributed_cooling_proxy<DisplacementMap, Cooling>
make_distributed_cooling(const DisplacementMap& displacement,
                         const Cooling& cooling)
{
  typedef distributed_cooling_proxy<DisplacementMap, Cooling> result_type;
  return result_type(displacement, cooling);
}

template<typename Point>
struct point_accumulating_reducer {
  BOOST_STATIC_CONSTANT(bool, non_default_resolver = true);

  template<typename K>
  Point operator()(const K&) const { return Point(); }

  template<typename K>
  Point operator()(const K&, const Point& p1, const Point& p2) const 
  { return Point(p1[0] + p2[0], p1[1] + p2[1]); }
};

template<typename Graph, typename PositionMap, 
         typename AttractiveForce, typename RepulsiveForce,
         typename ForcePairs, typename Cooling, typename DisplacementMap>
void
fruchterman_reingold_force_directed_layout
 (const Graph&    g,
  PositionMap     position,
  typename property_traits<PositionMap>::value_type const& origin,
  typename property_traits<PositionMap>::value_type const& extent,
  AttractiveForce attractive_force,
  RepulsiveForce  repulsive_force,
  ForcePairs      force_pairs,
  Cooling         cool,
  DisplacementMap displacement)
{
  typedef typename property_traits<PositionMap>::value_type Point;

  // Reduction in the displacement map involves summing the forces
  displacement.set_reduce(point_accumulating_reducer<Point>());

  // We need to track the positions of all of our neighbors
  BGL_FORALL_VERTICES_T(u, g, Graph)
    BGL_FORALL_ADJ_T(u, v, g, Graph)
      request(position, v);

  // Invoke the "sequential" Fruchterman-Reingold implementation
  boost::fruchterman_reingold_force_directed_layout
    (g, position, origin, extent,
     attractive_force, repulsive_force,
     make_distributed_force_pairs(position, displacement, force_pairs),
     make_distributed_cooling(displacement, cool),
     displacement);
}

template<typename Graph, typename PositionMap, 
         typename AttractiveForce, typename RepulsiveForce,
         typename ForcePairs, typename Cooling, typename DisplacementMap>
void
fruchterman_reingold_force_directed_layout
 (const Graph&    g,
  PositionMap     position,
  typename property_traits<PositionMap>::value_type const& origin,
  typename property_traits<PositionMap>::value_type const& extent,
  AttractiveForce attractive_force,
  RepulsiveForce  repulsive_force,
  ForcePairs      force_pairs,
  Cooling         cool,
  DisplacementMap displacement,
  simple_tiling   tiling)
{
  typedef typename property_traits<PositionMap>::value_type Point;

  // Reduction in the displacement map involves summing the forces
  displacement.set_reduce(point_accumulating_reducer<Point>());

  // We need to track the positions of all of our neighbors
  BGL_FORALL_VERTICES_T(u, g, Graph)
    BGL_FORALL_ADJ_T(u, v, g, Graph)
      request(position, v);

  // Invoke the "sequential" Fruchterman-Reingold implementation
  boost::fruchterman_reingold_force_directed_layout
    (g, position, origin, extent,
     attractive_force, repulsive_force,
     make_distributed_force_pairs
      (position, displacement, force_pairs,
       make_neighboring_tiles_force_pairs(position, origin, extent, tiling)),
     make_distributed_cooling(displacement, cool),
     displacement);
}

} } } // end namespace boost::graph::distributed

#endif // BOOST_GRAPH_DISTRIBUTED_FRUCHTERMAN_REINGOLD_HPP

/* fruchterman_reingold.hpp
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
*/
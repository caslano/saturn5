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
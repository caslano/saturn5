// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_PARALLEL_DIJKSTRA_HPP
#define BOOST_GRAPH_PARALLEL_DIJKSTRA_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/distributed/concepts.hpp>
#include <boost/graph/parallel/properties.hpp>
#include <boost/graph/distributed/crauser_et_al_shortest_paths.hpp>
#include <boost/graph/distributed/eager_dijkstra_shortest_paths.hpp>

namespace boost {

  namespace graph { namespace detail {

    
    template<typename Lookahead>
    struct parallel_dijkstra_impl2
    {
      template<typename DistributedGraph, typename DijkstraVisitor,
               typename PredecessorMap, typename DistanceMap, 
               typename WeightMap, typename IndexMap, typename ColorMap, 
               typename Compare, typename Combine, typename DistInf, 
               typename DistZero>
      static void 
      run(const DistributedGraph& g,
          typename graph_traits<DistributedGraph>::vertex_descriptor s,
          PredecessorMap predecessor, DistanceMap distance, 
          typename property_traits<DistanceMap>::value_type lookahead,
          WeightMap weight, IndexMap index_map, ColorMap color_map,
          Compare compare, Combine combine, DistInf inf, DistZero zero,
          DijkstraVisitor vis)
      {
        eager_dijkstra_shortest_paths(g, s, predecessor, distance, lookahead,
                                      weight, index_map, color_map, compare,
                                      combine, inf, zero, vis);
      }
    };

    template<>
    struct parallel_dijkstra_impl2< ::boost::param_not_found >
    {
      template<typename DistributedGraph, typename DijkstraVisitor,
               typename PredecessorMap, typename DistanceMap, 
               typename WeightMap, typename IndexMap, typename ColorMap, 
               typename Compare, typename Combine, typename DistInf, 
               typename DistZero>
      static void 
      run(const DistributedGraph& g,
          typename graph_traits<DistributedGraph>::vertex_descriptor s,
          PredecessorMap predecessor, DistanceMap distance, 
          ::boost::param_not_found,
          WeightMap weight, IndexMap index_map, ColorMap color_map,
          Compare compare, Combine combine, DistInf inf, DistZero zero,
          DijkstraVisitor vis)
      {
        crauser_et_al_shortest_paths(g, s, predecessor, distance, weight,
                                     index_map, color_map, compare, combine,
                                     inf, zero, vis);
      }
    };

    template<typename ColorMap>
    struct parallel_dijkstra_impl
    {
      template<typename DistributedGraph, typename DijkstraVisitor,
               typename PredecessorMap, typename DistanceMap, 
               typename Lookahead, typename WeightMap, typename IndexMap,
               typename Compare, typename Combine, 
               typename DistInf, typename DistZero>
      static void 
      run(const DistributedGraph& g,
          typename graph_traits<DistributedGraph>::vertex_descriptor s,
          PredecessorMap predecessor, DistanceMap distance, 
          Lookahead lookahead,
          WeightMap weight, IndexMap index_map, ColorMap color_map,
          Compare compare, Combine combine, DistInf inf, DistZero zero,
          DijkstraVisitor vis)
      {
        graph::detail::parallel_dijkstra_impl2<Lookahead>
          ::run(g, s, predecessor, distance, lookahead, weight, index_map,
                color_map, compare, combine, inf, zero, vis);
      }
    };
    
    template<>
    struct parallel_dijkstra_impl< ::boost::param_not_found >
    {
    private:
      template<typename DistributedGraph, typename DijkstraVisitor,
               typename PredecessorMap, typename DistanceMap, 
               typename Lookahead, typename WeightMap, typename IndexMap,
               typename ColorMap, typename Compare, typename Combine, 
               typename DistInf, typename DistZero>
      static void 
      run_impl(const DistributedGraph& g,
               typename graph_traits<DistributedGraph>::vertex_descriptor s,
               PredecessorMap predecessor, DistanceMap distance, 
               Lookahead lookahead, WeightMap weight, IndexMap index_map, 
               ColorMap color_map, Compare compare, Combine combine, 
               DistInf inf, DistZero zero, DijkstraVisitor vis)
      {
        BGL_FORALL_VERTICES_T(u, g, DistributedGraph)
          BGL_FORALL_OUTEDGES_T(u, e, g, DistributedGraph)
            local_put(color_map, target(e, g), white_color);

        graph::detail::parallel_dijkstra_impl2<Lookahead>
          ::run(g, s, predecessor, distance, lookahead, weight, index_map,
                color_map, compare, combine, inf, zero, vis);
      }

    public:
      template<typename DistributedGraph, typename DijkstraVisitor,
               typename PredecessorMap, typename DistanceMap, 
               typename Lookahead, typename WeightMap, typename IndexMap,
               typename Compare, typename Combine, 
               typename DistInf, typename DistZero>
      static void 
      run(const DistributedGraph& g,
          typename graph_traits<DistributedGraph>::vertex_descriptor s,
          PredecessorMap predecessor, DistanceMap distance, 
          Lookahead lookahead, WeightMap weight, IndexMap index_map, 
          ::boost::param_not_found,
          Compare compare, Combine combine, DistInf inf, DistZero zero,
          DijkstraVisitor vis)
      {
        typedef typename graph_traits<DistributedGraph>::vertices_size_type
          vertices_size_type;

        vertices_size_type n = num_vertices(g);
        std::vector<default_color_type> colors(n, white_color);

        run_impl(g, s, predecessor, distance, lookahead, weight, index_map,
                 make_iterator_property_map(colors.begin(), index_map),
                 compare, combine, inf, zero, vis);
      }
    };
  } } // end namespace graph::detail


  /** Dijkstra's single-source shortest paths algorithm for distributed
   * graphs.
   *
   * Also implements the heuristics of:
   *
   *   Andreas Crauser, Kurt Mehlhorn, Ulrich Meyer, and Peter
   *   Sanders. A Parallelization of Dijkstra's Shortest Path
   *   Algorithm. In Lubos Brim, Jozef Gruska, and Jiri Zlatuska,
   *   editors, Mathematical Foundations of Computer Science (MFCS),
   *   volume 1450 of Lecture Notes in Computer Science, pages
   *   722--731, 1998. Springer.
   */
  template<typename DistributedGraph, typename DijkstraVisitor,
           typename PredecessorMap, typename DistanceMap,
           typename WeightMap, typename IndexMap, typename Compare,
           typename Combine, typename DistInf, typename DistZero,
           typename T, typename Tag, typename Base>
  inline
  void
  dijkstra_shortest_paths
    (const DistributedGraph& g,
     typename graph_traits<DistributedGraph>::vertex_descriptor s,
     PredecessorMap predecessor, DistanceMap distance, WeightMap weight,
     IndexMap index_map,
     Compare compare, Combine combine, DistInf inf, DistZero zero,
     DijkstraVisitor vis,
     const bgl_named_params<T, Tag, Base>& params
     BOOST_GRAPH_ENABLE_IF_MODELS_PARM(DistributedGraph,distributed_graph_tag))
  {
    typedef typename graph_traits<DistributedGraph>::vertices_size_type
      vertices_size_type;

    // Build a distributed property map for vertex colors, if we need it
    bool use_default_color_map 
      = is_default_param(get_param(params, vertex_color));
    vertices_size_type n = use_default_color_map? num_vertices(g) : 1;
    std::vector<default_color_type> color(n, white_color);
    typedef iterator_property_map<std::vector<default_color_type>::iterator,
                                  IndexMap> DefColorMap;
    DefColorMap color_map(color.begin(), index_map);

    typedef typename get_param_type< vertex_color_t, bgl_named_params<T, Tag, Base> >::type color_map_type;

    graph::detail::parallel_dijkstra_impl<color_map_type>
      ::run(g, s, predecessor, distance, 
            get_param(params, lookahead_t()),
            weight, index_map,
            get_param(params, vertex_color),
            compare, combine, inf, zero, vis);
  }
} // end namespace boost

#endif // BOOST_GRAPH_PARALLEL_DIJKSTRA_HPP

/* dijkstra_shortest_paths.hpp
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
*/
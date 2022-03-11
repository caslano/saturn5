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
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
GLnLrwPQY8DgfiaOoPkBRuYxegB2+CifrE/3kTDAb4zIh3YfMdT2GxuqL4C8eH2BZQH6Avdr3+FNGMTWtZgnCJfWSMatNadRGNAxsN3J5EGRvVCGi9/LdE1zf9jkoPF9xtpkfH20L157f6gA3YNccWPPJKPjPt6MzU4St3wz3r+CxK7EbIs/s/F+/1r6u2X8RNOPrE2Y8fzCKO1T5WSpyvW4HA/KFxnQL3Y8H6/WbU1kPF+vzx/2YnV3WKfFPTns3Az1r/lu9qAx68n3b+x1X+OKcyYF7UMTK/KunNnsQ2P8bqCkPc2VrmPxIsLZe2sFjX2afbyKzr8wY5adJb7bXHWdbrlfjxUZb+8h7mOYF9LVETB3JPsS3S/lALa24meHK0R3QOeWNBb3+10tGOcPHpsln3T8dhysI/4edRU3bp+ocy5qiJ+9rm7OCGT+MdbMyXmy452Oswbt08F+hnkZ+RnTkOl+aK0kjrtcjZ1RIfMwEnU8uLL42e8aoDoZJ8SPt6zY+3nE2OPgpnw/KuEY2xa7Q+9XE+d0ZAMc3azKTpfZr6WMuB12Fd3TpKrm/fdNJT+4y73pS0+wZqJPs1HjTsAlSdz3OKJZTXMR5WCZo4Z93ZJ3ufnTMgrNHimJzbz+D1LH1GesIF/SsRd5tKTjNddzPJNNi8zV2CwMHZteleTjoUQfu6tc522EjFvfInuGIFezH9lLiboPrj3GrGPZyIh/NWZNwH5la73HhFkH1wfIb+D4RmMnrjPYp8w/Tv1OM3ucurBJ6J6h05uE7hk6rkno/qBlm4Tu+/lp49Bx7322zMS3tXHoePZ6W2bOcW3j0PHs6UbWRuzTmvrtrcVOGQman0JdFTI/ZVcxY9x7gse4RdYruN4V2YigsWveV0Hj1ua5NHpYJ0QuzxF+A8fXTXkNqr/Lxlry663rrl0AMypSlzeX+nvy9MmF6VTi6QWF+fKcpuOGHpwkUN9j6rexlag6LwPEXt5R3XIh8+/hlJEzUbYM1HrbhGtgdKz6ir2SozYp1Gcfe7apM9LEva6jOX9VR07jSLX3RCtSHyUj6yB+ajgaWdESbrIJV8W8M6wi72p3C6/7QLU7rKFij7QSTZ1UOC3Pp55j9hXSNGg9xv6pXpnWvVlyPg9VoU+/a6ToD5EfhZPMOa8RP5eFnLMd9UYpy/f83cRzuEF1SuZjjiVyD7mTNyO7BXOrmdslz788p2nhnlMt4/VaBO0HJOlNF30+331ODtqTLOA+ql7GkABdi0tMeTP3QeRNjD+TbyIfZ/xrnhXZoyzOe+FaLivCevDpFHK4hV0+CegtovImC1NG1X9tU0bXir2sow5/7X3GJArz3XC9+NnOfJU4LbP+eGqYe7RcxrsTQsprf/yuNOeI1PLqD58atty1l/gGh8Rvv0fz2JvH1qs6IvE9U/Qdat6XcRJ+SVAZ+oPW4RuT7P3jN2nZ4b2BH1N+sP/0N6O3DKW3DC5DTYLLkMjamDIk+SzlJ80uPyVz9M5CfyWcPkp30Ztpu/fVPY+M7NcosfYb7wwo3ddZMkfv9zJHj1OgZ6FtR3iTrjlZGs7Rh5I6cl4yrA8rwQYwFTaCjWFj2Bw2gW1gU9gJNoPdYHPYB7aAA2FLOAG2hpfCNvBa2A5KepzaBtP2H+7owpAebTNzLjl/C1hd9W0aw44wA3aC02EaXA77wK2wH7wTDoD3wYFwDxwM98Eh8Fk4DL4KRW8FjoAfwlEwgrSMgWXgxbARHAdbwPGwA5wAB8GJMFf1ay6HU+E8mAuXwBlwKcyHy2EhXAVnwtXwEng37AQfU72ZJ+EV8Fm4AL4Er4Yn4SL4I/wDdJBX3WAkzIRV1N4c7oXt4T4=
*/
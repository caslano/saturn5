//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

/*
  This file implements the function

  template <class EdgeListGraph, class Size, class P, class T, class R>
  bool bellman_ford_shortest_paths(EdgeListGraph& g, Size N,
     const bgl_named_params<P, T, R>& params)

 */

#ifndef BOOST_GRAPH_BELLMAN_FORD_SHORTEST_PATHS_HPP
#define BOOST_GRAPH_BELLMAN_FORD_SHORTEST_PATHS_HPP

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/relax.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{

template < class Visitor, class Graph > struct BellmanFordVisitorConcept
{
    void constraints()
    {
        BOOST_CONCEPT_ASSERT((CopyConstructibleConcept< Visitor >));
        vis.examine_edge(e, g);
        vis.edge_relaxed(e, g);
        vis.edge_not_relaxed(e, g);
        vis.edge_minimized(e, g);
        vis.edge_not_minimized(e, g);
    }
    Visitor vis;
    Graph g;
    typename graph_traits< Graph >::edge_descriptor e;
};

template < class Visitors = null_visitor > class bellman_visitor
{
public:
    bellman_visitor() {}
    bellman_visitor(Visitors vis) : m_vis(vis) {}

    template < class Edge, class Graph > void examine_edge(Edge u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_examine_edge());
    }
    template < class Edge, class Graph > void edge_relaxed(Edge u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_edge_relaxed());
    }
    template < class Edge, class Graph > void edge_not_relaxed(Edge u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_edge_not_relaxed());
    }
    template < class Edge, class Graph > void edge_minimized(Edge u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_edge_minimized());
    }
    template < class Edge, class Graph >
    void edge_not_minimized(Edge u, Graph& g)
    {
        invoke_visitors(m_vis, u, g, on_edge_not_minimized());
    }

protected:
    Visitors m_vis;
};
template < class Visitors >
bellman_visitor< Visitors > make_bellman_visitor(Visitors vis)
{
    return bellman_visitor< Visitors >(vis);
}
typedef bellman_visitor<> default_bellman_visitor;

template < class EdgeListGraph, class Size, class WeightMap,
    class PredecessorMap, class DistanceMap, class BinaryFunction,
    class BinaryPredicate, class BellmanFordVisitor >
bool bellman_ford_shortest_paths(EdgeListGraph& g, Size N, WeightMap weight,
    PredecessorMap pred, DistanceMap distance, BinaryFunction combine,
    BinaryPredicate compare, BellmanFordVisitor v)
{
    BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< EdgeListGraph >));
    typedef graph_traits< EdgeListGraph > GTraits;
    typedef typename GTraits::edge_descriptor Edge;
    typedef typename GTraits::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< DistanceMap, Vertex >));
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< WeightMap, Edge >));

    typename GTraits::edge_iterator i, end;

    for (Size k = 0; k < N; ++k)
    {
        bool at_least_one_edge_relaxed = false;
        for (boost::tie(i, end) = edges(g); i != end; ++i)
        {
            v.examine_edge(*i, g);
            if (relax(*i, g, weight, pred, distance, combine, compare))
            {
                at_least_one_edge_relaxed = true;
                v.edge_relaxed(*i, g);
            }
            else
                v.edge_not_relaxed(*i, g);
        }
        if (!at_least_one_edge_relaxed)
            break;
    }

    for (boost::tie(i, end) = edges(g); i != end; ++i)
        if (compare(combine(get(distance, source(*i, g)), get(weight, *i)),
                get(distance, target(*i, g))))
        {
            v.edge_not_minimized(*i, g);
            return false;
        }
        else
            v.edge_minimized(*i, g);

    return true;
}

namespace detail
{

    template < typename VertexAndEdgeListGraph, typename Size,
        typename WeightMap, typename PredecessorMap, typename DistanceMap,
        typename P, typename T, typename R >
    bool bellman_dispatch2(VertexAndEdgeListGraph& g,
        typename graph_traits< VertexAndEdgeListGraph >::vertex_descriptor s,
        Size N, WeightMap weight, PredecessorMap pred, DistanceMap distance,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename property_traits< DistanceMap >::value_type D;
        bellman_visitor<> null_vis;
        typedef typename property_traits< WeightMap >::value_type weight_type;
        typename graph_traits< VertexAndEdgeListGraph >::vertex_iterator v,
            v_end;
        for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v)
        {
            put(distance, *v, (std::numeric_limits< weight_type >::max)());
            put(pred, *v, *v);
        }
        put(distance, s, weight_type(0));
        return bellman_ford_shortest_paths(g, N, weight, pred, distance,
            choose_param(
                get_param(params, distance_combine_t()), closed_plus< D >()),
            choose_param(
                get_param(params, distance_compare_t()), std::less< D >()),
            choose_param(get_param(params, graph_visitor), null_vis));
    }

    template < typename VertexAndEdgeListGraph, typename Size,
        typename WeightMap, typename PredecessorMap, typename DistanceMap,
        typename P, typename T, typename R >
    bool bellman_dispatch2(VertexAndEdgeListGraph& g, param_not_found, Size N,
        WeightMap weight, PredecessorMap pred, DistanceMap distance,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename property_traits< DistanceMap >::value_type D;
        bellman_visitor<> null_vis;
        return bellman_ford_shortest_paths(g, N, weight, pred, distance,
            choose_param(
                get_param(params, distance_combine_t()), closed_plus< D >()),
            choose_param(
                get_param(params, distance_compare_t()), std::less< D >()),
            choose_param(get_param(params, graph_visitor), null_vis));
    }

    template < class EdgeListGraph, class Size, class WeightMap,
        class DistanceMap, class P, class T, class R >
    bool bellman_dispatch(EdgeListGraph& g, Size N, WeightMap weight,
        DistanceMap distance, const bgl_named_params< P, T, R >& params)
    {
        dummy_property_map dummy_pred;
        return detail::bellman_dispatch2(g, get_param(params, root_vertex_t()),
            N, weight,
            choose_param(get_param(params, vertex_predecessor), dummy_pred),
            distance, params);
    }
} // namespace detail

template < class EdgeListGraph, class Size, class P, class T, class R >
bool bellman_ford_shortest_paths(
    EdgeListGraph& g, Size N, const bgl_named_params< P, T, R >& params)
{
    return detail::bellman_dispatch(g, N,
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        choose_pmap(get_param(params, vertex_distance), g, vertex_distance),
        params);
}

template < class EdgeListGraph, class Size >
bool bellman_ford_shortest_paths(EdgeListGraph& g, Size N)
{
    bgl_named_params< int, int > params(0);
    return bellman_ford_shortest_paths(g, N, params);
}

template < class VertexAndEdgeListGraph, class P, class T, class R >
bool bellman_ford_shortest_paths(
    VertexAndEdgeListGraph& g, const bgl_named_params< P, T, R >& params)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< VertexAndEdgeListGraph >));
    return detail::bellman_dispatch(g, num_vertices(g),
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        choose_pmap(get_param(params, vertex_distance), g, vertex_distance),
        params);
}
} // namespace boost

#endif // BOOST_GRAPH_BELLMAN_FORD_SHORTEST_PATHS_HPP

/* bellman_ford_shortest_paths.hpp
9tGddFQs15dOpDPpQnohvUGt5dNN9Dm6ne6ko59mfdMT6Gy6mK6lN9B76JP0Rfo+HT2S9UHn0i56A72fbqM76Kj383imM+lCeiG9nt5BH6RP05fpdvouHT6K50d0Ap1NO+nFdAO9nT5An6Hb6dDRPB+gx9GT6Ty6jJ5Lr6a30I30afoKfY8Oj2N/QafSM+gF9EZ6P91Ct9O2D7D/pBPoTLpcreXRa+itai2XbqbP0+30fToinvVCj6XT6Dy6lF5Kb4vncuhjdBt9jX5ARz3DeqEn0IX0MnoPfZhuUWt59D06KoHn63QCnUpPpyvpNfRO+gjdRrfTD+gBY1gunUbn0OX0AnolvYXeQzfR5+h2+j7ddyzrnx5HT6WL1boceiO9nz5JX6Xv0v0+yPN3tZZHz6Sdai2XXk/vppvoVrqdDhvHfo+OpyfTM2g3vZLeRu+jm+hzdDsd/CG2ezqOnkpX0ivoLfQOej99gj5Lt9OddEQi+xk6np6g1uXRBXQx7aIX0evovfQh+hx9jb5L9/0wjwN6LJ1K59Fl9CJ6Pb2dPkC30Ffoe3RUEs+L6GQ6jy6m3fRieh29ld5Ln6Sv0p10+Hi2XzqeTqbz6TJ6Lr16PJdD76OP0Kfp8/Q1+j4dNYH1SCfROXQZvZBeT2+hd9GNdAvdTgdPZPugE+hkOoeeQy9S63LUul30HrqRPkmfo6/Rt+h7dOAkthd6CJ1E59Bl9DJ6E72bbqTP0FfpTjr8WWM7HUcn07l0Gb2IXkZvoHfQB+hjdCt9kW6n79EP6Ihk1jcdR0+mpyezvulF9Jpk1je9hz5Mt9JX6ft03xS2HzqRzqNd9Ap6C72PPpnC7aJvprB8OiKV20PH05PoTHom7VLr8tS6PHo3fYhuo6/Sd+mI59hO6HF0Jl1OL1Vr+fRBuoW+Qt+jI9JYT/QkOjeN+4NeSDfQ++gW+hYdls71pJPobLqUXkRvog/QLbSPDpzM8ZqOo9PombSHbqB300fo8/Qduu/z3G56Ap1HL6DXq7U8+jR9hQ7NYD9Mp9HlGdzf9A76CH2O7qDDp3DcpZPobNpJrzS2/q3n35MX08X0VHoCPZweQPvuGZ+jj9E76HX0XLqATqPjaDsdRne8bXyW3kevp130TDqZHkxH0Hfv8u+r9BF6j1rLo1fQC+hiOpW204H0hb8aH6I30YvoQnoyPZKOpm30zTssj26i99Cb6KW0k86lx9J96c6/GLfTF+kT9G56M72SdtPF9FR6HD2SHkz3pR/cNr5KH6a30ctoJ11Ap9EJ9CA6lL75Z9YLfZLeT2+nN9BLaQ89nZ5ED6Gj6TsdbLd0I72VXkmX09n0WHoQff9PLIc+QG+iF9NOOpuOo/vSD24ZX6HP0Ifp3fR62kPn02l0Ij2cjqLv/pHl0yfpPWotl15IF9IZdCwdTt+5aXyJbqEP0JvplbSTnkFn0En0cDqCvnWD7ZduphtvcL3pFfRCupzOpVPpsfRA+l472xd9gN5Au+kccY/n0WbZkgPw99BgtfWvOUDD7/zXaTPxjZj/v//zOouKKx12T7W9srqo1D7CXeQsra6y13iKPI4R4TK+lFfU2KscRc4au6e8yCNw2JnG6a0qdrjtsx1Oh7vIU+22lxfV2J3VHnuxw+G01zgcpY7ScP9y5lV4yu1V3pJyf+7SIk9RXLjtuWpnTUWpwy3pPZ4K52wsIDclO23ylMx0u8M5t8Jd7aySZ/3tc4vcFf51dVVXSEyR/LeXVUiUrppZFDdgBMq3lxQ5ZW3srzhcHnuF0x4rhZsM8yoqK3VO9VyHe567wuNxOJ+WtXm4PjTa8Y4KsU/srl99Gjme4c8ynMywP00Ow4EMFzI=
*/
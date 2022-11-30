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
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
*/
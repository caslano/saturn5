//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_MST_PRIM_HPP
#define BOOST_GRAPH_MST_PRIM_HPP

#include <functional>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

namespace boost
{

namespace detail
{
    // this should be somewhere else in boost...
    template < class U, class V > struct _project2nd
    {
        V operator()(U, V v) const { return v; }
    };
}

namespace detail
{

    // This is Prim's algorithm to calculate the Minimum Spanning Tree
    // for an undirected graph with weighted edges.

    template < class Graph, class P, class T, class R, class Weight >
    inline void prim_mst_impl(const Graph& G,
        typename graph_traits< Graph >::vertex_descriptor s,
        const bgl_named_params< P, T, R >& params, Weight)
    {
        typedef typename property_traits< Weight >::value_type W;
        std::less< W > compare;
        detail::_project2nd< W, W > combine;
        dijkstra_shortest_paths(
            G, s, params.distance_compare(compare).distance_combine(combine));
    }
} // namespace detail

template < class VertexListGraph, class DijkstraVisitor, class PredecessorMap,
    class DistanceMap, class WeightMap, class IndexMap >
inline void prim_minimum_spanning_tree(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    PredecessorMap predecessor, DistanceMap distance, WeightMap weight,
    IndexMap index_map, DijkstraVisitor vis)
{
    typedef typename property_traits< WeightMap >::value_type W;
    std::less< W > compare;
    detail::_project2nd< W, W > combine;
    dijkstra_shortest_paths(g, s, predecessor, distance, weight, index_map,
        compare, combine, (std::numeric_limits< W >::max)(), 0, vis);
}

template < class VertexListGraph, class PredecessorMap, class P, class T,
    class R >
inline void prim_minimum_spanning_tree(const VertexListGraph& g,
    PredecessorMap p_map, const bgl_named_params< P, T, R >& params)
{
    detail::prim_mst_impl(g,
        choose_param(get_param(params, root_vertex_t()), *vertices(g).first),
        params.predecessor_map(p_map),
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight));
}

template < class VertexListGraph, class PredecessorMap >
inline void prim_minimum_spanning_tree(
    const VertexListGraph& g, PredecessorMap p_map)
{
    detail::prim_mst_impl(g, *vertices(g).first,
        predecessor_map(p_map).weight_map(get(edge_weight, g)),
        get(edge_weight, g));
}

} // namespace boost

#endif // BOOST_GRAPH_MST_PRIM_HPP

/* prim_minimum_spanning_tree.hpp
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
*/
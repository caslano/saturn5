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
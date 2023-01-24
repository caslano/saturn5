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
gh7b3KKvRlzz6g9OOpzOpLZiJ4kWkm7bbi5Zk8a3fJmu86f8VNxCCWR56lAyb/L2xc8xGztWYBLi6bZMtvxSbxLE6n05T8sYonc3K7R+5jYI9+lzkt7QPGSynwlYBlTVRGDvpiMQw8XXbFtqjyeqQWIIxC+1UUQ/gAb0BTQ5AMERbmjsrt3AmUkIpD+09jvwFDR8bk9dR4k9C+o4IELE3T/i/o5ARK7CQz/O9/85UDMRBMAQaQXTg23XbQWddmZPIvCg0Uazs1fx3zumERUIZZAiaCHYGyezAxnsg3vUa9YGNkTqxgQ/vAIRCFP3NvEymEMI3J/DtDTCANHDOZsZKFwZkLmE++Yv4Rw/yBUq+1+1O8U/w7m6m7OdpYWHO6eX+1cXN7v3f35s3fLne3FCJX5H3YWn+mFe8Pj1m00ieX0mWMF/zziGGvrl+0l3NzsZx6gV98+stdphy8vV1TbqLoseYd0OR0xNgP7xkIRVOHQRk0OLKc3tILYGMJKBrK6BTEhJy5r87UHatQ1LBcZkp1G8/wftb84Jzaxvo9Q9rwCYcbZhmeis9yZxT2hukBz/PliiXc/6G0IZmzsfyT5noiSPCb0i7qS8vuDfrdX+smuQBXtU8Z83KUX6310C139wCUajf3UJzyEOWBZh1PZITQkcht2ZjqRPtFdSNYOZhNN/wB9PWV1sbfnaWn053EbD+DKgThX3wUzRwJm4
*/
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
vfZJx6iT3qSPV1m6COZhSS3o5eC1PbzJebG07/94MtSKidFrv42RYTWvwZs5aUAvAGGdpvfggSef+X6v/2PnmHZ53/ebza0/IahPAXP4wWSS+NmWBAb1BA5DGl1AbW8WLy60vuQoECr46OuD24EHkyALEFLyhynUnpqPLuM0i5bms2USXyDsm0+zJFik0zAxnwL2C5ah1WaGkLTjAXBP4fgcjUanHrT58cbLVosFYN40W02nCN3a0NJLsxGakTH4ZRhOxpfh+Mp8foHANY2twlkyWS0Lz8ZBao31QzZLH+M/5uNxDAMdZ4UGwiSJrRVAMPAXWWwvYpAAhQiyUFsJxGLXYXjlTQAHI56cx4vs0kNgTa3liMdXCACichL+YxUlAATYyj7hAVHAT7M4CS5Cq3qWZHE8nVoTmK9mWRRNbaCYFWYK2HQxK0AAIaBlkNFOIepC4jQL0sz7s6dKIXZOJaU7D5kqRohHEakbo+T2kmiRTR0dzcN5nNxYEwjnk/B8dSERoCfx5Y+dwbDb7/m9sxPv1UvvyccnT588e/IdDlLHb7BaQfZhmtLiT5MIzkMKO4JkdTJhEv5079nedzROcRSP2kN/OGqPfjyEv2enp/3ByHuaH0RRilqXXSVhMMN1aqStZStrzZsVTMyW
*/
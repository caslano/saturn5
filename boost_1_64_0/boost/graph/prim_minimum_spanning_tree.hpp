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
rICRKt1DpSdgRdyA/rgDK2MRBmDFOvw+jLVRSzdS6clYFRdiNXxdpVeo9FGsjvexJjryi2MtrIG1sRkGYiIGYQrWw71YH4+r9BmVrhnE79fYHBtgO5XuoNKjsCEux8ZYiCF4GJvj59gGv8ZQbX6wBT7AVvhYlZerx+sGHIbtcJxK56v059hea4cd8Ln6QnTCHOyMa7ArbsFu+C5G4KfYHU9gFF7DntgjmN9PMQHjtfqYgOewN1ZtwPVYK8d++BIOxAU4CF/FwfgOJmvbD1O0+cdUfJY3VNIxBLV0G5VegENxFw7DX3EENm0kxEhMwmzMxDE4BnNwLubhKzgON+PzaGrM9RS9UUsHqPRonIDLcCJ+gy+gbwjXVW374VSMwmnYC6fjSJyJY3A2zsY5eBHn4k2V/kWlo5twHcXxOB934ct4AxdilaZcF7EevoaNcClG4Otae1yBSbgSD+AqPIZrtfrN+P0eE/FNXIEb8EvciE/wIHo2531W9MGPMRgPYxM8ipF4DNfip1io0h+otFcovw9jK/wMf4fFuB1P4Hd4Bq/jV3gLz2KZFpzP0QfPYz28oLXHb3GOSi9W6Yv4Hbq15LyNnfESTsTLuBGv4U78I36GP2rj45/QqRXnYSyH/bTXAZiOg3AMTsMXcSnm41qciUdwMd7AVejXmnnEdvgupuFenItHcDuexK/xAoo25utGXbyD0fgIx6J2Hl2JvngQq+AfsT76PGc+flthPCZhLOZgL5yE6fgmjsdjOFebX9S2v39bXv9gMK7BUNS210DU5nMq3tbmGe/gKryrzSPex234Z2074gP8Pf6CRfgrHsVHeBYd3NmvVdrUzpzuik7YA7X8ZHQmnY6uOB/dcRF64FYsi17tuV5gLSyHDVS6kUoPRG8cotLZ6IOzsQK+jhVxPfrhYZX+XKU9eNO4ElZGLV1LpcegP07ByjhXpeer9If4DF7F6ig6ClEDA7AWhmAgdsG6mIxBuAbr40aVfwTL4g2shH5hvF+FU7AFLlHpNSp9D1uiWyfO+1getXRlle6GrXEatsON2B4LsREexBD8ApvgVxiGN7ET1u7M74kYhFr+c9gNO2IExmN3TMIemINR+Dz2xEsYg/dVWnQxp/tgLGZgL8xT6XEqvQ7j8CL2QVM4xyW64ABshtq8dsMhmIwpOBHTcRoO1eYLh2MhjsBDmIUlmI1Vu3IdwEDU8ruiNq+jMAYX4+9QdOM8r80vaumqKp2Lk3EGvoivqPRSlf4Y89EhgusBBuJ0bITjMAzHY0+cgL1xFmbjbHwD5+IGlb8bF+A+fBlP4Ct4ARfhTXwV7+FiHBLJ9QHzUEtPVulTuBR/wGV4W6XvqnTN7lxHMAlX4YtYgDPwDdyKw/Ej3IzH8S1tOXALih6c/zAEt2M/3IEpKn807sWFuA/XYxHuwQNoiuL6g+6o1WuB2nwPwtdwGu7W5hk/wDdxD36An+ABPI71evI+GLZFLd1VpVdjMb6PJ7T6Kn1Ype/hSQyO5rqEEXgek/ECLsLvcIXK34pXMSCG6wo2RC3dUqUX4HVciz9hoUpvV+kS/BNWjeW8i+3wHnbCP2NurHleZ+IjfAUf4xsoPHidhI54CJ3xS3TBu+iKVXtxPcFQ1MrDsDtGYHlMxoq4HGvibgzU+sM6+CnWxS8wCE/hYW3/waN4Bz9F5zjeD8RyeAlr4vfYCK9gKP6AUajNSy5q22M5lqPfd9BbGx998RjWw8+wPl7GBvhMPOctrInNMQlbYya2wQXYHtdgJdyO/rgPK+MBDMCjWB5vYQd04o39juiNXbEldtP6we5aPyq9R6V9e3Pew0CMwkYq3VylU7Cn1h57ae2wjzY+JuI=
*/
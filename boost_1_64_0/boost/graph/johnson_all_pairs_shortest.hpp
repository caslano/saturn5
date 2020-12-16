//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

/*
  This file implements the function

  template <class VertexAndEdgeListGraph, class DistanceMatrix,
            class P, class T, class R>
  bool
  johnson_all_pairs_shortest_paths
    (VertexAndEdgeListGraph& g,
     DistanceMatrix& D,
     const bgl_named_params<P, T, R>& params)
 */

#ifndef BOOST_GRAPH_JOHNSON_HPP
#define BOOST_GRAPH_JOHNSON_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_map/shared_array_property_map.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/type_traits/same_traits.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{

template < class VertexAndEdgeListGraph, class DistanceMatrix, class VertexID,
    class Weight, typename BinaryPredicate, typename BinaryFunction,
    typename Infinity, class DistanceZero >
bool johnson_all_pairs_shortest_paths(VertexAndEdgeListGraph& g1,
    DistanceMatrix& D, VertexID id1, Weight w1, const BinaryPredicate& compare,
    const BinaryFunction& combine, const Infinity& inf, DistanceZero zero)
{
    typedef graph_traits< VertexAndEdgeListGraph > Traits1;
    typedef typename property_traits< Weight >::value_type DT;
    BOOST_CONCEPT_ASSERT((BasicMatrixConcept< DistanceMatrix,
        typename Traits1::vertices_size_type, DT >));

    typedef typename Traits1::directed_category DirCat;
    bool is_undirected = is_same< DirCat, undirected_tag >::value;

    typedef adjacency_list< vecS, vecS, directedS,
        property< vertex_distance_t, DT >,
        property< edge_weight_t, DT, property< edge_weight2_t, DT > > >
        Graph2;
    typedef graph_traits< Graph2 > Traits2;

    Graph2 g2(num_vertices(g1) + 1);
    typename property_map< Graph2, edge_weight_t >::type w
        = get(edge_weight, g2);
    typename property_map< Graph2, edge_weight2_t >::type w_hat
        = get(edge_weight2, g2);
    typename property_map< Graph2, vertex_distance_t >::type d
        = get(vertex_distance, g2);
    typedef typename property_map< Graph2, vertex_index_t >::type VertexID2;
    VertexID2 id2 = get(vertex_index, g2);

    // Construct g2 where V[g2] = V[g1] U {s}
    //   and  E[g2] = E[g1] U {(s,v)| v in V[g1]}
    std::vector< typename Traits1::vertex_descriptor > verts1(
        num_vertices(g1) + 1);
    typename Traits2::vertex_descriptor s = *vertices(g2).first;
    {
        typename Traits1::vertex_iterator v, v_end;
        int i = 1;
        for (boost::tie(v, v_end) = vertices(g1); v != v_end; ++v, ++i)
        {
            typename Traits2::edge_descriptor e;
            bool z;
            boost::tie(e, z) = add_edge(s, get(id1, *v) + 1, g2);
            put(w, e, zero);
            verts1[i] = *v;
        }
        typename Traits1::edge_iterator e, e_end;
        for (boost::tie(e, e_end) = edges(g1); e != e_end; ++e)
        {
            typename Traits2::edge_descriptor e2;
            bool z;
            boost::tie(e2, z) = add_edge(
                get(id1, source(*e, g1)) + 1, get(id1, target(*e, g1)) + 1, g2);
            put(w, e2, get(w1, *e));
            if (is_undirected)
            {
                boost::tie(e2, z) = add_edge(get(id1, target(*e, g1)) + 1,
                    get(id1, source(*e, g1)) + 1, g2);
                put(w, e2, get(w1, *e));
            }
        }
    }
    typename Traits2::vertex_iterator v, v_end, u, u_end;
    typename Traits2::edge_iterator e, e_end;
    shared_array_property_map< DT, VertexID2 > h(num_vertices(g2), id2);

    for (boost::tie(v, v_end) = vertices(g2); v != v_end; ++v)
        put(d, *v, inf);

    put(d, s, zero);
    // Using the non-named parameter versions of bellman_ford and
    // dijkstra for portability reasons.
    dummy_property_map pred;
    bellman_visitor<> bvis;
    if (bellman_ford_shortest_paths(
            g2, num_vertices(g2), w, pred, d, combine, compare, bvis))
    {
        for (boost::tie(v, v_end) = vertices(g2); v != v_end; ++v)
            put(h, *v, get(d, *v));
        // Reweight the edges to remove negatives
        for (boost::tie(e, e_end) = edges(g2); e != e_end; ++e)
        {
            typename Traits2::vertex_descriptor a = source(*e, g2),
                                                b = target(*e, g2);
            put(w_hat, *e, combine((get(h, a) - get(h, b)), get(w, *e)));
        }
        for (boost::tie(u, u_end) = vertices(g2); u != u_end; ++u)
        {
            dijkstra_visitor<> dvis;
            dijkstra_shortest_paths(
                g2, *u, pred, d, w_hat, id2, compare, combine, inf, zero, dvis);
            for (boost::tie(v, v_end) = vertices(g2); v != v_end; ++v)
            {
                if (*u != s && *v != s)
                {
                    D[get(id2, *u) - 1][get(id2, *v) - 1]
                        = combine((get(h, *v) - get(h, *u)), get(d, *v));
                }
            }
        }
        return true;
    }
    else
        return false;
}

template < class VertexAndEdgeListGraph, class DistanceMatrix, class VertexID,
    class Weight, class DistanceZero >
bool johnson_all_pairs_shortest_paths(VertexAndEdgeListGraph& g1,
    DistanceMatrix& D, VertexID id1, Weight w1, DistanceZero zero)
{
    typedef typename property_traits< Weight >::value_type WT;
    return johnson_all_pairs_shortest_paths(g1, D, id1, w1, std::less< WT >(),
        closed_plus< WT >(), (std::numeric_limits< WT >::max)(), zero);
}

namespace detail
{

    template < class VertexAndEdgeListGraph, class DistanceMatrix, class P,
        class T, class R, class Weight, class VertexID >
    bool johnson_dispatch(VertexAndEdgeListGraph& g, DistanceMatrix& D,
        const bgl_named_params< P, T, R >& params, Weight w, VertexID id)
    {
        typedef typename property_traits< Weight >::value_type WT;

        return johnson_all_pairs_shortest_paths(g, D, id, w,
            choose_param(
                get_param(params, distance_compare_t()), std::less< WT >()),
            choose_param(
                get_param(params, distance_combine_t()), closed_plus< WT >()),
            choose_param(get_param(params, distance_inf_t()),
                std::numeric_limits< WT >::max
                    BOOST_PREVENT_MACRO_SUBSTITUTION()),
            choose_param(get_param(params, distance_zero_t()), WT()));
    }

} // namespace detail

template < class VertexAndEdgeListGraph, class DistanceMatrix, class P, class T,
    class R >
bool johnson_all_pairs_shortest_paths(VertexAndEdgeListGraph& g,
    DistanceMatrix& D, const bgl_named_params< P, T, R >& params)
{
    return detail::johnson_dispatch(g, D, params,
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        choose_const_pmap(get_param(params, vertex_index), g, vertex_index));
}

template < class VertexAndEdgeListGraph, class DistanceMatrix >
bool johnson_all_pairs_shortest_paths(
    VertexAndEdgeListGraph& g, DistanceMatrix& D)
{
    bgl_named_params< int, int > params(1);
    return detail::johnson_dispatch(
        g, D, params, get(edge_weight, g), get(vertex_index, g));
}

} // namespace boost

#endif // BOOST_GRAPH_JOHNSON_HPP

/* johnson_all_pairs_shortest.hpp
XQ0tbvHNwHDWjcq0T5alO0IXEeivLma/RGXif2a0scWNmgoE8G3AeHtNKgPe7BffCuTbp1g02e5U3oEnLa/dng3OdVRaNB1j7Pk8P65b+4iyZcmy+a0nlu1K5K3Sy9bs9jV3Wq6qH1gulyzXVant6yzB1nG5/MZyBQK+APDOyub/gWVb0knZHuikbCsMZUPn9PpOUrYVP7Bsd3dStivlCzkjEbohDELwoc3XG8qG72/w5UtnZdNkz6B08ZsAEJfpNqbSqewZ/2TZOTaavnfhGPRKf3Yrf0T8bRn392nv30Hp32my3vngzUgCrvsXDDXxkcROWbfcToT8Xue8sHqcGSkE06WdbtJO4m6jHY+XfU87/TqxsyWyY3+y29nxtYW+p52iMDtH5G9MrI7g3y39JGnl1q1z0+v23H3hxv2Dzs1jbFd3jj82oezIN2PzXr7p43e3N1oaX8I3Sz04/rtPRn68a9bWykuuLsreMe8LyFcQ7khoKt097UDr4DNWXnXpgoe+YuwolV1Qlfw9hCVW/l0Uv5bzr5yXs+U7ZOOkfIP8Lmo2OK+DOeApPD/4VMgvBefz+M/BxXdWcj6UYzA77DurQqmnGJzXS5EhX9VJ8o2R+c6S+cYa8vlPkm+8zDdR5ptgyLfiJPlKZL4pMl+pzDdaG2NyHGfLe/FQma8ccrw/VoAP4uMIPIviev6DMv9pHeTPlXZHgvM2y5P1PdKQP1H2o/QO8g+W+YfIcgwFT6a4nj97d+f2h8n82dJ+Drcv4zzvMlTSHQhrEbYg7EHYL1827ImQi1CF0BIh5rv7EJ4xX0Q0ySSTTDLJpB+F/l37f/pbgvPxK4a0/f/h+/8laUztZxPkfvbXcs31IMKduFi9ltbTjfhpkgYm92Uh2tv4LtL2PklMk0tnSYjzNcnTFG/B2iSeZFIQK32EY5Gk4yj9/kVjaL7UMdWi6ehFOsoRf5biq9ko/C/scqI9CsmkgW8nmevZQHiUBJm5iVLG2egOhITuEuj6luRi8HsW59hj+JoPhT4XslsRdiPUohYuQZmaUjku9gzZp9ijTQQP0X4MdSGxEvCjKRzjvom9RJ6s4w/k/vddhAEIzyKM74N9xiNUx/62gN8XdIufXNHq2kK/39jg8al9piY/GHFRT1dTfC3JzyV53fepSn4ExSsQ/wXFbyX5PyZzeX9Ia8tSpC+n9L4Ur1L5M1mcagOPaFNcraO0IOnqIn7HlP8kB6XPQN77Kf1mxFVe/FBmCHHRfm9Q+gwRx9V65Zsur5XNC313PSL6RF+0YzTwTBTCB0VL03i7tQvfa5/N29CSyNuL17HehnMJ4/UosCpgf0zmGOpKtutg2a5ro+Q+COXrBd4PvADtWvUotWvQM9vL4lTbzFf1vIDSbRbRrpr8IPL9fZL1X+ReINtRpZ9J8TLE51G8q0Ufk02uBUEh70A8SOldSP8clb8fS1LyjS0B93zV9t1565HMQop7VJ4MkY4r9zpdx6I0sumZ7Q6GRP8vtlciz0Cm5bOglorsq2Vf/r0Y8z5vM1N993OSu1jlzQ7L+wDXK/oWEO2XW3Rbo8Pk10tb86kv0hgknOsdiz7ThYnxnpqEnoXW6wF+OfzYmCh4OuJ7gb+M8ArCFcBWyL7kP+kZQqRd1A3rL84j7fbFqh/Npz50JeLvU5zalbAVag4RbecAdovCtPYhnOpxURrHjXVupzr6Pc05vG5JluqhC9nS6kw/V5qfqM1P7c9UFicIh0JW9GHwC8Cr+8B/8msxv/PQrOppXkB13Cet/Rw+xaLJZtH8PB3xX1M80uq3XAYZjlnYtg0cO8vQroX59ENQ2r1A6Zmg94ET+5uYn3RZrf07HGs=
*/
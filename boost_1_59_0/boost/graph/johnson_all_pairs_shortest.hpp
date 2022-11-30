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
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
*/
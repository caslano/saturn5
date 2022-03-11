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
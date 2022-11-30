// Copyright 2002 Rensselaer Polytechnic Institute

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Lauren Foutz
//           Scott Hill

/*
  This file implements the functions

  template <class VertexListGraph, class DistanceMatrix,
    class P, class T, class R>
  bool floyd_warshall_initialized_all_pairs_shortest_paths(
    const VertexListGraph& g, DistanceMatrix& d,
    const bgl_named_params<P, T, R>& params)

  AND

  template <class VertexAndEdgeListGraph, class DistanceMatrix,
    class P, class T, class R>
  bool floyd_warshall_all_pairs_shortest_paths(
    const VertexAndEdgeListGraph& g, DistanceMatrix& d,
    const bgl_named_params<P, T, R>& params)
*/

#ifndef BOOST_GRAPH_FLOYD_WARSHALL_HPP
#define BOOST_GRAPH_FLOYD_WARSHALL_HPP

#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/relax.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{
namespace detail
{
    template < typename T, typename BinaryPredicate >
    T min_with_compare(const T& x, const T& y, const BinaryPredicate& compare)
    {
        if (compare(x, y))
            return x;
        else
            return y;
    }

    template < typename VertexListGraph, typename DistanceMatrix,
        typename BinaryPredicate, typename BinaryFunction, typename Infinity,
        typename Zero >
    bool floyd_warshall_dispatch(const VertexListGraph& g, DistanceMatrix& d,
        const BinaryPredicate& compare, const BinaryFunction& combine,
        const Infinity& inf, const Zero& zero)
    {
        typename graph_traits< VertexListGraph >::vertex_iterator i, lasti, j,
            lastj, k, lastk;

        for (boost::tie(k, lastk) = vertices(g); k != lastk; k++)
            for (boost::tie(i, lasti) = vertices(g); i != lasti; i++)
                if (d[*i][*k] != inf)
                    for (boost::tie(j, lastj) = vertices(g); j != lastj; j++)
                        if (d[*k][*j] != inf)
                            d[*i][*j] = detail::min_with_compare(d[*i][*j],
                                combine(d[*i][*k], d[*k][*j]), compare);

        for (boost::tie(i, lasti) = vertices(g); i != lasti; i++)
            if (compare(d[*i][*i], zero))
                return false;
        return true;
    }
}

template < typename VertexListGraph, typename DistanceMatrix,
    typename BinaryPredicate, typename BinaryFunction, typename Infinity,
    typename Zero >
bool floyd_warshall_initialized_all_pairs_shortest_paths(
    const VertexListGraph& g, DistanceMatrix& d, const BinaryPredicate& compare,
    const BinaryFunction& combine, const Infinity& inf, const Zero& zero)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< VertexListGraph >));

    return detail::floyd_warshall_dispatch(g, d, compare, combine, inf, zero);
}

template < typename VertexAndEdgeListGraph, typename DistanceMatrix,
    typename WeightMap, typename BinaryPredicate, typename BinaryFunction,
    typename Infinity, typename Zero >
bool floyd_warshall_all_pairs_shortest_paths(const VertexAndEdgeListGraph& g,
    DistanceMatrix& d, const WeightMap& w, const BinaryPredicate& compare,
    const BinaryFunction& combine, const Infinity& inf, const Zero& zero)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< VertexAndEdgeListGraph >));
    BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< VertexAndEdgeListGraph >));
    BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< VertexAndEdgeListGraph >));

    typename graph_traits< VertexAndEdgeListGraph >::vertex_iterator firstv,
        lastv, firstv2, lastv2;
    typename graph_traits< VertexAndEdgeListGraph >::edge_iterator first, last;

    for (boost::tie(firstv, lastv) = vertices(g); firstv != lastv; firstv++)
        for (boost::tie(firstv2, lastv2) = vertices(g); firstv2 != lastv2;
             firstv2++)
            d[*firstv][*firstv2] = inf;

    for (boost::tie(firstv, lastv) = vertices(g); firstv != lastv; firstv++)
        d[*firstv][*firstv] = zero;

    for (boost::tie(first, last) = edges(g); first != last; first++)
    {
        if (d[source(*first, g)][target(*first, g)] != inf)
        {
            d[source(*first, g)][target(*first, g)]
                = detail::min_with_compare(get(w, *first),
                    d[source(*first, g)][target(*first, g)], compare);
        }
        else
            d[source(*first, g)][target(*first, g)] = get(w, *first);
    }

    bool is_undirected = is_same<
        typename graph_traits< VertexAndEdgeListGraph >::directed_category,
        undirected_tag >::value;
    if (is_undirected)
    {
        for (boost::tie(first, last) = edges(g); first != last; first++)
        {
            if (d[target(*first, g)][source(*first, g)] != inf)
                d[target(*first, g)][source(*first, g)]
                    = detail::min_with_compare(get(w, *first),
                        d[target(*first, g)][source(*first, g)], compare);
            else
                d[target(*first, g)][source(*first, g)] = get(w, *first);
        }
    }

    return detail::floyd_warshall_dispatch(g, d, compare, combine, inf, zero);
}

namespace detail
{
    template < class VertexListGraph, class DistanceMatrix, class WeightMap,
        class P, class T, class R >
    bool floyd_warshall_init_dispatch(const VertexListGraph& g,
        DistanceMatrix& d, WeightMap /*w*/,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename property_traits< WeightMap >::value_type WM;
        WM inf = choose_param(get_param(params, distance_inf_t()),
            std::numeric_limits< WM >::max BOOST_PREVENT_MACRO_SUBSTITUTION());

        return floyd_warshall_initialized_all_pairs_shortest_paths(g, d,
            choose_param(
                get_param(params, distance_compare_t()), std::less< WM >()),
            choose_param(get_param(params, distance_combine_t()),
                closed_plus< WM >(inf)),
            inf, choose_param(get_param(params, distance_zero_t()), WM()));
    }

    template < class VertexAndEdgeListGraph, class DistanceMatrix,
        class WeightMap, class P, class T, class R >
    bool floyd_warshall_noninit_dispatch(const VertexAndEdgeListGraph& g,
        DistanceMatrix& d, WeightMap w,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename property_traits< WeightMap >::value_type WM;

        WM inf = choose_param(get_param(params, distance_inf_t()),
            std::numeric_limits< WM >::max BOOST_PREVENT_MACRO_SUBSTITUTION());
        return floyd_warshall_all_pairs_shortest_paths(g, d, w,
            choose_param(
                get_param(params, distance_compare_t()), std::less< WM >()),
            choose_param(get_param(params, distance_combine_t()),
                closed_plus< WM >(inf)),
            inf, choose_param(get_param(params, distance_zero_t()), WM()));
    }

} // namespace detail

template < class VertexListGraph, class DistanceMatrix, class P, class T,
    class R >
bool floyd_warshall_initialized_all_pairs_shortest_paths(
    const VertexListGraph& g, DistanceMatrix& d,
    const bgl_named_params< P, T, R >& params)
{
    return detail::floyd_warshall_init_dispatch(g, d,
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        params);
}

template < class VertexListGraph, class DistanceMatrix >
bool floyd_warshall_initialized_all_pairs_shortest_paths(
    const VertexListGraph& g, DistanceMatrix& d)
{
    bgl_named_params< int, int > params(0);
    return detail::floyd_warshall_init_dispatch(
        g, d, get(edge_weight, g), params);
}

template < class VertexAndEdgeListGraph, class DistanceMatrix, class P, class T,
    class R >
bool floyd_warshall_all_pairs_shortest_paths(const VertexAndEdgeListGraph& g,
    DistanceMatrix& d, const bgl_named_params< P, T, R >& params)
{
    return detail::floyd_warshall_noninit_dispatch(g, d,
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        params);
}

template < class VertexAndEdgeListGraph, class DistanceMatrix >
bool floyd_warshall_all_pairs_shortest_paths(
    const VertexAndEdgeListGraph& g, DistanceMatrix& d)
{
    bgl_named_params< int, int > params(0);
    return detail::floyd_warshall_noninit_dispatch(
        g, d, get(edge_weight, g), params);
}

} // namespace boost

#endif

/* floyd_warshall_shortest.hpp
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
*/
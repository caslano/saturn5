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
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
3XL6r5ave/L4l3O2XtsTKc3bcNNF32tSN7z55BPF6Rf2XF9zw8Qrr/z7Icf/4vM9H++uvak0t/e2E866oH1pUsJz1+VJIHq/u2vVrFcPOvxzb3+n/bPX3HbL3Cvvefqip+ozbj3nnW/XPPnKts8u+fEts+pPOzCl6tSjk95ZOP6J2zfOPj/pC5OXzrjzmB8f8MJlCbltv/9YyqkTZ5533dGZ2yYteetxMXgu7O4++7Ezynq+ct5D9x/bc9aGG95u+lbz3Ss+JnsU3jp9+yvPDu74xsvTL5zzzPDS4i8WZl+U9E2nfP2LpmsKr4RZgrFtZ09sJxvbts2NbZsntp1sbHujjW3bNu9/9TLP06quqZ5vJggUFKSvb4qfV8VCQGGIsXhAm1Hzk1LZ6mRa2lkCSI5sAE7hcX1Dgja/JdFAAM9pgmcT6hUwHJcvVGs8aMES8VKa/UhKeFAlQP16sRtNAU7XUHnv2zwm1RdHsM3KbbjGW4f18hstzrSKFMHSNE0vYwE2OMtovupma1M/TzR5nVsu7USZ+nk9GVos3oOIGT7gWaOawHNonKVuatKlcS95yIORDU/sOUa5pAt4McvIzHMjpaUfkYOZyM7Sf2x0oSjp0wH5+vJSFhN8Yq5z/rWisGnL0dcQj9ym/AqRJUhHucQRO4Avep+4iJmb2XXvC74MhvHjFCXx8/Uj7hBnN2Ui17D0jVPuPwn+jyf+mdr8QWyijAfK9LaFVMy0jehl9Kg98ftI/RiPisVFMierqgVnTTtPWeRBFlSHUJw96gmBJ5/P3gu2eTTW66D15fOy2Z1DUk0KAE1Qgj3RiZXoNj1AAg9Wm9b+eUPe7AtYtty2H5hG+RslmOfl0Hdy0neUiQkHlBcf91pvHA8GG7ypPAcDRSL9IBzsXqjQYxbPmMp9gXBFsRhUkRB9GyB39puJ1Zpt0H4YwUlk5KqcLGoeaB9px8+TfEMfTpcbC8mGGjuOBIUYtPmk1mI/vt+cMtXqBaD/zkMa+u5mBbmoska9VtKvhsbcajMYbi8iMRMPxtieuRWN2s0mZW1KYz2yDvw32lyglWm5WG3xV69wBCgWLgICoW9nEu5s0Bhz8ChemMy2T/qyrJjSg8IvCtXDje2P857UjxzjpMKStOXYNL9WIdBrPVurUWeZMjGg8t9a1TZstGXptNSfTnJq4TwyoKByj7OV1EQ+eGzge+mFympbd06ocJrQZ4/SZvKsAsY28fww/72HWSgE4v2ZyqUxny5fdPYpyskVKSUTU+QxKLQPaP5aI9s9FS7Kmj+oucmgCvv3Fq/ur8cp3PZ7P5z5i72oFozSnrDzSVFop0I0/MiJH8pV58ySJ1LgKpn6tYiNYtutl+Xbg0U8Q1G7kGvIf0B2zUkW/IINeULLNG+n7XQDxxaXT9P6B+xgZd+WDs0kPUSaiUGS6FrJToZ9tR3EEkdtiiZ3n6kF3wR0JES5+k+ccr2Q1iryaWA/VZNIK36G6kwsvK589xshdvvhkDnbCjrdJsFKptmExJeLY4ByoR7yClGyuJJdFqyiUUdROUYCx5jqQAcZg3AxZB0I2kgZTuKl0hLTrL1y2v/ZAjJSgdtTgWhcrY/bfHhnZzBKBCgOxuy8qxZZxSNWyWnO7MTVA+bqkB/lqagUlFP7x3zUIB2HL1qWdsVG6JVdtWrjwwdzARS3gwbCfYoO/8knnsKTR5K41TJzU4hpKCxnZGIyQe8eL83Od0bRDS3zAMekYW8OvQvLSXaSXWeC9+fqvyNR6EjOeU5z+nPyS3QqXkA5PEQZvwZIkjzFeQQR4RaaOY8Be2iZ+a2ZCGbl60NE91k+xoKhgBiC+FOk90APbZQsgRIovqo=
*/
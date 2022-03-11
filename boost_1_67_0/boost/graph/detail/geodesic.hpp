// (C) Copyright 2007 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_GEODESIC_HPP
#define BOOST_GRAPH_DETAIL_GEODESIC_HPP

#include <functional>
#include <boost/config.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/numeric_values.hpp>
#include <boost/concept/assert.hpp>

// TODO: Should this really be in detail?

namespace boost
{
// This is a very good discussion on centrality measures. While I can't
// say that this has been the motivating factor for the design and
// implementation of ths centrality framework, it does provide a single
// point of reference for defining things like degree and closeness
// centrality. Plus, the bibliography seems fairly complete.
//
//     @article{citeulike:1144245,
//         author = {Borgatti, Stephen  P. and Everett, Martin  G.},
//         citeulike-article-id = {1144245},
//         doi = {10.1016/j.socnet.2005.11.005},
//         journal = {Social Networks},
//         month = {October},
//         number = {4},
//         pages = {466--484},
//         priority = {0},
//         title = {A Graph-theoretic perspective on centrality},
//         url = {https://doi.org/10.1016/j.socnet.2005.11.005},
//             volume = {28},
//             year = {2006}
//         }
//     }

namespace detail
{
    // Note that this assumes T == property_traits<DistanceMap>::value_type
    // and that the args and return of combine are also T.
    template < typename Graph, typename DistanceMap, typename Combinator,
        typename Distance >
    inline Distance combine_distances(
        const Graph& g, DistanceMap dist, Combinator combine, Distance init)
    {
        BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        typedef typename graph_traits< Graph >::vertex_iterator VertexIterator;
        BOOST_CONCEPT_ASSERT(
            (ReadablePropertyMapConcept< DistanceMap, Vertex >));
        BOOST_CONCEPT_ASSERT((NumericValueConcept< Distance >));
        typedef numeric_values< Distance > DistanceNumbers;
        BOOST_CONCEPT_ASSERT((AdaptableBinaryFunction< Combinator, Distance,
            Distance, Distance >));

        // If there's ever an infinite distance, then we simply return
        // infinity. Note that this /will/ include the a non-zero
        // distance-to-self in the combined values. However, this is usually
        // zero, so it shouldn't be too problematic.
        Distance ret = init;
        VertexIterator i, end;
        for (boost::tie(i, end) = vertices(g); i != end; ++i)
        {
            Vertex v = *i;
            if (get(dist, v) != DistanceNumbers::infinity())
            {
                ret = combine(ret, get(dist, v));
            }
            else
            {
                ret = DistanceNumbers::infinity();
                break;
            }
        }
        return ret;
    }

    // Similar to std::plus<T>, but maximizes parameters
    // rather than adding them.
    template < typename T > struct maximize
    {
        typedef T result_type;
        typedef T first_argument_type;
        typedef T second_argument_type;
        T operator()(T x, T y) const
        {
            BOOST_USING_STD_MAX();
            return max BOOST_PREVENT_MACRO_SUBSTITUTION(x, y);
        }
    };

    // Another helper, like maximize() to help abstract functional
    // concepts. This is trivially instantiated for builtin numeric
    // types, but should be specialized for those types that have
    // discrete notions of reciprocals.
    template < typename T > struct reciprocal
    {
        typedef T result_type;
        typedef T argument_type;
        T operator()(T t) { return T(1) / t; }
    };
} /* namespace detail */

// This type defines the basic facilities used for computing values
// based on the geodesic distances between vertices. Examples include
// closeness centrality and mean geodesic distance.
template < typename Graph, typename DistanceType, typename ResultType >
struct geodesic_measure
{
    typedef DistanceType distance_type;
    typedef ResultType result_type;
    typedef typename graph_traits< Graph >::vertices_size_type size_type;

    typedef numeric_values< distance_type > distance_values;
    typedef numeric_values< result_type > result_values;

    static inline distance_type infinite_distance()
    {
        return distance_values::infinity();
    }

    static inline result_type infinite_result()
    {
        return result_values::infinity();
    }

    static inline result_type zero_result() { return result_values::zero(); }
};

} /* namespace boost */

#endif

/* geodesic.hpp
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
*/
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
//      NOTE: Disabled until this concept assert is fixed in Boost.ConceptCheck.
//         BOOST_CONCEPT_ASSERT((AdaptableBinaryFunction< Combinator, Distance,
//             Distance, Distance >));

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
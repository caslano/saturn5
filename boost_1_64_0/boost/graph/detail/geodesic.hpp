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
v8wbYTX7CFUdCqnl+5HnY8nTzan8buGVnfr3uMTr7NyX5X3ZdufxGLonDkrurffnz5L/Hfo2GqrHny5oX4bpiqqcIKb2SSyYafLochtKuZtdxu8Lw8HUbRFW/RS69TEosRWkg6SrwbqvPd133Fr7fFyH7dQYv8tVf29n1Hi/nZz73GPeJJR+QtD9YY6LEyb1ZRbdL1zDU2a/cDVO6P6xdB9hlc1YuCNWxoxVccRym7HKjligGavkiMWc1LGKjti1k+79bY3M6V7fN4GYc30fMd4rjny8f5zqCjfrMXG89YIPUi94OdAe733g/LCZCzvnmHv8Xr6wSv1He+sF/x/qBffq7zz53pV6Qfsb/E3kQQ/g6fd+l8GKWB6fwjBsgxWwF1bE4VgTx2ItHId1cA7WxbkYiUuwPi7DBrgGn8Z12AjfUOXuwGjcj83wEMbiN9gSf8U4tLGtrbAotsUK2A6fwo4YiZ0wFjtjO+yCvbA7DsC+OBIT8QV8Bmdib5yv5i/HZNyFKbgHq+ExfApPYnV8D/vjJUzFe2rayv4dhI/iECyGaVgBh2ILHI5tMBz74kj+DcVROApH40Qcgy/iWPzRh/+42WMOyVFPGzjr9+tq16301tV662q9dbXeuto/Z13t4ZX/2braP/T8nyEZ+ibYKwD+9fP/193P/4m5n/8Tcz7/1zGrirU15JyeWObn9EedzumbqnP6G7xEjyrnMGfRETmnl2cnJ/Wez+lV3sZ6TK0uR+3TCZay/Aq5bnBOp87to49J3MhllPV4Xu9cVjTTiVKWxVqcsspZCuttYE6C9FOrxgc8Jcvdt+y2lNJjO06R9RXyOPbgp7LMJOsZi821HkGP/3RT8gy37rf4yHn/6y71Bbdlfh8jZ4b6gm5JMpafOjf+XPKMtx6yZCXmyENnjQmpDOaRni83kQuS76plY/pzIOZ4DiWcxw3u2lMt05eyv5BlxloPW/wkz+Dcsn5eLnM8reOSZ4E12OlcO6F77wGSR617v6xnpet69XhzH0kZ06zmuFADdP+ftSRvVo4/X92Ha0OJRRHJpWIZXn/nOhQ9ZuQXMn+ElFOYYyCZc/V87ufq5jm67m/ePAcvg8dVv54f8Pe6EDPPu6S2xK6QTpDHxryTrmPXGq4P9/7a+xw3z8vDj7qfb1cg5nq+XYiY6/l2PmKu59u5zFgFR2yFGQuT14zYZB2rJtMzj6VPJyT3UH18up+jpxlu5+hyfHDMEHMcM9WCSh3N2EdzLT39332+nvl588M7j8/8fNrT+ajn8/5tch7/5Q+vxy7IeiFoRe6Ltd9c1urNP76Pz8zrGx78vP9Bz9f/LOflmddP/HPn64f1d5l8p0ofnuH8vRPtj+L280t8HKOxDHbBsjgIq2AahuOzGIHDsRo+j9VxGtbAl7AWzsTa+Besi2tVudswCvdiAzyMDfE0NsKr2Bi/xvJosfAeQz+sgMFYEUOxEj6K0VgUY7EUNsdq2AJrYRw2wVYYi+1wCLbHSdgBX8ROuAo743qMx73YBfdjNzyP3fEmPovf4XC02O9xRhs+jyGYgPkxEcMwCZ/G3tgU+2IspmIPHICrVfw1TMaD2A+Pq3J9fPktu5776kinSVdIv6x/sHP40Ne85/Dec3jvObz3HP7PeQ4f9tp/9hz+X3n4kHr+Yef/9Ls/aGAfqQF4CG0AFrjVARBzqwMg5lIHkFvFrG7X+4nr6/2NmjnHfHV7ATPmJ7HYVvXI6ijTX2KRUS3iZHkdD5B43ZbNKsTWbdEySsezOOoh6reKjnUqO6vEWzZ6uplZRjaJtY5q0ahBO+dtyy7xFlGtndaXQz23yBbtYuOc4o9IvH6UxHUZqJ5zk6g=
*/
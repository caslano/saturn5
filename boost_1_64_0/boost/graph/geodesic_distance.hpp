// (C) Copyright Andrew Sutton 2007
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_GEODESIC_DISTANCE_HPP
#define BOOST_GRAPH_GEODESIC_DISTANCE_HPP

#include <boost/graph/detail/geodesic.hpp>
#include <boost/graph/exterior_property.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{
template < typename Graph, typename DistanceType, typename ResultType,
    typename Divides = std::divides< ResultType > >
struct mean_geodesic_measure
: public geodesic_measure< Graph, DistanceType, ResultType >
{
    typedef geodesic_measure< Graph, DistanceType, ResultType > base_type;
    typedef typename base_type::distance_type distance_type;
    typedef typename base_type::result_type result_type;

    result_type operator()(distance_type d, const Graph& g)
    {
        BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
        BOOST_CONCEPT_ASSERT((NumericValueConcept< DistanceType >));
        BOOST_CONCEPT_ASSERT((NumericValueConcept< ResultType >));
        BOOST_CONCEPT_ASSERT((AdaptableBinaryFunctionConcept< Divides,
            ResultType, ResultType, ResultType >));

        return (d == base_type::infinite_distance())
            ? base_type::infinite_result()
            : div(result_type(d), result_type(num_vertices(g) - 1));
    }
    Divides div;
};

template < typename Graph, typename DistanceMap >
inline mean_geodesic_measure< Graph,
    typename property_traits< DistanceMap >::value_type, double >
measure_mean_geodesic(const Graph&, DistanceMap)
{
    return mean_geodesic_measure< Graph,
        typename property_traits< DistanceMap >::value_type, double >();
}

template < typename T, typename Graph, typename DistanceMap >
inline mean_geodesic_measure< Graph,
    typename property_traits< DistanceMap >::value_type, T >
measure_mean_geodesic(const Graph&, DistanceMap)
{
    return mean_geodesic_measure< Graph,
        typename property_traits< DistanceMap >::value_type, T >();
}

// This is a little different because it's expected that the result type
// should (must?) be the same as the distance type. There's a type of
// transitivity in this thinking... If the average of distances has type
// X then the average of x's should also be type X. Is there a case where this
// is not true?
//
// This type is a little under-genericized... It needs generic parameters
// for addition and division.
template < typename Graph, typename DistanceType >
struct mean_graph_distance_measure
: public geodesic_measure< Graph, DistanceType, DistanceType >
{
    typedef geodesic_measure< Graph, DistanceType, DistanceType > base_type;
    typedef typename base_type::distance_type distance_type;
    typedef typename base_type::result_type result_type;

    inline result_type operator()(distance_type d, const Graph& g)
    {
        BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
        BOOST_CONCEPT_ASSERT((NumericValueConcept< DistanceType >));

        if (d == base_type::infinite_distance())
        {
            return base_type::infinite_result();
        }
        else
        {
            return d / result_type(num_vertices(g));
        }
    }
};

template < typename Graph, typename DistanceMap >
inline mean_graph_distance_measure< Graph,
    typename property_traits< DistanceMap >::value_type >
measure_graph_mean_geodesic(const Graph&, DistanceMap)
{
    typedef typename property_traits< DistanceMap >::value_type T;
    return mean_graph_distance_measure< Graph, T >();
}

template < typename Graph, typename DistanceMap, typename Measure,
    typename Combinator >
inline typename Measure::result_type mean_geodesic(
    const Graph& g, DistanceMap dist, Measure measure, Combinator combine)
{
    BOOST_CONCEPT_ASSERT((DistanceMeasureConcept< Measure, Graph >));
    typedef typename Measure::distance_type Distance;

    Distance n = detail::combine_distances(g, dist, combine, Distance(0));
    return measure(n, g);
}

template < typename Graph, typename DistanceMap, typename Measure >
inline typename Measure::result_type mean_geodesic(
    const Graph& g, DistanceMap dist, Measure measure)
{
    BOOST_CONCEPT_ASSERT((DistanceMeasureConcept< Measure, Graph >));
    typedef typename Measure::distance_type Distance;

    return mean_geodesic(g, dist, measure, std::plus< Distance >());
}

template < typename Graph, typename DistanceMap >
inline double mean_geodesic(const Graph& g, DistanceMap dist)
{
    return mean_geodesic(g, dist, measure_mean_geodesic(g, dist));
}

template < typename T, typename Graph, typename DistanceMap >
inline T mean_geodesic(const Graph& g, DistanceMap dist)
{
    return mean_geodesic(g, dist, measure_mean_geodesic< T >(g, dist));
}

template < typename Graph, typename DistanceMatrixMap, typename GeodesicMap,
    typename Measure >
inline typename property_traits< GeodesicMap >::value_type all_mean_geodesics(
    const Graph& g, DistanceMatrixMap dist, GeodesicMap geo, Measure measure)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename graph_traits< Graph >::vertex_iterator VertexIterator;
    BOOST_CONCEPT_ASSERT(
        (ReadablePropertyMapConcept< DistanceMatrixMap, Vertex >));
    typedef
        typename property_traits< DistanceMatrixMap >::value_type DistanceMap;
    BOOST_CONCEPT_ASSERT((DistanceMeasureConcept< Measure, Graph >));
    typedef typename Measure::result_type Result;
    BOOST_CONCEPT_ASSERT((WritablePropertyMapConcept< GeodesicMap, Vertex >));
    BOOST_CONCEPT_ASSERT((NumericValueConcept< Result >));

    // NOTE: We could compute the mean geodesic here by performing additional
    // computations (i.e., adding and dividing). However, I don't really feel
    // like fully genericizing the entire operation yet so I'm not going to.

    Result inf = numeric_values< Result >::infinity();
    Result sum = numeric_values< Result >::zero();
    VertexIterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        DistanceMap dm = get(dist, *i);
        Result r = mean_geodesic(g, dm, measure);
        put(geo, *i, r);

        // compute the sum along with geodesics
        if (r == inf)
        {
            sum = inf;
        }
        else if (sum != inf)
        {
            sum += r;
        }
    }

    // return the average of averages.
    return sum / Result(num_vertices(g));
}

template < typename Graph, typename DistanceMatrixMap, typename GeodesicMap >
inline typename property_traits< GeodesicMap >::value_type all_mean_geodesics(
    const Graph& g, DistanceMatrixMap dist, GeodesicMap geo)
{
    BOOST_CONCEPT_ASSERT((GraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT(
        (ReadablePropertyMapConcept< DistanceMatrixMap, Vertex >));
    typedef
        typename property_traits< DistanceMatrixMap >::value_type DistanceMap;
    BOOST_CONCEPT_ASSERT((WritablePropertyMapConcept< GeodesicMap, Vertex >));
    typedef typename property_traits< GeodesicMap >::value_type Result;

    return all_mean_geodesics(
        g, dist, geo, measure_mean_geodesic< Result >(g, DistanceMap()));
}

template < typename Graph, typename GeodesicMap, typename Measure >
inline typename Measure::result_type small_world_distance(
    const Graph& g, GeodesicMap geo, Measure measure)
{
    BOOST_CONCEPT_ASSERT((DistanceMeasureConcept< Measure, Graph >));
    typedef typename Measure::result_type Result;

    Result sum
        = detail::combine_distances(g, geo, std::plus< Result >(), Result(0));
    return measure(sum, g);
}

template < typename Graph, typename GeodesicMap >
inline typename property_traits< GeodesicMap >::value_type small_world_distance(
    const Graph& g, GeodesicMap geo)
{
    return small_world_distance(g, geo, measure_graph_mean_geodesic(g, geo));
}

}

#endif

/* geodesic_distance.hpp
yCvexzjiZJOtB40sxmNtzlKJHbwiSxfiiBtXAffd9SyMclIjR1G7CcVKbQ7Qe6zBhiYOz62hJFz8xwR1bIXMqNct/iNH3+TmupE2Y7RZhyaQF+lNBUKOgd3rK3IrkEHx7Z4pd/UkW3KDL533nb2fE+1V0lOYWPkjrCbFFSVEIv1rIm8igtQpPrQcKse+sHIrylUuBjCBAF1u7al78hYigJusj6OiYwUlmA4pFDxAZ4SqiA9InkVDn1NAQDju6/EC5ffDn4xGtxjim+bXzlHRir26cwG3/F/SgnASKxcPAVECd/RDpetIEF4rae3YR6bCJL/ErFC12i+yWo1/Z1LxgJWW2Jmjr2xt7ZJamvNQAe+TFmkLsX52KnKaeVCCJIcDmMUWW2mKt5KIeTGWmBbaOjuuTC9h5b1AU5O9eZ3FsDudeDm4aSZ6jiCJuhueD9Hemj/sNMr+3QMNj/iIUda1NI5hDItj+2ZV/jBQoPIPgO48IW5EBBHBIrfyCNhCLzQmsjLO9M4jiIiSVa+W5BxteN131Vfq5Rn/KUu+oGDR8xzGq0frm8ZXmFACZfnk1eZ+5PB7JUymdNqCkHX6ix/kXeVasUkwkVk9TMXrJJokU+rdMe6//Q+W+j/975+lz7EKDz0iSIRHScMR2EIbZAZQMaCiVgD6RLWLNlIJKcy/Wb20UylyWajQ8S6PpwoJsnSeO9QQ15k9c6+SfKLUdIPtbd4PePIOf7h21spzcwwonJFvo2PJ/PiSscQa9McTKcXGb4e7hw2jipymm1kIrB22PQIAr67PNlqHeUzykKojPUhxeh38QnZ+XqzHZvNb4U5kOB01+9q+Hc4fxDc3NKA5yI+9oLwUYQxI4p4bZnTSENd71fORvedTr3XjLxf3XhvSk4yZpd8O7v4Fs8aiYiyo8ARZ2/AReRbmzb/+9bzdbvkeC3oJKtwsr1FK0TbjrW4LPiwYE0OjtpzNDpKcdAF+TnLt3umJLoBZEDe2/TnftrswASvAS7c+K+XPCR1sew5jfgolilaVQhJParEAM/HQujERvlBlyS7bzMUxWTyXMoY4tDYwRMJCBbM/F83JtBHjqmB14VWFxV++YCW2W67AEMBWoYoPluIbZTvhOXZXzAB8/8JUQkGSi6gfefBcv2lSF/05pt0fI1lVIxkQDCqwtTpPpyReL9QynOD0GqyGH9Nx73xI56LI3TPEWNZgG5OL7l6EPmkbI7b7Ad9qeUrZZfbnLWvm+uuEuFGf7SHm7GM+sJePqaEJ9EQEuQOMVNgtiNk54RJa3AiRK1hwymthPYCOGHGWbSFxf+F2APR//fefTEizWbM7U5iufZZdvY0HcV+/S3Nzam+VmM3eHJdmtfvr6nZ0UMIc447eRD35qIx9fQ8Dst/N0LWgHHHK5AoP9jgZiWCjgUvJRxTa1M9ImAii60YtU7yL1jgK+4Xk4WQ0bmTPlZAiv8g/Etf2xPGVnZTJSe71II22kI/e/UqIxg/genfageT7c6hYrhdadGZA0CBwZgueoLaCCwdAw1pFGzyCxtGhKK65pG0tvXypvnA/8ldw++dlIczEJjqSgXOragzIhsOo3NDgCYhbdQ9R/a0dQzwzT2ZSyE7Q702G1sYKl52S5FqZLU1ktS3Wp/0lNg6NJc8Ehh6eVfmWHIDuvCSGv/Sg4W/qFxX/CFT65iF6+6tQ+GdgZk+d8B2DYy0us+3FpD0t6XaTYC0d3B98X19wQpn75p3Qle0EazjL5ztLc53baXHfU4c3Wz9X+d/uRzFgzxhyJUJxAv3GRI76nE1LR7syA3RMwYH2UgypR38zn/Vg89XASrjJSWcS/xTtI6Exyl3fq2n3HOGGMVc=
*/
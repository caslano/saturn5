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
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
*/
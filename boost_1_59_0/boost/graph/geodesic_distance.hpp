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
//      NOTE: Disabled until this concept assert is fixed in Boost.ConceptCheck.
//         BOOST_CONCEPT_ASSERT((AdaptableBinaryFunctionConcept< Divides,
//             ResultType, ResultType, ResultType >));

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
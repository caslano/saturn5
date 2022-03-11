// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_CLOSENESS_CENTRALITY_HPP
#define BOOST_GRAPH_CLOSENESS_CENTRALITY_HPP

#include <boost/graph/detail/geodesic.hpp>
#include <boost/graph/exterior_property.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{
template < typename Graph, typename DistanceType, typename ResultType,
    typename Reciprocal = detail::reciprocal< ResultType > >
struct closeness_measure
: public geodesic_measure< Graph, DistanceType, ResultType >
{
    typedef geodesic_measure< Graph, DistanceType, ResultType > base_type;
    typedef typename base_type::distance_type distance_type;
    typedef typename base_type::result_type result_type;

    result_type operator()(distance_type d, const Graph&)
    {
        BOOST_CONCEPT_ASSERT((NumericValueConcept< DistanceType >));
        BOOST_CONCEPT_ASSERT((NumericValueConcept< ResultType >));
        BOOST_CONCEPT_ASSERT((AdaptableUnaryFunctionConcept< Reciprocal,
            ResultType, ResultType >));
        return (d == base_type::infinite_distance()) ? base_type::zero_result()
                                                     : rec(result_type(d));
    }
    Reciprocal rec;
};

template < typename Graph, typename DistanceMap >
inline closeness_measure< Graph,
    typename property_traits< DistanceMap >::value_type, double,
    detail::reciprocal< double > >
measure_closeness(const Graph&, DistanceMap)
{
    typedef typename property_traits< DistanceMap >::value_type Distance;
    return closeness_measure< Graph, Distance, double,
        detail::reciprocal< double > >();
}

template < typename T, typename Graph, typename DistanceMap >
inline closeness_measure< Graph,
    typename property_traits< DistanceMap >::value_type, T,
    detail::reciprocal< T > >
measure_closeness(const Graph&, DistanceMap)
{
    typedef typename property_traits< DistanceMap >::value_type Distance;
    return closeness_measure< Graph, Distance, T, detail::reciprocal< T > >();
}

template < typename T, typename Graph, typename DistanceMap,
    typename Reciprocal >
inline closeness_measure< Graph,
    typename property_traits< DistanceMap >::value_type, T, Reciprocal >
measure_closeness(const Graph&, DistanceMap)
{
    typedef typename property_traits< DistanceMap >::value_type Distance;
    return closeness_measure< Graph, Distance, T, Reciprocal >();
}

template < typename Graph, typename DistanceMap, typename Measure,
    typename Combinator >
inline typename Measure::result_type closeness_centrality(
    const Graph& g, DistanceMap dist, Measure measure, Combinator combine)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< DistanceMap, Vertex >));
    typedef typename property_traits< DistanceMap >::value_type Distance;
    BOOST_CONCEPT_ASSERT((NumericValueConcept< Distance >));
    BOOST_CONCEPT_ASSERT((DistanceMeasureConcept< Measure, Graph >));

    Distance n = detail::combine_distances(g, dist, combine, Distance(0));
    return measure(n, g);
}

template < typename Graph, typename DistanceMap, typename Measure >
inline typename Measure::result_type closeness_centrality(
    const Graph& g, DistanceMap dist, Measure measure)
{
    BOOST_CONCEPT_ASSERT((GraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< DistanceMap, Vertex >));
    typedef typename property_traits< DistanceMap >::value_type Distance;

    return closeness_centrality(g, dist, measure, std::plus< Distance >());
}

template < typename Graph, typename DistanceMap >
inline double closeness_centrality(const Graph& g, DistanceMap dist)
{
    return closeness_centrality(g, dist, measure_closeness(g, dist));
}

template < typename T, typename Graph, typename DistanceMap >
inline T closeness_centrality(const Graph& g, DistanceMap dist)
{
    return closeness_centrality(g, dist, measure_closeness< T >(g, dist));
}

template < typename Graph, typename DistanceMatrixMap, typename CentralityMap,
    typename Measure >
inline void all_closeness_centralities(
    const Graph& g, DistanceMatrixMap dist, CentralityMap cent, Measure measure)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT(
        (ReadablePropertyMapConcept< DistanceMatrixMap, Vertex >));
    typedef
        typename property_traits< DistanceMatrixMap >::value_type DistanceMap;
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< DistanceMap, Vertex >));
    BOOST_CONCEPT_ASSERT((WritablePropertyMapConcept< CentralityMap, Vertex >));
    typedef typename property_traits< CentralityMap >::value_type Centrality;

    typename graph_traits< Graph >::vertex_iterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        DistanceMap dm = get(dist, *i);
        Centrality c = closeness_centrality(g, dm, measure);
        put(cent, *i, c);
    }
}

template < typename Graph, typename DistanceMatrixMap, typename CentralityMap >
inline void all_closeness_centralities(
    const Graph& g, DistanceMatrixMap dist, CentralityMap cent)
{
    BOOST_CONCEPT_ASSERT((GraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT(
        (ReadablePropertyMapConcept< DistanceMatrixMap, Vertex >));
    typedef
        typename property_traits< DistanceMatrixMap >::value_type DistanceMap;
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< DistanceMap, Vertex >));
    typedef typename property_traits< CentralityMap >::value_type Result;

    all_closeness_centralities(
        g, dist, cent, measure_closeness< Result >(g, DistanceMap()));
}

} /* namespace boost */

#endif

/* closeness_centrality.hpp
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
*/
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
OtFQHfHt6+n8fZxUVvCbr4PyzKWgjwZAVFrYR5EOHnyUL/dc8dymNF/hhzRyQKdE/A/vvHBHr0tGlVGf3PFaFfo8YJjm54umZcQvw1mGRBqXaQROEEa840ZfMLXvFDMr8/OCdXWpuTT52FKA+WT69msRHOh/jezO1vlNXeSNJalXmXFg94aRDjgh7A5dZLTlNgNiDnSzZXTdUvNBdrO18cTNLFqd32zG6ZsbH8TpW9PZBfOn3TaGYfWxKwmEuQg8WC79c9AgrbZq81mv3NQgrOSCODZoXLkCVfb1c+FIDidM9yiUewh35Oefwc1q4GY1cNMauKmHc/PujrkSp7MtLb3mXJgrRXy+GlNuBuuArZHxMkZ8rqFVutzLMdLoeSKVdwsIes+68TUuG9yXJU5jMAMjh8xhP2Nm4d3OruCRTCSXeXLwAD8ZK0+O55m+HzaSBVPJ6Ox6J4cwKb+KbP9f144//URS7B31ppF8xPc8wzdXV3fxTQ++zE6efJd8CTe8Yk/OfQyfKF2jMFUjWNKx89Hwxgr5N+/twfvyC7phJgj8Tms/Ehr0w5aK/Ugz2WdOu0LZYEzk11K49YwQmQz5S9UvsGyqJ+D4ktSy9Ly7YVw+2PFyhqRFrjQI73HfWbVBLoGc8PidFbJXzgd8QgR7mMEF+RQuVftZ69JGpd+QKI2Nyzu5pT0PVotO7Pl31bWfGeE45yd17wRysdFn4mD/KF+LLjfNiECtKEI7+MDdkuEte+mC++Q7QEjH2rtUdEXXfh7mrxpdNAn9VYO/3nVnhOmxrYpWkgzN9DCaXr2Qg/S4D5J7N+NJaRgOFN4DKu5CIXh6b6bq5Hm5H2iM0Eo6Ry+lZvz5spunZ970U9mMhYjg6j1AuwnFgRr5I/TdQeuOe/RUtGwgy9yJxuzQaarZTrG5WTOV0218mvPEtD2so9GYy98RcIpm95IA/7JS+3wUW9KWK8N1Tx/la4I/slHwV2rGEIj8FgIL8Xp5z7f7r6BMYW4yJ12qevvFPkNVrwvvPIH06b+YlBWY5HkPIbCfZQz/OD4BHJixRXLbuMRFWdze8zh870KinsMaLPKnAZobzXv1lADjghnQ4SODdBlcOpgaFvpPZhnbt7xASjfHVf/hWvpm4sfC9xD6K43k/t7fOP0GOFG/64xuMnfr1lWs+lYPotP3DfR8W0Bq/KGafv1dZOd96n6LrCAe/IPHxARDysn7BDC2Hw+C22VReVLNnngmsgzZv8p0sUXlGOQ9E4l+a1otWe9n+mHx2MFcIITm1WBm9frcUfv7n+MGi2a/8NcB2rzjyztsiOJ6H1/ZOW1/L9H/epmETcZyMlIxaKvPfYG9m8NCQ+YK38w5W3IjhPXoZWr45Peaoc80SlKxgfuqdtiQTzmqE1CoQ9ewT8BR9kCrSZzyZXPLDxVk4kphyVW7d+Qs498Ousp2Ve9BzoQUwcTunyOT/JJPvfJF27l+V+3VaUw37cHAwmENbStYBcflf0WifG9QPU+5RTwYhy6Cnr6lrKhc6jLVL/RunRTKMvodSVIgZ0/qHz+0qABYGYOHrDGQfATuEVkdi3IdOTQ78iWtYAsLRZ4u51WoH6RYV/q/gC/CdWBh3+zOZtkSPRUCxVSId0B5xxkau/TeKB6O2Ys1jHG64IGKFDIFY/08ND0NWz0ETrvR/GHKvCeNkvXQOSULthwOJhmEMr8vXbFf1DzKMH639K/Wzz7eoooMSoUrouFQkJK3pbVEP0yEzrXe54bbwVDPdxrQ4xk2522oyuXkJL1XAMC1XZu+nQBiIk1OjGeBHXc/Im8kwU8NvuJPOn40i/mDlz4LvCE0w3izD1c32d5WBUy/xs9W3LA=
*/
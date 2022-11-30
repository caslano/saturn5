// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_ECCENTRICITY_HPP
#define BOOST_GRAPH_ECCENTRICITY_HPP

#include <boost/next_prior.hpp>
#include <boost/config.hpp>
#include <boost/graph/detail/geodesic.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{
template < typename Graph, typename DistanceMap, typename Combinator >
inline typename property_traits< DistanceMap >::value_type eccentricity(
    const Graph& g, DistanceMap dist, Combinator combine)
{
    BOOST_CONCEPT_ASSERT((GraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< DistanceMap, Vertex >));
    typedef typename property_traits< DistanceMap >::value_type Distance;

    return detail::combine_distances(g, dist, combine, Distance(0));
}

template < typename Graph, typename DistanceMap >
inline typename property_traits< DistanceMap >::value_type eccentricity(
    const Graph& g, DistanceMap dist)
{
    BOOST_CONCEPT_ASSERT((GraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< DistanceMap, Vertex >));
    typedef typename property_traits< DistanceMap >::value_type Distance;

    return eccentricity(g, dist, detail::maximize< Distance >());
}

template < typename Graph, typename DistanceMatrix, typename EccentricityMap >
inline std::pair< typename property_traits< EccentricityMap >::value_type,
    typename property_traits< EccentricityMap >::value_type >
all_eccentricities(
    const Graph& g, const DistanceMatrix& dist, EccentricityMap ecc)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename graph_traits< Graph >::vertex_iterator VertexIterator;
    BOOST_CONCEPT_ASSERT(
        (ReadablePropertyMapConcept< DistanceMatrix, Vertex >));
    typedef typename property_traits< DistanceMatrix >::value_type DistanceMap;
    BOOST_CONCEPT_ASSERT(
        (WritablePropertyMapConcept< EccentricityMap, Vertex >));
    typedef
        typename property_traits< EccentricityMap >::value_type Eccentricity;
    BOOST_USING_STD_MIN();
    BOOST_USING_STD_MAX();

    Eccentricity r = numeric_values< Eccentricity >::infinity(),
                 d = numeric_values< Eccentricity >::zero();
    VertexIterator i, end;
    boost::tie(i, end) = vertices(g);
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        DistanceMap dm = get(dist, *i);
        Eccentricity e = eccentricity(g, dm);
        put(ecc, *i, e);

        // track the radius and diameter at the same time
        r = min BOOST_PREVENT_MACRO_SUBSTITUTION(r, e);
        d = max BOOST_PREVENT_MACRO_SUBSTITUTION(d, e);
    }
    return std::make_pair(r, d);
}

template < typename Graph, typename EccentricityMap >
inline std::pair< typename property_traits< EccentricityMap >::value_type,
    typename property_traits< EccentricityMap >::value_type >
radius_and_diameter(const Graph& g, EccentricityMap ecc)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename graph_traits< Graph >::vertex_iterator VertexIterator;
    BOOST_CONCEPT_ASSERT(
        (ReadablePropertyMapConcept< EccentricityMap, Vertex >));
    typedef
        typename property_traits< EccentricityMap >::value_type Eccentricity;
    BOOST_USING_STD_MIN();
    BOOST_USING_STD_MAX();

    VertexIterator i, end;
    boost::tie(i, end) = vertices(g);
    Eccentricity radius = get(ecc, *i);
    Eccentricity diameter = get(ecc, *i);
    for (i = boost::next(i); i != end; ++i)
    {
        Eccentricity cur = get(ecc, *i);
        radius = min BOOST_PREVENT_MACRO_SUBSTITUTION(radius, cur);
        diameter = max BOOST_PREVENT_MACRO_SUBSTITUTION(diameter, cur);
    }
    return std::make_pair(radius, diameter);
}

template < typename Graph, typename EccentricityMap >
inline typename property_traits< EccentricityMap >::value_type radius(
    const Graph& g, EccentricityMap ecc)
{
    return radius_and_diameter(g, ecc).first;
}

template < typename Graph, typename EccentricityMap >
inline typename property_traits< EccentricityMap >::value_type diameter(
    const Graph& g, EccentricityMap ecc)
{
    return radius_and_diameter(g, ecc).second;
}

} /* namespace boost */

#endif

/* eccentricity.hpp
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
*/
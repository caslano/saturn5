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
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
eaxjwNNtoHTU98G3vWbiiLwMwAgA1LvOe9GaNcUSPXm1iCO7D2yi23sQZc6VI9eVnQIsEwZW1TIStKSP6quv2tMarlrSqeNVZTZbiSXeHPDLT/ydXYD0FXmlm5sbyGklTYq6HsQa6JSymluP5rZNGUpzv87/bloqB5HD9xG6vrkz7A8ZOwY+cyQNHDiFDskUuV4QjzElZcI5IS/6J9E0l9MKDYp4WzC3qI/2HxQ7BMxahbbiCDOtPfdpzTCpD4Ni7DbyU9Kc0Xl1WlfQrdjgDkGtsO5VxoUq5g69yJaRkhTdRzXJQZgqtI+O9+vMoNQk15BSXBtX0rf8Z/Ocxgyhedo4/EwAlF+vZfH+ugvRXDy9GI7kq9I0FY0BNm1vB288sFB9o8TJ7bhJzqQWbBwh/bRTKUtpBXA2/tNm3shoD0/Div/0fnwjiF8/C23dBh/O0vh4SHqVVvwjlAXhgxpNqMCVV5EHEtFIT5HBf5f+QWNqUHpkhzxgpZ0vJm/TKEvmDx2SPdmXzgKiS5ZJoOAAfptBuQ1a2qzGf5/83o/Mlz3AOvpurZVuHkOpWQ==
*/
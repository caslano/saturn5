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
qOc1JjTVmzdF1csu07pu4wLJUlln1difCmh02mf1eGDESK8ipW7xOHeGY718+/CEhWLd6nbVb01/bNs961rVhETT3SiVOKqjUf9IcDjsqECv434QuFJi/JIzQvc+5qleY7xeJ/m5b4L8lh8L1jeq7eSt87DUAXL807ACW5xR36luXCVqhfnlpOj51qh+g6TQXJcpXLVmpfRt5YUFOq+OCbM8/2OXX1OeHx7Yf9jV0EUWf7SwIOzi6oBFUF1fWyttj+2bLpU/tDgsxFh+4/74WDqeu8bVGcc7A5g+GWvEpJOaNyrmEgW1yWVLJNnK85asKHSbq6/4/tH5fo/Qryo+rVC6yxUkdGuTaVE+G8yBYDWXnq3lbN21q0FdHsWWWSCFUT1lUIOUoacNahH0jEbiSls+Lxg7yHlukbZqVha4YW33bRwd9c0GS0MZ3VppvpLcIrns6zbJoFPCHVR/ztduNMEXWb9ReigJmbSn7niFab6H/FEmzH0pqwrLy/LzpNqWlSwvhpbxaIhff8JC8d757KtSd4d08mrzve5bdLvg2wktgXGqM9/wFx0eJxe8kMhOLhMqyp2PdfpU+35IYSgvJdnUr7Rf7jNPeM+ctno5FUfl+KN8jTN8LPU6W9qPc5vOlgnUn9rxwfc/ub63BNeb7jDjYb40vko3F+pZ3IYtgxfhw5bB1caf7IAN8AKu/eT8su8OSlI/YCmE/e0zutHvvN/W4d0thrXfkmvSyk6BxYYfHduTLN38SufL52ui1dr2XxTSySy60eUHdE3SWj5l52VLOLWfHK2XrGRTS4Hj5XdNrGIs46tP61SNpdmtNb6Z9YcAVurnvq8wrX7JxALb0LRZFG0+rzNJ9wrGOtsaU4uRpraEtNpfdY7PYrChUA2xLEFVG64zQTNN1cTSMl7ez6ol87XhJ3Va/cpKdVv3CPaUYxU6GjpztSvA46PRvYlO5x/cG0FO7ytYPMFeF3b0YtaErSSaktywa2Ii43YzQpCOWzqABbIKp9SHnHGFHp7oTJCcm6Jb1MLGDc1bo63FjfWutX1MirCS7rKyVV0jluR66RmyLU5eui6qntVPrxNu/oIcl1Kv+dyHFsC9Y7gFx58At9CesTKLuktDfHBlak+MuSKmJ9VG9znp/IqXnl5Zklea5479Pjqap8Wrsa1qTZ5lc5T79RZbpv2tsjn8PEbPJwY1sv6bkL+yrDLfmbdvlDSubcLtZzRfWrOhRnZLlbrfcXdVl4x6QgdEF5E3U62yIA6VKtejVfmpO6F9dZ8E0qvekqzqqFBZEb3R7UorWykjCe2r62M/jHavqQd0mMTAkG0SA/q38+V1mXczv+VxHRVpsx2O+nWP+e1NjPZphk6bDvj+IIe7SzVH2aypLhAvpPxppC6LoatxkRrWOjxWrwWQH8KHHVZ3ATroeuzxS4czvvzcQeZ9vwgiiqvThN47mtct630x3K9radFj62+S77I8WU/+YoN+YbRGh1G/S+f+7dqFboyaccZM662eJjug0WH5USyNCc1zWru50VuJV+qnmvHxbzXWcaihTJY7wf2Nl4bzdQjE5R0mdKSqukEzZRqMjo6UPJMPAUfi06+N36EKoi6PUWsoMdlK3WZCEH5uR6zn/Jk0eeeXYqT+2eua67UrHdw1ug2Uhcr5sm9St0W2jXOpxenHdAM+IdimGSv4+XBrpj1JDbvVFn5ymKV7c7pRhj2q0O/JKPyHGIaqpa7XbYM9j92j/Q4Oa48wz+lIWCObI22dNbKZZ+kYLamjgiwVThYNZW74YF+jzbLzA/20uw51QYipbGqoln7Mf44Weq5h7NnbHwbWDCXj6mvFbbG1kqONLFXjpIueuTs=
*/
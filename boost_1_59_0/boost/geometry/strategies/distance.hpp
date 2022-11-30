// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DISTANCE_HPP
#define BOOST_GEOMETRY_STRATEGIES_DISTANCE_HPP


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace distance { namespace services
{


template <typename Strategy> struct tag
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Strategy.",
        Strategy);
};

template <typename Strategy, typename P1, typename P2>
struct return_type
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Strategy.",
        Strategy, P1, P2);
};


template <typename Strategy> struct comparable_type
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Strategy.",
        Strategy);
};

template <typename Strategy> struct get_comparable
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Strategy.",
        Strategy);
};

template <typename Strategy, typename P1, typename P2>
struct result_from_distance
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Strategy.",
        Strategy, P1, P2);
};




// Default strategy


/*!
    \brief Traits class binding a default strategy for distance
        to one (or possibly two) coordinate system(s)
    \ingroup distance
    \tparam GeometryTag1 tag (point/segment/box) for which this strategy is the default
    \tparam GeometryTag2 tag (point/segment/box) for which this strategy is the default
    \tparam Point1 first point-type
    \tparam Point2 second point-type
    \tparam CsTag1 tag of coordinate system of first point type
    \tparam CsTag2 tag of coordinate system of second point type
*/
template
<
    typename GeometryTag1,
    typename GeometryTag2,
    typename Point1,
    typename Point2 = Point1,
    typename CsTag1 = typename cs_tag<Point1>::type,
    typename CsTag2 = typename cs_tag<Point2>::type,
    typename UnderlyingStrategy = void
>
struct default_strategy
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Point type combination.",
        Point1, Point2, CsTag1, CsTag2);
};


}}} // namespace strategy::distance::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DISTANCE_HPP

/* distance.hpp
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
*/
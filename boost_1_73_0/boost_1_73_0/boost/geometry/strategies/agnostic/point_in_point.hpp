// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POINT_HPP
#define BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POINT_HPP


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{

template
<
    typename Point1, typename Point2,
    typename CSTag = typename cs_tag<Point1>::type
>
struct point_in_point
    : strategy::within::cartesian_point_point
{};

template <typename Point1, typename Point2>
struct point_in_point<Point1, Point2, spherical_equatorial_tag>
    : strategy::within::spherical_point_point
{};

template <typename Point1, typename Point2>
struct point_in_point<Point1, Point2, spherical_polar_tag>
    : strategy::within::spherical_point_point
{};

template <typename Point1, typename Point2>
struct point_in_point<Point1, Point2, geographic_tag>
    : strategy::within::spherical_point_point
{};


}} // namespace strategy::within


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POINT_HPP

/* point_in_point.hpp
0o7YAaM8P3IJld5vwadD8QlT66FPt6xoYcd7KfFW4+nzW/0bKSUatMnzO34qIdFs/JQJ6Vw5IU2OiuRJ
*/
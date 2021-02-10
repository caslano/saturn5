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
xfXM1xKrTOuAf7o0G78ZjGYzaA/HOBm3MRVOughfTi6Pzz5f4svw4mJ4ejnB2d8Ynk4C2ceT0yNeesliFnRbWnIsbiGLUknKVpp/rsWtPalTVWWEdli8xJGvyn7e/m7cy4Lm/CjyYItnVvE2HYVSb4nwtQU8GOy5QihFdoC4h1Uf2jAZC26rV4KXnMtDfdN/tNyJgvQAdXlppPb1+oYF0nTrG+iCM4TMSHuZCoV/afkYW7mVjeOfP4ktRBdiCjcG306hXrObAsELh7Yz1rc30LmRGXqlWCojssEPxwojM+FF7cGVindLGkxkhpx+wWr1Jpyaygem/wZblqVXd2ts575HGbUePdQekvnuDg3JR5H1D5R4rju0fqr4TJymRYh7l99r8lNyzzf8bMdbgD1LheFTOHjmhw8bl82NztO1HlY2FCGSJ0NChtaYes3X/xo2nlJT8E8FcVCuI6ObLjrodGTfz/nkSLvAATo3629dvMfLV3iHq6dEc4/o8B4Rfp2oqpnWjqrfsNQwHd5nqj3td7lxVKT55yts3S1/scI+/R9QSwMECgAAAAgALWdKUmQIbs9NBwAARRcAABkACQBjdXJsLW1hc3Rlci9saWIvc3RyY2FzZS5jVVQFAAG2SCRg5Zj/U9s2FMB/z1/x
*/
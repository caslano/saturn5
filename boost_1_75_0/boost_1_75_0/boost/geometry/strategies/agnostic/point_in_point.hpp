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
6Fs3XoBIehgTTlO7EKsjq1RnncQ3XP0wi+0fI9TK+nmYbrE5JwaI2JrD7K2pnT0uwKiKNnAVJZW0DgH4/o/488HS8D2VOCzTnBnicuq64dKe+0PwcULQfFAaQXLZjn0Mq4Ha/dK4BhHghac41IuM35dBYL33iPNgr2talwP7IId1b4S18GDnvTDo5uCOelIYRYg7pmZ9dteOPReU8b0RXjVTdoNREhdjPuAV38GoCskdZLa3XgiwlfkuGDYmjJRQmlyMNKiUgjsHkr6mnjNOLMiy4rL4SgEYwBMTdLLdHgvy2I5n+t6TRRFXUoM5b26yXzPWy2f1cGHE+inBs5OEUEeMi4jLb59z9yyZqqbutPKXILPF0f03dkk1QFEVnR/FA3X6d0CBcOwjn8lA5p8uQzfzCqvq8HmszoD1fcHynQ/lxyGkOYtTM7/uOEbtAYrllE1kV8sdRsQQ6XBY8stL90jXWVfTS0TU3Xl1OlSaC+PgHo9ZjvZ1iHyFZgJXGgoI1Ns5+TSmvReDsderAl/tBgTBfxhAOr/BGGPAgGJJp8Rnd/ZmzinK6oCCYUDM5bXp2NOx9t41jZDHM8QWcoLo5+uU3YY6PKgVc8hKQQHqaDC39ayg9m7hNhXaNk6w4ZiPR2u8EMrX/Q9N/O3Gk3rI0PM+59G+mUGQYvG14rDeCfTbRdzU394otuAuELzy3NSa+Eg9xTR0wO+hjnkF
*/
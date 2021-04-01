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
/JM9W4jzXIejHGGXYAOBAG2nrvrNcMHmbNt4bOWE5lIpFg6Sdt0o52EkAgeGkA5axiXCUyLFyJodLLjPYWSfH4Qpg9IWhMmGm/q5NnMUuK3ngj/Gx4h19S5pdS5BIzgqu8Qrg598JYTqJXliO1+X9jzcOVEAHhPf5Bi/GksQxF8mNgic4AGvdizVE31QXMQAaHLeSSGuy2XgyMbE2FteI96l9am4Moijlq7gt016/ulVsT/02ZP9ATl3PzbwcSXf1BABdAP89kwSU/lervtEA0WBORe5Kl+g8fMCP8mqdkT6mC2Gdqdfyqbdm4tgFEiHweV/QD+letjEaLIJPykYSBQK3YTTpAIY/cJRD76N30J/g6/W3r+gj+IMOhsbGKK49g39eJEE2MOuCGM6+aZV6HvqP/X0hSpxjuwWWBciFGBjIODwHh5ixYZDXdJdJbHLzikomB+UiAsN4tux3CCKuN8SdpCRYsef1taRUdCdW6rYyrlgPcAuVMqsc+zt394d/fDEMIhxGw9ICyI4zh+nhZ8FMWY+AErFtiXQiW3CtnhzveD9cmIwF4Ux5A==
*/
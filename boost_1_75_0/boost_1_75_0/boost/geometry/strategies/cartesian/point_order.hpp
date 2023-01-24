// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/point_order.hpp>
#include <boost/geometry/strategies/cartesian/area.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

template <typename CalculationType = void>
struct cartesian
    : strategy::area::cartesian<CalculationType>
{
    typedef area_tag version_tag;
};

namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef cartesian<> type;
};

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP

/* point_order.hpp
d3AYfziThOxTOk+yuYvDcXFR1pvbIR1GxfOlt8Py8gfNTVNEU6ERNVtqb9PrrOy7kGznqxhSeba+N22MCs5XmZA5gnu+1WCBG0snIm+FKDvSARt62y8kMwvXorXT7YcnIhD/bf9pCPkWMRtzj8cvaAzlfOqslABUhRHoxnWVaf5GAYNn/1qoXIsxN/dRu620f+MvQr3ib0IdyYWCn9IQgRWFOJT4S6z2VnkB9sPKlNqfw3c4l4cGieW3sPU/wlfzk8sVf1aZMaxVe+c9TYwoxEi9+OqfTlV9WvBourRJzsiMTy16v1oeW8iNcYW1tsERAyNJpnJTevUe8F06CNWWWRPYHteOY1g45tEIodl4NOBtOwlw1/HV+OPLszQtKL59HIJSW9j07Iija3AiUrbxmwXYsNSLFpBRAm9xHHD8OCOibCNM9tssDP8vQt1hH4Qw3aiaDHJpPyt9GJsxCKYQzc5OhzPM+EHQ7tTvbGc+3I2nA5t0LHliSmaBtWkBuTmVzx+o7U2UJ3rrbyhmDlrCHNfk6RmzI182OP+NUEdjo2oPLl6Bl+yc/Jzom/jJJHeOyUdtLD9/pxsG2OH5q1HP7oMgZoStEAS3RjP+5AtzRgS9qkHSDeP7IZobZbQTv2Nw8cEF4MPVRtElvTSxn/vOl2Uh9Vr6ZKUvgLElzBm9l7gLebPmGCKxidhjofBkz3IKxTvuhD198fNvYyNd
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2017.
// Modifications copyright (c) 2013-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_IMPLEMENTATION_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/relate/interface.hpp>

#include <boost/geometry/algorithms/detail/relate/point_point.hpp>
#include <boost/geometry/algorithms/detail/relate/point_geometry.hpp>
#include <boost/geometry/algorithms/detail/relate/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/relate/linear_areal.hpp>
#include <boost/geometry/algorithms/detail/relate/multi_point_geometry.hpp>
#include <boost/geometry/algorithms/detail/relate/areal_areal.hpp>

#include <boost/geometry/strategies/intersection.hpp>
#include <boost/geometry/strategies/within.hpp>


namespace boost { namespace geometry {


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch {

template <typename Point1, typename Point2>
struct relate<Point1, Point2, point_tag, point_tag, 0, 0, false>
    : detail::relate::point_point<Point1, Point2>
{};

template <typename Point, typename MultiPoint>
struct relate<Point, MultiPoint, point_tag, multi_point_tag, 0, 0, false>
    : detail::relate::point_multipoint<Point, MultiPoint>
{};

template <typename MultiPoint, typename Point>
struct relate<MultiPoint, Point, multi_point_tag, point_tag, 0, 0, false>
    : detail::relate::multipoint_point<MultiPoint, Point>
{};

template <typename MultiPoint1, typename MultiPoint2>
struct relate<MultiPoint1, MultiPoint2, multi_point_tag, multi_point_tag, 0, 0, false>
    : detail::relate::multipoint_multipoint<MultiPoint1, MultiPoint2>
{};

// TODO - for now commented out because before implementing it we must consider:
// 1. how the Box degenerated to a Point should be treated
// 2. what should be the definition of a Box degenerated to a Point
// 3. what fields should the matrix/mask contain for dimension > 2 and dimension > 9
//
//template <typename Point, typename Box, int TopDim2>
//struct relate<Point, Box, point_tag, box_tag, 0, TopDim2, false>
//    : detail::relate::point_box<Point, Box>
//{};
//
//template <typename Box, typename Point, int TopDim1>
//struct relate<Box, Point, box_tag, point_tag, TopDim1, 0, false>
//    : detail::relate::box_point<Box, Point>
//{};


template <typename Point, typename Geometry, typename Tag2, int TopDim2>
struct relate<Point, Geometry, point_tag, Tag2, 0, TopDim2, true>
    : detail::relate::point_geometry<Point, Geometry>
{};

template <typename Geometry, typename Point, typename Tag1, int TopDim1>
struct relate<Geometry, Point, Tag1, point_tag, TopDim1, 0, true>
    : detail::relate::geometry_point<Geometry, Point>
{};

template <typename MultiPoint, typename Geometry, typename Tag2, int TopDim2>
struct relate<MultiPoint, Geometry, multi_point_tag, Tag2, 0, TopDim2, false>
    : detail::relate::multi_point_geometry<MultiPoint, Geometry>
{};

template <typename Geometry, typename MultiPoint, typename Tag1, int TopDim1>
struct relate<Geometry, MultiPoint, Tag1, multi_point_tag, TopDim1, 0, false>
    : detail::relate::geometry_multi_point<Geometry, MultiPoint>
{};


template <typename Linear1, typename Linear2, typename Tag1, typename Tag2>
struct relate<Linear1, Linear2, Tag1, Tag2, 1, 1, true>
    : detail::relate::linear_linear<Linear1, Linear2>
{};


template <typename Linear, typename Areal, typename Tag1, typename Tag2>
struct relate<Linear, Areal, Tag1, Tag2, 1, 2, true>
    : detail::relate::linear_areal<Linear, Areal>
{};

template <typename Areal, typename Linear, typename Tag1, typename Tag2>
struct relate<Areal, Linear, Tag1, Tag2, 2, 1, true>
    : detail::relate::areal_linear<Areal, Linear>
{};


template <typename Areal1, typename Areal2, typename Tag1, typename Tag2>
struct relate<Areal1, Areal2, Tag1, Tag2, 2, 2, true>
    : detail::relate::areal_areal<Areal1, Areal2>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_IMPLEMENTATION_HPP

/* implementation.hpp
z8Ey3s8bSEf5jDr2b2WTuJQzpuhMUzT2L5PgubNFLkw50OA+9/v1cFjGwmF6FEwly8al3t2vfrweb0MzH1jwtvaDGYGR7VIlzRksUR+fpez7Tyd24aqnDIaApZPAhSngvUngx0lgqVINzby4oUUrGPzOQpaa/o3bdbqICCwiHioiXi+6JrpolagZWp8fUf92MAA7yGBdkuqKbFHRECxHakJMBEExgwo/ntdDev/vICLH4KPoILnRA9jkEV7rwbUZL/Z1rPUg13tU1HhYB9SrI9JtHuU/qM+PqncPrR9/UK+uErWCNR8Lqv0cVPslqHYwqHanpJAINUWnmKK/maKXTNG1eaGqI+Gq6HDVsHBVlylgr8Iw0LnGw9uv3j2sPuSQMZpniv5pipa2c8JVt1IfqKqEqxpJ8RGqnAjVLQMaUGcSGDQJ1G/0CK/xeKhQj1TChqvWh6s6hKsei1CdThfGd+aYoidMrSaBphPA+Koa2j6dKeDCOPDlBNB0ChifNoUEZdV5/G9MCSXTOyG5+VfU8EzPwk35B0dKwYPFb/V1MoZAjHTlyTItuaphUKz5uueCC6Wnncab7ctxdyk/jZbLbQH0Qc1WZ0MNfRKymmbfkcjdGDuo4rs8/6FBb13Wtjlax/cUm7nvrYWqwJ2sXUlSXrk5zGQxdZt+QL8YwjN8gjdxY1cTWOU25MpruD1JC8/wQ7gO7Uw79FpjtUJe
*/
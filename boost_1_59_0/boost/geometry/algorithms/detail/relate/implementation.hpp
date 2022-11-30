// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021 Oracle and/or its affiliates.

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

#include <boost/geometry/strategies/relate/cartesian.hpp>
#include <boost/geometry/strategies/relate/geographic.hpp>
#include <boost/geometry/strategies/relate/spherical.hpp>


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
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
*/
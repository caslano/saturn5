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
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
*/
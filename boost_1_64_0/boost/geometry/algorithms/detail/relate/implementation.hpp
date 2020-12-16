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
X1Kw/oqhxQX1oLh0NQayt4RqzEeVkkiKxS1gvbKQUvlrVgfKq+QrKTqOT2+Ly4993bw/eMehDoavKMknZbm7TKklH4ld4AHcGnCq9azp41kzUWOpt1DGyXR15xzQnwmYAnsrVpGyCxXS6/wVnsfcBVuDo0pi2FXW5pQW1M3dJUjmcHzaqjiUskhFrmgXjSPQeyipyB9udjLXuUXIzgUfKmyqk+ewOn9B/RUj8JKYBLVg/uztnko+gAu2FJRbkIgmSNMqJF9D87sijLWqQr+n/tRmPKtKv+ZWs9L1j3LfwMZYSg3LA7T8w6PbPqOz/PY8yuPPATUn2d/zsB6JRdRY0iqZTdIFN3uDg+OYkjTScL67qV6vb3YqRqz42PkW38lm68YcsmQOoINKIHEXV1EsUF9zVf/tLWqu+0RQkT9rNGFelQLnIbbtKUWbM0aT7z8TTCHNpUbrKDn/KsqFMrUy8jKIpNFiHY2SgG47aOOGWZjGS0wHiuPsiXnGgwJXUyPr5IArVMDVe1aenCkvyZMCoy0MEyWGtcAQndwd6RcZl8n0VfKp/1cl+qnPZ5VEj3ieI/p0IhsEJEYFoPCEnGXsOZEEiZ1DvYTvc/iY0UuwV2kh7B6mZQkywBNExr0F0KujBXdXlqCrz5OIMkHFk2mk5cLD17XjYEcKRHWXRAbIZceqne9532D+Epp2wy9tTYuV9fBr2UGvzKmpSxQadKkv3hYnGENyWJf2Qsv2vEUQu5MtqiR6HDr3FEj6PjtTzD8VzO3B46UIhsHA2B8YxRUTIpibRafZeCyRN89RXAg6qtj4CGGswHJ42CoZ9PwIHkKMg41GwW4+jfv0U5AJaavhNW4Qja5YFZr7o0RZRg7CmHwQ7cjCrH92a7TbD6h7QNkgx9+k5pEWSTQOdSG5u4yPRkphkWClXLdS7NZ+v4pf1C2gP5GZTv9dWencmY2SVdJ5pHXhx9f3B8fLup7J6743bXJSZwKuabbW/hJQGym2E0dblHe8WASmC4CJGHg5/FejP5MPQ3JQ+IGALHcbr2cOHce8LXrc41XesxPzTjF2jEDiv0ihb/w2ITp5J6aaZjc3GWvQE7Er3z9aXm+xh5Ckax1srCbRshlgVLGS1d1kJotdxw5Mef2JpXo7x+LImpxIfwc8ASES9gwL3VwL3errJGW3HdUvLFSheuMGePRGmwLmlFC/ITEPifIuDnmMUfjI5lR2t2R26z2Csge1RjwXDJe7oXIpLXAOZ/XZ7HbmFdY3nNj/ST+1/73BJq94W0lB7bxuJQ0cSab2bGydAkITYfcSrBg3lSpBzl/JXkP63C/Tr6nuu7rK/APkJMYTSIA3o7x3LSTdTx0Ibyeh5YxHRju/ko9d4nvi+g7xfTzOxLc/Cnwzvg6+GYL+ReJj36LOAyGX6HdARnceMEoKzK6bCQZ3lqS3TJX4Z3w1/q4d4B/fHv8lifh/M+qr8cf5WRSTxO9WqDXi535NieZVDGXRn1M0zRNsV9DE3iz6sy6UZzaNlMsfJ+Tfi/AtHHo/9Bc0BC/kEDsdJw1uJXJYwPBTuwVfaC+4DOHiTE6wYwVYET5lcg4H3Fh/tAjbqXx/BP/LAUttJUzcXGBmdxKyI+g98DCH51H83F1NXTUFS0swK1sI8u2i3LONIIpEWr03EJkYcyZirBC9BWEZxgSEFTR4rntAoBI8GAvywB5RGfMsvRFh+VfkeZbqcJjluy2b8+N21EToCBWmf2G8fqwp9hpxRh5OkpE/rRBzXtBdgopw4ytQEWVKozMBY1sQeVwsvLhdOR9a0b6cv1khyrn8rFhM8YqopvKNUDcZ2IbyIuM7so/8w3+Faod9+HXmjIMq2yc=
*/
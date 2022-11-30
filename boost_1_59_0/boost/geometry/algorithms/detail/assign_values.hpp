// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018-2021.
// Modifications copyright (c) 2018-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_ASSIGN_VALUES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_ASSIGN_VALUES_HPP


#include <cstddef>
#include <type_traits>

#include <boost/concept/requires.hpp>
#include <boost/concept_check.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/util/algorithm.hpp>
#include <boost/geometry/util/is_inverse_spheroidal_coordinates.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace assign
{


struct assign_zero_point
{
    template <typename Point>
    static inline void apply(Point& point)
    {
        typedef typename coordinate_type<Point>::type coordinate_type;

        coordinate_type const zero = 0;
        detail::for_each_dimension<Point>([&](auto dimension)
        {
            set<dimension>(point, zero);
        });
    }
};


struct assign_inverse_box_or_segment
{

    template <typename BoxOrSegment>
    static inline void apply(BoxOrSegment& geometry)
    {
        typedef typename coordinate_type<BoxOrSegment>::type coordinate_type;

        coordinate_type const highest = geometry::bounds<coordinate_type>::highest();
        coordinate_type const lowest = geometry::bounds<coordinate_type>::lowest();
        detail::for_each_dimension<BoxOrSegment>([&](auto dimension)
        {
            set<0, dimension>(geometry, highest);
            set<1, dimension>(geometry, lowest);
        });
    }

};


struct assign_zero_box_or_segment
{
    template <typename BoxOrSegment>
    static inline void apply(BoxOrSegment& geometry)
    {
        typedef typename coordinate_type<BoxOrSegment>::type coordinate_type;

        coordinate_type const zero = 0;
        detail::for_each_dimension<BoxOrSegment>([&](auto dimension)
        {
            set<0, dimension>(geometry, zero);
            set<1, dimension>(geometry, zero);
        });
    }
};


template
<
    std::size_t Corner1, std::size_t Corner2,
    typename Box, typename Point
>
inline void assign_box_2d_corner(Box const& box, Point& point)
{
    // Be sure both are 2-Dimensional
    assert_dimension<Box, 2>();
    assert_dimension<Point, 2>();

    // Copy coordinates
    typedef typename coordinate_type<Point>::type coordinate_type;

    geometry::set<0>(point, boost::numeric_cast<coordinate_type>(get<Corner1, 0>(box)));
    geometry::set<1>(point, boost::numeric_cast<coordinate_type>(get<Corner2, 1>(box)));
}



template <typename Geometry>
struct assign_2d_box_or_segment
{
    typedef typename coordinate_type<Geometry>::type coordinate_type;

    // Here we assign 4 coordinates to a box of segment
    // -> Most logical is: x1,y1,x2,y2
    // In case the user reverses x1/x2 or y1/y2, for a box, we could reverse them (THAT IS NOT IMPLEMENTED)

    template <typename Type>
    static inline void apply(Geometry& geometry,
                Type const& x1, Type const& y1, Type const& x2, Type const& y2)
    {
        geometry::set<0, 0>(geometry, boost::numeric_cast<coordinate_type>(x1));
        geometry::set<0, 1>(geometry, boost::numeric_cast<coordinate_type>(y1));
        geometry::set<1, 0>(geometry, boost::numeric_cast<coordinate_type>(x2));
        geometry::set<1, 1>(geometry, boost::numeric_cast<coordinate_type>(y2));
    }
};


}} // namespace detail::assign
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename GeometryTag, typename Geometry, std::size_t DimensionCount>
struct assign
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not or not yet implemented for this Geometry type.",
        GeometryTag, Geometry, std::integral_constant<std::size_t, DimensionCount>);
};

template <typename Point>
struct assign<point_tag, Point, 2>
{
    typedef typename coordinate_type<Point>::type coordinate_type;

    template <typename T>
    static inline void apply(Point& point, T const& c1, T const& c2)
    {
        set<0>(point, boost::numeric_cast<coordinate_type>(c1));
        set<1>(point, boost::numeric_cast<coordinate_type>(c2));
    }
};

template <typename Point>
struct assign<point_tag, Point, 3>
{
    typedef typename coordinate_type<Point>::type coordinate_type;

    template <typename T>
    static inline void apply(Point& point, T const& c1, T const& c2, T const& c3)
    {
        set<0>(point, boost::numeric_cast<coordinate_type>(c1));
        set<1>(point, boost::numeric_cast<coordinate_type>(c2));
        set<2>(point, boost::numeric_cast<coordinate_type>(c3));
    }
};

template <typename Box>
struct assign<box_tag, Box, 2>
    : detail::assign::assign_2d_box_or_segment<Box>
{};

template <typename Segment>
struct assign<segment_tag, Segment, 2>
    : detail::assign::assign_2d_box_or_segment<Segment>
{};



template <typename GeometryTag, typename Geometry>
struct assign_zero {};


template <typename Point>
struct assign_zero<point_tag, Point>
    : detail::assign::assign_zero_point
{};

template <typename Box>
struct assign_zero<box_tag, Box>
    : detail::assign::assign_zero_box_or_segment
{};

template <typename Segment>
struct assign_zero<segment_tag, Segment>
    : detail::assign::assign_zero_box_or_segment
{};


template <typename GeometryTag, typename Geometry>
struct assign_inverse {};

template <typename Box>
struct assign_inverse<box_tag, Box>
    : detail::assign::assign_inverse_box_or_segment
{};

template <typename Segment>
struct assign_inverse<segment_tag, Segment>
    : detail::assign::assign_inverse_box_or_segment
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_ASSIGN_VALUES_HPP

/* assign_values.hpp
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
*/
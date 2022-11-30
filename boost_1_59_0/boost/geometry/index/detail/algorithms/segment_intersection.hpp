// Boost.Geometry Index
//
// n-dimensional box-segment intersection
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SEGMENT_INTERSECTION_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SEGMENT_INTERSECTION_HPP

#include <limits>
#include <type_traits>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

//template <typename Indexable, typename Point>
//struct default_relative_distance_type
//{
//    typedef typename select_most_precise<
//        typename select_most_precise<
//        typename coordinate_type<Indexable>::type,
//        typename coordinate_type<Point>::type
//        >::type,
//        float // TODO - use bigger type, calculated from the size of coordinate types
//    >::type type;
//
//
//    BOOST_GEOMETRY_STATIC_ASSERT((!std::is_unsigned<type>::value),
//        "Distance type can not be unsigned.", type);
//};

namespace dispatch {

template <typename Box, typename Point, size_t I>
struct box_segment_intersection_dim
{
    BOOST_STATIC_ASSERT(0 <= dimension<Box>::value);
    BOOST_STATIC_ASSERT(0 <= dimension<Point>::value);
    BOOST_STATIC_ASSERT(I < size_t(dimension<Box>::value));
    BOOST_STATIC_ASSERT(I < size_t(dimension<Point>::value));
    BOOST_STATIC_ASSERT(dimension<Point>::value == dimension<Box>::value);

    // WARNING! - RelativeDistance must be IEEE float for this to work

    template <typename RelativeDistance>
    static inline bool apply(Box const& b, Point const& p0, Point const& p1,
                             RelativeDistance & t_near, RelativeDistance & t_far)
    {
        RelativeDistance ray_d = geometry::get<I>(p1) - geometry::get<I>(p0);
        RelativeDistance tn = ( geometry::get<min_corner, I>(b) - geometry::get<I>(p0) ) / ray_d;
        RelativeDistance tf = ( geometry::get<max_corner, I>(b) - geometry::get<I>(p0) ) / ray_d;
        if ( tf < tn )
            ::std::swap(tn, tf);

        if ( t_near < tn )
            t_near = tn;
        if ( tf < t_far )
            t_far = tf;

        return 0 <= t_far && t_near <= t_far;
    }
};

template <typename Box, typename Point, size_t CurrentDimension>
struct box_segment_intersection
{
    BOOST_STATIC_ASSERT(0 < CurrentDimension);

    typedef box_segment_intersection_dim<Box, Point, CurrentDimension - 1> for_dim;

    template <typename RelativeDistance>
    static inline bool apply(Box const& b, Point const& p0, Point const& p1,
                             RelativeDistance & t_near, RelativeDistance & t_far)
    {
        return box_segment_intersection<Box, Point, CurrentDimension - 1>::apply(b, p0, p1, t_near, t_far)
            && for_dim::apply(b, p0, p1, t_near, t_far);
    }
};

template <typename Box, typename Point>
struct box_segment_intersection<Box, Point, 1>
{
    typedef box_segment_intersection_dim<Box, Point, 0> for_dim;

    template <typename RelativeDistance>
    static inline bool apply(Box const& b, Point const& p0, Point const& p1,
                             RelativeDistance & t_near, RelativeDistance & t_far)
    {
        return for_dim::apply(b, p0, p1, t_near, t_far);
    }
};

template <typename Indexable, typename Point, typename Tag>
struct segment_intersection
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Indexable type.",
        Indexable, Point, Tag);
};

template <typename Indexable, typename Point>
struct segment_intersection<Indexable, Point, point_tag>
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Segment-Point intersection unavailable.",
        Indexable, Point);
};

template <typename Indexable, typename Point>
struct segment_intersection<Indexable, Point, box_tag>
{
    typedef dispatch::box_segment_intersection<Indexable, Point, dimension<Indexable>::value> impl;

    template <typename RelativeDistance>
    static inline bool apply(Indexable const& b, Point const& p0, Point const& p1, RelativeDistance & relative_distance)
    {

// TODO: this ASSERT CHECK is wrong for user-defined CoordinateTypes!

        static const bool check = !std::is_integral<RelativeDistance>::value;
        BOOST_GEOMETRY_STATIC_ASSERT(check,
            "RelativeDistance must be a floating point type.",
            RelativeDistance);

        RelativeDistance t_near = -(::std::numeric_limits<RelativeDistance>::max)();
        RelativeDistance t_far = (::std::numeric_limits<RelativeDistance>::max)();

        return impl::apply(b, p0, p1, t_near, t_far) &&
               (t_near <= 1) &&
               ( relative_distance = 0 < t_near ? t_near : 0, true );
    }
};

} // namespace dispatch

template <typename Indexable, typename Point, typename RelativeDistance> inline
bool segment_intersection(Indexable const& b,
                          Point const& p0,
                          Point const& p1,
                          RelativeDistance & relative_distance)
{
    // TODO check Indexable and Point concepts

    return dispatch::segment_intersection<
            Indexable, Point,
            typename tag<Indexable>::type
        >::apply(b, p0, p1, relative_distance);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SEGMENT_INTERSECTION_HPP

/* segment_intersection.hpp
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
*/
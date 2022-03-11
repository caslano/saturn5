// Boost.Geometry Index
//
// n-dimensional box-segment intersection
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SEGMENT_INTERSECTION_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SEGMENT_INTERSECTION_HPP

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
//    BOOST_MPL_ASSERT_MSG((!::boost::is_unsigned<type>::value),
//        THIS_TYPE_SHOULDNT_BE_UNSIGNED, (type));
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
    BOOST_MPL_ASSERT_MSG((false), NOT_IMPLEMENTED_FOR_THIS_GEOMETRY, (segment_intersection));
};

template <typename Indexable, typename Point>
struct segment_intersection<Indexable, Point, point_tag>
{
    BOOST_MPL_ASSERT_MSG((false), SEGMENT_POINT_INTERSECTION_UNAVAILABLE, (segment_intersection));
};

template <typename Indexable, typename Point>
struct segment_intersection<Indexable, Point, box_tag>
{
    typedef dispatch::box_segment_intersection<Indexable, Point, dimension<Indexable>::value> impl;

    template <typename RelativeDistance>
    static inline bool apply(Indexable const& b, Point const& p0, Point const& p1, RelativeDistance & relative_distance)
    {

// TODO: this ASSERT CHECK is wrong for user-defined CoordinateTypes!

        static const bool check = !::boost::is_integral<RelativeDistance>::value;
        BOOST_MPL_ASSERT_MSG(check, RELATIVE_DISTANCE_MUST_BE_FLOATING_POINT_TYPE, (RelativeDistance));

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
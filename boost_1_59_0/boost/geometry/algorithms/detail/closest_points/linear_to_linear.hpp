// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_LINEAR_TO_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_LINEAR_TO_LINEAR_HPP

#include <boost/geometry/algorithms/detail/closest_points/range_to_geometry_rtree.hpp>
#include <boost/geometry/algorithms/detail/closest_points/utilities.hpp>

#include <boost/geometry/algorithms/num_points.hpp>
#include <boost/geometry/algorithms/num_segments.hpp>

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>
#include <boost/geometry/iterators/segment_iterator.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace closest_points
{


struct linear_to_linear
{
    template <typename Linear1, typename Linear2, typename Segment, typename Strategies>
    static inline void apply(Linear1 const& linear1,
                             Linear2 const& linear2,
                             Segment& shortest_seg,                       
                             Strategies const& strategies,
                             bool = false)
    {
        if (geometry::num_points(linear1) == 1)
        {
            dispatch::closest_points
                <
                    typename point_type<Linear1>::type,
                    Linear2
                >::apply(*points_begin(linear1), linear2, shortest_seg, strategies);
            return;
        }

        if (geometry::num_points(linear2) == 1)
        {
            dispatch::closest_points
                <
                    typename point_type<Linear2>::type,
                    Linear1
                >::apply(*points_begin(linear2), linear1, shortest_seg, strategies);
            detail::closest_points::swap_segment_points::apply(shortest_seg);
            return;
        }

        if (geometry::num_segments(linear1) < geometry::num_segments(linear2))
        {
            point_or_segment_range_to_geometry_rtree::apply(
                geometry::segments_begin(linear2),
                geometry::segments_end(linear2),
                linear1,
                shortest_seg,
                strategies);
            detail::closest_points::swap_segment_points::apply(shortest_seg);
            return;
        }

        point_or_segment_range_to_geometry_rtree::apply(
            geometry::segments_begin(linear1),
            geometry::segments_end(linear1),
            linear2,
            shortest_seg,
            strategies);
    }
};

struct segment_to_linear
{
    template <typename Segment, typename Linear, typename OutSegment, typename Strategies>
    static inline void apply(Segment const& segment,
                             Linear const& linear,
                             OutSegment& shortest_seg,                       
                             Strategies const& strategies,
                             bool = false)
    {
        using linestring_type = geometry::model::linestring
            <typename point_type<Segment>::type>;
        linestring_type linestring;
        convert(segment, linestring);
        linear_to_linear::apply(linestring, linear, shortest_seg, strategies);
    }
};

struct linear_to_segment
{
    template <typename Linear, typename Segment, typename OutSegment, typename Strategies>
    static inline void apply(Linear const& linear,
                             Segment const& segment,
                             OutSegment& shortest_seg,                       
                             Strategies const& strategies,
                             bool = false)
    {
        segment_to_linear::apply(segment, linear, shortest_seg, strategies);
        detail::closest_points::swap_segment_points::apply(shortest_seg);
    }
};

}} // namespace detail::closest_points
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Linear1, typename Linear2>
struct closest_points
    <
        Linear1, Linear2,
        linear_tag, linear_tag, 
        false
    > : detail::closest_points::linear_to_linear
{};

template <typename Segment, typename Linear>
struct closest_points
    <
        Segment, Linear, 
        segment_tag, linear_tag,
        false
    > : detail::closest_points::segment_to_linear
{};

template <typename Linear, typename Segment>
struct closest_points
    <
        Linear, Segment, 
        linear_tag, segment_tag,
        false
    > : detail::closest_points::linear_to_segment
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_LINEAR_TO_LINEAR_HPP

/* linear_to_linear.hpp
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
*/
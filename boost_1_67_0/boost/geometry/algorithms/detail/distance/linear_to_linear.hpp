// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>
#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/algorithms/num_points.hpp>
#include <boost/geometry/algorithms/num_segments.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/distance/range_to_geometry_rtree.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename Linear1, typename Linear2, typename Strategy>
struct linear_to_linear
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Linear1>::type,
            typename point_type<Linear2>::type
        >::type return_type;

    static inline return_type apply(Linear1 const& linear1,
                                    Linear2 const& linear2,
                                    Strategy const& strategy,
                                    bool = false)
    {
        if (geometry::num_points(linear1) == 1)
        {
            return dispatch::distance
                <
                    typename point_type<Linear1>::type,
                    Linear2,
                    Strategy
                >::apply(*points_begin(linear1), linear2, strategy);
        }

        if (geometry::num_points(linear2) == 1)
        {
            return dispatch::distance
                <
                    typename point_type<Linear2>::type,
                    Linear1,
                    Strategy
                >::apply(*points_begin(linear2), linear1, strategy);
        }

        if (geometry::num_segments(linear2) < geometry::num_segments(linear1))
        {
            return point_or_segment_range_to_geometry_rtree
                <
                    geometry::segment_iterator<Linear2 const>,
                    Linear1,
                    Strategy
                >::apply(geometry::segments_begin(linear2),
                         geometry::segments_end(linear2),
                         linear1,
                         strategy);

        }

        return point_or_segment_range_to_geometry_rtree
            <
                geometry::segment_iterator<Linear1 const>,
                Linear2,
                Strategy
            >::apply(geometry::segments_begin(linear1),
                     geometry::segments_end(linear1),
                     linear2,
                     strategy);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Linear1, typename Linear2, typename Strategy>
struct distance
    <
        Linear1, Linear2, Strategy,
        linear_tag, linear_tag, 
        strategy_tag_distance_point_segment, false
    > : detail::distance::linear_to_linear
        <
            Linear1, Linear2, Strategy
        >
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP

/* linear_to_linear.hpp
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
*/
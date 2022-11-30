// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP

#include <boost/geometry/algorithms/detail/distance/range_to_geometry_rtree.hpp>
#include <boost/geometry/algorithms/detail/distance/strategy_utils.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>
#include <boost/geometry/algorithms/num_points.hpp>
#include <boost/geometry/algorithms/num_segments.hpp>

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>
#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename Linear1, typename Linear2, typename Strategies>
struct linear_to_linear
{
    typedef distance::return_t<Linear1, Linear2, Strategies> return_type;

    static inline return_type apply(Linear1 const& linear1,
                                    Linear2 const& linear2,
                                    Strategies const& strategies,
                                    bool = false)
    {
        if (geometry::num_points(linear1) == 1)
        {
            return dispatch::distance
                <
                    typename point_type<Linear1>::type,
                    Linear2,
                    Strategies
                >::apply(*points_begin(linear1), linear2, strategies);
        }

        if (geometry::num_points(linear2) == 1)
        {
            return dispatch::distance
                <
                    typename point_type<Linear2>::type,
                    Linear1,
                    Strategies
                >::apply(*points_begin(linear2), linear1, strategies);
        }

        if (geometry::num_segments(linear2) < geometry::num_segments(linear1))
        {
            return point_or_segment_range_to_geometry_rtree
                <
                    geometry::segment_iterator<Linear2 const>,
                    Linear1,
                    Strategies
                >::apply(geometry::segments_begin(linear2),
                         geometry::segments_end(linear2),
                         linear1,
                         strategies);

        }

        return point_or_segment_range_to_geometry_rtree
            <
                geometry::segment_iterator<Linear1 const>,
                Linear2,
                Strategies
            >::apply(geometry::segments_begin(linear1),
                     geometry::segments_end(linear1),
                     linear2,
                     strategies);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Linear1, typename Linear2, typename Strategy, typename StrategyTag>
struct distance
    <
        Linear1, Linear2, Strategy,
        linear_tag, linear_tag, 
        StrategyTag, false
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
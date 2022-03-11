// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_SQUARE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_SQUARE_HPP

#include <cstddef>

#include <boost/range/value_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{

/*!
\brief Create a squared form buffer around a point
\ingroup strategies
\details This strategy can be used as PointStrategy for the buffer algorithm.
    It creates a square from each point, where the point lies in the center.
    It can be applied for points and multi_points, but also for a linestring (if it is degenerate,
    so consisting of only one point) and for polygons (if it is degenerate).
    This strategy is only applicable for Cartesian coordinate systems.

\qbk{
[heading Example]
[buffer_point_square]
[heading Output]
[$img/strategies/buffer_point_square.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_point_circle point_circle]
\* [link geometry.reference.strategies.strategy_buffer_geographic_point_circle geographic_point_circle]
}
 */
class point_square
{
    template
    <
        typename Point,
        typename DistanceType,
        typename OutputRange
    >
    inline void add_point(Point const& point,
                DistanceType const& distance,
                DistanceType const& x,
                DistanceType const& y,
                OutputRange& output_range) const
    {
        typename boost::range_value<OutputRange>::type p;
        set<0>(p, get<0>(point) + x * distance);
        set<1>(p, get<1>(point) + y * distance);
        output_range.push_back(p);
    }

    template
    <
        typename Point,
        typename DistanceType,
        typename OutputRange
    >
    inline void add_points(Point const& point,
                DistanceType const& distance,
                OutputRange& output_range) const
    {
        add_point(point, distance, -1.0, -1.0, output_range);
        add_point(point, distance, -1.0, +1.0, output_range);
        add_point(point, distance, +1.0, +1.0, output_range);
        add_point(point, distance, +1.0, -1.0, output_range);

        // Close it:
        output_range.push_back(output_range.front());
    }

public :

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Fills output_range with a square around point using distance_strategy
    template
    <
        typename Point,
        typename DistanceStrategy,
        typename OutputRange
    >
    inline void apply(Point const& point,
                DistanceStrategy const& distance_strategy,
                OutputRange& output_range) const
    {
        add_points(point, distance_strategy.apply(point, point,
                        strategy::buffer::buffer_side_left), output_range);
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS

};


}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_SQUARE_HPP

/* buffer_point_square.hpp
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
*/
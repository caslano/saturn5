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
        typename MultiplierType,
        typename OutputRange
    >
    inline void add_point(Point const& point,
                DistanceType const& distance,
                MultiplierType const& x,
                MultiplierType const& y,
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
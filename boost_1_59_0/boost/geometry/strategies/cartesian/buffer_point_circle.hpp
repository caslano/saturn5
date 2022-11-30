// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015, 2018.
// Modifications copyright (c) 2015, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_CIRCLE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_CIRCLE_HPP

#include <cstddef>

#include <boost/range/value_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/strategies/buffer.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{

/*!
\brief Create a circular buffer around a point
\ingroup strategies
\details This strategy can be used as PointStrategy for the buffer algorithm.
    It creates a circular buffer around a point. It can be applied
    for points and multi_points, but also for a linestring (if it is degenerate,
    so consisting of only one point) and for polygons (if it is degenerate).
    This strategy is only applicable for Cartesian coordinate systems.

\qbk{
[heading Example]
[buffer_point_circle]
[heading Output]
[$img/strategies/buffer_point_circle.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_point_square point_square]
\* [link geometry.reference.strategies.strategy_buffer_geographic_point_circle geographic_point_circle]
}
 */
class point_circle
{
public :
    //! \brief Constructs the strategy
    //! \param count number of points for the created circle (if count
    //! is smaller than 3, count is internally set to 3)
    explicit point_circle(std::size_t count = 90)
        : m_count((count < 3u) ? 3u : count)
    {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Fills output_range with a circle around point using distance_strategy
    template
    <
        typename Point,
        typename OutputRange,
        typename DistanceStrategy
    >
    inline void apply(Point const& point,
                DistanceStrategy const& distance_strategy,
                OutputRange& output_range) const
    {
        typedef typename boost::range_value<OutputRange>::type output_point_type;

        typedef typename geometry::select_most_precise
            <
                typename geometry::select_most_precise
                    <
                        typename geometry::coordinate_type<Point>::type,
                        typename geometry::coordinate_type<output_point_type>::type
                    >::type,
                double
            >::type promoted_type;

        promoted_type const buffer_distance = distance_strategy.apply(point, point,
                        strategy::buffer::buffer_side_left);

        promoted_type const two_pi = geometry::math::two_pi<promoted_type>();

        promoted_type const diff = two_pi / promoted_type(m_count);
        promoted_type a = 0;

        for (std::size_t i = 0; i < m_count; i++, a -= diff)
        {
            output_point_type p;
            set<0>(p, get<0>(point) + buffer_distance * cos(a));
            set<1>(p, get<1>(point) + buffer_distance * sin(a));
            output_range.push_back(p);
        }

        // Close it:
        output_range.push_back(output_range.front());
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS

private :
    std::size_t m_count;
};


}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_CIRCLE_HPP

/* buffer_point_circle.hpp
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
*/
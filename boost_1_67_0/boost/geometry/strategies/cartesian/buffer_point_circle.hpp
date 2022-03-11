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
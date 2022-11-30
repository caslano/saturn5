// Boost.Geometry

// Copyright (c) 2018-2019 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_BUFFER_POINT_CIRCLE_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_BUFFER_POINT_CIRCLE_HPP

#include <cstddef>

#include <boost/range/value_type.hpp>

#include <boost/geometry/srs/spheroid.hpp>
#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{

/*!
\brief Create a circular buffer around a point, on the Earth
\ingroup strategies
\details This strategy can be used as PointStrategy for the buffer algorithm.
    It creates a circular buffer around a point, on the Earth. It can be applied
    for points and multi_points.

\qbk{
[heading Example]
[buffer_geographic_point_circle]
[buffer_geographic_point_circle_output]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_point_circle point_circle]
\* [link geometry.reference.strategies.strategy_buffer_point_square point_square]
}
 */
template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic_point_circle
{
public :
    //! \brief Constructs the strategy
    //! \param count number of points for the created circle (if count
    //! is smaller than 3, count is internally set to 3)
    explicit geographic_point_circle(std::size_t count = 90)
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

        typedef typename select_calculation_type
            <
                Point, output_point_type,
                CalculationType
                //double
            >::type calculation_type;

        calculation_type const buffer_distance = distance_strategy.apply(point, point,
                        strategy::buffer::buffer_side_left);

        typedef typename FormulaPolicy::template direct
            <
                calculation_type, true, false, false, false
            > direct_t;

        calculation_type const two_pi = geometry::math::two_pi<calculation_type>();
        calculation_type const pi = geometry::math::pi<calculation_type>();

        calculation_type const diff = two_pi / calculation_type(m_count);
        // TODO: after calculation of some angles is corrected,
        // we can start at 0.0
        calculation_type angle = 0.001;

        for (std::size_t i = 0; i < m_count; i++, angle += diff)
        {
            if (angle > pi)
            {
                angle -= two_pi;
            }

            typename direct_t::result_type
                dir_r = direct_t::apply(get_as_radian<0>(point), get_as_radian<1>(point),
                                        buffer_distance, angle,
                                        m_spheroid);
            output_point_type p;
            set_from_radian<0>(p, dir_r.lon2);
            set_from_radian<1>(p, dir_r.lat2);
            output_range.push_back(p);
        }

        {
            // Close the range
            const output_point_type p = output_range.front();
            output_range.push_back(p);
        }
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS

private :
    std::size_t m_count;
    Spheroid m_spheroid;
};


}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_BUFFER_POINT_CIRCLE_HPP

/* buffer_point_circle.hpp
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
*/
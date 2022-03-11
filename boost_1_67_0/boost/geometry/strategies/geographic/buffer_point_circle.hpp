// Boost.Geometry

// Copyright (c) 2018-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_BUFFER_POINT_CIRCLE_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_BUFFER_POINT_CIRCLE_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/strategies/buffer.hpp>


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

        typedef typename select_most_precise
            <
                typename geometry::coordinate_type<Point>::type,
                typename geometry::coordinate_type<output_point_type>::type,
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
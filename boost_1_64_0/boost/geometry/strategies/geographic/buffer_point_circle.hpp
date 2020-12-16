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
FibjUZyCGWX+vncvb2A5R4hLhBPn2nZEIBFLLCK2EceIK0T57cxL+BMRxHxiE3GE4H4m9zxLxipxKBmr5G/rX1MyTsnfc8807zglNzl4utPgCCBiiXRiL1HyKfmUfEo+JZ/8n7/t/j9vKbg39/+3V7W9+y9YDu0pRH0ikahei3PDc7T5lXf/hccbp5pekeVQ5HdKBOR7958nepQzTeOGKxNd5bpeQ8IyLcT0Ihbbe9fKKe9mUb1f7ojOOwH7k5bDmrz5Nb3Sq+jvKcybV3m3iKrfQBWirKQZxnc9VGklGCaGxcRRyHecXrd8z/+PlG0xhKjJtvCR9Ho/ZHltXJ6OAIVezydNylnbTyEAV1SXfgrSl8Fb3nuRty9DafN2SFbde5hfWpvP2iw/I18+x8XE31FepV/CPcmrk7yLz0C4EaFEHfLq8bw1r5Y3w6gyKvdJggvJa6hOuUajN/knr6r7pM/p5KMe867Nnw8K7U7zIuWmlxdVPfMvK2ONk7AbLkGPWsQLyr0jv2HBIWEREeaDDm9PKfy+kVLPLNslKcW27SQP4XI/V9sfphl669zj+kbyuYNwJbYRDUz5XKfKp/llOtaccvwqtO+OKc0gJa+JSv1xIXhnjPR9IS3p++IieXyAtPl3ylf9PrDoctp3wzXkuw4vqvJpfvdlbIwhDgwJ/N+4IryfTY4ZecpVnfYlnbQbmcpIm3ZMXGS88vLNorwbTidtVT0apvMOvsb84aNNmxORIT65GO9im6NTH3IlvfayD7UiTPU2VJ0eB+T4yQZrhSjCuyTlnKWpu562uqvKx7Dy2vNCE9O+rM6HKQPmlSfY2IWvu055q9I9oZNuU9I9aCfdOMOUu0rXWscC7tem24x0L+qnKxvg7uq3dZ0zJe2aRAWiBtHCVOHWa9NOvMuytr73b51yblHnJbSCNi+tTPuaXl7usvyteXlWyYt6m1zXyUsb076nl5d7sE2s+XlePz8MZm5ZgLvkpzbRzrRv5svPvToGWvOzNV9++ljP+xXlPSSEG7GB6EB+0grOjyEuiteWFeE5iYLOd3vM0wyq/GyoqC2fTuTHuEGbn/j4CTEGanKcISEs6R5ss+12tlmnSto8dSFPa+3lSV4uSo7uKj877OTniE5+PMnPqXz5uVfnMsmP6n1vqvObvGPPl3AlehBetfi/lzT5kfNb4c+0SdtC1fZolq/t4aD8Hat63k3e+cc7Rfh3bIbdTfuYKT/q/sGRCQZDkeuwtL1oOkn+bO8+VR3/Aqpo2xo9SN9jkyZ9DsPtQsJjjNGGhMK3jZzzOYhp30F7UCfNnqTpYyfNaN4EGBc2sVjvvs2Xrupdhy2lLrYgvE1lbSfdmAj2kbgkQ0ox2jiSrlIPk9W/eZVyP+ikLQMf035qJy9Gg6FY7x7Wa3uPMf8/6ch539xnlTQP6qfJDhA+wXAX697cnAfTUiz1sob6GoBq22RK3oDyYP8l/GrhZr28sV0mGhM4D7KNip8/VZm4WL7YgXAlWhO9SbedfrqGFPN1iMLbn/KeT1WZeNr2wYj87e6LLvp106ibD1a7GHWhsDrZx1oWVS0zV5JtUJHoQx4y9PPAO3iT4sPjY01nEFOrvNj5yfte7Nyq2u2fUpO6qZ+2qVJBbEykwXSYDuHFpEl3lL61/AOrWb5YR9J3J/qy7hftpT+x6O/D1qt3B+2k57Qlf3p39ltLL81O1eU9dYQL0Um2r482zeiwRCnjIjzTLecX0tS+33qvpPkt4UZcIdbwL2maNNmYXDDkAkWh+1bhv+1kvSUPPq6WmUeQYAUcjqY8HNyqlwdpVxfhvd7S/tDkw0mdD+VcnyH5GEyilTAQA0z7+MuafPA=
*/
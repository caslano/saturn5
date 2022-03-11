// Boost.Geometry (aka GGL, Generic Geometry Library)
// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_SIDE_STRAIGHT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_SIDE_STRAIGHT_HPP

#include <cstddef>

#include <boost/math/special_functions/fpclassify.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/strategies/side.hpp>



namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{



/*!
\brief Let the buffer use straight sides along segments (the default)
\ingroup strategies
\details This strategy can be used as SideStrategy for the buffer algorithm.
    It is currently the only provided strategy for this purpose

\qbk{
[heading Example]
See the examples for other buffer strategies\, for example
[link geometry.reference.strategies.strategy_buffer_join_round join_round]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
}
 */
class side_straight
{
public :
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template
    <
        typename Point,
        typename OutputRange,
        typename DistanceStrategy
    >
    static inline result_code apply(
                Point const& input_p1, Point const& input_p2,
                buffer_side_selector side,
                DistanceStrategy const& distance,
                OutputRange& output_range)
    {
        typedef typename coordinate_type<Point>::type coordinate_type;
        typedef typename geometry::select_most_precise
        <
            coordinate_type,
            double
        >::type promoted_type;

        // Generate a block along (left or right of) the segment

        // Simulate a vector d (dx,dy)
        coordinate_type const dx = get<0>(input_p2) - get<0>(input_p1);
        coordinate_type const dy = get<1>(input_p2) - get<1>(input_p1);

        // For normalization [0,1] (=dot product d.d, sqrt)
        promoted_type const length = geometry::math::sqrt(dx * dx + dy * dy);

        if (! boost::math::isfinite(length))
        {
            // In case of coordinates differences of e.g. 1e300, length
            // will overflow and we should not generate output
#ifdef BOOST_GEOMETRY_DEBUG_BUFFER_WARN
            std::cout << "Error in length calculation for points "
                << geometry::wkt(input_p1) << " " << geometry::wkt(input_p2)
                << " length: " << length << std::endl;
#endif
            return result_error_numerical;
        }

        if (geometry::math::equals(length, 0))
        {
            // Coordinates are simplified and therefore most often not equal.
            // But if simplify is skipped, or for lines with two
            // equal points, length is 0 and we cannot generate output.
            return result_no_output;
        }

        promoted_type const d = distance.apply(input_p1, input_p2, side);

        // Generate the normalized perpendicular p, to the left (ccw)
        promoted_type const px = -dy / length;
        promoted_type const py = dx / length;

        if (geometry::math::equals(px, 0)
            && geometry::math::equals(py, 0))
        {
            // This basically should not occur - because of the checks above.
            // There are no unit tests triggering this condition
#ifdef BOOST_GEOMETRY_DEBUG_BUFFER_WARN
            std::cout << "Error in perpendicular calculation for points "
                << geometry::wkt(input_p1) << " " << geometry::wkt(input_p2)
                << " length: " << length
                << " distance: " << d
                << std::endl;
#endif
            return result_no_output;
        }

        output_range.resize(2);

        set<0>(output_range.front(), get<0>(input_p1) + px * d);
        set<1>(output_range.front(), get<1>(input_p1) + py * d);
        set<0>(output_range.back(), get<0>(input_p2) + px * d);
        set<1>(output_range.back(), get<1>(input_p2) + py * d);

        return result_normal;
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS
};


}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_SIDE_STRAIGHT_HPP

/* buffer_side_straight.hpp
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
*/
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

    // Returns true if the buffer distance is always the same
    static inline bool equidistant()
    {
        return true;
    }

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
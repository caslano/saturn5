// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_ROUND_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_ROUND_HPP

#include <algorithm>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/policies/compare.hpp>
#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_BUFFER_WARN
#include <iostream>
#include <boost/geometry/io/wkt/wkt.hpp>
#endif


namespace boost { namespace geometry
{


namespace strategy { namespace buffer
{

/*!
\brief Let the buffer create rounded corners
\ingroup strategies
\details This strategy can be used as JoinStrategy for the buffer algorithm.
    It creates a rounded corners around each convex vertex. It can be applied
    for (multi)linestrings and (multi)polygons.
    This strategy is only applicable for Cartesian coordinate systems.

\qbk{
[heading Example]
[buffer_join_round]
[heading Output]
[$img/strategies/buffer_join_round.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_join_miter join_miter]
}
 */
class join_round
{
public :

    //! \brief Constructs the strategy
    //! \param points_per_circle points which would be used for a full circle
    explicit inline join_round(std::size_t points_per_circle = 90)
        : m_points_per_circle(points_per_circle)
    {}

private :
    template
    <
        typename PromotedType,
        typename Point,
        typename DistanceType,
        typename RangeOut
    >
    inline void generate_points(Point const& vertex,
                Point const& perp1, Point const& perp2,
                DistanceType const& buffer_distance,
                RangeOut& range_out) const
    {
        PromotedType const dx1 = get<0>(perp1) - get<0>(vertex);
        PromotedType const dy1 = get<1>(perp1) - get<1>(vertex);
        PromotedType const dx2 = get<0>(perp2) - get<0>(vertex);
        PromotedType const dy2 = get<1>(perp2) - get<1>(vertex);

        PromotedType const two_pi = geometry::math::two_pi<PromotedType>();

        PromotedType const angle1 = atan2(dy1, dx1);
        PromotedType angle2 = atan2(dy2, dx2);
        while (angle2 > angle1)
        {
            angle2 -= two_pi;
        }
        PromotedType const angle_diff = angle1 - angle2;

        // Divide the angle into an integer amount of steps to make it
        // visually correct also for a low number of points / circle

        // If a full circle is divided into 3 parts (e.g. angle is 125),
        // the one point in between must still be generated
        // The calculation below:
        // - generates 1 point  in between for an angle of 125 based on 3 points
        // - generates 0 points in between for an angle of 90  based on 4 points

        std::size_t const n = (std::max)(static_cast<std::size_t>(
            ceil(m_points_per_circle * angle_diff / two_pi)), std::size_t(1));

        PromotedType const diff = angle_diff / static_cast<PromotedType>(n);
        PromotedType a = angle1 - diff;

        // Walk to n - 1 to avoid generating the last point
        for (std::size_t i = 0; i < n - 1; i++, a -= diff)
        {
            Point p;
            set<0>(p, get<0>(vertex) + buffer_distance * cos(a));
            set<1>(p, get<1>(vertex) + buffer_distance * sin(a));
            range_out.push_back(p);
        }
    }

public :


#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Fills output_range with a rounded shape around a vertex
    template <typename Point, typename DistanceType, typename RangeOut>
    inline bool apply(Point const& ip, Point const& vertex,
                Point const& perp1, Point const& perp2,
                DistanceType const& buffer_distance,
                RangeOut& range_out) const
    {
        typedef typename coordinate_type<Point>::type coordinate_type;
        typedef typename boost::range_value<RangeOut>::type output_point_type;

        typedef typename geometry::select_most_precise
            <
                typename geometry::select_most_precise
                    <
                        coordinate_type,
                        typename geometry::coordinate_type<output_point_type>::type
                    >::type,
                double
            >::type promoted_type;

        geometry::equal_to<Point> equals;
        if (equals(perp1, perp2))
        {
#ifdef BOOST_GEOMETRY_DEBUG_BUFFER_WARN
            std::cout << "Corner for equal points " << geometry::wkt(ip) << " " << geometry::wkt(perp1) << std::endl;
#endif
            return false;
        }

        // Generate 'vectors'
        coordinate_type vix = (get<0>(ip) - get<0>(vertex));
        coordinate_type viy = (get<1>(ip) - get<1>(vertex));

        promoted_type length_i = geometry::math::sqrt(vix * vix + viy * viy);
        DistanceType const bd = geometry::math::abs(buffer_distance);
        promoted_type prop = bd / length_i;

        Point bp;
        set<0>(bp, get<0>(vertex) + vix * prop);
        set<1>(bp, get<1>(vertex) + viy * prop);

        range_out.push_back(perp1);
        generate_points<promoted_type>(vertex, perp1, perp2, bd, range_out);
        range_out.push_back(perp2);
        return true;
    }

    template <typename NumericType>
    static inline NumericType max_distance(NumericType const& distance)
    {
        return distance;
    }

#endif // DOXYGEN_SHOULD_SKIP_THIS

private :
    std::size_t m_points_per_circle;
};


}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_ROUND_HPP

/* buffer_join_round.hpp
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
*/
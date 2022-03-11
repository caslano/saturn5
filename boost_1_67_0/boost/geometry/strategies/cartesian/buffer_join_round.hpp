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
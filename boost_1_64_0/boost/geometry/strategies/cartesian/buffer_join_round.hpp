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
OmWpOFjI9Ohs+BDVTOW/N6N8v1FP99n55hjE+fdb+WyvM9kT/f9bVj7b+stj8oCVjvKYbe/BTLxAT0KO2d/OxGfhwnJNrlMessqw8alCrj/2ZuDZ283DdhmzTjn/ETvfFrdH7Xwzbty/71j5cmzkvO8Knu0MjuB9z+CZ52/kWc7HiBcMhfQExf/7khYOV/D+Q3oeN+nm/l8ad35g8thikvYiD3SfiiUVapf9vWNMHUL2CVOWd/whhLnNJ01ZsWc/Hh6QY+YPJS+K/Py4H51opDp/aig+dspDiOv4kSrDjzVZdfzYwbfo4D4+LWRsZ4ZELPdJHrKnxOEcTv+JoItzRGJk5v48I+jO80VUX88KPmkS9p9TaXIFSbyfCh7Vl+z5QtfzgkfnkATtZ4Imz+FyHT83aM4zuL8QPNuZJaHrlwYvaZwj/ZWgOc8qUbxeUPikjtv5tUF3nkF6UeGxBU2QtRYq/28kL45hJhbG2eiNvF+MAe8lyRtIcNsvm7/lxnZOf0XQzfNN1DZelfQtiXiSDyasXfSjwpKRIJ07ec2Qwfld8UcHBxJMXA/zGP1W8C3z3O8ETcwr5qEAloX783uFzwtN+f5gp/NjrHG29Oax+KPCN4Ml5vg/qTzzQgdfe+PpSNCw/WcpZ56n4rpft9B1dvwbfVnw/mLnKfPxXwVv2DNWf1NkxIIxoodFn+H63zD5FbJ9ynF/v8IzQy+PYYkyHTBlAkA2RnK7byp0dO1AMLUVfw+yJyz71lsmX107cbtvqzy0vF4Yted/x5Qhh8w293cHL8V9etegO85gcP4/7Hwju+C/5+Qn0S/i/RTrf6r8gWTSVCDi+b6DbznSy2X+5ZRhfSTI2z/Vy78NmUz3Q8Q88YGQOehZNea35rHLyrlTxNOj8PVkMp6k8WaESZetjtvOctIDa+aXL8KfgMSfphTTaHiLGOeyFdkeOk+WY9LoCLFunMPPlTz7fQzyaaTJl6M5z5dn0nk34o2O9wMR91EOvtkope3RNhnTOeH3ISZfORIp8h5q8izXALKvHWbyh7xGGCNlHPcY6N0GCj+JVwDINUy+Qaf7W8E+/C/iX6DyesR6rdCkOe9TyHcaSJkh7lGMM/nGCMyvktnYyBYu8r0Gphxd01CfIt8n2PhiABR5j8jI4wsNHo+JJt9yVvlIhS5e+GHt50UOvvwLwMKno0y+WQPU/iaZPJmJ04+WdLpH4SP5yTZ6r3xvgY0+kKKrQeIXO/ii9JI/1eRbwi7HzxLBt53nFD4dY/Dor+SSzmMl3XmOk/OnSb793gTZnC749vObPO8MB4/f/oumKU4zrXxWl5w+S6Fv5m1etOvZKp3a9RxBY9dMbKURQtfqVdZkXN9cRQbvhQlDhNNLiY6bAN16D44Jkp0yg84vDTjtOElLBdhfHeblKzdoTM4c14z3Cxh8asoU80pBF2dVzUmLVSVfh80TfHadx21Xid9sfNooYzFf0GR5OG2BoLHxwPBhoUEzVi48btVOeiDY3Z3UB9lXcU2+yCkj7fG6Xyz5rEGZ1wk87/EWnvM6Y4ng0ziirLCoXZ0g+LIq4cNASq65TjR46XIaFHmZTpL0jGsnkXepIsMbF9FrTLq4xiN6rUIX6ztBrzPo1jVSvUkX15Cyu1G5vAbfcv6V11+DwoNn3E6jQTMOjnI9TQbdslbiPjQbvMxromUmn65rDCfFWX+DP+S5UO5biyLH365E9dBq0Idey/gMmeHWMsKfNkN2yGc63J92U07WOo/rCoXeQ/eMOgRtqGcsPMadpgxvEuISS8TQb/BsaxbirxR8x3MXeY9pleB/qOcirGyrDXnrewPWCPpQz0O4zFohM9SzEK5/nZQ=
*/
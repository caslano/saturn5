// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_ROUND_BY_DIVIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_ROUND_BY_DIVIDE_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/policies/compare.hpp>
#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_BUFFER_WARN
#include <boost/geometry/io/wkt/wkt.hpp>
#endif

namespace boost { namespace geometry
{


namespace strategy { namespace buffer
{


class join_round_by_divide
{
public :

    inline join_round_by_divide(std::size_t max_level = 4)
        : m_max_level(max_level)
    {}

    template
    <
        typename PromotedType,
        typename Point,
        typename DistanceType,
        typename RangeOut
    >
    inline void mid_points(Point const& vertex,
                Point const& p1, Point const& p2,
                DistanceType const& buffer_distance,
                RangeOut& range_out,
                std::size_t level = 1) const
    {
        typedef typename coordinate_type<Point>::type coordinate_type;

        // Generate 'vectors'
        coordinate_type const vp1_x = get<0>(p1) - get<0>(vertex);
        coordinate_type const vp1_y = get<1>(p1) - get<1>(vertex);

        coordinate_type const vp2_x = (get<0>(p2) - get<0>(vertex));
        coordinate_type const vp2_y = (get<1>(p2) - get<1>(vertex));

        // Average them to generate vector in between
        coordinate_type const two = 2;
        coordinate_type const v_x = (vp1_x + vp2_x) / two;
        coordinate_type const v_y = (vp1_y + vp2_y) / two;

        PromotedType const length2 = geometry::math::sqrt(v_x * v_x + v_y * v_y);

        PromotedType prop = buffer_distance / length2;

        Point mid_point;
        set<0>(mid_point, get<0>(vertex) + v_x * prop);
        set<1>(mid_point, get<1>(vertex) + v_y * prop);

        if (level < m_max_level)
        {
            mid_points<PromotedType>(vertex, p1, mid_point, buffer_distance, range_out, level + 1);
        }
        range_out.push_back(mid_point);
        if (level < m_max_level)
        {
            mid_points<PromotedType>(vertex, mid_point, p2, buffer_distance, range_out, level + 1);
        }
    }

    template <typename Point, typename DistanceType, typename RangeOut>
    inline bool apply(Point const& ip, Point const& vertex,
                Point const& perp1, Point const& perp2,
                DistanceType const& buffer_distance,
                RangeOut& range_out) const
    {
        typedef typename coordinate_type<Point>::type coordinate_type;

        typedef typename geometry::select_most_precise
            <
                coordinate_type,
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
        coordinate_type const vix = (get<0>(ip) - get<0>(vertex));
        coordinate_type const viy = (get<1>(ip) - get<1>(vertex));

        promoted_type const length_i = geometry::math::sqrt(vix * vix + viy * viy);

        promoted_type const bd = geometry::math::abs(buffer_distance);
        promoted_type prop = bd / length_i;

        Point bp;
        set<0>(bp, get<0>(vertex) + vix * prop);
        set<1>(bp, get<1>(vertex) + viy * prop);

        range_out.push_back(perp1);

        if (m_max_level > 1)
        {
            mid_points<promoted_type>(vertex, perp1, bp, bd, range_out);
            range_out.push_back(bp);
            mid_points<promoted_type>(vertex, bp, perp2, bd, range_out);
        }
        else if (m_max_level == 1)
        {
            range_out.push_back(bp);
        }

        range_out.push_back(perp2);
        return true;
    }

    template <typename NumericType>
    static inline NumericType max_distance(NumericType const& distance)
    {
        return distance;
    }

private :
    std::size_t m_max_level;
};


}} // namespace strategy::buffer


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_JOIN_ROUND_BY_DIVIDE_HPP

/* buffer_join_round_by_divide.hpp
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
*/
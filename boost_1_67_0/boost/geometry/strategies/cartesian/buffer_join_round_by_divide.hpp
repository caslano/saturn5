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
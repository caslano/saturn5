// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_END_ROUND_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_END_ROUND_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/strategies/tags.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

#include <boost/geometry/strategies/buffer.hpp>


#include <boost/geometry/io/wkt/wkt.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace buffer
{


/*!
\brief Let the buffer create rounded ends
\ingroup strategies
\details This strategy can be used as EndStrategy for the buffer algorithm.
    It creates a rounded end for each linestring-end. It can be applied
    for (multi)linestrings. Also it is applicable for spikes in (multi)polygons.
    This strategy is only applicable for Cartesian coordinate systems.

\qbk{
[heading Example]
[buffer_end_round]
[heading Output]
[$img/strategies/buffer_end_round.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_end_flat end_flat]
}
 */
class end_round
{
private :
    std::size_t m_points_per_circle;

    template
    <
        typename Point,
        typename PromotedType,
        typename DistanceType,
        typename RangeOut
    >
    inline void generate_points(Point const& point,
                PromotedType alpha, // by value
                DistanceType const& buffer_distance,
                RangeOut& range_out) const
    {
        PromotedType const two_pi = geometry::math::two_pi<PromotedType>();

        std::size_t point_buffer_count = m_points_per_circle;

        PromotedType const diff = two_pi / PromotedType(point_buffer_count);

        // For half circle:
        point_buffer_count /= 2;
        point_buffer_count++;

        for (std::size_t i = 0; i < point_buffer_count; i++, alpha -= diff)
        {
            typename boost::range_value<RangeOut>::type p;
            set<0>(p, get<0>(point) + buffer_distance * cos(alpha));
            set<1>(p, get<1>(point) + buffer_distance * sin(alpha));
            range_out.push_back(p);
        }
    }

    template <typename T, typename P1, typename P2>
    static inline T calculate_angle(P1 const& from_point, P2 const& to_point)
    {
        typedef P1 vector_type;
        vector_type v = from_point;
        geometry::subtract_point(v, to_point);
        return atan2(geometry::get<1>(v), geometry::get<0>(v));
    }

public :

    //! \brief Constructs the strategy
    //! \param points_per_circle points which would be used for a full circle
    //! (if points_per_circle is smaller than 4, it is internally set to 4)
    explicit inline end_round(std::size_t points_per_circle = 90)
        : m_points_per_circle((points_per_circle < 4u) ? 4u : points_per_circle)
    {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS

    //! Fills output_range with a flat end
    template <typename Point, typename RangeOut, typename DistanceStrategy>
    inline void apply(Point const& penultimate_point,
                Point const& perp_left_point,
                Point const& ultimate_point,
                Point const& perp_right_point,
                buffer_side_selector side,
                DistanceStrategy const& distance,
                RangeOut& range_out) const
    {
        boost::ignore_unused(perp_left_point);
        typedef typename coordinate_type<Point>::type coordinate_type;

        typedef typename geometry::select_most_precise
        <
            coordinate_type,
            double
        >::type promoted_type;

        promoted_type const dist_left = distance.apply(penultimate_point, ultimate_point, buffer_side_left);
        promoted_type const dist_right = distance.apply(penultimate_point, ultimate_point, buffer_side_right);
        promoted_type const alpha
                = calculate_angle<promoted_type>(penultimate_point, ultimate_point)
                    - geometry::math::half_pi<promoted_type>();

        if (geometry::math::equals(dist_left, dist_right))
        {
            generate_points(ultimate_point, alpha, dist_left, range_out);
        }
        else
        {
            static promoted_type const two = 2.0;
            promoted_type const dist_average = (dist_left + dist_right) / two;
            promoted_type const dist_half
                    = (side == buffer_side_right
                    ? (dist_right - dist_left)
                    : (dist_left - dist_right)) / two;

            Point shifted_point;
            set<0>(shifted_point, get<0>(ultimate_point) + dist_half * cos(alpha));
            set<1>(shifted_point, get<1>(ultimate_point) + dist_half * sin(alpha));
            generate_points(shifted_point, alpha, dist_average, range_out);
        }

        if (m_points_per_circle % 2 == 1)
        {
            // For a half circle, if the number of points is not even,
            // we should insert the end point too, to generate a full cap
            range_out.push_back(perp_right_point);
        }
    }

    template <typename NumericType>
    static inline NumericType max_distance(NumericType const& distance)
    {
        return distance;
    }

    //! Returns the piece_type (flat end)
    static inline piece_type get_piece_type()
    {
        return buffered_round_end;
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS
};


}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_END_ROUND_HPP

/* buffer_end_round.hpp
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
*/
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
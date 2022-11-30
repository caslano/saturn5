// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2020 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_TURN_IN_RING_WINDING_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_TURN_IN_RING_WINDING_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/config.hpp>
#include <boost/geometry/algorithms/detail/make/make.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{

#ifndef DOXYGEN_NO_DETAIL

enum place_on_ring_type
{
    // +----offsetted----> (offsetted is considered as outside)
    // |                 |
    // |                 |
    // left              right (first point outside, rest inside)
    // |                 |
    // |                 |
    // <-----original----+ (original is considered as inside)
    place_on_ring_offsetted,
    place_on_ring_original,
    place_on_ring_to_offsetted,
    place_on_ring_from_offsetted,
};

template <typename CalculationType>
class turn_in_ring_winding
{

    // Implements the winding rule.
    // Basic calculations (on a clockwise ring of 5 segments)
    // (as everywhere in BG, -1 = right, 0 = on segment, +1 = left)
    // +--------2--------+  // P : For 1/3, nothing happens, it returns
    // |                 |  //     For 2, side is right (-1), multiplier=2, -2
    // |        P        |  //     For 4, side is right (-1), multiplier=1, -1
    // 1                 3  //     For 5, side is right (-1), multiplier=1, -1, total -4
    // |             Q   |  // Q : For 2: -2, for 4: -2, total -4
    // |                 |  // R : For 2: -2, for 5: +2, total 0
    // +----5---*----4---+  // S : For 2: -1, 3: nothing, 4: +1, total 0
    //
    //     R             S
    //


public:

    struct counter
    {
        inline counter()
            : m_count(0)
            , m_min_distance(0)
            , m_close_to_offset(false)
        {}

        //! Returns -1 for outside, 1 for inside
        inline int code() const
        {
            return m_count == 0 ? -1 : 1;
        }

        //! Counter, is increased if point is left of a segment (outside),
        //! and decreased if point is right of a segment (inside)
        int m_count;

        //! Indicate an indication of distance. It is always set, unless
        //! the point is located on the border-part of the original.
        //! It is not guaranteed to be the minimum distance, because it is only
        //! calculated for a selection of the offsetted ring.
        CalculationType m_min_distance;
        bool m_close_to_offset;
    };

    typedef counter state_type;

    template <typename Point, typename PointOfSegment>
    static inline bool in_vertical_range(Point const& point,
                             PointOfSegment const& s1,
                             PointOfSegment const& s2)
    {
        CalculationType const py = get<1>(point);
        CalculationType const s1y = get<1>(s1);
        CalculationType const s2y = get<1>(s2);

        return (s1y >= py && s2y <= py)
            || (s2y >= py && s1y <= py);
    }

    template <typename Dm, typename Point, typename PointOfSegment>
    static inline void apply_on_boundary(Point const& point,
                             PointOfSegment const& s1,
                             PointOfSegment const& s2,
                             place_on_ring_type place_on_ring,
                             counter& the_state)
    {
        if (place_on_ring == place_on_ring_offsetted)
        {
            // Consider the point as "outside"
            the_state.m_count = 0;
            the_state.m_close_to_offset = true;
            the_state.m_min_distance = 0;
        }
        else if (place_on_ring == place_on_ring_to_offsetted
            || place_on_ring == place_on_ring_from_offsetted)
        {
            // Check distance from "point" to either s1 or s2
            // on a line perpendicular to s1-s2
            typedef model::infinite_line<CalculationType> line_type;

            line_type const line
                    = detail::make::make_perpendicular_line<CalculationType>(s1, s2,
                    place_on_ring == place_on_ring_to_offsetted ? s2 : s1);

            Dm perp;
            perp.measure = arithmetic::side_value(line, point);

            // If it is to the utmost point s1 or s2, it is "outside"
            the_state.m_count = perp.is_zero() ? 0 : 1;
            the_state.m_close_to_offset = true;
            the_state.m_min_distance = geometry::math::abs(perp.measure);
        }
        else
        {
            // It is on the border, the part of the original
            // Consider it as "inside".
            the_state.m_count = 1;
        }
    }

    template <typename Dm, typename Point, typename PointOfSegment>
    static inline bool apply(Point const& point,
                             PointOfSegment const& s1,
                             PointOfSegment const& s2,
                             Dm const& dm,
                             place_on_ring_type place_on_ring,
                             counter& the_state)
    {
        CalculationType const px = get<0>(point);
        CalculationType const s1x = get<0>(s1);
        CalculationType const s2x = get<0>(s2);

        bool const in_horizontal_range
                 = (s1x >= px && s2x <= px)
                || (s2x >= px && s1x <= px);

        bool const vertical = s1x == s2x;
        bool const measured_on_boundary = dm.is_zero();

        if (measured_on_boundary
            && (in_horizontal_range
                || (vertical && in_vertical_range(point, s1, s2))))
        {
            apply_on_boundary<Dm>(point, s1, s2, place_on_ring, the_state);
            // Indicate that no further processing is necessary.
            return false;
        }

        bool const is_on_right_side = dm.is_negative();

        if (place_on_ring == place_on_ring_offsetted
            && is_on_right_side
            && (! the_state.m_close_to_offset
                || -dm.measure < the_state.m_min_distance))
        {
            // This part of the ring was the offsetted part,
            // keep track of the distance WITHIN the ring
            // with respect to the offsetted part
            // NOTE: this is also done if it is NOT in the horizontal range.
            the_state.m_min_distance = -dm.measure;
            the_state.m_close_to_offset = true;
        }

        if (in_horizontal_range)
        {
            // Use only absolute comparisons, because the ring is continuous -
            // what was missed is there earlier or later, and turns should
            // not be counted twice (which can happen if an epsilon is used).
            bool const eq1 = s1x == px;
            bool const eq2 = s2x == px;

            // Account for  1 or  2 for left side (outside)
            //     and for -1 or -2 for right side (inside)
            int const side = is_on_right_side ? -1 : 1;
            int const multiplier = eq1 || eq2 ? 1 : 2;

            the_state.m_count += side * multiplier;
        }

        return true;
    }
};

#endif // DOXYGEN_NO_DETAIL

}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_TURN_IN_RING_WINDING_HPP


/* turn_in_ring_winding.hpp
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
*/
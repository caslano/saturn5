// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2020-2021 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2020-2022.
// Modifications copyright (c) 2020-2022, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_PIECE_BORDER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_PIECE_BORDER_HPP


#include <boost/array.hpp>
#include <boost/core/addressof.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/config.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/comparable_distance.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/detail/buffer/buffer_policies.hpp>
#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>
#include <boost/geometry/strategies/cartesian/turn_in_ring_winding.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/segment.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{
template <typename It, typename T, typename Compare>
inline bool get_range_around(It begin, It end, T const& value, Compare const& compare, It& lower, It& upper)
{
    lower = end;
    upper = end;

    // Get first element not smaller than value
    if (begin == end)
    {
        return false;
    }
    if (compare(value, *begin))
    {
        // The value is smaller than the first item, therefore not in range
        return false;
    }
    // *(begin + std::distance(begin, end) - 1))
    if (compare(*(end - 1), value))
    {
        // The last item is larger than the value, therefore not in range
        return false;
    }

    // Assign the iterators.
    // lower >= begin and lower < end
    // upper > lower and upper <= end
    // lower_bound points to first element NOT LESS than value - but because
    // we want the first value LESS than value, we decrease it
    lower = std::lower_bound(begin, end, value, compare);
    // upper_bound points to first element of which value is LESS
    upper = std::upper_bound(begin, end, value, compare);

    if (lower != begin)
    {
        --lower;
    }
    if (upper != end)
    {
        ++upper;
    }
    return true;
}

}


namespace detail { namespace buffer
{

//! Contains the border of the piece, consisting of 4 parts:
//! 1: the part of the offsetted ring (referenced, not copied)
//! 2: the part of the original (one or two points)
//! 3: the left part (from original to offsetted)
//! 4: the right part (from offsetted to original)
//! Besides that, it contains some properties of the piece(border);
//!   - convexity
//!   - envelope
//!   - monotonicity of the offsetted ring
//!   - min/max radius of a point buffer
//!   - if it is a "reversed" piece (linear features with partly negative buffers)
template <typename Ring, typename Point>
struct piece_border
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;
    typedef typename default_comparable_distance_result<Point>::type radius_type;
    typedef typename geometry::strategy::buffer::turn_in_ring_winding<coordinate_type>::state_type state_type;

    bool m_reversed;

    // Points from the offsetted ring. They are not copied, this structure
    // refers to those points
    Ring const* m_ring;
    std::size_t m_begin;
    std::size_t m_end;

    // Points from the original (one or two, depending on piece shape)
    // Note, if there are 2 points, they are REVERSED w.r.t. the original
    // Therefore here we can walk in its order.
    boost::array<Point, 2> m_originals;
    std::size_t m_original_size;

    geometry::model::box<Point> m_envelope;
    bool m_has_envelope;

    // True if piece is determined as "convex"
    bool m_is_convex;

    // True if offsetted part is monotonically changing in x-direction
    bool m_is_monotonic_increasing;
    bool m_is_monotonic_decreasing;

    radius_type m_min_comparable_radius;
    radius_type m_max_comparable_radius;

    piece_border()
        : m_reversed(false)
        , m_ring(NULL)
        , m_begin(0)
        , m_end(0)
        , m_original_size(0)
        , m_has_envelope(false)
        , m_is_convex(false)
        , m_is_monotonic_increasing(false)
        , m_is_monotonic_decreasing(false)
        , m_min_comparable_radius(0)
        , m_max_comparable_radius(0)
    {
    }

    // Only used for debugging (SVG)
    Ring get_full_ring() const
    {
        Ring result;
        if (ring_or_original_empty())
        {
            return result;
        }
        std::copy(m_ring->begin() + m_begin,
                  m_ring->begin() + m_end,
                  std::back_inserter(result));
        std::copy(m_originals.begin(),
                  m_originals.begin() + m_original_size,
                  std::back_inserter(result));
        // Add the closing point
        result.push_back(*(m_ring->begin() + m_begin));

        return result;
    }

    template <typename Strategy>
    void get_properties_of_border(bool is_point_buffer, Point const& center,
                                  Strategy const& strategy)
    {
        m_has_envelope = calculate_envelope(m_envelope, strategy);
        if (m_has_envelope)
        {
            // Take roundings into account, enlarge box
            geometry::detail::expand_by_epsilon(m_envelope);
        }
        if (! ring_or_original_empty() && is_point_buffer)
        {
            // Determine min/max radius
            calculate_radii(center, m_ring->begin() + m_begin, m_ring->begin() + m_end);
        }
    }

    template <typename Strategy>
    void get_properties_of_offsetted_ring_part(Strategy const& strategy)
    {
        if (! ring_or_original_empty())
        {
            m_is_convex = is_convex(strategy);
            check_monotonicity(m_ring->begin() + m_begin, m_ring->begin() + m_end);
        }
    }

    void set_offsetted(Ring const& ring, std::size_t begin, std::size_t end)
    {
        BOOST_GEOMETRY_ASSERT(begin <= end);
        BOOST_GEOMETRY_ASSERT(begin < boost::size(ring));
        BOOST_GEOMETRY_ASSERT(end <= boost::size(ring));

        m_ring = boost::addressof(ring);
        m_begin = begin;
        m_end = end;
    }

    void add_original_point(Point const& point)
    {
        BOOST_GEOMETRY_ASSERT(m_original_size < 2);
        m_originals[m_original_size++] = point;
    }

    template <typename Box, typename Strategy>
    bool calculate_envelope(Box& envelope, Strategy const& strategy) const
    {
        geometry::assign_inverse(envelope);
        if (ring_or_original_empty())
        {
            return false;
        }
        expand_envelope(envelope, m_ring->begin() + m_begin, m_ring->begin() + m_end, strategy);
        expand_envelope(envelope, m_originals.begin(), m_originals.begin() + m_original_size, strategy);
        return true;
    }


    // Whatever the return value, the state should be checked.
    template <typename TurnPoint, typename UmbrellaStrategy, typename State>
    bool point_on_piece(TurnPoint const& point,
                        UmbrellaStrategy const& umbrella_strategy,
                        bool one_sided, bool is_linear_end_point,
                        State& state) const
    {
        if (ring_or_original_empty())
        {
            return false;
        }

        // Walk over the different parts of the ring, in clockwise order
        // For performance reasons: start with the helper part (one segment)
        // then the original part (one segment, if any), then the other helper
        // part (one segment), and only then the offsetted part
        // (probably more segments, check monotonicity)
        geometry::strategy::buffer::turn_in_ring_winding<coordinate_type> tir;

        Point const offsetted_front = *(m_ring->begin() + m_begin);
        Point const offsetted_back = *(m_ring->begin() + m_end - 1);

        // For onesided buffers, or turns colocated with linear end points,
        // the place on the ring is changed to offsetted (because of colocation)
        geometry::strategy::buffer::place_on_ring_type const por_original
            = adapted_place_on_ring(geometry::strategy::buffer::place_on_ring_original,
                                    one_sided, is_linear_end_point);
        geometry::strategy::buffer::place_on_ring_type const por_from_offsetted
            = adapted_place_on_ring(geometry::strategy::buffer::place_on_ring_from_offsetted,
                                    one_sided, is_linear_end_point);
        geometry::strategy::buffer::place_on_ring_type const por_to_offsetted
            = adapted_place_on_ring(geometry::strategy::buffer::place_on_ring_to_offsetted,
                                    one_sided, is_linear_end_point);

        bool continue_processing = true;
        if (m_original_size == 1)
        {
            // One point. Walk from last offsetted to point, and from point to first offsetted
            continue_processing = step(point, offsetted_back, m_originals[0],
                                       tir, umbrella_strategy, por_from_offsetted, state)
                               && step(point, m_originals[0], offsetted_front,
                                       tir, umbrella_strategy, por_to_offsetted, state);
        }
        else if (m_original_size == 2)
        {
            // Two original points. Walk from last offsetted point to first original point,
            // then along original, then from second oginal to first offsetted point
            continue_processing = step(point, offsetted_back, m_originals[0],
                                       tir, umbrella_strategy, por_from_offsetted, state)
                               && step(point, m_originals[0], m_originals[1],
                                       tir, umbrella_strategy, por_original, state)
                               && step(point, m_originals[1], offsetted_front,
                                       tir, umbrella_strategy, por_to_offsetted, state);
        }

        if (continue_processing)
        {
            // Check the offsetted ring (in rounded joins, these might be
            // several segments)
            walk_offsetted(point, m_ring->begin() + m_begin, m_ring->begin() + m_end,
                           tir, umbrella_strategy, state);
        }

        return true;
    }

    //! Returns true if empty (no ring, or no points, or no original)
    bool ring_or_original_empty() const
    {
        return m_ring == NULL || m_begin >= m_end || m_original_size == 0;
    }

private :

    static geometry::strategy::buffer::place_on_ring_type
        adapted_place_on_ring(geometry::strategy::buffer::place_on_ring_type target,
                              bool one_sided, bool is_linear_end_point)
    {
        return one_sided || is_linear_end_point
               ? geometry::strategy::buffer::place_on_ring_offsetted
               : target;
    }

    template
    <
        typename TurnPoint, typename Iterator,
        typename TiRStrategy, typename UmbrellaStrategy,
        typename State
    >
    bool walk_offsetted(TurnPoint const& point, Iterator begin, Iterator end,
                        TiRStrategy const & strategy, UmbrellaStrategy const& umbrella_strategy,
                        State& state) const
    {
        Iterator it = begin;
        Iterator beyond = end;

        // Move iterators if the offsetted ring is monotonic increasing or decreasing
        if (m_is_monotonic_increasing)
        {
            if (! get_range_around(begin, end, point, geometry::less<Point, 0>(), it, beyond))
            {
                return true;
            }
        }
        else if (m_is_monotonic_decreasing)
        {
            if (! get_range_around(begin, end, point, geometry::greater<Point, 0>(), it, beyond))
            {
                return true;
            }
        }

        for (Iterator previous = it++ ; it != beyond ; ++previous, ++it )
        {
            if (! step(point, *previous, *it, strategy, umbrella_strategy,
                       geometry::strategy::buffer::place_on_ring_offsetted, state))
            {
                return false;
            }
        }
        return true;
    }

    template <typename TurnPoint, typename TiRStrategy, typename UmbrellaStrategy, typename State>
    bool step(TurnPoint const& point, Point const& p1, Point const& p2,
              TiRStrategy const& strategy, UmbrellaStrategy const& umbrella_strategy,
              geometry::strategy::buffer::place_on_ring_type place_on_ring, State& state) const
    {
        // A step between original/offsetted ring is always convex
        // (unless the join strategy generates points left of it -
        //  future: convexity might be added to the buffer-join-strategy)
        // Therefore, if the state count > 0, it means the point is left of it,
        // and because it is convex, we can stop

        auto const dm = geometry::detail::get_distance_measure(point, p1, p2, umbrella_strategy);
        if (m_is_convex && dm.measure > 0)
        {
            // The point is left of this segment of a convex piece
            state.m_count = 0;
            return false;
        }
        // Call strategy, and if it is on the border, return false
        // to stop further processing.
        return strategy.apply(point, p1, p2, dm, place_on_ring, state);
    }

    template <typename It, typename Box, typename Strategy>
    void expand_envelope(Box& envelope, It begin, It end, Strategy const& strategy) const
    {
        for (It it = begin; it != end; ++it)
        {
            geometry::expand(envelope, *it, strategy);
        }
    }

    template <typename Strategy>
    bool is_convex(Strategy const& strategy) const
    {
        if (ring_or_original_empty())
        {
            // Convexity is undetermined, and for this case it does not matter,
            // because it is only used for optimization in point_on_piece,
            // but that is not called if the piece border is not valid
            return false;
        }

        if (m_end - m_begin <= 2)
        {
            // The offsetted ring part of this piece has only two points.
            // If this is true, and the original ring part has only one point,
            // a triangle and it is convex. If the original ring part has two
            // points, it is a rectangle and theoretically could be concave,
            // but because of the way the buffer is generated, that is never
            // the case.
            return true;
        }

        // The offsetted ring part of thie piece has at least three points
        // (this is often the case in a piece marked as "join")

        // We can assume all points of the offset ring are different, and also
        // that all points on the original are different, and that the offsetted
        // ring is different from the original(s)
        Point const offsetted_front = *(m_ring->begin() + m_begin);
        Point const offsetted_second = *(m_ring->begin() + m_begin + 1);

        // These two points will be reassigned in every is_convex call
        Point previous = offsetted_front;
        Point current = offsetted_second;

        // Verify the offsetted range (from the second point on), the original,
        // and loop through the first two points of the offsetted range
        bool const result = is_convex(previous, current, m_ring->begin() + m_begin + 2, m_ring->begin() + m_end, strategy)
            && is_convex(previous, current, m_originals.begin(), m_originals.begin() + m_original_size, strategy)
            && is_convex(previous, current, offsetted_front, strategy)
            && is_convex(previous, current, offsetted_second, strategy);

        return result;
    }

    template <typename It, typename Strategy>
    bool is_convex(Point& previous, Point& current, It begin, It end, Strategy const& strategy) const
    {
        for (It it = begin; it != end; ++it)
        {
            if (! is_convex(previous, current, *it, strategy))
            {
                return false;
            }
        }
        return true;
    }

    template <typename Strategy>
    bool is_convex(Point& previous, Point& current, Point const& next, Strategy const& strategy) const
    {
        int const side = strategy.side().apply(previous, current, next);
        if (side == 1)
        {
            // Next is on the left side of clockwise ring: piece is not convex
            return false;
        }
        if (! equals::equals_point_point(current, next, strategy))
        {
            previous = current;
            current = next;
        }
        return true;
    }

    template <int Direction>
    inline void step_for_monotonicity(Point const& current, Point const& next)
    {
        if (geometry::get<Direction>(current) >= geometry::get<Direction>(next))
        {
            m_is_monotonic_increasing = false;
        }
        if (geometry::get<Direction>(current) <= geometry::get<Direction>(next))
        {
            m_is_monotonic_decreasing = false;
        }
    }

    template <typename It>
    void check_monotonicity(It begin, It end)
    {
        m_is_monotonic_increasing = true;
        m_is_monotonic_decreasing = true;

        if (begin == end || begin + 1 == end)
        {
            return;
        }

        It it = begin;
        for (It previous = it++; it != end; ++previous, ++it)
        {
            step_for_monotonicity<0>(*previous, *it);
        }
    }

    template <typename It>
    inline void calculate_radii(Point const& center, It begin, It end)
    {
        typedef geometry::model::referring_segment<Point const> segment_type;

        bool first = true;

        // An offsetted point-buffer ring around a point is supposed to be closed,
        // therefore walking from start to end is fine.
        It it = begin;
        for (It previous = it++; it != end; ++previous, ++it)
        {
            Point const& p0 = *previous;
            Point const& p1 = *it;
            segment_type const s(p0, p1);
            radius_type const d = geometry::comparable_distance(center, s);

            if (first || d < m_min_comparable_radius)
            {
                m_min_comparable_radius = d;
            }
            if (first || d > m_max_comparable_radius)
            {
                m_max_comparable_radius = d;
            }
            first = false;
        }
    }

};

}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_PIECE_BORDER_HPP

/* piece_border.hpp
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
*/
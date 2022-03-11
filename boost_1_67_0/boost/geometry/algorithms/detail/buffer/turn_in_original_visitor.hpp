// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016, 2018.
// Modifications copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_ORIGINAL_VISITOR
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_ORIGINAL_VISITOR


#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/detail/buffer/buffer_policies.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/strategies/agnostic/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/buffer.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

struct original_get_box
{
    template <typename Box, typename Original>
    static inline void apply(Box& total, Original const& original)
    {
        geometry::expand(total, original.m_box);
    }
};

template <typename DisjointBoxBoxStrategy>
struct original_ovelaps_box
{
    template <typename Box, typename Original>
    static inline bool apply(Box const& box, Original const& original)
    {
        return ! detail::disjoint::disjoint_box_box(box, original.m_box,
                                                    DisjointBoxBoxStrategy());
    }
};

struct include_turn_policy
{
    template <typename Turn>
    static inline bool apply(Turn const& turn)
    {
        return turn.location == location_ok;
    }
};

template <typename DisjointPointBoxStrategy>
struct turn_in_original_ovelaps_box
{
    template <typename Box, typename Turn>
    static inline bool apply(Box const& box, Turn const& turn)
    {
        if (turn.location != location_ok || turn.within_original)
        {
            // Skip all points already processed
            return false;
        }

        return ! geometry::detail::disjoint::disjoint_point_box(
                    turn.robust_point, box, DisjointPointBoxStrategy());
    }
};

//! Check if specified is in range of specified iterators
//! Return value of strategy (true if we can bail out)
template
<
    typename Strategy,
    typename State,
    typename Point,
    typename Iterator
>
inline bool point_in_range(Strategy& strategy, State& state,
        Point const& point, Iterator begin, Iterator end)
{
    boost::ignore_unused(strategy);

    Iterator it = begin;
    for (Iterator previous = it++; it != end; ++previous, ++it)
    {
        if (! strategy.apply(point, *previous, *it, state))
        {
            // We're probably on the boundary
            return false;
        }
    }
    return true;
}

template
<
    typename Strategy,
    typename State,
    typename Point,
    typename CoordinateType,
    typename Iterator
>
inline bool point_in_section(Strategy& strategy, State& state,
        Point const& point, CoordinateType const& point_x,
        Iterator begin, Iterator end,
        int direction)
{
    if (direction == 0)
    {
        // Not a monotonic section, or no change in X-direction
        return point_in_range(strategy, state, point, begin, end);
    }

    // We're in a monotonic section in x-direction
    Iterator it = begin;

    for (Iterator previous = it++; it != end; ++previous, ++it)
    {
        // Depending on sections.direction we can quit for this section
        CoordinateType const previous_x = geometry::get<0>(*previous);

        if (direction == 1 && point_x < previous_x)
        {
            // Section goes upwards, x increases, point is is below section
            return true;
        }
        else if (direction == -1 && point_x > previous_x)
        {
            // Section goes downwards, x decreases, point is above section
            return true;
        }

        if (! strategy.apply(point, *previous, *it, state))
        {
            // We're probably on the boundary
            return false;
        }
    }
    return true;
}


template <typename Point, typename Original, typename PointInGeometryStrategy>
inline int point_in_original(Point const& point, Original const& original,
                             PointInGeometryStrategy const& strategy)
{
    typename PointInGeometryStrategy::state_type state;

    if (boost::size(original.m_sections) == 0
        || boost::size(original.m_ring) - boost::size(original.m_sections) < 16)
    {
        // There are no sections, or it does not profit to walk over sections
        // instead of over points. Boundary of 16 is arbitrary but can influence
        // performance
        point_in_range(strategy, state, point,
                original.m_ring.begin(), original.m_ring.end());
        return strategy.result(state);
    }

    typedef typename Original::sections_type sections_type;
    typedef typename boost::range_iterator<sections_type const>::type iterator_type;
    typedef typename boost::range_value<sections_type const>::type section_type;
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;

    coordinate_type const point_x = geometry::get<0>(point);

    // Walk through all monotonic sections of this original
    for (iterator_type it = boost::begin(original.m_sections);
        it != boost::end(original.m_sections);
        ++it)
    {
        section_type const& section = *it;

        if (! section.duplicate
            && section.begin_index < section.end_index
            && point_x >= geometry::get<min_corner, 0>(section.bounding_box)
            && point_x <= geometry::get<max_corner, 0>(section.bounding_box))
        {
            // x-coordinate of point overlaps with section
            if (! point_in_section(strategy, state, point, point_x,
                    boost::begin(original.m_ring) + section.begin_index,
                    boost::begin(original.m_ring) + section.end_index + 1,
                    section.directions[0]))
            {
                // We're probably on the boundary
                break;
            }
        }
    }

    return strategy.result(state);
}


template <typename Turns, typename PointInGeometryStrategy>
class turn_in_original_visitor
{
public:
    turn_in_original_visitor(Turns& turns, PointInGeometryStrategy const& strategy)
        : m_mutable_turns(turns)
        , m_point_in_geometry_strategy(strategy)
    {}

    template <typename Turn, typename Original>
    inline bool apply(Turn const& turn, Original const& original)
    {
        if (boost::empty(original.m_ring))
        {
            // Skip empty rings
            return true;
        }

        if (turn.location != location_ok || turn.within_original)
        {
            // Skip all points already processed
            return true;
        }

        if (geometry::disjoint(turn.robust_point, original.m_box))
        {
            // Skip all disjoint
            return true;
        }

        int const code = point_in_original(turn.robust_point, original, m_point_in_geometry_strategy);

        if (code == -1)
        {
            return true;
        }

        Turn& mutable_turn = m_mutable_turns[turn.turn_index];

        if (code == 0)
        {
            // On border of original: always discard
            mutable_turn.location = location_discard;
        }

        // Point is inside an original ring
        if (original.m_is_interior)
        {
            mutable_turn.count_in_original--;
        }
        else if (original.m_has_interiors)
        {
            mutable_turn.count_in_original++;
        }
        else
        {
            // It is an exterior ring and there are no interior rings.
            // Then we are completely ready with this turn
            mutable_turn.within_original = true;
            mutable_turn.count_in_original = 1;
        }

        return true;
    }

private :
    Turns& m_mutable_turns;
    PointInGeometryStrategy const& m_point_in_geometry_strategy;
};


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_ORIGINAL_VISITOR

/* turn_in_original_visitor.hpp
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
*/
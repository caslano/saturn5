// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016-2020.
// Modifications copyright (c) 2016-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_ORIGINAL_VISITOR
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_ORIGINAL_VISITOR


#include <boost/core/ignore_unused.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/algorithms/detail/buffer/buffer_policies.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/strategies/agnostic/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/buffer.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{


template <typename Strategy>    
struct original_get_box
{
    explicit original_get_box(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Box, typename Original>
    inline void apply(Box& total, Original const& original) const
    {
        assert_coordinate_type_equal(total, original.m_box);
        geometry::expand(total, original.m_box, m_strategy);
    }

    Strategy const& m_strategy;
};

template <typename Strategy>
struct original_overlaps_box
{
    explicit original_overlaps_box(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Box, typename Original>
    inline bool apply(Box const& box, Original const& original) const
    {
        assert_coordinate_type_equal(box, original.m_box);
        return ! detail::disjoint::disjoint_box_box(box, original.m_box,
                                                    m_strategy);
    }

    Strategy const& m_strategy;
};

struct include_turn_policy
{
    template <typename Turn>
    static inline bool apply(Turn const& turn)
    {
        return turn.is_turn_traversable;
    }
};

template <typename Strategy>
struct turn_in_original_overlaps_box
{
    explicit turn_in_original_overlaps_box(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Box, typename Turn>
    inline bool apply(Box const& box, Turn const& turn) const
    {
        if (! turn.is_turn_traversable || turn.within_original)
        {
            // Skip all points already processed
            return false;
        }

        return ! geometry::detail::disjoint::disjoint_point_box(
                    turn.point, box, m_strategy);
    }

    Strategy const& m_strategy;
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


template <typename Turns, typename Strategy>
class turn_in_original_visitor
{
public:
    turn_in_original_visitor(Turns& turns, Strategy const& strategy)
        : m_mutable_turns(turns)
        , m_strategy(strategy)
    {}

    template <typename Turn, typename Original>
    inline bool apply(Turn const& turn, Original const& original)
    {
        if (boost::empty(original.m_ring))
        {
            // Skip empty rings
            return true;
        }

        if (! turn.is_turn_traversable || turn.within_original)
        {
            // Skip all points already processed
            return true;
        }

        if (geometry::disjoint(turn.point, original.m_box, m_strategy))
        {
            // Skip all disjoint
            return true;
        }

        int const code = point_in_original(turn.point, original,
                                           m_strategy.relate(turn.point, original.m_ring));

        if (code == -1)
        {
            return true;
        }

        Turn& mutable_turn = m_mutable_turns[turn.turn_index];

        if (code == 0)
        {
            // On border of original: always discard
            mutable_turn.is_turn_traversable = false;
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
    Strategy const& m_strategy;
};


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_ORIGINAL_VISITOR

/* turn_in_original_visitor.hpp
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
*/
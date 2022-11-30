// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_FOLLOW_LINEAR_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_FOLLOW_LINEAR_LINEAR_HPP

#include <cstddef>
#include <algorithm>
#include <iterator>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>
#include <boost/throw_exception.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/overlay/copy_segments.hpp>
#include <boost/geometry/algorithms/detail/overlay/follow.hpp>
#include <boost/geometry/algorithms/detail/overlay/inconsistent_turns_exception.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

#include <boost/geometry/algorithms/detail/turns/debug_turn.hpp>

#include <boost/geometry/algorithms/detail/tupled_output.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/util/condition.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

namespace following { namespace linear
{




// follower for linear/linear geometries set operations

template <typename Turn, typename Operation>
static inline bool is_entering(Turn const& turn,
                               Operation const& operation)
{
    if ( turn.method != method_touch && turn.method != method_touch_interior )
    {
        return false;
    }
    return operation.operation == operation_intersection;
}



template <typename Turn, typename Operation>
static inline bool is_staying_inside(Turn const& turn,
                                     Operation const& operation, 
                                     bool entered)
{
    if ( !entered )
    {
        return false;
    }

    if ( turn.method != method_equal && turn.method != method_collinear )
    {
        return false;
    }
    return operation.operation == operation_continue;
}



template <typename Turn, typename Operation>
static inline bool is_leaving(Turn const& turn,
                              Operation const& operation,
                              bool entered)
{
    if ( !entered )
    {
        return false;
    }

    if ( turn.method != method_touch
         && turn.method != method_touch_interior
         && turn.method != method_equal
         && turn.method != method_collinear )
    {
        return false;
    }

    if ( operation.operation == operation_blocked )
    {
        return true;
    }

    if ( operation.operation != operation_union )
    {
        return false;
    }

    return operation.is_collinear;
}



template <typename Turn, typename Operation>
static inline bool is_isolated_point(Turn const& turn,
                                     Operation const& operation,
                                     bool entered)
{
    if ( entered )
    {
        return false;
    }

    if ( turn.method == method_none )
    {
        BOOST_GEOMETRY_ASSERT( operation.operation == operation_continue );
        return true;
    }

    if ( turn.method == method_crosses )
    {
        return true;
    }

    if ( turn.method != method_touch && turn.method != method_touch_interior )
    {
        return false;
    }

    if ( operation.operation == operation_blocked )
    {
        return true;
    }

    if ( operation.operation != operation_union )
    {
        return false;
    }

    return !operation.is_collinear;
}





// GeometryOut - linestring or tuple of at least point and linestring
template
<
    typename GeometryOut,
    typename Linestring,
    typename Linear,
    overlay_type OverlayType,
    bool FollowIsolatedPoints,
    bool FollowContinueTurns
>
class follow_linestring_linear
{
protected:
    // allow spikes (false indicates: do not remove spikes)
    typedef following::action_selector<OverlayType, false> action;

    typedef geometry::detail::output_geometry_access
        <
            GeometryOut, linestring_tag, linestring_tag
        > linear;
    typedef geometry::detail::output_geometry_access
        <
            GeometryOut, point_tag, linestring_tag
        > pointlike;

    template
    <
        typename TurnIterator,
        typename TurnOperationIterator,
        typename LinestringOut,
        typename SegmentIdentifier,
        typename OutputIterator,
        typename SideStrategy
    >
    static inline OutputIterator
    process_turn(TurnIterator it,
                 TurnOperationIterator op_it,
                 bool& entered,
                 std::size_t& enter_count,
                 Linestring const& linestring,
                 LinestringOut& current_piece,
                 SegmentIdentifier& current_segment_id,
                 OutputIterator oit,
                 SideStrategy const& strategy)
    {
        // We don't rescale linear/linear
        detail::no_rescale_policy robust_policy;

        if ( is_entering(*it, *op_it) )
        {
            detail::turns::debug_turn(*it, *op_it, "-> Entering");

            entered = true;
            if ( enter_count == 0 )
            {
                action::enter(current_piece,
                              linestring,
                              current_segment_id,
                              op_it->seg_id.segment_index,
                              it->point, *op_it, strategy, robust_policy,
                              linear::get(oit));
            }
            ++enter_count;
        }
        else if ( is_leaving(*it, *op_it, entered) )
        {
            detail::turns::debug_turn(*it, *op_it, "-> Leaving");

            --enter_count;
            if ( enter_count == 0 )
            {
                entered = false;
                action::leave(current_piece,
                              linestring,
                              current_segment_id,
                              op_it->seg_id.segment_index,
                              it->point, *op_it, strategy, robust_policy,
                              linear::get(oit));
            }
        }
        else if ( BOOST_GEOMETRY_CONDITION(FollowIsolatedPoints)
                  && is_isolated_point(*it, *op_it, entered) )
        {
            detail::turns::debug_turn(*it, *op_it, "-> Isolated point");

            action::template isolated_point
                <
                    typename pointlike::type
                >(it->point, pointlike::get(oit));
        }
        else if ( BOOST_GEOMETRY_CONDITION(FollowContinueTurns)
                  && is_staying_inside(*it, *op_it, entered) )
        {
            detail::turns::debug_turn(*it, *op_it, "-> Staying inside");

            entered = true;
        }
        return oit;
    }

    template
    <
        typename SegmentIdentifier,
        typename LinestringOut,
        typename OutputIterator,
        typename SideStrategy
    >
    static inline OutputIterator
    process_end(bool entered,
                Linestring const& linestring,
                SegmentIdentifier const& current_segment_id,
                LinestringOut& current_piece,
                OutputIterator oit,
                SideStrategy const& strategy)
    {
        if ( action::is_entered(entered) )
        {
            // We don't rescale linear/linear
            detail::no_rescale_policy robust_policy;

            detail::copy_segments::copy_segments_linestring
                <
                    false, false // do not reverse; do not remove spikes
                >::apply(linestring,
                         current_segment_id,
                         static_cast<signed_size_type>(boost::size(linestring) - 1),
                         strategy,
                         robust_policy,
                         current_piece);
        }

        // Output the last one, if applicable
        if (::boost::size(current_piece) > 1)
        {
            *linear::get(oit)++ = current_piece;
        }

        return oit;
    }

public:
    template <typename TurnIterator, typename OutputIterator, typename SideStrategy>
    static inline OutputIterator
    apply(Linestring const& linestring, Linear const&,
          TurnIterator first, TurnIterator beyond,
          OutputIterator oit,
          SideStrategy const& strategy)
    {
        // Iterate through all intersection points (they are
        // ordered along the each line)

        typename linear::type current_piece;
        geometry::segment_identifier current_segment_id(0, -1, -1, -1);

        bool entered = false;
        std::size_t enter_count = 0;

        for (TurnIterator it = first; it != beyond; ++it)
        {
            oit = process_turn(it, boost::begin(it->operations),
                               entered, enter_count, 
                               linestring,
                               current_piece, current_segment_id,
                               oit,
                               strategy);
        }

        if (enter_count != 0)
        {
           return oit;
        }

        return process_end(entered, linestring,
                           current_segment_id, current_piece,
                           oit,
                           strategy);
    }
};




template
<
    typename LinestringOut,
    typename MultiLinestring,
    typename Linear,
    overlay_type OverlayType,
    bool FollowIsolatedPoints,
    bool FollowContinueTurns
>
class follow_multilinestring_linear
    : follow_linestring_linear
        <
            LinestringOut,
            typename boost::range_value<MultiLinestring>::type,
            Linear,
            OverlayType,
            FollowIsolatedPoints,
            FollowContinueTurns
        >
{
protected:
    typedef typename boost::range_value<MultiLinestring>::type Linestring;

    typedef follow_linestring_linear
        <
            LinestringOut, Linestring, Linear,
            OverlayType, FollowIsolatedPoints, FollowContinueTurns
        > Base;

    typedef following::action_selector<OverlayType> action;

    typedef typename boost::range_iterator
        <
            MultiLinestring const
        >::type linestring_iterator;


    template <typename OutputIt, overlay_type OT>
    struct copy_linestrings_in_range
    {
        static inline OutputIt
        apply(linestring_iterator, linestring_iterator, OutputIt oit)
        {
            return oit;
        }
    };

    template <typename OutputIt>
    struct copy_linestrings_in_range<OutputIt, overlay_difference>
    {
        static inline OutputIt
        apply(linestring_iterator first, linestring_iterator beyond,
              OutputIt oit)
        {
            for (linestring_iterator ls_it = first; ls_it != beyond; ++ls_it)
            {
                LinestringOut line_out;
                geometry::convert(*ls_it, line_out);
                *oit++ = line_out;
            }
            return oit;
        }
    };

    template <typename TurnIterator>
    static inline signed_size_type get_multi_index(TurnIterator it)
    {
        return boost::begin(it->operations)->seg_id.multi_index;
    }

    class has_other_multi_id
    {
    private:
        signed_size_type m_multi_id;

    public:
        has_other_multi_id(signed_size_type multi_id)
            : m_multi_id(multi_id) {}

        template <typename Turn>
        bool operator()(Turn const& turn) const
        {
            return boost::begin(turn.operations)->seg_id.multi_index
                != m_multi_id;
        }
    };

public:
    template <typename TurnIterator, typename OutputIterator, typename SideStrategy>
    static inline OutputIterator
    apply(MultiLinestring const& multilinestring, Linear const& linear,
          TurnIterator first, TurnIterator beyond,
          OutputIterator oit,
          SideStrategy const& strategy)
    {
        BOOST_GEOMETRY_ASSERT( first != beyond );

        typedef copy_linestrings_in_range
            <
                OutputIterator, OverlayType
            > copy_linestrings;

        linestring_iterator ls_first = boost::begin(multilinestring);
        linestring_iterator ls_beyond = boost::end(multilinestring);

        // Iterate through all intersection points (they are
        // ordered along the each linestring)

        signed_size_type current_multi_id = get_multi_index(first);

        oit = copy_linestrings::apply(ls_first,
                                      ls_first + current_multi_id,
                                      oit);

        TurnIterator per_ls_next = first;
        do {
            TurnIterator per_ls_current = per_ls_next;

            // find turn with different multi-index
            per_ls_next = std::find_if(per_ls_current, beyond,
                                       has_other_multi_id(current_multi_id));

            oit = Base::apply(*(ls_first + current_multi_id),
                              linear, per_ls_current, per_ls_next, oit, strategy);

            signed_size_type next_multi_id = -1;
            linestring_iterator ls_next = ls_beyond;
            if ( per_ls_next != beyond )
            {
                next_multi_id = get_multi_index(per_ls_next);
                ls_next = ls_first + next_multi_id;
            }
            oit = copy_linestrings::apply(ls_first + current_multi_id + 1,
                                          ls_next,
                                          oit);

            current_multi_id = next_multi_id;
        }
        while ( per_ls_next != beyond );

        return oit;
    }
};






template
<
    typename LinestringOut,
    typename Geometry1,
    typename Geometry2,
    overlay_type OverlayType,
    bool FollowIsolatedPoints,
    bool FollowContinueTurns,
    typename TagIn1 = typename tag<Geometry1>::type
>
struct follow
    : not_implemented<Geometry1>
{};



template
<
    typename LinestringOut,
    typename Linestring,
    typename Linear,
    overlay_type OverlayType,
    bool FollowIsolatedPoints,
    bool FollowContinueTurns
>
struct follow
    <
        LinestringOut, Linestring, Linear,
        OverlayType, FollowIsolatedPoints, FollowContinueTurns,
        linestring_tag
    > : follow_linestring_linear
        <
            LinestringOut, Linestring, Linear,
            OverlayType, FollowIsolatedPoints, FollowContinueTurns
        >
{};


template
<
    typename LinestringOut,
    typename MultiLinestring,
    typename Linear,
    overlay_type OverlayType,
    bool FollowIsolatedPoints,
    bool FollowContinueTurns
>
struct follow
    <
        LinestringOut, MultiLinestring, Linear,
        OverlayType, FollowIsolatedPoints, FollowContinueTurns,
        multi_linestring_tag
    > : follow_multilinestring_linear
        <
            LinestringOut, MultiLinestring, Linear,
            OverlayType, FollowIsolatedPoints, FollowContinueTurns
        >
{};



}} // namespace following::linear

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_FOLLOW_LINEAR_LINEAR_HPP

/* follow_linear_linear.hpp
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
*/
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

#include <boost/range.hpp>
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
        else if ( FollowIsolatedPoints
                  && is_isolated_point(*it, *op_it, entered) )
        {
            detail::turns::debug_turn(*it, *op_it, "-> Isolated point");

            action::template isolated_point
                <
                    typename pointlike::type
                >(it->point, pointlike::get(oit));
        }
        else if ( FollowContinueTurns
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

#if ! defined(BOOST_GEOMETRY_OVERLAY_NO_THROW)
        if (enter_count != 0)
        {
            BOOST_THROW_EXCEPTION(inconsistent_turns_exception());
        }
#else
        BOOST_GEOMETRY_ASSERT(enter_count == 0);
#endif

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
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_FOLLOW_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_FOLLOW_HPP

#include <cstddef>
#include <type_traits>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/detail/overlay/append_no_duplicates.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segments.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>
#include <boost/geometry/algorithms/detail/relate/turns.hpp>
#include <boost/geometry/algorithms/detail/tupled_output.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/util/condition.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

namespace following
{

template <typename Turn, typename Operation>
inline bool is_entering(Turn const& /* TODO remove this parameter */, Operation const& op)
{
    // (Blocked means: blocked for polygon/polygon intersection, because
    // they are reversed. But for polygon/line it is similar to continue)
    return op.operation == operation_intersection
        || op.operation == operation_continue
        || op.operation == operation_blocked
        ;
}

template
<
    typename Turn,
    typename Operation,
    typename LineString,
    typename Polygon,
    typename Strategy
>
inline bool last_covered_by(Turn const& /*turn*/, Operation const& op,
                LineString const& linestring, Polygon const& polygon,
                Strategy const& strategy)
{
    return geometry::covered_by(range::at(linestring, op.seg_id.segment_index), polygon, strategy);
}


template
<
    typename Turn,
    typename Operation,
    typename LineString,
    typename Polygon,
    typename Strategy
>
inline bool is_leaving(Turn const& turn, Operation const& op,
                bool entered, bool first,
                LineString const& linestring, Polygon const& polygon,
                Strategy const& strategy)
{
    if (op.operation == operation_union)
    {
        return entered
            || turn.method == method_crosses
            || (first
                && op.position != position_front
                && last_covered_by(turn, op, linestring, polygon, strategy))
            ;
    }
    return false;
}


template
<
    typename Turn,
    typename Operation,
    typename LineString,
    typename Polygon,
    typename Strategy
>
inline bool is_staying_inside(Turn const& turn, Operation const& op,
                bool entered, bool first,
                LineString const& linestring, Polygon const& polygon,
                Strategy const& strategy)
{
    if (turn.method == method_crosses)
    {
        // The normal case, this is completely covered with entering/leaving
        // so stay out of this time consuming "covered_by"
        return false;
    }

    if (is_entering(turn, op))
    {
        return entered || (first && last_covered_by(turn, op, linestring, polygon, strategy));
    }

    return false;
}

template
<
    typename Turn,
    typename Operation,
    typename Linestring,
    typename Polygon,
    typename Strategy
>
inline bool was_entered(Turn const& turn, Operation const& op, bool first,
                Linestring const& linestring, Polygon const& polygon,
                Strategy const& strategy)
{
    if (first && (turn.method == method_collinear || turn.method == method_equal))
    {
        return last_covered_by(turn, op, linestring, polygon, strategy);
    }
    return false;
}

template
<
    typename Turn,
    typename Operation
>
inline bool is_touching(Turn const& turn, Operation const& op,
                        bool entered)
{
    return (op.operation == operation_union || op.operation == operation_blocked)
        && (turn.method == method_touch || turn.method == method_touch_interior)
        && !entered
        && !op.is_collinear;
}


template
<
    typename GeometryOut,
    typename Tag = typename geometry::tag<GeometryOut>::type
>
struct add_isolated_point
{};

template <typename LineStringOut>
struct add_isolated_point<LineStringOut, linestring_tag>
{
    template <typename Point, typename OutputIterator>
    static inline void apply(Point const& point, OutputIterator& out)
    {
        LineStringOut isolated_point_ls;
        geometry::append(isolated_point_ls, point);

#ifndef BOOST_GEOMETRY_ALLOW_ONE_POINT_LINESTRINGS
        geometry::append(isolated_point_ls, point);
#endif // BOOST_GEOMETRY_ALLOW_ONE_POINT_LINESTRINGS

        *out++ = isolated_point_ls;
    }
};

template <typename PointOut>
struct add_isolated_point<PointOut, point_tag>
{
    template <typename Point, typename OutputIterator>
    static inline void apply(Point const& point, OutputIterator& out)
    {
        PointOut isolated_point;

        geometry::detail::conversion::convert_point_to_point(point, isolated_point);

        *out++ = isolated_point;
    }
};


// Template specialization structure to call the right actions for the right type
template <overlay_type OverlayType, bool RemoveSpikes = true>
struct action_selector
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "If you get here the overlay type is not intersection or difference.",
        std::integral_constant<overlay_type, OverlayType>);
};

// Specialization for intersection, containing the implementation
template <bool RemoveSpikes>
struct action_selector<overlay_intersection, RemoveSpikes>
{
    template
    <
        typename OutputIterator,
        typename LineStringOut,
        typename LineString,
        typename Point,
        typename Operation,
        typename Strategy,
        typename RobustPolicy
    >
    static inline void enter(LineStringOut& current_piece,
                LineString const& ,
                segment_identifier& segment_id,
                signed_size_type , Point const& point,
                Operation const& operation,
                Strategy const& strategy,
                RobustPolicy const& ,
                OutputIterator& )
    {
        // On enter, append the intersection point and remember starting point
        // TODO: we don't check on spikes for linestrings (?). Consider this.
        detail::overlay::append_no_duplicates(current_piece, point, strategy);
        segment_id = operation.seg_id;
    }

    template
    <
        typename OutputIterator,
        typename LineStringOut,
        typename LineString,
        typename Point,
        typename Operation,
        typename Strategy,
        typename RobustPolicy
    >
    static inline void leave(LineStringOut& current_piece,
                LineString const& linestring,
                segment_identifier& segment_id,
                signed_size_type index, Point const& point,
                Operation const& ,
                Strategy const& strategy,
                RobustPolicy const& robust_policy,
                OutputIterator& out)
    {
        // On leave, copy all segments from starting point, append the intersection point
        // and add the output piece
        detail::copy_segments::copy_segments_linestring
            <
                false, RemoveSpikes
            >::apply(linestring, segment_id, index, strategy, robust_policy, current_piece);
        detail::overlay::append_no_duplicates(current_piece, point, strategy);
        if (::boost::size(current_piece) > 1)
        {
            *out++ = current_piece;
        }

        geometry::clear(current_piece);
    }

    template
    <
        typename LineStringOrPointOut,
        typename Point,
        typename OutputIterator
    >
    static inline void isolated_point(Point const& point,
                                      OutputIterator& out)
    {
        add_isolated_point<LineStringOrPointOut>::apply(point, out);
    }

    static inline bool is_entered(bool entered)
    {
        return entered;
    }

    static inline bool included(int inside_value)
    {
        return inside_value >= 0; // covered_by
    }

};

// Specialization for difference, which reverses these actions
template <bool RemoveSpikes>
struct action_selector<overlay_difference, RemoveSpikes>
{
    typedef action_selector<overlay_intersection, RemoveSpikes> normal_action;

    template
    <
        typename OutputIterator,
        typename LineStringOut,
        typename LineString,
        typename Point,
        typename Operation,
        typename Strategy,
        typename RobustPolicy
    >
    static inline void enter(LineStringOut& current_piece,
                LineString const& linestring,
                segment_identifier& segment_id,
                signed_size_type index, Point const& point,
                Operation const& operation,
                Strategy const& strategy,
                RobustPolicy const& robust_policy,
                OutputIterator& out)
    {
        normal_action::leave(current_piece, linestring, segment_id, index,
                    point, operation, strategy, robust_policy, out);
    }

    template
    <
        typename OutputIterator,
        typename LineStringOut,
        typename LineString,
        typename Point,
        typename Operation,
        typename Strategy,
        typename RobustPolicy
    >
    static inline void leave(LineStringOut& current_piece,
                LineString const& linestring,
                segment_identifier& segment_id,
                signed_size_type index, Point const& point,
                Operation const& operation,
                Strategy const& strategy,
                RobustPolicy const& robust_policy,
                OutputIterator& out)
    {
        normal_action::enter(current_piece, linestring, segment_id, index,
                    point, operation, strategy, robust_policy, out);
    }

    template
    <
        typename LineStringOrPointOut,
        typename Point,
        typename OutputIterator
    >
    static inline void isolated_point(Point const&,
                                      OutputIterator const&)
    {
    }

    static inline bool is_entered(bool entered)
    {
        return ! normal_action::is_entered(entered);
    }

    static inline bool included(int inside_value)
    {
        return ! normal_action::included(inside_value);
    }

};

} // namespace following

/*!
\brief Follows a linestring from intersection point to intersection point, outputting which
    is inside, or outside, a ring or polygon
\ingroup overlay
 */
template
<
    typename GeometryOut,
    typename LineString,
    typename Polygon,
    overlay_type OverlayType,
    bool RemoveSpikes,
    bool FollowIsolatedPoints
>
class follow
{
    typedef geometry::detail::output_geometry_access
        <
            GeometryOut, linestring_tag, linestring_tag
        > linear;
    typedef geometry::detail::output_geometry_access
        <
            GeometryOut, point_tag, linestring_tag
        > pointlike;

public :

    static inline bool included(int inside_value)
    {
        return following::action_selector
            <
                OverlayType, RemoveSpikes
            >::included(inside_value);
    }

    template
    <
        typename Turns,
        typename OutputIterator,
        typename RobustPolicy,
        typename Strategy
    >
    static inline OutputIterator apply(LineString const& linestring, Polygon const& polygon,
                detail::overlay::operation_type ,  // TODO: this parameter might be redundant
                Turns& turns,
                RobustPolicy const& robust_policy,
                OutputIterator out,
                Strategy const& strategy)
    {
        typedef typename boost::range_iterator<Turns>::type turn_iterator;
        typedef typename boost::range_value<Turns>::type turn_type;
        typedef typename boost::range_iterator
            <
                typename turn_type::container_type
            >::type turn_operation_iterator_type;

        typedef following::action_selector<OverlayType, RemoveSpikes> action;

        // Sort intersection points on segments-along-linestring, and distance
        // (like in enrich is done for poly/poly)
        // sort turns by Linear seg_id, then by fraction, then
        // for same ring id: x, u, i, c
        // for different ring id: c, i, u, x
        typedef relate::turns::less
            <
                0, relate::turns::less_op_linear_areal_single<0>,
                typename Strategy::cs_tag
            > turn_less;
        std::sort(boost::begin(turns), boost::end(turns), turn_less());

        typename linear::type current_piece;
        geometry::segment_identifier current_segment_id(0, -1, -1, -1);

        // Iterate through all intersection points (they are ordered along the line)
        bool entered = false;
        bool first = true;
        for (turn_iterator it = boost::begin(turns); it != boost::end(turns); ++it)
        {
            turn_operation_iterator_type iit = boost::begin(it->operations);

            if (following::was_entered(*it, *iit, first, linestring, polygon, strategy))
            {
                debug_traverse(*it, *iit, "-> Was entered");
                entered = true;
            }

            if (following::is_staying_inside(*it, *iit, entered, first, linestring, polygon, strategy))
            {
                debug_traverse(*it, *iit, "-> Staying inside");

                entered = true;
            }
            else if (following::is_entering(*it, *iit))
            {
                debug_traverse(*it, *iit, "-> Entering");

                entered = true;
                action::enter(current_piece, linestring, current_segment_id,
                    iit->seg_id.segment_index, it->point, *iit,
                    strategy, robust_policy,
                    linear::get(out));
            }
            else if (following::is_leaving(*it, *iit, entered, first, linestring, polygon, strategy))
            {
                debug_traverse(*it, *iit, "-> Leaving");

                entered = false;
                action::leave(current_piece, linestring, current_segment_id,
                    iit->seg_id.segment_index, it->point, *iit,
                    strategy, robust_policy,
                    linear::get(out));
            }
            else if (BOOST_GEOMETRY_CONDITION(FollowIsolatedPoints)
                  && following::is_touching(*it, *iit, entered))
            {
                debug_traverse(*it, *iit, "-> Isolated point");

                action::template isolated_point
                    <
                        typename pointlike::type
                    >(it->point, pointlike::get(out));
            }

            first = false;
        }

        if (action::is_entered(entered))
        {
            detail::copy_segments::copy_segments_linestring
                <
                    false, RemoveSpikes
                >::apply(linestring,
                         current_segment_id,
                         static_cast<signed_size_type>(boost::size(linestring) - 1),
                         strategy, robust_policy,
                         current_piece);
        }

        // Output the last one, if applicable
        std::size_t current_piece_size = ::boost::size(current_piece);
        if (current_piece_size > 1)
        {
            *linear::get(out)++ = current_piece;
        }
        else if (BOOST_GEOMETRY_CONDITION(FollowIsolatedPoints)
              && current_piece_size == 1)
        {
            action::template isolated_point
                <
                    typename pointlike::type
                >(range::front(current_piece), pointlike::get(out));
        }

        return out;
    }

};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_FOLLOW_HPP

/* follow.hpp
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
*/
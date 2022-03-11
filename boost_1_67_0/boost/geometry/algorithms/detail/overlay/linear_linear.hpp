// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_LINEAR_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_LINEAR_LINEAR_HPP

#include <algorithm>
#include <vector>

#include <boost/range.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/relate/turns.hpp>

#include <boost/geometry/algorithms/detail/turns/compare_turns.hpp>
#include <boost/geometry/algorithms/detail/turns/filter_continue_turns.hpp>
#include <boost/geometry/algorithms/detail/turns/remove_duplicate_turns.hpp>

#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/follow_linear_linear.hpp>

#include <boost/geometry/algorithms/convert.hpp>



namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template
<
    typename LineStringOut,
    overlay_type OverlayType,
    typename Geometry,
    typename GeometryTag
>
struct linear_linear_no_intersections;


template <typename LineStringOut, typename LineString>
struct linear_linear_no_intersections
    <
        LineStringOut, overlay_difference, LineString, linestring_tag
    >
{
    template <typename OutputIterator>
    static inline OutputIterator apply(LineString const& linestring,
                                       OutputIterator oit)
    {
        LineStringOut ls_out;
        geometry::convert(linestring, ls_out);
        *oit++ = ls_out;
        return oit;
    }
};


template <typename LineStringOut, typename MultiLineString>
struct linear_linear_no_intersections
    <
        LineStringOut,
        overlay_difference,
        MultiLineString,
        multi_linestring_tag
    >
{
    template <typename OutputIterator>
    static inline OutputIterator apply(MultiLineString const& multilinestring,
                                       OutputIterator oit)
    {
        for (typename boost::range_iterator<MultiLineString const>::type
                 it = boost::begin(multilinestring);
             it != boost::end(multilinestring); ++it)
        {
            LineStringOut ls_out;
            geometry::convert(*it, ls_out);
            *oit++ = ls_out;
        }
        return oit;
    }
};


template <typename LineStringOut, typename Geometry, typename GeometryTag>
struct linear_linear_no_intersections
    <
        LineStringOut, overlay_intersection, Geometry, GeometryTag
    >
{
    template <typename OutputIterator>
    static inline OutputIterator apply(Geometry const&,
                                       OutputIterator oit)
    {
        return oit;
    }
};







template
<
    typename Linear1,
    typename Linear2,
    typename LinestringOut,
    overlay_type OverlayType,
    bool EnableFilterContinueTurns = false,
    bool EnableRemoveDuplicateTurns = false,
    bool EnableDegenerateTurns = true,
#ifdef BOOST_GEOMETRY_INTERSECTION_DO_NOT_INCLUDE_ISOLATED_POINTS
    bool EnableFollowIsolatedPoints = false
#else
    bool EnableFollowIsolatedPoints = true
#endif
>
class linear_linear_linestring
{
protected:
    struct assign_policy
    {
        static bool const include_no_turn = false;
        static bool const include_degenerate = EnableDegenerateTurns;
        static bool const include_opposite = false;
    };


    template
    <
        typename Turns,
        typename LinearGeometry1,
        typename LinearGeometry2,
        typename IntersectionStrategy,
        typename RobustPolicy
    >
    static inline void compute_turns(Turns& turns,
                                     LinearGeometry1 const& linear1,
                                     LinearGeometry2 const& linear2,
                                     IntersectionStrategy const& strategy,
                                     RobustPolicy const& robust_policy)
    {
        turns.clear();

        detail::get_turns::no_interrupt_policy interrupt_policy;

        geometry::detail::relate::turns::get_turns
            <
                LinearGeometry1,
                LinearGeometry2,
                detail::get_turns::get_turn_info_type
                <
                    LinearGeometry1,
                    LinearGeometry2,
                    assign_policy
                >
            >::apply(turns, linear1, linear2, interrupt_policy, strategy, robust_policy);
    }


    template
    <
        overlay_type OverlayTypeForFollow,
        bool FollowIsolatedPoints,
        typename Turns,
        typename LinearGeometry1,
        typename LinearGeometry2,
        typename OutputIterator,
        typename IntersectionStrategy
    >
    static inline OutputIterator
    sort_and_follow_turns(Turns& turns,
                          LinearGeometry1 const& linear1,
                          LinearGeometry2 const& linear2,
                          OutputIterator oit,
                          IntersectionStrategy const& strategy)
    {
        // remove turns that have no added value
        turns::filter_continue_turns
            <
                Turns,
                EnableFilterContinueTurns && OverlayType != overlay_intersection
            >::apply(turns);

        // sort by seg_id, distance, and operation
        std::sort(boost::begin(turns), boost::end(turns),
                  detail::turns::less_seg_fraction_other_op<>());

        // remove duplicate turns
        turns::remove_duplicate_turns
            <
                Turns, EnableRemoveDuplicateTurns
            >::apply(turns);

        return detail::overlay::following::linear::follow
            <
                LinestringOut,
                LinearGeometry1,
                LinearGeometry2,
                OverlayTypeForFollow,
                FollowIsolatedPoints,
                !EnableFilterContinueTurns || OverlayType == overlay_intersection
            >::apply(linear1, linear2, boost::begin(turns), boost::end(turns),
                     oit, strategy.get_side_strategy());
    }

public:
    template
    <
        typename RobustPolicy, typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Linear1 const& linear1,
                                       Linear2 const& linear2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        typedef typename detail::relate::turns::get_turns
            <
                Linear1,
                Linear2,
                detail::get_turns::get_turn_info_type
                    <
                        Linear1,
                        Linear2,
                        assign_policy
                    >
            >::template turn_info_type<Strategy, RobustPolicy>::type turn_info;

        typedef std::vector<turn_info> turns_container;

        turns_container turns;
        compute_turns(turns, linear1, linear2, strategy, robust_policy);

        if ( turns.empty() )
        {
            // the two linear geometries are disjoint
            return linear_linear_no_intersections
                <
                    LinestringOut,
                    OverlayType,
                    Linear1,
                    typename tag<Linear1>::type
                >::apply(linear1, oit);
        }

        return sort_and_follow_turns
            <
                OverlayType,
                EnableFollowIsolatedPoints
                && OverlayType == overlay_intersection
            >(turns, linear1, linear2, oit, strategy);
    }
};




template
<
    typename Linear1,
    typename Linear2,
    typename LinestringOut,
    bool EnableFilterContinueTurns,
    bool EnableRemoveDuplicateTurns,
    bool EnableDegenerateTurns,
    bool EnableFollowIsolatedPoints
>
struct linear_linear_linestring
    <
        Linear1, Linear2, LinestringOut, overlay_union,
        EnableFilterContinueTurns, EnableRemoveDuplicateTurns,
        EnableDegenerateTurns, EnableFollowIsolatedPoints
    >
{
    template
    <
        typename RobustPolicy, typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Linear1 const& linear1,
                                       Linear2 const& linear2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        oit = linear_linear_no_intersections
            <
                LinestringOut,
                overlay_difference,
                Linear1,
                typename tag<Linear1>::type
            >::apply(linear1, oit);

        return linear_linear_linestring
            <
                Linear2, Linear1, LinestringOut, overlay_difference,
                EnableFilterContinueTurns, EnableRemoveDuplicateTurns,
                EnableDegenerateTurns, EnableFollowIsolatedPoints
            >::apply(linear2, linear1, robust_policy, oit, strategy);
    }
};




}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_LINEAR_LINEAR_HPP

/* linear_linear.hpp
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
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_LINEAR_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_LINEAR_LINEAR_HPP

#include <algorithm>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

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
        static bool const include_start_turn = false;
    };


    template
    <
        typename Turns,
        typename LinearGeometry1,
        typename LinearGeometry2,
        typename Strategy,
        typename RobustPolicy
    >
    static inline void compute_turns(Turns& turns,
                                     LinearGeometry1 const& linear1,
                                     LinearGeometry2 const& linear2,
                                     Strategy const& strategy,
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
        typename Strategy
    >
    static inline OutputIterator
    sort_and_follow_turns(Turns& turns,
                          LinearGeometry1 const& linear1,
                          LinearGeometry2 const& linear2,
                          OutputIterator oit,
                          Strategy const& strategy)
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
                     oit, strategy);
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
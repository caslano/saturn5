// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2015, 2017, 2019, 2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INTERSECTION_INSERT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INTERSECTION_INSERT_HPP


#include <cstddef>

#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/range/metafunctions.hpp>


#include <boost/geometry/core/is_areal.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>
#include <boost/geometry/algorithms/detail/overlay/clip_linestring.hpp>
#include <boost/geometry/algorithms/detail/overlay/follow.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_intersection_points.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/range_in_geometry.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_as_subrange.hpp>

#include <boost/geometry/policies/robustness/rescale_policy_tags.hpp>
#include <boost/geometry/policies/robustness/segment_ratio_type.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>

#include <boost/geometry/views/segment_view.hpp>
#include <boost/geometry/views/detail/boundary_view.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/detail/overlay/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/overlay/pointlike_areal.hpp>
#include <boost/geometry/algorithms/detail/overlay/pointlike_linear.hpp>
#include <boost/geometry/algorithms/detail/overlay/pointlike_pointlike.hpp>

#if defined(BOOST_GEOMETRY_DEBUG_FOLLOW)
#include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#endif

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace intersection
{

template <typename PointOut>
struct intersection_segment_segment_point
{
    template
    <
        typename Segment1, typename Segment2,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Segment1 const& segment1,
            Segment2 const& segment2,
            RobustPolicy const& ,
            OutputIterator out,
            Strategy const& strategy)
    {
        // Make sure this is only called with no rescaling
        BOOST_STATIC_ASSERT((boost::is_same
           <
               no_rescale_policy_tag,
               typename rescale_policy_type<RobustPolicy>::type
           >::value));

        typedef typename point_type<PointOut>::type point_type;

        // Get the intersection point (or two points)
        typedef segment_intersection_points<point_type> intersection_return_type;

        typedef policies::relate::segments_intersection_points
            <
                intersection_return_type
            > policy_type;

        detail::segment_as_subrange<Segment1> sub_range1(segment1);
        detail::segment_as_subrange<Segment2> sub_range2(segment2);

        intersection_return_type
            is = strategy.apply(sub_range1, sub_range2, policy_type());

        for (std::size_t i = 0; i < is.count; i++)
        {
            PointOut p;
            geometry::convert(is.intersections[i], p);
            *out++ = p;
        }
        return out;
    }
};

template <typename PointOut>
struct intersection_linestring_linestring_point
{
    template
    <
        typename Linestring1, typename Linestring2,
        typename RobustPolicy,
        typename OutputIterator,
        typename Strategy
    >
    static inline OutputIterator apply(Linestring1 const& linestring1,
            Linestring2 const& linestring2,
            RobustPolicy const& robust_policy,
            OutputIterator out,
            Strategy const& strategy)
    {
        // Make sure this is only called with no rescaling
        BOOST_STATIC_ASSERT((boost::is_same
           <
               no_rescale_policy_tag,
               typename rescale_policy_type<RobustPolicy>::type
           >::value));

        typedef detail::overlay::turn_info<PointOut> turn_info;
        std::deque<turn_info> turns;

        geometry::get_intersection_points(linestring1, linestring2,
                                          robust_policy, turns, strategy);

        for (typename boost::range_iterator<std::deque<turn_info> const>::type
            it = boost::begin(turns); it != boost::end(turns); ++it)
        {
            PointOut p;
            geometry::convert(it->point, p);
            *out++ = p;
        }
        return out;
    }
};

/*!
\brief Version of linestring with an areal feature (polygon or multipolygon)
*/
template
<
    bool ReverseAreal,
    typename GeometryOut,
    overlay_type OverlayType,
    bool FollowIsolatedPoints
>
struct intersection_of_linestring_with_areal
{
#if defined(BOOST_GEOMETRY_DEBUG_FOLLOW)
    template <typename Turn, typename Operation>
    static inline void debug_follow(Turn const& turn, Operation op,
                                    int index)
    {
        std::cout << index
                  << " at " << op.seg_id
                  << " meth: " << method_char(turn.method)
                  << " op: " << operation_char(op.operation)
                  << " vis: " << visited_char(op.visited)
                  << " of:  " << operation_char(turn.operations[0].operation)
                  << operation_char(turn.operations[1].operation)
                  << " " << geometry::wkt(turn.point)
                  << std::endl;
    }

    template <typename Turn>
    static inline void debug_turn(Turn const& t, bool non_crossing)
    {
        std::cout << "checking turn @"
                  << geometry::wkt(t.point)
                  << "; " << method_char(t.method)
                  << ":" << operation_char(t.operations[0].operation)
                  << "/" << operation_char(t.operations[1].operation)
                  << "; non-crossing? "
                  << std::boolalpha << non_crossing << std::noboolalpha
                  << std::endl;
    }
#endif

    template <typename Linestring, typename Areal, typename Strategy, typename Turns>
    static inline bool simple_turns_analysis(Linestring const& linestring,
                                             Areal const& areal,
                                             Strategy const& strategy,
                                             Turns const& turns,
                                             int & inside_value)
    {
        using namespace overlay;

        bool found_continue = false;
        bool found_intersection = false;
        bool found_union = false;
        bool found_front = false;

        for (typename Turns::const_iterator it = turns.begin();
                it != turns.end(); ++it)
        {
            method_type const method = it->method;
            operation_type const op = it->operations[0].operation;

            if (method == method_crosses)
            {
                return false;
            }
            else if (op == operation_intersection)
            {
                found_intersection = true;
            }
            else if (op == operation_union)
            {
                found_union = true;
            }
            else if (op == operation_continue)
            {
                found_continue = true;
            }

            if ((found_intersection || found_continue) && found_union)
            {
                return false;
            }

            if (it->operations[0].position == position_front)
            {
                found_front = true;
            }
        }

        if (found_front)
        {
            if (found_intersection)
            {
                inside_value = 1; // inside
            }
            else if (found_union)
            {
                inside_value = -1; // outside
            }
            else // continue and blocked
            {
                inside_value = 0;
            }
            return true;
        }

        // if needed analyse points of a linestring
        // NOTE: range_in_geometry checks points of a linestring
        // until a point inside/outside areal is found
        // TODO: Could be replaced with point_in_geometry() because found_front is false
        inside_value = range_in_geometry(linestring, areal, strategy);

        if ( (found_intersection && inside_value == -1) // going in from outside
          || (found_continue && inside_value == -1) // going on boundary from outside
          || (found_union && inside_value == 1) ) // going out from inside
        {
            return false;
        }

        return true;
    }

    template
    <
        typename LineString, typename Areal,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(LineString const& linestring, Areal const& areal,
            RobustPolicy const& robust_policy,
            OutputIterator out,
            Strategy const& strategy)
    {
        // Make sure this is only called with no rescaling
        BOOST_STATIC_ASSERT((boost::is_same
           <
               no_rescale_policy_tag,
               typename rescale_policy_type<RobustPolicy>::type
           >::value));

        if (boost::size(linestring) == 0)
        {
            return out;
        }

        typedef detail::overlay::follow
                <
                    GeometryOut,
                    LineString,
                    Areal,
                    OverlayType,
                    false, // do not remove spikes for linear geometries
                    FollowIsolatedPoints
                > follower;

        typedef typename geometry::detail::output_geometry_access
            <
                GeometryOut, linestring_tag, linestring_tag
            > linear;

        typedef typename point_type
            <
                typename linear::type
            >::type point_type;

        typedef geometry::segment_ratio
            <
                typename coordinate_type<point_type>::type
            > ratio_type;

        typedef detail::overlay::turn_info
            <
                point_type,
                ratio_type,
                detail::overlay::turn_operation_linear
                    <
                        point_type,
                        ratio_type
                    >
            > turn_info;

        std::deque<turn_info> turns;

        detail::get_turns::no_interrupt_policy policy;

        typedef detail::overlay::get_turn_info_linear_areal
            <
                detail::overlay::assign_null_policy
            > turn_policy;

        dispatch::get_turns
            <
                typename geometry::tag<LineString>::type,
                typename geometry::tag<Areal>::type,
                LineString,
                Areal,
                false,
                (OverlayType == overlay_intersection ? ReverseAreal : !ReverseAreal),
                turn_policy
            >::apply(0, linestring, 1, areal,
                     strategy, robust_policy,
                     turns, policy);

        int inside_value = 0;
        if (simple_turns_analysis(linestring, areal, strategy, turns, inside_value))
        {
            // No crossing the boundary, it is either
            // inside (interior + borders)
            // or outside (exterior + borders)
            // or on boundary

            // add linestring to the output if conditions are met
            if (follower::included(inside_value))
            {
                typename linear::type copy;
                geometry::convert(linestring, copy);
                *linear::get(out)++ = copy;
            }

            return out;
        }
        
#if defined(BOOST_GEOMETRY_DEBUG_FOLLOW)
        int index = 0;
        for(typename std::deque<turn_info>::const_iterator
            it = turns.begin(); it != turns.end(); ++it)
        {
            debug_follow(*it, it->operations[0], index++);
        }
#endif

        return follower::apply
                (
                    linestring, areal,
                    geometry::detail::overlay::operation_intersection,
                    turns, robust_policy, out, strategy
                );
    }
};


template <typename Turns, typename OutputIterator>
inline OutputIterator intersection_output_turn_points(Turns const& turns,
                                                      OutputIterator out)
{
    for (typename Turns::const_iterator
            it = turns.begin(); it != turns.end(); ++it)
    {
        *out++ = it->point;
    }

    return out;
}

template <typename PointOut>
struct intersection_areal_areal_point
{
    template
    <
        typename Geometry1, typename Geometry2,
        typename RobustPolicy,
        typename OutputIterator,
        typename Strategy
    >
    static inline OutputIterator apply(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        typedef detail::overlay::turn_info
            <
                PointOut,
                typename segment_ratio_type<PointOut, RobustPolicy>::type
            > turn_info;
        std::vector<turn_info> turns;

        detail::get_turns::no_interrupt_policy policy;

        geometry::get_turns
            <
                false, false, detail::overlay::assign_null_policy
            >(geometry1, geometry2, strategy, robust_policy, turns, policy);

        return intersection_output_turn_points(turns, out);
    }
};

template <typename PointOut>
struct intersection_linear_areal_point
{
    template
    <
        typename Geometry1, typename Geometry2,
        typename RobustPolicy,
        typename OutputIterator,
        typename Strategy
    >
    static inline OutputIterator apply(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        // Make sure this is only called with no rescaling
        BOOST_STATIC_ASSERT((boost::is_same
           <
               no_rescale_policy_tag,
               typename rescale_policy_type<RobustPolicy>::type
           >::value));

        typedef geometry::segment_ratio<typename geometry::coordinate_type<PointOut>::type> ratio_type;

        typedef detail::overlay::turn_info
            <
                PointOut,
                ratio_type,
                detail::overlay::turn_operation_linear
                    <
                        PointOut,
                        ratio_type
                    >
            > turn_info;

        typedef detail::overlay::get_turn_info_linear_areal
            <
                detail::overlay::assign_null_policy
            > turn_policy;

        std::vector<turn_info> turns;

        detail::get_turns::no_interrupt_policy interrupt_policy;

        dispatch::get_turns
            <
                typename geometry::tag<Geometry1>::type,
                typename geometry::tag<Geometry2>::type,
                Geometry1,
                Geometry2,
                false,
                false,
                turn_policy
            >::apply(0, geometry1, 1, geometry2,
                     strategy, robust_policy,
                     turns, interrupt_policy);

        return intersection_output_turn_points(turns, out);
    }
};

template <typename PointOut>
struct intersection_areal_linear_point
{
    template
    <
        typename Geometry1, typename Geometry2,
        typename RobustPolicy,
        typename OutputIterator,
        typename Strategy
    >
    static inline OutputIterator apply(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        return intersection_linear_areal_point
            <
                PointOut
            >::apply(geometry2, geometry1, robust_policy, out, strategy);
    }
};


struct tupled_output_tag {};


template
<
    typename GeometryOut,
    bool IsTupled = geometry::detail::is_tupled_range_values<GeometryOut>::value
>
struct tag
    : geometry::tag<GeometryOut>
{};

template <typename GeometryOut>
struct tag<GeometryOut, true>
{
    typedef tupled_output_tag type;
};


template <typename Geometry1, typename Geometry2, typename TupledOut>
struct expect_output_p
{
    static const bool is_point_found = geometry::tuples::exists_if
        <
            TupledOut, geometry::detail::is_tag_same_as_pred<point_tag>::template pred
        >::value;

    BOOST_MPL_ASSERT_MSG
        (
            is_point_found, POINTLIKE_GEOMETRY_EXPECTED_IN_TUPLED_OUTPUT,
            (types<Geometry1, Geometry2, TupledOut>)
        );
};

template <typename Geometry1, typename Geometry2, typename TupledOut>
struct expect_output_pl
    : expect_output_p<Geometry1, Geometry2, TupledOut>
{
    static const bool is_linestring_found = geometry::tuples::exists_if
        <
            TupledOut, geometry::detail::is_tag_same_as_pred<linestring_tag>::template pred
        >::value;

    BOOST_MPL_ASSERT_MSG
        (
            is_linestring_found, LINEAR_GEOMETRY_EXPECTED_IN_TUPLED_OUTPUT,
            (types<Geometry1, Geometry2, TupledOut>)
        );
};

template <typename Geometry1, typename Geometry2, typename TupledOut>
struct expect_output_pla
    : expect_output_pl<Geometry1, Geometry2, TupledOut>
{
    static const bool is_polygon_found = geometry::tuples::exists_if
        <
            TupledOut, geometry::detail::is_tag_same_as_pred<polygon_tag>::template pred
        >::value;

    BOOST_MPL_ASSERT_MSG
    (
        is_polygon_found, AREAL_GEOMETRY_EXPECTED_IN_TUPLED_OUTPUT,
        (types<Geometry1, Geometry2, TupledOut>)
    );
};


}} // namespace detail::intersection
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    // real types
    typename Geometry1,
    typename Geometry2,
    typename GeometryOut,
    overlay_type OverlayType,
    // orientation
    bool Reverse1 = detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
    bool Reverse2 = detail::overlay::do_reverse<geometry::point_order<Geometry2>::value>::value,
    // tag dispatching:
    typename TagIn1 = typename geometry::tag<Geometry1>::type,
    typename TagIn2 = typename geometry::tag<Geometry2>::type,
    typename TagOut = typename detail::intersection::tag<GeometryOut>::type,
    // metafunction finetuning helpers:
    typename CastedTagIn1 = typename geometry::tag_cast<TagIn1, areal_tag, linear_tag, pointlike_tag>::type,
    typename CastedTagIn2 = typename geometry::tag_cast<TagIn2, areal_tag, linear_tag, pointlike_tag>::type,
    typename CastedTagOut = typename geometry::tag_cast<TagOut, areal_tag, linear_tag, pointlike_tag>::type
>
struct intersection_insert
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPES_OR_ORIENTATIONS
            , (types<Geometry1, Geometry2, GeometryOut>)
        );
};


template
<
    typename Geometry1, typename Geometry2,
    typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename TagIn1, typename TagIn2, typename TagOut
>
struct intersection_insert
    <
        Geometry1, Geometry2,
        GeometryOut,
        OverlayType,
        Reverse1, Reverse2,
        TagIn1, TagIn2, TagOut,
        areal_tag, areal_tag, areal_tag
    > : detail::overlay::overlay
        <
            Geometry1, Geometry2, Reverse1, Reverse2,
            detail::overlay::do_reverse<geometry::point_order<GeometryOut>::value>::value,
            GeometryOut, OverlayType
        >
{};


// Any areal type with box:
template
<
    typename Geometry, typename Box,
    typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename TagIn, typename TagOut
>
struct intersection_insert
    <
        Geometry, Box,
        GeometryOut,
        OverlayType,
        Reverse1, Reverse2,
        TagIn, box_tag, TagOut,
        areal_tag, areal_tag, areal_tag
    > : detail::overlay::overlay
        <
            Geometry, Box, Reverse1, Reverse2,
            detail::overlay::do_reverse<geometry::point_order<GeometryOut>::value>::value,
            GeometryOut, OverlayType
        >
{};


template
<
    typename Segment1, typename Segment2,
    typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        Segment1, Segment2,
        GeometryOut,
        OverlayType,
        Reverse1, Reverse2,
        segment_tag, segment_tag, point_tag,
        linear_tag, linear_tag, pointlike_tag
    > : detail::intersection::intersection_segment_segment_point<GeometryOut>
{};


template
<
    typename Linestring1, typename Linestring2,
    typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        Linestring1, Linestring2,
        GeometryOut,
        OverlayType,
        Reverse1, Reverse2,
        linestring_tag, linestring_tag, point_tag,
        linear_tag, linear_tag, pointlike_tag
    > : detail::intersection::intersection_linestring_linestring_point<GeometryOut>
{};


template
<
    typename Linestring, typename Box,
    typename GeometryOut,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        Linestring, Box,
        GeometryOut,
        overlay_intersection,
        Reverse1, Reverse2,
        linestring_tag, box_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    >
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Linestring const& linestring,
            Box const& box,
            RobustPolicy const& robust_policy,
            OutputIterator out, Strategy const& )
    {
        typedef typename point_type<GeometryOut>::type point_type;
        strategy::intersection::liang_barsky<Box, point_type> lb_strategy;
        return detail::intersection::clip_range_with_box
            <GeometryOut>(box, linestring, robust_policy, out, lb_strategy);
    }
};


template
<
    typename Linestring, typename Polygon,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReverseLinestring, bool ReversePolygon
>
struct intersection_insert
    <
        Linestring, Polygon,
        GeometryOut,
        OverlayType,
        ReverseLinestring, ReversePolygon,
        linestring_tag, polygon_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::intersection_of_linestring_with_areal
            <
                ReversePolygon,
                GeometryOut,
                OverlayType,
                false
            >
{};


template
<
    typename Linestring, typename Ring,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReverseLinestring, bool ReverseRing
>
struct intersection_insert
    <
        Linestring, Ring,
        GeometryOut,
        OverlayType,
        ReverseLinestring, ReverseRing,
        linestring_tag, ring_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::intersection_of_linestring_with_areal
            <
                ReverseRing,
                GeometryOut,
                OverlayType,
                false
            >
{};

template
<
    typename Segment, typename Box,
    typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        Segment, Box,
        GeometryOut,
        OverlayType,
        Reverse1, Reverse2,
        segment_tag, box_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    >
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Segment const& segment,
            Box const& box,
            RobustPolicy const& robust_policy,
            OutputIterator out, Strategy const& )
    {
        geometry::segment_view<Segment> range(segment);

        typedef typename point_type<GeometryOut>::type point_type;
        strategy::intersection::liang_barsky<Box, point_type> lb_strategy;
        return detail::intersection::clip_range_with_box
            <GeometryOut>(box, range, robust_policy, out, lb_strategy);
    }
};

template
<
    typename Geometry1, typename Geometry2,
    typename PointOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename Tag1, typename Tag2
>
struct intersection_insert
    <
        Geometry1, Geometry2,
        PointOut,
        OverlayType,
        Reverse1, Reverse2,
        Tag1, Tag2, point_tag,
        areal_tag, areal_tag, pointlike_tag
    >
    : public detail::intersection::intersection_areal_areal_point
        <
            PointOut
        >
{};

template
<
    typename Geometry1, typename Geometry2,
    typename PointOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename Tag1, typename Tag2
>
struct intersection_insert
    <
        Geometry1, Geometry2,
        PointOut,
        OverlayType,
        Reverse1, Reverse2,
        Tag1, Tag2, point_tag,
        linear_tag, areal_tag, pointlike_tag
    >
    : public detail::intersection::intersection_linear_areal_point
        <
            PointOut
        >
{};

template
<
    typename Geometry1, typename Geometry2,
    typename PointOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename Tag1, typename Tag2
>
struct intersection_insert
    <
        Geometry1, Geometry2,
        PointOut,
        OverlayType,
        Reverse1, Reverse2,
        Tag1, Tag2, point_tag,
        areal_tag, linear_tag, pointlike_tag
    >
    : public detail::intersection::intersection_areal_linear_point
        <
            PointOut
        >
{};

template
<
    typename Geometry1, typename Geometry2, typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert_reversed
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry1 const& g1,
                Geometry2 const& g2,
                RobustPolicy const& robust_policy,
                OutputIterator out,
                Strategy const& strategy)
    {
        return intersection_insert
            <
                Geometry2, Geometry1, GeometryOut,
                OverlayType,
                Reverse2, Reverse1
            >::apply(g2, g1, robust_policy, out, strategy);
    }
};


// dispatch for intersection(areal, areal, linear)
template
<
    typename Geometry1, typename Geometry2,
    typename LinestringOut,
    bool Reverse1, bool Reverse2,
    typename Tag1, typename Tag2
>
struct intersection_insert
    <
        Geometry1, Geometry2,
        LinestringOut,
        overlay_intersection,
        Reverse1, Reverse2,
        Tag1, Tag2, linestring_tag,
        areal_tag, areal_tag, linear_tag
    >
{
    template
    <
        typename RobustPolicy, typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        detail::boundary_view<Geometry1 const> view1(geometry1);
        detail::boundary_view<Geometry2 const> view2(geometry2);

        return detail::overlay::linear_linear_linestring
            <
                detail::boundary_view<Geometry1 const>,
                detail::boundary_view<Geometry2 const>,
                LinestringOut,
                overlay_intersection
            >::apply(view1, view2, robust_policy, oit, strategy);
    }
};

// dispatch for difference/intersection of linear geometries
template
<
    typename Linear1, typename Linear2, typename LineStringOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename TagIn1, typename TagIn2
>
struct intersection_insert
    <
        Linear1, Linear2, LineStringOut, OverlayType,
        Reverse1, Reverse2,
        TagIn1, TagIn2, linestring_tag,
        linear_tag, linear_tag, linear_tag
    > : detail::overlay::linear_linear_linestring
        <
            Linear1, Linear2, LineStringOut, OverlayType
        >
{};

template
<
    typename Linear1, typename Linear2, typename TupledOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename TagIn1, typename TagIn2
>
struct intersection_insert
    <
        Linear1, Linear2, TupledOut, OverlayType,
        Reverse1, Reverse2,
        TagIn1, TagIn2, detail::intersection::tupled_output_tag,
        linear_tag, linear_tag, detail::intersection::tupled_output_tag
    >
    // NOTE: This is not fully correct because points can be the result only in
    // case of intersection but intersection_insert is called also by difference.
    // So this requirement could be relaxed in the future.
    : detail::intersection::expect_output_pl<Linear1, Linear2, TupledOut>
{
    // NOTE: The order of geometries in TupledOut tuple/pair must correspond to the order
    // iterators in OutputIterators tuple/pair.
    template
    <
        typename RobustPolicy, typename OutputIterators, typename Strategy
    >
    static inline OutputIterators apply(Linear1 const& linear1,
                                        Linear2 const& linear2,
                                        RobustPolicy const& robust_policy,
                                        OutputIterators oit,
                                        Strategy const& strategy)
    {
        return detail::overlay::linear_linear_linestring
            <
                Linear1, Linear2, TupledOut, OverlayType
            >::apply(linear1, linear2, robust_policy, oit, strategy);
    }
};


// dispatch for difference/intersection of point-like geometries

template
<
    typename Point1, typename Point2, typename PointOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        Point1, Point2, PointOut, OverlayType,
        Reverse1, Reverse2,
        point_tag, point_tag, point_tag,
        pointlike_tag, pointlike_tag, pointlike_tag
    > : detail::overlay::point_point_point
        <
            Point1, Point2, PointOut, OverlayType
        >
{};


template
<
    typename MultiPoint, typename Point, typename PointOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        MultiPoint, Point, PointOut, OverlayType,
        Reverse1, Reverse2,
        multi_point_tag, point_tag, point_tag,
        pointlike_tag, pointlike_tag, pointlike_tag
    > : detail::overlay::multipoint_point_point
        <
            MultiPoint, Point, PointOut, OverlayType
        >
{};


template
<
    typename Point, typename MultiPoint, typename PointOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        Point, MultiPoint, PointOut, OverlayType,
        Reverse1, Reverse2,
        point_tag, multi_point_tag, point_tag,
        pointlike_tag, pointlike_tag, pointlike_tag
    > : detail::overlay::point_multipoint_point
        <
            Point, MultiPoint, PointOut, OverlayType
        >
{};


template
<
    typename MultiPoint1, typename MultiPoint2, typename PointOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        MultiPoint1, MultiPoint2, PointOut, OverlayType,
        Reverse1, Reverse2,
        multi_point_tag, multi_point_tag, point_tag,
        pointlike_tag, pointlike_tag, pointlike_tag
    > : detail::overlay::multipoint_multipoint_point
        <
            MultiPoint1, MultiPoint2, PointOut, OverlayType
        >
{};


template
<
    typename PointLike1, typename PointLike2, typename TupledOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename TagIn1, typename TagIn2
>
struct intersection_insert
    <
        PointLike1, PointLike2, TupledOut, OverlayType,
        Reverse1, Reverse2,
        TagIn1, TagIn2, detail::intersection::tupled_output_tag,
        pointlike_tag, pointlike_tag, detail::intersection::tupled_output_tag
    >
    : detail::intersection::expect_output_p<PointLike1, PointLike2, TupledOut>
{
    // NOTE: The order of geometries in TupledOut tuple/pair must correspond to the order
    // of iterators in OutputIterators tuple/pair.
    template
    <
        typename RobustPolicy, typename OutputIterators, typename Strategy
    >
    static inline OutputIterators apply(PointLike1 const& pointlike1,
                                        PointLike2 const& pointlike2,
                                        RobustPolicy const& robust_policy,
                                        OutputIterators oits,
                                        Strategy const& strategy)
    {
        namespace bgt = boost::geometry::tuples;

        static const bool out_point_index = bgt::find_index_if
            <
                TupledOut, geometry::detail::is_tag_same_as_pred<point_tag>::template pred
            >::value;

        bgt::get<out_point_index>(oits) = intersection_insert
            <
                PointLike1, PointLike2,
                typename bgt::element
                    <
                        out_point_index, TupledOut
                    >::type,
                OverlayType
            >::apply(pointlike1, pointlike2, robust_policy,
                     bgt::get<out_point_index>(oits),
                     strategy);

        return oits;
    }
};


// dispatch for difference/intersection of pointlike-linear geometries
template
<
    typename Point, typename Linear, typename PointOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename Tag
>
struct intersection_insert
    <
        Point, Linear, PointOut, OverlayType,
        Reverse1, Reverse2,
        point_tag, Tag, point_tag,
        pointlike_tag, linear_tag, pointlike_tag
    > : detail_dispatch::overlay::pointlike_linear_point
        <
            Point, Linear, PointOut, OverlayType,
            point_tag, typename tag_cast<Tag, segment_tag, linear_tag>::type
        >
{};


template
<
    typename MultiPoint, typename Linear, typename PointOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename Tag
>
struct intersection_insert
    <
        MultiPoint, Linear, PointOut, OverlayType,
        Reverse1, Reverse2,
        multi_point_tag, Tag, point_tag,
        pointlike_tag, linear_tag, pointlike_tag
    > : detail_dispatch::overlay::pointlike_linear_point
        <
            MultiPoint, Linear, PointOut, OverlayType,
            multi_point_tag,
            typename tag_cast<Tag, segment_tag, linear_tag>::type
        >
{};


// This specialization is needed because intersection() reverses the arguments
// for MultiPoint/Linestring combination.
template
<
    typename Linestring, typename MultiPoint, typename PointOut,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        Linestring, MultiPoint, PointOut, overlay_intersection,
        Reverse1, Reverse2,
        linestring_tag, multi_point_tag, point_tag,
        linear_tag, pointlike_tag, pointlike_tag
    >
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Linestring const& linestring,
                                       MultiPoint const& multipoint,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        return detail_dispatch::overlay::pointlike_linear_point
            <
                MultiPoint, Linestring, PointOut, overlay_intersection,
                multi_point_tag, linear_tag
            >::apply(multipoint, linestring, robust_policy, out, strategy);
    }
};


template
<
    typename PointLike, typename Linear, typename TupledOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename TagIn1, typename TagIn2
>
struct intersection_insert
    <
        PointLike, Linear, TupledOut, OverlayType,
        Reverse1, Reverse2,
        TagIn1, TagIn2, detail::intersection::tupled_output_tag,
        pointlike_tag, linear_tag, detail::intersection::tupled_output_tag
    >
    // Reuse the implementation for PointLike/PointLike.
    : intersection_insert
        <
            PointLike, Linear, TupledOut, OverlayType,
            Reverse1, Reverse2,
            TagIn1, TagIn2, detail::intersection::tupled_output_tag,
            pointlike_tag, pointlike_tag, detail::intersection::tupled_output_tag
        >
{};


// This specialization is needed because intersection() reverses the arguments
// for MultiPoint/Linestring combination.
template
<
    typename Linestring, typename MultiPoint, typename TupledOut,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        Linestring, MultiPoint, TupledOut, overlay_intersection,
        Reverse1, Reverse2,
        linestring_tag, multi_point_tag, detail::intersection::tupled_output_tag,
        linear_tag, pointlike_tag, detail::intersection::tupled_output_tag
    >
{
    template <typename RobustPolicy, typename OutputIterators, typename Strategy>
    static inline OutputIterators apply(Linestring const& linestring,
                                        MultiPoint const& multipoint,
                                        RobustPolicy const& robust_policy,
                                        OutputIterators out,
                                        Strategy const& strategy)
    {
        return intersection_insert
            <
                MultiPoint, Linestring, TupledOut, overlay_intersection
            >::apply(multipoint, linestring, robust_policy, out, strategy);
    }
};


// dispatch for difference/intersection of pointlike-areal geometries
template
<
    typename Point, typename Areal, typename PointOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename ArealTag
>
struct intersection_insert
    <
        Point, Areal, PointOut, OverlayType,
        Reverse1, Reverse2,
        point_tag, ArealTag, point_tag,
        pointlike_tag, areal_tag, pointlike_tag
    > : detail_dispatch::overlay::pointlike_areal_point
        <
            Point, Areal, PointOut, OverlayType,
            point_tag, ArealTag
        >
{};

template
<
    typename MultiPoint, typename Areal, typename PointOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename ArealTag
>
struct intersection_insert
    <
        MultiPoint, Areal, PointOut, OverlayType,
        Reverse1, Reverse2,
        multi_point_tag, ArealTag, point_tag,
        pointlike_tag, areal_tag, pointlike_tag
    > : detail_dispatch::overlay::pointlike_areal_point
        <
            MultiPoint, Areal, PointOut, OverlayType,
            multi_point_tag, ArealTag
        >
{};

// This specialization is needed because intersection() reverses the arguments
// for MultiPoint/Ring and MultiPoint/Polygon combinations.
template
<
    typename Areal, typename MultiPoint, typename PointOut,
    bool Reverse1, bool Reverse2,
    typename ArealTag
>
struct intersection_insert
    <
        Areal, MultiPoint, PointOut, overlay_intersection,
        Reverse1, Reverse2,
        ArealTag, multi_point_tag, point_tag,
        areal_tag, pointlike_tag, pointlike_tag
    >
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Areal const& areal,
                                       MultiPoint const& multipoint,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        return detail_dispatch::overlay::pointlike_areal_point
            <
                MultiPoint, Areal, PointOut, overlay_intersection,
                multi_point_tag, ArealTag
            >::apply(multipoint, areal, robust_policy, out, strategy);
    }
};


template
<
    typename PointLike, typename Areal, typename TupledOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2,
    typename TagIn1, typename TagIn2
>
struct intersection_insert
    <
        PointLike, Areal, TupledOut, OverlayType,
        Reverse1, Reverse2,
        TagIn1, TagIn2, detail::intersection::tupled_output_tag,
        pointlike_tag, areal_tag, detail::intersection::tupled_output_tag
    >
    // Reuse the implementation for PointLike/PointLike.
    : intersection_insert
        <
            PointLike, Areal, TupledOut, OverlayType,
            Reverse1, Reverse2,
            TagIn1, TagIn2, detail::intersection::tupled_output_tag,
            pointlike_tag, pointlike_tag, detail::intersection::tupled_output_tag
        >
{};


// This specialization is needed because intersection() reverses the arguments
// for MultiPoint/Ring and MultiPoint/Polygon combinations.
template
<
    typename Areal, typename MultiPoint, typename TupledOut,
    bool Reverse1, bool Reverse2,
    typename TagIn1
>
struct intersection_insert
    <
        Areal, MultiPoint, TupledOut, overlay_intersection,
        Reverse1, Reverse2,
        TagIn1, multi_point_tag, detail::intersection::tupled_output_tag,
        areal_tag, pointlike_tag, detail::intersection::tupled_output_tag
    >
{
    template <typename RobustPolicy, typename OutputIterators, typename Strategy>
    static inline OutputIterators apply(Areal const& areal,
                                        MultiPoint const& multipoint,
                                        RobustPolicy const& robust_policy,
                                        OutputIterators out,
                                        Strategy const& strategy)
    {
        return intersection_insert
            <
                MultiPoint, Areal, TupledOut, overlay_intersection
            >::apply(multipoint, areal, robust_policy, out, strategy);
    }
};


template
<
    typename Linestring, typename Polygon,
    typename TupledOut,
    overlay_type OverlayType,
    bool ReverseLinestring, bool ReversePolygon
>
struct intersection_insert
    <
        Linestring, Polygon,
        TupledOut,
        OverlayType,
        ReverseLinestring, ReversePolygon,
        linestring_tag, polygon_tag, detail::intersection::tupled_output_tag,
        linear_tag, areal_tag, detail::intersection::tupled_output_tag
    > : detail::intersection::intersection_of_linestring_with_areal
            <
                ReversePolygon,
                TupledOut,
                OverlayType,
                true
            >
{};

template
<
    typename Linestring, typename Ring,
    typename TupledOut,
    overlay_type OverlayType,
    bool ReverseLinestring, bool ReverseRing
>
struct intersection_insert
    <
        Linestring, Ring,
        TupledOut,
        OverlayType,
        ReverseLinestring, ReverseRing,
        linestring_tag, ring_tag, detail::intersection::tupled_output_tag,
        linear_tag, areal_tag, detail::intersection::tupled_output_tag
    > : detail::intersection::intersection_of_linestring_with_areal
            <
                ReverseRing,
                TupledOut,
                OverlayType,
                true
            >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace intersection
{


template
<
    typename GeometryOut,
    bool ReverseSecond,
    overlay_type OverlayType,
    typename Geometry1, typename Geometry2,
    typename RobustPolicy,
    typename OutputIterator,
    typename Strategy
>
inline OutputIterator insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            RobustPolicy robust_policy,
            OutputIterator out,
            Strategy const& strategy)
{
    return boost::mpl::if_c
    <
        geometry::reverse_dispatch<Geometry1, Geometry2>::type::value,
        geometry::dispatch::intersection_insert_reversed
        <
            Geometry1, Geometry2,
            GeometryOut,
            OverlayType,
            overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
            overlay::do_reverse<geometry::point_order<Geometry2>::value, ReverseSecond>::value
        >,
        geometry::dispatch::intersection_insert
        <
            Geometry1, Geometry2,
            GeometryOut,
            OverlayType,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry2>::value, ReverseSecond>::value
        >
    >::type::apply(geometry1, geometry2, robust_policy, out, strategy);
}


/*!
\brief \brief_calc2{intersection} \brief_strategy
\ingroup intersection
\details \details_calc2{intersection_insert, spatial set theoretic intersection}
    \brief_strategy. \details_insert{intersection}
\tparam GeometryOut \tparam_geometry{\p_l_or_c}
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam OutputIterator \tparam_out{\p_l_or_c}
\tparam Strategy \tparam_strategy_overlay
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param out \param_out{intersection}
\param strategy \param_strategy{intersection}
\return \return_out

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/intersection.qbk]}
*/
template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator,
    typename Strategy
>
inline OutputIterator intersection_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out,
            Strategy const& strategy)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    typedef typename geometry::rescale_overlay_policy_type
        <
            Geometry1,
            Geometry2,
            typename Strategy::cs_tag
        >::type rescale_policy_type;

    rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(
                geometry1, geometry2, strategy);

    return detail::intersection::insert
        <
            GeometryOut, false, overlay_intersection
        >(geometry1, geometry2, robust_policy, out, strategy);
}


/*!
\brief \brief_calc2{intersection}
\ingroup intersection
\details \details_calc2{intersection_insert, spatial set theoretic intersection}.
    \details_insert{intersection}
\tparam GeometryOut \tparam_geometry{\p_l_or_c}
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam OutputIterator \tparam_out{\p_l_or_c}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param out \param_out{intersection}
\return \return_out

\qbk{[include reference/algorithms/intersection.qbk]}
*/
template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator
>
inline OutputIterator intersection_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    typedef typename strategy::intersection::services::default_strategy
        <
            typename cs_tag<GeometryOut>::type
        >::type strategy_type;
    
    return intersection_insert<GeometryOut>(geometry1, geometry2, out,
                                            strategy_type());
}

}} // namespace detail::intersection
#endif // DOXYGEN_NO_DETAIL



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INTERSECTION_INSERT_HPP

/* intersection_insert.hpp
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
*/
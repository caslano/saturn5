// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_MULTI_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_MULTI_HPP

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/geometry_id.hpp>
#include <boost/geometry/core/is_areal.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>

// TODO: those headers probably may be removed
#include <boost/geometry/algorithms/detail/overlay/get_ring.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segments.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segment_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/select_rings.hpp>
#include <boost/geometry/algorithms/detail/sections/range_by_section.hpp>
#include <boost/geometry/algorithms/detail/sections/sectionalize.hpp>

#include <boost/geometry/algorithms/detail/intersection/interface.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/num_points.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace intersection
{


template <typename PointOut>
struct intersection_multi_linestring_multi_linestring_point
{
    template
    <
        typename MultiLinestring1, typename MultiLinestring2,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(MultiLinestring1 const& ml1,
            MultiLinestring2 const& ml2,
            RobustPolicy const& robust_policy,
            OutputIterator out,
            Strategy const& strategy)
    {
        // Note, this loop is quadratic w.r.t. number of linestrings per input.
        // Future Enhancement: first do the sections of each, then intersect.
        for (typename boost::range_iterator
                <
                    MultiLinestring1 const
                >::type it1 = boost::begin(ml1);
            it1 != boost::end(ml1);
            ++it1)
        {
            for (typename boost::range_iterator
                    <
                        MultiLinestring2 const
                    >::type it2 = boost::begin(ml2);
                it2 != boost::end(ml2);
                ++it2)
            {
                out = intersection_linestring_linestring_point<PointOut>
                      ::apply(*it1, *it2, robust_policy, out, strategy);
            }
        }

        return out;
    }
};


template <typename PointOut>
struct intersection_linestring_multi_linestring_point
{
    template
    <
        typename Linestring, typename MultiLinestring,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Linestring const& linestring,
            MultiLinestring const& ml,
            RobustPolicy const& robust_policy,
            OutputIterator out,
            Strategy const& strategy)
    {
        for (typename boost::range_iterator
                <
                    MultiLinestring const
                >::type it = boost::begin(ml);
            it != boost::end(ml);
            ++it)
        {
            out = intersection_linestring_linestring_point<PointOut>
                  ::apply(linestring, *it, robust_policy, out, strategy);
        }

        return out;
    }
};


// This loop is quite similar to the loop above, but beacuse the iterator
// is second (above) or first (below) argument, it is not trivial to merge them.
template
<
    bool ReverseAreal,
    typename LineStringOut,
    overlay_type OverlayType,
    bool FollowIsolatedPoints
>
struct intersection_of_multi_linestring_with_areal
{
    template
    <
        typename MultiLinestring, typename Areal,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(MultiLinestring const& ml, Areal const& areal,
            RobustPolicy const& robust_policy,
            OutputIterator out,
            Strategy const& strategy)
    {
        for (typename boost::range_iterator
                <
                    MultiLinestring const
                >::type it = boost::begin(ml);
            it != boost::end(ml);
            ++it)
        {
            out = intersection_of_linestring_with_areal
                <
                    ReverseAreal, LineStringOut, OverlayType, FollowIsolatedPoints
                >::apply(*it, areal, robust_policy, out, strategy);
        }

        return out;

    }
};

// This one calls the one above with reversed arguments
template
<
    bool ReverseAreal,
    typename LineStringOut,
    overlay_type OverlayType,
    bool FollowIsolatedPoints
>
struct intersection_of_areal_with_multi_linestring
{
    template
    <
        typename Areal, typename MultiLinestring,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(Areal const& areal, MultiLinestring const& ml,
            RobustPolicy const& robust_policy,
            OutputIterator out,
            Strategy const& strategy)
    {
        return intersection_of_multi_linestring_with_areal
            <
                ReverseAreal, LineStringOut, OverlayType, FollowIsolatedPoints
            >::apply(ml, areal, robust_policy, out, strategy);
    }
};



template <typename LinestringOut>
struct clip_multi_linestring
{
    template
    <
        typename MultiLinestring, typename Box,
        typename RobustPolicy,
        typename OutputIterator, typename Strategy
    >
    static inline OutputIterator apply(MultiLinestring const& multi_linestring,
            Box const& box,
            RobustPolicy const& robust_policy,
            OutputIterator out, Strategy const& )
    {
        typedef typename point_type<LinestringOut>::type point_type;
        strategy::intersection::liang_barsky<Box, point_type> lb_strategy;
        for (typename boost::range_iterator<MultiLinestring const>::type it
            = boost::begin(multi_linestring);
            it != boost::end(multi_linestring); ++it)
        {
            out = detail::intersection::clip_range_with_box
                <LinestringOut>(box, *it, robust_policy, out, lb_strategy);
        }
        return out;
    }
};


}} // namespace detail::intersection
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Linear
template
<
    typename MultiLinestring1, typename MultiLinestring2,
    typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        MultiLinestring1, MultiLinestring2,
        GeometryOut,
        OverlayType,
        Reverse1, Reverse2,
        multi_linestring_tag, multi_linestring_tag, point_tag,
        linear_tag, linear_tag, pointlike_tag
    > : detail::intersection::intersection_multi_linestring_multi_linestring_point
            <
                GeometryOut
            >
{};


template
<
    typename Linestring, typename MultiLinestring,
    typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        Linestring, MultiLinestring,
        GeometryOut,
        OverlayType,
        Reverse1, Reverse2,
        linestring_tag, multi_linestring_tag, point_tag,
        linear_tag, linear_tag, pointlike_tag
    > : detail::intersection::intersection_linestring_multi_linestring_point
            <
                GeometryOut
            >
{};


template
<
    typename MultiLinestring, typename Box,
    typename GeometryOut,
    overlay_type OverlayType,
    bool Reverse1, bool Reverse2
>
struct intersection_insert
    <
        MultiLinestring, Box,
        GeometryOut,
        OverlayType,
        Reverse1, Reverse2,
        multi_linestring_tag, box_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::clip_multi_linestring
            <
                GeometryOut
            >
{};


template
<
    typename Linestring, typename MultiPolygon,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReverseLinestring, bool ReverseMultiPolygon
>
struct intersection_insert
    <
        Linestring, MultiPolygon,
        GeometryOut,
        OverlayType,
        ReverseLinestring, ReverseMultiPolygon,
        linestring_tag, multi_polygon_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::intersection_of_linestring_with_areal
            <
                ReverseMultiPolygon,
                GeometryOut,
                OverlayType,
                false
            >
{};


// Derives from areal/mls because runtime arguments are in that order.
// areal/mls reverses it itself to mls/areal
template
<
    typename Polygon, typename MultiLinestring,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReversePolygon, bool ReverseMultiLinestring
>
struct intersection_insert
    <
        Polygon, MultiLinestring,
        GeometryOut,
        OverlayType,
        ReversePolygon, ReverseMultiLinestring,
        polygon_tag, multi_linestring_tag, linestring_tag,
        areal_tag, linear_tag, linear_tag
    > : detail::intersection::intersection_of_areal_with_multi_linestring
            <
                ReversePolygon,
                GeometryOut,
                OverlayType,
                false
            >
{};


template
<
    typename MultiLinestring, typename Ring,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReverseRing
>
struct intersection_insert
    <
        MultiLinestring, Ring,
        GeometryOut,
        OverlayType,
        ReverseMultiLinestring, ReverseRing,
        multi_linestring_tag, ring_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReverseRing,
                GeometryOut,
                OverlayType,
                false
            >
{};

template
<
    typename MultiLinestring, typename Polygon,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReversePolygon
>
struct intersection_insert
    <
        MultiLinestring, Polygon,
        GeometryOut,
        OverlayType,
        ReverseMultiLinestring, ReversePolygon,
        multi_linestring_tag, polygon_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReversePolygon,
                GeometryOut,
                OverlayType,
                false
            >
{};



template
<
    typename MultiLinestring, typename MultiPolygon,
    typename GeometryOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReverseMultiPolygon
>
struct intersection_insert
    <
        MultiLinestring, MultiPolygon,
        GeometryOut,
        OverlayType,
        ReverseMultiLinestring, ReverseMultiPolygon,
        multi_linestring_tag, multi_polygon_tag, linestring_tag,
        linear_tag, areal_tag, linear_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReverseMultiPolygon,
                GeometryOut,
                OverlayType,
                false
            >
{};



template
<
    typename MultiLinestring, typename Ring,
    typename TupledOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReverseRing
>
struct intersection_insert
    <
        MultiLinestring, Ring,
        TupledOut,
        OverlayType,
        ReverseMultiLinestring, ReverseRing,
        multi_linestring_tag, ring_tag, detail::intersection::tupled_output_tag,
        linear_tag, areal_tag, detail::intersection::tupled_output_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReverseRing,
                TupledOut,
                OverlayType,
                true
            >
      , detail::intersection::expect_output_pl<MultiLinestring, Ring, TupledOut>
{};


template
<
    typename MultiLinestring, typename Polygon,
    typename TupledOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReversePolygon
>
struct intersection_insert
    <
        MultiLinestring, Polygon,
        TupledOut,
        OverlayType,
        ReverseMultiLinestring, ReversePolygon,
        multi_linestring_tag, polygon_tag, detail::intersection::tupled_output_tag,
        linear_tag, areal_tag, detail::intersection::tupled_output_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReversePolygon,
                TupledOut,
                OverlayType,
                true
            >
    , detail::intersection::expect_output_pl<MultiLinestring, Polygon, TupledOut>
{};

template
<
    typename Polygon, typename MultiLinestring,
    typename TupledOut,
    overlay_type OverlayType,
    bool ReversePolygon, bool ReverseMultiLinestring
>
struct intersection_insert
    <
        Polygon, MultiLinestring,
        TupledOut,
        OverlayType,
        ReversePolygon, ReverseMultiLinestring,
        polygon_tag, multi_linestring_tag, detail::intersection::tupled_output_tag,
        areal_tag, linear_tag, detail::intersection::tupled_output_tag
    > : detail::intersection::intersection_of_areal_with_multi_linestring
            <
                ReversePolygon,
                TupledOut,
                OverlayType,
                true
            >
    , detail::intersection::expect_output_pl<Polygon, MultiLinestring, TupledOut>
{};

template
<
    typename MultiLinestring, typename MultiPolygon,
    typename TupledOut,
    overlay_type OverlayType,
    bool ReverseMultiLinestring, bool ReverseMultiPolygon
>
struct intersection_insert
    <
        MultiLinestring, MultiPolygon,
        TupledOut,
        OverlayType,
        ReverseMultiLinestring, ReverseMultiPolygon,
        multi_linestring_tag, multi_polygon_tag, detail::intersection::tupled_output_tag,
        linear_tag, areal_tag, detail::intersection::tupled_output_tag
    > : detail::intersection::intersection_of_multi_linestring_with_areal
            <
                ReverseMultiPolygon,
                TupledOut,
                OverlayType,
                true
            >
    , detail::intersection::expect_output_pl<MultiLinestring, MultiPolygon, TupledOut>
{};


} // namespace dispatch
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_MULTI_HPP


/* multi.hpp
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
*/
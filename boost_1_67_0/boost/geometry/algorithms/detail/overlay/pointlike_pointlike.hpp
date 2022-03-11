// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_POINTLIKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_POINTLIKE_HPP

#include <algorithm>
#include <vector>

#include <boost/range.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>

#include <boost/geometry/policies/compare.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


// struct for copying points of the pointlike geometries to output
template
<
    typename PointOut,
    typename GeometryIn,
    typename TagIn = typename tag<GeometryIn>::type
>
struct copy_points
    : not_implemented<PointOut, GeometryIn>
{};

template <typename PointOut, typename PointIn>
struct copy_points<PointOut, PointIn, point_tag>
{
    template <typename OutputIterator>
    static inline void apply(PointIn const& point_in,
                             OutputIterator& oit)
    {
        PointOut point_out;
        geometry::convert(point_in, point_out);
        *oit++ = point_out;
    }
};


template <typename PointOut, typename MultiPointIn>
struct copy_points<PointOut, MultiPointIn, multi_point_tag>
{
    template <typename OutputIterator>
    static inline void apply(MultiPointIn const& multi_point_in,
                             OutputIterator& oit)
    {
        for (typename boost::range_iterator<MultiPointIn const>::type
                 it = boost::begin(multi_point_in);
             it != boost::end(multi_point_in); ++it)
        {
            PointOut point_out;
            geometry::convert(*it, point_out);
            *oit++ = point_out;
        }
    }
};



// action struct for difference/intersection
template <typename PointOut, overlay_type OverlayType>
struct action_selector_pl
{};

template <typename PointOut>
struct action_selector_pl<PointOut, overlay_intersection>
{
    template
    <
        typename Point,
        typename OutputIterator
    >
    static inline void apply(Point const& point,
                             bool is_common,
                             OutputIterator& oit)
    {
        if ( is_common )
        {
            copy_points<PointOut, Point>::apply(point, oit);
        }
    }
};



template <typename PointOut>
struct action_selector_pl<PointOut, overlay_difference>
{
    template
    <
        typename Point,
        typename OutputIterator
    >
    static inline void apply(Point const& point,
                             bool is_common,
                             OutputIterator& oit)
    {
        if ( !is_common )
        {
            copy_points<PointOut, Point>::apply(point, oit);
        }
    }
};


//===========================================================================

// difference/intersection of point-point
template
<
    typename Point1,
    typename Point2,
    typename PointOut,
    overlay_type OverlayType
>
struct point_point_point
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Point1 const& point1,
                                       Point2 const& point2,
                                       RobustPolicy const& ,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        action_selector_pl
            <
                PointOut, OverlayType
            >::apply(point1,
                     detail::equals::equals_point_point(point1, point2, strategy),
                     oit);

        return oit;
    }
};



// difference of multipoint-point
//
// the apply method in the following struct is called only for
// difference; for intersection the reversal will
// always call the point-multipoint version
template
<
    typename MultiPoint,
    typename Point,
    typename PointOut,
    overlay_type OverlayType
>
struct multipoint_point_point
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(MultiPoint const& multipoint,
                                       Point const& point,
                                       RobustPolicy const& ,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        BOOST_GEOMETRY_ASSERT( OverlayType == overlay_difference );

        for (typename boost::range_iterator<MultiPoint const>::type
                 it = boost::begin(multipoint);
             it != boost::end(multipoint); ++it)
        {
            action_selector_pl
                <
                    PointOut, OverlayType
                >::apply(*it,
                         detail::equals::equals_point_point(*it, point, strategy),
                         oit);
        }

        return oit;
    }
};


// difference/intersection of point-multipoint
template
<
    typename Point,
    typename MultiPoint,
    typename PointOut,
    overlay_type OverlayType
>
struct point_multipoint_point
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Point const& point,
                                       MultiPoint const& multipoint,
                                       RobustPolicy const& ,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        typedef action_selector_pl<PointOut, OverlayType> action;

        for (typename boost::range_iterator<MultiPoint const>::type
                 it = boost::begin(multipoint);
             it != boost::end(multipoint); ++it)
        {
            if ( detail::equals::equals_point_point(*it, point, strategy) )
            {
                action::apply(point, true, oit);
                return oit;
            }
        }

        action::apply(point, false, oit);
        return oit;
    }
};



// difference/intersection of multipoint-multipoint
template
<
    typename MultiPoint1,
    typename MultiPoint2,
    typename PointOut,
    overlay_type OverlayType
>
struct multipoint_multipoint_point
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(MultiPoint1 const& multipoint1,
                                       MultiPoint2 const& multipoint2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        typedef geometry::less<void, -1, typename Strategy::cs_tag> less_type;

        if ( OverlayType != overlay_difference
             && boost::size(multipoint1) > boost::size(multipoint2) )
        {
            return multipoint_multipoint_point
                <
                    MultiPoint2, MultiPoint1, PointOut, OverlayType
                >::apply(multipoint2, multipoint1, robust_policy, oit, strategy);
        }

        typedef typename boost::range_value<MultiPoint2>::type point2_type;

        std::vector<point2_type> points2(boost::begin(multipoint2),
                                         boost::end(multipoint2));

        less_type const less = less_type();
        std::sort(points2.begin(), points2.end(), less);

        for (typename boost::range_iterator<MultiPoint1 const>::type
                 it1 = boost::begin(multipoint1);
             it1 != boost::end(multipoint1); ++it1)
        {
            bool found = std::binary_search(points2.begin(), points2.end(),
                                            *it1, less);

            action_selector_pl
                <
                    PointOut, OverlayType
                >::apply(*it1, found, oit);
        }
        return oit;
    }
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


//===========================================================================


#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch { namespace overlay
{

// dispatch struct for pointlike-pointlike difference/intersection
// computation
template
<
    typename PointLike1,
    typename PointLike2,
    typename PointOut,
    overlay_type OverlayType,
    typename Tag1,
    typename Tag2
>
struct pointlike_pointlike_point
    : not_implemented<PointLike1, PointLike2, PointOut>
{};


template
<
    typename Point1,
    typename Point2,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_pointlike_point
    <
        Point1, Point2, PointOut, OverlayType,
        point_tag, point_tag
    > : detail::overlay::point_point_point
        <
            Point1, Point2, PointOut, OverlayType
        >
{};


template
<
    typename Point,
    typename MultiPoint,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_pointlike_point
    <
        Point, MultiPoint, PointOut, OverlayType,
        point_tag, multi_point_tag
    > : detail::overlay::point_multipoint_point
        <
            Point, MultiPoint, PointOut, OverlayType
        >
{};


template
<
    typename MultiPoint,
    typename Point,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_pointlike_point
    <
        MultiPoint, Point, PointOut, OverlayType,
        multi_point_tag, point_tag
    > : detail::overlay::multipoint_point_point
        <
            MultiPoint, Point, PointOut, OverlayType
        >
{};


template
<
    typename MultiPoint1,
    typename MultiPoint2,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_pointlike_point
    <
        MultiPoint1, MultiPoint2, PointOut, OverlayType,
        multi_point_tag, multi_point_tag
    > : detail::overlay::multipoint_multipoint_point
        <
            MultiPoint1, MultiPoint2, PointOut, OverlayType
        >
{};


}} // namespace detail_dispatch::overlay
#endif // DOXYGEN_NO_DISPATCH


//===========================================================================


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


// generic pointlike-pointlike union implementation
template
<
    typename PointLike1,
    typename PointLike2,
    typename PointOut
>
struct union_pointlike_pointlike_point
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(PointLike1 const& pointlike1,
                                       PointLike2 const& pointlike2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        copy_points<PointOut, PointLike1>::apply(pointlike1, oit);

        return detail_dispatch::overlay::pointlike_pointlike_point
            <
                PointLike2, PointLike1, PointOut, overlay_difference,
                typename tag<PointLike2>::type,
                typename tag<PointLike1>::type
            >::apply(pointlike2, pointlike1, robust_policy, oit, strategy);
    }

};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_POINTLIKE_HPP

/* pointlike_pointlike.hpp
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
*/
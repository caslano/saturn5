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

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

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
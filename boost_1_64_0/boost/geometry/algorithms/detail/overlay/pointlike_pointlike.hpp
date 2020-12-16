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
G7I9TQ2e6oMWinBXa6M95npPeAwkRy23Q1lrDezZaOWyQ9yxS+fTjAHug00K9+zWuN9GHl20bstcv96kNvHD4dkiQzxWUEyuEJZmis1OUb07NMmmXTrFrA7Vw7Nh0HacI3e3GA9B7sbQuEzfkCae77HZGL+jN+Tr06z9XraUWbIzvCFLHzSk1nuKaj1G6679FDG8IXcfm1wyqVYgOztn1ImZ1B9rYq6DrP8lk1RUh4xKdjjjEFEmZlKfGIvXNId2L47faQsqWIP2P5xuv2sB6b7gyx5l/fF+ZSx2imq9VxsJfpnc9E6SdclozK/HJ+5kJICGCAB9tVGELH0Zka/IJazqJTFrc6j+mwGQ1a4u3riqSFXzzN8q0RNUqRyhPpI8yd2AFtlIO1V6apkD+SDPM+j0T0R+i1V+s2R+fy6JviKZ3xl6fpcjv8Xx/NJXC19H7PRlRL4inQCfYXzgXJBAlSdRFQGVU6H6/edE9RhRmRQqRpF1fypqFOiccXQM0foQnfRlZL7E+KzQuCz4lSg/vvC1VH3xRfFmvFRfsE5WwswqGC8GV8SDP5gkgytUMF78qpSZvXe58lRfP+SXuLOKx9R3VKl4dSoCX9r5T6vDkzmQL0Hax1UivrRz9KDxCALyeh35Ka7K1Wrg3P8ZhvtIVR8ylLFPkLHXNJx05N99//BtP3L+PymhP1zzbEw9RplzL63m/Bdch+4kOItpL/vMBnk2ZP8RWa6cKLTIRMWcrHlMKtJ6VP/s+in6pxKeu9bLCGKGCmj+hAEHGTBNBSxQATtlwCEGnKsC8lTAGhnwhdxpqgB2Pu16n3RX0D2X7rCQks8HnqCBCiE7zG66hdB5i7dIQCYGbPUwsSrU+xPpbVVxZn6iSvO8x9yOBfQ4n5i+1iW/k/VMejq2UL2znz3XEzfInkP73PDj3HMeF4tHku1fIl5Mc8oTrMquDcbXqRBVhH9lpSvI8VYbrNKDaJuUb2YgMsHMCLGVaRSQFevIvK2RjfWweiaoAXbuflU9y8cn5UDUfEMqW3LXHNOWOvuZmJiRT2pIBbqopdCptIOUdo43PCub9EkeMpEbxcY4fxhoofwSW2Aa+MGoG6wyB9KXaDz/lYuXzeDvgXWO00ZnqnysQE1ITm+0Vq1J0fQlW+P6fgCcjNKrm72L7PKG+ijXm69+jafVUYn76RjJ6qNs1X6dcC2NEa63K8I1h1s7WJtubfKSLH4qlyzhcUPUJXZqr4yTm5aC5POvTdqf4Auy102yTvJh3uQi+OijkvgNjFa7ltA4uWsBb6GIu5YLPGYwjsfHKMvQLQ55pOATQNYyH+hKPfeqrtRVp50viNPOTYXyeOzr9xT1JItupD+V4Ffvp7yKPenWy5GYB8B3UQpdVfFR5u+H8oNKZ/lPQBSk6ofCXjledfLdqIO2qp9fQ4nTE/oxFlmaO+PqWnNs/pEs2dAnZclgdKVSLasHXuAEaC/c6kIfgWlw0bmTdjnzHDq9AJKNGegfait5PjyTs3ut3p3bm2efqGYfvCp40Biw5G6JfCd40BS4BIcBCXLYO6QuJS0cXRU8mH7LmZ656zgAbxnkCbtIG5d6wxZMG5DeSfcES2yGgCN5mH6QW4UxpvpYO7L3aqVH8r+f0LnOP1YXQt6uqAkuYLyUga4cqakGIz5uZFBshhJ59CfEgorw1BwL/tO/jcF3tgd+7pb2AU8lfzRGoXJR1X2rUgyFFIZYpw38BYzNWrUC3LQo6sFZGVx6iJbb7OVXcoGOTrGHZ8HRtrNWWgEWVtkn1+MufQ8tO1lHR8hdtlQED3Wwl1FgMXioo73sAemw+5eEg9EoZwLTjRe5CpqXjJbMxUZnpiUwQng=
*/
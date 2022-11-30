// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_LINEAR_HPP

#include <iterator>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/disjoint.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/not.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_geometry.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/pointlike_pointlike.hpp>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>

// TEMP
#include <boost/geometry/strategies/envelope/cartesian.hpp>
#include <boost/geometry/strategies/envelope/geographic.hpp>
#include <boost/geometry/strategies/envelope/spherical.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


// difference/intersection of point-linear
template
<
    typename Point,
    typename Geometry,
    typename PointOut,
    overlay_type OverlayType,
    typename Policy
>
struct point_single_point
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Point const& point,
                                       Geometry const& geometry,
                                       RobustPolicy const&,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        action_selector_pl
            <
                PointOut, OverlayType
            >::apply(point, Policy::apply(point, geometry, strategy), oit);
        return oit;
    }
};

// difference/intersection of multipoint-segment
template
<
    typename MultiPoint,
    typename Geometry,
    typename PointOut,
    overlay_type OverlayType,
    typename Policy
>
struct multipoint_single_point
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(MultiPoint const& multipoint,
                                       Geometry const& geometry,
                                       RobustPolicy const&,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        for (typename boost::range_iterator<MultiPoint const>::type
                 it = boost::begin(multipoint);
             it != boost::end(multipoint);
             ++it)
        {
            action_selector_pl
                <
                    PointOut, OverlayType
                >::apply(*it, Policy::apply(*it, geometry, strategy), oit);
        }

        return oit;
    }
};


// difference/intersection of multipoint-linear
template
<
    typename MultiPoint,
    typename Linear,
    typename PointOut,
    overlay_type OverlayType,
    typename Policy
>
class multipoint_linear_point
{
private:
    // structs for partition -- start
    template <typename Strategy>
    struct expand_box_point
    {
        expand_box_point(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Point>
        inline void apply(Box& total, Point const& point) const
        {
            geometry::expand(total, point, m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct expand_box_segment
    {
        explicit expand_box_segment(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Segment>
        inline void apply(Box& total, Segment const& segment) const
        {
            geometry::expand(total,
                             geometry::return_envelope<Box>(segment, m_strategy),
                             m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct overlaps_box_point
    {
        explicit overlaps_box_point(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Point>
        inline bool apply(Box const& box, Point const& point) const
        {
            return ! geometry::disjoint(point, box, m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct overlaps_box_segment
    {
        explicit overlaps_box_segment(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Segment>
        inline bool apply(Box const& box, Segment const& segment) const
        {
            return ! geometry::disjoint(segment, box, m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename OutputIterator, typename Strategy>
    class item_visitor_type
    {
    public:
        item_visitor_type(OutputIterator& oit, Strategy const& strategy)
            : m_oit(oit)
            , m_strategy(strategy)
        {}

        template <typename Item1, typename Item2>
        inline bool apply(Item1 const& item1, Item2 const& item2)
        {
            action_selector_pl
                <
                    PointOut, overlay_intersection
                >::apply(item1, Policy::apply(item1, item2, m_strategy), m_oit);

            return true;
        }

    private:
        OutputIterator& m_oit;
        Strategy const& m_strategy;
    };
    // structs for partition -- end

    class segment_range
    {
    public:
        typedef geometry::segment_iterator<Linear const> const_iterator;
        typedef const_iterator iterator;

        explicit segment_range(Linear const& linear)
            : m_linear(linear)
        {}

        const_iterator begin() const
        {
            return geometry::segments_begin(m_linear);
        }

        const_iterator end() const
        {
            return geometry::segments_end(m_linear);
        }

    private:
        Linear const& m_linear;
    };

    template <typename OutputIterator, typename Strategy>
    static inline OutputIterator get_common_points(MultiPoint const& multipoint,
                                                   Linear const& linear,
                                                   OutputIterator oit,
                                                   Strategy const& strategy)
    {
        item_visitor_type<OutputIterator, Strategy> item_visitor(oit, strategy);

        // TODO: disjoint Segment/Box may be called in partition multiple times
        // possibly for non-cartesian segments which could be slow. We should consider
        // passing a range of bounding boxes of segments after calculating them once.
        // Alternatively instead of a range of segments a range of Segment/Envelope pairs
        // should be passed, where envelope would be lazily calculated when needed the first time
        geometry::partition
            <
                geometry::model::box
                    <
                        typename boost::range_value<MultiPoint>::type
                    >
            >::apply(multipoint, segment_range(linear), item_visitor,
                     expand_box_point<Strategy>(strategy),
                     overlaps_box_point<Strategy>(strategy),
                     expand_box_segment<Strategy>(strategy),
                     overlaps_box_segment<Strategy>(strategy));

        return oit;
    }

public:
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(MultiPoint const& multipoint,
                                       Linear const& linear,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        typedef std::vector
            <
                typename boost::range_value<MultiPoint>::type
            > point_vector_type;

        point_vector_type common_points;

        // compute the common points
        get_common_points(multipoint, linear,
                          std::back_inserter(common_points),
                          strategy);

        return multipoint_multipoint_point
            <
                MultiPoint, point_vector_type, PointOut, OverlayType
            >::apply(multipoint, common_points, robust_policy, oit, strategy);
    }
};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch { namespace overlay
{

// dispatch struct for pointlike-linear difference/intersection computation
template
<
    typename PointLike,
    typename Linear,
    typename PointOut,
    overlay_type OverlayType,
    typename Tag1,
    typename Tag2
>
struct pointlike_linear_point
    : not_implemented<PointLike, Linear, PointOut>
{};


template
<
    typename Point,
    typename Linear,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_linear_point
    <
        Point, Linear, PointOut, OverlayType, point_tag, linear_tag
    > : detail::overlay::point_single_point
        <
            Point, Linear, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


template
<
    typename Point,
    typename Segment,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_linear_point
    <
        Point, Segment, PointOut, OverlayType, point_tag, segment_tag
    > : detail::overlay::point_single_point
        <
            Point, Segment, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


template
<
    typename MultiPoint,
    typename Linear,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_linear_point
    <
        MultiPoint, Linear, PointOut, OverlayType, multi_point_tag, linear_tag
    > : detail::overlay::multipoint_linear_point
        <
            MultiPoint, Linear, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


template
<
    typename MultiPoint,
    typename Segment,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_linear_point
    <
        MultiPoint, Segment, PointOut, OverlayType, multi_point_tag, segment_tag
    > : detail::overlay::multipoint_single_point
        <
            MultiPoint, Segment, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


}} // namespace detail_dispatch::overlay
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_LINEAR_HPP

/* pointlike_linear.hpp
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
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_AREAL_HPP

#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
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

#include <boost/geometry/algorithms/detail/overlay/pointlike_linear.hpp>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>

// TEMP
#include <boost/geometry/strategies/envelope/cartesian.hpp>
#include <boost/geometry/strategies/envelope/geographic.hpp>
#include <boost/geometry/strategies/envelope/spherical.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


// difference/intersection of multipoint-multipolygon
template
<
    typename MultiPoint,
    typename MultiPolygon,
    typename PointOut,
    overlay_type OverlayType,
    typename Policy
>
class multipoint_multipolygon_point
{
private:
    template <typename Strategy>
    struct expand_box_point
    {
        explicit expand_box_point(Strategy const& strategy)
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
    struct expand_box_boxpair
    {
        explicit expand_box_boxpair(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box1, typename Box2, typename SizeT>
        inline void apply(Box1& total, std::pair<Box2, SizeT> const& box_pair) const
        {
            geometry::expand(total, box_pair.first, m_strategy);
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
    struct overlaps_box_boxpair
    {
        explicit overlaps_box_boxpair(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box1, typename Box2, typename SizeT>
        inline bool apply(Box1 const& box, std::pair<Box2, SizeT> const& box_pair) const
        {
            return ! geometry::disjoint(box, box_pair.first, m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename OutputIterator, typename Strategy>
    class item_visitor_type
    {
    public:
        item_visitor_type(MultiPolygon const& multipolygon,
                          OutputIterator& oit,
                          Strategy const& strategy)
            : m_multipolygon(multipolygon)
            , m_oit(oit)
            , m_strategy(strategy)
        {}

        template <typename Point, typename Box, typename SizeT>
        inline bool apply(Point const& item1, std::pair<Box, SizeT> const& item2)
        {
            action_selector_pl
                <
                    PointOut, overlay_intersection
                >::apply(item1,
                         Policy::apply(item1,
                                       range::at(m_multipolygon,
                                                 item2.second),
                         m_strategy),
                         m_oit);

            return true;
        }

    private:
        MultiPolygon const& m_multipolygon;
        OutputIterator& m_oit;        
        Strategy const& m_strategy;
    };

    template <typename Iterator, typename Box, typename SizeT, typename Strategy>
    static inline void fill_box_pairs(Iterator first, Iterator last,
                                      std::vector<std::pair<Box, SizeT> > & box_pairs,
                                      Strategy const& strategy)
    {
        SizeT index = 0;
        for (; first != last; ++first, ++index)
        {
            box_pairs.push_back(
                std::make_pair(geometry::return_envelope<Box>(*first, strategy),
                               index));
        }
    }

    template <typename OutputIterator, typename Strategy>
    static inline OutputIterator get_common_points(MultiPoint const& multipoint,
                                                   MultiPolygon const& multipolygon,
                                                   OutputIterator oit,
                                                   Strategy const& strategy)
    {
        item_visitor_type<OutputIterator, Strategy> item_visitor(multipolygon, oit, strategy);

        typedef geometry::model::point
            <
                typename geometry::coordinate_type<MultiPoint>::type,
                geometry::dimension<MultiPoint>::value,
                typename geometry::coordinate_system<MultiPoint>::type
            > point_type;
        typedef geometry::model::box<point_type> box_type;
        typedef std::pair<box_type, std::size_t> box_pair;
        std::vector<box_pair> box_pairs;
        box_pairs.reserve(boost::size(multipolygon));

        fill_box_pairs(boost::begin(multipolygon),
                       boost::end(multipolygon),
                       box_pairs, strategy);

        geometry::partition
            <
                box_type
            >::apply(multipoint, box_pairs, item_visitor,
                     expand_box_point<Strategy>(strategy),
                     overlaps_box_point<Strategy>(strategy),
                     expand_box_boxpair<Strategy>(strategy),
                     overlaps_box_boxpair<Strategy>(strategy));

        return oit;
    }

public:
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(MultiPoint const& multipoint,
                                       MultiPolygon const& multipolygon,
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
        get_common_points(multipoint, multipolygon,
                          std::back_inserter(common_points),
                          strategy);

        return multipoint_multipoint_point
            <
                MultiPoint, point_vector_type, PointOut, OverlayType
            >::apply(multipoint, common_points, robust_policy, oit, strategy);
    }
};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DISPATCH


#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch { namespace overlay
{

// dispatch struct for pointlike-areal difference/intersection computation
template
<
    typename PointLike,
    typename Areal,
    typename PointOut,
    overlay_type OverlayType,
    typename Tag1,
    typename Tag2
>
struct pointlike_areal_point
    : not_implemented<PointLike, Areal, PointOut>
{};


template
<
    typename Point,
    typename Areal,
    typename PointOut,
    overlay_type OverlayType,
    typename Tag2
>
struct pointlike_areal_point
    <
        Point, Areal, PointOut, OverlayType, point_tag, Tag2
    > : detail::overlay::point_single_point
        <
            Point, Areal, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


// TODO: Consider implementing Areal-specific version
//   calculating envelope first in order to reject Points without
//   calling disjoint for Rings and Polygons
template
<
    typename MultiPoint,
    typename Areal,
    typename PointOut,
    overlay_type OverlayType,
    typename Tag2
>
struct pointlike_areal_point
    <
        MultiPoint, Areal, PointOut, OverlayType, multi_point_tag, Tag2
    > : detail::overlay::multipoint_single_point
        <
            MultiPoint, Areal, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


template
<
    typename MultiPoint,
    typename MultiPolygon,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_areal_point
    <
        MultiPoint, MultiPolygon, PointOut, OverlayType, multi_point_tag, multi_polygon_tag
    > : detail::overlay::multipoint_multipolygon_point
        <
            MultiPoint, MultiPolygon, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


}} // namespace detail_dispatch::overlay
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_AREAL_HPP

/* pointlike_areal.hpp
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
*/
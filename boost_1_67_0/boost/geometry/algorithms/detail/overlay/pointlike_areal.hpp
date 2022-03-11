// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_AREAL_HPP

#include <vector>

#include <boost/range.hpp>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>

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
    template <typename ExpandPointStrategy>
    struct expand_box_point
    {
        template <typename Box, typename Point>
        static inline void apply(Box& total, Point const& point)
        {
            geometry::expand(total, point, ExpandPointStrategy());
        }
    };

    template <typename ExpandBoxStrategy>
    struct expand_box_boxpair
    {
        template <typename Box1, typename Box2, typename SizeT>
        static inline void apply(Box1& total, std::pair<Box2, SizeT> const& box_pair)
        {
            geometry::expand(total, box_pair.first, ExpandBoxStrategy());
        }
    };

    template <typename DisjointPointBoxStrategy>
    struct overlaps_box_point
    {
        template <typename Box, typename Point>
        static inline bool apply(Box const& box, Point const& point)
        {
            return ! geometry::disjoint(point, box, DisjointPointBoxStrategy());
        }
    };

    template <typename DisjointBoxBoxStrategy>
    struct overlaps_box_boxpair
    {
        template <typename Box1, typename Box2, typename SizeT>
        static inline bool apply(Box1 const& box, std::pair<Box2, SizeT> const& box_pair)
        {
            return ! geometry::disjoint(box, box_pair.first, DisjointBoxBoxStrategy());
        }
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

    template <typename Iterator, typename Box, typename SizeT, typename EnvelopeStrategy>
    static inline void fill_box_pairs(Iterator first, Iterator last,
                                      std::vector<std::pair<Box, SizeT> > & box_pairs,
                                      EnvelopeStrategy const& strategy)
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
                       box_pairs,
                       strategy.get_envelope_strategy());

        typedef typename Strategy::envelope_strategy_type::box_expand_strategy_type expand_box_strategy_type;
        typedef typename Strategy::disjoint_box_box_strategy_type disjoint_box_box_strategy_type;
        typedef typename Strategy::disjoint_point_box_strategy_type disjoint_point_box_strategy_type;
        typedef typename Strategy::expand_point_strategy_type expand_point_strategy_type;

        geometry::partition
            <
                box_type
            >::apply(multipoint, box_pairs, item_visitor,
                     expand_box_point<expand_point_strategy_type>(),
                     overlaps_box_point<disjoint_point_box_strategy_type>(),
                     expand_box_boxpair<expand_box_strategy_type>(),
                     overlaps_box_boxpair<disjoint_box_box_strategy_type>());

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
// Boost.Geometry Index
//
// R-tree strategies
//
// Copyright (c) 2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_INDEX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_INDEX_HPP

#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_point_box.hpp>
#include <boost/geometry/strategies/spherical/distance_segment_box.hpp>
#include <boost/geometry/strategies/spherical/envelope_box.hpp>
#include <boost/geometry/strategies/spherical/envelope_point.hpp>
#include <boost/geometry/strategies/spherical/envelope_segment.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>
#include <boost/geometry/strategies/spherical/expand_point.hpp>
#include <boost/geometry/strategies/spherical/expand_segment.hpp>
#include <boost/geometry/strategies/spherical/intersection.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>

#include <boost/geometry/strategies/index.hpp>


namespace boost { namespace geometry { namespace strategy { namespace index
{

template
<
    typename CalculationType = void
>
struct spherical
{
    typedef spherical_tag cs_tag;

    typedef geometry::strategy::envelope::spherical_point envelope_point_strategy_type;
    typedef geometry::strategy::envelope::spherical_box envelope_box_strategy_type;
    typedef geometry::strategy::envelope::spherical_segment
        <
            CalculationType
        > envelope_segment_strategy_type;

    static inline envelope_segment_strategy_type get_envelope_segment_strategy()
    {
        return envelope_segment_strategy_type();
    }

    typedef geometry::strategy::expand::spherical_point expand_point_strategy_type;
    typedef geometry::strategy::expand::spherical_box expand_box_strategy_type;
    typedef geometry::strategy::expand::spherical_segment
        <
            CalculationType
        > expand_segment_strategy_type;

    static inline expand_segment_strategy_type get_expand_segment_strategy()
    {
        return expand_segment_strategy_type();
    }

	typedef geometry::strategy::covered_by::spherical_point_box covered_by_point_box_strategy_type;
	typedef geometry::strategy::covered_by::spherical_box_box covered_by_box_box_strategy_type;
	typedef geometry::strategy::within::spherical_point_point within_point_point_strategy_type;
	//typedef geometry::strategy::within::spherical_point_box within_point_box_strategy_type;
	//typedef geometry::strategy::within::spherical_box_box within_box_box_strategy_type;

    // used in equals(Seg, Seg) but only to get_point_in_point_strategy()
    typedef geometry::strategy::intersection::spherical_segments
        <
            CalculationType
        > relate_segment_segment_strategy_type;

    static inline relate_segment_segment_strategy_type get_relate_segment_segment_strategy()
    {
        return relate_segment_segment_strategy_type();
    }
    
    // used in intersection_content
    typedef geometry::strategy::disjoint::spherical_box_box disjoint_box_box_strategy_type;

    typedef geometry::strategy::distance::comparable::haversine
        <
            double,
            CalculationType
        > comparable_distance_point_point_strategy_type;

    static inline comparable_distance_point_point_strategy_type get_comparable_distance_point_point_strategy()
    {
        return comparable_distance_point_point_strategy_type();
    }

    // TODO: Comparable version should be possible
    typedef geometry::strategy::distance::cross_track_point_box
        <
            CalculationType,
            geometry::strategy::distance::haversine<double, CalculationType>
        > comparable_distance_point_box_strategy_type;

    static inline comparable_distance_point_box_strategy_type get_comparable_distance_point_box_strategy()
    {
        return comparable_distance_point_box_strategy_type();
    }

    // TODO: Radius is not needed in comparable strategy
    typedef geometry::strategy::distance::comparable::cross_track
        <
            CalculationType,
            geometry::strategy::distance::comparable::haversine<double, CalculationType>
        > comparable_distance_point_segment_strategy_type;

    static inline comparable_distance_point_segment_strategy_type get_comparable_distance_point_segment_strategy()
    {
        return comparable_distance_point_segment_strategy_type();
    }

    // comparable?
    typedef geometry::strategy::distance::spherical_segment_box
        <
            CalculationType,
            geometry::strategy::distance::haversine<double, CalculationType>
        > comparable_distance_segment_box_strategy_type;

    static inline comparable_distance_segment_box_strategy_type get_comparable_distance_segment_box_strategy()
    {
        return comparable_distance_segment_box_strategy_type();
    }
};


namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, spherical_tag>
{
    typedef spherical<> type;
};

template <typename Geometry>
struct default_strategy<Geometry, spherical_polar_tag>
{
    typedef spherical<> type;
};

template <typename Geometry>
struct default_strategy<Geometry, spherical_equatorial_tag>
{
    typedef spherical<> type;
};


template <typename Point1, typename Point2, typename CalculationType>
struct from_strategy<within::spherical_winding<Point1, Point2, CalculationType> >
{
    typedef strategy::index::spherical<CalculationType> type;

    static inline type get(within::spherical_winding<Point1, Point2, CalculationType> const&)
    {
        return type();
    }
};

// distance (MPt, MPt)
template <typename RadiusType, typename CalculationType>
struct from_strategy<distance::comparable::haversine<RadiusType, CalculationType> >
{
    typedef strategy::index::spherical<CalculationType> type;

    static inline type get(distance::comparable::haversine<RadiusType, CalculationType> const&)
    {
        return type();
    }
};

// distance (MPt, Linear/Areal)
template <typename CalculationType, typename PPStrategy>
struct from_strategy<distance::comparable::cross_track<CalculationType, PPStrategy> >
{
    typedef strategy::index::spherical<CalculationType> type;

    static inline type get(distance::comparable::cross_track<CalculationType, PPStrategy> const&)
    {
        return type();
    }
};


} // namespace services


}}}} // namespace boost::geometry::strategy::index

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_INDEX_HPP

/* index.hpp
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
*/
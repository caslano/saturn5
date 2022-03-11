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

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_INDEX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_INDEX_HPP


#include <boost/geometry/strategies/cartesian/box_in_box.hpp>
#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
//#include <boost/geometry/strategies/cartesian/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_projected_point.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras_point_box.hpp>
#include <boost/geometry/strategies/cartesian/distance_segment_box.hpp>
#include <boost/geometry/strategies/cartesian/envelope_box.hpp>
#include <boost/geometry/strategies/cartesian/envelope_point.hpp>
#include <boost/geometry/strategies/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategies/cartesian/expand_box.hpp>
#include <boost/geometry/strategies/cartesian/expand_point.hpp>
#include <boost/geometry/strategies/cartesian/expand_segment.hpp>
#include <boost/geometry/strategies/cartesian/intersection.hpp>
#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>

#include <boost/geometry/strategies/index.hpp>


namespace boost { namespace geometry { namespace strategy { namespace index
{

template
<
    typename CalculationType = void
>
struct cartesian
{
    typedef cartesian_tag cs_tag;

    typedef geometry::strategy::envelope::cartesian_point envelope_point_strategy_type;
    typedef geometry::strategy::envelope::cartesian_box envelope_box_strategy_type;
    typedef geometry::strategy::envelope::cartesian_segment
        <
            CalculationType
        > envelope_segment_strategy_type;

    static inline envelope_segment_strategy_type get_envelope_segment_strategy()
    {
        return envelope_segment_strategy_type();
    }

    typedef geometry::strategy::expand::cartesian_point expand_point_strategy_type;
    typedef geometry::strategy::expand::cartesian_box expand_box_strategy_type;
    typedef geometry::strategy::expand::cartesian_segment expand_segment_strategy_type;

    static inline expand_segment_strategy_type get_expand_segment_strategy()
    {
        return expand_segment_strategy_type();
    }

    typedef geometry::strategy::covered_by::cartesian_point_box covered_by_point_box_strategy_type;
    typedef geometry::strategy::covered_by::cartesian_box_box covered_by_box_box_strategy_type;
    typedef geometry::strategy::within::cartesian_point_point within_point_point_strategy_type;
    /*
    typedef geometry::strategy::within::cartesian_point_box within_point_box_strategy_type;
    typedef geometry::strategy::within::cartesian_box_box within_box_box_strategy_type;
    typedef geometry::strategy::within::cartesian_winding
        <
            void, void, CalculationType
        > within_point_segment_strategy_type;

    static inline within_point_segment_strategy_type get_within_point_segment_strategy()
    {
        return within_point_segment_strategy_type();
    }
    */
    
    // used in equals(Seg, Seg) but only to get_point_in_point_strategy()
    typedef geometry::strategy::intersection::cartesian_segments
        <
            CalculationType
        > relate_segment_segment_strategy_type;

    static inline relate_segment_segment_strategy_type get_relate_segment_segment_strategy()
    {
        return relate_segment_segment_strategy_type();
    }
    
    // used in intersection_content
    typedef geometry::strategy::disjoint::cartesian_box_box disjoint_box_box_strategy_type;
    
    typedef geometry::strategy::distance::comparable::pythagoras
        <
            CalculationType
        > comparable_distance_point_point_strategy_type;

    static inline comparable_distance_point_point_strategy_type get_comparable_distance_point_point_strategy()
    {
        return comparable_distance_point_point_strategy_type();
    }

    typedef geometry::strategy::distance::comparable::pythagoras_point_box
        <
            CalculationType
        > comparable_distance_point_box_strategy_type;

    static inline comparable_distance_point_box_strategy_type get_comparable_distance_point_box_strategy()
    {
        return comparable_distance_point_box_strategy_type();
    }

    // TODO: comparable version should be possible
    typedef geometry::strategy::distance::projected_point
        <
            CalculationType,
            geometry::strategy::distance::pythagoras<CalculationType>
        > comparable_distance_point_segment_strategy_type;

    static inline comparable_distance_point_segment_strategy_type get_comparable_distance_point_segment_strategy()
    {
        return comparable_distance_point_segment_strategy_type();
    }

    typedef geometry::strategy::distance::cartesian_segment_box
        <
            CalculationType,
            geometry::strategy::distance::pythagoras<CalculationType>
        > comparable_distance_segment_box_strategy_type;

    static inline comparable_distance_segment_box_strategy_type get_comparable_distance_segment_box_strategy()
    {
        return comparable_distance_segment_box_strategy_type();
    }
};


namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, cartesian_tag>
{
    typedef cartesian<> type;
};


// within and relate (MPt, Mls/MPoly)
template <typename Point1, typename Point2, typename CalculationType>
struct from_strategy<within::cartesian_winding<Point1, Point2, CalculationType> >
{
    typedef strategy::index::cartesian<CalculationType> type;

    static inline type get(within::cartesian_winding<Point1, Point2, CalculationType> const&)
    {
        return type();
    }
};

// distance (MPt, MPt)
template <typename CalculationType>
struct from_strategy<distance::comparable::pythagoras<CalculationType> >
{
    typedef strategy::index::cartesian<CalculationType> type;

    static inline type get(distance::comparable::pythagoras<CalculationType> const&)
    {
        return type();
    }
};

// distance (MPt, Linear/Areal)
template <typename CalculationType, typename PPStrategy>
struct from_strategy<distance::projected_point<CalculationType, PPStrategy> >
{
    typedef strategy::index::cartesian<CalculationType> type;

    static inline type get(distance::projected_point<CalculationType, PPStrategy> const&)
    {
        return type();
    }
};


} // namespace services


}}}} // namespace boost::geometry::strategy::index

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_INDEX_HPP

/* index.hpp
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
*/
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

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INDEX_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INDEX_HPP


#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/distance_andoyer.hpp> // backward compatibility
#include <boost/geometry/strategies/geographic/distance_cross_track.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track_point_box.hpp>
#include <boost/geometry/strategies/geographic/distance_segment_box.hpp>
#include <boost/geometry/strategies/geographic/distance_thomas.hpp> // backward compatibility
#include <boost/geometry/strategies/geographic/distance_vincenty.hpp> // backward compatibility
#include <boost/geometry/strategies/geographic/envelope_segment.hpp>
#include <boost/geometry/strategies/geographic/expand_segment.hpp>
#include <boost/geometry/strategies/geographic/intersection.hpp>
#include <boost/geometry/strategies/geographic/point_in_poly_winding.hpp>

#include <boost/geometry/strategies/spherical/index.hpp>


namespace boost { namespace geometry { namespace strategy { namespace index
{

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = geometry::srs::spheroid<double>,
    typename CalculationType = void
>
struct geographic
    : spherical<CalculationType>
{
    typedef geographic_tag cs_tag;

    typedef geometry::strategy::envelope::geographic_segment
        <
            FormulaPolicy, Spheroid, CalculationType
        > envelope_segment_strategy_type;

    inline envelope_segment_strategy_type get_envelope_segment_strategy() const
    {
        return envelope_segment_strategy_type(m_spheroid);
    }

    typedef geometry::strategy::expand::geographic_segment
        <
            FormulaPolicy, Spheroid, CalculationType
        > expand_segment_strategy_type;

    inline expand_segment_strategy_type get_expand_segment_strategy() const
    {
        return expand_segment_strategy_type(m_spheroid);
    }

    // used in equals(Seg, Seg) but only to get_point_in_point_strategy()
    typedef geometry::strategy::intersection::geographic_segments
        <
            FormulaPolicy,
            // If index::geographic formula is derived from intersection::geographic_segments
            // formula with different Order this may cause an inconsistency
            strategy::default_order<FormulaPolicy>::value,
            Spheroid,
            CalculationType
        > relate_segment_segment_strategy_type;

    inline relate_segment_segment_strategy_type get_relate_segment_segment_strategy() const
    {
        return relate_segment_segment_strategy_type(m_spheroid);
    }

	typedef geometry::strategy::distance::geographic
        <
            FormulaPolicy, Spheroid, CalculationType
        > comparable_distance_point_point_strategy_type;

    inline comparable_distance_point_point_strategy_type get_comparable_distance_point_point_strategy() const
    {
        return comparable_distance_point_point_strategy_type(m_spheroid);
    }

    typedef geometry::strategy::distance::geographic_cross_track_point_box
        <
            FormulaPolicy, Spheroid, CalculationType
        > comparable_distance_point_box_strategy_type;

    inline comparable_distance_point_box_strategy_type get_comparable_distance_point_box_strategy() const
    {
        return comparable_distance_point_box_strategy_type(m_spheroid);
    }

    typedef geometry::strategy::distance::geographic_cross_track
        <
            FormulaPolicy, Spheroid, CalculationType
        > comparable_distance_point_segment_strategy_type;

    inline comparable_distance_point_segment_strategy_type get_comparable_distance_point_segment_strategy() const
    {
        return comparable_distance_point_segment_strategy_type(m_spheroid);
    }

    typedef geometry::strategy::distance::geographic_segment_box
        <
            FormulaPolicy, Spheroid, CalculationType
        > comparable_distance_segment_box_strategy_type;

    inline comparable_distance_segment_box_strategy_type get_comparable_distance_segment_box_strategy() const
    {
        return comparable_distance_segment_box_strategy_type(m_spheroid);
    }

    geographic()
        : m_spheroid()
    {}

    explicit geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

public:
    Spheroid m_spheroid;
};


namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, geographic_tag>
{
    typedef geographic<> type;
};


// within and relate (MPt, Mls/MPoly)
template <typename Point1, typename Point2, typename Formula, typename Spheroid, typename CalculationType>
struct from_strategy<within::geographic_winding<Point1, Point2, Formula, Spheroid, CalculationType> >
{
    typedef strategy::index::geographic<Formula, Spheroid, CalculationType> type;

    static inline type get(within::geographic_winding<Point1, Point2, Formula, Spheroid, CalculationType> const& strategy)
    {
        return type(strategy.model());
    }
};

// distance (MPt, MPt)
template <typename Formula, typename Spheroid, typename CalculationType>
struct from_strategy<distance::geographic<Formula, Spheroid, CalculationType> >
{
    typedef strategy::index::geographic<Formula, Spheroid, CalculationType> type;

    static inline type get(distance::geographic<Formula, Spheroid, CalculationType> const& strategy)
    {
        return type(strategy.model());
    }
};
template <typename Spheroid, typename CalculationType>
struct from_strategy<distance::andoyer<Spheroid, CalculationType> >
{
    typedef strategy::index::geographic<strategy::andoyer, Spheroid, CalculationType> type;

    static inline type get(distance::andoyer<Spheroid, CalculationType> const& strategy)
    {
        return type(strategy.model());
    }
};
template <typename Spheroid, typename CalculationType>
struct from_strategy<distance::thomas<Spheroid, CalculationType> >
{
    typedef strategy::index::geographic<strategy::thomas, Spheroid, CalculationType> type;

    static inline type get(distance::thomas<Spheroid, CalculationType> const& strategy)
    {
        return type(strategy.model());
    }
};
template <typename Spheroid, typename CalculationType>
struct from_strategy<distance::vincenty<Spheroid, CalculationType> >
{
    typedef strategy::index::geographic<strategy::vincenty, Spheroid, CalculationType> type;

    static inline type get(distance::vincenty<Spheroid, CalculationType> const& strategy)
    {
        return type(strategy.model());
    }
};

// distance (MPt, Linear/Areal)
template <typename Formula, typename Spheroid, typename CalculationType>
struct from_strategy<distance::geographic_cross_track<Formula, Spheroid, CalculationType> >
{
    typedef strategy::index::geographic<Formula, Spheroid, CalculationType> type;

    static inline type get(distance::geographic_cross_track<Formula, Spheroid, CalculationType> const& strategy)
    {
        return type(strategy.model());
    }
};


} // namespace services


}}}} // namespace boost::geometry::strategy::index

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INDEX_HPP

/* index.hpp
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
*/
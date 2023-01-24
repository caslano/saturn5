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
p4HshtNd1VgspY4kw6ns6e82bGUqxXD+M65gtkqV9H1jdDvherSNP2lY8fdMrhHt5ZmHpS2/b9bmqcUemhRM9y3YtMOGFqtyh2plRVVQ9qwxJxyi+ME8INyIDYxFyeXa6ReESeuLOZptFAf/uOn87NnSBLbfiZm3tE66TE5vv1fzovxpFASKisG0EC5EPopBVM9LYG5/I70jappi163VRyK4nQhL3PXmMxH5mDkxdqdu2DjMvM4oz7j3kJOsF7dSMUyVB77EZUElh6GncXCs68EKd2wf7uq04Ra6bLos4rJIevLRWn6PMnMj48ZcJ4N/0BQ6Ebg1iDDKsSi6TLv6yY4rrZQGuSXIuUxpmrPNyjJ4kxo52V4iMBMLEvndXHpwNeiiReYgYQv14WkZZ+YhL2S+mjUuokv2useRR/7Gjr5NOQr3yv8yjXOccExgti9xi58VnSob0gy/6PY0OJinILHvwg8ObSZDqcy05jz+e9dJgoVcL4WGgIBA/G+VTvOfk2XWvwVi5g42juJOjpY2rg7/EpJ562tgCV9bUNtltihodfWUUTnYLFCLZ6Y5TjCa/HSoVmAyrdvlus8RzJoa5nGyFq+WDyanNaNV/ZNFXsliuoqosn5/F4vGACyamGTdO9z4MRz7l5dPqk3GBPl25Z0LyOt39/Vvt2udq87nAj/A8424WkHX5xWfSCmkDSbWXNwaO/0Mgxrlnbps
*/
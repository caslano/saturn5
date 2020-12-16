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
hgh9/bx1A01mUiJhdJnDpxkyOzSwvvPHbzBCp4jMKbh+/CNZZHKkK4S9IvLdfobKIqdE5PSWu0mX4baQV6V+cmalafP+8ucVsn5jy2tXwHkw5Ov3dpIZn6KgK+rU4LHN89uvXPF64wErLyz95QTrlw00/6a7Fq4412rSa8vnjnr+1lef20//U03z/+GHmg+tu3TlsgHvFOTF9PorBXNtlOa/8br5k05WX7l28bqLSvc/cw+T4f16PAcXfLjv1+/vPjPvzhaNtqyYzPj1hf58XNzaxC8O/tx4/OEFzcc/3pwDaXdV1fyviHX/sGjK9E5V5kyvtfBL94fUCd3/j/d8tm+wO/OJJd/Nn/bCJevR5Z1ozf+GVxescR2KeXbUzcenZp2dxHvUuMqa/9oXqr/S7vKVP/V6rMbG6xIffpexp6HmP+DH9u0Sf1i4fNPw6xufvOBOJld96mv+b9W+aEdSz55vDqzWqe/si4c1Y2zR/X93KLVW1g1XLf3Lhbd6WndIeIq6cpEe/4Pp47dW/frPrz3d9teHV93GfGmdnp/b/rDl0M/Nhi94Kz73g7d7vrmS/K+i+Xub3v79knEPX39Lx4mPu3pe+DfOT9bQ/KvsjE6bNrvLkw9vfGHiL5fsZzzorqdr/RNrhy6tWuWXwam9N2T/tTeVcaHuf+7IGzUeWrykcPgnP6RkTm5Tyv1P3f/kithHuuzOPrfk9JrtN69pweH2g3o+eA7MuvX7U+32fXjvkOadP+uzk/LS9a/8dOYlrRf/0Lfp2abRDV+axgdr/6r7x9ROG/nBuJOzOrZ58PaF8zZ8T35W1/zn13/wjTdmN73mwJMzXirtMJnKOlPPnyvHpDb9bNKZzhd6mpfe1Oss8XfSy33LFaPPnOt32Yf3f3lsT2pU6vvUcz29bx6c9NX6rGbHf723aOinrbacZvzV9Vz27CMff74nLm7JnglzM+965iRnhvXniz+7ruVDyRtq3lJrf1TMD89up33EaP5PPf/wroPvzD67oP62Bp1q/Hg17UmvJ7NbdIjd2mjV8z/Ne/m2D24/PZ5xTM//sS+vG3P019+P/HbDA6trbmzD2sZ6vT5UO9Pon7PGZkz9tGa7uzz3LKlLPuvluOZQvb63VLn6X8Pb1nvtvbbH9vG8nj8v3z37vs4rtqUfa/SvTd+3b9mT9F6o+Sf+/o6jrVt8/MPxt1YVVJv/N/LttLS9Ym28hMNxI6TdNZDGO6hepYLTcATO9STPQbc8Vx0OkOcmX1CpoBmcAjvDG+DlcBocCt0wGU6Hp2EyrlDi2y3xXQgTJb7sapUK6sMceCn0wAlwNpwI8+As6IX3wHx4P7wR7oTz4GkYhyt8CjlwsMipAluLnB6kLwb2hJfDXtAMd0rC9XUI18WFfrAr7AkvhafhKQLEP22Ea1fNCNeff/8tSu48VK9UEAtPwfbwH3A4PAOvh2dhNvwJ5sNf4BZYiXx7E1SGB2EVeAxWhSfgBfBnWANWQ1Yt2BDWga1hXdgD1oMDYH04Al4EE2EDOBXGwBmwMZwDm8CbYVN4J2wOV8MWcCNsCbfBVvAt2AYehO3gUdgBnoSd4D9hF3hhZfILNoHdYFvYA/aAveAQ2Bt6YF/4BOwPt8AB8BV4OdwHB8Jj8Ar4I4yHUeT5YNgEDoGxcCi8FA6DfeFwOByOgGPgSDgVjoLT4Wj4KBwDD8AE+B2cAGNox9fC3nCS1Od4XPF6yh2OlvpSDfaU+tKtCuFgd9ga9oRDYS84HF4GzXrn2kA8sKOt3kGeqw/bwDawrV+4BAk3yiHcWp5rCZ+Bw+CzUOkt4UY46N1B9O4oeneG8bALHAK7SjwJONdG4oFLJZ4L4FA=
*/
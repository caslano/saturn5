// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_POINT_ORDER_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/point_order.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

template
    <
        typename FormulaPolicy = strategy::andoyer,
        typename Spheroid = srs::spheroid<double>,
        typename CalculationType = void
    >
struct geographic
{
    typedef azimuth_tag version_tag;

    template <typename Geometry>
    struct result_type
    {
        typedef typename geometry::select_calculation_type_alt
            <
                CalculationType, Geometry
            >::type type;
    };

    geographic()
    {}

    explicit geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    template <typename Point>
    inline bool apply(Point const& p1, Point const& p2,
                      typename result_type<Point>::type & azi,
                      typename result_type<Point>::type & razi) const
    {
        typedef typename result_type<Point>::type calc_t;

        if (equals_point_point(p1, p2))
        {
            return false;
        }

        formula::result_inverse<calc_t> res = FormulaPolicy::template inverse
            <
                calc_t, false, true, true, false, false
            >::apply(geometry::get_as_radian<0>(p1),
                     geometry::get_as_radian<1>(p1),
                     geometry::get_as_radian<0>(p2),
                     geometry::get_as_radian<1>(p2),
                     m_spheroid);

        azi = res.azimuth;
        razi = res.reverse_azimuth;

        return true;
    }

    template <typename Point>
    inline typename result_type<Point>::type
    apply(Point const& /*p0*/, Point const& /*p1*/, Point const& /*p2*/,
          typename result_type<Point>::type const& azi1,
          typename result_type<Point>::type const& azi2) const
    {
        // TODO: support poles
        return math::longitude_distance_signed<radian>(azi1, azi2);
    }

private:
    template <typename Point>
    static bool equals_point_point(Point const& p0, Point const& p1)
    {
        return strategy::within::spherical_point_point::apply(p0, p1);
    }

    Spheroid m_spheroid;
};

namespace services
{

template <>
struct default_strategy<geographic_tag>
{
    typedef geographic<> type;
};

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_POINT_ORDER_HPP

/* point_order.hpp
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
*/
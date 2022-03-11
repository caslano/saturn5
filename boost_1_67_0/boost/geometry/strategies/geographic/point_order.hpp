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
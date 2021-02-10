// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_POINT_ORDER_HPP


#include <boost/type_traits/is_same.hpp>


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/strategies/spherical/area.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/point_order.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

//template <typename CalculationType = void>
//struct spherical
//{
//    typedef azimuth_tag version_tag;
//
//    template <typename Geometry>
//    struct result_type
//    {
//        typedef typename geometry::select_calculation_type_alt
//            <
//                CalculationType, Geometry
//            >::type type;
//    };
//
//    template <typename Point>
//    inline bool apply(Point const& p1, Point const& p2,
//                      typename result_type<Point>::type & azi,
//                      typename result_type<Point>::type & razi) const
//    {
//        typedef typename result_type<Point>::type calc_t;
//
//        if (equals_point_point(p1, p2))
//        {
//            return false;
//        }
//
//        calc_t lon1 = geometry::get_as_radian<0>(p1);
//        calc_t lat1 = geometry::get_as_radian<1>(p1);
//        calc_t lon2 = geometry::get_as_radian<0>(p2);
//        calc_t lat2 = geometry::get_as_radian<1>(p2);
//
//        convert_latitudes<Point>(lat1, lat2);
//
//        formula::result_spherical<calc_t>
//            res = formula::spherical_azimuth<calc_t, true>(lon1, lat1, lon2, lat2);
//
//        azi = res.azimuth;
//        razi = res.reverse_azimuth;
//
//        return true;
//    }
//
//    template <typename Point>
//    inline typename result_type<Point>::type
//    apply(Point const& /*p0*/, Point const& /*p1*/, Point const& /*p2*/,
//          typename result_type<Point>::type const& azi1,
//          typename result_type<Point>::type const& azi2) const
//    {
//        // TODO: support poles
//        return math::longitude_distance_signed<radian>(azi1, azi2);
//    }
//
//private:
//    template <typename Point>
//    static bool equals_point_point(Point const& p0, Point const& p1)
//    {
//        return strategy::within::spherical_point_point::apply(p0, p1);
//    }
//
//    template <typename Point, typename CalcT>
//    static void convert_latitudes(CalcT & lat1, CalcT & lat2)
//    {
//        static const bool is_polar = boost::is_same
//            <
//                typename geometry::cs_tag<Point>::type,
//                spherical_polar_tag
//            >::value;
//
//        if (BOOST_GEOMETRY_CONDITION(is_polar))
//        {
//            CalcT pi_half = math::half_pi<CalcT>();
//            lat1 = pi_half - lat1;
//            lat2 = pi_half - lat2;
//        }
//    }
//};

template <typename CalculationType = void>
struct spherical
    : strategy::area::spherical<double, CalculationType>
{
    typedef area_tag version_tag;
};

namespace services
{

template <>
struct default_strategy<spherical_equatorial_tag>
{
    typedef spherical<> type;
};

/*template <>
struct default_strategy<spherical_polar_tag>
{
    typedef spherical<> type;
};*/

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_POINT_ORDER_HPP

/* point_order.hpp
LU9p2WXZ1hoseEHRmMr9YUV/ADKh1QpzaCefShIv01KfalXqyRfnFy8LiPPwPC58uVlCO/8SLNPlS+8KeDpgQcPyPG4lkRan84FUNeFDbp0u4qFXBn+q1utqfl8LhKHiEDbQinXCumcRVO4p18POzu2L6Hr7+igWnRKHzwF/EwzuIT5lMyj55zEZ//TLV3YWN7ZlSlOFgRJSUFzW4Td7gIT/eF6vC2SrkilpmZNBAPFAlgQQmOgJf/cTv/cLSMlP0PVdGeP1S0GAcOYLFyTiIM/GeBv+NP4cNbabLRuZ455qjFXeosyE6YjnpqhMOTrAhoWxLAj78L0fFVIkj2Yg8F/nY3UfLHrEyqXgCmImOmWqRc2y25t9/VV2/mKwgomSabGx4f7AA3uAoQq/LpLV++ft2pzH7Fb9EoiBazoPteadMTHW7v0rFxlrlPNv8NpoNOfenqkQaQI8X7+xnkAWVKmIAouVVEaH4oH3lvMIg5RlBWK64ODgMWZjS4Dr+EgaLfX6vDw33tPWCedFNDyQNAxMfjUpyk2qEmH/NHq1kwZOp+Zs4QPHODzVeFE2LOXxSlNI1OXGAX5YJxbliyh3cUGPm4u+3cqzPmZ4ogY+FCZ3waeYbVia0E3GGB0N9knOQ6zyj4FZLddSjA5e
*/
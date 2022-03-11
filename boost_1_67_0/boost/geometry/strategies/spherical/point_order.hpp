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
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
*/
// Boost.Geometry

// Copyright (c) 2019-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_POINT_ORDER_HPP


//#include <type_traits>


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/strategy/spherical/area.hpp>
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
//        static const bool is_polar = std::is_same
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

    // TEMP
    static strategy::area::spherical<double, CalculationType> get_area_strategy()
    {
        return strategy::area::spherical<double, CalculationType>();
    }
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
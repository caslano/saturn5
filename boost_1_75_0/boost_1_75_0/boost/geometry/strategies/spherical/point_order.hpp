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
sT87WDJYXWOgm7Y/061rjtNtdTrRXF1jweDpbHb/vWSQewIXWn4qYZ6LUXeqsF9oCSC9rHu2de811B4/41aM/QSGGtG3a/qo9siyafQ4oDzYEonUcvpnZcq2+uTpCitVGypWa41rjZWMw9g+Gmam5vRD1XoOU6GuY7AGqOd6UEXBG3sc7K6zqFFXDwuZHMiLP9vl/Gfk6aub5iv8txRhBWq1x02DgE5dLYYjfPJWr3rsSpNsjKLDdIRrCl93xYYQHE1qpJiStQW3qQIuprBrMik8dMoSwZcwFV2Ojfi21oGvZMbFDN4SbUOfJswICmu15Rc0HHowXWoTsDysBDSZYcUqCdvQyCA+le3Pygtlyo4Y9nua08cOJhGIi+DeC4CIuqNiZiuH+djzuNLcx5jGVgxrVifl09T28medBEx1g9jbq38zVLQMy2DF4Y9JOx3ZZ/HruWesVfAZKtbtbx946PSb93dYkmmW+dhOkikdl2l+IZPWb+EMNbbFPeUj4WprptJlX9n8s7Rfdxaz683iTnU5joOMgjT3zqcKFH7g8gtXD65HK+5eXs94mHSu9QP9EFS5xF8WjM3i4lvtc6JagHJ2ElJm29leYNATM/VqbvBx4WWMh2llqoPNpNz7A5fK2UfBgvq3Dt01lbOXmIQOqOUqa9Ipi7sKtTi+vFSG2F9O6nkKFqy2X+mv7mEqNPgWtdzKGnHXWb/rZOOt
*/
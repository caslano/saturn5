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
5/R5VrbHsKjg4FeMMTbP95Dk+0zyfSJ9AqTMt5JvePDY7PTHL3EhWfaDq2k/qGJZ20nbspZSjiaZ679AoxwS7D0+fKihzfyf2Q6dJP9zkn8RMiuBBTCVz7olaOUvgd7RQ2LZmWP9gyMjhoa8WhkyY2UqGuNtVGWKlNj75qQS0rb0c/05stB6mYwb5M/F30vbf1Mci0Wc7zKJN4/Ny7sdHIxp+n21MDPONygmLLq+7JvsxSKewsw432ZLlTjfbMUc6n/HDOoYB4k1HGMRx+KU6+WxvEEa8bnjNOJzAyzic/0s43OlbJEaYwX4mGKfLGOh9BtcxmjIEourxBsOKCZxuxLvEmI1Pjd30Rj9O4o8xnjaL94xxboNtBJPuzdRHU8bmKSOl72TpI6nbfWuEuum7q8ir7SnlXFYF+IR5vFcbvi84SCRgHSJuXr1mJfDhu3LQT8m2LDtAkzbMyo0ggNxvBzX2ai3jetQxLAOj2Udrso5eIl0jM/GJ5utw9CIyPGyBtmpG7XGKvHRKJdr1nIp52CitInbTypC2kf6Wl9vrzKVy9CJTWBozKghka8c6y/xr8pxVlKJDaWHmHDiA6XyM6/Lk/IbF/xUru2PZFyTxNVmZZOLoX/m5VW2X3S2xjdRxTXK+aOOQZRYJSUuOJJ7mYiROs1tXVqJCcuyXlpxwMp4HR8ZliEb2KKODCtsLHBrfnLHajiWZTitNW0D84BtQ2zhS2L7mFGJ1y7zSdZ47eR1WeO1XdUxgMT2ZY3XdntBvHZTjXhtT414bR9VvLbESmvEZQ+0iBH0sYjLjlfFZWvHYHfXiMEeZxmDTb23jOPQV99elp9/MmwbqY8t9j/7Tfn8fT5flXqq9numWMLe2rHScg1Q4rAlRlY7dnqOOnbakF938rpNGqk/dt43lW9Z1hhkVRldC+ljSfBD0zwpWedRPr+Bz5fMzfn3oWmd/F4Qax30gljrKiwrhXScnzd8ZMr/vnastVKGfIbx2Nm2HzOPnEPbcKChzKOih/uHBEVJHptYvn1h4zou2GbKY1PWdVSuWd3XqeOvb21Wx19v/cAiPnuL+u/Xtqjjs8tsUz6vul92dZRxJ/hjcayIJ/T17i7TeS0dEXEd9ydANJCBol79miDnz1ggP/MxrVi8oe6Q8zrr/ZpSHx+SMsfINSyCdJIyO+1RlZl+adjRlhXyn7iemV2TNb4zqe8V4ouYvv+4yvcffSz0NrMyqoKhX3N87GmN+NgY6/GxckwUMV7vnOS7i76uxCZ4mvWM3Gsoe8gQtmrIkPAgvnGPDFZuNV/+fcFy7DBDfZy1/Gz7rHW0j3n55byawTZOdDKONbJdXzbJw95UJ0tfS1n7mwBVfxNO5v1NvIaxqmxxv7a4339n3G+4Ie632cPcM5pO2pe3qt2bN+sfLtTj9cb9MhPPs0Cec6VYjPXTROJommEZbI210Qs7YBt8C9tiJLbDedgel6A3LkUf/AQ7Yhp2wp+xMz5BX9QXogvaYTcsh92xFvZAb+yJQ7AXjsTeOAr74ETsi3PRD5diP9yM/XE3DsDDOBDP4CBkO/B5eY6FCdKuMh/6ynaoI9uhLpbFelgf3dAb6+MAdMfx2ADnYkNZ/jKdPK/CZ7J8J5wvyy8myy+OjbEEemAp7IplcCCWxRFYDsehKyZjRfwAK+EerIxfYhW8gG/iHayKD7CGbPeaShymPMfClhpxmJFSvtHYBKNkvgCdPH/CInL86L9a9Zb5AiReegi6Y6BspyCcjcNwHQ7HrzEU/4ZhWIDljVLKJ8+UsLlG+cZIPrHYCMfKfOl2JJkvNq9xvn78/yzqpzSJ1zqIzfEv2AaPYQCexJF4CmfgafwIv8M=
*/
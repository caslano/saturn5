// Boost.Geometry

// Copyright (c) 2016-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_SPHERICAL_HPP
#define BOOST_GEOMETRY_FORMULAS_SPHERICAL_HPP

#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/radius.hpp>

//#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/formulas/result_direct.hpp>

namespace boost { namespace geometry {
    
namespace formula {

template <typename T>
struct result_spherical
{
    result_spherical()
        : azimuth(0)
        , reverse_azimuth(0)
    {}

    T azimuth;
    T reverse_azimuth;
};

template <typename T>
static inline void sph_to_cart3d(T const& lon, T const& lat, T & x, T & y, T & z)
{
    T const cos_lat = cos(lat);
    x = cos_lat * cos(lon);
    y = cos_lat * sin(lon);
    z = sin(lat);
}

template <typename Point3d, typename PointSph>
static inline Point3d sph_to_cart3d(PointSph const& point_sph)
{
    typedef typename coordinate_type<Point3d>::type calc_t;

    calc_t const lon = get_as_radian<0>(point_sph);
    calc_t const lat = get_as_radian<1>(point_sph);
    calc_t x, y, z;
    sph_to_cart3d(lon, lat, x, y, z);

    Point3d res;
    set<0>(res, x);
    set<1>(res, y);
    set<2>(res, z);

    return res;
}

template <typename T>
static inline void cart3d_to_sph(T const& x, T const& y, T const& z, T & lon, T & lat)
{
    lon = atan2(y, x);
    lat = asin(z);
}

template <typename PointSph, typename Point3d>
static inline PointSph cart3d_to_sph(Point3d const& point_3d)
{
    typedef typename coordinate_type<PointSph>::type coord_t;
    typedef typename coordinate_type<Point3d>::type calc_t;

    calc_t const x = get<0>(point_3d);
    calc_t const y = get<1>(point_3d);
    calc_t const z = get<2>(point_3d);
    calc_t lonr, latr;
    cart3d_to_sph(x, y, z, lonr, latr);

    PointSph res;
    set_from_radian<0>(res, lonr);
    set_from_radian<1>(res, latr);

    coord_t lon = get<0>(res);
    coord_t lat = get<1>(res);

    math::normalize_spheroidal_coordinates
        <
            typename detail::cs_angular_units<PointSph>::type,
            coord_t
        >(lon, lat);

    set<0>(res, lon);
    set<1>(res, lat);

    return res;
}

// -1 right
// 1 left
// 0 on
template <typename Point3d1, typename Point3d2>
static inline int sph_side_value(Point3d1 const& norm, Point3d2 const& pt)
{
    typedef typename select_coordinate_type<Point3d1, Point3d2>::type calc_t;
    calc_t c0 = 0;
    calc_t d = dot_product(norm, pt);
    return math::equals(d, c0) ? 0
        : d > c0 ? 1
        : -1; // d < 0
}

template <typename CT, bool ReverseAzimuth, typename T1, typename T2>
static inline result_spherical<CT> spherical_azimuth(T1 const& lon1,
                                                     T1 const& lat1,
                                                     T2 const& lon2,
                                                     T2 const& lat2)
{
    typedef result_spherical<CT> result_type;
    result_type result;

    // http://williams.best.vwh.net/avform.htm#Crs
    // https://en.wikipedia.org/wiki/Great-circle_navigation
    CT dlon = lon2 - lon1;

    // An optimization which should kick in often for Boxes
    //if ( math::equals(dlon, ReturnType(0)) )
    //if ( get<0>(p1) == get<0>(p2) )
    //{
    //    return - sin(get_as_radian<1>(p1)) * cos_p2lat);
    //}

    CT const cos_dlon = cos(dlon);
    CT const sin_dlon = sin(dlon);
    CT const cos_lat1 = cos(lat1);
    CT const cos_lat2 = cos(lat2);
    CT const sin_lat1 = sin(lat1);
    CT const sin_lat2 = sin(lat2);

    {
        // "An alternative formula, not requiring the pre-computation of d"
        // In the formula below dlon is used as "d"
        CT const y = sin_dlon * cos_lat2;
        CT const x = cos_lat1 * sin_lat2 - sin_lat1 * cos_lat2 * cos_dlon;
        result.azimuth = atan2(y, x);
    }

    if (ReverseAzimuth)
    {
        CT const y = sin_dlon * cos_lat1;
        CT const x = sin_lat2 * cos_lat1 * cos_dlon - cos_lat2 * sin_lat1;
        result.reverse_azimuth = atan2(y, x);
    }

    return result;
}

template <typename ReturnType, typename T1, typename T2>
inline ReturnType spherical_azimuth(T1 const& lon1, T1 const& lat1,
                                    T2 const& lon2, T2 const& lat2)
{
    return spherical_azimuth<ReturnType, false>(lon1, lat1, lon2, lat2).azimuth;
}

template <typename T>
inline T spherical_azimuth(T const& lon1, T const& lat1, T const& lon2, T const& lat2)
{
    return spherical_azimuth<T, false>(lon1, lat1, lon2, lat2).azimuth;
}

template <typename T>
inline int azimuth_side_value(T const& azi_a1_p, T const& azi_a1_a2)
{
    T const c0 = 0;
    T const pi = math::pi<T>();
    T const two_pi = math::two_pi<T>();

    // instead of the formula from XTD
    //calc_t a_diff = asin(sin(azi_a1_p - azi_a1_a2));

    T a_diff = azi_a1_p - azi_a1_a2;
    // normalize, angle in [-pi, pi]
    while (a_diff > pi)
        a_diff -= two_pi;
    while (a_diff < -pi)
        a_diff += two_pi;

    // NOTE: in general it shouldn't be required to support the pi/-pi case
    // because in non-cartesian systems it makes sense to check the side
    // only "between" the endpoints.
    // However currently the winding strategy calls the side strategy
    // for vertical segments to check if the point is "between the endpoints.
    // This could be avoided since the side strategy is not required for that
    // because meridian is the shortest path. So a difference of
    // longitudes would be sufficient (of course normalized to [-pi, pi]).

    // NOTE: with the above said, the pi/-pi check is temporary
    // however in case if this was required
    // the geodesics on ellipsoid aren't "symmetrical"
    // therefore instead of comparing a_diff to pi and -pi
    // one should probably use inverse azimuths and compare
    // the difference to 0 as well

    // positive azimuth is on the right side
    return math::equals(a_diff, c0)
        || math::equals(a_diff, pi)
        || math::equals(a_diff, -pi) ? 0
        : a_diff > 0 ? -1 // right
        : 1; // left
}

template
<
    bool Coordinates,
    bool ReverseAzimuth,
    typename CT,
    typename Sphere
>
inline result_direct<CT> spherical_direct(CT const& lon1,
                                          CT const& lat1,
                                          CT const& sig12,
                                          CT const& alp1,
                                          Sphere const& sphere)
{
    result_direct<CT> result;

    CT const sin_alp1 = sin(alp1);
    CT const sin_lat1 = sin(lat1);
    CT const cos_alp1 = cos(alp1);
    CT const cos_lat1 = cos(lat1);

    CT const norm = math::sqrt(cos_alp1 * cos_alp1 + sin_alp1 * sin_alp1
                                                   * sin_lat1 * sin_lat1);
    CT const alp0 = atan2(sin_alp1 * cos_lat1, norm);
    CT const sig1 = atan2(sin_lat1, cos_alp1 * cos_lat1);
    CT const sig2 = sig1 + sig12 / get_radius<0>(sphere);

    CT const cos_sig2 = cos(sig2);
    CT const sin_alp0 = sin(alp0);
    CT const cos_alp0 = cos(alp0);

    if (Coordinates)
    {
        CT const sin_sig2 = sin(sig2);
        CT const sin_sig1 = sin(sig1);
        CT const cos_sig1 = cos(sig1);

        CT const norm2 = math::sqrt(cos_alp0 * cos_alp0 * cos_sig2 * cos_sig2
                                    + sin_alp0 * sin_alp0);
        CT const lat2 = atan2(cos_alp0 * sin_sig2, norm2);

        CT const omg1 = atan2(sin_alp0 * sin_sig1, cos_sig1);
        CT const lon2 = atan2(sin_alp0 * sin_sig2, cos_sig2);

        result.lon2 = lon1 + lon2 - omg1;
        result.lat2 = lat2;
    }

    if (ReverseAzimuth)
    {
        CT const alp2 = atan2(sin_alp0, cos_alp0 * cos_sig2);
        result.reverse_azimuth = alp2;
    }

    return result;
}

} // namespace formula

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_SPHERICAL_HPP

/* spherical.hpp
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
*/
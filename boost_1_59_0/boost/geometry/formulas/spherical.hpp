// Boost.Geometry

// Copyright (c) 2016-2020, Oracle and/or its affiliates.
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
            typename geometry::detail::cs_angular_units<PointSph>::type,
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

    // instead of the formula from XTD
    //calc_t a_diff = asin(sin(azi_a1_p - azi_a1_a2));

    T a_diff = azi_a1_p - azi_a1_a2;
    // normalize, angle in (-pi, pi]
    math::detail::normalize_angle_loop<radian>(a_diff);

    // NOTE: in general it shouldn't be required to support the pi/-pi case
    // because in non-cartesian systems it makes sense to check the side
    // only "between" the endpoints.
    // However currently the winding strategy calls the side strategy
    // for vertical segments to check if the point is "between the endpoints.
    // This could be avoided since the side strategy is not required for that
    // because meridian is the shortest path. So a difference of
    // longitudes would be sufficient (of course normalized to (-pi, pi]).

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

        // For longitudes close to the antimeridian the result can be out
        // of range. Therefore normalize.
        math::detail::normalize_angle_cond<radian>(result.lon2);
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
// Boost.Geometry

// Copyright (c) 2016-2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_GEOGRAPHIC_HPP
#define BOOST_GEOMETRY_FORMULAS_GEOGRAPHIC_HPP

#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/arithmetic/normalize.hpp>

#include <boost/geometry/formulas/eccentricity_sqr.hpp>
#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/unit_spheroid.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

namespace boost { namespace geometry {
    
namespace formula {

template <typename Point3d, typename PointGeo, typename Spheroid>
inline Point3d geo_to_cart3d(PointGeo const& point_geo, Spheroid const& spheroid)
{
    typedef typename coordinate_type<Point3d>::type calc_t;

    calc_t const c1 = 1;
    calc_t const e_sqr = eccentricity_sqr<calc_t>(spheroid);

    calc_t const lon = get_as_radian<0>(point_geo);
    calc_t const lat = get_as_radian<1>(point_geo);

    Point3d res;

    calc_t const sin_lat = sin(lat);

    // "unit" spheroid, a = 1
    calc_t const N = c1 / math::sqrt(c1 - e_sqr * math::sqr(sin_lat));
    calc_t const N_cos_lat = N * cos(lat);

    set<0>(res, N_cos_lat * cos(lon));
    set<1>(res, N_cos_lat * sin(lon));
    set<2>(res, N * (c1 - e_sqr) * sin_lat);

    return res;
}

template <typename PointGeo, typename Spheroid, typename Point3d>
inline void geo_to_cart3d(PointGeo const& point_geo, Point3d & result, Point3d & north, Point3d & east, Spheroid const& spheroid)
{
    typedef typename coordinate_type<Point3d>::type calc_t;

    calc_t const c1 = 1;
    calc_t const e_sqr = eccentricity_sqr<calc_t>(spheroid);

    calc_t const lon = get_as_radian<0>(point_geo);
    calc_t const lat = get_as_radian<1>(point_geo);

    calc_t const sin_lon = sin(lon);
    calc_t const cos_lon = cos(lon);
    calc_t const sin_lat = sin(lat);
    calc_t const cos_lat = cos(lat);

    // "unit" spheroid, a = 1
    calc_t const N = c1 / math::sqrt(c1 - e_sqr * math::sqr(sin_lat));
    calc_t const N_cos_lat = N * cos_lat;

    set<0>(result, N_cos_lat * cos_lon);
    set<1>(result, N_cos_lat * sin_lon);
    set<2>(result, N * (c1 - e_sqr) * sin_lat);

    set<0>(east, -sin_lon);
    set<1>(east, cos_lon);
    set<2>(east, 0);

    set<0>(north, -sin_lat * cos_lon);
    set<1>(north, -sin_lat * sin_lon);
    set<2>(north, cos_lat);
}

template <typename PointGeo, typename Point3d, typename Spheroid>
inline PointGeo cart3d_to_geo(Point3d const& point_3d, Spheroid const& spheroid)
{
    typedef typename coordinate_type<PointGeo>::type coord_t;
    typedef typename coordinate_type<Point3d>::type calc_t;

    calc_t const c1 = 1;
    //calc_t const c2 = 2;
    calc_t const e_sqr = eccentricity_sqr<calc_t>(spheroid);

    calc_t const x = get<0>(point_3d);
    calc_t const y = get<1>(point_3d);
    calc_t const z = get<2>(point_3d);
    calc_t const xy_l = math::sqrt(math::sqr(x) + math::sqr(y));

    calc_t const lonr = atan2(y, x);
    
    // NOTE: Alternative version
    // http://www.iag-aig.org/attach/989c8e501d9c5b5e2736955baf2632f5/V60N2_5FT.pdf
    // calc_t const lonr = c2 * atan2(y, x + xy_l);
    
    calc_t const latr = atan2(z, (c1 - e_sqr) * xy_l);

    // NOTE: If h is equal to 0 then there is no need to improve value of latitude
    //       because then N_i / (N_i + h_i) = 1
    // http://www.navipedia.net/index.php/Ellipsoidal_and_Cartesian_Coordinates_Conversion

    PointGeo res;

    set_from_radian<0>(res, lonr);
    set_from_radian<1>(res, latr);

    coord_t lon = get<0>(res);
    coord_t lat = get<1>(res);

    math::normalize_spheroidal_coordinates
        <
            typename coordinate_system<PointGeo>::type::units,
            coord_t
        >(lon, lat);

    set<0>(res, lon);
    set<1>(res, lat);

    return res;
}

template <typename Point3d, typename Spheroid>
inline Point3d projected_to_xy(Point3d const& point_3d, Spheroid const& spheroid)
{
    typedef typename coordinate_type<Point3d>::type coord_t;    
    
    // len_xy = sqrt(x^2 + y^2)
    // r = len_xy - |z / tan(lat)|
    // assuming h = 0
    // lat = atan2(z, (1 - e^2) * len_xy);
    // |z / tan(lat)| = (1 - e^2) * len_xy
    // r = e^2 * len_xy
    // x_res = r * cos(lon) = e^2 * len_xy * x / len_xy = e^2 * x
    // y_res = r * sin(lon) = e^2 * len_xy * y / len_xy = e^2 * y
    
    coord_t const c0 = 0;
    coord_t const e_sqr = formula::eccentricity_sqr<coord_t>(spheroid);

    Point3d res;

    set<0>(res, e_sqr * get<0>(point_3d));
    set<1>(res, e_sqr * get<1>(point_3d));
    set<2>(res, c0);

    return res;
}

template <typename Point3d, typename Spheroid>
inline Point3d projected_to_surface(Point3d const& direction, Spheroid const& spheroid)
{
    typedef typename coordinate_type<Point3d>::type coord_t;

    //coord_t const c0 = 0;
    coord_t const c2 = 2;
    coord_t const c4 = 4;

    // calculate the point of intersection of a ray and spheroid's surface
    // the origin is the origin of the coordinate system
    //(x*x+y*y)/(a*a) + z*z/(b*b) = 1
    // x = d.x * t
    // y = d.y * t
    // z = d.z * t        
    coord_t const dx = get<0>(direction);
    coord_t const dy = get<1>(direction);
    coord_t const dz = get<2>(direction);

    //coord_t const a_sqr = math::sqr(get_radius<0>(spheroid));
    //coord_t const b_sqr = math::sqr(get_radius<2>(spheroid));
    // "unit" spheroid, a = 1
    coord_t const a_sqr = 1;
    coord_t const b_sqr = math::sqr(formula::unit_spheroid_b<coord_t>(spheroid));

    coord_t const param_a = (dx*dx + dy*dy) / a_sqr + dz*dz / b_sqr;
    coord_t const delta = c4 * param_a;
    // delta >= 0
    coord_t const t = math::sqrt(delta) / (c2 * param_a);

    // result = direction * t
    Point3d result = direction;
    multiply_value(result, t);

    return result;
}

template <typename Point3d, typename Spheroid>
inline bool projected_to_surface(Point3d const& origin, Point3d const& direction, Point3d & result1, Point3d & result2, Spheroid const& spheroid)
{
    typedef typename coordinate_type<Point3d>::type coord_t;

    coord_t const c0 = 0;
    coord_t const c1 = 1;
    coord_t const c2 = 2;
    coord_t const c4 = 4;

    // calculate the point of intersection of a ray and spheroid's surface
    //(x*x+y*y)/(a*a) + z*z/(b*b) = 1
    // x = o.x + d.x * t
    // y = o.y + d.y * t
    // z = o.z + d.z * t        
    coord_t const ox = get<0>(origin);
    coord_t const oy = get<1>(origin);
    coord_t const oz = get<2>(origin);
    coord_t const dx = get<0>(direction);
    coord_t const dy = get<1>(direction);
    coord_t const dz = get<2>(direction);

    //coord_t const a_sqr = math::sqr(get_radius<0>(spheroid));
    //coord_t const b_sqr = math::sqr(get_radius<2>(spheroid));
    // "unit" spheroid, a = 1
    coord_t const a_sqr = 1;
    coord_t const b_sqr = math::sqr(formula::unit_spheroid_b<coord_t>(spheroid));

    coord_t const param_a = (dx*dx + dy*dy) / a_sqr + dz*dz / b_sqr;
    coord_t const param_b = c2 * ((ox*dx + oy*dy) / a_sqr + oz*dz / b_sqr);
    coord_t const param_c = (ox*ox + oy*oy) / a_sqr + oz*oz / b_sqr - c1;

    coord_t const delta = math::sqr(param_b) - c4 * param_a*param_c;

    // equals() ?
    if (delta < c0 || param_a == 0)
    {
        return false;
    }

    // result = origin + direction * t

    coord_t const sqrt_delta = math::sqrt(delta);
    coord_t const two_a = c2 * param_a;

    coord_t const t1 = (-param_b + sqrt_delta) / two_a;
    result1 = direction;
    multiply_value(result1, t1);
    add_point(result1, origin);

    coord_t const t2 = (-param_b - sqrt_delta) / two_a;
    result2 = direction;
    multiply_value(result2, t2);
    add_point(result2, origin);

    return true;
}

template <typename Point3d, typename Spheroid>
inline bool great_elliptic_intersection(Point3d const& a1, Point3d const& a2,
                                        Point3d const& b1, Point3d const& b2,
                                        Point3d & result,
                                        Spheroid const& spheroid)
{
    typedef typename coordinate_type<Point3d>::type coord_t;

    coord_t c0 = 0;
    coord_t c1 = 1;

    Point3d n1 = cross_product(a1, a2);
    Point3d n2 = cross_product(b1, b2);

    // intersection direction
    Point3d id = cross_product(n1, n2);
    coord_t id_len_sqr = dot_product(id, id);

    if (math::equals(id_len_sqr, c0))
    {
        return false;
    }

    // no need to normalize a1 and a2 because the intersection point on
    // the opposite side of the globe is at the same distance from the origin
    coord_t cos_a1i = dot_product(a1, id);
    coord_t cos_a2i = dot_product(a2, id);
    coord_t gri = math::detail::greatest(cos_a1i, cos_a2i);
    Point3d neg_id = id;
    multiply_value(neg_id, -c1);
    coord_t cos_a1ni = dot_product(a1, neg_id);
    coord_t cos_a2ni = dot_product(a2, neg_id);
    coord_t grni = math::detail::greatest(cos_a1ni, cos_a2ni);

    if (gri >= grni)
    {
        result = projected_to_surface(id, spheroid);
    }
    else
    {
        result = projected_to_surface(neg_id, spheroid);
    }

    return true;
}

template <typename Point3d1, typename Point3d2>
static inline int elliptic_side_value(Point3d1 const& origin, Point3d1 const& norm, Point3d2 const& pt)
{
    typedef typename coordinate_type<Point3d1>::type calc_t;
    calc_t c0 = 0;

    // vector oposite to pt - origin
    // only for the purpose of assigning origin
    Point3d1 vec = origin;
    subtract_point(vec, pt);

    calc_t d = dot_product(norm, vec);

    // since the vector is opposite the signs are opposite
    return math::equals(d, c0) ? 0
        : d < c0 ? 1
        : -1; // d > 0
}

template <typename Point3d, typename Spheroid>
inline bool planes_spheroid_intersection(Point3d const& o1, Point3d const& n1,
                                         Point3d const& o2, Point3d const& n2,
                                         Point3d & ip1, Point3d & ip2,
                                         Spheroid const& spheroid)
{
    typedef typename coordinate_type<Point3d>::type coord_t;

    coord_t c0 = 0;
    coord_t c1 = 1;

    // Below
    // n . (p - o) = 0
    // n . p - n . o = 0
    // n . p + d = 0
    // n . p = h

    // intersection direction
    Point3d id = cross_product(n1, n2);

    if (math::equals(dot_product(id, id), c0))
    {
        return false;
    }

    coord_t dot_n1_n2 = dot_product(n1, n2);
    coord_t dot_n1_n2_sqr = math::sqr(dot_n1_n2);

    coord_t h1 = dot_product(n1, o1);
    coord_t h2 = dot_product(n2, o2);

    coord_t denom = c1 - dot_n1_n2_sqr;
    coord_t C1 = (h1 - h2 * dot_n1_n2) / denom;
    coord_t C2 = (h2 - h1 * dot_n1_n2) / denom;

    // C1 * n1 + C2 * n2
    Point3d C1_n1 = n1;
    multiply_value(C1_n1, C1);
    Point3d C2_n2 = n2;
    multiply_value(C2_n2, C2);
    Point3d io = C1_n1;
    add_point(io, C2_n2);

    if (! projected_to_surface(io, id, ip1, ip2, spheroid))
    {
        return false;
    }

    return true;
}


template <typename Point3d, typename Spheroid>
inline void experimental_elliptic_plane(Point3d const& p1, Point3d const& p2,
                                        Point3d & v1, Point3d & v2,
                                        Point3d & origin, Point3d & normal,
                                        Spheroid const& spheroid)
{
    typedef typename coordinate_type<Point3d>::type coord_t;

    Point3d xy1 = projected_to_xy(p1, spheroid);
    Point3d xy2 = projected_to_xy(p2, spheroid);

    // origin = (xy1 + xy2) / 2
    origin = xy1;
    add_point(origin, xy2);
    multiply_value(origin, coord_t(0.5));

    // v1 = p1 - origin
    v1 = p1;
    subtract_point(v1, origin);
    // v2 = p2 - origin
    v2 = p2;
    subtract_point(v2, origin);

    normal = cross_product(v1, v2);
}

template <typename Point3d, typename Spheroid>
inline void experimental_elliptic_plane(Point3d const& p1, Point3d const& p2,
                                        Point3d & origin, Point3d & normal,
                                        Spheroid const& spheroid)
{
    Point3d v1, v2;
    experimental_elliptic_plane(p1, p2, v1, v2, origin, normal, spheroid);
}

template <typename Point3d, typename Spheroid>
inline bool experimental_elliptic_intersection(Point3d const& a1, Point3d const& a2,
                                               Point3d const& b1, Point3d const& b2,
                                               Point3d & result,
                                               Spheroid const& spheroid)
{
    typedef typename coordinate_type<Point3d>::type coord_t;

    coord_t c0 = 0;
    coord_t c1 = 1;

    Point3d a1v, a2v, o1, n1;
    experimental_elliptic_plane(a1, a2, a1v, a2v, o1, n1, spheroid);
    Point3d b1v, b2v, o2, n2;
    experimental_elliptic_plane(b1, b2, b1v, b2v, o2, n2, spheroid);

    if (! detail::vec_normalize(n1) || ! detail::vec_normalize(n2))
    {
        return false;
    }

    Point3d ip1_s, ip2_s;
    if (! planes_spheroid_intersection(o1, n1, o2, n2, ip1_s, ip2_s, spheroid))
    {
        return false;
    }

    // NOTE: simplified test, may not work in all cases
    coord_t dot_a1i1 = dot_product(a1, ip1_s);
    coord_t dot_a2i1 = dot_product(a2, ip1_s);
    coord_t gri1 = math::detail::greatest(dot_a1i1, dot_a2i1);
    coord_t dot_a1i2 = dot_product(a1, ip2_s);
    coord_t dot_a2i2 = dot_product(a2, ip2_s);
    coord_t gri2 = math::detail::greatest(dot_a1i2, dot_a2i2);

    result = gri1 >= gri2 ? ip1_s : ip2_s;

    return true;
}

} // namespace formula

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_GEOGRAPHIC_HPP

/* geographic.hpp
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
*/
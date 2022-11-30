// Boost.Geometry

// Copyright (c) 2016-2021, Oracle and/or its affiliates.
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
inline bool projected_to_surface(Point3d const& origin, Point3d const& direction,
                                 Point3d & result1, Point3d & result2,
                                 Spheroid const& spheroid)
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
    coord_t const t2 = (-param_b - sqrt_delta) / two_a;
    geometry::detail::for_each_dimension<Point3d>([&](auto index)
    {
        set<index>(result1, get<index>(origin) + get<index>(direction) * t1);
        set<index>(result2, get<index>(origin) + get<index>(direction) * t2);
    });

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
    Point3d io;
    geometry::detail::for_each_dimension<Point3d>([&](auto index)
    {
        set<index>(io, C1 * get<index>(n1) + C2 * get<index>(n2));
    });

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
    // v1 = p1 - origin
    // v2 = p2 - origin
    coord_t const half = coord_t(0.5);
    geometry::detail::for_each_dimension<Point3d>([&](auto index)
    {
        coord_t const o = (get<index>(xy1) + get<index>(xy2)) * half;
        set<index>(origin, o);
        set<index>(v1, get<index>(p1) - o);
        set<index>(v2, get<index>(p1) - o);
    });

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

    if (! geometry::detail::vec_normalize(n1) || ! geometry::detail::vec_normalize(n2))
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
// Boost.Geometry

// Copyright (c) 2016-2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INTERSECTION_ELLIPTIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INTERSECTION_ELLIPTIC_HPP


#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/formulas/geographic.hpp>

#include <boost/geometry/strategies/spherical/intersection.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace intersection
{

template <typename Spheroid>
struct great_elliptic_segments_calc_policy
    : spherical_segments_calc_policy
{
    explicit great_elliptic_segments_calc_policy(Spheroid const& spheroid = Spheroid())
        : m_spheroid(spheroid)
    {}

    template <typename Point, typename Point3d>
    Point from_cart3d(Point3d const& point_3d) const
    {
        return formula::cart3d_to_geo<Point>(point_3d, m_spheroid);
    }

    template <typename Point3d, typename Point>
    Point3d to_cart3d(Point const& point) const
    {
        return formula::geo_to_cart3d<Point3d>(point, m_spheroid);
    }

    // relate_xxx_calc_policy must live londer than plane because it contains
    // Spheroid object and plane keeps the reference to that object.
    template <typename Point3d>
    struct plane
    {
        typedef typename coordinate_type<Point3d>::type coord_t;

        // not normalized
        plane(Point3d const& p1, Point3d const& p2)
            : normal(cross_product(p1, p2))
        {}

        int side_value(Point3d const& pt) const
        {
            return formula::sph_side_value(normal, pt);
        }

        coord_t cos_angle_between(Point3d const& p1, Point3d const& p2) const
        {
            Point3d v1 = p1;
            detail::vec_normalize(v1);
            Point3d v2 = p2;
            detail::vec_normalize(v2);

            return dot_product(v1, v2);
        }

        coord_t cos_angle_between(Point3d const& p1, Point3d const& p2, bool & is_forward) const
        {
            coord_t const c0 = 0;

            Point3d v1 = p1;
            detail::vec_normalize(v1);
            Point3d v2 = p2;
            detail::vec_normalize(v2);

            is_forward = dot_product(normal, cross_product(v1, v2)) >= c0;
            return dot_product(v1, v2);
        }

        Point3d normal;
    };

    template <typename Point3d>
    plane<Point3d> get_plane(Point3d const& p1, Point3d const& p2) const
    {
        return plane<Point3d>(p1, p2);
    }

    template <typename Point3d>
    bool intersection_points(plane<Point3d> const& plane1,
                             plane<Point3d> const& plane2,
                             Point3d & ip1, Point3d & ip2) const
    {
        typedef typename coordinate_type<Point3d>::type coord_t;

        Point3d id = cross_product(plane1.normal, plane2.normal);
        // NOTE: the length should be greater than 0 at this point
        // NOTE: no need to normalize in this case

        ip1 = formula::projected_to_surface(id, m_spheroid);

        ip2 = ip1;
        multiply_value(ip2, coord_t(-1));

        return true;
    }

private:
    Spheroid m_spheroid;
};

template <typename Spheroid>
struct experimental_elliptic_segments_calc_policy
{
    explicit experimental_elliptic_segments_calc_policy(Spheroid const& spheroid = Spheroid())
        : m_spheroid(spheroid)
    {}

    template <typename Point, typename Point3d>
    Point from_cart3d(Point3d const& point_3d) const
    {
        return formula::cart3d_to_geo<Point>(point_3d, m_spheroid);
    }

    template <typename Point3d, typename Point>
    Point3d to_cart3d(Point const& point) const
    {
        return formula::geo_to_cart3d<Point3d>(point, m_spheroid);
    }

    // relate_xxx_calc_policy must live londer than plane because it contains
    // Spheroid object and plane keeps the reference to that object.
    template <typename Point3d>
    struct plane
    {
        typedef typename coordinate_type<Point3d>::type coord_t;

        // not normalized
        plane(Point3d const& p1, Point3d const& p2, Spheroid const& spheroid)
            : m_spheroid(spheroid)
        {
            formula::experimental_elliptic_plane(p1, p2, origin, normal, m_spheroid);
        }

        int side_value(Point3d const& pt) const
        {
            return formula::elliptic_side_value(origin, normal, pt);
        }

        coord_t cos_angle_between(Point3d const& p1, Point3d const& p2) const
        {
            Point3d const v1 = normalized_vec(p1);
            Point3d const v2 = normalized_vec(p2);
            return dot_product(v1, v2);
        }

        coord_t cos_angle_between(Point3d const& p1, Point3d const& p2, bool & is_forward) const
        {
            coord_t const c0 = 0;

            Point3d const v1 = normalized_vec(p1);
            Point3d const v2 = normalized_vec(p2);
            
            is_forward = dot_product(normal, cross_product(v1, v2)) >= c0;
            return dot_product(v1, v2);
        }

        Point3d origin;
        Point3d normal;

    private:
        Point3d normalized_vec(Point3d const& p) const
        {
            Point3d v = p;
            subtract_point(v, origin);
            detail::vec_normalize(v);
            return v;
        }

        Spheroid const& m_spheroid;
    };

    template <typename Point3d>
    plane<Point3d> get_plane(Point3d const& p1, Point3d const& p2) const
    {
        return plane<Point3d>(p1, p2, m_spheroid);
    }

    template <typename Point3d>
    bool intersection_points(plane<Point3d> const& plane1,
                             plane<Point3d> const& plane2,
                             Point3d & ip1, Point3d & ip2) const
    {
        return formula::planes_spheroid_intersection(plane1.origin, plane1.normal,
                                                     plane2.origin, plane2.normal,
                                                     ip1, ip2, m_spheroid);
    }

private:
    Spheroid m_spheroid;
};


template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
struct great_elliptic_segments
    : ecef_segments
        <
            great_elliptic_segments_calc_policy<Spheroid>,
            CalculationType
        >
{};

template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
struct experimental_elliptic_segments
    : ecef_segments
        <
            experimental_elliptic_segments_calc_policy<Spheroid>,
            CalculationType
        >
{};


}} // namespace strategy::intersection

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_INTERSECTION_ELLIPTIC_HPP

/* intersection_elliptic.hpp
jsB9n0SarCXOcicaui7F0aHVt/2ONhzFtRMZJpzL465GcQcXdBn2qSYPiEbblzE9XacWoms3Hk4qTA/eqMG46Gxs6QFCIGyUY5yGRO8UJq7nbFUVnniAVTsyWlyZGmj6Q1iQ0cnJPm/0CINiik7vmvgn+ruBAsGVOivhuVM3LvDyuzJ69iwxGO0XRznHb7KCqzccm/m2KKLy0C5ZMGNOm62MdZlOgdSiTAarQLlAKozFtaS4UH7JTi4kHyisGL6b7gnZHtpk51EbvXbYbzWDPyMBeqJCoo9qF2r74m0ynyrM3VUb8g7x8zPxMlHsbP4DSYTh77h+PsG41WoCz1RVLmYZRaUYRF5vLaTVSCk+FrU6d6RWJ6HWN82b9QhD1V+83v+v5ARUpAwcPHYR4w6H50QTNPr8AKbtMJ6DdXFjnHVK9E46MYXSQkQB4h99dmcEy/GunZtoGw/i4CzgqeLJGDe21KGgmRNPNBz2S+7oLqZiBKmMJz4kRUwxdTesYWcqz2c7CO+3/T9qHGtd/tnQEk7r9Z3G/zSOe30MBEndM+YikJsD6ZQkhUoDZO3NNqC2tdaFgqsKP19WS9w9FPGVEjQOAjJSUr/FOJQybWu584dMDAXFADx2pTfSlFYzeRr5fG6jsniePM+SNmPA
*/
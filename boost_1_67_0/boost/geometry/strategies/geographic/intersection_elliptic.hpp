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
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
*/
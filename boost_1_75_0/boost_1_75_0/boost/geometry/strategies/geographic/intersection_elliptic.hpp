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
2qhJKCDq2kJAt2fAxy5pm/jVdmmMyzm4dSdAU6nGsh0CnKUKin4SI2nS79rq3GReQCFQ7MZeiF2bidpe/TU21KlUSGzDM6g6ndffuBWJBX1c51tGUe+FqzeddZlA/Ce4q0qMbb2Puy30GN1XijlbTwlvQCDHMtGy34uo2JhmN419y8klHIM1F4sVNFard/WKu29E8Pt0Ykc5B+L41967aZvNmM7EzElIRtVSuZvkbKVRu0c1Pkl+JNYjkufY90GZRiym6RoCaLuz3I0cAqgEhxr8lXobvfaukZUjm6f8c4Otzc2ernIV7SGC9kvr8ITI8cuQ0vC9S25MLye3KmC8825tPdOfs+qihuSTI5CRH5ERCc7OCUgjtJIkkBC73E+37rK1mqzMvlacieozJQy2tAh9h66WmRw2dDd0H2Vq67CgewAm07FvbZFtb0NNxdR6rnYxGVPzncKRZ3v67pC8PUyWcKUZPnxI1VHtOehDA3BPNxcN8cApa0Fqe5UqCpNeolvtyiKs7bqtt5Bo3PDvCTzWrYa9n/MmtXOjZf2CcQ6r6mrNVpQlvRsJ0KH7MmkEdrY7eVMW0OhPjJQmTPffHBacDZp01w4VoQ1JECS+R0Q46/5pcYJsXU+mxSA/0jJWKrI8m22a/UE5yVI6X/USiWS5BL2OBr+9xVPegtFjOTbmEBMYYNL8qVoXyVZrojA328TVDbC70mfomVNG
*/
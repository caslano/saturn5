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
B9gC/gjNdul6g3BwmUO73EZ6msPtsC18RervDjgGvg6nwp1wPtwFb4JEqeIvkfg32+Pn7r/M+2Fr+AtMh1GEXwgrwyJYBa6B1eB6WN2/3bwZvHyipP5VlvpXBar8KiNcdVlPuQB2gjWgai+7CQcvdWgvvWtS1WEf+DvYF3aF/fz7593B5V5eE7lwIOwEr4Bmf1Mk4R506G9ek3l/CbwC7oJD4G6YD9+C98K34WlYgEt+i/jgtxJfHeiV+OpKvtWDcdAFE2E0nAwvggWwAbwNNoQvwBi4FzaC+2Fj+D5sAj+HTeEJ2EzKIQNX+DZ6wCWiR004RfTYJe9Bb8B2cDfsBN+GPeAeOBDuhWPgPjgFvgNvhO/ChXC/WifA7UEe7O2wTrBR1rM3wYvhZtgePg+7wxegat8STy+n932Zb8bAONgImuVYKuHSHcrxk+oy3sDO8Ai8HJbCofAzmAI/h6o+7Q0+v3hd1iF3wlawRPSYiyvaay3/2jBLwi2SfFgMm8Kb4EBYAIfBm+H1cClcDJfBm+GtcDVcDnfA22AJvAOegCugXg4IPrBPxk9ZL2yjlYOsv++IQj58DV4MX4eD4U44Er4BJ8I3YQbcDefCPXA53AsfgPvgU/BdWAz3w4/ge/BP8AD8HB6EP8IP4YXo8BFsCA/BVvCPMA4ehv3gJ3AkPAInwT/D6fAvcC48Cm+DpXA1/AxuhCfgX+FX8Dt4EtYi/V/DWPgNbA2/hW3hKdgbnoaj4Bk4Fn4P1fvS/uD7Jn1kHO0LL4f9oBoP3wu+bhEn60DdoAt2928/7wVvPy9KvXkJXgy3wfbwVdgd7pDyL9ScxBMbZcRTT8Yg7W8czzWCiRLuGtgXToZXwynwBjgVeuAN8BaYBFfAaXAXTIUHYZrUPzesj7x0GAMzYTM4A0q+sBgYfF2mvczXO8CesCM8DYsJkCDhnqtqhNP6pzVSn5fLftId8Aa4AmbDlXARvBuugIXwfngffAaugsXwQfhn+BCsTZyPwObwMdgJPg77wSfgEPgknAifgjfAp+EsuAbeAtfCR+AzcC1cB1+D6+FuuAF+CDfCP8Pfw6/gZngaPgejKpNuWAM+DxvBF2BLuBXGwRfhSPgyTIDb4S3wVbgDvg53w53wU1gCj8Fd8Bx8A15EXr4JG8LdsAXcA0fBvTAR7oOz4DtwDtwP58P34Rr4B/g+/AiegoegWZ/jPg6+H5Ql84BZsDXMgUOhBw6Hs+FpeBhXKPHskvrcuBJ6SDx9ZTzoB9vBAXAgvBxOgwNhJoyH+XAQfAgOhkVwFHwOXgXfgaPhN/BqeBaOhw2ROwH2hYkwHk6Eo+EkOAleB3Ph9bAAToEr4FRYDG+AL8NkuAOmQDOfDvwx+P5TmuSTW/JpOoyHGXAIzITqvfYw8cCpDu3rCZ6LhUVwEnxSwt2GK5ZwRyVcXbhQwu2pRbuEe2FT+A5sC9+Fo+B+mAg/gG74B7gEHoRPwI/hevhH+CY8DN+Cn8BD8Aj8FP4ZnoYZlcmPTwx9Rso6rCZniqzDtqqNPrAj7Ao7wYmwM0yB3WEB7AGXw17wAdgProf94WY4AG6BQ+A7cCj8AF4J/wKHQ338hrWj0AU2g6NgLLwajoBj4NVwHEyG46EbToB5MBHeDq+BT8Br4T44ER6Fk+CP8DpYjzReDwfAyXA8nAJnwBvgEpgC18NpcDN0w1dgOiyF0+HnMBP+A86A1cjDmbATzIJxcBbsDrNhPMyB42EenAa9MBvmw3lwDrwFzoV3w/nwCbgAvggXwffgYvg5LICVtfVVGA2XwXh4CxwGl8NEeDtcCu+At8G74CNwJdwO74avwkK4H94DT8F7YRXqx32wFVwFu8A=
*/
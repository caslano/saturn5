// Boost.Geometry

// Copyright (c) 2019 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_INTERPOLATE_POINT_SPHERICAL_HPP
#define BOOST_GEOMETRY_FORMULAS_INTERPOLATE_POINT_SPHERICAL_HPP

namespace boost { namespace geometry { namespace formula
{

template <typename CalculationType>
class interpolate_point_spherical
{
    typedef model::point<CalculationType, 3, cs::cartesian> point3d_t;

public :

    template <typename Point>
    void compute_angle(Point const& p0,
                       Point const& p1,
                       CalculationType& angle01)
    {    
        m_xyz0 = formula::sph_to_cart3d<point3d_t>(p0);
        m_xyz1 = formula::sph_to_cart3d<point3d_t>(p1);
        CalculationType const dot01 = geometry::dot_product(m_xyz0, m_xyz1);
        angle01 = acos(dot01);
    }

    template <typename Point>
    void compute_axis(Point const& p0,
                      CalculationType const& angle01)
    {
        CalculationType const c0 = 0, c1 = 1;
        CalculationType const pi = math::pi<CalculationType>();

        if (! math::equals(angle01, pi))
        {
            m_axis = geometry::cross_product(m_xyz0, m_xyz1);
            geometry::detail::vec_normalize(m_axis);
        }
        else // antipodal
        {
            CalculationType const half_pi = math::half_pi<CalculationType>();
            CalculationType const lat = geometry::get_as_radian<1>(p0);

            if (math::equals(lat, half_pi))
            {
                // pointing east, segment lies on prime meridian, going south
                m_axis = point3d_t(c0, c1, c0);
            }
            else if (math::equals(lat, -half_pi))
            {
                // pointing west, segment lies on prime meridian, going north
                m_axis = point3d_t(c0, -c1, c0);
            }
            else
            {
                // lon rotated west by pi/2 at equator
                CalculationType const lon = geometry::get_as_radian<0>(p0);
                m_axis = point3d_t(sin(lon), -cos(lon), c0);
            }
        }
    }

    template <typename Point>
    void compute_point(CalculationType const& a, Point& p)
    {
        CalculationType const c1 = 1;

        // Axis-Angle rotation
        // see: https://en.wikipedia.org/wiki/Axis-angle_representation
        CalculationType const cos_a = cos(a);
        CalculationType const sin_a = sin(a);
        // cos_a * v
        point3d_t s1 = m_xyz0;
        geometry::multiply_value(s1, cos_a);
        // sin_a * (n x v)
        point3d_t s2 = geometry::cross_product(m_axis, m_xyz0);
        geometry::multiply_value(s2, sin_a);
        // (1 - cos_a)(n.v) * n
        point3d_t s3 = m_axis;
        geometry::multiply_value(s3, (c1 - cos_a) *
                                 geometry::dot_product(m_axis, m_xyz0));
        // v_rot = cos_a * v + sin_a * (n x v) + (1 - cos_a)(n.v) * e
        point3d_t v_rot = s1;
        geometry::add_point(v_rot, s2);
        geometry::add_point(v_rot, s3);

        p = formula::cart3d_to_sph<Point>(v_rot);
    }

private :
    point3d_t m_xyz0;
    point3d_t m_xyz1;
    point3d_t m_axis;
};

}}} // namespace boost::geometry::formula

#endif // BOOST_GEOMETRY_FORMULAS_INTERPOLATE_POINT_SPHERICAL_HPP

/* interpolate_point_spherical.hpp
mquBvGaX7x9ju7LKtzBd2//LWgtYf2BwKrdh9J4d381oT9M40me1fcHgUEAVGg2oe9+F0uEmsY+9/tnk6zOFUdyh2h3ymvLvoPUklbJpSLJRrNKYJPQAdo9tYy459Ahfy/F7UdvsOXGz8NeXsQP7psKqG6/3JP1fGx5rU99Xvz1+RB+Wp6q/0qk2M3vQiPkYehLy5nPWRFyrZMmd1Y6SXggWqv9LUYC4KOCVjFrAq9F90GerATZkH384XyupD3fRwqO/ONOhtACYwKbcjWCcylIafekHqDld2qv+heR3HaqBEqKpRlvuWvFwsWJRb8qCxx2haWbyuCBr+KXA+/OB+BL6DVrMU3g8YnBy1v3sv6NLPy30P/v2J+Q/X17OWBf4o9lq2wxK+N+ARKu/w8w28h1X1uocJ1udFUFfKBSIIJ4bZqj+C0aUmXkVIc+S/ue10PM0j+HtrDe2UdxeQhbPPBSYHz5OefByLe7T/s9luoArZrLUwMHfAU/sAUdbu0+dTdzmfEDJWNYtbt/zMkucMDMPCptbDyDgb+gyQIWaWXU5GNfHweAP9Wn+cg==
*/
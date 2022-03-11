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
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
*/
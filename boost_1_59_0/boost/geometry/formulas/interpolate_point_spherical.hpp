// Boost.Geometry

// Copyright (c) 2019-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_INTERPOLATE_POINT_SPHERICAL_HPP
#define BOOST_GEOMETRY_FORMULAS_INTERPOLATE_POINT_SPHERICAL_HPP

#include <boost/geometry/formulas/spherical.hpp>
#include <boost/geometry/geometries/point.hpp>

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
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
ZqXbR7zzdSZ2eNlD6LZD62SSKJwmSX5/CwXFCtgLo7xOrhQ2OOuPQts9X3cemsZu24KoXsRm4zwLw21Dvee3NfDaWKMlE8akKIjtEixeOntr4LkUkT+/XcivVGPqicrmu9svpScpz0K87Jm2tDGYhaNevbuebJPsb/3BRs9Cu0sOBgNyiduxhS824oUbswoc5rkFnmNsMM16gYFU8nsRWwu9qpDYizS9RQbx2yyMljw8gfssMg/vWAkwdC3o9XRwKDpIAjN88/LKj1noyCW9K7uKw+L5seWVvHgY010ZGent7sENHlL2Tyjbgai2TL2Y8xpR6QuF1xUxnZuVwVZl0WoK1MhXY6JXS1Y76SeK1oqVeKKsrJKF3oPoNXKXKzvpqfe/9d3J/jlyDNVECFX3J9PzE+Ph8IZKITAO5WRvqWv8bufHH/rZhpSvDKZD5vpgn3z6fMIJ716iJ5u7BVNfM6jnyYzHCR/55wnNLar66RbzQmnueSVwgxRfoWMxjT4G3BfV/gi+FM89dfeEIin80/2LMMfOgjN6OKQb4Ks/QfEBc9NuwG0aWL1wEF3iUTgKvDiDiXRhI3f7kEIYBd3ueDgeBPh6XpaAxEkbTSxFT1RTvIMBR2iN4zwaYAgt9ks/aG1eGXLPwYXXUU7v
*/
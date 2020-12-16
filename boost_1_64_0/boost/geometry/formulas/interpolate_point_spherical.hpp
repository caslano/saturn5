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
9ER7Yj3DPfGekZ7RnvGeyR7Va+vN7o31DffF+0b6En2jfWN9430TfZN9/COcflt/dr+9P6ff0Z/bn9df2O/sL+sv7/f0+/ub+sP9Lf2R/mh/rH+4P94/0p/oH+0f6x/vn+if7OcvQA/YBrIH7AM5A46B3IG8gcIB50DZgH+gaSA00DwQHmgZiAxEB2IDwwPxgZGBxMDowNjA+MDEwOQAf11/0DaYPWgfzBl0DOYOOgfLBssHPYP+wabB0GDzYHiwZTAyGB2MDQ4PxgdHBhODo4Njg+ODE4OTg/zDniHbUPaQYyh3KG+ocMg5VDZUPuQZ8g81DYWGmofCQy1DkaHoUGxoeCg+NDKUGBodGhsaH5oYmhxSjrlqB3sgWyQ7Yo/kRByR3EhepDDijJRFyiOeiD/SFAlFmiPhSEskEolGYpHhSDwyEklERiMTkcmIas1qtbVmt9pbc1odrbmtea2Frc7WstbyVk+rv7WpNdTa3BpubWmNtEZbY63DrYnW0dax1vHWidbJVtWW1WZry26zt+W0Odpy2/LaCtucbWVt5W2eNn9bU1uorbkt3NbSFmsbbou3jbQl2kbbxtrG2ybaJttUe1a7rT273d6e0+5oz23Pay9sd7aXtZe3e9r97U3t4faW9kh7tD3WPtwebx9pT7SPto+1j7dPtE+281dRO2wd2R32jpwOR0duR15HYYezo6zD39HUEepo7gh3tHREOqIdsY7hjnjHSEeiY7RjrGO8Y6JjsoN/VtVp68zutHfmdDo6czudnWWd5Z2eTn9nU2eos7kz3NnSGemMdsY6hzvjnSOdic7RzrHO8c6JzslO1ZXVZevK7nJ05XbldRV2ObvKusq7PF3+rqauUFdzV7irpSvSFe2KdQ13xbtGuhJdo11jXeNdE12TXbbu7G57d063ozu3O6+7sNvZXdZd3u3p9nc3dYe6m7vD3S3dke5od6x7uDvePdKd6B7tnuie7OavzEVt0eyoPZoTdURzo3nRwqgzWhYtj3qi/mhTNBRNjqKoMY4S0dHoWHQ8OhGdjKqerB5bT3ZP+rhyMrLKGVt+Y3Q1G+MrObYSjK4xxteEMcKyjDFm783pdfTm9ub1FvY6e8t6y3s9vf7ept5wb0tvpDfaG+sd7o33jvQmekd7x3rHeyd6J3v5J259tr7sPntfTp+jL7cvr6+wz9lX1ufva+oL9TX3hfta+iJ90b6/Z/ymj91Qf/PfNX7Tx275gOfvGr/pYzdvsPDvGr8qb66yK6V0X411jxv9lUVf0VNGPynnXFXGdfrB6APa32h72t2Y02hzo71pa6OdaWOjfUO9zUbb0q5Gm9Keui2NdiyjDVU5Y55scyJ+RrNixIYZlXZGXYyRldfezGjJ7ijviBLxuZ0hothGpEaIRAfRFqeMTiJmLJrT46fnFU8N03v2Pk9fjB7Io5UT/dm0XJSWyR0MUVsbM1KEGYeH+ueqHOBgXolHspgrWpgPctr8jHHFGA4zTu0dJAjNVQeBjRnJSTnDzDwJZhwbs4yTmSXMbJKQmcSYR2QWMeYQmUH0/BFpi1Irc/Zg7tDzhjlnyIyh54sQNQ7LbGHMFTJTME/oOULmhzFGv41Rn8eI9zPSI4zxOON7jLGtGNc5XXm0kp9xHGH8Jhi1Wd12Rqvu4LnKAxg5xrhh1OiRYoyTrN70yM0mallzjonaFiKWeD0mWrNZaYhVI1J5wNhcdSLQdc8x6sdJOFPtBCpiY353yJzeTFtmM0dHab3cthCtY2PujFBrB3NgvCOLea2FmuV0+amLYr4JE6N25owY80IeNUj0ZBNrUcZrbl+IMWijxBFK5mCsxAeyiP8W1qecIT9rjopkEm8=
*/
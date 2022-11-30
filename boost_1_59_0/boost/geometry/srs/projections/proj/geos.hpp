// Boost.Geometry - gis-projections (based on PROJ4)

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 5.0.0

// Original copyright notice:

// Copyright (c) 2004   Gerald I. Evenden
// Copyright (c) 2012   Martin Raspaud

// See also (section 4.4.3.2):
//   http://www.eumetsat.int/en/area4/msg/news/us_doc/cgms_03_26.pdf

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_PROJECTIONS_GEOS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GEOS_HPP

#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace geos
    {
            template <typename T>
            struct par_geos
            {
                T           h;
                T           radius_p;
                T           radius_p2;
                T           radius_p_inv2;
                T           radius_g;
                T           radius_g_1;
                T           C;
                bool        flip_axis;
            };

            template <typename T, typename Parameters>
            struct base_geos_ellipsoid
            {
                par_geos<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T r, Vx, Vy, Vz, tmp;

                    /* Calculation of geocentric latitude. */
                    lp_lat = atan (this->m_proj_parm.radius_p2 * tan (lp_lat));
                
                    /* Calculation of the three components of the vector from satellite to
                    ** position on earth surface (lon,lat).*/
                    r = (this->m_proj_parm.radius_p) / boost::math::hypot(this->m_proj_parm.radius_p * cos (lp_lat), sin (lp_lat));
                    Vx = r * cos (lp_lon) * cos (lp_lat);
                    Vy = r * sin (lp_lon) * cos (lp_lat);
                    Vz = r * sin (lp_lat);

                    /* Check visibility. */
                    if (((this->m_proj_parm.radius_g - Vx) * Vx - Vy * Vy - Vz * Vz * this->m_proj_parm.radius_p_inv2) < 0.) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }

                    /* Calculation based on view angles from satellite. */
                    tmp = this->m_proj_parm.radius_g - Vx;

                    if(this->m_proj_parm.flip_axis) {
                        xy_x = this->m_proj_parm.radius_g_1 * atan (Vy / boost::math::hypot (Vz, tmp));
                        xy_y = this->m_proj_parm.radius_g_1 * atan (Vz / tmp);
                    } else {
                        xy_x = this->m_proj_parm.radius_g_1 * atan (Vy / tmp);
                        xy_y = this->m_proj_parm.radius_g_1 * atan (Vz / boost::math::hypot (Vy, tmp));
                    }
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T Vx, Vy, Vz, a, b, det, k;

                    /* Setting three components of vector from satellite to position.*/
                    Vx = -1.0;
                        
                    if(this->m_proj_parm.flip_axis) {
                        Vz = tan (xy_y / this->m_proj_parm.radius_g_1);
                        Vy = tan (xy_x / this->m_proj_parm.radius_g_1) * boost::math::hypot(1.0, Vz);
                    } else {
                        Vy = tan (xy_x / this->m_proj_parm.radius_g_1);
                        Vz = tan (xy_y / this->m_proj_parm.radius_g_1) * boost::math::hypot(1.0, Vy);
                    }

                    /* Calculation of terms in cubic equation and determinant.*/
                    a = Vz / this->m_proj_parm.radius_p;
                    a   = Vy * Vy + a * a + Vx * Vx;
                    b   = 2 * this->m_proj_parm.radius_g * Vx;
                    if ((det = (b * b) - 4 * a * this->m_proj_parm.C) < 0.) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }

                    /* Calculation of three components of vector from satellite to position.*/
                    k  = (-b - sqrt(det)) / (2. * a);
                    Vx = this->m_proj_parm.radius_g + k * Vx;
                    Vy *= k;
                    Vz *= k;

                    /* Calculation of longitude and latitude.*/
                    lp_lon = atan2 (Vy, Vx);
                    lp_lat = atan (Vz * cos (lp_lon) / Vx);
                    lp_lat = atan (this->m_proj_parm.radius_p_inv2 * tan (lp_lat));
                }

                static inline std::string get_name()
                {
                    return "geos_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_geos_spheroid
            {
                par_geos<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T Vx, Vy, Vz, tmp;

                    /* Calculation of the three components of the vector from satellite to
                    ** position on earth surface (lon,lat).*/
                    tmp = cos(lp_lat);
                    Vx = cos (lp_lon) * tmp;
                    Vy = sin (lp_lon) * tmp;
                    Vz = sin (lp_lat);

                    /* Check visibility.*/
                    // TODO: in proj4 5.0.0 this check is not present
                    if (((this->m_proj_parm.radius_g - Vx) * Vx - Vy * Vy - Vz * Vz) < 0.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );

                    /* Calculation based on view angles from satellite.*/
                    tmp = this->m_proj_parm.radius_g - Vx;

                    if(this->m_proj_parm.flip_axis) {
                        xy_x = this->m_proj_parm.radius_g_1 * atan(Vy / boost::math::hypot(Vz, tmp));
                        xy_y = this->m_proj_parm.radius_g_1 * atan(Vz / tmp);
                    } else {
                        xy_x = this->m_proj_parm.radius_g_1 * atan(Vy / tmp);
                        xy_y = this->m_proj_parm.radius_g_1 * atan(Vz / boost::math::hypot(Vy, tmp));
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T Vx, Vy, Vz, a, b, det, k;

                    /* Setting three components of vector from satellite to position.*/
                    Vx = -1.0;
                    if(this->m_proj_parm.flip_axis) {
                        Vz = tan (xy_y / (this->m_proj_parm.radius_g - 1.0));
                        Vy = tan (xy_x / (this->m_proj_parm.radius_g - 1.0)) * sqrt (1.0 + Vz * Vz);
                    } else {
                        Vy = tan (xy_x / (this->m_proj_parm.radius_g - 1.0));
                        Vz = tan (xy_y / (this->m_proj_parm.radius_g - 1.0)) * sqrt (1.0 + Vy * Vy);
                    }
                    
                    /* Calculation of terms in cubic equation and determinant.*/
                    a   = Vy * Vy + Vz * Vz + Vx * Vx;
                    b   = 2 * this->m_proj_parm.radius_g * Vx;
                    if ((det = (b * b) - 4 * a * this->m_proj_parm.C) < 0.) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }

                    /* Calculation of three components of vector from satellite to position.*/
                    k  = (-b - sqrt(det)) / (2 * a);
                    Vx = this->m_proj_parm.radius_g + k * Vx;
                    Vy *= k;
                    Vz *= k;

                    /* Calculation of longitude and latitude.*/
                    lp_lon = atan2 (Vy, Vx);
                    lp_lat = atan (Vz * cos (lp_lon) / Vx);
                }

                static inline std::string get_name()
                {
                    return "geos_spheroid";
                }

            };

            inline bool geos_flip_axis(srs::detail::proj4_parameters const& params)
            {
                std::string sweep_axis = pj_get_param_s(params, "sweep");
                if (sweep_axis.empty())
                    return false;
                else {
                    if (sweep_axis[1] != '\0' || (sweep_axis[0] != 'x' && sweep_axis[0] != 'y'))
                        BOOST_THROW_EXCEPTION( projection_exception(error_invalid_sweep_axis) );

                    if (sweep_axis[0] == 'x')
                        return true;
                    else
                        return false;
                }
            }

            template <typename T>
            inline bool geos_flip_axis(srs::dpar::parameters<T> const& params)
            {
                typename srs::dpar::parameters<T>::const_iterator
                    it = pj_param_find(params, srs::dpar::sweep);
                if (it == params.end()) {
                    return false;
                } else {
                    srs::dpar::value_sweep s = static_cast<srs::dpar::value_sweep>(it->template get_value<int>());
                    return s == srs::dpar::sweep_x;
                }
            }

            // Geostationary Satellite View
            template <typename Params, typename Parameters, typename T>
            inline void setup_geos(Params const& params, Parameters& par, par_geos<T>& proj_parm)
            {
                std::string sweep_axis;

                if ((proj_parm.h = pj_get_param_f<T, srs::spar::h>(params, "h", srs::dpar::h)) <= 0.)
                    BOOST_THROW_EXCEPTION( projection_exception(error_h_less_than_zero) );

                if (par.phi0 != 0.0)
                    BOOST_THROW_EXCEPTION( projection_exception(error_unknown_prime_meridian) );

                
                proj_parm.flip_axis = geos_flip_axis(params);

                proj_parm.radius_g_1 = proj_parm.h / par.a;
                proj_parm.radius_g = 1. + proj_parm.radius_g_1;
                proj_parm.C  = proj_parm.radius_g * proj_parm.radius_g - 1.0;
                if (par.es != 0.0) {
                    proj_parm.radius_p      = sqrt (par.one_es);
                    proj_parm.radius_p2     = par.one_es;
                    proj_parm.radius_p_inv2 = par.rone_es;
                } else {
                    proj_parm.radius_p = proj_parm.radius_p2 = proj_parm.radius_p_inv2 = 1.0;
                }
            }

    }} // namespace detail::geos
    #endif // doxygen

    /*!
        \brief Geostationary Satellite View projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - h: Height (real)
         - sweep: Sweep axis ('x' or 'y') (string)
        \par Example
        \image html ex_geos.gif
    */
    template <typename T, typename Parameters>
    struct geos_ellipsoid : public detail::geos::base_geos_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline geos_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::geos::setup_geos(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Geostationary Satellite View projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - h: Height (real)
         - sweep: Sweep axis ('x' or 'y') (string)
        \par Example
        \image html ex_geos.gif
    */
    template <typename T, typename Parameters>
    struct geos_spheroid : public detail::geos::base_geos_spheroid<T, Parameters>
    {
        template <typename Params>
        inline geos_spheroid(Params const& params, Parameters const& par)
        {
            detail::geos::setup_geos(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_geos, geos_spheroid, geos_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(geos_entry, geos_spheroid, geos_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(geos_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(geos, geos_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GEOS_HPP


/* geos.hpp
RTuJGY+CBPhzMc7Z2nTuZt3uL3gTffbUew5IY2Eu5hf3wFfwDU/OZuPi5cPkR1HejbzAoKxFX5nRMfFyTtEJY7x8QK4yDSjZS2g1vdJZLOIKmIFuCDDJ1mKP4lOMRFxehWLmHCdbi82CyTen0PrSOzLXSdNQEY3OaDsmZXuVKgdMuC6lKp9VFRo7i6ucCYcyBwPw2mTsSmQ91mks7qLmYFoLvEH4zionZFEb4J9DbbAJgkOQHNJjlDYk2HZsktyZRxAr+BsxR8zGv9QKgHl5N7ZNF53OqkzFVRZ2fRFEGoFrU33+AMsurjKnhWvV92Ba66MuWJa3I60gInELm2MpnmMiD7BhZKQgr9rnyl22GrkTnSjAqp99/1U/qbxDVJ+9qG/9JiBWCzU25tChn8U3QmlwG5HCjrcdKHK8SIbCMCgnTkPw5Xj1+/xnv9Lr4r73Xbh3gercdBAw49Vn2EkCJlOazihNZ5Wmc0oTVwN1zMeLfWdZ9bni6jPhG3UDukCNGj2rRs+QR4nXYSHBBeDiT/Waa7T3u33vlz6yJMYLDiNupZdbf3ZVw9+CEVmhpX+dLv3sZbVu9NnL5hEbtyYzO+UaxE1l92u0I93aY4Kh/JrArdtpIttae0BdaQY1ezyB5tiTbm/Jdk0iW7ayxkaYcK87CYhzKpImkq0eD0QMKD89gw4a0MiMz2nX42nAFB1kKcUsEdu+VieKnHpMbXQN1o4kn8JvgORMxtkEejd+KbRsc7+Gc8W65iMjhUsSZgatZ/Amzjo0VuhkTIgAhDU30xQAKYDJyO0Yw+KM+5Ryu4iIW0o9Pctvj1uyPYeXF4vamE1IH9btcws8B1ZOFG60QKBQXxP8kBzZyVSF8CQxhlxDoAIsoiNmisDDJ1FjIKKTu5wRXY0Y+Fo91MqIQe50BtQfJt0soOYCPXgNB6MROkiYwVCQte3fhIPcfIHFixsa8ls0gq2tzwor6DDuwd16v3AjpRs6iZ9q6JSrE6/7uWUktBSGuGXwX4L/eGzUCNmWBWgPEBFG4MPGiiGGMTrz6mmakIxJcgHx9RshSmJsw0giihlJ5NTWn8A0EjBy8C981UANxnnxCoJo7xE+7Xk9LlZZ+KKE/BtD5NAGvS7E9vHDoT+iwWQpxv1xA3rfMsmdxgDMdm+AHAVD/NcvYLzFK2IhomxzMiIbE+OeB23hjk5ng3RxcQKHZ0qqmCyquAcp/4bOlwzwi6QwuPDyEzkbgcHmj4tEwhPMajxeTGHoi2+LQzVms7Ya0xYDxnDIoUAWt9/mOWpd+wlGTsDzxxpyS+FUf7JXZC4CbirGB/BT7mm9qIoQMbdQCDGu4L8TlsixsEBq73Cq8rEbIW02azChJwg9ekoWXhIK9eLXiSc8+kpaEh1aFfDES36arIN74VF9TQxRkppfS0rNv0kN26TU7B2ZdkXE5CudJcKXhEwT9elFl1U1MeVvZ/IMRb8l5qI8rG/Ii+j9tJGcTXa2ZXzVP+t1dB+0AR6AWyCL0e1C5oGxtN9k2P8xGq2+rBmtlkFkGf9zz8d49LlZN/oICj8xyKuOp66UV7UFAdn/xodHQwZpL2ulnMWL+vY9TBoXLKfWVsQ69Vtbkfv6pR/4Ja9fusPvlwr81rZ27GRLpjzgLehbc7Xo/MTyCMIVJZ5IvdogXs0oAE6UH9EXvxMZI3fmuo4tHho0tiDFEuXflNZ1DFJDWvYcpi0+OjcxgVE2byJHPPgj+gDnwOUz7LhCESO7UFe8lhQU+stvOfe5CiISe5bi1pEETm+gyduJsR5R1qIqw180jQC2i0oiem+Ay6YU+LsW6Q/wJ0xpiPDsCyGAhrhji+ZtMou3nL+EWvUvz6sqL4Y2hIRw/CMJheOILpzTCxL5eM39IvrnNqYAkTPQ70lYKhnRoYvI5QFoGiA30Rm3DQaNxQAKLPXTTbKShD5InAH+f+aRUuU16fP0FSZIJdY+XPdQ0CnUVkaNccq36IQYp1uZD0pwyun9qytTTu+/hnltYXc8NlhkJLkoDhOYbDJA95R3iaFXrWHRleD+G2HSVZoHgKeyecB2e9ALCESWvnsB/jrilbYBIRnNetLg2t/WCX87AzXiEutElKXUFWQxobogXOIQ/tTRY7wKI8azRszPR0BO7LsHhcVGJ+6bkVz8WGcRs5tZpdk0ecLkChNEb9KiVcnmYHnwN79Gk7ONaZlUyQx8xZwPFWtvkXLevv4M93p06wUaZgoQ6PgXvE5ASd/E1pQSHzDQTSO9NwVICoQLcAv5TrryNjabb3Y/R1/ODsqIQo+apd9SHKijtuCwdtaCiWqhJmkcSB2uY3NrYZD+O1Ah7X7DqMSINiJZKC2M3VVXTSv3OzM2agjpy3U6FHRvxTKsbQcJqJNsCaZ3CLdehWKzQD2RuS9CmoPQ+Q+s+JbQHEBuIruXlguo+zeYQJMn2sAsRC9vbghKdaIYvBt1lW0Bx6htgXy8nGB3qTMDIRBWG50l/J4XaWNgfBAKLqSNgcIQX7aFpvo2muqHOd5t6HtBl9TJ2IXH1KJu6gXt584rK1QChfDjVECSEUnmldmUgA1+7Aru5GBBxi487vtHlE/h9zt40VGkJddb8cYcBypzd+L3fw+9VImADQM2LSVNTx8C1+qrLWJXV66jXeASMf1uk64C2jgf/QILMimbyjL2WWYVhDzv4h5N2Sju7KYmr8hW6NelumnCRsePUCWi56eBJu4mi+R07XcT0lrDda5jQbZV7HZMcJTL7xR51ovdjgci+lCaT76UrkGw7h2VaHS6YT3ZQ4BOHa/0qOwLpc2PkHU3fSSYsbdQIUdork5Z1Vuf79TQomeTq12+zCMO7pN7UvmRMaFAvA3fBnjWdVDyG7PJrFa6L94WEA7abMHaSAAdCJLzSVvCrr6BNWbE2ts6m68XOQLCj2VEc+ma3CVHQ6Qvu3tV/tD6jIvh07+GPs2K465tCufjwF2ilRr/i5rFvlgiW0wSukwU75gxgOtC7s3CF02I/HHUW8gsOYsv+uwSmRouGtBuwFiShX0HWI+bNqSlfLaeyJArPnS9u7xg5Rg31bUSNy0Jx/YadJtRhi1/Nj5KzaplXexV2rfD884Q66Bvvnr00h6X7lY9A+RoB53jLLqyDMpxB9smcjTke14tS5aqZbvCOU8XvXWdljuwWwbr83/7RLY0WdZVExGDsslNFj1uUUljeM/jMI9bhOhoAw02CaMK6i1+R9xHEIDMuMARUQ2Sl7ASaPGD2bZ1mIZQsZu2zaOTIpbdhifxYy26waBD8G7cPVfW0LY5bZ4nxtLGeihjXx3NetPtgbSrQdczgy68EKWKX3/26RVXg05/AnPhE5a6GsRTRyfd+nMXH4r1Pf3sRXXUlU2M5xGI/ztWz3J/fm0ofOe7T8d2hBFg/3HHF6q4JRct5P2JSypeQKPb9hOLNLBq3hQkUkxwN5uks65O+LFu7BT+pWAxG0y73nfyD5+r6jJY2jj/g16c8n/6XzrC7t75QqrNkDKtBX+6VkD88yeg9oiBHe72muikw7Xpopou6ggneNliTNazQH6o3hMoaBjDeupZeX69Ul7A66B+FjO5TrsXm6Ne92JL1ONebJKyB6umGaTSkbx+SO53pIULIHydegeoTv11MG+H9dITiduT7911tuj3Ua2aWjuETb0+WaZeuobydGh5cG3/IRvHWpK5cnn/rEtIu0/+Xt1pdUk72FqUQ3dXInNQqhy8r8CA14uRP8zJ51Xmj1XPHiDY9D9dUsk1ylUvAwab03ZOSrPSd06KskbvnHizUjsnp+LP0FoMS3Ahr87FJUHZ6fSj65nvwZK2w9yLXMZvjkZ430nBr6nlnm6pWo7ZjdGZzO+ErwNcHI3A1IkbUfkXZQoepZTbWKsIiz7HbNFr0EggG40E3q8cUvs2m2Ghb3U6kguvUWtUDW4QJI9cVkAiuvtUS3pU3dQhFfQobKk+o/xBr73Q2ooWeu6dThtJK0E8pfcNkCqWz89lfayGq0TIAUXMhiIM/DDGzhSxRVqskXdgrF/ElmixJv4LRCLRh0IQMQ8istDiFpqMUzySTaa6EBHiH75yMdnEbCDJWXHyXKSUY2Lc6uVLOi6q2jOOqLu01Fn8l7+6iDabRWjt9URXLz478fkh8UwXKGrFs6PPl0OcrzLA56PNEZJHa2oOnyMSVWKGb8OzVluqorvSKspKq+hC50hFf4bnFKnx6BzxHzuF+XElP+JKfQgzq5BgYFjlzsIAvTsKqRL5oAdbniHjkCy+8tNLqNx60SosdwXQC81pH0y6R4DSZ8t7LVhwCUh+D9qF/fBSHhmpBE2CS9xPno9O1YYZdR3YfZjPm3mJup/8UmP4fZ0j3b8FG3MjunAMmwTqUglfuKtXpRBZTnPz0CUVN/XoMDrNYlirOk8bUdEbM0YcHv3hRt9NTXqUV6dljmHhGvGgOKpLFmANv7b36RjUWaZOfAlmDO9xgZ7fE4LW+fkHJ2ivQOJh5aIa1PpiCRti1OhGNLqmBeAXP76oprHWZ6/5QnXt93QjGN0Ra+tzoIwoMVNt2ngey2+6PUXHcbSBMdsZC+9H/rvhPb1uhKCgGRzwXUomtaqllPAAJnz0PX1y+IwD0vqRtAeBjLjbU0vuY7CR3AvJIlmYjXcd1+vU153CISGaGqQm5otizV4YEJR4GSgBDMtL00GNroIvXQni6O8h/1Xo+ar4iBLP/oFO7K18+COoM8lZnvIOpUZz8a7UCM7DLEBCiUh4y7qLqjZfaGzxz6EIEPz6OHpq0thYixByAtdZty9zoBCtzAPVWXLaPUdXjEu+9dKpQTLkL0BPoqDZwF985xlYQb5RIdZOsXbQhPM985z2HXiqMqlTPvu1F22cPO9GszFTItt4FKvZVQHMp5b/b4cBWW5eLQ1vfpvhYwRoc2iElFxXIQ/t7l4ZjVtffZJmzQTELsTjXGi5tfUJjJx6CFHlrl4a1IamNtbWqZBSPc4c6nGlDD4sFoH78SZxTyFyH4nZR4WYrR53l0kW9bhayu+FSbwgYYJcDki+0YQ2UIeS48X2Lnzk67VtaMk5TX0vYsZfOot5Dy1lAiCqiMERSDr2hfAUbfJ6xb4zXYCY+DIUw2BFQ5DE1VenwzeQB0e1p7v5+oxlDHUqY5e7kr5qJZ3CQUWv2FBqsiof0Nh+ibxRWFuP6HRpc6kuwJtngKhFJkGsB4ZaAIaajX+8rRe9HXaaEVIrbUbVDZ2+7jSO2uhbverXe6xtb4pZMhsIgDaaQPGAuBKyVJ3YYcabelGrqFwefsra1iK2QmcLi0J2coHnI+kpsT0uOQNB0PRGF0AeWSvyg2h2r4mSZMlfOVTpnKeDdVe6K4QzlP/qr6CTEV2lEqSSXowfljaM2nZ/paqJbyEaAKZMWPAvHu4jV0yyv3wo3kH7IUDDXwMNE2O05/HkjAZn/Ylj3zzrbY9ps56v1OuSE33Gm39jok9vHTXRs2OUixY+y5u0SnjxWSeeS/D5/I5e3JHFDKrWEH5AfFsSoTI2ZFHMAk197VLS1FMY0Z9VrInxSas0Gx+Q6ASm15YSdIOkNF0On8E1rtmpNBcpzSVKcymXP9aUhH742nhl+AjIgmGTzgTqyM7pwgujogmQ7CCIk/lJcZJ4CUQUyHOmqMpiu9JcqDSblWaL0mxSFtuU5mlKcxnbx2Or0tAL/oCYIk81aw0kVTub4FpEBV68XDoB/avgnNIqkh+06di4NHMjVpUvcxvf0wFK53UjpZv5vixy3pXTrTsJnyETTQOVF7RtyK7lXZAsU3uBF5Ep8SpTRBfozi6j6aU5ULoCwgbtkuJVZpDZRUreO+0rlc104gnvzDI8FJ7ZqFQVMgjSfV9obPKhMHkDWKkqUqqc7L5SpWrKEmVOSXdVqfB5MqpNeIwl5SaLMsvN+RTMTwYLMdhQSIgGZq2dHR1qJlpOvw3k8fDelldrwp3wip3iF5/E/Y9uY4kOBA+ZxGaZrERk1A265Q2ahVz8LbJjy1FmmpSZZmWmRZHJgE0+SX9pg0Ymm0QZrVKX2h+Kdct4oVtnhIKTdxRB9YxH8R6da395u8Lw+rjCLPS3leznZLq4RSdtO45+T6d78+x0DJPvdxl3txd3y3iqdJTykBHRT/dSrZtxOaInHNfkH2xP0uICBlusCWbD2Ma0wRZfT+azdZEhNb6ewDsel1JmaPtioBsfaMwwQ0MflLVj0AmV9B3UEdHWMRfI1zIH3cKYIkvrlCr00AnkrHKeL18S8452a6T5LWHLSdElILdlIXXq0ZU/jrHp5PROF55qEk6cToSzgAFChC8ZEV+D9AxAVFUyCj10AXOg7UtlzTNisOYwdJ5nCFenUhHGzyFyfrlk1LDiR1cQBpKyhj7GGvwYI16mwtgNSNRyENVsqPn3mY57r5Ytout4Hs/6X8YDoi94ycHPyWXil31DGsIiefxDzTKiDybqQP2IGoOJv+Km9QL+9QFKHd+1gU4yqu4dUt1bcVRGvxUMBsOvhBDRAzU91JOLydAUB0ExGZwVk+1eQKW9obDflNZU8oV4KutTlf/1qYyPGiF8xVzdaF8lcr+9Nu4bpv3nkAvtz1mVpDQNdPvOTzj+dEypHgYWSopFwWlQj4+5O9BY1vr8O/EZetzBzBqLW89slmPo3cEuPd6YCEi28D3pbUpcF56VHk7fz3Q3XZbyQhH0KMzfuPZyupvtiK1jKwJ5x54k+AhWinu/c4eSqHusyY5XlpQcNkfUjTYs4/HGkjROnVuJQBpfPkmX3NW5XiUn8ZlAkWPVnJWb8W7yDFMSLXjyyUtqx1ro7Z5ETzIV4k4q5SZWfQ5IAnw4ixsxVQ2mGhlVYm4BbX9o5g0wwWjsuNM7m+mlS+530JWnCnttKL7CqUQvx5u4dpcZSe0TiIQBJznwwH2zGK6iTcPCaFmpsHt8lhWPspxgLZpsoYgFwlyDWbM3NMOj4tNCCPaO7QHSJqU5fGxI2Q+IMkgeg3KpAsnihTqYz+KusC/fgvCene577RHVurGTHYaSWTae3jbRleYoNXwJpTej0ZF5lPfgJjPLgTVGHO6LXnvIcq7BFkQHdn+iw5yo8cYKG+25ZBLKP3IBSBhUsenUxx9CD9gp9URkGXW2A6Z9dQf71tCpmqGTgbhvL/mL90JfG0zqCXk4SyplVYh8MhlocX9APRGI3E+vApE6pIX4xTCd0LciZarM8iM7dfIjnTrGyEbad5RVmRTfISYTJ/btZTKtEtU9xQw5cDy6M950Ttxw3yksOxRfp0hdLHeIpJgNyQZJ3xdJz+PVCt9w3HcI/YLSsFmRds2I7kZteeDKu1HTrrjMlaIOdpudUnw9//99F71lUWjwIdEraCYM0B6t3cKFJ46s3djkELSZumKHrqjHsTNq1IGxwqmneL8XtJmmHoaX4ffGo++Lm/7Yvx33Y//smaCRQVYHXKlCRVfznbEVYmw2PcaepWsXppaIGhA+9Y5+hcClkTHsCAxOcuzm9pkbrVBEcrO9Xqkr8Pwc80edIiVnIlmTHQG5nsUJrG7HBPz1+iFVG4m89LiGpUYH3XiXhn2RObM10/CkR06SEnb9N7D46gf3RgCAQ0ulfQ98U+W5f9KkbaCBBEihQJGgUatFrQa0
*/
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
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
*/
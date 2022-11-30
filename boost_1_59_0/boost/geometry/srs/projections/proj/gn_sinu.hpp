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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GN_SINU_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GN_SINU_HPP

#include <boost/geometry/srs/projections/impl/aasincos.hpp>
#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_mlfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace gn_sinu
    {

            static const double epsilon10 = 1e-10;
            static const int max_iter = 8;
            static const double loop_tol = 1e-7;

            template <typename T>
            struct par_gn_sinu_e
            {
                detail::en<T> en;
            };

            template <typename T>
            struct par_gn_sinu_s
            {
                T m, n, C_x, C_y;
            };

            /* Ellipsoidal Sinusoidal only */

            template <typename T, typename Parameters>
            struct base_gn_sinu_ellipsoid
            {
                par_gn_sinu_e<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T s, c;

                    xy_y = pj_mlfn(lp_lat, s = sin(lp_lat), c = cos(lp_lat), this->m_proj_parm.en);
                    xy_x = lp_lon * c / sqrt(1. - par.es * s * s);
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T s;

                    if ((s = fabs(lp_lat = pj_inv_mlfn(xy_y, par.es, this->m_proj_parm.en))) < half_pi) {
                        s = sin(lp_lat);
                        lp_lon = xy_x * sqrt(1. - par.es * s * s) / cos(lp_lat);
                    } else if ((s - epsilon10) < half_pi)
                        lp_lon = 0.;
                    else
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                }
                /* General spherical sinusoidals */

                static inline std::string get_name()
                {
                    return "gn_sinu_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_gn_sinu_spheroid
            {
                par_gn_sinu_s<T> m_proj_parm;

                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    if (this->m_proj_parm.m == 0.0)
                        lp_lat = this->m_proj_parm.n != 1. ? aasin(this->m_proj_parm.n * sin(lp_lat)): lp_lat;
                    else {
                        T k, V;
                        int i;

                        k = this->m_proj_parm.n * sin(lp_lat);
                        for (i = max_iter; i ; --i) {
                            lp_lat -= V = (this->m_proj_parm.m * lp_lat + sin(lp_lat) - k) /
                                (this->m_proj_parm.m + cos(lp_lat));
                            if (fabs(V) < loop_tol)
                                break;
                        }
                        if (!i) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                    }
                    xy_x = this->m_proj_parm.C_x * lp_lon * (this->m_proj_parm.m + cos(lp_lat));
                    xy_y = this->m_proj_parm.C_y * lp_lat;
                }

                // INVERSE(s_inverse)  sphere
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    xy_y /= this->m_proj_parm.C_y;
                    lp_lat = (this->m_proj_parm.m != 0.0) ? aasin((this->m_proj_parm.m * xy_y + sin(xy_y)) / this->m_proj_parm.n) :
                        ( this->m_proj_parm.n != 1. ? aasin(sin(xy_y) / this->m_proj_parm.n) : xy_y );
                    lp_lon = xy_x / (this->m_proj_parm.C_x * (this->m_proj_parm.m + cos(xy_y)));
                }

                static inline std::string get_name()
                {
                    return "gn_sinu_spheroid";
                }

            };

            template <typename Parameters, typename T>
            inline void setup(Parameters& par, par_gn_sinu_s<T>& proj_parm) 
            {
                par.es = 0;

                proj_parm.C_x = (proj_parm.C_y = sqrt((proj_parm.m + 1.) / proj_parm.n))/(proj_parm.m + 1.);
            }


            // General Sinusoidal Series
            template <typename Params, typename Parameters, typename T>
            inline void setup_gn_sinu(Params const& params, Parameters& par, par_gn_sinu_s<T>& proj_parm)
            {
                if (pj_param_f<srs::spar::n>(params, "n", srs::dpar::n, proj_parm.n)
                 && pj_param_f<srs::spar::m>(params, "m", srs::dpar::m, proj_parm.m)) {
                    if (proj_parm.n <= 0 || proj_parm.m < 0)
                        BOOST_THROW_EXCEPTION( projection_exception(error_invalid_m_or_n) );
                } else
                    BOOST_THROW_EXCEPTION( projection_exception(error_invalid_m_or_n) );

                setup(par, proj_parm);
            }

            // Sinusoidal (Sanson-Flamsteed)
            template <typename Parameters, typename T>
            inline void setup_sinu(Parameters const& par, par_gn_sinu_e<T>& proj_parm)
            {
                proj_parm.en = pj_enfn<T>(par.es);
            }

            // Sinusoidal (Sanson-Flamsteed)
            template <typename Parameters, typename T>
            inline void setup_sinu(Parameters& par, par_gn_sinu_s<T>& proj_parm)
            {
                proj_parm.n = 1.;
                proj_parm.m = 0.;
                setup(par, proj_parm);
            }

            // Eckert VI
            template <typename Parameters, typename T>
            inline void setup_eck6(Parameters& par, par_gn_sinu_s<T>& proj_parm)
            {
                proj_parm.m = 1.;
                proj_parm.n = 2.570796326794896619231321691;
                setup(par, proj_parm);
            }

            // McBryde-Thomas Flat-Polar Sinusoidal
            template <typename Parameters, typename T>
            inline void setup_mbtfps(Parameters& par, par_gn_sinu_s<T>& proj_parm)
            {
                proj_parm.m = 0.5;
                proj_parm.n = 1.785398163397448309615660845;
                setup(par, proj_parm);
            }

    }} // namespace detail::gn_sinu
    #endif // doxygen

    /*!
        \brief General Sinusoidal Series projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Projection parameters
         - m (real)
         - n (real)
        \par Example
        \image html ex_gn_sinu.gif
    */
    template <typename T, typename Parameters>
    struct gn_sinu_spheroid : public detail::gn_sinu::base_gn_sinu_spheroid<T, Parameters>
    {
        template <typename Params>
        inline gn_sinu_spheroid(Params const& params, Parameters & par)
        {
            detail::gn_sinu::setup_gn_sinu(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Sinusoidal (Sanson-Flamsteed) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_sinu.gif
    */
    template <typename T, typename Parameters>
    struct sinu_ellipsoid : public detail::gn_sinu::base_gn_sinu_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline sinu_ellipsoid(Params const& , Parameters & par)
        {
            detail::gn_sinu::setup_sinu(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Sinusoidal (Sanson-Flamsteed) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_sinu.gif
    */
    template <typename T, typename Parameters>
    struct sinu_spheroid : public detail::gn_sinu::base_gn_sinu_spheroid<T, Parameters>
    {
        template <typename Params>
        inline sinu_spheroid(Params const& , Parameters & par)
        {
            detail::gn_sinu::setup_sinu(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Eckert VI projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck6.gif
    */
    template <typename T, typename Parameters>
    struct eck6_spheroid : public detail::gn_sinu::base_gn_sinu_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck6_spheroid(Params const& , Parameters & par)
        {
            detail::gn_sinu::setup_eck6(par, this->m_proj_parm);
        }
    };

    /*!
        \brief McBryde-Thomas Flat-Polar Sinusoidal projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_mbtfps.gif
    */
    template <typename T, typename Parameters>
    struct mbtfps_spheroid : public detail::gn_sinu::base_gn_sinu_spheroid<T, Parameters>
    {
        template <typename Params>
        inline mbtfps_spheroid(Params const& , Parameters & par)
        {
            detail::gn_sinu::setup_mbtfps(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_gn_sinu, gn_sinu_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_sinu, sinu_spheroid, sinu_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck6, eck6_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mbtfps, mbtfps_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(gn_sinu_entry, gn_sinu_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(sinu_entry, sinu_spheroid, sinu_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck6_entry, eck6_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mbtfps_entry, mbtfps_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(gn_sinu_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(gn_sinu, gn_sinu_entry);
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(sinu, sinu_entry);
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck6, eck6_entry);
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mbtfps, mbtfps_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GN_SINU_HPP


/* gn_sinu.hpp
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
*/
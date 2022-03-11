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
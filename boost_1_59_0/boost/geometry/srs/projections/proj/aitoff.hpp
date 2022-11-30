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

// Purpose:  Implementation of the aitoff (Aitoff) and wintri (Winkel Tripel)
//           projections.
// Author:   Gerald Evenden (1995)
//           Drazen Tutic, Lovro Gradiser (2015) - add inverse
//           Thomas Knudsen (2016) - revise/add regression tests
// Copyright (c) 1995, Gerald Evenden

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_AITOFF_HPP
#define BOOST_GEOMETRY_PROJECTIONS_AITOFF_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace aitoff
    {
            enum mode_type {
                mode_aitoff = 0,
                mode_winkel_tripel = 1
            };

            template <typename T>
            struct par_aitoff
            {
                T    cosphi1;
                mode_type mode;
            };

            template <typename T, typename Parameters>
            struct base_aitoff_spheroid
            {
                par_aitoff<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T c, d;

                    if((d = acos(cos(lp_lat) * cos(c = 0.5 * lp_lon)))) {/* basic Aitoff */
                        xy_x = 2. * d * cos(lp_lat) * sin(c) * (xy_y = 1. / sin(d));
                        xy_y *= d * sin(lp_lat);
                    } else
                        xy_x = xy_y = 0.;
                    if (this->m_proj_parm.mode == mode_winkel_tripel) { /* Winkel Tripel */
                        xy_x = (xy_x + lp_lon * this->m_proj_parm.cosphi1) * 0.5;
                        xy_y = (xy_y + lp_lat) * 0.5;
                    }
                }
                /***********************************************************************************
                *
                * Inverse functions added by Drazen Tutic and Lovro Gradiser based on paper:
                *
                * I.Özbug Biklirici and Cengizhan Ipbüker. A General Algorithm for the Inverse
                * Transformation of Map Projections Using Jacobian Matrices. In Proceedings of the
                * Third International Symposium Mathematical & Computational Applications,
                * pages 175{182, Turkey, September 2002.
                *
                * Expected accuracy is defined by epsilon = 1e-12. Should be appropriate for
                * most applications of Aitoff and Winkel Tripel projections.
                *
                * Longitudes of 180W and 180E can be mixed in solution obtained.
                *
                * Inverse for Aitoff projection in poles is undefined, longitude value of 0 is assumed.
                *
                * Contact : dtutic@geof.hr
                * Date: 2015-02-16
                *
                ************************************************************************************/

                // INVERSE(s_inverse)  sphere
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T pi = detail::pi<T>();
                    static const T two_pi = detail::two_pi<T>();
                    static const T epsilon = 1e-12;

                    int iter, max_iter = 10, round = 0, max_round = 20;
                    T D, C, f1, f2, f1p, f1l, f2p, f2l, dp, dl, sl, sp, cp, cl, x, y;

                    if ((fabs(xy_x) < epsilon) && (fabs(xy_y) < epsilon )) {
                        lp_lat = 0.; lp_lon = 0.;
                        return;
                    }

                    /* intial values for Newton-Raphson method */
                    lp_lat = xy_y; lp_lon = xy_x;
                    do {
                        iter = 0;
                        do {
                            sl = sin(lp_lon * 0.5); cl = cos(lp_lon * 0.5);
                            sp = sin(lp_lat); cp = cos(lp_lat);
                            D = cp * cl;
                            C = 1. - D * D;
                            D = acos(D) / math::pow(C, T(1.5));
                            f1 = 2. * D * C * cp * sl;
                            f2 = D * C * sp;
                            f1p = 2.* (sl * cl * sp * cp / C - D * sp * sl);
                            f1l = cp * cp * sl * sl / C + D * cp * cl * sp * sp;
                            f2p = sp * sp * cl / C + D * sl * sl * cp;
                            f2l = 0.5 * (sp * cp * sl / C - D * sp * cp * cp * sl * cl);
                            if (this->m_proj_parm.mode == mode_winkel_tripel) { /* Winkel Tripel */
                                f1 = 0.5 * (f1 + lp_lon * this->m_proj_parm.cosphi1);
                                f2 = 0.5 * (f2 + lp_lat);
                                f1p *= 0.5;
                                f1l = 0.5 * (f1l + this->m_proj_parm.cosphi1);
                                f2p = 0.5 * (f2p + 1.);
                                f2l *= 0.5;
                            }
                            f1 -= xy_x; f2 -= xy_y;
                            dl = (f2 * f1p - f1 * f2p) / (dp = f1p * f2l - f2p * f1l);
                            dp = (f1 * f2l - f2 * f1l) / dp;
                            dl = fmod(dl, pi); /* set to interval [-M_PI, M_PI] */
                            lp_lat -= dp;    lp_lon -= dl;
                        } while ((fabs(dp) > epsilon || fabs(dl) > epsilon) && (iter++ < max_iter));
                        if (lp_lat > two_pi) lp_lat -= 2.*(lp_lat-two_pi); /* correct if symmetrical solution for Aitoff */
                        if (lp_lat < -two_pi) lp_lat -= 2.*(lp_lat+two_pi); /* correct if symmetrical solution for Aitoff */
                        if ((fabs(fabs(lp_lat) - two_pi) < epsilon) && (!this->m_proj_parm.mode)) lp_lon = 0.; /* if pole in Aitoff, return longitude of 0 */

                        /* calculate x,y coordinates with solution obtained */
                        if((D = acos(cos(lp_lat) * cos(C = 0.5 * lp_lon))) != 0.0) {/* Aitoff */
                            x = 2. * D * cos(lp_lat) * sin(C) * (y = 1. / sin(D));
                            y *= D * sin(lp_lat);
                        } else
                            x = y = 0.;
                        if (this->m_proj_parm.mode == mode_winkel_tripel) { /* Winkel Tripel */
                            x = (x + lp_lon * this->m_proj_parm.cosphi1) * 0.5;
                            y = (y + lp_lat) * 0.5;
                        }
                    /* if too far from given values of x,y, repeat with better approximation of phi,lam */
                    } while (((fabs(xy_x-x) > epsilon) || (fabs(xy_y-y) > epsilon)) && (round++ < max_round));

                    if (iter == max_iter && round == max_round)
                    {
                        BOOST_THROW_EXCEPTION( projection_exception(error_non_convergent) );
                        //fprintf(stderr, "Warning: Accuracy of 1e-12 not reached. Last increments: dlat=%e and dlon=%e\n", dp, dl);
                    }
                }

                static inline std::string get_name()
                {
                    return "aitoff_spheroid";
                }

            };

            template <typename Parameters>
            inline void setup(Parameters& par)
            {
                par.es = 0.;
            }


            // Aitoff
            template <typename Parameters, typename T>
            inline void setup_aitoff(Parameters& par, par_aitoff<T>& proj_parm)
            {
                proj_parm.mode = mode_aitoff;
                setup(par);
            }

            // Winkel Tripel
            template <typename Params, typename Parameters, typename T>
            inline void setup_wintri(Params& params, Parameters& par, par_aitoff<T>& proj_parm)
            {
                static const T two_div_pi = detail::two_div_pi<T>();

                T phi1;

                proj_parm.mode = mode_winkel_tripel;
                if (pj_param_r<srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1, phi1)) {
                    if ((proj_parm.cosphi1 = cos(phi1)) == 0.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_larger_than_90) );
                } else /* 50d28' or phi1=acos(2/pi) */
                    proj_parm.cosphi1 = two_div_pi;
                setup(par);
            }

    }} // namespace detail::aitoff
    #endif // doxygen

    /*!
        \brief Aitoff projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
        \par Example
        \image html ex_aitoff.gif
    */
    template <typename T, typename Parameters>
    struct aitoff_spheroid : public detail::aitoff::base_aitoff_spheroid<T, Parameters>
    {
        template <typename Params>
        inline aitoff_spheroid(Params const& , Parameters & par)
        {
            detail::aitoff::setup_aitoff(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Winkel Tripel projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
        \par Example
        \image html ex_wintri.gif
    */
    template <typename T, typename Parameters>
    struct wintri_spheroid : public detail::aitoff::base_aitoff_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wintri_spheroid(Params const& params, Parameters & par)
        {
            detail::aitoff::setup_wintri(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_aitoff, aitoff_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wintri, wintri_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(aitoff_entry, aitoff_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wintri_entry, wintri_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(aitoff_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(aitoff, aitoff_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wintri, wintri_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_AITOFF_HPP


/* aitoff.hpp
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
*/
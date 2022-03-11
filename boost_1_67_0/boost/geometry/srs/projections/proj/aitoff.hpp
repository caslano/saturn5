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
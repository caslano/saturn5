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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMW_P_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMW_P_HPP

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
    namespace detail { namespace imw_p
    {

            static const double tolerance = 1e-10;
            static const double epsilon = 1e-10;

            template <typename T>
            struct point_xy { T x, y; }; // specific for IMW_P

            enum mode_type {
                none_is_zero  =  0, /* phi_1 and phi_2 != 0 */
                phi_1_is_zero =  1, /* phi_1 = 0 */
                phi_2_is_zero = -1  /* phi_2 = 0 */
            };

            template <typename T>
            struct par_imw_p
            {
                T    P, Pp, Q, Qp, R_1, R_2, sphi_1, sphi_2, C2;
                T    phi_1, phi_2, lam_1;
                detail::en<T> en;
                mode_type mode;
            };

            template <typename Params, typename T>
            inline int phi12(Params const& params,
                             par_imw_p<T> & proj_parm, T *del, T *sig)
            {
                int err = 0;

                if (!pj_param_r<srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1, proj_parm.phi_1) ||
                    !pj_param_r<srs::spar::lat_2>(params, "lat_2", srs::dpar::lat_2, proj_parm.phi_2)) {
                    err = -41;
                } else {
                    //proj_parm.phi_1 = pj_get_param_r(par.params, "lat_1"); // set above
                    //proj_parm.phi_2 = pj_get_param_r(par.params, "lat_2"); // set above
                    *del = 0.5 * (proj_parm.phi_2 - proj_parm.phi_1);
                    *sig = 0.5 * (proj_parm.phi_2 + proj_parm.phi_1);
                    err = (fabs(*del) < epsilon || fabs(*sig) < epsilon) ? -42 : 0;
                }
                return err;
            }
            template <typename Parameters, typename T>
            inline point_xy<T> loc_for(T const& lp_lam, T const& lp_phi,
                                       Parameters const& par,
                                       par_imw_p<T> const& proj_parm,
                                       T *yc)
            {
                point_xy<T> xy;

                if (lp_phi == 0.0) {
                    xy.x = lp_lam;
                    xy.y = 0.;
                } else {
                    T xa, ya, xb, yb, xc, D, B, m, sp, t, R, C;

                    sp = sin(lp_phi);
                    m = pj_mlfn(lp_phi, sp, cos(lp_phi), proj_parm.en);
                    xa = proj_parm.Pp + proj_parm.Qp * m;
                    ya = proj_parm.P + proj_parm.Q * m;
                    R = 1. / (tan(lp_phi) * sqrt(1. - par.es * sp * sp));
                    C = sqrt(R * R - xa * xa);
                    if (lp_phi < 0.) C = - C;
                    C += ya - R;
                    if (proj_parm.mode == phi_2_is_zero) {
                        xb = lp_lam;
                        yb = proj_parm.C2;
                    } else {
                        t = lp_lam * proj_parm.sphi_2;
                        xb = proj_parm.R_2 * sin(t);
                        yb = proj_parm.C2 + proj_parm.R_2 * (1. - cos(t));
                    }
                    if (proj_parm.mode == phi_1_is_zero) {
                        xc = lp_lam;
                        *yc = 0.;
                    } else {
                        t = lp_lam * proj_parm.sphi_1;
                        xc = proj_parm.R_1 * sin(t);
                        *yc = proj_parm.R_1 * (1. - cos(t));
                    }
                    D = (xb - xc)/(yb - *yc);
                    B = xc + D * (C + R - *yc);
                    xy.x = D * sqrt(R * R * (1 + D * D) - B * B);
                    if (lp_phi > 0)
                        xy.x = - xy.x;
                    xy.x = (B + xy.x) / (1. + D * D);
                    xy.y = sqrt(R * R - xy.x * xy.x);
                    if (lp_phi > 0)
                        xy.y = - xy.y;
                    xy.y += C + R;
                }
                return (xy);
            }
            template <typename Parameters, typename T>
            inline void xy(Parameters const& par, par_imw_p<T> const& proj_parm,
                           T const& phi,
                           T *x, T *y, T *sp, T *R)
            {
                T F;

                *sp = sin(phi);
                *R = 1./(tan(phi) * sqrt(1. - par.es * *sp * *sp ));
                F = proj_parm.lam_1 * *sp;
                *y = *R * (1 - cos(F));
                *x = *R * sin(F);
            }

            template <typename T, typename Parameters>
            struct base_imw_p_ellipsoid
            {
                par_imw_p<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T yc = 0;
                    point_xy<T> xy = loc_for(lp_lon, lp_lat, par, m_proj_parm, &yc);
                    xy_x = xy.x; xy_y = xy.y;
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    point_xy<T> t;
                    T yc = 0.0;
                    int i = 0;
                    const int n_max_iter = 1000; /* Arbitrarily choosen number... */

                    lp_lat = this->m_proj_parm.phi_2;
                    lp_lon = xy_x / cos(lp_lat);
                    do {
                        t = loc_for(lp_lon, lp_lat, par, m_proj_parm, &yc);
                        lp_lat = ((lp_lat - this->m_proj_parm.phi_1) * (xy_y - yc) / (t.y - yc)) + this->m_proj_parm.phi_1;
                        lp_lon = lp_lon * xy_x / t.x;
                        i++;
                    } while (i < n_max_iter &&
                             (fabs(t.x - xy_x) > tolerance || fabs(t.y - xy_y) > tolerance));

                    if( i == n_max_iter )
                    {
                        lp_lon = lp_lat = HUGE_VAL;
                    }
                }

                static inline std::string get_name()
                {
                    return "imw_p_ellipsoid";
                }

            };

            // International Map of the World Polyconic
            template <typename Params, typename Parameters, typename T>
            inline void setup_imw_p(Params const& params, Parameters const& par, par_imw_p<T>& proj_parm)
            {
                T del, sig, s, t, x1, x2, T2, y1, m1, m2, y2;
                int err;

                proj_parm.en = pj_enfn<T>(par.es);
                if( (err = phi12(params, proj_parm, &del, &sig)) != 0)
                    BOOST_THROW_EXCEPTION( projection_exception(err) );
                if (proj_parm.phi_2 < proj_parm.phi_1) { /* make sure proj_parm.phi_1 most southerly */
                    del = proj_parm.phi_1;
                    proj_parm.phi_1 = proj_parm.phi_2;
                    proj_parm.phi_2 = del;
                }
                if (pj_param_r<srs::spar::lon_1>(params, "lon_1", srs::dpar::lon_1, proj_parm.lam_1)) {
                    /* empty */
                } else { /* use predefined based upon latitude */
                    sig = fabs(sig * geometry::math::r2d<T>());
                    if (sig <= 60)      sig = 2.;
                    else if (sig <= 76) sig = 4.;
                    else                sig = 8.;
                    proj_parm.lam_1 = sig * geometry::math::d2r<T>();
                }
                proj_parm.mode = none_is_zero;
                if (proj_parm.phi_1 != 0.0)
                    xy(par, proj_parm, proj_parm.phi_1, &x1, &y1, &proj_parm.sphi_1, &proj_parm.R_1);
                else {
                    proj_parm.mode = phi_1_is_zero;
                    y1 = 0.;
                    x1 = proj_parm.lam_1;
                }
                if (proj_parm.phi_2 != 0.0)
                    xy(par, proj_parm, proj_parm.phi_2, &x2, &T2, &proj_parm.sphi_2, &proj_parm.R_2);
                else {
                    proj_parm.mode = phi_2_is_zero;
                    T2 = 0.;
                    x2 = proj_parm.lam_1;
                }
                m1 = pj_mlfn(proj_parm.phi_1, proj_parm.sphi_1, cos(proj_parm.phi_1), proj_parm.en);
                m2 = pj_mlfn(proj_parm.phi_2, proj_parm.sphi_2, cos(proj_parm.phi_2), proj_parm.en);
                t = m2 - m1;
                s = x2 - x1;
                y2 = sqrt(t * t - s * s) + y1;
                proj_parm.C2 = y2 - T2;
                t = 1. / t;
                proj_parm.P = (m2 * y1 - m1 * y2) * t;
                proj_parm.Q = (y2 - y1) * t;
                proj_parm.Pp = (m2 * x1 - m1 * x2) * t;
                proj_parm.Qp = (x2 - x1) * t;
            }

    }} // namespace detail::imw_p
    #endif // doxygen

    /*!
        \brief International Map of the World Polyconic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Mod. Polyconic
         - Ellipsoid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel
         - lat_2: Latitude of second standard parallel
         - lon_1 (degrees)
        \par Example
        \image html ex_imw_p.gif
    */
    template <typename T, typename Parameters>
    struct imw_p_ellipsoid : public detail::imw_p::base_imw_p_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline imw_p_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::imw_p::setup_imw_p(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_imw_p, imw_p_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(imw_p_entry, imw_p_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(imw_p_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(imw_p, imw_p_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_IMW_P_HPP


/* imw_p.hpp
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
*/
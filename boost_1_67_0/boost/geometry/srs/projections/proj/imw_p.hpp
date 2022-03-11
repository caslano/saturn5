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
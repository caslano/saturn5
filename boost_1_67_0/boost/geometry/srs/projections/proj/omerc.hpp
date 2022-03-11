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

// Copyright (c) 2003, 2006   Gerald I. Evenden

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_OMERC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_OMERC_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/pj_phi2.hpp>
#include <boost/geometry/srs/projections/impl/pj_tsfn.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace omerc
    {
            template <typename T>
            struct par_omerc
            {
                T    A, B, E, AB, ArB, BrA, rB, singam, cosgam, sinrot, cosrot;
                T    v_pole_n, v_pole_s, u_0;
                bool no_rot;
            };

            static const double tolerance = 1.e-7;
            static const double epsilon = 1.e-10;

            template <typename T, typename Parameters>
            struct base_omerc_ellipsoid
            {
                par_omerc<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T  s, t, U, V, W, temp, u, v;

                    if (fabs(fabs(lp_lat) - half_pi) > epsilon) {
                        W = this->m_proj_parm.E / math::pow(pj_tsfn(lp_lat, sin(lp_lat), par.e), this->m_proj_parm.B);
                        temp = 1. / W;
                        s = .5 * (W - temp);
                        t = .5 * (W + temp);
                        V = sin(this->m_proj_parm.B * lp_lon);
                        U = (s * this->m_proj_parm.singam - V * this->m_proj_parm.cosgam) / t;
                        if (fabs(fabs(U) - 1.0) < epsilon) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        v = 0.5 * this->m_proj_parm.ArB * log((1. - U)/(1. + U));
                        temp = cos(this->m_proj_parm.B * lp_lon);
                        if(fabs(temp) < tolerance) {
                            u = this->m_proj_parm.A * lp_lon;
                        } else {
                            u = this->m_proj_parm.ArB * atan2((s * this->m_proj_parm.cosgam + V * this->m_proj_parm.singam), temp);
                        }
                    } else {
                        v = lp_lat > 0 ? this->m_proj_parm.v_pole_n : this->m_proj_parm.v_pole_s;
                        u = this->m_proj_parm.ArB * lp_lat;
                    }
                    if (this->m_proj_parm.no_rot) {
                        xy_x = u;
                        xy_y = v;
                    } else {
                        u -= this->m_proj_parm.u_0;
                        xy_x = v * this->m_proj_parm.cosrot + u * this->m_proj_parm.sinrot;
                        xy_y = u * this->m_proj_parm.cosrot - v * this->m_proj_parm.sinrot;
                    }
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T  u, v, Qp, Sp, Tp, Vp, Up;

                    if (this->m_proj_parm.no_rot) {
                        v = xy_y;
                        u = xy_x;
                    } else {
                        v = xy_x * this->m_proj_parm.cosrot - xy_y * this->m_proj_parm.sinrot;
                        u = xy_y * this->m_proj_parm.cosrot + xy_x * this->m_proj_parm.sinrot + this->m_proj_parm.u_0;
                    }
                    Qp = exp(- this->m_proj_parm.BrA * v);
                    Sp = .5 * (Qp - 1. / Qp);
                    Tp = .5 * (Qp + 1. / Qp);
                    Vp = sin(this->m_proj_parm.BrA * u);
                    Up = (Vp * this->m_proj_parm.cosgam + Sp * this->m_proj_parm.singam) / Tp;
                    if (fabs(fabs(Up) - 1.) < epsilon) {
                        lp_lon = 0.;
                        lp_lat = Up < 0. ? -half_pi : half_pi;
                    } else {
                        lp_lat = this->m_proj_parm.E / sqrt((1. + Up) / (1. - Up));
                        if ((lp_lat = pj_phi2(math::pow(lp_lat, T(1) / this->m_proj_parm.B), par.e)) == HUGE_VAL) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        lp_lon = - this->m_proj_parm.rB * atan2((Sp * this->m_proj_parm.cosgam -
                            Vp * this->m_proj_parm.singam), cos(this->m_proj_parm.BrA * u));
                    }
                }

                static inline std::string get_name()
                {
                    return "omerc_ellipsoid";
                }

            };

            // Oblique Mercator
            template <typename Params, typename Parameters, typename T>
            inline void setup_omerc(Params const& params, Parameters & par, par_omerc<T>& proj_parm)
            {
                static const T fourth_pi = detail::fourth_pi<T>();
                static const T half_pi = detail::half_pi<T>();
                static const T pi = detail::pi<T>();
                static const T two_pi = detail::two_pi<T>();

                T con, com, cosph0, D, F, H, L, sinph0, p, J, gamma=0,
                  gamma0, lamc=0, lam1=0, lam2=0, phi1=0, phi2=0, alpha_c=0;
                int alp, gam, no_off = 0;

                proj_parm.no_rot = pj_get_param_b<srs::spar::no_rot>(params, "no_rot", srs::dpar::no_rot);
                alp = pj_param_r<srs::spar::alpha>(params, "alpha", srs::dpar::alpha, alpha_c);
                gam = pj_param_r<srs::spar::gamma>(params, "gamma", srs::dpar::gamma, gamma);
                if (alp || gam) {
                    lamc = pj_get_param_r<T, srs::spar::lonc>(params, "lonc", srs::dpar::lonc);
                    // NOTE: This is not needed in Boost.Geometry
                    //no_off =
                    //            /* For libproj4 compatability */
                    //            pj_param_exists(par.params, "no_off")
                    //            /* for backward compatibility */
                    //            || pj_param_exists(par.params, "no_uoff");
                    //if( no_off )
                    //{
                    //    /* Mark the parameter as used, so that the pj_get_def() return them */
                    //    pj_get_param_s(par.params, "no_uoff");
                    //    pj_get_param_s(par.params, "no_off");
                    //}
                } else {
                    lam1 = pj_get_param_r<T, srs::spar::lon_1>(params, "lon_1", srs::dpar::lon_1);
                    phi1 = pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1);
                    lam2 = pj_get_param_r<T, srs::spar::lon_2>(params, "lon_2", srs::dpar::lon_2);
                    phi2 = pj_get_param_r<T, srs::spar::lat_2>(params, "lat_2", srs::dpar::lat_2);
                    if (fabs(phi1 - phi2) <= tolerance ||
                        (con = fabs(phi1)) <= tolerance ||
                        fabs(con - half_pi) <= tolerance ||
                        fabs(fabs(par.phi0) - half_pi) <= tolerance ||
                        fabs(fabs(phi2) - half_pi) <= tolerance)
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_0_or_alpha_eq_90) );
                }
                com = sqrt(par.one_es);
                if (fabs(par.phi0) > epsilon) {
                    sinph0 = sin(par.phi0);
                    cosph0 = cos(par.phi0);
                    con = 1. - par.es * sinph0 * sinph0;
                    proj_parm.B = cosph0 * cosph0;
                    proj_parm.B = sqrt(1. + par.es * proj_parm.B * proj_parm.B / par.one_es);
                    proj_parm.A = proj_parm.B * par.k0 * com / con;
                    D = proj_parm.B * com / (cosph0 * sqrt(con));
                    if ((F = D * D - 1.) <= 0.)
                        F = 0.;
                    else {
                        F = sqrt(F);
                        if (par.phi0 < 0.)
                            F = -F;
                    }
                    proj_parm.E = F += D;
                    proj_parm.E *= math::pow(pj_tsfn(par.phi0, sinph0, par.e), proj_parm.B);
                } else {
                    proj_parm.B = 1. / com;
                    proj_parm.A = par.k0;
                    proj_parm.E = D = F = 1.;
                }
                if (alp || gam) {
                    if (alp) {
                        gamma0 = aasin(sin(alpha_c) / D);
                        if (!gam)
                            gamma = alpha_c;
                    } else
                        alpha_c = aasin(D*sin(gamma0 = gamma));
                    par.lam0 = lamc - aasin(.5 * (F - 1. / F) *
                       tan(gamma0)) / proj_parm.B;
                } else {
                    H = math::pow(pj_tsfn(phi1, sin(phi1), par.e), proj_parm.B);
                    L = math::pow(pj_tsfn(phi2, sin(phi2), par.e), proj_parm.B);
                    F = proj_parm.E / H;
                    p = (L - H) / (L + H);
                    J = proj_parm.E * proj_parm.E;
                    J = (J - L * H) / (J + L * H);
                    if ((con = lam1 - lam2) < -pi)
                        lam2 -= two_pi;
                    else if (con > pi)
                        lam2 += two_pi;
                    par.lam0 = adjlon(.5 * (lam1 + lam2) - atan(
                       J * tan(.5 * proj_parm.B * (lam1 - lam2)) / p) / proj_parm.B);
                    gamma0 = atan(2. * sin(proj_parm.B * adjlon(lam1 - par.lam0)) /
                       (F - 1. / F));
                    gamma = alpha_c = aasin(D * sin(gamma0));
                }
                proj_parm.singam = sin(gamma0);
                proj_parm.cosgam = cos(gamma0);
                proj_parm.sinrot = sin(gamma);
                proj_parm.cosrot = cos(gamma);
                proj_parm.BrA = 1. / (proj_parm.ArB = proj_parm.A * (proj_parm.rB = 1. / proj_parm.B));
                proj_parm.AB = proj_parm.A * proj_parm.B;
                if (no_off)
                    proj_parm.u_0 = 0;
                else {
                    proj_parm.u_0 = fabs(proj_parm.ArB * atan(sqrt(D * D - 1.) / cos(alpha_c)));
                    if (par.phi0 < 0.)
                        proj_parm.u_0 = - proj_parm.u_0;
                }
                F = 0.5 * gamma0;
                proj_parm.v_pole_n = proj_parm.ArB * log(tan(fourth_pi - F));
                proj_parm.v_pole_s = proj_parm.ArB * log(tan(fourth_pi + F));
            }

    }} // namespace detail::omerc
    #endif // doxygen

    /*!
        \brief Oblique Mercator projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - no_rot: No rotation
         - alpha: Alpha (degrees)
         - gamma: Gamma (degrees)
         - no_off: Only for compatibility with libproj, proj4 (string)
         - lonc: Longitude (only used if alpha (or gamma) is specified) (degrees)
         - lon_1 (degrees)
         - lat_1: Latitude of first standard parallel (degrees)
         - lon_2 (degrees)
         - lat_2: Latitude of second standard parallel (degrees)
         - no_uoff (string)
        \par Example
        \image html ex_omerc.gif
    */
    template <typename T, typename Parameters>
    struct omerc_ellipsoid : public detail::omerc::base_omerc_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline omerc_ellipsoid(Params const& params, Parameters & par)
        {
            detail::omerc::setup_omerc(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_omerc, omerc_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(omerc_entry, omerc_ellipsoid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(omerc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(omerc, omerc_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_OMERC_HPP


/* omerc.hpp
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
*/
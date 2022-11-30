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
ObgDOmTPtECkoSM4ZDHgbmvfmt007mHEP6SOEdgWbjQl7Q47WanjcImhc2bF0e3jaRfFpcoE/ZiTxHQJ09J0r4Uyh1nuhgppTthxuuGoG9wzQ0E8lT1UQv+H1oQwYpp6oiOKzv5j3DtxMuQQRxZi6LxcO3b2ZjLqg2F7DZoeiSahfunWnxlh+faMcD2Ko+tXMN8pmtdMr/1lbZvD0ynl+RXDsAO8MAZe+w2jzq9O4ymWAx2LfwAUCEQEHFt6XUQ3DVp3csss5lXsBQ3S5LZLM3BaqbEQ+o4jr75EnQ3t4CKlLvGiud3YvrIxa3C2697hsTMWjhfR7zpq/Njsno8gQZdOtJHkRii4UqT/iE8M9d0NmwgLn3verYvYuzHOTmBVwafWo1sVLfYUSyczQ3kb6VMcEIoztvAedC+K4pEtLx6TZ5ifu8OmL7w7+iFxDpBpwrVDCtcyNQjL4ImjJCXqJRumlexjpkwBPLW0fbXTmSkiWuRHRII/nD1Gua8rh/4jIKEvfujmoMrJIP/TWb3c9lCxOckl869y0A/Ljr7NVRF1gIuAU6M+vn25Sj578GOFH5VtwbXD3XoS+w4Km7NC6YhDbE3xsdvdhGrUa5Ty/UKIeQjnoUsJaMbGScJ3N2czW1oovr3DtvssQbJNm2amt7tj7sOG2UDI6xV5pPf8rNl6VAykJHhcRNNOXG2ahX91OT4ZVo4H3WFH+eY96CfBLp3FucBM7nFBswdYhlwU7JbZ9h3Va+nFLamFmjwe0vhlPzie5F8zIq2YGkfsjaQ/q+TubN9/DbJks/eXzWnFVfQY0HnsAm5do5Ui6Zw4Tgra9JOcDKR2YBc8n/zw919cYfZqW1vmx9fG5IFbGhc080GhrKBv/mEsxOohwrh3ezSF0yOgw9U8Qx0YboecIKCQZGtEmXwIQ4k0oXJe8SL3valEOkIp+vaIrgvvvS1u1gAH6W6GrtBJpXHA2G7JDUDMu4/koVrwtDOvSo95kNRVMs4Tb5VBVdfPqIlr2eUcArGVyIhBYXgTG6xdjD7647gdlBDRkQq837nMlxuSvofFFSIZIEul5CP7HhxHQq/6iwFJJUhaUKU8YkYGSx5zuIRbbAZfmfuoPJne7emoQaBdZF5oEpBKvqpT6uJLV41wIcriN+eo0JH5W006lu0BKGe3GRmggVeIeyD5vFzJUuE6XCnV2WWnR3wVX3QNhQaFBrkR+AnhB9kF3YVECC0I4QfTBdeFBmogz6+yc7XRhWYYtlwzVyJUgazEmpwVFsPM0Zs/+qbmF9I2NF8bE7ZpOfRsM74sq05wX36r2R9dDDOe4KsjP5nRcVTVipe2TyyxrkrGWk10KmJR3irEt7qgRYe1MDzj4YdqUO/9ly3nUTPIRST26GuFYp4+O4h5cfgOrSguGSPSfXqJ2kxzqImVKtaq+L2vquDlveIvNnJeYOiO7GaPegvBhc3nMBcyc8/usqDRheMB409Apw/oFhXq+aKJJo5yCKLeORdjdQrh7KGtkvgTATQR+zNXkdgUsLyUzRIpttnHOMNnJaiyir9771J5UDxplTALXhzGk87SbSinyuc7KO+aPHoHZ5G4ggSu8QyUBf9engR/1LXF9iMsRJ2vfnmv/5kluQOX0GPA1v388wq2GnkdIZVJ79nqOWAZZZ0Upxb0zfJqzRehieNvTkd0LrCWTY5ZIX8TN0789gw/QpzXpdVmZ3bva4MQW7cmLU+2H4sKIRdWu8y2nZSXwRRBYFd9okJnrsRBjAiG5GhXtKjZWsx0rueXS58PP94PiV95JpnUGxl5IjV2XWuxMYEdR1a6CSwSPYqtiNMSolwMxet7RGu/GPdlo039OuKYlvcd5IpaA/0HhP1/CHh8WqSWCnVyOr0mHQUKKo1JTgPf/qH/JvD0+FiqkF6LcU9rkZGvZVK0iR6dT8B7C3J3orGxj2AMlHyZYdtHsPWhvgkJkg7vJfW+jvmd9nbpqcyg07AlIXiGwyssvYtyv0W9gUFwrVNj7XVbrpjPT8CO00mn17FYenm0eKjo2t3yk3Wz+C8LsdBKuGcT8wJ+9p+BW+5H1o4pnIkl0qQbwM/j65sOyp3Ey32bKTP9BzO3Xwxs/iIsOmf+JMgJDtMzHlMv48ncT2JYVXcZPe44Hu7OZnRKn/Kx+Oh3HZ0Ekaz8M5x0n1NM6WmNFwjZsVS3zV4rrOvMl3eYw5ZpacOsLfy9JqADYUbObcWPUBuDwZGdloui97lDl2gi7HM7o/WmZG1T//3F/QbfxJjA6yOq7nZgjqWgKMwyes0zUXmt5PE/KeypoTZqKoJw1vHWyC+ht3foI9HoBcWcIdaDP1UcRSR/ZjxX2TAbOwEzWU+nR0nEDvdKWJNWVoJT+VOvZx+xtwwpY5HDVBtpkZZPr9wZtW9DTt4LC3+L48+0jrYarzWk7D07DSrlKnzx9fbcZni6rXdyEaRbl8iWorH/xp2cQL//x7kiayi+bpY3in9jJqq0kHQ7H8q0KZOPas/HWvveVvVczXfCRotpv5NnHceeMGp2h9w7u4YD4F+JffjrOfP5E1Fl3Op3l/wDz3MnWtV6FTqUfwq+PQb08dVu3utdxD3KuElb4jUpcV+Kj6Ijdc1BZzGKbi2pNZLuZ229yZrtN3iJ7PiTQFEgNOqho7Ba7Xc+N8QwEblv9N7CIm4NkBojTC06lBHMu0OjDrvUr3A+8Jur4Y2za/KKsQJxOVq17hYWFlSBynC035+fU97InRRNNtDGUhRQ/dHGHmOVTaI2hbqA9e2yNSRjj8fdxipbY9rRu3gG2XOiX568tXXnug4McUkUntujMK1B5uM8H16h57kuEFrrjh/DQde5A47HiKtlcY2X9WPpxDG5RDhZgz+fuGZ7Iz1v4DOAM1EletID7SLP16FF3qb/Ir9cGD7o5FuRSd+vFgFSYywv4kTcb7X/CbCeNoSUtCJsPbCWRgq9PgrfgQRT+PMy+c3m4TT0Owa5DJYpXQHtThY0yHeQDhZx1sy8i3WIo8ugqs6JS9f5QwMnIJk53l4K66c2b1aJ1YuTE68v1zHCobmgiKxeWrw95nxz3oNVzhPkpNLeFhIQ5Rz8iB45sPCqdc8RhRqAh+9V5TmW/YjaEOJYcjvGY3WynjmZgODemkQ5qITQP+nd5yfCu6m6FW9dFzfm16sbxWKWQ7JVz9oWoTaveQaqg9+w8Nw62FrtgOIW9J1lvk2EL810MtenhnL0cWpBkZeIrOg6v2iDI/BDfmgcHlzItQCRwhzhl2bDGbJ9v93c8VMuVesZsjE0lIzhP+jboMY1kA28pQRG4nQ7zJQZfxLvpqIky8zuTL5tFhdC3Z+JE82woGG72cRoIDReoBbdbK6U1jhDUhh599huuk0Iumb7Qx1JEYzSrwTMyloK74TA9qb4bPpJ/abhxF3jbt2z6sbsL7XKF/jxY3dGEA9U4rimd/R+18h2HLsXb3T08IgyhU0IXhHgYJpsw+1Df1ZnyotxPx3bf6367i1FNHxv932j5jcit1BUSkjkPjvqMWkXFb01itr6/nn8eVK3/4pRLFDrnwhjxpNNa3Waea2mtU/4mwB3sN7FqcEHKoTCEdCYXegNr4eoEVREE60vH9BVlptDBnXcUvCSFlbwaIR1PI18Tz6/gKFBb8hYxC3dPUCADbm7X5jXZLvAa9j5FLhKt8aZLCtheF3r0Blzu774LsQ9slibQfy/L9MOc7w9dA99j+Ns9sdiHUNYvtvNrHLHQpigojqqQh9JNWwl1FrE2KqmxifE132R4E0wtZAr9xaxKbiru1icxFhyzEEorkqdc5lIrJpocJHRUzejzelgUNNKy2lbVEJ2pdLaU8PgerifEc+cBE74ub095C3dg0C3wK7jJ+9Zs5lHgRKbLE8kyeSMktJX3lfo7Uurc44NU+8+XyOVkfx3aBtgysqhfKyxQbxArN5CW/GLoFN+DkhrOdqmc0LNzPYo9cJ+hueqpO9tdnpYGnbzmoZC6ywr6Jq0cyHZbIPp5HJtbXFrAedBoS+z5AJOwQtqp/uE0JINzRzmcucOrfFLs23SdKfn5AijznD3Y4ME0eT65NbSfIY9JevL691T6gW/2eSdjtITxd89banKs1rPir/GeZxq7DzKrDN9CSlHyj8yJtwCzbRaPT+n2eBUGvSaOQCBcO7YxG6czj88vb6u9gzNzFxA9N9raavOL4u0tfobesvetHJF+eHdMwqmfeKYEcSfZZWQlCR89qNm146TehPDMzDL9zRsYmH7RrmEVkw2fNjxxn2cFN9sZdqD9g+erQ8MADrEURebz84TMynubtvzPHU6zZLJvuO6DIUD80BhDYd3HBSdF4wVl300H/UT3cue9LsJN8tpZtmeojtuHn/9f1Xrh5aMk7JNl0Z3k1dRd7KU7sBGoZt08jIhjve7W1gi5pTkSSBb+MiizbNozpouVM3+pSXKRWkTevLd+2IAcP3uKhfOyWAT0eNjvalRfVkHMOIxzFE20Cn50+woU/lD8/dPf2/2bIM8g9Vu+zuvtY+Gc7O1nQD5GEaCKD/N6Rbl12i147Qp8TkRUZLDhZRne5qNZWkyW0hbdYtn92KBZH2S86u1DFvEEg/kQ1vdnFE2neN35BGedbauwqy1k8Xe84UU3Ba+e290kEIPbY4N3l+fHkQC8zU2P1vfHKLADZt7Imiire4kcbPLtUcvvRxfAu/rHJvMXhsv21y+OfDt5U9XaqUfyqIYlfag3CMHO7UPDb2w5GpH/Od3UVcNbNfewD/3GTjYrnLrmJTBoxG9f5LAtklYtNxPZ0XytqtpEMylCdJ+Tg2DQS/2+TJw0QrQDuFc/cm13vgsM71DvwJ6PWjx/76r/TkycQ8aeASN33ZrsvfIryjGXM/f3WKrIztf9hiTrBwdkgScbP3LzfocM1HZr9Zm5diuhY1uZbHZ5dVQzTWxA9ljxXy6q8vH+LMYgsxTkZw5ldg3NzdKwt5QeHTtamQ2vq0v4PtU9WRtuc+xdeagtXjq9c8m1V6uvf/tUDSeWHwWbrT/lx7comfrzaXhw+d45/U7v73o73l5e0NBoeRWj/Kt69glozgum7hQKJUyfa3i0TpJkgpj9+hd6HhYcCO9zbz2pdOZjtdqJ6W7BukL3/2nRiH66Crlvc7LR1qbxYYy+5Gr7dFyuNdxV8OoPB/0EyCQvKnqdAbujzf9+bX+41tPt1klj9nY1hKNvfff5qKqu4vCoh1dg2z849nFEiGNte1/i52dpeTuc1on+Q++ww13Aejq21mZXcnqgqe750ZmKzslfK2/bX3quvmeiZtXhHz1sHb24Yk1tIA8579/e/Pl3d1ZXx4eUrrj0LXq8Mim8JhvcGK76mr7zZj943eF1DRYYNIZLVkj5ub0+n7SFlbdXlf4LrLvO09VQeZ/z/WiG/PIXpfWYM3yWw7SlsBckXPIcatkO/cKrgRVhq52PPXpl+BVdc77EUptS48zw8qF8bhgvEpLLrvbxenVNXLPs5aqOmviveaTcebafdSAJl1qca6EAAIs/dMfwaRgIsbLhb21eDu+yRMX7ebGW5/L82KJX5uMd216797en537C1snZ2Y+QwHG5ONY+Tf65XbnrXDmzaC8nt4/t2X7ISC3QRpZNGS6GdbWMfeAhkkTb9kn35UB7quqLjflk1HdoR42h7ccOrSa+0t9uOOEvQ75Htt5P9fq2U2g5TnJydQ2uf0GZe1zxuvYdiQLc+GZVcJp7t4sq+rmc6Y5iFHgndLAiYbZfn2rVwM5r1bSj6C0ot5YL5eBuWdnYWvN/yrbmQ9w+or0LcsDh9W/u7O81T1tY3nLIrcLkZuKd+ctAugHVVuZbku3MraxHhjgZjZ57Zq2k6R7A3c5Twm8Dx1yB50wGkw31wI1T4EiLVdIuH+g4kQnJu9jAEdURF29yGeUbVs6rKCDvmJfNf00ZH6cHz0+WHvpxab+39gjis/oTnKal+/uApQqbuW5apyjSw/aA50PiRZFh90wQSgtm0tF5VywqastNs57n5fdQXde9oSrKQT5PM3wbertNXzra0rbkruNyeK+dm8WHpDGkVuLq3iLnCNPqQ24QTKtW+UNzl18yQRxlnkNzWUXhDsqm9vGT9R8LU1V5ZZwJbuysyey/u7Twb9USk0aGE70fcfrppOsz1yOAw59k3NKj2I/16jl3HP+NnU1pFz9tSALilXRiZqE+vbGlOde3ztL5J6VZYT97Ok8ug4s+GfE6agwqGV3xesjvJWamjWugawk6H8okH3NZlyBcr9r0frnLffD3brjtgI99xxIzDPTZ3Vu4rdkfcqDV3NhlGflv0HDvCnwtZeNr0HDl9Ot1SLvfWNRfU1fdtwz7565IU9nA6/NfoaoNH4hdqbnacK6JbvZDfWLP+53DaorbNNJqFxZruNolVDs0Xt3G6vtrw9Mvm6rbwUqvV8VzPjmfl76ZWkQBHW1y+DsNt7XuclPcnKgHblG/r3N2O/qcxttpF7R8cosrfmeVjN7+LySJWvnBaefBn9SaLM1vo0327ua4JtgPVo0MW3a9x63tzfRACH07uJ0nTx2emDAQ6s7WNUSdCWZleNy46nixrO11qCV+4admTol6E/gM9vJUZY3HkZPnfUH91Jb+f3nW2JDP/2Rp7Wsc5vPO+8GMdEUyTloG8YgctlnZRbVmf0m9yz10r3KdnOTcLvhcWbaGmpjbezyXs5Ee028IPZa5lWXwLVh8Mgu7mj7YG1xY76dvhcTYdP+QPvLmd1srp/485+n4QaD+inFCXRomK7BlTWh79tq8TuCFTZcHTcIRQ0m8w1ac4eQ100paDkC9ypWMMu+56q9wLy4o753ayX/JN/kbeaiWLfnDOePtw53heZPbvbj7ZNBMdx5mSrS1K9I8FFjqjsEvlEeuXhkxFTakRxDP4whHZ9MHkRNe2mf+yVJfCNXRS+oYCP8CuJeyADo3WJot9/rozwC2vJOqDoicoZ8SbCIoDuA7nSlnc/ptr0SXf451t2dbDfvcw7XfWEz3XcEnWtUDVAbihOcepTr33fnxHyhy+a+isx1yXFcYGweZf7e6T3h0++fXQld4bRnseWOtLjgvH2bG9ZnpJnFaa0vLCzDWHR/D+qxSPIlkeph5r5s5US67FO8R7Uc5pKg2+7PsfOlZQcJ6gmtXS8d5moje+h33mldbsLsKF/nHjdldvI+Pzw+2QAxwr2OshJ/7mzqN3JtkJGE//ENnLU48j+W7Z1JfvN+L4Ge76X2kwIlp7fvCT+I7P0wRncUuNXacysIbQt+4a9PkrIV/OobzrLfXk85KrTl8v2V8BY3y2mrtlboq2+uRyYeWY8sReT7kGiI5KbkprwN5cDQ7z3zPd49hD1lY2LW4HRD3tLI5wj3CKzbb7c/bqFY5QhJe0RClo+P+vc+88hqpmb3X13hCp6/bsCHa0ozkONgug75GOPcNjbDFeDvUThmc0tEY9R+ZcaYRXfco91z3EMnk3n4SjSkFyJbRW5Hqf5VL7qVmIkC56szQhR345HwA/TeF1aJLmlCSn0yjKHGIaO976xS/G1UaZM4L/RD3UPaezh7VHsLQ0tDw0OEe4VH0PN5X68xy4826z7DPIHfbuX3dIbcI4TIPqJfdPbehuIi
*/
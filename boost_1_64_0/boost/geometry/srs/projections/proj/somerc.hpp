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

#ifndef BOOST_GEOMETRY_PROJECTIONS_SOMERC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_SOMERC_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/aasincos.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace somerc
    {
            static const double epsilon = 1.e-10;
            static const int n_iter = 6;

            template <typename T>
            struct par_somerc
            {
                T K, c, hlf_e, kR, cosp0, sinp0;
            };

            template <typename T, typename Parameters>
            struct base_somerc_ellipsoid
            {
                par_somerc<T> m_proj_parm;

                // FORWARD(e_forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T half_pi = detail::half_pi<T>();

                    T phip, lamp, phipp, lampp, sp, cp;

                    sp = par.e * sin(lp_lat);
                    phip = 2.* atan( exp( this->m_proj_parm.c * (
                        log(tan(fourth_pi + 0.5 * lp_lat)) - this->m_proj_parm.hlf_e * log((1. + sp)/(1. - sp)))
                        + this->m_proj_parm.K)) - half_pi;
                    lamp = this->m_proj_parm.c * lp_lon;
                    cp = cos(phip);
                    phipp = aasin(this->m_proj_parm.cosp0 * sin(phip) - this->m_proj_parm.sinp0 * cp * cos(lamp));
                    lampp = aasin(cp * sin(lamp) / cos(phipp));
                    xy_x = this->m_proj_parm.kR * lampp;
                    xy_y = this->m_proj_parm.kR * log(tan(fourth_pi + 0.5 * phipp));
                }

                // INVERSE(e_inverse)  ellipsoid & spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    T phip, lamp, phipp, lampp, cp, esp, con, delp;
                    int i;

                    phipp = 2. * (atan(exp(xy_y / this->m_proj_parm.kR)) - fourth_pi);
                    lampp = xy_x / this->m_proj_parm.kR;
                    cp = cos(phipp);
                    phip = aasin(this->m_proj_parm.cosp0 * sin(phipp) + this->m_proj_parm.sinp0 * cp * cos(lampp));
                    lamp = aasin(cp * sin(lampp) / cos(phip));
                    con = (this->m_proj_parm.K - log(tan(fourth_pi + 0.5 * phip)))/this->m_proj_parm.c;
                    for (i = n_iter; i ; --i) {
                        esp = par.e * sin(phip);
                        delp = (con + log(tan(fourth_pi + 0.5 * phip)) - this->m_proj_parm.hlf_e *
                            log((1. + esp)/(1. - esp)) ) *
                            (1. - esp * esp) * cos(phip) * par.rone_es;
                        phip -= delp;
                        if (fabs(delp) < epsilon)
                            break;
                    }
                    if (i) {
                        lp_lat = phip;
                        lp_lon = lamp / this->m_proj_parm.c;
                    } else {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                }

                static inline std::string get_name()
                {
                    return "somerc_ellipsoid";
                }

            };

            // Swiss. Obl. Mercator
            template <typename Parameters, typename T>
            inline void setup_somerc(Parameters const& par, par_somerc<T>& proj_parm)
            {
                static const T fourth_pi = detail::fourth_pi<T>();

                T cp, phip0, sp;

                proj_parm.hlf_e = 0.5 * par.e;
                cp = cos(par.phi0);
                cp *= cp;
                proj_parm.c = sqrt(1 + par.es * cp * cp * par.rone_es);
                sp = sin(par.phi0);
                proj_parm.cosp0 = cos( phip0 = aasin(proj_parm.sinp0 = sp / proj_parm.c) );
                sp *= par.e;
                proj_parm.K = log(tan(fourth_pi + 0.5 * phip0)) - proj_parm.c * (
                    log(tan(fourth_pi + 0.5 * par.phi0)) - proj_parm.hlf_e *
                    log((1. + sp) / (1. - sp)));
                proj_parm.kR = par.k0 * sqrt(par.one_es) / (1. - sp * sp);
            }

    }} // namespace detail::somerc
    #endif // doxygen

    /*!
        \brief Swiss. Obl. Mercator projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Ellipsoid
         - For CH1903
        \par Example
        \image html ex_somerc.gif
    */
    template <typename T, typename Parameters>
    struct somerc_ellipsoid : public detail::somerc::base_somerc_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline somerc_ellipsoid(Params const& , Parameters const& par)
        {
            detail::somerc::setup_somerc(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_somerc, somerc_ellipsoid)
    
        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(somerc_entry, somerc_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(somerc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(somerc, somerc_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_SOMERC_HPP


/* somerc.hpp
1BbmfvvuZhtcd/PoUajlMnyAHkp2TRBQET/wtQDSEBwE8MOZnjZK0t+hWjEKxkU1RRhLLMk9zPDlIjzgLPKo2OOHzpTD/f14kJvKay37E6CU+J6xYvznqZ3+6w9ZbLKO5+EebvUAzJnOWHhjNc64HYcI732TxQpxbQlZCiHLMZFdgMgqXWhiCMKo5gPaGF3DNJ8YA/sYAbstw97wV4eC+AB2bM2Gu8eG8Sx3WM6GIQQu7hIApy3nUh62zAaxH9z9b7CIngf9ye846F54m7uXGnVmyWMXirBGMEy50LLneR/V8Wl/UXW8WNXxyjV0lfRstzTgsg4aJubx/BcZQhcnCOcRBOpmXNvdYeHBmuw8bFPNTlEYGg/8QT649zpD3vBnB8g+gMwgtz1IOGpJvR8UF5VE/rq1nCQYOhp8FXXxSyvejfds2dzoodsm1W51xYxf9NnAT+y84BLcoXOVt5NIYsS7zXj0ovK+JfQe3SIsiXG/8TvLJaBgGsbMlLd/0Pqve/ut+f52xl/N7Uhsd+Oe6NzvVJuLXvMJt+3uXaptb1VtO/QBo99lh7JA6qX1XGZzXzCEO50gfLTKgn0NfJoqkYWhD3fbfPIbBjCJALQxAaxBAK+Dj/sTv5X4qKXuUwkaLGa13QhEkgliCoK4SRk/6r3aMkfmNFJT8ckeRD0jcX1ClR0SqdO71LTg+epFbZHEF7p2p+pdkJo7V05tlwTS5Sr7k0cMgNz7LcEH2zM1C6GK/yvW+I79bTXO7w1vieV7XOZ6r3yUD03exHI8NESBRz3qii93Unl/H/NEb4rlYsyHef/oMVKKM/Yl0mAg9jow3zMGk9TjeborXeyxAqL9/4jtfzxuWW+z238l9eJTvHJf1R2GO98w7L5K54IGZLl7O4ohP/0mz6sG5PYMudEjCgqLcETPjV7zpmz0Y1Yylny+ildyRCyWExnLRCcsq1ZA/z3PI8fgVQ/hLalZnbH78TRdvpLuTTmAPY3Bughsrgn2JATbzgO+dpBfm0340JzW9ZtXsfGx3fR3B3PLugeJgGlGk5r3N1Xa+hWUNjcm7bzYtHdx2lQ04lGEw30ah9+4orniXcjF6/MHh+JNuw+KN9SS890oABLULSFOIyk/QvHRwoj+J2s9GyPw47puRzV7nQPqyxj1qjcQdWezw31xL6B+TNhpqOWd7DZXpvySHGUef1W7iRtFBDfiq2dktA0rIoC2I5TeSahsTXN1UcoEpTgRdAES5KfnAoFt44C78jKDtvJmaePtDk27KrQmocrdQoaKOg+G1eE1X3c493tDsWwoeTVGbciMvpALNUBZBQjaPKqnsSCgugqWkk5RQYhabsm16UgGkwhgcjbMowqNe+51HMZqrF1xr1zuvAP5+EW4BeJFuAl/aiJbE7+8CPdv+DnOV3g/MjTmDTlflf1OzVeo6RU9XanZyZyvAnK+SuL3r5dDVmDaOMjSeKWy9jUcZHuQ4dyuBlnkbu586ZYclg3pHuQp5eI1V5x6Jr1oCdBqgqNdtpsNz+xDzFiwnA04SpEBFJJdGh43nItzRxYgXTV1tByjcU36v2OQzFFMZgKRmWuSWWCQmU7Pm4M3fBQv6bicAQZQ/yoC+JsJoFssgGzwcvn++HokwjRlIk2ZSPkMAnkUgyx51YGm5+6KAfkPNzLlXMoUl/2q2CnKOgrdd6+QNOfUHuOj6bYHpGEa/PfI6Zat6Ph42uWSHctkfPwKTbQmGWMNMvLVWavdXgtokshjjA8CDHzODvvc1Dtlu0azF4x3igpA1FrL7oPR3QI244zmaEZDNoniAI2ZTjG4KtWN1Z3qzSFfMHpDtbh/KuZVe6ZMM4U7OkWl+HIJZsw=
*/
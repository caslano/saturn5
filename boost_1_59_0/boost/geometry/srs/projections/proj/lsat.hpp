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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LSAT_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LSAT_HPP

#include <boost/geometry/srs/projections/impl/aasincos.hpp>
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
    namespace detail { namespace lsat
    {
            static const double tolerance = 1e-7;

            template <typename T>
            struct par_lsat
            {
                T a2, a4, b, c1, c3;
                T q, t, u, w, p22, sa, ca, xj, rlm, rlm2;
            };

            /* based upon Snyder and Linck, USGS-NMD */
            template <typename T>
            inline void
            seraz0(T lam, T const& mult, par_lsat<T>& proj_parm)
            {
                T sdsq, h, s, fc, sd, sq, d__1 = 0;

                lam *= geometry::math::d2r<T>();
                sd = sin(lam);
                sdsq = sd * sd;
                s = proj_parm.p22 * proj_parm.sa * cos(lam) * sqrt((1. + proj_parm.t * sdsq)
                    / ((1. + proj_parm.w * sdsq) * (1. + proj_parm.q * sdsq)));

                d__1 = 1. + proj_parm.q * sdsq;
                h = sqrt((1. + proj_parm.q * sdsq) / (1. + proj_parm.w * sdsq)) * ((1. + proj_parm.w * sdsq)
                    / (d__1 * d__1) - proj_parm.p22 * proj_parm.ca);

                sq = sqrt(proj_parm.xj * proj_parm.xj + s * s);
                fc = mult * (h * proj_parm.xj - s * s) / sq;
                proj_parm.b += fc;
                proj_parm.a2 += fc * cos(lam + lam);
                proj_parm.a4 += fc * cos(lam * 4.);
                fc = mult * s * (h + proj_parm.xj) / sq;
                proj_parm.c1 += fc * cos(lam);
                proj_parm.c3 += fc * cos(lam * 3.);
            }

            template <typename T, typename Parameters>
            struct base_lsat_ellipsoid
            {
                par_lsat<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T half_pi = detail::half_pi<T>();
                    static const T one_and_half_pi = detail::one_and_half_pi<T>();
                    static const T two_and_half_pi = detail::two_and_half_pi<T>();

                    int l, nn;
                    T lamt = 0.0, xlam, sdsq, c, d, s, lamdp = 0.0, phidp, lampp, tanph;
                    T lamtp, cl, sd, sp, sav, tanphi;

                    if (lp_lat > half_pi)
                        lp_lat = half_pi;
                    else if (lp_lat < -half_pi)
                        lp_lat = -half_pi;

                    if (lp_lat >= 0. )
                        lampp = half_pi;
                    else
                        lampp = one_and_half_pi;
                    tanphi = tan(lp_lat);
                    for (nn = 0;;) {
                        T fac;
                        sav = lampp;
                        lamtp = lp_lon + this->m_proj_parm.p22 * lampp;
                        cl = cos(lamtp);
                        if (fabs(cl) < tolerance)
                            lamtp -= tolerance;
                        if( cl < 0 )
                            fac = lampp + sin(lampp) * half_pi;
                        else
                            fac = lampp - sin(lampp) * half_pi;
                        for (l = 50; l; --l) {
                            lamt = lp_lon + this->m_proj_parm.p22 * sav;
                            c = cos(lamt);
                            if (fabs(c) < tolerance)
                                lamt -= tolerance;
                            xlam = (par.one_es * tanphi * this->m_proj_parm.sa + sin(lamt) * this->m_proj_parm.ca) / c;
                            lamdp = atan(xlam) + fac;
                            if (fabs(fabs(sav) - fabs(lamdp)) < tolerance)
                                break;
                            sav = lamdp;
                        }
                        if (!l || ++nn >= 3 || (lamdp > this->m_proj_parm.rlm && lamdp < this->m_proj_parm.rlm2))
                            break;
                        if (lamdp <= this->m_proj_parm.rlm)
                            lampp = two_and_half_pi;
                        else if (lamdp >= this->m_proj_parm.rlm2)
                            lampp = half_pi;
                    }
                    if (l) {
                        sp = sin(lp_lat);
                        phidp = aasin((par.one_es * this->m_proj_parm.ca * sp - this->m_proj_parm.sa * cos(lp_lat) *
                            sin(lamt)) / sqrt(1. - par.es * sp * sp));
                        tanph = log(tan(fourth_pi + .5 * phidp));
                        sd = sin(lamdp);
                        sdsq = sd * sd;
                        s = this->m_proj_parm.p22 * this->m_proj_parm.sa * cos(lamdp) * sqrt((1. + this->m_proj_parm.t * sdsq)
                             / ((1. + this->m_proj_parm.w * sdsq) * (1. + this->m_proj_parm.q * sdsq)));
                        d = sqrt(this->m_proj_parm.xj * this->m_proj_parm.xj + s * s);
                        xy_x = this->m_proj_parm.b * lamdp + this->m_proj_parm.a2 * sin(2. * lamdp) + this->m_proj_parm.a4 *
                            sin(lamdp * 4.) - tanph * s / d;
                        xy_y = this->m_proj_parm.c1 * sd + this->m_proj_parm.c3 * sin(lamdp * 3.) + tanph * this->m_proj_parm.xj / d;
                    } else
                        xy_x = xy_y = HUGE_VAL;
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T half_pi = detail::half_pi<T>();

                    int nn;
                    T lamt, sdsq, s, lamdp, phidp, sppsq, dd, sd, sl, fac, scl, sav, spp;

                    lamdp = xy_x / this->m_proj_parm.b;
                    nn = 50;
                    do {
                        sav = lamdp;
                        sd = sin(lamdp);
                        sdsq = sd * sd;
                        s = this->m_proj_parm.p22 * this->m_proj_parm.sa * cos(lamdp) * sqrt((1. + this->m_proj_parm.t * sdsq)
                             / ((1. + this->m_proj_parm.w * sdsq) * (1. + this->m_proj_parm.q * sdsq)));
                        lamdp = xy_x + xy_y * s / this->m_proj_parm.xj - this->m_proj_parm.a2 * sin(
                            2. * lamdp) - this->m_proj_parm.a4 * sin(lamdp * 4.) - s / this->m_proj_parm.xj * (
                            this->m_proj_parm.c1 * sin(lamdp) + this->m_proj_parm.c3 * sin(lamdp * 3.));
                        lamdp /= this->m_proj_parm.b;
                    } while (fabs(lamdp - sav) >= tolerance && --nn);
                    sl = sin(lamdp);
                    fac = exp(sqrt(1. + s * s / this->m_proj_parm.xj / this->m_proj_parm.xj) * (xy_y -
                        this->m_proj_parm.c1 * sl - this->m_proj_parm.c3 * sin(lamdp * 3.)));
                    phidp = 2. * (atan(fac) - fourth_pi);
                    dd = sl * sl;
                    if (fabs(cos(lamdp)) < tolerance)
                        lamdp -= tolerance;
                    spp = sin(phidp);
                    sppsq = spp * spp;
                    lamt = atan(((1. - sppsq * par.rone_es) * tan(lamdp) *
                        this->m_proj_parm.ca - spp * this->m_proj_parm.sa * sqrt((1. + this->m_proj_parm.q * dd) * (
                        1. - sppsq) - sppsq * this->m_proj_parm.u) / cos(lamdp)) / (1. - sppsq
                        * (1. + this->m_proj_parm.u)));
                    sl = lamt >= 0. ? 1. : -1.;
                    scl = cos(lamdp) >= 0. ? 1. : -1;
                    lamt -= half_pi * (1. - scl) * sl;
                    lp_lon = lamt - this->m_proj_parm.p22 * lamdp;
                    if (fabs(this->m_proj_parm.sa) < tolerance)
                        lp_lat = aasin(spp / sqrt(par.one_es * par.one_es + par.es * sppsq));
                    else
                        lp_lat = atan((tan(lamdp) * cos(lamt) - this->m_proj_parm.ca * sin(lamt)) /
                            (par.one_es * this->m_proj_parm.sa));
                }

                static inline std::string get_name()
                {
                    return "lsat_ellipsoid";
                }

            };

            // Space oblique for LANDSAT
            template <typename Params, typename Parameters, typename T>
            inline void setup_lsat(Params const& params, Parameters& par, par_lsat<T>& proj_parm)
            {
                static T const d2r = geometry::math::d2r<T>();
                static T const pi = detail::pi<T>();
                static T const two_pi = detail::two_pi<T>();

                int land, path;
                T lam, alf, esc, ess;

                land = pj_get_param_i<srs::spar::lsat>(params, "lsat", srs::dpar::lsat);
                if (land <= 0 || land > 5)
                    BOOST_THROW_EXCEPTION( projection_exception(error_lsat_not_in_range) );

                path = pj_get_param_i<srs::spar::path>(params, "path", srs::dpar::path);
                if (path <= 0 || path > (land <= 3 ? 251 : 233))
                    BOOST_THROW_EXCEPTION( projection_exception(error_path_not_in_range) );

                if (land <= 3) {
                    par.lam0 = d2r * 128.87 - two_pi / 251. * path;
                    proj_parm.p22 = 103.2669323;
                    alf = d2r * 99.092;
                } else {
                    par.lam0 = d2r * 129.3 - two_pi / 233. * path;
                    proj_parm.p22 = 98.8841202;
                    alf = d2r * 98.2;
                }
                proj_parm.p22 /= 1440.;
                proj_parm.sa = sin(alf);
                proj_parm.ca = cos(alf);
                if (fabs(proj_parm.ca) < 1e-9)
                    proj_parm.ca = 1e-9;
                esc = par.es * proj_parm.ca * proj_parm.ca;
                ess = par.es * proj_parm.sa * proj_parm.sa;
                proj_parm.w = (1. - esc) * par.rone_es;
                proj_parm.w = proj_parm.w * proj_parm.w - 1.;
                proj_parm.q = ess * par.rone_es;
                proj_parm.t = ess * (2. - par.es) * par.rone_es * par.rone_es;
                proj_parm.u = esc * par.rone_es;
                proj_parm.xj = par.one_es * par.one_es * par.one_es;
                proj_parm.rlm = pi * (1. / 248. + .5161290322580645);
                proj_parm.rlm2 = proj_parm.rlm + two_pi;
                proj_parm.a2 = proj_parm.a4 = proj_parm.b = proj_parm.c1 = proj_parm.c3 = 0.;
                seraz0(0., 1., proj_parm);
                for (lam = 9.; lam <= 81.0001; lam += 18.)
                    seraz0(lam, 4., proj_parm);
                for (lam = 18; lam <= 72.0001; lam += 18.)
                    seraz0(lam, 2., proj_parm);
                seraz0(90., 1., proj_parm);
                proj_parm.a2 /= 30.;
                proj_parm.a4 /= 60.;
                proj_parm.b /= 30.;
                proj_parm.c1 /= 15.;
                proj_parm.c3 /= 45.;
            }

    }} // namespace detail::lsat
    #endif // doxygen

    /*!
        \brief Space oblique for LANDSAT projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lsat (integer)
         - path (integer)
        \par Example
        \image html ex_lsat.gif
    */
    template <typename T, typename Parameters>
    struct lsat_ellipsoid : public detail::lsat::base_lsat_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline lsat_ellipsoid(Params const& params, Parameters & par)
        {
            detail::lsat::setup_lsat(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_lsat, lsat_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(lsat_entry, lsat_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(lsat_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(lsat, lsat_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LSAT_HPP


/* lsat.hpp
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
*/
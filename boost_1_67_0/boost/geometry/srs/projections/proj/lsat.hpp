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
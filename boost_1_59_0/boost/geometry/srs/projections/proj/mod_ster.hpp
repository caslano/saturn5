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

#ifndef BOOST_GEOMETRY_PROJECTIONS_MOD_STER_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MOD_STER_HPP

#include <boost/geometry/util/math.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/aasincos.hpp>
#include <boost/geometry/srs/projections/impl/pj_zpoly1.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace mod_ster
    {

            static const double epsilon = 1e-12;

            template <typename T>
            struct par_mod_ster
            {
                T              cchio, schio;
                pj_complex<T>* zcoeff;
                int            n;
            };

            /* based upon Snyder and Linck, USGS-NMD */

            template <typename T, typename Parameters>
            struct base_mod_ster_ellipsoid
            {
                par_mod_ster<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T sinlon, coslon, esphi, chi, schi, cchi, s;
                    pj_complex<T> p;

                    sinlon = sin(lp_lon);
                    coslon = cos(lp_lon);
                    esphi = par.e * sin(lp_lat);
                    chi = 2. * atan(tan((half_pi + lp_lat) * .5) *
                        math::pow((T(1) - esphi) / (T(1) + esphi), par.e * T(0.5))) - half_pi;
                    schi = sin(chi);
                    cchi = cos(chi);
                    s = 2. / (1. + this->m_proj_parm.schio * schi + this->m_proj_parm.cchio * cchi * coslon);
                    p.r = s * cchi * sinlon;
                    p.i = s * (this->m_proj_parm.cchio * schi - this->m_proj_parm.schio * cchi * coslon);
                    p = pj_zpoly1(p, this->m_proj_parm.zcoeff, this->m_proj_parm.n);
                    xy_x = p.r;
                    xy_y = p.i;
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    int nn;
                    pj_complex<T> p, fxy, fpxy, dp;
                    T den, rh = 0, z, sinz = 0, cosz = 0, chi, phi = 0, dphi, esphi;

                    p.r = xy_x;
                    p.i = xy_y;
                    for (nn = 20; nn ;--nn) {
                        fxy = pj_zpolyd1(p, this->m_proj_parm.zcoeff, this->m_proj_parm.n, &fpxy);
                        fxy.r -= xy_x;
                        fxy.i -= xy_y;
                        den = fpxy.r * fpxy.r + fpxy.i * fpxy.i;
                        dp.r = -(fxy.r * fpxy.r + fxy.i * fpxy.i) / den;
                        dp.i = -(fxy.i * fpxy.r - fxy.r * fpxy.i) / den;
                        p.r += dp.r;
                        p.i += dp.i;
                        if ((fabs(dp.r) + fabs(dp.i)) <= epsilon)
                            break;
                    }
                    if (nn) {
                        rh = boost::math::hypot(p.r, p.i);
                        z = 2. * atan(.5 * rh);
                        sinz = sin(z);
                        cosz = cos(z);
                        lp_lon = par.lam0;
                        if (fabs(rh) <= epsilon) {
                            /* if we end up here input coordinates were (0,0).
                             * pj_inv() adds P->lam0 to lp.lam, this way we are
                             * sure to get the correct offset */
                            lp_lon = 0.0;
                            lp_lat = par.phi0;
                            return;
                        }
                        chi = aasin(cosz * this->m_proj_parm.schio + p.i * sinz * this->m_proj_parm.cchio / rh);
                        phi = chi;
                        for (nn = 20; nn ;--nn) {
                            esphi = par.e * sin(phi);
                            dphi = 2. * atan(tan((half_pi + chi) * .5) *
                                math::pow((T(1) + esphi) / (T(1) - esphi), par.e * T(0.5))) - half_pi - phi;
                            phi += dphi;
                            if (fabs(dphi) <= epsilon)
                                break;
                        }
                    }
                    if (nn) {
                        lp_lat = phi;
                        lp_lon = atan2(p.r * sinz, rh * this->m_proj_parm.cchio * cosz - p.i *
                            this->m_proj_parm.schio * sinz);
                    } else
                        lp_lon = lp_lat = HUGE_VAL;
                }

                static inline std::string get_name()
                {
                    return "mod_ster_ellipsoid";
                }

            };

            template <typename Parameters, typename T>
            inline void setup(Parameters& par, par_mod_ster<T>& proj_parm)  /* general initialization */
            {
                static T const half_pi = detail::half_pi<T>();

                T esphi, chio;

                if (par.es != 0.0) {
                    esphi = par.e * sin(par.phi0);
                    chio = 2. * atan(tan((half_pi + par.phi0) * .5) *
                        math::pow((T(1) - esphi) / (T(1) + esphi), par.e * T(0.5))) - half_pi;
                } else
                    chio = par.phi0;
                proj_parm.schio = sin(chio);
                proj_parm.cchio = cos(chio);
            }


            /* Miller Oblated Stereographic */
            template <typename Parameters, typename T>
            inline void setup_mil_os(Parameters& par, par_mod_ster<T>& proj_parm)
            {
                static const T d2r = geometry::math::d2r<T>();

                static pj_complex<T> AB[] = {
                    {0.924500, 0.},
                    {0.,       0.},
                    {0.019430, 0.}
                };

                proj_parm.n = 2;
                par.lam0 = d2r * 20.;
                par.phi0 = d2r * 18.;
                proj_parm.zcoeff = AB;
                par.es = 0.;

                setup(par, proj_parm);
            }

            /* Lee Oblated Stereographic */
            template <typename Parameters, typename T>
            inline void setup_lee_os(Parameters& par, par_mod_ster<T>& proj_parm)
            {
                static const T d2r = geometry::math::d2r<T>();

                static pj_complex<T> AB[] = {
                    { 0.721316,   0.},
                    { 0.,         0.},
                    {-0.0088162, -0.00617325}
                };

                proj_parm.n = 2;
                par.lam0 = d2r * -165.;
                par.phi0 = d2r * -10.;
                proj_parm.zcoeff = AB;
                par.es = 0.;

                setup(par, proj_parm);
            }

            // Mod. Stererographics of 48 U.S.
            template <typename Parameters, typename T>
            inline void setup_gs48(Parameters& par, par_mod_ster<T>& proj_parm)
            {
                static const T d2r = geometry::math::d2r<T>();

                static pj_complex<T> AB[] = { /* 48 United States */
                    { 0.98879,  0.},
                    { 0.,       0.},
                    {-0.050909, 0.},
                    { 0.,       0.},
                    { 0.075528, 0.}
                };

                proj_parm.n = 4;
                par.lam0 = d2r * -96.;
                par.phi0 = d2r * -39.;
                proj_parm.zcoeff = AB;
                par.es = 0.;
                par.a = 6370997.;

                setup(par, proj_parm);
            }

            // Mod. Stererographics of Alaska
            template <typename Parameters, typename T>
            inline void setup_alsk(Parameters& par, par_mod_ster<T>& proj_parm)
            {
                static const T d2r = geometry::math::d2r<T>();

                static pj_complex<T> ABe[] = { /* Alaska ellipsoid */
                    { .9945303, 0.},
                    { .0052083, -.0027404},
                    { .0072721,  .0048181},
                    {-.0151089, -.1932526},
                    { .0642675, -.1381226},
                    { .3582802, -.2884586}
                };

                static pj_complex<T> ABs[] = { /* Alaska sphere */
                    { .9972523, 0.},
                    { .0052513, -.0041175},
                    { .0074606,  .0048125},
                    {-.0153783, -.1968253},
                    { .0636871, -.1408027},
                    { .3660976, -.2937382}
                };

                proj_parm.n = 5;
                par.lam0 = d2r * -152.;
                par.phi0 = d2r * 64.;
                if (par.es != 0.0) { /* fixed ellipsoid/sphere */
                    proj_parm.zcoeff = ABe;
                    par.a = 6378206.4;
                    par.e = sqrt(par.es = 0.00676866);
                } else {
                    proj_parm.zcoeff = ABs;
                    par.a = 6370997.;
                }

                setup(par, proj_parm);
            }

            // Mod. Stererographics of 50 U.S.
            template <typename Parameters, typename T>
            inline void setup_gs50(Parameters& par, par_mod_ster<T>& proj_parm)
            {
                static const T d2r = geometry::math::d2r<T>();

                static pj_complex<T> ABe[] = { /* GS50 ellipsoid */
                    { .9827497, 0.},
                    { .0210669,  .0053804},
                    {-.1031415, -.0571664},
                    {-.0323337, -.0322847},
                    { .0502303,  .1211983},
                    { .0251805,  .0895678},
                    {-.0012315, -.1416121},
                    { .0072202, -.1317091},
                    {-.0194029,  .0759677},
                    {-.0210072,  .0834037}
                };
                static pj_complex<T> ABs[] = { /* GS50 sphere */
                    { .9842990, 0.},
                    { .0211642,  .0037608},
                    {-.1036018, -.0575102},
                    {-.0329095, -.0320119},
                    { .0499471,  .1223335},
                    { .0260460,  .0899805},
                    { .0007388, -.1435792},
                    { .0075848, -.1334108},
                    {-.0216473,  .0776645},
                    {-.0225161,  .0853673}
                };

                proj_parm.n = 9;
                par.lam0 = d2r * -120.;
                par.phi0 = d2r * 45.;
                if (par.es != 0.0) { /* fixed ellipsoid/sphere */
                    proj_parm.zcoeff = ABe;
                    par.a = 6378206.4;
                    par.e = sqrt(par.es = 0.00676866);
                } else {
                    proj_parm.zcoeff = ABs;
                    par.a = 6370997.;
                }

                setup(par, proj_parm);
            }

    }} // namespace detail::mod_ster
    #endif // doxygen

    /*!
        \brief Miller Oblated Stereographic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal (mod)
        \par Example
        \image html ex_mil_os.gif
    */
    template <typename T, typename Parameters>
    struct mil_os_ellipsoid : public detail::mod_ster::base_mod_ster_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline mil_os_ellipsoid(Params const& , Parameters & par)
        {
            detail::mod_ster::setup_mil_os(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Lee Oblated Stereographic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal (mod)
        \par Example
        \image html ex_lee_os.gif
    */
    template <typename T, typename Parameters>
    struct lee_os_ellipsoid : public detail::mod_ster::base_mod_ster_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline lee_os_ellipsoid(Params const& , Parameters & par)
        {
            detail::mod_ster::setup_lee_os(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Mod. Stererographics of 48 U.S. projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal (mod)
        \par Example
        \image html ex_gs48.gif
    */
    template <typename T, typename Parameters>
    struct gs48_ellipsoid : public detail::mod_ster::base_mod_ster_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline gs48_ellipsoid(Params const& , Parameters & par)
        {
            detail::mod_ster::setup_gs48(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Mod. Stererographics of Alaska projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal (mod)
        \par Example
        \image html ex_alsk.gif
    */
    template <typename T, typename Parameters>
    struct alsk_ellipsoid : public detail::mod_ster::base_mod_ster_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline alsk_ellipsoid(Params const& , Parameters & par)
        {
            detail::mod_ster::setup_alsk(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Mod. Stererographics of 50 U.S. projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal (mod)
        \par Example
        \image html ex_gs50.gif
    */
    template <typename T, typename Parameters>
    struct gs50_ellipsoid : public detail::mod_ster::base_mod_ster_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline gs50_ellipsoid(Params const& , Parameters & par)
        {
            detail::mod_ster::setup_gs50(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mil_os, mil_os_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_lee_os, lee_os_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_gs48, gs48_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_alsk, alsk_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_gs50, gs50_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mil_os_entry, mil_os_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(lee_os_entry, lee_os_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(gs48_entry, gs48_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(alsk_entry, alsk_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(gs50_entry, gs50_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(mod_ster_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mil_os, mil_os_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(lee_os, lee_os_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(gs48, gs48_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(alsk, alsk_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(gs50, gs50_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MOD_STER_HPP


/* mod_ster.hpp
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
*/
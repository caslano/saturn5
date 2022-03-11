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
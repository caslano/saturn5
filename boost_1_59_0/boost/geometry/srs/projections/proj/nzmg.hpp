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

// Purpose:  Implementation of the nzmg (New Zealand Map Grid) projection.
//           Very loosely based upon DMA code by Bradford W. Drew
// Author:   Gerald Evenden
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_NZMG_HPP
#define BOOST_GEOMETRY_PROJECTIONS_NZMG_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_zpoly1.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace nzmg
    {

            static const double epsilon = 1e-10;
            static const int Nbf = 5;
            static const int Ntpsi = 9;
            static const int Ntphi = 8;

            template <typename T>
            inline T sec5_to_rad() { return 0.4848136811095359935899141023; }
            template <typename T>
            inline T rad_to_sec5() { return 2.062648062470963551564733573; }

            template <typename T>
            inline const pj_complex<T> * bf()
            {
                static const pj_complex<T> result[] = {
                    {.7557853228,    0.0},
                    {.249204646,    .003371507},
                    {-.001541739,    .041058560},
                    {-.10162907,    .01727609},
                    {-.26623489,    -.36249218},
                    {-.6870983,    -1.1651967}
                };
                return result;
            }

            template <typename T>
            inline const T * tphi()
            {
                static const T result[] = { 1.5627014243, .5185406398, -.03333098,
                                            -.1052906,   -.0368594,     .007317,
                                             .01220,      .00394,      -.0013 };
                return result;
            }
            template <typename T>
            inline const T * tpsi()
            {
                static const T result[] = { .6399175073, -.1358797613, .063294409, -.02526853, .0117879,
                                           -.0055161,     .0026906,   -.001333,     .00067,   -.00034 };
                return result;
            }

            template <typename T, typename Parameters>
            struct base_nzmg_ellipsoid
            {
                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T rad_to_sec5 = nzmg::rad_to_sec5<T>();

                    pj_complex<T> p;
                    const T * C;
                    int i;

                    lp_lat = (lp_lat - par.phi0) * rad_to_sec5;
                    for (p.r = *(C = tpsi<T>() + (i = Ntpsi)); i ; --i)
                        p.r = *--C + lp_lat * p.r;
                    p.r *= lp_lat;
                    p.i = lp_lon;
                    p = pj_zpoly1(p, bf<T>(), Nbf);
                    xy_x = p.i;
                    xy_y = p.r;
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T sec5_to_rad = nzmg::sec5_to_rad<T>();

                    int nn, i;
                    pj_complex<T> p, f, fp, dp;
                    T den;
                    const T* C;

                    p.r = xy_y;
                    p.i = xy_x;
                    for (nn = 20; nn ;--nn) {
                        f = pj_zpolyd1(p, bf<T>(), Nbf, &fp);
                        f.r -= xy_y;
                        f.i -= xy_x;
                        den = fp.r * fp.r + fp.i * fp.i;
                        p.r += dp.r = -(f.r * fp.r + f.i * fp.i) / den;
                        p.i += dp.i = -(f.i * fp.r - f.r * fp.i) / den;
                        if ((fabs(dp.r) + fabs(dp.i)) <= epsilon)
                            break;
                    }
                    if (nn) {
                        lp_lon = p.i;
                        for (lp_lat = *(C = tphi<T>() + (i = Ntphi)); i ; --i)
                            lp_lat = *--C + p.r * lp_lat;
                        lp_lat = par.phi0 + p.r * lp_lat * sec5_to_rad;
                    } else
                        lp_lon = lp_lat = HUGE_VAL;
                }

                static inline std::string get_name()
                {
                    return "nzmg_ellipsoid";
                }

            };

            // New Zealand Map Grid
            template <typename Parameters>
            inline void setup_nzmg(Parameters& par)
            {
                typedef typename Parameters::type calc_t;
                static const calc_t d2r = geometry::math::d2r<calc_t>();

                /* force to International major axis */
                par.a = 6378388.0;
                par.ra = 1. / par.a;
                par.lam0 = 173. * d2r;
                par.phi0 = -41. * d2r;
                par.x0 = 2510000.;
                par.y0 = 6023150.;
            }

    }} // namespace detail::nzmg
    #endif // doxygen

    /*!
        \brief New Zealand Map Grid projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Fixed Earth
        \par Example
        \image html ex_nzmg.gif
    */
    template <typename T, typename Parameters>
    struct nzmg_ellipsoid : public detail::nzmg::base_nzmg_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline nzmg_ellipsoid(Params const& , Parameters & par)
        {
            detail::nzmg::setup_nzmg(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_nzmg, nzmg_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(nzmg_entry, nzmg_ellipsoid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(nzmg_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(nzmg, nzmg_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_NZMG_HPP


/* nzmg.hpp
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
*/
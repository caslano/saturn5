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
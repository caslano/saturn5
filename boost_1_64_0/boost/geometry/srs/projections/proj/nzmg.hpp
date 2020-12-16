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
0frk2AkjD0uxE9Ze5NAJLH7l23PVD/xoguiLjqqZtKEKrHFVuUVvdLIm4UE/4ua0IntaEaR5OK2YfdyYacXEFeZRYok9sYQftXb/+B5MgR6q6Wse8hMcNOfZTv3hB2Hcdo+Y7anMc003L+Zqzl5xem+LFkysgARwQ8R+OA+HcEYPDtUNo1B7Dp00HEMzPfGewoAGc+IYUxBKxQWC/Fanov5iqY8RMusj1/bnYDVIrs8h2xtp3l5WGYY66yOXhHQv6rzNW9tT6ewpZ3nLVeofux5obPpY0XiOOFaUmseGC88VRyZ8AMvtsnjRv7oniQqGCdFHhrEMspvCEKEHrTKEje2QjgIlDg2HEABk1E/DbVZrPXGo9d8q7L8U+GWvQ01WAdlgVU142KNTgeZKK2Skp7Y8avbVEd2+O5KCfXfT++9Jvcz9N1c6QQn9MCmOc9xJ5xhnfu5loW0q5xXqqW96mntoLmMs7xaGd4cEC38Nci89MdblGgJLBmkihs3eSxuXOFXSaRIg00uhX53sx8dSx6qjf1D2MwbjufFBMnkVDcPh1lnCm7EO1ihph56CfzdRfjfKrrbUh1AQpCPcvI5WK3z4w6/mp6b/18Pa621j9DTySRQMTcOlFf5Khia3G2l4h6Er+u3r2HJFP6qF3q6jrQ2B2Drq7c625mFs8u6zns+Wdrfqa8VCVFi23KqGyFQq7hW+s9OVfYX5sE+y85+OP6zjx6BxzcHhl00PBZv3RxAONre+Le1mXU8ifrbYlmPlTI8TOQ/uSFhL4Bce9Lnxd69LOkVzlR1ZDZ+1RjY94VzZ4ClvF0uDr/p90GL5MsBH8D8hCSxYplTNzukA/g4bvIG5D7pkVENnIe9Wxixh47CPveQhlW+5lyLW0nUeleyTyV5MvgGTR6/zqeSP91LyKRx6BkJSJwQr2hbznIZ5emKUF6L8GDWA6s7tOEJVeEUWVtgTmCvF6hG1A7VUaOpea4UMnKdXW5ozbq+1OVsw+SxLfX/JyUM45HWq792Yp5tW35sxqi3VN34DV/a7IFbWB+Tsw9gJHPshxaZBbDrGjuLYVym2DcRmYOyJbH7NDxZUR/LZRXkPCgr6r4yh5h4yizaYIy2W9lNpELXuz8b55nTVTJXcpn+Op//mTWLfFuW8vNTd0Jk1z1I6P7XnnBoLiKiT4BhrP0cnVMg3NMSRYjCsx9My+HsefGvQaUEA5q2ENH8tau9jHnNQo2PlL1STZvyVvKuSnfW/unCreQEPcJ2Y6aMqn9D/YiX4kMno6ZqFblVTUSi09PLKzlb/ngFdAfQQ1flSL1sVuFQ/ysknCgK8s3h7j7cl3ek8/p1bMv6dPC0Y/8WJ49+ulcZf7i+V/55Iyv57eP8SsK7zzpsWlNwmf98/dXwVqeGj+RuJJPF3EwluaCad1QQJwvk8ld1R+edthB8fctoGxHFqnenFYf97Xu01y64FC2Dm4UXbJLVMvPKeN6U3bvTzYBJ/QBHTH1Cz+8WzOhzEfnF+wn5xfXrL94s2/YuNWVQT7iflbl2xlbIwBZU+zS9svKVB8JZ4UCZke1rCbTT+lst10StwkV6BBHVXeryhm0O1+EmGLL1e+Wrus9ouzqNUamn+8p2OerOC5lHPVCrgoNqG7yLmRMqZnpm4FTxW3MIXmQ+R66cPmtc8pdNGuKRL/u9czd08vnsaiwgCC3BzaooJBo2wPhtFcrUpx7hc0ktvYw2cAotnhbk+gCBclilev6lT1Qu/Iiocn8Z5okvhJoQRKvWIo9r62MMvBaNefLvLiuEk7VEdxoPCtKNBBw1iiuv7wZjIt1aQyCGTzy06qhUEEC38WflbfjL+5m+OvyF3btbfV24=
*/
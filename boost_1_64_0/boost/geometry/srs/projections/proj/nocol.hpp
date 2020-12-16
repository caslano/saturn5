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

#ifndef BOOST_GEOMETRY_PROJECTIONS_NOCOL_HPP
#define BOOST_GEOMETRY_PROJECTIONS_NOCOL_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace nocol
    {

            static const double epsilon = 1e-10;

            template <typename T, typename Parameters>
            struct base_nocol_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    if (fabs(lp_lon) < epsilon) {
                        xy_x = 0;
                        xy_y = lp_lat;
                    } else if (fabs(lp_lat) < epsilon) {
                        xy_x = lp_lon;
                        xy_y = 0.;
                    } else if (fabs(fabs(lp_lon) - half_pi) < epsilon) {
                        xy_x = lp_lon * cos(lp_lat);
                        xy_y = half_pi * sin(lp_lat);
                    } else if (fabs(fabs(lp_lat) - half_pi) < epsilon) {
                        xy_x = 0;
                        xy_y = lp_lat;
                    } else {
                        T tb, c, d, m, n, r2, sp;

                        tb = half_pi / lp_lon - lp_lon / half_pi;
                        c = lp_lat / half_pi;
                        d = (1 - c * c)/((sp = sin(lp_lat)) - c);
                        r2 = tb / d;
                        r2 *= r2;
                        m = (tb * sp / d - 0.5 * tb)/(1. + r2);
                        n = (sp / r2 + 0.5 * d)/(1. + 1./r2);
                        xy_x = cos(lp_lat);
                        xy_x = sqrt(m * m + xy_x * xy_x / (1. + r2));
                        xy_x = half_pi * ( m + (lp_lon < 0. ? -xy_x : xy_x));
                        xy_y = sqrt(n * n - (sp * sp / r2 + d * sp - 1.) /
                            (1. + 1./r2));
                        xy_y = half_pi * ( n + (lp_lat < 0. ? xy_y : -xy_y ));
                    }
                }

                static inline std::string get_name()
                {
                    return "nocol_spheroid";
                }

            };

            // Nicolosi Globular
            template <typename Parameters>
            inline void setup_nicol(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::nocol
    #endif // doxygen

    /*!
        \brief Nicolosi Globular projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_nicol.gif
    */
    template <typename T, typename Parameters>
    struct nicol_spheroid : public detail::nocol::base_nocol_spheroid<T, Parameters>
    {
        template <typename Params>
        inline nicol_spheroid(Params const& , Parameters & par)
        {
            detail::nocol::setup_nicol(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_nicol, nicol_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(nicol_entry, nicol_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(nocol_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(nicol, nicol_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_NOCOL_HPP


/* nocol.hpp
OFFjXMTX0oWgKf9HXFV1a1kEUoNUFucFmWNAEmJbnt8fri3PZe15su6aSQdZ6gUP98LMX2IvfIKL4B9UL/g6/oiFuSn6P91CP21M+j85Kf1Q9kGnO8/HD7v6XE3zD6dJmeu2ET8L25KU/+wI5/J/1VT5llk4nfM2e6XhFgfSrE50IMWV6Gy8zvDgdcZGls/sGEjXGQO2whq0OcvnSvQ3hTncB+0ypHn/P6dZt1ZD+QRw+gRwtof6ANNotx9sT3PqqIE4p+7CORVUG6tVQRIpoSjOopUDcB3bU+O+GYBHj6rt2Kn7Aj5pvz0iL9aZAV4HAC410MGnq/LMmw3ZNLRwCsEoXtJ7xbtqaZsrMO1H2mdvS0V+OivfXGTBayebGo0Wcp1DKBpe7PDFT1GfqNYcmdZehU3JEPrU5IMIn79yjbeHiHuUpItx8/uRXadaXZFMh41QBhPnhpMggb7uhWU6ZX9WhLSSkbIykEk0MTLr6pRcA89Jn+24U1PQZ1umntTsqZzD2hXaticfdqv/1+HaVilCfOfEA43J5e2C/jm/GHailJtYea3xOKSUU5FSlivue0smUcojFkqJ2FXnKjn/S5T/aT3/iExddS6SoDp3K+eeTbnX67n9nLufnlvRW0RXnVvRobWu6Cz9Fc3TrP78os/Wu6nWrx6LtX4Ba71C1XpMO+qzNh553qs9mc57vbUL3r8CYnkdihHqOhSEi3pwlcsajOSr78qYH08FZVSjbVyjwVSjfL1GNYco7+Zco6HAC9SEpCgwhXNTDIfS51V941ZFEmcXqdHpxv2AjkLsGkAiPeFiVeUv9BZ86mJpo0wVQe16eECmQloBEfhT4V0iPHAnxUjS7djeJ4r+8gQSiV5NyUq2fbGcN6tkw3HyDM7zl+XrjW8sDDmCzsvz2wGDwizp6HiWPUmQftpCr4t1z2E73opM/Sf82c4H405J1Bd9N1Ff9N2W6YuK+z6cVhua4f8nN8H/r81V/H9IC/h/LvF/Rsor9mu0kGznifPUyeoO7yOAtEhaqkf60ZysbJjzVDGB5kUdJ0lbywYjKnkXZ2LGNbt2F5IsTH+3deNl3J8hCEGy9zEDBLFq2edRImNPK5DI86tnR+Fbtc8Pc1Aap/50c9Eyd7KHavrAYU+r6gOvG2LVJAphIaS6y+svqO4i7cknz68Iseruwj2kuhvdo6vuLgXQ+psRXoXJNtuqbOnl3Wr9hXbV3ZVyYa+PeDXl091S+TQsI8PzaISRmvD6UVc+3S2VT01dVQXev36vqej6KcTVv2ENJ9QWori2T3ia1Fm9C6IsWfbbdFYbSGd1f4LOKsbARZvSJj3TrMh+B53V/nopZr6OHged1R/cGrRLwswKUOxmGhm36vA/S3CYXgv5kXsOsi1edcULOLC/B6g4Yl8mwYkGdcXXHFtCDmuw5tRf5ZDJVHwdpJJs+rKDICwexBttrRMqxnvkg2gBxq0SaUrBN0KwPwSVBP9DJBkgx4XjmB1SJVeucmU9WPOt8Rii9PYc2n0chsoyyCy//gGVidV3uOZscJrO+9MZ5JJgGkEpx0uYYR6uiJp27grYbsYLBKTRHOSvEbIPQSJ3dFTkrZDH+sChro8/gDbCfciT8Hc9/LsIvifDv0Xwb8qHHtcx8HcZ/H0T/rX7yOO6Fv5thX/fwL9vd0M6xPfaAziybD83//F4ZQSo7GY5/9pm+Z2i0zPU5yGW6HaZoOu77f+/lv1s+429v7Tqn37jStS/hTir/i0E1RKSijyrkgsQU1Y+ea+oH+dtYE2F34sSKd7fn8yvYcb74G76UdxNVyvpwXUu2k2P1fwI8CY8j7M9S9ke17MN4Ww9LOwrm5jCSLo=
*/
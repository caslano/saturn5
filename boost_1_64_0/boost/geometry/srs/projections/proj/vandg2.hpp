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

#ifndef BOOST_GEOMETRY_PROJECTIONS_VANDG2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_VANDG2_HPP

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
    namespace detail { namespace vandg2
    {

            static const double tolerance = 1e-10;

            struct par_vandg2
            {
                bool    vdg3;
            };

            template <typename T, typename Parameters>
            struct base_vandg2_spheroid
            {
                par_vandg2 m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T pi = detail::pi<T>();
                    static const T two_div_pi = detail::two_div_pi<T>();

                    T x1, at, bt, ct;

                    bt = fabs(two_div_pi * lp_lat);
                    if ((ct = 1. - bt * bt) < 0.)
                        ct = 0.;
                    else
                        ct = sqrt(ct);
                    if (fabs(lp_lon) < tolerance) {
                        xy_x = 0.;
                        xy_y = pi * (lp_lat < 0. ? -bt : bt) / (1. + ct);
                    } else {
                        at = 0.5 * fabs(pi / lp_lon - lp_lon / pi);
                        if (this->m_proj_parm.vdg3) {
                            x1 = bt / (1. + ct);
                            xy_x = pi * (sqrt(at * at + 1. - x1 * x1) - at);
                            xy_y = pi * x1;
                        } else {
                            x1 = (ct * sqrt(1. + at * at) - at * ct * ct) /
                                (1. + at * at * bt * bt);
                            xy_x = pi * x1;
                            xy_y = pi * sqrt(1. - x1 * (x1 + 2. * at) + tolerance);
                        }
                        if ( lp_lon < 0.) xy_x = -xy_x;
                        if ( lp_lat < 0.) xy_y = -xy_y;
                    }
                }

                static inline std::string get_name()
                {
                    return "vandg2_spheroid";
                }

            };

            // van der Grinten II
            inline void setup_vandg2(par_vandg2& proj_parm)
            {
                proj_parm.vdg3 = false;
            }

            // van der Grinten III
            template <typename Parameters>
            inline void setup_vandg3(Parameters& par, par_vandg2& proj_parm)
            {
                proj_parm.vdg3 = true;
                par.es = 0.;
            }

    }} // namespace detail::vandg2
    #endif // doxygen

    /*!
        \brief van der Grinten II projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_vandg2.gif
    */
    template <typename T, typename Parameters>
    struct vandg2_spheroid : public detail::vandg2::base_vandg2_spheroid<T, Parameters>
    {
        template <typename Params>
        inline vandg2_spheroid(Params const& , Parameters const& )
        {
            detail::vandg2::setup_vandg2(this->m_proj_parm);
        }
    };

    /*!
        \brief van der Grinten III projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_vandg3.gif
    */
    template <typename T, typename Parameters>
    struct vandg3_spheroid : public detail::vandg2::base_vandg2_spheroid<T, Parameters>
    {
        template <typename Params>
        inline vandg3_spheroid(Params const& , Parameters & par)
        {
            detail::vandg2::setup_vandg3(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_vandg2, vandg2_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_vandg3, vandg3_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(vandg2_entry, vandg2_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(vandg3_entry, vandg3_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(vandg2_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(vandg2, vandg2_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(vandg3, vandg3_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_VANDG2_HPP


/* vandg2.hpp
sgr2bBFUowyMzJrlGK5h0wBOLaSD7PaG+fpBXtSyYkl7mmRfxWTf1QvJnmeSvettIPs52wGu+GvQpK2tzxeJBLkjUZSwjQ3XamrtoVnM77QYS48xLWmMmFu0GK8WU3U1YTWsK5AeS6NHMZpJFOJiZVNjWNn4hO1rGbEWBYa5C78jg2ErNChpz900byBJ1AeJK1hmu3ANGC6GysBSzBglzrSzogfdHzo9NWZx550J4JA4O6Y2fAgbPu0OwxXmw1bcnNJWbm7bytzdtpWx2zYkiYoltcdltTB9g6n3XPIVFZbWNg9yvxtyIDlCMvtd/VuWJ35amgUj2yKfLKBeOBd/l71xqxMmzi5zxA7rhM7Jv7265av9Uu7/76bd//+HN8hYbCyt6tyW6mc7ByDY6nSsXdVDC4sWY1jS/bGLPHzfUzfFcS9VXajkTWBd41CU7JbzDs650i1nFuZMwJur/p/ASN55D4M5n8DMM8G0vAFgmiUYxeFjUorDAig/ralGItCIALqSgeYQ0JAJ9FIAGr+ow1o8TjtOcTr0ar1SD0k+R+h6ogRDWbWdLy5XVQD9mQCQ3sbm7Ezsf4HYV/wlr0e8udz/TCYCSgqPbMaxshmf4xq/Mxdr/E6s8emqxj//EzTjibbLXE2AXCbeGjSwwBlFCi6D6rqt9WAzyRvl8eujRIK8NGUTk9CLSJhhkjALSVjHIjGGqK50cwRDaBZCGyuFbLxAFi7lvVdE3IK+FsDNa2H0YwT61xn90gCiv9VE/9nrgD5sJc3r9Xe6y7TeZpnWyQGSac2FP7F+f0qSablTLxd4uqjNXbL1VoatiHGRtt1qUDZBUvYeU/Z4V6LsPfgTuw6Khkn2mTIpcyt3KCtHyo5zo0yJ3ZotdWvxWHMKesjemVAfr/q/CfMRyZuTfObOyFEyiaIU/gXpc4UH+OIq1BpdC42Y66kaIAPndALFCrukgBeLNSxxXF4Uu2ihioUWKuiixwpKPRGA9ZPTmxyC68c3Agx/99Wh6p717eHmBP/mhsdBxCwsYL4wHy3FNH75gbnCvJlcmz58ruCunVkTKU/1FPNZ7OWZpOdAnD20y1fH5XOfTMt3rGkPu3d6SMp6bTbRw4K0YX7ANB4mITILG4VERtimgsn1xwr/iKypI6Mgkr+lw/+pKryMmkv6SBajLp5JdaBVzeED0qyDFP/PnQi+Buoqn1PLNBFz8Kb+aWFwbc9jOrm2Z6XPtT1/kB6m5PKcfgav2F7yc4nYbnVHuClaUP5ELsR8sgK12vnsX2b7F3TNWx9sEZAPkb6bY46C3i2oGiOAXINscZsAoiwtCqG3Y3bhC6NESU7C55279oU0f6n0H5AW/SjNdqf/qi/+M/RzU0/OSu5PZ3m1/mSr/lTXL61WTob/SWYy/Bt1+F4Ff3B68F37602Zrv11o9e1vz7RNy1Me+Av/RlfSXM13xDyiO2Vfnj8sZUbLfGh+//gd+ZIS72GekHqe8MlT9TS7jTjPIIndQwI9PNXLXmznsXAQQNNJeumTFryoX98ZY2Bxm+ZZPEe9OPH2r22tzdD53+4gBUt0EtMv+heln2sW+k0gmt7L/NpSE60mckGickeKH0vIq5OWCMKSfrwj9Hh/93S4ffjTsZlyWXvaM/utNLuUMmoNnk1VHNJKbXDJkzFWoWBY31RZ05g0BLmY51BwbAPNbpneo7V6fnQQ/R4iZ4zDXpyXehBKk2SzAT2fiDYffzbGtFHefT26uXSXpv/mUgwzn0/X5PMCrozati+MCtY8YXtsIK7XrDEkL8PJqmSJ5by8K6hNBvV4D71Dy6DO/qlliN7sveosKR/dzmu8wNP4aSUT3ZanpqZvShQCAY=
*/
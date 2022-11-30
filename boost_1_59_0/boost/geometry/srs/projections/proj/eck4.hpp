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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ECK4_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ECK4_HPP

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
    namespace detail { namespace eck4
    {

            static const double C_x = .42223820031577120149;
            static const double C_y = 1.32650042817700232218;
            static const double RC_y = .75386330736002178205;
            static const double C_p = 3.57079632679489661922;
            static const double RC_p = .28004957675577868795;
            static const double epsilon = 1e-7;
            static const int n_iter = 6;

            template <typename T, typename Parameters>
            struct base_eck4_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T p, V, s, c;
                    int i;

                    p = C_p * sin(lp_lat);
                    V = lp_lat * lp_lat;
                    lp_lat *= 0.895168 + V * ( 0.0218849 + V * 0.00826809 );
                    for (i = n_iter; i ; --i) {
                        c = cos(lp_lat);
                        s = sin(lp_lat);
                        lp_lat -= V = (lp_lat + s * (c + 2.) - p) /
                            (1. + c * (c + 2.) - s * s);
                        if (fabs(V) < epsilon)
                            break;
                    }
                    if (!i) {
                        xy_x = C_x * lp_lon;
                        xy_y = lp_lat < 0. ? -C_y : C_y;
                    } else {
                        xy_x = C_x * lp_lon * (1. + cos(lp_lat));
                        xy_y = C_y * sin(lp_lat);
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T c;

                    lp_lat = aasin(xy_y * RC_y);
                    lp_lon = xy_x / (C_x * (1. + (c = cos(lp_lat))));
                    lp_lat = aasin((lp_lat + sin(lp_lat) * (c + 2.)) * RC_p);
                }

                static inline std::string get_name()
                {
                    return "eck4_spheroid";
                }

            };

            // Eckert IV
            template <typename Parameters>
            inline void setup_eck4(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::eck4
    #endif // doxygen

    /*!
        \brief Eckert IV projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck4.gif
    */
    template <typename T, typename Parameters>
    struct eck4_spheroid : public detail::eck4::base_eck4_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck4_spheroid(Params const& , Parameters & par)
        {
            detail::eck4::setup_eck4(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck4, eck4_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck4_entry, eck4_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eck4_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck4, eck4_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ECK4_HPP


/* eck4.hpp
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
*/
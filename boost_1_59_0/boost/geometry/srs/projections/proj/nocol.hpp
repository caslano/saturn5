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
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
*/
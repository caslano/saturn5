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
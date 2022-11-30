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

#ifndef BOOST_GEOMETRY_PROJECTIONS_NELL_HPP
#define BOOST_GEOMETRY_PROJECTIONS_NELL_HPP

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
    namespace detail { namespace nell
    {

            static const int max_iter = 10;
            static const double loop_tol = 1e-7;

            template <typename T, typename Parameters>
            struct base_nell_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T k, V;
                    int i;

                    k = 2. * sin(lp_lat);
                    V = lp_lat * lp_lat;
                    lp_lat *= 1.00371 + V * (-0.0935382 + V * -0.011412);
                    for (i = max_iter; i ; --i) {
                        lp_lat -= V = (lp_lat + sin(lp_lat) - k) /
                            (1. + cos(lp_lat));
                        if (fabs(V) < loop_tol)
                            break;
                    }
                    xy_x = 0.5 * lp_lon * (1. + cos(lp_lat));
                    xy_y = lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lon = 2. * xy_x / (1. + cos(xy_y));
                    lp_lat = aasin(0.5 * (xy_y + sin(xy_y)));
                }

                static inline std::string get_name()
                {
                    return "nell_spheroid";
                }

            };

            // Nell
            template <typename Parameters>
            inline void setup_nell(Parameters& par)
            {
                par.es = 0;
            }

    }} // namespace detail::nell
    #endif // doxygen

    /*!
        \brief Nell projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_nell.gif
    */
    template <typename T, typename Parameters>
    struct nell_spheroid : public detail::nell::base_nell_spheroid<T, Parameters>
    {
        template <typename Params>
        inline nell_spheroid(Params const& , Parameters & par)
        {
            detail::nell::setup_nell(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_nell, nell_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(nell_entry, nell_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(nell_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(nell, nell_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_NELL_HPP


/* nell.hpp
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
*/
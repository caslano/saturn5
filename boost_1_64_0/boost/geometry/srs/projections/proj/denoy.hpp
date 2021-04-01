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

#ifndef BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace denoy
    {

            static const double C0 = 0.95;
            //static const double C1 = -0.08333333333333333333;
            //static const double C3 = 0.00166666666666666666;
            static const double D1 = 0.9;
            static const double D5 = 0.03;

            template <typename T>
            inline T C1() { return -0.0833333333333333333333333333333; }
            template <typename T>
            inline T C3() { return 0.0016666666666666666666666666666; }

            template <typename T, typename Parameters>
            struct base_denoy_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T C1 = denoy::C1<T>();
                    static const T C3 = denoy::C3<T>();

                    xy_y = lp_lat;
                    xy_x = lp_lon;
                    lp_lon = fabs(lp_lon);
                    xy_x *= cos((C0 + lp_lon * (C1 + lp_lon * lp_lon * C3)) *
                        (lp_lat * (D1 + D5 * lp_lat * lp_lat * lp_lat * lp_lat)));
                }

                static inline std::string get_name()
                {
                    return "denoy_spheroid";
                }

            };

            // Denoyer Semi-Elliptical
            template <typename Parameters>
            inline void setup_denoy(Parameters& par)
            {
                par.es = 0.0;
            }

    }} // namespace detail::denoy
    #endif // doxygen

    /*!
        \brief Denoyer Semi-Elliptical projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - no inverse
         - Spheroid
        \par Example
        \image html ex_denoy.gif
    */
    template <typename T, typename Parameters>
    struct denoy_spheroid : public detail::denoy::base_denoy_spheroid<T, Parameters>
    {
        template <typename Params>
        inline denoy_spheroid(Params const& , Parameters & par)
        {
            detail::denoy::setup_denoy(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_denoy, denoy_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(denoy_entry, denoy_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(denoy_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(denoy, denoy_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP


/* denoy.hpp
vkulO0dgRmjB6w+Rl3GywFvcsV9Rvy7B3u516L3rtvlhuCDx+rUT8fljumJZe9dm5r/uulscsjndhzjqttaVKD+5pPF9EqwI21uZx5MjSKB4zYpBvgRbogwPwMHrAbomm1unNAS9AEFuMmO38dScGbA7L8TfR6EmbWkv/DqKYygyX3EGZs/o4DAlvzayODqNpjIPbHgK3tT8SoCc/5bxEGxmEw9bx+G8rJcvrbG5Y1xZ1JKF1Ds1QxTJQoy1+6+Ry4TBRcUtrMKwn4S5QtvA3Xh4tqL3typlKJy/iYT8nVl3g4PTy+nDZlVZxI6pv9hb3SVFZgJXFS+lAGkFJMgUQxyT1BRtqdVoBF6GLHgQc4DutYrzWhsJ2puFc8CqSxGTKU6HoAxiZB740xUXlSed42B8EkoW0lrw2owXLq0mATy0oa0aE61o8veGRl8DJNcDkQQL8zx6DY4kijl2LdreDMGFr0nwMUvZLoZwOcNVdN3erOEcx6kksRpFpekmwi3HEptCGeDhguT7+UiXxStS3ntLkf51WtS08nfsx2XmGw3VxBrL38nw5Z83UA==
*/
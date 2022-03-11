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
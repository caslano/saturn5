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

#ifndef BOOST_GEOMETRY_PROJECTIONS_WAG2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WAG2_HPP

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
    namespace detail { namespace wag2
    {

            static const double C_x = 0.92483;
            static const double C_y = 1.38725;
            static const double C_p1 = 0.88022;
            static const double C_p2 = 0.88550;

            template <typename T, typename Parameters>
            struct base_wag2_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    lp_lat = aasin(C_p1 * sin(C_p2 * lp_lat));
                    xy_x = C_x * lp_lon * cos(lp_lat);
                    xy_y = C_y * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y / C_y;
                    lp_lon = xy_x / (C_x * cos(lp_lat));
                    lp_lat = aasin(sin(lp_lat) / C_p1) / C_p2;
                }

                static inline std::string get_name()
                {
                    return "wag2_spheroid";
                }

            };

            // Wagner II
            template <typename Parameters>
            inline void setup_wag2(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::wag2
    #endif // doxygen

    /*!
        \brief Wagner II projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_wag2.gif
    */
    template <typename T, typename Parameters>
    struct wag2_spheroid : public detail::wag2::base_wag2_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wag2_spheroid(Params const& , Parameters & par)
        {
            detail::wag2::setup_wag2(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wag2, wag2_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wag2_entry, wag2_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(wag2_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wag2, wag2_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_WAG2_HPP


/* wag2.hpp
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
*/
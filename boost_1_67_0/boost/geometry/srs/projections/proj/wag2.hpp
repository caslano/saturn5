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
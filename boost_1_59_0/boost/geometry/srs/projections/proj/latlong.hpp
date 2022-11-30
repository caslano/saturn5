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

// Purpose:  Stub projection implementation for lat/long coordinates. We
//           don't actually change the coordinates, but we want proj=latlong
//           to act sort of like a projection.
// Author:   Frank Warmerdam, warmerdam@pobox.com
// Copyright (c) 2000, Frank Warmerdam

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LATLONG_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LATLONG_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>


namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace latlong
    {

            /* very loosely based upon DMA code by Bradford W. Drew */

            template <typename T, typename Parameters>
            struct base_latlong_other
            {
                // FORWARD(forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    // TODO: in the original code a is not used
                    // different mechanism is probably used instead
                    xy_x = lp_lon / par.a;
                    xy_y = lp_lat / par.a;
                }

                // INVERSE(inverse)
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    // TODO: in the original code a is not used
                    // different mechanism is probably used instead
                    lp_lat = xy_y * par.a;
                    lp_lon = xy_x * par.a;
                }

                static inline std::string get_name()
                {
                    return "latlong_other";
                }

            };

            // Lat/long (Geodetic)
            template <typename Parameters>
            inline void setup_latlong(Parameters& par)
            {
                    par.is_latlong = 1;
                    par.x0 = 0.0;
                    par.y0 = 0.0;
            }

    }} // namespace detail::latlong
    #endif // doxygen

    /*!
        \brief Lat/long (Geodetic) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Example
        \image html ex_latlong.gif
    */
    template <typename T, typename Parameters>
    struct latlong_other : public detail::latlong::base_latlong_other<T, Parameters>
    {
        template <typename Params>
        inline latlong_other(Params const& , Parameters & par)
        {
            detail::latlong::setup_latlong(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_lonlat, latlong_other)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_latlon, latlong_other)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_latlong, latlong_other)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_longlat, latlong_other)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(latlong_entry, latlong_other)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(latlong_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(lonlat, latlong_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(latlon, latlong_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(latlong, latlong_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(longlat, latlong_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LATLONG_HPP


/* latlong.hpp
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
*/
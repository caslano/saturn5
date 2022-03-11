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
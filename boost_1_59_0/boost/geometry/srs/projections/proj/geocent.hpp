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

// Purpose:  Stub projection for geocentric.  The transformation isn't
//           really done here since this code is 2D.  The real transformation
//           is handled by pj_transform.c.
// Author:   Frank Warmerdam, warmerdam@pobox.com
// Copyright (c) 2002, Frank Warmerdam

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace geocent
    {

            template <typename T, typename Parameters>
            struct base_geocent_other
            {
                // FORWARD(forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                        xy_x = lp_lon;
                        xy_y = lp_lat;
                }

                // INVERSE(inverse)
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                        lp_lat = xy_y;
                        lp_lon = xy_x;
                }

                static inline std::string get_name()
                {
                    return "geocent_other";
                }

            };

            // Geocentric
            template <typename Parameters>
            inline void setup_geocent(Parameters& par)
            {
                par.is_geocent = true;
                par.x0 = 0.0;
                par.y0 = 0.0;
            }

    }} // namespace detail::geocent
    #endif // doxygen

    /*!
        \brief Geocentric projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Example
        \image html ex_geocent.gif
    */
    template <typename T, typename Parameters>
    struct geocent_other : public detail::geocent::base_geocent_other<T, Parameters>
    {
        template <typename Params>
        inline geocent_other(Params const& , Parameters & par)
        {
            detail::geocent::setup_geocent(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_geocent, geocent_other)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(geocent_entry, geocent_other)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(geocent_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(geocent, geocent_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP


/* geocent.hpp
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
*/
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
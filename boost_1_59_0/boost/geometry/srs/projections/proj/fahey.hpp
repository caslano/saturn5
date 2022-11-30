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

#ifndef BOOST_GEOMETRY_PROJECTIONS_FAHEY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_FAHEY_HPP

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
    namespace detail { namespace fahey
    {

            static const double tolerance = 1e-6;

            template <typename T, typename Parameters>
            struct base_fahey_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = tan(0.5 * lp_lat);
                    xy_y = 1.819152 * xy_x;
                    xy_x = 0.819152 * lp_lon * asqrt(1 - xy_x * xy_x);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    xy_y /= 1.819152;
                    lp_lat = 2. * atan(xy_y);
                    xy_y = 1. - xy_y * xy_y;
                    lp_lon = fabs(xy_y) < tolerance ? 0. : xy_x / (0.819152 * sqrt(xy_y));
                }

                static inline std::string get_name()
                {
                    return "fahey_spheroid";
                }

            };

            // Fahey
            template <typename Parameters>
            inline void setup_fahey(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::fahey
    #endif // doxygen

    /*!
        \brief Fahey projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_fahey.gif
    */
    template <typename T, typename Parameters>
    struct fahey_spheroid : public detail::fahey::base_fahey_spheroid<T, Parameters>
    {
        template <typename Params>
        inline fahey_spheroid(Params const& , Parameters & par)
        {
            detail::fahey::setup_fahey(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_fahey, fahey_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(fahey_entry, fahey_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(fahey_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(fahey, fahey_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_FAHEY_HPP


/* fahey.hpp
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
*/
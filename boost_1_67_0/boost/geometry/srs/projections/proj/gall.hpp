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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GALL_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GALL_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace gall
    {

            static const double YF = 1.70710678118654752440;
            static const double XF = 0.70710678118654752440;
            static const double RYF = 0.58578643762690495119;
            static const double RXF = 1.41421356237309504880;

            template <typename T, typename Parameters>
            struct base_gall_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = XF * lp_lon;
                    xy_y = YF * tan(.5 * lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lon = RXF * xy_x;
                    lp_lat = 2. * atan(xy_y * RYF);
                }

                static inline std::string get_name()
                {
                    return "gall_spheroid";
                }

            };

            // Gall (Gall Stereographic)
            template <typename Parameters>
            inline void setup_gall(Parameters& par)
            {
                par.es = 0.0;
            }

    }} // namespace detail::gall
    #endif // doxygen

    /*!
        \brief Gall (Gall Stereographic) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_gall.gif
    */
    template <typename T, typename Parameters>
    struct gall_spheroid : public detail::gall::base_gall_spheroid<T, Parameters>
    {
        template <typename Params>
        inline gall_spheroid(Params const& , Parameters & par)
        {
            detail::gall::setup_gall(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_gall, gall_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(gall_entry, gall_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(gall_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(gall, gall_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GALL_HPP


/* gall.hpp
+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
*/
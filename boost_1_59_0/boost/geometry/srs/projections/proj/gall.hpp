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
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
*/
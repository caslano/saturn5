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
FFIaUnZjbaxJqkAsUR2NR0wqNJgpJvgB+qagaLqS2oZ2TxIpgNwQlpBLdEQUxEqt5WG/H2ZpgtH3IxHKfpgv/yBWq2IlHzCIFdmAWCtQAjJJPdCSHqxExJb6ignBwXV2mTAZe2U06IpHfZGCpEmibaEeo9KGTcF36fG0GKwxYqb0RQoutavbWKxqgphHbWWZpRwdYR5QKBKYZg8yHtHUCJuV5y5cTk2Cd0JTxhuB4BgMPB34MPGfwiWRTHrwfrI4nV8s4P3g/HwwW3yA+RsYzD5oY+8msxFCz9BZCvTTOqUSnafAVuuE0cj5fLxPv9N5xniYZBGFpxq9QFKVrQ/ip5WJYz1hsY1fVeRxICKKaOFyUMaYhvrQWib1gRuVyL7+qg8b/yu6EunGBNDfN7WXEKmgkDK17ar4kh4CLqG0gMoRvcyujDqikCGlDM2qdFSYu7C4CRhnqnsjWNTr/NkBaJG2lxMISZKIsIvbVrI/qFh2G7K93hGaYDhj7kAbRJP65ttXK3LFQjQzvDifBm/n81Hgnw7Ox0dVGbmmIVsyBP3zCXRfHh8b4el8+C4YDRYDq4FOjA76Ma5X10HEZUjCmHb3nKFYSGVGenkUAMuUUhfZkRtKEeWUw+xiOrVDXzr6r1PMGPGjDg4903th
*/
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace denoy
    {

            static const double C0 = 0.95;
            //static const double C1 = -0.08333333333333333333;
            //static const double C3 = 0.00166666666666666666;
            static const double D1 = 0.9;
            static const double D5 = 0.03;

            template <typename T>
            inline T C1() { return -0.0833333333333333333333333333333; }
            template <typename T>
            inline T C3() { return 0.0016666666666666666666666666666; }

            template <typename T, typename Parameters>
            struct base_denoy_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T C1 = denoy::C1<T>();
                    static const T C3 = denoy::C3<T>();

                    xy_y = lp_lat;
                    xy_x = lp_lon;
                    lp_lon = fabs(lp_lon);
                    xy_x *= cos((C0 + lp_lon * (C1 + lp_lon * lp_lon * C3)) *
                        (lp_lat * (D1 + D5 * lp_lat * lp_lat * lp_lat * lp_lat)));
                }

                static inline std::string get_name()
                {
                    return "denoy_spheroid";
                }

            };

            // Denoyer Semi-Elliptical
            template <typename Parameters>
            inline void setup_denoy(Parameters& par)
            {
                par.es = 0.0;
            }

    }} // namespace detail::denoy
    #endif // doxygen

    /*!
        \brief Denoyer Semi-Elliptical projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - no inverse
         - Spheroid
        \par Example
        \image html ex_denoy.gif
    */
    template <typename T, typename Parameters>
    struct denoy_spheroid : public detail::denoy::base_denoy_spheroid<T, Parameters>
    {
        template <typename Params>
        inline denoy_spheroid(Params const& , Parameters & par)
        {
            detail::denoy::setup_denoy(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_denoy, denoy_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(denoy_entry, denoy_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(denoy_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(denoy, denoy_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP


/* denoy.hpp
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
*/
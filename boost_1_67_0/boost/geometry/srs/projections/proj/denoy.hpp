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
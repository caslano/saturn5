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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ECK5_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ECK5_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace eck5
    {

            static const double XF  = 0.44101277172455148219;
            static const double RXF = 2.26750802723822639137;
            static const double YF  = 0.88202554344910296438;
            static const double RYF = 1.13375401361911319568;

            template <typename T, typename Parameters>
            struct base_eck5_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = XF * (1. + cos(lp_lat)) * lp_lon;
                    xy_y = YF * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lon = RXF * xy_x / (1. + cos( lp_lat = RYF * xy_y));
                }

                static inline std::string get_name()
                {
                    return "eck5_spheroid";
                }

            };

            // Eckert V
            template <typename Parameters>
            inline void setup_eck5(Parameters& par)
            {
                par.es = 0.0;
            }

    }} // namespace detail::eck5
    #endif // doxygen

    /*!
        \brief Eckert V projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck5.gif
    */
    template <typename T, typename Parameters>
    struct eck5_spheroid : public detail::eck5::base_eck5_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck5_spheroid(Params const& , Parameters & par)
        {
            detail::eck5::setup_eck5(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck5, eck5_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck5_entry, eck5_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eck5_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck5, eck5_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ECK5_HPP


/* eck5.hpp
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
*/
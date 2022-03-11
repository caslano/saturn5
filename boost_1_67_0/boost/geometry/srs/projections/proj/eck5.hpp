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
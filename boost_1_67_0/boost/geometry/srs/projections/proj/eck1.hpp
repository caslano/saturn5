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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ECK1_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ECK1_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace eck1
    {

            static const double FC = .92131773192356127802;
            static const double RP = .31830988618379067154;

            template <typename T, typename Parameters>
            struct base_eck1_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = FC * lp_lon * (1. - RP * fabs(lp_lat));
                    xy_y = FC * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y / FC;
                    lp_lon = xy_x / (FC * (1. - RP * fabs(lp_lat)));
                }

                static inline std::string get_name()
                {
                    return "eck1_spheroid";
                }

            };

            // Eckert I
            template <typename Parameters>
            inline void setup_eck1(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::eck1
    #endif // doxygen

    /*!
        \brief Eckert I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck1.gif
    */
    template <typename T, typename Parameters>
    struct eck1_spheroid : public detail::eck1::base_eck1_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck1_spheroid(Params const& , Parameters & par)
        {
            detail::eck1::setup_eck1(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck1, eck1_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck1_entry, eck1_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eck1_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck1, eck1_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ECK1_HPP


/* eck1.hpp
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
*/
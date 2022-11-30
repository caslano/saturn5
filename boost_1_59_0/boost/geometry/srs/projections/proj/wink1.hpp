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

#ifndef BOOST_GEOMETRY_PROJECTIONS_WINK1_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WINK1_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace wink1
    {

            template <typename T>
            struct par_wink1
            {
                T    cosphi1;
            };

            template <typename T, typename Parameters>
            struct base_wink1_spheroid
            {
                par_wink1<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = .5 * lp_lon * (this->m_proj_parm.cosphi1 + cos(lp_lat));
                    xy_y = lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y;
                    lp_lon = 2. * xy_x / (this->m_proj_parm.cosphi1 + cos(lp_lat));
                }

                static inline std::string get_name()
                {
                    return "wink1_spheroid";
                }

            };

            // Winkel I
            template <typename Params, typename Parameters, typename T>
            inline void setup_wink1(Params const& params, Parameters& par, par_wink1<T>& proj_parm)
            {
                proj_parm.cosphi1 = cos(pj_get_param_r<T, srs::spar::lat_ts>(params, "lat_ts", srs::dpar::lat_ts));
                par.es = 0.;
            }

    }} // namespace detail::wink1
    #endif // doxygen

    /*!
        \brief Winkel I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
        \par Example
        \image html ex_wink1.gif
    */
    template <typename T, typename Parameters>
    struct wink1_spheroid : public detail::wink1::base_wink1_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wink1_spheroid(Params const& params, Parameters & par)
        {
            detail::wink1::setup_wink1(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wink1, wink1_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wink1_entry, wink1_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(wink1_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wink1, wink1_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_WINK1_HPP


/* wink1.hpp
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
*/
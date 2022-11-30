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

#ifndef BOOST_GEOMETRY_PROJECTIONS_WAG3_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WAG3_HPP

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
    namespace detail { namespace wag3
    {
            template <typename T>
            struct par_wag3
            {
                T    C_x;
            };

            template <typename T, typename Parameters>
            struct base_wag3_spheroid
            {
                par_wag3<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T two_thirds = detail::two_thirds<T>();

                    xy_x = this->m_proj_parm.C_x * lp_lon * cos(two_thirds * lp_lat);
                    xy_y = lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T two_thirds = detail::two_thirds<T>();

                    lp_lat = xy_y;
                    lp_lon = xy_x / (this->m_proj_parm.C_x * cos(two_thirds * lp_lat));
                }

                static inline std::string get_name()
                {
                    return "wag3_spheroid";
                }

            };

            // Wagner III
            template <typename Params, typename Parameters, typename T>
            inline void setup_wag3(Params const& params, Parameters& par, par_wag3<T>& proj_parm)
            {
                T const ts = pj_get_param_r<T, srs::spar::lat_ts>(params, "lat_ts", srs::dpar::lat_ts);
                proj_parm.C_x = cos(ts) / cos(2.*ts/3.);
                par.es = 0.;
            }

    }} // namespace detail::wag3
    #endif // doxygen

    /*!
        \brief Wagner III projection
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
        \image html ex_wag3.gif
    */
    template <typename T, typename Parameters>
    struct wag3_spheroid : public detail::wag3::base_wag3_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wag3_spheroid(Params const& params, Parameters & par)
        {
            detail::wag3::setup_wag3(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wag3, wag3_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wag3_entry, wag3_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(wag3_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wag3, wag3_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_WAG3_HPP


/* wag3.hpp
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
*/
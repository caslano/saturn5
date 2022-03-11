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
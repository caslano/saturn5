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

#ifndef BOOST_GEOMETRY_PROJECTIONS_WINK2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WINK2_HPP

#include <boost/geometry/util/math.hpp>

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
    namespace detail { namespace wink2
    {

            static const int max_iter = 10;
            static const double loop_tol = 1e-7;

            template <typename T>
            struct par_wink2
            {
                T    cosphi1;
            };

            template <typename T, typename Parameters>
            struct base_wink2_spheroid
            {
                par_wink2<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T pi = detail::pi<T>();
                    static const T half_pi = detail::half_pi<T>();
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T two_div_pi = detail::two_div_pi<T>();

                    T k, V;
                    int i;

                    xy_y = lp_lat * two_div_pi;
                    k = pi * sin(lp_lat);
                    lp_lat *= 1.8;
                    for (i = max_iter; i ; --i) {
                        lp_lat -= V = (lp_lat + sin(lp_lat) - k) /
                            (1. + cos(lp_lat));
                        if (fabs(V) < loop_tol)
                            break;
                    }
                    if (!i)
                        lp_lat = (lp_lat < 0.) ? -half_pi : half_pi;
                    else
                        lp_lat *= 0.5;
                    xy_x = 0.5 * lp_lon * (cos(lp_lat) + this->m_proj_parm.cosphi1);
                    xy_y = fourth_pi * (sin(lp_lat) + xy_y);
                }

                static inline std::string get_name()
                {
                    return "wink2_spheroid";
                }

            };

            // Winkel II
            template <typename Params, typename Parameters, typename T>
            inline void setup_wink2(Params const& params, Parameters& par, par_wink2<T>& proj_parm)
            {
                proj_parm.cosphi1 = cos(pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1));
                par.es = 0.;
            }

    }} // namespace detail::wink2
    #endif // doxygen

    /*!
        \brief Winkel II projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
         - no inverse
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
        \par Example
        \image html ex_wink2.gif
    */
    template <typename T, typename Parameters>
    struct wink2_spheroid : public detail::wink2::base_wink2_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wink2_spheroid(Params const& params, Parameters & par)
        {
            detail::wink2::setup_wink2(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_wink2, wink2_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(wink2_entry, wink2_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(wink2_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wink2, wink2_entry)
        }
        
    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_WINK2_HPP


/* wink2.hpp
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
*/
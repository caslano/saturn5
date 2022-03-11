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
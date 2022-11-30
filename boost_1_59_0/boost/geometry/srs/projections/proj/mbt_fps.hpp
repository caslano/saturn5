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

#ifndef BOOST_GEOMETRY_PROJECTIONS_MBT_FPS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MBT_FPS_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/aasincos.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace mbt_fps
    {

            static const int max_iter = 10;
            static const double loop_tol = 1e-7;
            static const double C1 = 0.45503;
            static const double C2 = 1.36509;
            static const double C3 = 1.41546;
            static const double C_x = 0.22248;
            static const double C_y = 1.44492;
            //static const double C1_2 = 0.33333333333333333333333333;

            template <typename T>
            inline T C1_2() { return detail::third<T>(); }

            template <typename T, typename Parameters>
            struct base_mbt_fps_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T C1_2 = mbt_fps::C1_2<T>();

                    T k, V, t;
                    int i;

                    k = C3 * sin(lp_lat);
                    for (i = max_iter; i ; --i) {
                        t = lp_lat / C2;
                        lp_lat -= V = (C1 * sin(t) + sin(lp_lat) - k) /
                            (C1_2 * cos(t) + cos(lp_lat));
                        if (fabs(V) < loop_tol)
                            break;
                    }
                    t = lp_lat / C2;
                    xy_x = C_x * lp_lon * (1. + 3. * cos(lp_lat)/cos(t) );
                    xy_y = C_y * sin(t);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const&, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T t;

                    lp_lat = C2 * (t = aasin(xy_y / C_y));
                    lp_lon = xy_x / (C_x * (1. + 3. * cos(lp_lat)/cos(t)));
                    lp_lat = aasin((C1 * sin(t) + sin(lp_lat)) / C3);
                }

                static inline std::string get_name()
                {
                    return "mbt_fps_spheroid";
                }

            };

            // McBryde-Thomas Flat-Pole Sine (No. 2)
            template <typename Parameters>
            inline void setup_mbt_fps(Parameters& par)
            {
                par.es = 0;
            }

    }} // namespace detail::mbt_fps
    #endif // doxygen

    /*!
        \brief McBryde-Thomas Flat-Pole Sine (No. 2) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_mbt_fps.gif
    */
    template <typename T, typename Parameters>
    struct mbt_fps_spheroid : public detail::mbt_fps::base_mbt_fps_spheroid<T, Parameters>
    {
        template <typename Params>
        inline mbt_fps_spheroid(Params const& , Parameters & par)
        {
            detail::mbt_fps::setup_mbt_fps(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mbt_fps, mbt_fps_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mbt_fps_entry, mbt_fps_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(mbt_fps_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mbt_fps, mbt_fps_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MBT_FPS_HPP


/* mbt_fps.hpp
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
*/
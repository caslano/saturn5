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

#ifndef BOOST_GEOMETRY_PROJECTIONS_NELL_H_HPP
#define BOOST_GEOMETRY_PROJECTIONS_NELL_H_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace nell_h
    {

            static const int n_iter = 9;
            static const double epsilon = 1e-7;

            template <typename T, typename Parameters>
            struct base_nell_h_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = 0.5 * lp_lon * (1. + cos(lp_lat));
                    xy_y = 2.0 * (lp_lat - tan(0.5 *lp_lat));
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T V, c, p;
                    int i;

                    p = 0.5 * xy_y;
                    for (i = n_iter; i ; --i) {
                        c = cos(0.5 * lp_lat);
                        lp_lat -= V = (lp_lat - tan(lp_lat/2) - p)/(1. - 0.5/(c*c));
                        if (fabs(V) < epsilon)
                            break;
                    }
                    if (!i) {
                        lp_lat = p < 0. ? -half_pi : half_pi;
                        lp_lon = 2. * xy_x;
                    } else
                        lp_lon = 2. * xy_x / (1. + cos(lp_lat));
                }

                static inline std::string get_name()
                {
                    return "nell_h_spheroid";
                }

            };

            // Nell-Hammer
            template <typename Parameters>
            inline void setup_nell_h(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::nell_h
    #endif // doxygen

    /*!
        \brief Nell-Hammer projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_nell_h.gif
    */
    template <typename T, typename Parameters>
    struct nell_h_spheroid : public detail::nell_h::base_nell_h_spheroid<T, Parameters>
    {
        template <typename Params>
        inline nell_h_spheroid(Params const& , Parameters & par)
        {
            detail::nell_h::setup_nell_h(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_nell_h, nell_h_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(nell_h_entry, nell_h_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(nell_h_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(nell_h, nell_h_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_NELL_H_HPP


/* nell_h.hpp
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
*/
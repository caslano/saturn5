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

#ifndef BOOST_GEOMETRY_PROJECTIONS_AUGUST_HPP
#define BOOST_GEOMETRY_PROJECTIONS_AUGUST_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace august
    {

            //static const double M = 1.333333333333333;

            template <typename T, typename Parameters>
            struct base_august_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T M = 1.333333333333333333333333333333333333;

                    T t, c1, c, x1, x12, y1, y12;

                    t = tan(.5 * lp_lat);
                    c1 = sqrt(1. - t * t);
                    c = 1. + c1 * cos(lp_lon *= .5);
                    x1 = sin(lp_lon) *  c1 / c;
                    y1 =  t / c;
                    xy_x = M * x1 * (3. + (x12 = x1 * x1) - 3. * (y12 = y1 *  y1));
                    xy_y = M * y1 * (3. + 3. * x12 - y12);
                }

                static inline std::string get_name()
                {
                    return "august_spheroid";
                }

            };

            // August Epicycloidal
            template <typename Parameters>
            inline void setup_august(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::august
    #endif // doxygen

    /*!
        \brief August Epicycloidal projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_august.gif
    */
    template <typename T, typename Parameters>
    struct august_spheroid : public detail::august::base_august_spheroid<T, Parameters>
    {
        template <typename Params>
        inline august_spheroid(Params const& , Parameters & par)
        {
            detail::august::setup_august(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_august, august_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(august_entry, august_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(august_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(august, august_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_AUGUST_HPP


/* august.hpp
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
*/
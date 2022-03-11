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
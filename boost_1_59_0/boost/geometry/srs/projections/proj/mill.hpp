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

#ifndef BOOST_GEOMETRY_PROJECTIONS_MILL_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MILL_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace mill
    {
            template <typename T, typename Parameters>
            struct base_mill_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    xy_x = lp_lon;
                    xy_y = log(tan(fourth_pi + lp_lat * .4)) * 1.25;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    lp_lon = xy_x;
                    lp_lat = 2.5 * (atan(exp(.8 * xy_y)) - fourth_pi);
                }

                static inline std::string get_name()
                {
                    return "mill_spheroid";
                }

            };

            // Miller Cylindrical
            template <typename Parameters>
            inline void setup_mill(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::mill
    #endif // doxygen

    /*!
        \brief Miller Cylindrical projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_mill.gif
    */
    template <typename T, typename Parameters>
    struct mill_spheroid : public detail::mill::base_mill_spheroid<T, Parameters>
    {
        template <typename Params>
        inline mill_spheroid(Params const& , Parameters & par)
        {
            detail::mill::setup_mill(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mill, mill_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mill_entry, mill_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(mill_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mill, mill_entry)
        }
        
    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MILL_HPP


/* mill.hpp
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
*/
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
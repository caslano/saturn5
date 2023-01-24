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
F7Oj/v37NJ1FR3e7Jqay5vdoKxKpK7qgXqm5cfuFKrm5Zjo4rVyfm739IqE75+PNqOzDOryurrlGFR9ANRdXcjNi+aWz49qlpFAwq+R4mf7O96u1GEfJzUfSfK2zuviVD7fHIbPAXmUVb+VUrubMe0gFF8OsR7OfUKUL2VAA9UGhqGYMqC2m98fCnosTIseazeSl+WpWbcn6A9hKEJq00Ckvyvcpc95ssQBVbd187i+SRh/dMRCzjbnMKUhtaq6PKie0l1u0b6atsY2oeoK59oh+cfT85trLXJeI0mazE1uiotv250qyT30GVJY+cmOmeNdVwS66vnbX1L8qXkbky6/w3LYKY2m12SkuuyXnp/eip8BLFbxzUmr9tBKyTuzqq9cCZsQ3/ngAYlSrjcwznhOabB3t2/4oaJFvqPoAFMxUcutsMg0lthZobdu1HG3dlJj60HT3MHDkz8VJ5l9Ybbd6HyKPe2C331JhyyzWGQKUBWgVK7rmNVudjtL88YWpbp0/1MhdnmvBeNFAZeIVmF6AjpVqCQ+ntoxBLi1mmXipMtlqEs9L5a9gvYtjeW6bgWNvTdmuDcxT7obR0UjljdjtYWOxPOMNSKer1uP2+9aqSc23XHqzk6eAsuo1AfdtUGGXeIk01E4DYOEaZ+9mYBVZ6cP1DrXvMbNMzQ570T2sbnj9NgRfcxvtBLBJfZlQFy5xe0AQ3raIF16L
*/
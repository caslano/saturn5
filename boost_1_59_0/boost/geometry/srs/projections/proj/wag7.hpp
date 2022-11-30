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

#ifndef BOOST_GEOMETRY_PROJECTIONS_WAG7_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WAG7_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace wag7
    {

            template <typename T, typename Parameters>
            struct base_wag7_spheroid
            {
                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T theta, ct, D;

                    theta = asin(xy_y = 0.90630778703664996 * sin(lp_lat));
                    xy_x = 2.66723 * (ct = cos(theta)) * sin(lp_lon /= 3.);
                    xy_y *= 1.24104 * (D = 1/(sqrt(0.5 * (1 + ct * cos(lp_lon)))));
                    xy_x *= D;
                }

                static inline std::string get_name()
                {
                    return "wag7_spheroid";
                }

            };

            // Wagner VII
            template <typename Parameters>
            inline void setup_wag7(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::wag7
    #endif // doxygen

    /*!
        \brief Wagner VII projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_wag7.gif
    */
    template <typename T, typename Parameters>
    struct wag7_spheroid : public detail::wag7::base_wag7_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wag7_spheroid(Params const& , Parameters & par)
        {
            detail::wag7::setup_wag7(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_wag7, wag7_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(wag7_entry, wag7_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(wag7_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wag7, wag7_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_WAG7_HPP


/* wag7.hpp
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
*/
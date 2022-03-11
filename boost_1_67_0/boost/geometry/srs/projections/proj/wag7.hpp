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
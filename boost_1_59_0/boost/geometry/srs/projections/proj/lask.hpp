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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LASK_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LASK_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace lask
    {

            static const double a10 = 0.975534;
            static const double a12 = -0.119161;
            static const double a32 = -0.0143059;
            static const double a14 = -0.0547009;
            static const double b01 = 1.00384;
            static const double b21 = 0.0802894;
            static const double b03 = 0.0998909;
            static const double b41 = 0.000199025;
            static const double b23 = -0.0285500;
            static const double b05 = -0.0491032;

            template <typename T, typename Parameters>
            struct base_lask_spheroid
            {
                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T l2, p2;

                    l2 = lp_lon * lp_lon;
                    p2 = lp_lat * lp_lat;
                    xy_x = lp_lon * (a10 + p2 * (a12 + l2 * a32 + p2 * a14));
                    xy_y = lp_lat * (b01 + l2 * (b21 + p2 * b23 + l2 * b41) +
                               p2 * (b03 + p2 * b05));
                }

                static inline std::string get_name()
                {
                    return "lask_spheroid";
                }

            };

            // Laskowski
            template <typename Parameters>
            inline void setup_lask(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::lask
    #endif // doxygen

    /*!
        \brief Laskowski projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_lask.gif
    */
    template <typename T, typename Parameters>
    struct lask_spheroid : public detail::lask::base_lask_spheroid<T, Parameters>
    {
        template <typename Params>
        inline lask_spheroid(Params const& , Parameters & par)
        {
            detail::lask::setup_lask(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_lask, lask_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(lask_entry, lask_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(lask_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(lask, lask_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LASK_HPP


/* lask.hpp
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
*/
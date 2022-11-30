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

#ifndef BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace crast
    {

            static const double XM = 0.97720502380583984317;
            static const double RXM = 1.02332670794648848847;
            static const double YM = 3.06998012383946546542;
            static const double RYM = 0.32573500793527994772;
            //static const double third = 0.333333333333333333;

            template <typename T, typename Parameters>
            struct base_crast_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T third = detail::third<T>();

                    lp_lat *= third;
                    xy_x = XM * lp_lon * (2. * cos(lp_lat + lp_lat) - 1.);
                    xy_y = YM * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T third = detail::third<T>();

                    lp_lat = 3. * asin(xy_y * RYM);
                    lp_lon = xy_x * RXM / (2. * cos((lp_lat + lp_lat) * third) - 1);
                }

                static inline std::string get_name()
                {
                    return "crast_spheroid";
                }

            };

            // Craster Parabolic (Putnins P4)
            template <typename Parameters>
            inline void setup_crast(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::crast
    #endif // doxygen

    /*!
        \brief Craster Parabolic (Putnins P4) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_crast.gif
    */
    template <typename T, typename Parameters>
    struct crast_spheroid : public detail::crast::base_crast_spheroid<T, Parameters>
    {
        template <typename Params>
        inline crast_spheroid(Params const& , Parameters & par)
        {
            detail::crast::setup_crast(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_crast, crast_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(crast_entry, crast_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(crast_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(crast, crast_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP


/* crast.hpp
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
*/
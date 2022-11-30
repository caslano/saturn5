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

#ifndef BOOST_GEOMETRY_PROJECTIONS_TCEA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_TCEA_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace tcea
    {
            template <typename T, typename Parameters>
            struct base_tcea_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = cos(lp_lat) * sin(lp_lon) / par.k0;
                    xy_y = par.k0 * (atan2(tan(lp_lat), cos(lp_lon)) - par.phi0);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T t;

                    xy_y = xy_y / par.k0 + par.phi0;
                    xy_x *= par.k0;
                    t = sqrt(1. - xy_x * xy_x);
                    lp_lat = asin(t * sin(xy_y));
                    lp_lon = atan2(xy_x, t * cos(xy_y));
                }

                static inline std::string get_name()
                {
                    return "tcea_spheroid";
                }

            };

            // Transverse Cylindrical Equal Area
            template <typename Parameters>
            inline void setup_tcea(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::tcea
    #endif // doxygen
    
    /*!
        \brief Transverse Cylindrical Equal Area projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_tcea.gif
    */
    template <typename T, typename Parameters>
    struct tcea_spheroid : public detail::tcea::base_tcea_spheroid<T, Parameters>
    {
        template <typename Params>
        inline tcea_spheroid(Params const& , Parameters & par)
        {
            detail::tcea::setup_tcea(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_tcea, tcea_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(tcea_entry, tcea_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(tcea_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(tcea, tcea_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_TCEA_HPP


/* tcea.hpp
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
*/
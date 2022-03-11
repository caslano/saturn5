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
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
DPonH90lyWYvEZuqIBfjCOPYr47hHFEe31LEMCkivMDDX5f9ehii+Dt8q2GKrAkrrhQyT/x6ob27gGekai/NGxVLkAHcKmBuT8NbRSdxrI7D312WAC2E6L4x+DDvwmPbsDAYz2sIt7OqltLRv3Z3OD/yBbqCclw6iDwVIpEncz9QIXloa/OOqAFwSRe6Tg5A7655mNpiv7rGUPv4O2Gs3bFg4I9+ibQc+iyVEWzMwYSxMpmP/tPQH7D4eziLVtSdOiv2KyQqVSwBIeH8rOmBLJTutzDaLgOagmk+KD7lf73dlbQfy8++wy9K+dZtL1VYpLE4ji7Z8PBftuQI3A0vmeGwb/RG2xYl4/vjkQ2M/oNNCSTaTpXE/kcKcl82EDN4kj/ToMgMIg4OIIyG7N9psWmbxzE3wxJCYXcn8dxdIgfVjQ92Q/5j6yf6r9jYkWT8HnN5OoHOLh3QG119kBLd+l3y6RbAu7tCMiyh2g5j3kHs70X/liSFtmevdX+Yjq2EgWPK5klj4W7PvPtEwNXzDzhvEZd/T1MoLnd6qJO0/X5HYZgwey3wg2j4Cg==
*/
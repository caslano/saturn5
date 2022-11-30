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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LARR_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LARR_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace larr
    {

            template <typename T, typename Parameters>
            struct base_larr_spheroid
            {
                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T sixth = detail::sixth<T>();

                    xy_x = 0.5 * lp_lon * (1. + sqrt(cos(lp_lat)));
                    xy_y = lp_lat / (cos(0.5 * lp_lat) * cos(sixth * lp_lon));
                }

                static inline std::string get_name()
                {
                    return "larr_spheroid";
                }

            };

            // Larrivee
            template <typename Parameters>
            inline void setup_larr(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::larr
    #endif // doxygen

    /*!
        \brief Larrivee projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_larr.gif
    */
    template <typename T, typename Parameters>
    struct larr_spheroid : public detail::larr::base_larr_spheroid<T, Parameters>
    {
        template <typename Params>
        inline larr_spheroid(Params const& , Parameters & par)
        {
            detail::larr::setup_larr(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_larr, larr_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(larr_entry, larr_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(larr_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(larr, larr_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LARR_HPP


/* larr.hpp
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
*/
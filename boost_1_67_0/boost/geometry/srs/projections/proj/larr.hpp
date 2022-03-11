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
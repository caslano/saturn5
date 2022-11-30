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

#ifndef BOOST_GEOMETRY_PROJECTIONS_COLLG_HPP
#define BOOST_GEOMETRY_PROJECTIONS_COLLG_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace collg
    {

            static const double FXC = 1.12837916709551257390;
            static const double FYC = 1.77245385090551602729;
            static const double one_plus_eps = 1.0000001;

            template <typename T, typename Parameters>
            struct base_collg_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    if ((xy_y = 1. - sin(lp_lat)) <= 0.)
                        xy_y = 0.;
                    else
                        xy_y = sqrt(xy_y);
                    xy_x = FXC * lp_lon * xy_y;
                    xy_y = FYC * (1. - xy_y);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static T const half_pi = detail::half_pi<T>();

                    lp_lat = xy_y / FYC - 1.;
                    if (fabs(lp_lat = 1. - lp_lat * lp_lat) < 1.)
                        lp_lat = asin(lp_lat);
                    else if (fabs(lp_lat) > one_plus_eps) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    } else {
                        lp_lat = lp_lat < 0. ? -half_pi : half_pi;
                    }

                    if ((lp_lon = 1. - sin(lp_lat)) <= 0.)
                        lp_lon = 0.;
                    else
                        lp_lon = xy_x / (FXC * sqrt(lp_lon));
                }

                static inline std::string get_name()
                {
                    return "collg_spheroid";
                }

            };

            // Collignon
            template <typename Parameters>
            inline void setup_collg(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace collg
    #endif // doxygen

    /*!
        \brief Collignon projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_collg.gif
    */
    template <typename T, typename Parameters>
    struct collg_spheroid : public detail::collg::base_collg_spheroid<T, Parameters>
    {
        template <typename Params>
        inline collg_spheroid(Params const& , Parameters & par)
        {
            detail::collg::setup_collg(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_collg, collg_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(collg_entry, collg_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(collg_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(collg, collg_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_COLLG_HPP


/* collg.hpp
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
*/
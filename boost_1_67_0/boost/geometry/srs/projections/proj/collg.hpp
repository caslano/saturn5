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
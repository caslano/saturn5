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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ECK2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ECK2_HPP

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
    namespace detail { namespace eck2
    {

            static const double FXC = 0.46065886596178063902;
            static const double FYC = 1.44720250911653531871;
            //static const double C13 = 0.33333333333333333333;
            static const double one_plus_eps = 1.0000001;

            template <typename T, typename Parameters>
            struct base_eck2_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = FXC * lp_lon * (xy_y = sqrt(4. - 3. * sin(fabs(lp_lat))));
                    xy_y = FYC * (2. - xy_y);
                    if ( lp_lat < 0.) xy_y = -xy_y;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T C13 = detail::third<T>();

                    lp_lon = xy_x / (FXC * ( lp_lat = 2. - fabs(xy_y) / FYC) );
                    lp_lat = (4. - lp_lat * lp_lat) * C13;
                    if (fabs(lp_lat) >= 1.) {
                        if (fabs(lp_lat) > one_plus_eps)
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        else
                            lp_lat = lp_lat < 0. ? -half_pi : half_pi;
                    } else
                        lp_lat = asin(lp_lat);
                    if (xy_y < 0)
                        lp_lat = -lp_lat;
                }

                static inline std::string get_name()
                {
                    return "eck2_spheroid";
                }

            };

            // Eckert II
            template <typename Parameters>
            inline void setup_eck2(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::eck2
    #endif // doxygen

    /*!
        \brief Eckert II projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck2.gif
    */
    template <typename T, typename Parameters>
    struct eck2_spheroid : public detail::eck2::base_eck2_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck2_spheroid(Params const& , Parameters & par)
        {
            detail::eck2::setup_eck2(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck2, eck2_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck2_entry, eck2_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eck2_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck2, eck2_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ECK2_HPP


/* eck2.hpp
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
*/
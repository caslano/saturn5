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
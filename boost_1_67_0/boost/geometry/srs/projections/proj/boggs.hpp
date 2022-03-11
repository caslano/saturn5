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

#ifndef BOOST_GEOMETRY_PROJECTIONS_BOGGS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_BOGGS_HPP

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
    namespace detail { namespace boggs
    {

            static const int n_iter = 20;
            static const double epsilon = 1e-7;
            static const double FXC = 2.00276;
            static const double FXC2 = 1.11072;
            static const double FYC = 0.49931;

            template <typename T, typename Parameters>
            struct base_boggs_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T pi = detail::pi<T>();
                    static const T root_two = boost::math::constants::root_two<T>();

                    T theta, th1, c;
                    int i;

                    theta = lp_lat;
                    if (fabs(fabs(lp_lat) - half_pi) < epsilon)
                        xy_x = 0.;
                    else {
                        c = sin(theta) * pi;
                        for (i = n_iter; i; --i) {
                            theta -= th1 = (theta + sin(theta) - c) /
                                (1. + cos(theta));
                            if (fabs(th1) < epsilon) break;
                        }
                        theta *= 0.5;
                        xy_x = FXC * lp_lon / (1. / cos(lp_lat) + FXC2 / cos(theta));
                    }
                    xy_y = FYC * (lp_lat + root_two * sin(theta));
                }

                static inline std::string get_name()
                {
                    return "boggs_spheroid";
                }

            };

            // Boggs Eumorphic
            template <typename Parameters>
            inline void setup_boggs(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::boggs
    #endif // doxygen

    /*!
        \brief Boggs Eumorphic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - no inverse
         - Spheroid
        \par Example
        \image html ex_boggs.gif
    */
    template <typename T, typename Parameters>
    struct boggs_spheroid : public detail::boggs::base_boggs_spheroid<T, Parameters>
    {
        template <typename Params>
        inline boggs_spheroid(Params const& , Parameters & par)
        {
            detail::boggs::setup_boggs(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_boggs, boggs_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(boggs_entry, boggs_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(boggs_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(boggs, boggs_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_BOGGS_HPP


/* boggs.hpp
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
*/
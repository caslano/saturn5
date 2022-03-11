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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PUTP2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PUTP2_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/aasincos.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace putp2
    {

            static const double C_x = 1.89490;
            static const double C_y = 1.71848;
            static const double C_p = 0.6141848493043784;
            static const double epsilon = 1e-10;
            static const int n_iter = 10;
            //static const double third_pi = 1.0471975511965977;

            template <typename T, typename Parameters>
            struct base_putp2_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T third_pi = detail::third_pi<T>();

                    T p, c, s, V;
                    int i;

                    p = C_p * sin(lp_lat);
                    s = lp_lat * lp_lat;
                    lp_lat *= 0.615709 + s * ( 0.00909953 + s * 0.0046292 );
                    for (i = n_iter; i ; --i) {
                        c = cos(lp_lat);
                        s = sin(lp_lat);
                        lp_lat -= V = (lp_lat + s * (c - 1.) - p) /
                            (1. + c * (c - 1.) - s * s);
                        if (fabs(V) < epsilon)
                            break;
                    }
                    if (!i)
                        lp_lat = lp_lat < 0 ? - third_pi : third_pi;
                    xy_x = C_x * lp_lon * (cos(lp_lat) - 0.5);
                    xy_y = C_y * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T c;

                    lp_lat = aasin(xy_y / C_y);
                    lp_lon = xy_x / (C_x * ((c = cos(lp_lat)) - 0.5));
                    lp_lat = aasin((lp_lat + sin(lp_lat) * (c - 1.)) / C_p);
                }

                static inline std::string get_name()
                {
                    return "putp2_spheroid";
                }

            };

            // Putnins P2
            template <typename Parameters>
            inline void setup_putp2(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::putp2
    #endif // doxygen

    /*!
        \brief Putnins P2 projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp2.gif
    */
    template <typename T, typename Parameters>
    struct putp2_spheroid : public detail::putp2::base_putp2_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp2_spheroid(Params const& , Parameters & par)
        {
            detail::putp2::setup_putp2(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp2, putp2_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp2_entry, putp2_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(putp2_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp2, putp2_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_PUTP2_HPP


/* putp2.hpp
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
*/
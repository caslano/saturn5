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

// The Natural Earth projection was designed by Tom Patterson, US National Park
// Service, in 2007, using Flex Projector. The shape of the original projection
// was defined at every 5 degrees and piece-wise cubic spline interpolation was
// used to compute the complete graticule.
// The code here uses polynomial functions instead of cubic splines and
// is therefore much simpler to program. The polynomial approximation was
// developed by Bojan Savric, in collaboration with Tom Patterson and Bernhard
// Jenny, Institute of Cartography, ETH Zurich. It slightly deviates from
// Patterson's original projection by adding additional curvature to meridians
// where they meet the horizontal pole line. This improvement is by intention
// and designed in collaboration with Tom Patterson.
// Port to PROJ.4 by Bernhard Jenny, 6 June 2011

#ifndef BOOST_GEOMETRY_PROJECTIONS_NATEARTH_HPP
#define BOOST_GEOMETRY_PROJECTIONS_NATEARTH_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace natearth
    {

            static const double A0 = 0.8707;
            static const double A1 = -0.131979;
            static const double A2 = -0.013791;
            static const double A3 = 0.003971;
            static const double A4 = -0.001529;
            static const double B0 = 1.007226;
            static const double B1 = 0.015085;
            static const double B2 = -0.044475;
            static const double B3 = 0.028874;
            static const double B4 = -0.005916;
            static const double C0 = B0;
            static const double C1 = (3 * B1);
            static const double C2 = (7 * B2);
            static const double C3 = (9 * B3);
            static const double C4 = (11 * B4);
            static const double epsilon = 1e-11;

            template <typename T>
            inline T max_y() { return (0.8707 * 0.52 * detail::pi<T>()); }

            /* Not sure at all of the appropriate number for max_iter... */
            static const int max_iter = 100;

            template <typename T, typename Parameters>
            struct base_natearth_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T phi2, phi4;

                    phi2 = lp_lat * lp_lat;
                    phi4 = phi2 * phi2;
                    xy_x = lp_lon * (A0 + phi2 * (A1 + phi2 * (A2 + phi4 * phi2 * (A3 + phi2 * A4))));
                    xy_y = lp_lat * (B0 + phi2 * (B1 + phi4 * (B2 + B3 * phi2 + B4 * phi4)));
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T max_y = natearth::max_y<T>();

                    T yc, tol, y2, y4, f, fder;
                    int i;

                    /* make sure y is inside valid range */
                    if (xy_y > max_y) {
                        xy_y = max_y;
                    } else if (xy_y < -max_y) {
                        xy_y = -max_y;
                    }

                    /* latitude */
                    yc = xy_y;
                    for (i = max_iter; i ; --i) { /* Newton-Raphson */
                        y2 = yc * yc;
                        y4 = y2 * y2;
                        f = (yc * (B0 + y2 * (B1 + y4 * (B2 + B3 * y2 + B4 * y4)))) - xy_y;
                        fder = C0 + y2 * (C1 + y4 * (C2 + C3 * y2 + C4 * y4));
                        yc -= tol = f / fder;
                        if (fabs(tol) < epsilon) {
                            break;
                        }
                    }
                    if( i == 0 )
                        BOOST_THROW_EXCEPTION( projection_exception(error_non_convergent) );
                    lp_lat = yc;

                    /* longitude */
                    y2 = yc * yc;
                    lp_lon = xy_x / (A0 + y2 * (A1 + y2 * (A2 + y2 * y2 * y2 * (A3 + y2 * A4))));
                }

                static inline std::string get_name()
                {
                    return "natearth_spheroid";
                }

            };

            // Natural Earth
            template <typename Parameters>
            inline void setup_natearth(Parameters& par)
            {
                par.es = 0;
            }

    }} // namespace detail::natearth
    #endif // doxygen

    /*!
        \brief Natural Earth projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_natearth.gif
    */
    template <typename T, typename Parameters>
    struct natearth_spheroid : public detail::natearth::base_natearth_spheroid<T, Parameters>
    {
        template <typename Params>
        inline natearth_spheroid(Params const& , Parameters & par)
        {
            detail::natearth::setup_natearth(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_natearth, natearth_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(natearth_entry, natearth_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(natearth_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(natearth, natearth_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_NATEARTH_HPP


/* natearth.hpp
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
*/
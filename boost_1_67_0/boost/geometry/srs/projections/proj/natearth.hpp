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
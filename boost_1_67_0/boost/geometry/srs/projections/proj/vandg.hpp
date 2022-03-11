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

#ifndef BOOST_GEOMETRY_PROJECTIONS_VANDG_HPP
#define BOOST_GEOMETRY_PROJECTIONS_VANDG_HPP

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
    namespace detail { namespace vandg
    {

            static const double tolerance = 1.e-10;

            template <typename T>
            inline T C2_27() { return .07407407407407407407407407407407; }
            template <typename T>
            inline T PI4_3() { return boost::math::constants::four_thirds_pi<T>(); }
            template <typename T>
            inline T TPISQ() { return 19.739208802178717237668981999752; }
            template <typename T>
            inline T HPISQ() { return 4.9348022005446793094172454999381; }

            template <typename T, typename Parameters>
            struct base_vandg_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T pi = detail::pi<T>();

                    T  al, al2, g, g2, p2;

                    p2 = fabs(lp_lat / half_pi);
                    if ((p2 - tolerance) > 1.) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    if (p2 > 1.)
                        p2 = 1.;
                    if (fabs(lp_lat) <= tolerance) {
                        xy_x = lp_lon;
                        xy_y = 0.;
                    } else if (fabs(lp_lon) <= tolerance || fabs(p2 - 1.) < tolerance) {
                        xy_x = 0.;
                        xy_y = pi * tan(.5 * asin(p2));
                        if (lp_lat < 0.) xy_y = -xy_y;
                    } else {
                        al = .5 * fabs(pi / lp_lon - lp_lon / pi);
                        al2 = al * al;
                        g = sqrt(1. - p2 * p2);
                        g = g / (p2 + g - 1.);
                        g2 = g * g;
                        p2 = g * (2. / p2 - 1.);
                        p2 = p2 * p2;
                        xy_x = g - p2; g = p2 + al2;
                        xy_x = pi * (al * xy_x + sqrt(al2 * xy_x * xy_x - g * (g2 - p2))) / g;
                        if (lp_lon < 0.) xy_x = -xy_x;
                        xy_y = fabs(xy_x / pi);
                        xy_y = 1. - xy_y * (xy_y + 2. * al);
                        if (xy_y < -tolerance) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        if (xy_y < 0.)
                            xy_y = 0.;
                        else
                            xy_y = sqrt(xy_y) * (lp_lat < 0. ? -pi : pi);
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T pi = detail::pi<T>();
                    static const T pi_sqr = detail::pi_sqr<T>();
                    static const T third = detail::third<T>();
                    static const T two_pi = detail::two_pi<T>();

                    static const T C2_27 = vandg::C2_27<T>();
                    static const T PI4_3 = vandg::PI4_3<T>();                    
                    static const T TPISQ = vandg::TPISQ<T>();
                    static const T HPISQ = vandg::HPISQ<T>();
                    
                    T t, c0, c1, c2, c3, al, r2, r, m, d, ay, x2, y2;

                    x2 = xy_x * xy_x;
                    if ((ay = fabs(xy_y)) < tolerance) {
                        lp_lat = 0.;
                        t = x2 * x2 + TPISQ * (x2 + HPISQ);
                        lp_lon = fabs(xy_x) <= tolerance ? 0. :
                           .5 * (x2 - pi_sqr + sqrt(t)) / xy_x;
                            return;
                    }
                    y2 = xy_y * xy_y;
                    r = x2 + y2;    r2 = r * r;
                    c1 = - pi * ay * (r + pi_sqr);
                    c3 = r2 + two_pi * (ay * r + pi * (y2 + pi * (ay + half_pi)));
                    c2 = c1 + pi_sqr * (r - 3. *  y2);
                    c0 = pi * ay;
                    c2 /= c3;
                    al = c1 / c3 - third * c2 * c2;
                    m = 2. * sqrt(-third * al);
                    d = C2_27 * c2 * c2 * c2 + (c0 * c0 - third * c2 * c1) / c3;
                    if (((t = fabs(d = 3. * d / (al * m))) - tolerance) <= 1.) {
                        d = t > 1. ? (d > 0. ? 0. : pi) : acos(d);
                        lp_lat = pi * (m * cos(d * third + PI4_3) - third * c2);
                        if (xy_y < 0.) lp_lat = -lp_lat;
                        t = r2 + TPISQ * (x2 - y2 + HPISQ);
                        lp_lon = fabs(xy_x) <= tolerance ? 0. :
                           .5 * (r - pi_sqr + (t <= 0. ? 0. : sqrt(t))) / xy_x;
                    } else {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                }

                static inline std::string get_name()
                {
                    return "vandg_spheroid";
                }

            };

            // van der Grinten (I)
            template <typename Parameters>
            inline void setup_vandg(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::vandg
    #endif // doxygen

    /*!
        \brief van der Grinten (I) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
        \par Example
        \image html ex_vandg.gif
    */
    template <typename T, typename Parameters>
    struct vandg_spheroid : public detail::vandg::base_vandg_spheroid<T, Parameters>
    {
        template <typename Params>
        inline vandg_spheroid(Params const& , Parameters & par)
        {
            detail::vandg::setup_vandg(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_vandg, vandg_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(vandg_entry, vandg_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(vandg_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(vandg, vandg_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_VANDG_HPP


/* vandg.hpp
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
*/
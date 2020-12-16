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
XG9eXU2gu7oqhRXaZnYDIWZogDR56UejULTA5tv38SOQwn4aPPqJrUi6RRjXMPgLr62U8a9GWHpTzyeen0lX3Y81vaiY5baejvamwRV7WtwlTEylcR9/3fVfgn3V5PyN4UThbG/qsWIgF5smm9vdRp6812CFnAJoIwoZzQ+12kZNDteO6so6/0bLNS6ZTVk9HK3JfohtJ2n8DnHa3ay7KH48g3lH1m7WXSQXQlH4h5W++fk44zXJ4rhPQBokxDAyqZ5ijRTofzuN1zoBaNsKTq33xDLsmta3Wj8O4XptSS+5XWHYB/yiGrfte6KTr7McYuSL/hjkonREHXLTXm33DJbhfvm8lkLDvI7gGeCZQFwJgcXUhctIcMymm8GF+tjqjkS6LSFlvt5QbUjJrC4m68rQlH/hWFoN+WAndcPRbvlOVo5Tn1pFFsD7q+DbITgKJlTg0vIjKG7S5pJ3HT5cxPYUL5/WnT3FLYtS7P+Vpmn/j4REHcenPIKAyZc3sqkyNGXAwwswjZzUFk+mAM0I0ETAEArwGwF+CDCeGExHonQtX1641tjf5mFpq2VbZIX7GSh6qjfWeAiIagyox1KVFAoM9dY1YiTDvt/rMIQD899W+5pO8A2nqGxEbIjaBfTTI76hq6jmswgSD6p4Log3QsbzwE6HJR7Yc87YlGmKmBUrh0bSc/OB3X4p739FVPkV88AC7UZOCXKlSXji2Vuv1EHoxS5Y6tMSCoInlPgWYYTX5daXLKoR8uBGvvRV7hEEIMv645BlfmjzJzKiLKtAVxHf5IjYjq4SULH7llHiE2bWnPFZFk6CEhHGPLyhP6jJaUxUMCAbbyqK1pkvkaGxSHqAn8Z+5cF+duMT11RsobHzSDxFZ+REHUM31+3KEVxfh50gESkgOaTq6bErNFlYc+NsypjsVIY8kSNxGhUSz1kHjfJd2qzKd1ipmpuXQmVw9PIcFi1TgK+DLBYbe14siD67hrIruwzZlvyxOJvlGu1NSlW7nTh4InSYAzbF+e1iR3gszmmceMcGHS5w9IsXSTtvpDbtiR8t/VXs7yf9Afa74uO4WwyUi/ki02I+no81Ybfl13OpZhpPbZ4S/ujbqiiIU5pGO+Vyirvqq2KqkQifT1N2auUjIkeRR4i8CnBX0lWxSkkhPpKxuU8c2QW29XVVCAvBSN0g1PaCLFuLRdRiMbK35FOgxCYlv/EQvHAUFp184LhSTWSCPMy3f05CN0taWPnJF2hhhfvWiioq4SafoT/WH9TxcSh/eAo9rgm9akVe4uRM1L7/CYDAt+dY8t0xRetBJ0g5/+SU6yZdeybM++Gxv0mXoSMyqtV9ATicQml/k4MWoAMvwAXodNykn6MWoH0m0PL9I2PLuE2DP4+YGrbpDuBQbMo+wxrv0zVSSvvrLDAuddEkaVX6NfDS9FXZMaeFOEW8VVEHM0c+em70JCA000mE7kdCgxShHzOhsURoLBOCXxJSZygqfkWllXXkKpDKCxMllfOYSjFQEc2OH9b9Ul8o5vZx5VU8/zoCaqvV3TSTKsam1pX9a4H/JL3HuQrwO2scRCMlfseVwr49xZ/dVXx+/1PgT5/EZzy/g199ivA8ip5S4VmHnhHC8z30FArPSvQMFZ5l6CkQnjB68oTnUvQcLjzno6e/8MxEz2cT2RNEj1uEjEHPThFyDHreEZ5B6HlbeHLQ87rwJOBXf1l4PkbPc+yhuHqb8OxAz2bh+QN6moXnSfQ8IjwPo6dmPHseAA+8ynpxH7ej2VlLTW/xeW7gYwJyNoGRlmOMchGjmmOcbIrxdYzx6wkE/wa4JXw+wu9GSj8UlCZAZICwZxR6VgvPUei5WXgGoKc=
*/
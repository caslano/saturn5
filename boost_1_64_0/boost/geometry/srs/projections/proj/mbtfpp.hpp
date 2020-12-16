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

#ifndef BOOST_GEOMETRY_PROJECTIONS_MBTFPP_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MBTFPP_HPP

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
    namespace detail { namespace mbtfpp
    {

            static const double CS_ = .95257934441568037152;
            static const double FXC = .92582009977255146156;
            static const double FYC = 3.40168025708304504493;
            //static const double C23 = .66666666666666666666;
            //static const double C13 = .33333333333333333333;
            static const double one_plus_eps = 1.0000001;

            template <typename T, typename Parameters>
            struct base_mbtfpp_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T C23 = detail::two_thirds<T>();
                    static const T C13 = detail::third<T>();

                    lp_lat = asin(CS_ * sin(lp_lat));
                    xy_x = FXC * lp_lon * (2. * cos(C23 * lp_lat) - 1.);
                    xy_y = FYC * sin(C13 * lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T C23 = detail::two_thirds<T>();

                    lp_lat = xy_y / FYC;
                    if (fabs(lp_lat) >= 1.) {
                        if (fabs(lp_lat) > one_plus_eps) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else {
                            lp_lat = (lp_lat < 0.) ? -half_pi : half_pi;
                        }
                    } else
                        lp_lat = asin(lp_lat);

                    lp_lon = xy_x / ( FXC * (2. * cos(C23 * (lp_lat *= 3.)) - 1.) );
                    if (fabs(lp_lat = sin(lp_lat) / CS_) >= 1.) {
                        if (fabs(lp_lat) > one_plus_eps) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else {
                            lp_lat = (lp_lat < 0.) ? -half_pi : half_pi;
                        }
                    } else
                        lp_lat = asin(lp_lat);
                }

                static inline std::string get_name()
                {
                    return "mbtfpp_spheroid";
                }

            };

            // McBride-Thomas Flat-Polar Parabolic
            template <typename Parameters>
            inline void setup_mbtfpp(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::mbtfpp
    #endif // doxygen

    /*!
        \brief McBride-Thomas Flat-Polar Parabolic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_mbtfpp.gif
    */
    template <typename T, typename Parameters>
    struct mbtfpp_spheroid : public detail::mbtfpp::base_mbtfpp_spheroid<T, Parameters>
    {
        template <typename Params>
        inline mbtfpp_spheroid(Params const& , Parameters & par)
        {
            detail::mbtfpp::setup_mbtfpp(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mbtfpp, mbtfpp_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mbtfpp_entry, mbtfpp_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(mbtfpp_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mbtfpp, mbtfpp_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MBTFPP_HPP


/* mbtfpp.hpp
XsHI/9zLPcK74gZSwJXwvYKI5QnoKBFdQy1JmYOd2N6RkI9nOcOTEb+VC+/I5TyOjzWV3dXP0n7OEqgTTmgnMCAlQ/xkessCwi+EcKN7PgY45JM2YX2YmCMiThys4kGabdj6J1lLz4ML2eiRJZqvvnS+Mjv90FmJDrkJVCGuoFSoqTv3tPgAKcnyTVCEBY1pOqve3Gm9tF5GA5BxuXPT3zus00j16vR935XTyPNV89u9lcbl6YaSWyRXf2V3IiE2Nkp8KoT2v8EYJwGoGV69B7sln/d+QcrZZbb6Tx1UnskH5cOc+yU7XiEboHMZB9Hd2b9hqkrNtlWWM8sJZbgHwv1Z3hXrAMy2fa5oCXA/hBmN37DzhPtEP3uGu22AT9jZTUfnU4yQoEdsnV8nYVS6z3+USEgMn4OusL/FeK/UuhVevn5nq0EpHxCUhziPTQMBcuD7f12cD1R/3sGqBecwVyXA1UbdCSGJp20Wl+cKvf9aNVy+rnbaL2+l+W01KEWzXkgtGiZ2GpdlWvzi9kq2sPN118YAhu77VJZ+MZc+t1qnvgbatfAs22UoiTah2xGZigx9gxm6aakNQ39+WgNgBWescqm8aj8SwMDnNrdiDN4kC/uZuLpHCkojhorEWW3AiDnch+LagERn5IMR7tTxiDswtDPgmI2my5xWqXYWtMCLFTyktpL5ngCfjmLhNXqE36NPhhJiPJUJhWhkIkiZuLlV4LIcKCM3NdL9beKAQYqKEKHwxKaGSziwxKaEFz0FE4HrteS8QYtxFsMmxTsOU0hJUx3XxBvwBhahwT/OoL76KQ2QyhBpa4AEAeS+V7G1VJgiM7ScGbpzsQ1D7/4eGHo/w5SslTTJ2RnRUkcQEwnaYM2fjY7tARRX5YQ+k9CFgPYUy1qnSaCnWP8Q9YN7w6vA8kpYyElWe5ZRZxfGCN+vUdemG8qxd93ze6Nph2TTlpEjbnzQiSOArhtEkJFXKVwghG7QE7U2zUbCbqRU4qKJttYSWdO1tblmHu9iHqebeKxA0p9uMXica+JxruDxuy6DxwoTj3NNPKJbf+ajJB4rmMcKC4+ASp/0V5p5VvbwlpY0/ZT5veN6xS+rS88w8Vts4rdY8LvdafAbNPGrcKWJnsOT+SVsVso2d/qCxlCBBa+a8fDHAq9lOPwkXRw8TmYAvDCv/n1SunydEAKNeA3WeOjVm5Pj8UIKA63wJoY3WeBw/wv8YFE/GbuNsdtU6m51YxiscrN7m376ng62FnetQFpnQlonkIZJJL65rw7YJ5Q0PcW12XadUZsQBmvO3xm1uU2yJiPiiSoB4kJ/Y1K8A9TW/+NOQr/6DuQzzed27LXO55ar6yPq2YNgGVjtdgpd7+YEfHjWumCzxvoTS9wxkIXsXjy0pOljbm9zF7nhp88y+NEH/lZzpNphMEbOuS1yXXeD3gE3sz9lEnkQl5CkLN6+CSccn3HovmtVKEvBDRT6Tw79sym0EkPvoNDPOfRxGSolUjWEEkCKis0tCsAyYL0CcC+FIrjzQyg7Bq0ToHoAgZ4b2zb/mkxFdrl+plR2IWBQCzLlZvRjAJ1L4f0ntIM4jT74jzdsN+0RU9cJXGg3ROTUtfQJiy4HT10n87ShIqKmDT9S04ZfPUFTwhZwNwVMz14WqfmoUo61zmoBoc+SLCVUBUaLBQMur6EH09nypFK1VRPaIjWhnYJszmA2N4Zt2PQ8gdVxOmf3zrA0gfX1x1lLIHSIzSCqL3mrfNpu1Snn8nL2ta6WWYtnWJZY5Vyocg+TD2VAXzziJy/PZGklXS7KysO6zN+J3995Gl+3S0Mt45joOHLTlHo4nUWpJZ7rSdrJM1INqFS1+Jo=
*/
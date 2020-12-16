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
891vpAmrCpbbBZitc1FF8SwJrRavvNgkbtLYBT7h8/hE6Dhh+uHOi13JyYMoWRUVNLIklGz6dBJHtqNP7gUwsq/PQhnPzAONyi0k714zFSE+BsSFfPL/hg32+4i6B0zXRHzDf6nlxjatz4w08dZ8d+uTlfJF1JpsSgRA9wwm9vDUQ+nWhABwSZm8GA918v1jXzx2EA6R7fc7Hc1KR4VvMC/75rugWu09n3Qp+8df0TVoF6wYn8Wln/OOR6akVGF7L8E0T77tfqqIeh8gko+TFcWIkYE7iadNudrBkdlgruwTt2FlM7GyT6nKll1Ble2tzsUlRvUiVvThc2v3EtaLaYHtrKO/o9fuk4vWIN2L6/wSvpSefLlu9XyU5Zm+r+ap6+ZVquprIUN9RzcAYLXZAcy6ycrnbtHldAdIaLowmscIjUdHcx2i2cZUXOouH4hEnS5tmwuqq1aa3xXL6KaM8Q+dLLo6TkuCp7w75sy0QHgUBK0WfbgSR1AlZuiV+GwirBZniEE7HKGPYOiGKp8rH/vfAlyDwD3ViBUbf7mTRmwQj9gkGFLhLxsAqyG+BWPXGj+7KP31pYp+ioRG5Gphv1el6Odp1bwPJ7AxPcmuL3eYz2s483u3YuY2euYVlDl+GbP93CvZn2/ROgTj7hl6Jc2LbIYIQojjB1xOOcPUr9oLhhcdxnIdhsu4vLUVxRzp5cF7FK2XMK0j1ZMVJYgTrprk0C//4H7ZdIui89WqX+ZfZqPzYqPhXiudt53UYjpvtv7vL2mC3h+YyPQ+41IHen+Nm+C5RdH7M6oJWy5tlt5LLjXp/XVG8/xconcdzc2XSnp3ptoRJZJqi1vIEfqWaPT+AVfiBKrEDL0SB4rt9L6Hof1zJb2bwNuLbfR+ylIrvY/6laT344p/FvS+Z7FJ72Jq9uPW9Zuj6P0x1bwvL6GpOVH6iwVlJKJZkhLDXC+tNhVP3WVHIthxjO6dStlZJrbll5irb5FGxh/3OMiTGi3FtjY2LlLmK0VIlMVQ0U8mOhDlw1zVnEpFlI+run53sY0oC40xS61E+WnxwfCaBPuvRYnywFhIyANTpef2i5qg523FTM+Pj3eg5xu59QNuVvT8hGr9PyFDfXqT9Lx0vEnPFYwmPpvoWUezGtG83DQ9l048WHreWKzRczVX4gqqxAy9EsdAJeIRKz0vZOjc2XKKmsAuBO5ooefxSyz0TLOCK3DJRf8Vena8D29/J42/uLEKirOY3+qDY5SXmnxahSLyQnXQbXcRLerXQ4TQ1irmBfi4znjVyAhGMwIfIZjj1hC8eiEhOMHyNA1Stfmi8zmcefNNfB+tZb6dM//TZctc7cpbez7lS7sD8lG16IZharGmIcklABJ6v5lKyNNL6M8l3JNYglSEzLbF09NjxKWoxMtv9TrlLEYVygKOV332r46mhdavuFLbZzn02T0XtMp7Ha39M6fWuefFSN7y9O1is5PWcKV6/H2pYDNFkt8UaozH6okvIj9K6WOBlEBl1s/EUW2IVn+5NggxX6+Q8iPlY0cpdymPLmWH4GededEwg7v46plqXo82/R/A9KlHLWtj44XMB1cUea3uaRjFzYyiH6Foq6P4EjLUf+ZBPjifirWxwmJjQZHJCm9hTLtnECvUMT2KmJZ7ZKOUXKaEztH4dwF0mhAzAaspWCC3lFzOeZfQ4ZnWrxIx6e/i8kqpvLlurbwTsbyBUB54lcjySMb9XnvaLk+PLphPw2Bsgwg8qA6pm0pNuJdR9iSUVTrKvecByt0QVLlvx9w15O2SRZqsvtD5rNfTUOGaMD7IGF+9ETHeqmO86zwhM0NK9s0YJFUWPdK1nLt2t1/TQ8xFPUQ=
*/
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_AUGUST_HPP
#define BOOST_GEOMETRY_PROJECTIONS_AUGUST_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace august
    {

            //static const double M = 1.333333333333333;

            template <typename T, typename Parameters>
            struct base_august_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T M = 1.333333333333333333333333333333333333;

                    T t, c1, c, x1, x12, y1, y12;

                    t = tan(.5 * lp_lat);
                    c1 = sqrt(1. - t * t);
                    c = 1. + c1 * cos(lp_lon *= .5);
                    x1 = sin(lp_lon) *  c1 / c;
                    y1 =  t / c;
                    xy_x = M * x1 * (3. + (x12 = x1 * x1) - 3. * (y12 = y1 *  y1));
                    xy_y = M * y1 * (3. + 3. * x12 - y12);
                }

                static inline std::string get_name()
                {
                    return "august_spheroid";
                }

            };

            // August Epicycloidal
            template <typename Parameters>
            inline void setup_august(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::august
    #endif // doxygen

    /*!
        \brief August Epicycloidal projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_august.gif
    */
    template <typename T, typename Parameters>
    struct august_spheroid : public detail::august::base_august_spheroid<T, Parameters>
    {
        template <typename Params>
        inline august_spheroid(Params const& , Parameters & par)
        {
            detail::august::setup_august(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_august, august_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(august_entry, august_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(august_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(august, august_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_AUGUST_HPP


/* august.hpp
l7xiaTHc6CQ/vEJ2kILxInb1dSJBclODSYjgXjl6+a+O3Bq9b+d7qws3+le2cYevf/2UV509R27HeZfIBalYiFyi9cfuMXrXan0xv3USxqh60GfLG1YbhSbW4f4UnWt5ybThnKVpwzulFaP4bRsPWtttDu6YMbp0TuiZunBds8iR2HYeMjSyKQuYVM5niBmLz1AmXeH4EY9YvrL61dLx78YGypruPPXYzUD1KUtBi0cT9ZvIVcRgEkGMBM4Tqf3bY8BSDzxpcJSI2TO+ohzRtDyaPcTpk1HHSSbTcl0MFnPjrdRMjp6i7XfEUJP7UC5W+ljNTkry7/P+3I2M6MiAqx292KdEXoPPuH4RKK9PcK7b9IEXwi6pOFvzyjC9N4yIGJb2U/HJvWAXrjImgtffdOH+drGl4Vs+fMm03D39u3ycEtP8INp4R8gpuBYjAX9XtGE32wUd3xdwW1nogQ8lnI1x6UfdORhYrB1/Jh5fiehQOdpqTn7XChp+lJRH4tb6TulLn2flOeXqsYV/Yv3E5mg0ntCJXoo+sEd+6pRK1Y8KRDpW46emypJGgVuXy3MZn9K+OIJIPqejVbOcGP96w2uweGeMliV9vjAyUsmFDLM2rq7SxfrgqgkoZf2vTdvc2+qIhtrpODm370XbtnOV9xU66meFUxQCQ8lArjrrCn2TY/jFh8+uqlhYGTIH2nBBOVZi9Tk/LQ0N3N5rQEKMnEFaBVeE4iRnWniugSd4pK+E4/ea+vpvyUsuXq7Akzq3v8TTbpQ9o2f7HGBwmK7ZzdMZTU1d2daWqW3ZhiTOQEMbOMOQLlKfz9U4ibNNd/ppVe3kpa0PQo5do0k5HizbMPfkZB9DA+CuPRg+PKk31bFkPTHfdbQ4I3wcODHSUq8RfELLvnIcuphf2C60PMM7yoI3zeUb628lz5qucuTa8v1RAkeDBC1Gm/4BCZkT501NXfe4adCdmeoq4aYIuTs1acc6jFKx4z+2O4zwStEpZnlsB35yCz5UG8fB4PCdsEURue+943DRllwTYUd2MvM1S6t1VNCehHMEVMxH+jRRA0xPC/c+1O8S88U8mUmk+AcrDFzv9Ip2dxkucm+0ihuAH5TkteNtvc5udJRt2zaUv93z3omlgNAdgWfZ5faOPUdq+go+RmppKc881jZwu8K9oyOSprb812YNaSnSJdZ2NyEnQT7xJAE3lfX6yPnlBuAwBZYj1Zbkd8ezc59qxpfGbUvm8kUbQf79dAlnLin7HhKmbUXxHHcPUNvDSEuLuWwQYxWi0iea6Y5TK+009AIEnqaXpMPe3XGsbO8T1L7Rxokx7BewZki1hRc4cFd/FQr7g56OwinNrfnivHrCH4nGrFwoVd6rc8L4r8HnhIsHu7kJqTvcY8Lju8GjbtjZ3lDn+ffIwHyxPz53Bv6/yakspWyrAXzP0EuWhQxecSZlvYqdVbI83qYOP6TOZV7gXCqGGz1WUq1fxiioLs8Lib3UJn7W50dCAseue4uAyfqSb6L8NG2iRcAWfa/gp7i2rZPC7cLHjDljk3eROmS75l6CzWE69dz7SO/DK8r5dv3+1c54cKzb8Kxtn7/hZyS/Xs7X8u8RTt2oEiDR9lFu28Cln3GMbTs9LY9LmTPY8i7RcBkP6GFr/jmH8j3gqVKVozU8dbEp+0SU3WTKykXZHaZsjSi7x5R9K8rWmTIvI1n2mil7UeC9lSjLTJZ9YcpOE3UztvPLOkXdiabsn6JumSm7TuAtMGVvibKwKdsyK1l2HGWtlI0UeCcZvPNF2emmrF2UnWXKBov2LjRlX4vxXWPKckXdv5iyh0TZ7absJ1H3IVP2vsB73ZRtIWj1oZnHWIE=
*/
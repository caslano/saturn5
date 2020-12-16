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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ECK4_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ECK4_HPP

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
    namespace detail { namespace eck4
    {

            static const double C_x = .42223820031577120149;
            static const double C_y = 1.32650042817700232218;
            static const double RC_y = .75386330736002178205;
            static const double C_p = 3.57079632679489661922;
            static const double RC_p = .28004957675577868795;
            static const double epsilon = 1e-7;
            static const int n_iter = 6;

            template <typename T, typename Parameters>
            struct base_eck4_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T p, V, s, c;
                    int i;

                    p = C_p * sin(lp_lat);
                    V = lp_lat * lp_lat;
                    lp_lat *= 0.895168 + V * ( 0.0218849 + V * 0.00826809 );
                    for (i = n_iter; i ; --i) {
                        c = cos(lp_lat);
                        s = sin(lp_lat);
                        lp_lat -= V = (lp_lat + s * (c + 2.) - p) /
                            (1. + c * (c + 2.) - s * s);
                        if (fabs(V) < epsilon)
                            break;
                    }
                    if (!i) {
                        xy_x = C_x * lp_lon;
                        xy_y = lp_lat < 0. ? -C_y : C_y;
                    } else {
                        xy_x = C_x * lp_lon * (1. + cos(lp_lat));
                        xy_y = C_y * sin(lp_lat);
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T c;

                    lp_lat = aasin(xy_y * RC_y);
                    lp_lon = xy_x / (C_x * (1. + (c = cos(lp_lat))));
                    lp_lat = aasin((lp_lat + sin(lp_lat) * (c + 2.)) * RC_p);
                }

                static inline std::string get_name()
                {
                    return "eck4_spheroid";
                }

            };

            // Eckert IV
            template <typename Parameters>
            inline void setup_eck4(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::eck4
    #endif // doxygen

    /*!
        \brief Eckert IV projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck4.gif
    */
    template <typename T, typename Parameters>
    struct eck4_spheroid : public detail::eck4::base_eck4_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck4_spheroid(Params const& , Parameters & par)
        {
            detail::eck4::setup_eck4(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck4, eck4_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck4_entry, eck4_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eck4_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck4, eck4_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ECK4_HPP


/* eck4.hpp
PvT9i4/QYZT7u+vp61DsgIvRT7T/03HYadXojgeRI+Tk0JHAkZWfn2MeOxf9g05adjt+8zPU1xe7mJjImw85auVa6ELcsAhb8aCbGAvmjN/D8z9jYy1Hf2XEwePw7tXI82g/LvABcwN8XTscv7EbYz8KXhmtVD9SH9JA0jDSMdg1yTPwc4ZQJ3r2qaWu2vA3paqJA/baiG//Hv3YBR5cg117I7ptGr9nETtbSWz7EPyebxy1Q5VLLAO6ICdf/A5dUIMPhf/kokP7o8vuzoQvBsFryYzxcHwAxn36h9iZtdgo7/PugDX05WHmH+yzP9/IXDobvltGHJDYdeHlxINqHNoCT+BzlO3CPEcsLGE8c9N8/DT07+uTqZ/4NSygznwM3wi7fcAQbCFsp3Uutjp89fyJ+OXp2BvYX9t8Af3zmQNz0CHI4DZPEb8ow+dgbt6cRj0Z+I7v4As9gZ5lHt7vaWT+YWyKD7DR4I3fleK/Iv/XfQHforPe+4qyq9Avt+OnQdNTSeeQnFuYP/DFeiL3F52KjH1FfL2cWAx2Vx46pPg4dCHz7iXHMhfjq+T1JgZO3Gj717C/r4A3+PuDO/EJP0e2viROdTXpTOj/KnMkc809G2hbHPjMn14lcyvzS9Pa2sWjwzW1h/l+lPQM6YXR4d+PkJ4kPU56lvQ86Q3SO6T+cfAHaTBpTFy49jSa7x3iwjWlF/GlPvmSWB5tOZoY6J4fY48fwHzC87PROUvhtyXwbiXz01f4ZuOx7SYzfo7jqV7EwrKRuz/sjJ4iHlSYjH76a7ge2JP8tJs2B22j3rC+A7vgl+Y7AU4/cCTeQH5vT5L4m5CV23/AD8I+ncezPFIBqZiUQ1pIKiJ9RLxsxe3wOLKzqjty/jxrXevhqVc89cIH0PxwxqYWOxReXphIPBH5HoI+fWB2QJ+AZuVxdtsDWut2CRpr2h4n6Om3tQtz17Q69AEy/WMWdnwOf+MHnD6P+YLx7U7MRJZ/cpypo82+rYsL23C6bsfZpHNJF5IuIJ1PuiguNvYPxVEm6Sl/7HUbn+C7PGgnz0s95aGv99oenMmMIT70vMeRj+UK3sRmQY7L3mFeQvfeeiD92YhMwLfvIScrniE/8nh9PDZvIfPZr/GjmHO6HYY9wNxfnsMYLKLv2CxVrzAW+BaDtiH+sB269XBs8vMdi8a02+/3oJC+T8cJXnkTfbStZ+G3T6vTW6WRoI2oJ5+1xIYVbot63uX3W/7fY9qvs9cYzSdjYuM0mN8jSGNJo0ndSXGkhaQ9SYWkk0mXktaTZHvP5O8LSLQ3eH4xyY8VvzIm1v43xoR9eH1M2I/rWZe5ZU/WXkfbNGNMO9CH0/1ywXt8jEU/TbtngFv0Y/2afj2Y4ExTfHoT9x2MzkkgrqJ+/hmzkv89/gc2Nkw5/C7lm495P5GjkCUKcMT+fh92bE4MNgLYXGA9VAw2SuM9MSEGi9OwzQI2NoRht8VgycB+A2xD1xhsqob13CoGS9Gw8QIvXcNuFLA5wC4FVuTFYJnAXgS2u2jzPA2bIGDzgfWggdcK2EJdx5GijsU6b3+Bt1Tj7S7wCjQsUcD203lTRd6a3r5/yNgL2FE6720i78kaxlKsga0HhkpWQ0Tey4BdB+wIAbsG2NvA9hGwR4CxpKMyBewx3b5cAXtG0/QjAXsF2F7knS1gHwI7HNgC0b7NwJ4AluaJcesT9mOFgO3TJ8z7gRK0AjYKnDcF7ACd9zxRxxoNW90lBjsEWD55B4q864BdBGywgD2s82LmG9iLwD4D727Rvi/6hLSqFHl/7hP27Q2Rd6u+YZvLBF7vvuF4zBGwvn1D+o0XsMF9w7YUizEfqvP2EXg=
*/
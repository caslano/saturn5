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

#ifndef BOOST_GEOMETRY_PROJECTIONS_MILL_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MILL_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace mill
    {
            template <typename T, typename Parameters>
            struct base_mill_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    xy_x = lp_lon;
                    xy_y = log(tan(fourth_pi + lp_lat * .4)) * 1.25;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    lp_lon = xy_x;
                    lp_lat = 2.5 * (atan(exp(.8 * xy_y)) - fourth_pi);
                }

                static inline std::string get_name()
                {
                    return "mill_spheroid";
                }

            };

            // Miller Cylindrical
            template <typename Parameters>
            inline void setup_mill(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::mill
    #endif // doxygen

    /*!
        \brief Miller Cylindrical projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_mill.gif
    */
    template <typename T, typename Parameters>
    struct mill_spheroid : public detail::mill::base_mill_spheroid<T, Parameters>
    {
        template <typename Params>
        inline mill_spheroid(Params const& , Parameters & par)
        {
            detail::mill::setup_mill(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mill, mill_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mill_entry, mill_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(mill_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mill, mill_entry)
        }
        
    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MILL_HPP


/* mill.hpp
QnwUAt0Rrz6zgTf+KpGRfHlGmAdsijtRGhhrc8kE1KFnPSbwUYY5gVl8p9nIQrU4MqwWIDWLz5WjOwcIcecPRrKVrbH4+ZKV4YKVKskKUx4owz+7msOr8TKCy0hkkESYQQTWEJhx2CQXmm3wqWf6cXQ4nENAfbFPPVplcvjpLf+4U+Unl/JDUfGehFpLiCraIt9EVRbZ+5AX7uhDUS0WWPc48UpnHY1CAnSTiBigGwlTZYk4IydDBtafD2X94A2WM8HwEOZVzUmNoo+NNhELGsRcRGwhErswfWLvyApaVl2AJZhMbxrSy02f3u0OM3NTJDFfZCwQG4jENi+3EhvcKbH4GRbOJhnERgOx2HlALJxEbFCnxOQNJ9dXT8L1wB4hjQxDHmXRKufZg+hwMNGizgzlpNMvFnVa4UK+Xob1ADssbsAHK51tPRf6tvKe1MAaNxBToEn8ffm0Ny++1YNv8GsYQvQ+hm+pVXifhH9oOr0Lhiby1bUfHzkM5FINjnGES1mD3/gVAmEEI2gpCKcLhKMYwZWCcJxACDKCOwXBg2BkWSCeEh4iXP7wAOGaEO4lXCMj/SzRY34oUMj3zUYRNBjOesNZazhXGS+hh/HXXDxMvLGelvYsqxVnJTWSi/OXTBeuIgUbv2S0cH1Twb6zZIgsYZWXUSovkyLDLHkx84FSmGaS1fFlJJkjM3ClUKDx+z2z8RAzH7UR3nWo968XkxpBFXJM16q4NViLC+QYzHChHiJ9JG7sGoCpej4cCugn2IhSKqo3hdBnSQcCF6hGyNPwBTj476AhceJmR/gyhFXDLBYD1nBANOcZupZ8lgdwqbQTeQ3teL0gMspKAkZFjFpNL3Q+qXkAIwfTJ3GWS5PuBVRUC+J1PGtwx/ChvxQqddWwHF0AQxo1lvCUFARYFoHvZrFVJrTlJb6pwEqAenywXXSKY5t0Pifd0GnS+aa9PKG6T/jWpJ92dZJ0PsaxT7qAk67vJGneRqxXSZOT8K1Jn9FZ0gUYxz5pPydd22nSftM+p1BNJ3xr0tucnSTtF3Fsgsby1uUlUejl7Ax2glXXtgvEdJhYAGQVwcTAmcyAfXyMZBfE8/2rmJ6/cwb8dW1vpjLgNzNAyuDxoZ3Ex8i9IbItI2R0zCair5H7bPzilEBcv4dnqbnfcSkItFtMoWHqijzjti2gwkZGBGokPGCHwh27CZ6xJSnkXV7vJJm81sEfyjpPJFjS5GEdkmFnuR2GgLj0ExIQR6EU2SZMfNIVvWtxJcBUYlsFmV7e5XeDU6mjvF9uJlXApK5vcvLqN1sGgYhx1ulFfA8G2IYfUoQTLveSY1AQb2BB/INZNoL4+GoNbmDgCIy3boEsxCObTCqnJLrozKaZ6cyxo/POIs0ht+kjvcXgrgYsVjWaJt04cJ5kePxQa9IDw2eB4RkZ9lrl+sN0/5ckZ/hK4JpLFoLK0SOXkaSFkIAP4tYIE8Fh+C0ybpIExKKHL4KzSCkVCz+osJupMKjN6U+/Aw/onHmI82GQo0aWuY8PJ8QDoV/ZVf3q+wK+ZNPle9fJbd0F3FXlDTueiov9jQnUVpWdR4CTCfYF40MTl3gVABTJgYzwBn3czDdFAUabhJt3uUqamjPYftXpbn6HfKEmzKBTh+ZL3U+wteM9M5Ri6XtKyNQupEvd+zrn9VSD1+GSNXhseSIbnNOWAS/gAmh2aP4MgM6GKaF2UxLXjyDXdCOoF90zbkM3mcepmR+aD26iVjdxmWPJWdIUuJJBq6QMEnYYgqidqJk0ouR5b7KyE7ziPw9M4cRvLmnazuX0YUgYrNT3fFsoeP17jS7zYcCm+6Uqarg+U5wJtboXgFtYor0Y7qA=
*/
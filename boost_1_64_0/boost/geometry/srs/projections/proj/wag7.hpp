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

#ifndef BOOST_GEOMETRY_PROJECTIONS_WAG7_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WAG7_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace wag7
    {

            template <typename T, typename Parameters>
            struct base_wag7_spheroid
            {
                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T theta, ct, D;

                    theta = asin(xy_y = 0.90630778703664996 * sin(lp_lat));
                    xy_x = 2.66723 * (ct = cos(theta)) * sin(lp_lon /= 3.);
                    xy_y *= 1.24104 * (D = 1/(sqrt(0.5 * (1 + ct * cos(lp_lon)))));
                    xy_x *= D;
                }

                static inline std::string get_name()
                {
                    return "wag7_spheroid";
                }

            };

            // Wagner VII
            template <typename Parameters>
            inline void setup_wag7(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::wag7
    #endif // doxygen

    /*!
        \brief Wagner VII projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_wag7.gif
    */
    template <typename T, typename Parameters>
    struct wag7_spheroid : public detail::wag7::base_wag7_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wag7_spheroid(Params const& , Parameters & par)
        {
            detail::wag7::setup_wag7(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_wag7, wag7_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(wag7_entry, wag7_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(wag7_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wag7, wag7_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_WAG7_HPP


/* wag7.hpp
OZagmlaIVX2keUs5Fz9byL+eaf/ynko116Hr11N5pO/klBuFw2n6i3au4oiwX0aUIRKpPFMGxUwZFLHEMt3iTb/TeH5LLnQ2csl//1vLI7Vr+UaWSotsRsjpTwEFKq+1QZJ2VQ2kUDHrV3XXM4othwqibMXSWjb/WjoJ155BzfnMetWc1ao5f73IEh4kPWtp59VJGryxWxi/UUzD4TMbh7ZOYFUXF3PrUwBOJgqquc+sIHHAvgEF27FXfkO7pGKav/eYq665mvpWLyIJVvkGafFhJooaTCxky56k1uICn0tdcy5V0QHc4+9Zh1XU3TKqaOktsorebKUq2qo2OxmeIOYrJQUeFYsTPgfjjTGxHvZ45VGHIYFhKBuP9ma8h6xzaZp8hff7hFe7kiKoFgcT3D1lK0zaqB7IuH7zrAuuxxdKXJ+3tCf+d3xm78+fsHdCcUDFM1J+8shyJT/xW4b8hLZVyo2j+Fsu48hkmloRapbk5NgVKtmvV/4p3BSjf6dEFleqpjjkZgshhUhBfHYub4vyITpFgUSMjiOVJH89CvT8wv0kEOKLMR0q0HYLtNwCPXqgdjFpeMh6iyw0v8fXdJO8VNFhGnxFD06OaGrAiNjNrYkEdmSvcHmMcNlwjAQTjMcmPIH6ybg5NOFgWZvFmhumhJT4uuo8EE8s5lUqRcRmPYuDkrfesbk36xIoNG6ve5JiPFXHKAVu5S1OU2CzzeZmu3otjSCz2a5YAJKmh7riJpdRrOknnWnGcpdYjpSnIg6nxJh4OV1VhIUI5NbUgvAdUHPNUEDv8bGkiQtHN0DVSzkLb5eHAGfVhWyj9KLM46I8+rRLUX46H4rydhclmVIEMohCAWIBg7iMQDxogrgQQSwDECxxz7jJ4jccY3wmumVNlsfnNM74ZmTGJoIljCCHENxoGQi8iODoLlp1qVmikAx5STR4B0N4rtWllK1NAKGbInHTaqgtokY3/kBY7hiE8HE5Y6ggDJkmhvMQw6M5LiO4ASHEshazeOZR1VE+hVIRizEH5wIeh09wwAYUyeRgAEljePIVcpyuAFKNdJmP0mxUacoXAVl+rxhj9R4eY89Ye6nLx7ik17a41GXVjQDy2c4QBlqThGrUV3/VnhBiVKlcmNhC0305C08J8JMMeAgBHm82cz8EfBkAJrnnQY/vaxsZfX4tI3ryty5t9VgjIHo/24QkJCB6m33/FpaekUddpv95Bvt9Aptrgp2KYH8OYIV+KYKbdOR3ismmzY51xu3O4ttQzceMNB+b9BPFTahGisnA4AgtJEghBVpImEK6aSERr+rrW7mg1zyFBb3IbKiZDVDQZzpps4fWUOwmcT4RqsqoxQdd4m0tPuwS79XiI1p83GAhHzPJG36DJLebbdNyA5Dc7qeERaxBZe2zXD6DG/AnlN/FuiefibE9332aL0YKi/0F2FtdS9Ydde9keZ9u3eEl7WVj/fzNws+jXTVENUu0D+Vtqq/HWNYHWxatYE/ktMO1uS/av9kn6rOp3qflsClHngssVl+OpnHIrehiJR5CV9WrPXtYXPAkzw6tzVRYo1KsthBTq/GeB4Nb6o1wPq2h+bQLNshoOm+RpXmU3L2ARlIpw3bV80c7N0ECXmGUaq/xHtDtGTq3cyn+dQU0XS4yvJBKaq/XI/4rGzTtdb8sXv//mrTXZj9ZOg/6SVumgaCay5yGhQTq3dSyiVnt0ZjPfb0UqMfjcR2smc5uhjUT7GCEdLH2SfqL1TCLCjGCC/HGGhcOvakeClHAheDscOdy2F1HrZKkq6jWaC1Vss+FSDN7Udr4qKXwJltFxEcb+pliQz+jQkycexiwK63UAbvEksNwlDMMhzo=
*/
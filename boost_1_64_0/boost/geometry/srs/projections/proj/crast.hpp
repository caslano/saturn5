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

#ifndef BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace crast
    {

            static const double XM = 0.97720502380583984317;
            static const double RXM = 1.02332670794648848847;
            static const double YM = 3.06998012383946546542;
            static const double RYM = 0.32573500793527994772;
            //static const double third = 0.333333333333333333;

            template <typename T, typename Parameters>
            struct base_crast_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T third = detail::third<T>();

                    lp_lat *= third;
                    xy_x = XM * lp_lon * (2. * cos(lp_lat + lp_lat) - 1.);
                    xy_y = YM * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T third = detail::third<T>();

                    lp_lat = 3. * asin(xy_y * RYM);
                    lp_lon = xy_x * RXM / (2. * cos((lp_lat + lp_lat) * third) - 1);
                }

                static inline std::string get_name()
                {
                    return "crast_spheroid";
                }

            };

            // Craster Parabolic (Putnins P4)
            template <typename Parameters>
            inline void setup_crast(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::crast
    #endif // doxygen

    /*!
        \brief Craster Parabolic (Putnins P4) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_crast.gif
    */
    template <typename T, typename Parameters>
    struct crast_spheroid : public detail::crast::base_crast_spheroid<T, Parameters>
    {
        template <typename Params>
        inline crast_spheroid(Params const& , Parameters & par)
        {
            detail::crast::setup_crast(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_crast, crast_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(crast_entry, crast_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(crast_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(crast, crast_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP


/* crast.hpp
sI+0Ht7Oi8H26h/OE70cA5O2nYF9Qt5pzAdTFbAIHZ4QoZsTttgW41xhaIxZOvm0Ntc1EiNokxhBm8QI2iRG2BaJEbZFYoRtkRhhWyRG2BaJEbZFYoRtkRhhWyRG2BGJETZDYoTNkBhhMyRG2AyJETZDYoTNkBhhCyRG2AKJEbZAYgTPJNo8o2EZHeSZiPkcRdpYrNc6LHv+KjOvR/FQUgQPJUXwEDCbhwzsB/IuR0a2VzHYz8A2AEsXMHekBbP4D5jNf8Bs/gMWwX/AbP4DZvMfsAj+A2bzn4F1lW227V0B66XxjhUwybtJtg0sYP0i6hgQARsUARsKzB+PtWkx2GgN+52AzQDmj9EqkXeBhl0iYMXAvgdWLGCNGraLgB2lYbIf6zXsYAG7StdxvIAJWQVmyyowW1YF7BpNgzVK4GnYIQImZNXAbo3Au13DZgjY47rNvxKwZzTe4QImZR+YLfsG9rwub5zIK/SBgb0Y0E/wi9QRGm9GB3VE2fKChmp/J391Y220Xtgk9YKxdV6nDYW+hRizbrAeOdFRs8a868XWIckROiQ5QocAs3WIgb1FvQnEQNYpYBG6IdnWDQJP6gZgtm4AZusGYBG6AZitG4DZugGYLd8i77sR/fjAgtlzGDBbLoDZcgEsQi6A2fOVgX1s1WvLBTCbj4HZfAzM5llJF2B7U8cQUcdnsl6bj3Xe3A7ysVnPb8OFieZvd1AUf2/2+VsWom/RaCpL+53RuMFp3BiqLQeTW8qBgX2ldXLx9BjsG2A+jV91gEXICzA7dmRg35H3OGj8WwGTcgXMjicZmBrlwyhTtMXVsIEzgEXIHzBb/oDZ8gcsQv6A2fIHzJY/YBHyB8yWPwPbSrf5WNFmIZMGtq3G21fgSfkDZssfMFv+gNnyJ2DShgRmy6SB9dZtWTweWEQsanJELAqYLbsG1k+XN0jQZXsNGyJgAzUsR9Qr5X5yhNwDs+NYwGxdACwijgXMjucDs3UBsC2Y0xobKipxGJu+I2JY8VLmjRwPG+XLcVOIhunMf3sPr60LlvgF3giDV1fDIoxB0W+qaK28smqrvCHKHXAr/b6NFC7ME1X2j2OujPnAoykjiG7oDgaPC6soKIYzxseJFcACO5fQBIixmNE4cIIzxrV+XL75/XM786yinobxJgA/blC5JnwfQRgLKSwmAGPiWBPAzW5IDYMl+WXyvjnuhJfxlUYdGyj0wxf14owgeK3vJRsvcETcSHcKGq6sqKupDt6oCm5bcboaXq9AwCAI8HAeulmMamVkHLE5TlEHcEQ5sEv75RgcMy6ToCcDslzHTHyCmbYm8oyoCvGPhubdURbNoXZJYYMOJDGywQ13wWWayJGIpZRQhKBb0ijTvlbjS+DK/raJO8LGleOh7OdFrT2nXZF1qXGCLq2NtGlH6/0zca3JPNeZTazq3MHAyMGQB3Dz3g9wiUaWV9RD5zCTuMmR8RT5i/yXL1ewj9ZHEv0SZUsExkjm1TDLZpgSYTMAs20BYPYcDywibgXM1s/AbL0LbAvWD5r0rgjERqwb7jNIxKpMrH/6qI7Fcm26TI2gCzCbLsBsugCLsH2A2bYPMNv2ARZh+wCzbR9gtu0DLML2AWbbPsBs2weYbfuIvNL2AWbbPsBs2weYbfsIPGn7ALNtH2C27QMswvYBZts+BrYb9f4N+3SpgMl1cmC2jQTMtoeARdjPwGwbCZhtIwET6+7f05anPQOT6+7AbHsIWMQ6HDDbRgJm20jAbBkU5e3Bc78t1wq+StWwmwVMrPcbWLrG29+UJ2Raw2ZvoUzrb9/HX9FQUxthUx0pbSqj8+Y22UDkLG4sL/ffAE0I3+jVeTzPrM8=
*/
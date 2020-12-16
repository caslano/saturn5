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

#ifndef BOOST_GEOMETRY_PROJECTIONS_TCC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_TCC_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace tcc
    {

            static const double epsilon10 = 1.e-10;

            template <typename T, typename Parameters>
            struct base_tcc_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T b, bt;

                    b = cos(lp_lat) * sin(lp_lon);
                    if ((bt = 1. - b * b) < epsilon10) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    xy_x = b / sqrt(bt);
                    xy_y = atan2(tan(lp_lat) , cos(lp_lon));
                }

                static inline std::string get_name()
                {
                    return "tcc_spheroid";
                }

            };

            // Transverse Central Cylindrical
            template <typename Parameters>
            inline void setup_tcc(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::tcc
    #endif // doxygen

    /*!
        \brief Transverse Central Cylindrical projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - no inverse
        \par Example
        \image html ex_tcc.gif
    */
    template <typename T, typename Parameters>
    struct tcc_spheroid : public detail::tcc::base_tcc_spheroid<T, Parameters>
    {
        template <typename Params>
        inline tcc_spheroid(Params const& , Parameters & par)
        {
            detail::tcc::setup_tcc(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_tcc, tcc_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(tcc_entry, tcc_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(tcc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(tcc, tcc_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_TCC_HPP


/* tcc.hpp
Aw8Q8GUm8LkIvB0kUGDKbxeCld8IwUpQRd2wSAlWgkKwUqQiuy+IHRYrGfMziz043k3MHRDzQnFLq4hWJbkImKCCIOWhotjl3ujBAvDDDPhCAtzBBLzuPBzIABih8QhSgpMis2Z+z2B6OdF3GYL5pyXvFvL7SY/YgpL1nPfdWxyabATmfdnSOkLDXSQoEU+gLqCjjUVNEUPRuraM9OGPJd4/O1uGA892o0TyVko+GnG/yrinEO4bTNxPnCtWu6F3wEdHabMyMdMbnGkEZCK+oeUph5RYL3R59lt3zK0BycRXa7Zu33qY+3GA+7i94pvC7VbA1uH4uZiC0N+LSF/jV6pGWIOE26GBSbttEZbnE7M8ewstfq+D5aOM40b9YNIZ5qcM89cE8ysT5kKEmSLLaWz7/VhzFtc1b3hmFtaAF4XZxadjgK8kBfG2KSZV27jiHPzjNUumHlH6jqnYtBCpmO02qGiHVNwce0eDj3eWGxHGHcbQufLAMwkGkZlIXQ9e4pSfux4oLcEX3CDWWRXyLmLu/W3mrvrq1dXA3+THfcDsGf0555KQrUDQkx3KfZCEbPm/aOr+tL/o89aKRTT/8FB7diFx8BnHGzJiFED8fi4LiP/M8/zAm9WMME31ypKzLGmyfz4pFOyFqAPZrivg1KdVkU778Qj/HYa/7SaEf7HbgJ9ylsONqO5AmLAax0gxvbhvuhjhouZDupln7w0yTyfOk2W/S9AfkkUSK3e7RIh9hcBvkZ7GVjOGQQqbhFCvyPAXpFsynO4ILMCstuWo7Jza35oETbiBazfCpa+fj6UPmqXvNhl1qejtLWZeY2PqooMA4+XrrOUEJsdspB1n0m26E+XRdDoZfx/DAMbOZ3u+wmglziq8IegeU4f3zvlx7p/91D/dqhSd1NyspL/5Qm6XTwZg6PynOlZudxNfORg9T/X436rKrJgEfLhXAnRpAWUthl44T78Gl4nAxkuhFwP7sEZeh7NhHYGwdvqI9RIcZ5tFitZb5sTSejeDr6pxoPVPZwD8KzX4+CoJ/6R1GwX7qxtiYa9i2EOdYF+LsLvSjXbB6Uvmyzme7m9d5eO/LL2TU9wjDPKtGxHkULcBMh1Bbo3X5avTFH0f2mX3/56BLL7Rga73CiyXkorOiLfLzq+5JM4b6ZZhbC6Uh3gPLdTYDWJkxF6Tx6SCZ9MzXQ5567zUOYwLaT6U8HLQIiwidtR0OopGnx/M/PKNNc5pA42QYjiMySAvk/jphAISBoa70T5P9cQBwBAoIpoiNitXVY+zNtXiq1yLv6km0ZhZi3dPtMWGDZniwmYAquLQ2HqqySa7uYHEOd85VkQW3VFU3WRcBcoRxZWuUiptfWhDBYlX52yKhcAlQzSTx5Qjgyw5RaaoKcNvVVvlm/Pok+vY3vnCwSvrhvOtOXlaiHhzWMnY6KJ/5Xo5vIoM/JlddM7paGwgLnpE0ZWCDQbtSvYyY5wWuJbqqzRSp3UODKvOKR21U7Xha7CA4rsV3uarI6HaFxXF7/yLLdCMYarGXy6PRGI7Y5ZohB2hwddbzWJxjWH9K8XO9nPtpM7F2tlp9pqLToPawRMcs0suqqAuqTTpjdr2enn+uwHhNZrwuiE8GOwmfzTqoGrogaMzyS6SR1iKDiqavLCGiG74LkzKWCIlzmz4eROAlDQApiAEZ2Gp6IhQwaaP0My76ULhBCjtBNd1BooejOLPcxxQDEIUz1lOfKiebjtnGBH0ByOimrYmO6m6fIfWF6VJ5HwHjgDXEpLGVGFqsyoGM50jic7nzVYpPxXo7GHQaVgh8ltCv0rx7pdm27x7BEPeVenAu9NO1Xj3RndsEfKiisCHc8B8Rps=
*/
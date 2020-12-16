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

#ifndef BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace denoy
    {

            static const double C0 = 0.95;
            //static const double C1 = -0.08333333333333333333;
            //static const double C3 = 0.00166666666666666666;
            static const double D1 = 0.9;
            static const double D5 = 0.03;

            template <typename T>
            inline T C1() { return -0.0833333333333333333333333333333; }
            template <typename T>
            inline T C3() { return 0.0016666666666666666666666666666; }

            template <typename T, typename Parameters>
            struct base_denoy_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T C1 = denoy::C1<T>();
                    static const T C3 = denoy::C3<T>();

                    xy_y = lp_lat;
                    xy_x = lp_lon;
                    lp_lon = fabs(lp_lon);
                    xy_x *= cos((C0 + lp_lon * (C1 + lp_lon * lp_lon * C3)) *
                        (lp_lat * (D1 + D5 * lp_lat * lp_lat * lp_lat * lp_lat)));
                }

                static inline std::string get_name()
                {
                    return "denoy_spheroid";
                }

            };

            // Denoyer Semi-Elliptical
            template <typename Parameters>
            inline void setup_denoy(Parameters& par)
            {
                par.es = 0.0;
            }

    }} // namespace detail::denoy
    #endif // doxygen

    /*!
        \brief Denoyer Semi-Elliptical projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - no inverse
         - Spheroid
        \par Example
        \image html ex_denoy.gif
    */
    template <typename T, typename Parameters>
    struct denoy_spheroid : public detail::denoy::base_denoy_spheroid<T, Parameters>
    {
        template <typename Params>
        inline denoy_spheroid(Params const& , Parameters & par)
        {
            detail::denoy::setup_denoy(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_denoy, denoy_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(denoy_entry, denoy_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(denoy_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(denoy, denoy_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_DENOY_HPP


/* denoy.hpp
CVfgauoyyoJ35rAfsb75e9uzmuuH+uUYA6uCXZWhMSRsiwhbAMy6BmEDSDulqqgaK4c5nh5tjliDYXb254/gBDVo9iqH0GF5po1t4w8QdTTN2mURMddpEboNmK3bDGwJ9ccBH6+AReg7YLbOAmbrLGC2zhIwqbOA2ToLmK2zgEXoLGC2zgJmx02B2TpLwGSMFJitn4DZ+gmYrZ8ETOqEabasC5iUa2C2DAOzZQ7YFvgvdQ1sK4Z5fTs9OmZx2aC2YvXTI/gGmMU3wCJ4BJg9BsBsegOLsCmA2bQAZtMC2BasewVnVoLtPyXLyluse13XzJZotr8o2HqmzzNV+BZES5tqRgSdgNl0AmbTCViELAGzZQmYLUvAImQJmC1LwGxZAhYhS8BsWQJmjyMwW5YETI4tMHv+B2bLFzBbvgRMyhcwew4HZsscMFvmBEzKHDCbz4DZfAbsF8xzsUmjrpV44eMtZG/UKOax3vSBenaL4IvdIvgCmM0XwGy+ABbBF8BsvgBm8wWwLbDdTfzUxBeC3lt9fzHW919A2zAigFsaOE0IcwvavtxMnseZs2dtxxVsuZ4ZIdfAbLkGZss1sAi9BszmN2A2vwHbAnoHei3QUWZRP4Ie7zSjR1yb+o0NLbVKxk80jn4aYHKrEQs1vM6sNOrcXkYEn2ZE8GlGBJ9mRPBpRgSfZkTwacYW0E3yUrCYXR/Fp5utmL5t9wU5C6FEiyjEpLZx7YjQZx3Fh+0lPrGJKHw7UsE8uSX4sWgM+Qwf2PlaDRdFydKcCFmaEyFLwGxZMrAi7Vte8KsYrETDfi1gUuaA2TIHzJY5YFtqS/g3VwamhM0z3mApa6rz0/np/HR+Oj+dn85P56fz0/np/HR+Oj+dn//STw/eZ70taQdSd1I3Ui/SSNIIUhYph5RNyiflkpaQ9iftRyollZPKSItIp5DOIl1CWqd/P0d6hvQy6S3Ss6Tn/XKHh3cElJH2IpWSjiKtHw4OaRPpVdLbpJ7EEoaSBpPGkuJIY0g5pGzSIlKJ/t6PVEo6jnQ+6RLSSSMol3QuaQPpUtKjIyib9DBp3EhoQepG6kMaSBpJGkUaS1pAKiZlky4mnTKSMklnkh4lPUt6gLSR9JT+m73ZwZ7nYUSWvpjqqtTrHXVtqaPql7sqbj9PPb3IUU8/76r9uKz5sI9d9aDnqFN+ctV2e3jqu/c8dSLBiud34/d63uG+h6MOOtJVv9/fU3ec7aoxb7vq77sSH5vgKO8xT329i6smXOiq6+7x1OxXPfXnixy1zXpX1W/tqG9ZPP/qYlctrWXN9yJXXfWWUn9J9dTH61y1977EQAio7feMp55NpM4aT83I8lTR1p7avZJ1F2DLtmUcf++pPn8iXeioCRM8teMTjnrgFPiB8rc/w1W/meio0a9zpz5155zlKvc3rjp8b1e9+rCrpm30VN5dtJU2JB4IfS5x1FWZjtrrM0f9OokyoM8iUgFpP9LL4B1xAvcj3++oqSc56ru3PfXFJZ76YS/uVDvWUWm/9dQVD8ODVZ56dLKrBlV46k8fKvXBPE/d865SW21krPfjbCc0HJABDQ911d3lnhpc6Kkjt3HVjpT/01r4YKOrNhMXemFn3i//R/j619CV51W/ZS1hJ1eln05dBZR/qKeGNDoqM9VRN9zhqCUD4dfrHPW7nzy16HNHrb6WO2ZudtRdw6HhyZ5KOdVVr/0MHx1GPH2Vo+Z+iwxMcNUIxqz/r4h9TaeP4L9xLjw6CDlJcdTlX3hqVqGrvtjXUemfc87hKE/9dC+whz117rae2u9ZV/X7Ct6Yx70QjxLlXe5xh4mrRv/KVX9d7KkVWyEfI121G2087wLyX+M=
*/
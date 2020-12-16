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

#ifndef BOOST_GEOMETRY_PROJECTIONS_FAHEY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_FAHEY_HPP

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
    namespace detail { namespace fahey
    {

            static const double tolerance = 1e-6;

            template <typename T, typename Parameters>
            struct base_fahey_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = tan(0.5 * lp_lat);
                    xy_y = 1.819152 * xy_x;
                    xy_x = 0.819152 * lp_lon * asqrt(1 - xy_x * xy_x);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    xy_y /= 1.819152;
                    lp_lat = 2. * atan(xy_y);
                    xy_y = 1. - xy_y * xy_y;
                    lp_lon = fabs(xy_y) < tolerance ? 0. : xy_x / (0.819152 * sqrt(xy_y));
                }

                static inline std::string get_name()
                {
                    return "fahey_spheroid";
                }

            };

            // Fahey
            template <typename Parameters>
            inline void setup_fahey(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::fahey
    #endif // doxygen

    /*!
        \brief Fahey projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_fahey.gif
    */
    template <typename T, typename Parameters>
    struct fahey_spheroid : public detail::fahey::base_fahey_spheroid<T, Parameters>
    {
        template <typename Params>
        inline fahey_spheroid(Params const& , Parameters & par)
        {
            detail::fahey::setup_fahey(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_fahey, fahey_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(fahey_entry, fahey_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(fahey_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(fahey, fahey_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_FAHEY_HPP


/* fahey.hpp
qvs7XFPseF1HiIUz4Jp6Gzj3fSqC2l94h1IdPIMUM24PXIWlZF9uhavXAbL3FqpvO+HqciVeMQ8gxH2T4XruU3Apomo1Zim1H1RrY1tQfXsRrjN2kj14E6+X/gF+xQR7llJ0YQH1/yhZM6pJn9dT/X2M7L0H3gaK98w9CHEPdbsHUNXY/BW152/C9THpS3+y2fs1uDpTsDvvIns1ndrftyykL1Q/PiN79T7Vt8lAnPk16B4fA5f3T6x+UP7FgHgvFW2nj0GXSClqU0ztx1QgsqLAYCuJ1no92XuS/jpSwvIBVL6ryD5Tssa/QPlHXZzJLal9o2ofdZDqRw7VNwq7jtJ75dlk/+aRPTgE1+AHqb9rQeRF1PG6v8ICfg54q85EiPdJltnUQvycRvaZatnijXgtoshvJMSfp5O9GkPjDxqnNCer980w6k9OpP4fdUTejo4CPxJ881jqP9vJvtwEusJDVB5LiB+1Aeuov5ZVC8SMr6l/SohdL1H79gAY5BWQfAPx6kr6V5GEEN1ZfygVr+mfUf5RvUwhnfxkB+K4sydetVT6c0mRPiSplrwEuiMkc95YeL+kgcQq4vcR2dhD1GX6YgFez1B2zuliEe2l70Nqj9pS+/t3ko+SUNc2Bvp8BkSb+QwkKGoFRIuRVB7TAfuJ1Od9MgXbXgSi580kH3UwtlNP4ZfP8BpOQ54OVPe3Uto+zMPrjhoaz3xE9mUvXi9cQvJdgrCxRPL+UMS7+lKy9++SPpOFm0/twrVkLe68B95bs0EX3xmwS7dR/+8o9TeWUXtOynXmXLyO0hDvnP14uSYC8S2VzM+kp8vvofbtY+oPkaJfSEktaQfXjBl4XeSh8oij8QfZtR1URu81IMRIakjH+0G8YDUQF1NEd1PR/u15vAq603ghjuxzU7y+uw3EOZfgdVMs2edKGn/kRIFfE3hbkC1+ZQuNj6hapdIQ1L4U3kdWg+4BknnnG+C3nmReR934W200nvmU+s8HqX6sBOwtB7Ceb0m+f5B8n5O9uhH8un8NVtffD9cjw0D3B8qwFGruesXj9XoO2ZddZJ9pvHVXNTgvIS3+rC8QC1dS/s2j8riF8q8S2N1DKL1jSF+mWSm9lH8UwofR9tZTz6nn1HPqOfWcek49p55Tz6nn1HPqOfWcek49p57wn+yK7NRkZ8XQ1ERnRU6qrRIzRZpn1l6/39l5Z112ahcND75p9HWWzkjN1wpjMmq86y3wunNSR3nOfClac4JJptPNXszjqLZrkmD3i9FaNnAFTvfQ1HyCOTy5u/1+kKUCksohy30MkoIoUjTX+fSx2sssiIacEfayrzTujLSXHRbOGHtZHAi8bTlVqjY7ypsIN5OktChemzacOd2OxIhsHlFmRVYigzGPe0B8D2fitHQGqXOwLUIihM1fI+htXMBJyBPKEPCXESRp03IRbxetcEDGFs8l2LGCFKQLBskseERWUg/ApqUxKCDpFc7kxqJogih8g6vjVNYtxVS6L6s6VgHuI0B6dbwClABAxUNS+VobEPkCYQUEuZzGoW8A6qasKN2ct2nrf8ITUv+O7pH6l2Lh+pcq9LBLgB5uVHq4aO1x9HDE2mA9fOoLrnWApHBIOy+DpCGKNJv9rsuI/xj4nfMSsrb6/e6ykuQ/ABRR699JKkgqd06jKpfy61Tulz3HUbltzX6tyi1EFL5bDBqW/jw07BqDDp5BgAEGzWoKAJUIpDLr4vdrOCIiUBc/FQihi6kc2vd5pospTBfnv5kBJHL2ge6a9iT+X+5Ofv7vhXt7d+0/ctrToLqZpLr9vmKqS0l0ejbaWfmkZLN0IulOnustkCFk/kRVzDxGVcwB6xRWSfQ=
*/
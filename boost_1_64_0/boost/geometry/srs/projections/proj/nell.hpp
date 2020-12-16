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

#ifndef BOOST_GEOMETRY_PROJECTIONS_NELL_HPP
#define BOOST_GEOMETRY_PROJECTIONS_NELL_HPP

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
    namespace detail { namespace nell
    {

            static const int max_iter = 10;
            static const double loop_tol = 1e-7;

            template <typename T, typename Parameters>
            struct base_nell_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T k, V;
                    int i;

                    k = 2. * sin(lp_lat);
                    V = lp_lat * lp_lat;
                    lp_lat *= 1.00371 + V * (-0.0935382 + V * -0.011412);
                    for (i = max_iter; i ; --i) {
                        lp_lat -= V = (lp_lat + sin(lp_lat) - k) /
                            (1. + cos(lp_lat));
                        if (fabs(V) < loop_tol)
                            break;
                    }
                    xy_x = 0.5 * lp_lon * (1. + cos(lp_lat));
                    xy_y = lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lon = 2. * xy_x / (1. + cos(xy_y));
                    lp_lat = aasin(0.5 * (xy_y + sin(xy_y)));
                }

                static inline std::string get_name()
                {
                    return "nell_spheroid";
                }

            };

            // Nell
            template <typename Parameters>
            inline void setup_nell(Parameters& par)
            {
                par.es = 0;
            }

    }} // namespace detail::nell
    #endif // doxygen

    /*!
        \brief Nell projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_nell.gif
    */
    template <typename T, typename Parameters>
    struct nell_spheroid : public detail::nell::base_nell_spheroid<T, Parameters>
    {
        template <typename Params>
        inline nell_spheroid(Params const& , Parameters & par)
        {
            detail::nell::setup_nell(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_nell, nell_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(nell_entry, nell_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(nell_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(nell, nell_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_NELL_HPP


/* nell.hpp
4eqOhO6/DP65HFyoN4rVeyqgtLrHnQHN7uBH3EP7cfubeQW3P2j20F7XnN5dez3iCiH1agEVnwA5ptV9zemcvbpJZxLQrW+8qCNRN2mm8I09RUsj1+b3vy5XR6V7e5P4PG0uis+pKD6fUreN/jROc4iJdhr2q4jyhZfLTY3Xfyp2Zko2ojgvJdlmbNw0Ac9EOd3xnsgnLpOmb4k07Y9AGeWrA41y0NkJOKUJsgIBd9BaWCWeWLUjjX0R8/r3MvN7QHlEVW58ROk+C7/8UsVXtz6bg4X5MBbmOuP+71jaQq1MiVztEbHDHPsJiv2kNfY0jj08OTZkB7yN7M3mtUC2/uZ4rdvsdfslzTrrK2XRB3hm5482Yqsc2taYIxbCOYWNDQ5ntw+Fpe6/BZg2UZEPkff4/bGyzuwlP3Opqr1yR2Qmbn8KvabAvLAPfy4KF+DPJeG8+LHYVCrp/t8Vl3QkYq9nKOWMSoBd/S2AbQUYDPy/gx9BrDAKf3W6D52oO3mV98Y6YRiqEETVUWX8am/7b+jV3hr44Vd7qVnW4oZULAz4Jr86/sfd28YGBGHpxGZKNGFpsqFItvbYaIOCDykebfKnUvRJiv90SbRgwIoTChDCThNC7I+GJ5iEHSTsh0wIsXtd5gPsZ+4Crm42witiSw1PZewaw7MgdrHh+VZsruEJx84wPFWxycpTW093HQx/A/qHGMjVsb6GpyamGZi1DvFssMpMtFYDb+/NaFNbAkc2NiAwCqBYKzsqqCdAaKPGPQHWQRK9SKEXxdbyQ3cVDhfa9yFXEB66w9njYggy1cr3pVfQxZjjCbpwoBmOkMaGtaruT1JkajFoPPC2KMtYAx1mTcWItx/+QTRnDWH7iaeYw4J9n8LeJgOEBBLWm6mcxiYFjG0MFUQBHPueTaR9z5PRZ1oQWYOKOVpx/FIOUMeTgJMN63E8FAMJd/F80HEoFSg5tihTEeUoQZ60eCpLsc7UUV1iVYOcKQ/f4HLsgL84/LXDn/tRl6Mf/B0JfyPhbzz8zYC/8+DvEvhbCH918Lf3EZcjA/Br4O8e+HsA/v4Af6fC39fg703AWQ9/P3vM5XgN/nzQ88fAXwm4r4O/OeB2DBkyxOnK0NyZWZ7sXr1zhvQZQl+u19e3X390DcgbOKSz7zA7YP4ge+TDBxcc8exX36H5ksbHBd802XSuzcmgDRfLaIkwuRfib1wGXpshzf79T6YtzkXaXQ6aFvde3uVkt7QBx8MGm/2yjRXJ5Eq9j8H2AvwLswveIAf6ZzQI+unlv8Im/9IyaYAhvdPNO35Jo7jG9MWAW8Q6VyfgjzM8GadPd/ho+rR4Jk6fXsTp00q1EaCN4OkTjOSwqP7dd4W80JfNARkxgKHPKugVczoO4HDaNF+c+w3z+7rumMcl9WPdN8s30MqijSGyloS22RLwYZG/PVJq7bljLwD3fJwDyk8vZNPuxH1ldLXO+VdYEN0xXHOkqPYpFacqAOt1J2gMMBrNQGg0ptOlHFZaDOrTLwSWGRUVFuTO50YnHZ2M0szXgW4136W5EliWidZiojshUUPd6N3VBrJP32H4GvIR+fFzcC2XFx5hEGnHFK++nfJ7kQm+C+GX3mHo4+sAMGfZlwEIAyEFztHHZwNpEbQe0/rDSNQu/yeX5Jwz3CpiACOeEcDQzzm02BRajKHHU+h+Dj3cFKq7INQLoRIQIi5GILqrF6HHT5e6Ze8dewjm5V/UZ1IlqiMDgXJ317zcEGadt3QZHyJgS9jSRXgVhneb/mEp6Qc9tgyo+NYItW2YjE14MH9Luu8zc2Ld5fc+R9f5XZcaniSUC79uCGXug1IOnzVCLe/t6UdrHSqf9uE=
*/
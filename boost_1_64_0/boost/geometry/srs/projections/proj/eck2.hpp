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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ECK2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ECK2_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace eck2
    {

            static const double FXC = 0.46065886596178063902;
            static const double FYC = 1.44720250911653531871;
            //static const double C13 = 0.33333333333333333333;
            static const double one_plus_eps = 1.0000001;

            template <typename T, typename Parameters>
            struct base_eck2_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = FXC * lp_lon * (xy_y = sqrt(4. - 3. * sin(fabs(lp_lat))));
                    xy_y = FYC * (2. - xy_y);
                    if ( lp_lat < 0.) xy_y = -xy_y;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T C13 = detail::third<T>();

                    lp_lon = xy_x / (FXC * ( lp_lat = 2. - fabs(xy_y) / FYC) );
                    lp_lat = (4. - lp_lat * lp_lat) * C13;
                    if (fabs(lp_lat) >= 1.) {
                        if (fabs(lp_lat) > one_plus_eps)
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        else
                            lp_lat = lp_lat < 0. ? -half_pi : half_pi;
                    } else
                        lp_lat = asin(lp_lat);
                    if (xy_y < 0)
                        lp_lat = -lp_lat;
                }

                static inline std::string get_name()
                {
                    return "eck2_spheroid";
                }

            };

            // Eckert II
            template <typename Parameters>
            inline void setup_eck2(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::eck2
    #endif // doxygen

    /*!
        \brief Eckert II projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck2.gif
    */
    template <typename T, typename Parameters>
    struct eck2_spheroid : public detail::eck2::base_eck2_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck2_spheroid(Params const& , Parameters & par)
        {
            detail::eck2::setup_eck2(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck2, eck2_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck2_entry, eck2_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eck2_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck2, eck2_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ECK2_HPP


/* eck2.hpp
8B1z1g205QzKXbQTdH/ZUwdXcf6tH32YTVvK0e3I7KxaRz3yIvvggB2M/pn2NeN4s6eOQD+UMxfeeiu2I+tPdzawzjXDVfs+TLkjyFeN3kVfJ6XDq32gz9+ZI5Cz21731Ib9XGjsqeWf8g6BAxx1AHZOPbx+80PMdU866qwG5t3zufcUnZR7BbphMvZYJboaedrwW8qhbw+RHpzDXHOuo2bQz4wjsAE95vb3kLtkdE0v7BNk+HnG6lnGzDmUfqAX+l6GjfUFeyAo874fHFXHYb+/boAPhzNPUsbRVzvqmhpskPW0fTHy+nfsDHit4GfmBsbyZ+RjNPbeGuySy5nf3t/LVX+ZxTuJmSv2W6SQbWQBmbwJOX6eOejUedi3yMR2f3LUmA/YA9kF3YU+LkZ3dUE+ytDV350Hj5bT3nPg7W7Mt9ibK7Ath60EfxA6/GrmxwfQL9gUn27vqE9Yk1s10lFrX4Le2H4HcmD+MA5zrJ3iqfeOpw/QdU/KziHtRdqHdCvPhu5PXezhGE5Z545w1d9K2Mm0lHaMYA6cjZ3+HPr3OvaCYj/NuwY/4RJoRHu3L0LXr8BuHueoBOzfG+9Ghs5nPmaer57oqprDXNUV2m76g6Nu+5F5krnyshuZLx5A5x6GLeuikxjfY4vA4ffsm+H3A5Hph5knfTsmgd2LufhNPeBtdPT4Z6D1GY6qgp8fwvargCdnHMe+ugL0yMHYW44LEDudfr/5JfLejXn2JO6huwVd7tP0PvQr4/D+idy5tIerjmWtsgba34kdtv8NrhrCnJv+gG+7OGqZb7Nu8lTFXEfdUeeqnsjtcxchW9gkV9/nqpfwFw6DTzbWIn/ML48g8y+iB5f80VEfbYU87sfciw21cwK8MRO5PAT7nbH74+/hVcq9JAkbLc5RMxcyDgc76v6DPDUK3hib7alL9/XUWa6nytKwxxifJYzDfX9HF3Wnn/Brz53gIWz9Y+jTUaQTSOtIb5Mexq7rje21TSYy9AY0OQHb5w/o6m7IIz7Np7TzxFnQYIFSK/oxByDDK4/C3mJcttmOvxnn+XmM0XbMYfDUvsjMmkM81fiEp45CVp/8ljkiAX+LsZ/c11X37Eyb+lLHvejlRlfdep6jVl2NLYVfMu/3DrzlqonUMe8bT/18A/PuA9jqvsx/jW2GDXD61Yr5lnO5bIrNOwOZmeOqn5ln6plTv2TuGPyzp5YezdyYAc8jayndkEl4cBHj+AJ65NpXXfVQCbbgNo7683OO+uBRfpN/m8XoI2yfeGzYQmj7DjK0mPGNx5a/8Az8HP/M4ypoPR67MIt5GptqV8o75zP4Dfts+hO0ET/HG0Wd8POJDzAeN2P7D6ed0zz1IH7YWd8iW8zJxW946sJN8PQHyAN23m83Mnd8yFh+TJ97QfsRyHYifEM/UJOq9hP8BnjwK+yJSXs56srV2L3FzJv0sff+nMfEL3wKn66BMUve0VXZ+Z7aiL68C1v+2cfQIyc66q/Qbfd54P3VUbuix9d97anfD2EOeZc5ZS76Aput4DH4YwE6CP+j8Xv0/SvMu9gm3zZ6KmsOecl/KLq64mlkBft2YwG2OP7LTn+gvbRvPTrPfRNevMVVJV8gwzm0IdeDqdAzB6GHN7lqj4Pow5OuWow+/hjef7KUufVWVx15NTSZ5KgzmMf3eAFb5lvk+xnu0XoOG+BTRx3NnPH62YztSE/tku+oInydnxz0xp+QYeibztg9UMx4IlNXVTEvvYkNif2++nu+8Rkz0L31+KzraF/lSHg0zVMTnmUevRS+m8l8VwdvrYGP4OFLF2HD/5k5gGc/nOaonWcjy/gH12N3zqL/X8/AX4SH38POH7Q=
*/
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

// Purpose:  Stub projection for geocentric.  The transformation isn't
//           really done here since this code is 2D.  The real transformation
//           is handled by pj_transform.c.
// Author:   Frank Warmerdam, warmerdam@pobox.com
// Copyright (c) 2002, Frank Warmerdam

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace geocent
    {

            template <typename T, typename Parameters>
            struct base_geocent_other
            {
                // FORWARD(forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                        xy_x = lp_lon;
                        xy_y = lp_lat;
                }

                // INVERSE(inverse)
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                        lp_lat = xy_y;
                        lp_lon = xy_x;
                }

                static inline std::string get_name()
                {
                    return "geocent_other";
                }

            };

            // Geocentric
            template <typename Parameters>
            inline void setup_geocent(Parameters& par)
            {
                par.is_geocent = true;
                par.x0 = 0.0;
                par.y0 = 0.0;
            }

    }} // namespace detail::geocent
    #endif // doxygen

    /*!
        \brief Geocentric projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Example
        \image html ex_geocent.gif
    */
    template <typename T, typename Parameters>
    struct geocent_other : public detail::geocent::base_geocent_other<T, Parameters>
    {
        template <typename Params>
        inline geocent_other(Params const& , Parameters & par)
        {
            detail::geocent::setup_geocent(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_geocent, geocent_other)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(geocent_entry, geocent_other)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(geocent_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(geocent, geocent_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GEOCENT_HPP


/* geocent.hpp
etDNEMC7xMJZF5Bp6Kr6vC/8mfq8s05XqC5iOaSYraYAy9YCPF/BpYZO2ZRUZkwU5TjgewE6s1O1zchh0Z9Fn7oj4hf9X7iEiWpiJE1jpLMDGFwjGfxdkwxSLdz2We1zWh3y+w1Zu1CW0o0V5fH4NoKyNY6KM6Ki5kcYdafek7sJc59aisHenrHZMFr8+VXMUsGTB485m3Pms7QlOAXWswgAMTq16KNTkdlF8w3G+fTaIIt+9N5ojW1vcbUMMuzpCMtX5xmLdEpHxlbP2DrIWbKZhsvhjspPPaeeU89/w5Nj3h/nrPTzZzaNeJKn0aQcm7KlRpRobNJDoZw21qfYFD5/PlM3q4ZNuuVQG6g2EaR7aLeKmAhMYu0kB59zGu/H8enJcOYDhYyhBAsU5eBGfRLUcy91xtEUZU7lMuiiLU8OU4ZA/vcL/jqrayL0VLLpBw7uF14MIfOz68aQ+ZkbETI/P2odVkyB6Rl+FV/2qH2Fp2ge64Y0ON2u1FFVicAcXOacR2sW8yiSQ0dp9tN1upttT6shTBrH9PSr6d4MwWQGLantl0wQJF/uvKHgcAOALYVqjfP6kZu2hvkEy28JS/4yAELLP/3o7yM/L+p+fw3Up55Wgz5ZlT4dbBlWKQfy/3JDIP+bjfwjFP/7w+Mfuv5vCKmva6yh6394MYVOT4sNhvq9mno0IobWcp3Xvk7je1Yt4UQSMj2r1hsiGWjlRsTBjEhLuTWX4oqFRuiRhM//ciP/vRYj/7YsE0VaEvn2pQ/WRoedYUHlX22IajYbtzdYWUyZhgyr3WkTeaYDHRYGcsc2qXfXnkCOHlueIUZ5vmXcGiKYPFeb5EkMIQ9JqYsUTGD9DQQOWV6PVxmE7qkZy6t1iPIqahDLVMdpzxy2Tcdaj04TsdLCmxia8BkWtimbYBUEqyghmJGqtJIg1mk38MXojHV+fyeNT9lfwUE3vKQGEt3EQOKlUrYWkm6OjsZXPQCd2soIZ1tNy1NDRhs/rTMNQsdb+PxfDA1CM+Gp7qvP/5WKKR2f9WSXucNZz/e8rOcfjd94Op9aAygDlVayBUF7mT0gIfgkWsRYPADO5iVDZ5NcDNehKRyayvP8PviyKuvZWF7QlROd58iqaB59aRFWoE0ZXVdMQ0L65zzyX1RF6eoSUCIpvEQCoKkV5SkBUNGWlSeGgKcDnqyie/t5mVf6tE0CA9RpR45i/vES5nEXf4ognbRiJldbTsCk5s7iQyIRvuaKG4sAs8qW37j8T/Qx1PLKlwy13AIPd7V7WdTm4+1HKOLhA7aNyHVylcks3z29njftfnGlsq0AcskyjW8UaRBCpHg8IPe9HMZCunH/14vhyZNM8jy7Jgx58pU8eeHKE3AeQZduIJdOntWhqUS5QbqZvWyOOLI1wHU6fQa6utOnyNWHPn9y3eC9TzNMdTg8u1eAG5TPJk+aeOepvW6fPM0Pj/lmekZGMXOWO5NM9xRjPpA6sqrCW1rfMM8FUfhc7umMT6knXYXqHRyKIiS99qWwCbtscuuHN8qf8fvDPLxxEk9lSls+YAvWZ89aZf/Shbz2l4s3QNh3uJKLBuTGihIChqArbeg9K9kIr+rNp8YIyWvH5Of8/hNpXw3yOQ3y6fa5xSpZ8fo/LV1XHYaLyAIqUYeXBDxAmWMBz6p8nG8+HGyJ4WmT9va2GdECUMdCaSfYRTjmfqupz6tEOVS7+CKpVGFbM5D0jG/LbMvWtKha9Y2VtVM36z3KKfiM9NDwwu4B8NQe5cR5dls+3Z3xLt+vtXAFT7TTuyrQAkQRH06NVSdOPkaSU0xurTPrT8kN7RSL2xEpgVmRDFpaFKnN7MQJNH+9MQCIoxw=
*/
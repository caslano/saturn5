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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GALL_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GALL_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace gall
    {

            static const double YF = 1.70710678118654752440;
            static const double XF = 0.70710678118654752440;
            static const double RYF = 0.58578643762690495119;
            static const double RXF = 1.41421356237309504880;

            template <typename T, typename Parameters>
            struct base_gall_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = XF * lp_lon;
                    xy_y = YF * tan(.5 * lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lon = RXF * xy_x;
                    lp_lat = 2. * atan(xy_y * RYF);
                }

                static inline std::string get_name()
                {
                    return "gall_spheroid";
                }

            };

            // Gall (Gall Stereographic)
            template <typename Parameters>
            inline void setup_gall(Parameters& par)
            {
                par.es = 0.0;
            }

    }} // namespace detail::gall
    #endif // doxygen

    /*!
        \brief Gall (Gall Stereographic) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_gall.gif
    */
    template <typename T, typename Parameters>
    struct gall_spheroid : public detail::gall::base_gall_spheroid<T, Parameters>
    {
        template <typename Params>
        inline gall_spheroid(Params const& , Parameters & par)
        {
            detail::gall::setup_gall(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_gall, gall_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(gall_entry, gall_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(gall_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(gall, gall_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GALL_HPP


/* gall.hpp
SnoTqHhqax4bJlmYeYlM9ddURKb63ofLXr3/DESevCms+NIovob31VRCur/lC21iKX/TNoWYPwvQkY08oOw/YnCSTW77OjUBcQWqBoFKa+IZoKKkXCTJUVc8V2OPMv2WN39FMRvSk8bFqm4lqlW6Zxhm1GSagvXdaUWgg++JTIjqucamOTM2OyvKUtOBqePTFGJeMF/W6wJ8WQ8/l42TilAdoQNzmdfzzBtgJj11XHvjKv14vM82Beinx6M1hZ+5jdf5IgU5DAhFXyzmIIuojpRuYH6tsCuZlzctrNOwqiN1GghePRKQqiRK/zhw55H1RWSSK7N/KCJh/S7AiyzSD49Fq2S4tU4ajgr30Y5C61k0n/NoLmXRRFhM0Rx9TEbzYYIpK4o0+5yVRKFRMit4p5/kX6zLv5sz/kcH1enRGS9XjGclAKE5eCIWE66KxEVu9lKQJwAhjns5x0dDcRyiOHZRoiqmENFZpMMcRfi3sVmGjC3+lqkxseDHZOCNe05qkcf+GGvYR6FsRmmzO1bTGVOO+fZR1tWJ8k6L10SUVfFcc5hGj0GoHHcN5zVvbup2Eq84kWZGeMY0sbJk/C2FkpFtTsbcR2UyxoEnRZ4w8xwKdDoPtJgFOtdcTFfRYUFPE2MJVfLJpEv1RBfLAVy6gAmTTcwTgKJ2Mw/ZYKHamrFFEvnns/ybtyC1El+VHq0Zpcd1GiE2GBF7eEKZzJ24zPvOIJn/Yk7o0kV0kqgJTXwxzq1cLMi5PEgVC3LIHKSAglgQpGQDi/Mo/nmoDB6qlIVymUP1pFBvxgFmMcr5hZ0lIDOr0ibSl2YxoNPtevpWGMM91ExPXy8ebXyo9G16hE5uIFpu5m6p0TDBGYk4KHRLCbToQJ6S/iL97UOln1ha4rgwKwjyc1ON1b79Igk1mgF5HUuCvWw+A8JeK8xBXnjTKchmY5DpHDGaEPVGRC1HOInPWAV9lkMvgK0fm+2uoVA7jaF8HN9cAU5vCaxM6lCe1Lfbhci9OXQet1UsaQdLlIUHuZoHWdQuRO4MpiBf2igIS5R1GgtyPQ+Sz4LcZ643Z1CQNTxIPTNccTSJ0gPJ4YEn8MCdWeA/mwPvWkgnu2whKt1VlB9oDskGzBW1r4LXPrRUHMY9aaxxx+QJlSCiaGVocNyJoSphucjfnSTCm3ZdF6dxUYvbhsjNi0jU+hhWccrF5Q+Y/uazdtQc+JoiIsJUcJjBVNpKMhX5XEne0kjgRiiGcvOPmA2c1sfMxe+3iNo6W9i/NiRqE3Ouzn0IoraLASzFmNLz47mmURYkWwwIZ4JeT21GRLcEPW/u5hGObRMib9pQhCujWUjGwVPYHB6xPpDLJuurTVlSvMbCCrtGb+oe5hFEsAjuN6eo+kFp0e83xmJvzqtug2YAnks2XNcZFlHF3FSNvu4FjDbb/arTvV0nKmNY//wajaU3YO7Pypa3AbHP+S7S0FHY97rfzyeaVS9h+wPRwa1g7IOGXszLr4fqXSxEuODMqWQ1oW8AImdeWeoCocnpFikPiQ96Nn9QsoER+EmBWNa+wrN2xWmUtfPNWXv9AzJrM6N0Q5vAFgKcEfVOdy3v9LvphQqZbV9njJ/LvwVrT3K61vG6FsG+ot/tIHNQ60nsRPJUcf5bWP44yiPjONJmQlqMSBPGKjFSnAgWg5Saj8Bej7SodFgURIawhh1CQqxBPCL+TemCh7IczhxC5DGgyONWpjwONhOFXQThUZ1QD+03AX3Zete2toEvRZdbTCQ6ARM8FImxFyAHw7dvjFa5ZpNpytEzJjjXckJnmSo+xaS0JoEyJqjlGHiS3TUWpbmx8Ay9j49kC2h4UaBxS+jntemaViE=
*/
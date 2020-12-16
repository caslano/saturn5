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

#ifndef BOOST_GEOMETRY_PROJECTIONS_MERC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MERC_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_msfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/pj_phi2.hpp>
#include <boost/geometry/srs/projections/impl/pj_tsfn.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace merc
    {

            static const double epsilon10 = 1.e-10;

            template <typename T, typename Parameters>
            struct base_merc_ellipsoid
            {
                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    if (fabs(fabs(lp_lat) - half_pi) <= epsilon10) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    xy_x = par.k0 * lp_lon;
                    xy_y = - par.k0 * log(pj_tsfn(lp_lat, sin(lp_lat), par.e));
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    if ((lp_lat = pj_phi2(exp(- xy_y / par.k0), par.e)) == HUGE_VAL) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    lp_lon = xy_x / par.k0;
                }

                static inline std::string get_name()
                {
                    return "merc_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_merc_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T fourth_pi = detail::fourth_pi<T>();

                    if (fabs(fabs(lp_lat) - half_pi) <= epsilon10) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    xy_x = par.k0 * lp_lon;
                    xy_y = par.k0 * log(tan(fourth_pi + .5 * lp_lat));
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    lp_lat = half_pi - 2. * atan(exp(-xy_y / par.k0));
                    lp_lon = xy_x / par.k0;
                }

                static inline std::string get_name()
                {
                    return "merc_spheroid";
                }

            };

            // Mercator
            template <typename Params, typename Parameters>
            inline void setup_merc(Params const& params, Parameters& par)
            {
                typedef typename Parameters::type calc_t;
                static const calc_t half_pi = detail::half_pi<calc_t>();

                calc_t phits=0.0;
                int is_phits;

                if( (is_phits = pj_param_r<srs::spar::lat_ts>(params, "lat_ts", srs::dpar::lat_ts, phits)) ) {
                    phits = fabs(phits);
                    if (phits >= half_pi)
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_ts_larger_than_90) );
                }
                if (par.es != 0.0) { /* ellipsoid */
                    if (is_phits)
                        par.k0 = pj_msfn(sin(phits), cos(phits), par.es);
                } else { /* sphere */
                    if (is_phits)
                        par.k0 = cos(phits);
                }
            }

    }} // namespace detail::merc
    #endif // doxygen

    /*!
        \brief Mercator projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
        \par Example
        \image html ex_merc.gif
    */
    template <typename T, typename Parameters>
    struct merc_ellipsoid : public detail::merc::base_merc_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline merc_ellipsoid(Params const& params, Parameters & par)
        {
            detail::merc::setup_merc(params, par);
        }
    };

    /*!
        \brief Mercator projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
        \par Example
        \image html ex_merc.gif
    */
    template <typename T, typename Parameters>
    struct merc_spheroid : public detail::merc::base_merc_spheroid<T, Parameters>
    {
        template <typename Params>
        inline merc_spheroid(Params const& params, Parameters & par)
        {
            detail::merc::setup_merc(params, par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_merc, merc_spheroid, merc_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(merc_entry, merc_spheroid, merc_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(merc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(merc, merc_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MERC_HPP


/* merc.hpp
Z/LvWZZ/b+zH/c6GB4T469oe1DqOpO4pyu5eQkaE6ACYzaDWfM9ykhM+0fQqlvU1RWkbtvx79B5MkmGsIECxC6R3UtuVvoMjBGdzvoiwBhcFFAXrS15WiQBd+5Cw4siK7APZDVNDE0IoX2LkmzCYhNTfl+kyUEWJEkvZEsOHNzJ6YCwyjc8m//k2+fdY8+8xMe9JL3fdl1C+yr+KAj6AZqsCkTdXCP2Q5J/7e8fWDmGVJacDmibYkv8Z9KamO6U9rDt+ZrGH1YPHZM32P7aa9u/L1nZv/8OM/+4ae3xGncSoerPE6tz+zdbk84e1a3piH+SFtuT44TvSPL9YC1EN+yB3pnd+MT8lvb+sTjO9gDm9l+/otrzbW034C1anx9+W1mT+butRedalxPekm7+QmV/XHWnZWxnAcUzWeW4T8brdT7CIKOiU8J9jxOZO0+OO9ZOnKT1lrU1tDYiLuIthQEHNFDtlyijAx8Pv4uNwuGP842HkMFQp2bhvJIs8oPy0pYePwafoExmX0eJPEeOSLzi+WkfvtPcSrswIiQIeoKVhZ0OzqMXwF/MAP1ANaiFa6vHp+gDlDqnwctNbcOgbD76IW1iNAUTrE7P7YbjnFHxUDFJBYm48V/p95KfJp0opIFU2IT/rMa0aMqUQhN2f8fUEgWvyNfhkjAZ55BcJBwmMAbgvPLQtupm0EM4FJCBSS6f2BQIlX2wTK6wTGavBglUAWA1mrN6MtcqC5eeL0AbWO/sJay2bVhBYhcD2Wmb7KQhXF5aPBAk+2PBRMxpaMpYIfd+M6Lcg+i2ICwFRVLwzUkTlhzp4ET8q+hfTM5c8MflFu7hjCZcwaVKPN2NFTC1SqGKGByTHXAgxYyMN7AxTOuGUdE7dZ6RDtzLxKoFsml2m0xtixn5vYLu8yx9TdzxRETfis7SbovhA1a5oKioHdRWjOJJraXnFZsbILYd+RZfpGEN/gKcPXabEQ7/1ZmpsJxiYkf1PamjL/idNqX11EydF3tm9f9zCIwOs7/ZtE0qDleQaCa4qchWBq5pcY83qk36WU+DyiNXMKDVJ9MtbohTY4lEKrX7ZwPzxZ8QWhKEOi6JqPGwyrKBLKKwVG4Jp2Q+m49aocwBE85nANzI4H8ADTOAqBhdgbk3g8xjsB3ABsAstM08MJj4lYhaCIIKwARw2EsIGGAKPw/I5rAjnqCpsAocVcNhYCCtQYUdCmImN7ae6HWxsR+jwOq2FFPsIhA6D4K73v2udbdNeeGR/5knLAAm/hWoAx0qEf8GF8gGqEXVEIZOFQp0WhxfTKBbuxfKKzCa36NNuoml3Xx7ig2PZzIgrfr8c88thCBqKZXqShMwFkUGQQgmpgNGFIP0kpBJGEoTAAIEW8ImVZD1RnxCchTiyjukEKyyxRiJWH8CS9z34UjkL28YBTisYRnUnSbBUcH4qGKAkP43pUOzH0B6oe3lXTkcdYL+4HWQlgxhO78pnHQaGkzC4rW30G3acAAY3j3183cxadaxHjJW3eA5BQaeYeVOU8J5yIVDyK0r5HD8NTF98Db1PrbtSkMHlT2wNzd9qJS0Vm1OL01oOTEScXDtTY3GwOsR29nS++J/2mfZzix83n7fk8yEet9hsMngcL4/PIJCLQC4ETYqfRCAngDJhXn58/BjwD8PSISQPIuXH+wKQp0jwLi2AxIN86ewAd/8+Bm8XXddsUeBvs8gI1hvTNJOisbf+Fow2YTfNAAgmBCWR4D7Lu0qTXr8T9+FCwtxYn+fAq9+2J2Go2tccIbbUNmBQ68dAE+em3Ebi3uQEUBsf3hzB3yq1f3tJhgwJeyiEmT4zQ0xazOegp052gy0mzXQGyJOoSpE=
*/
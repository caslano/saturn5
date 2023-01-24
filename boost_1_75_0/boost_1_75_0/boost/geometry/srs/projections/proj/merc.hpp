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
bJ6WfXUNowsbWU505ofKGc/hBXQCkm5MP7F7CmgdUlLPBn7qc9I4l0gYx505Y2tO1jmpOglyEI2nLRK2YrhRFGlmNOG7B9/YKKcJdtKukZ2ck11jDL1hAb5egc7VDuD3lPS3iE5PQR+QfYXeHcY6S0Ol0tJo3hi9TNhT6yzEjoeLnDSIHEsP2LYbhHhIo0ICQ+FGFV5Ekgcfy4nPSp08yB693p5ObrwVS7CHSmkfMZFMB4gUjsXOw6dwRXjG1t9k746lv2N+OKln8MGNEg6d5/GP6oHt/Eu1gepk1NvQmr2GB8MX8XdB4egis9OFkUIKq9PCFGFvH6r3+i2xCSne7BamXcJQ3SYTP6Rsq88VCUrLWGfOIS06WbUdvGThVIEvXTG8y2x9To5Wro704VR3L17EjnqjcpPDnpWRVO7X9/FtwqtPahpXddz5pTU5AjykRNFk4cPGKl4f3dOWilZbS2ljwBWTdVmpJSrFnhrIXTv92GYKQBBJlEV5VU9v6YWMxEqf7uClTkGQgCiLa9kql8lycmW+qFW7KKdEc+2FR/LfU1x9iwC51khqGjVIbz0Nfrf2yzf2QPY34VY/kdPHziMp10OrORDTeSlF+Qx51+Q/U1ztyROzCnUJl729dT82u+C14i22nSxY3DHfNzQgbHFIlYjkFS92WMre19K5ksncfyzHcA/WScVJikjw7moLjzQS5CtpJnh2SV7b
*/
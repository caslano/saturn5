// Boost.Geometry - gis-projections (based on PROJ4)

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019, 2022.
// Modifications copyright (c) 2017-2022, Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle.
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

    /*!
        \brief Web Mercator projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
    */
    template <typename T, typename Parameters>
    struct webmerc_spheroid : public detail::merc::base_merc_spheroid<T, Parameters>
    {
        template <typename Params>
        inline webmerc_spheroid(Params const&, Parameters & par)
        {
            par.k0 = 1;
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_merc, merc_spheroid, 
            merc_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_webmerc,
            webmerc_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(merc_entry, merc_spheroid, 
            merc_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(webmerc_entry, webmerc_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(merc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(merc, merc_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(webmerc, webmerc_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MERC_HPP

/* merc.hpp
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
*/
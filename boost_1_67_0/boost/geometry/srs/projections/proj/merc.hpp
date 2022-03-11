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
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
*/
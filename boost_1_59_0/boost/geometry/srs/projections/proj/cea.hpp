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

#ifndef BOOST_GEOMETRY_PROJECTIONS_CEA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CEA_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_auth.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/pj_qsfn.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace cea
    {

            static const double epsilon = 1e-10;

            template <typename T>
            struct par_cea
            {
                T qp;
                detail::apa<T> apa;
            };

            template <typename T, typename Parameters>
            struct base_cea_ellipsoid
            {
                par_cea<T> m_proj_parm;

                // FORWARD(e_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = par.k0 * lp_lon;
                    xy_y = .5 * pj_qsfn(sin(lp_lat), par.e, par.one_es) / par.k0;
                }

                // INVERSE(e_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = pj_authlat(asin( 2. * xy_y * par.k0 / this->m_proj_parm.qp), this->m_proj_parm.apa);
                    lp_lon = xy_x / par.k0;
                }

                static inline std::string get_name()
                {
                    return "cea_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_cea_spheroid
            {
                par_cea<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = par.k0 * lp_lon;
                    xy_y = sin(lp_lat) / par.k0;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T t;

                    if ((t = fabs(xy_y *= par.k0)) - epsilon <= 1.) {
                        if (t >= 1.)
                            lp_lat = xy_y < 0. ? -half_pi : half_pi;
                        else
                            lp_lat = asin(xy_y);
                        lp_lon = xy_x / par.k0;
                    } else
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                }

                static inline std::string get_name()
                {
                    return "cea_spheroid";
                }

            };

            // Equal Area Cylindrical
            template <typename Params, typename Parameters, typename T>
            inline void setup_cea(Params const& params, Parameters& par, par_cea<T>& proj_parm)
            {
                T t = 0;

                if (pj_param_r<srs::spar::lat_ts>(params, "lat_ts", srs::dpar::lat_ts, t)) {
                    par.k0 = cos(t);
                    if (par.k0 < 0.) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_ts_larger_than_90) );
                    }
                }
                if (par.es != 0.0) {
                    t = sin(t);
                    par.k0 /= sqrt(1. - par.es * t * t);
                    par.e = sqrt(par.es);
                    proj_parm.apa = pj_authset<T>(par.es);

                    proj_parm.qp = pj_qsfn(T(1), par.e, par.one_es);
                }
            }

    }} // namespace detail::cea
    #endif // doxygen

    /*!
        \brief Equal Area Cylindrical projection
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
        \image html ex_cea.gif
    */
    template <typename T, typename Parameters>
    struct cea_ellipsoid : public detail::cea::base_cea_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline cea_ellipsoid(Params const& params, Parameters & par)
        {
            detail::cea::setup_cea(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Equal Area Cylindrical projection
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
        \image html ex_cea.gif
    */
    template <typename T, typename Parameters>
    struct cea_spheroid : public detail::cea::base_cea_spheroid<T, Parameters>
    {
        template <typename Params>
        inline cea_spheroid(Params const& params, Parameters & par)
        {
            detail::cea::setup_cea(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_cea, cea_spheroid, cea_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(cea_entry, cea_spheroid, cea_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(cea_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(cea, cea_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_CEA_HPP


/* cea.hpp
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
*/
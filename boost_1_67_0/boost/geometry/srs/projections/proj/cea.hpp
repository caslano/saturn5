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
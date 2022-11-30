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

#ifndef BOOST_GEOMETRY_PROJECTIONS_BONNE_HPP
#define BOOST_GEOMETRY_PROJECTIONS_BONNE_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_mlfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/math/special_functions/hypot.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace bonne
    {

            static const double epsilon10 = 1e-10;

            template <typename T>
            struct par_bonne
            {
                T phi1;
                T cphi1;
                T am1;
                T m1;
                detail::en<T> en;
            };

            template <typename T, typename Parameters>
            struct base_bonne_ellipsoid
            {
                par_bonne<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T rh, E, c;

                    rh = this->m_proj_parm.am1 + this->m_proj_parm.m1 - pj_mlfn(lp_lat, E = sin(lp_lat), c = cos(lp_lat), this->m_proj_parm.en);
                    E = c * lp_lon / (rh * sqrt(1. - par.es * E * E));
                    xy_x = rh * sin(E);
                    xy_y = this->m_proj_parm.am1 - rh * cos(E);
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T s, rh;

                    rh = boost::math::hypot(xy_x, xy_y = this->m_proj_parm.am1 - xy_y);
                    lp_lat = pj_inv_mlfn(this->m_proj_parm.am1 + this->m_proj_parm.m1 - rh, par.es, this->m_proj_parm.en);
                    if ((s = fabs(lp_lat)) < half_pi) {
                        s = sin(lp_lat);
                        lp_lon = rh * atan2(xy_x, xy_y) *
                           sqrt(1. - par.es * s * s) / cos(lp_lat);
                    } else if (fabs(s - half_pi) <= epsilon10)
                        lp_lon = 0.;
                    else
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                }

                static inline std::string get_name()
                {
                    return "bonne_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_bonne_spheroid
            {
                par_bonne<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T E, rh;

                    rh = this->m_proj_parm.cphi1 + this->m_proj_parm.phi1 - lp_lat;
                    if (fabs(rh) > epsilon10) {
                        xy_x = rh * sin(E = lp_lon * cos(lp_lat) / rh);
                        xy_y = this->m_proj_parm.cphi1 - rh * cos(E);
                    } else
                        xy_x = xy_y = 0.;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T rh;

                    rh = boost::math::hypot(xy_x, xy_y = this->m_proj_parm.cphi1 - xy_y);
                    lp_lat = this->m_proj_parm.cphi1 + this->m_proj_parm.phi1 - rh;
                    if (fabs(lp_lat) > half_pi) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    if (fabs(fabs(lp_lat) - half_pi) <= epsilon10)
                        lp_lon = 0.;
                    else
                        lp_lon = rh * atan2(xy_x, xy_y) / cos(lp_lat);
                }

                static inline std::string get_name()
                {
                    return "bonne_spheroid";
                }

            };

            // Bonne (Werner lat_1=90)
            template <typename Params, typename Parameters, typename T>
            inline void setup_bonne(Params const& params, Parameters const& par, par_bonne<T>& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();

                T c;

                proj_parm.phi1 = pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1);
                if (fabs(proj_parm.phi1) < epsilon10)
                    BOOST_THROW_EXCEPTION( projection_exception(error_lat1_is_zero) );

                if (par.es != 0.0) {
                    proj_parm.en = pj_enfn<T>(par.es);
                    proj_parm.m1 = pj_mlfn(proj_parm.phi1, proj_parm.am1 = sin(proj_parm.phi1),
                        c = cos(proj_parm.phi1), proj_parm.en);
                    proj_parm.am1 = c / (sqrt(1. - par.es * proj_parm.am1 * proj_parm.am1) * proj_parm.am1);
                } else {
                    if (fabs(proj_parm.phi1) + epsilon10 >= half_pi)
                        proj_parm.cphi1 = 0.;
                    else
                        proj_parm.cphi1 = 1. / tan(proj_parm.phi1);
                }
            }

    }} // namespace detail::bonne
    #endif // doxygen

    /*!
        \brief Bonne (Werner lat_1=90) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
        \par Example
        \image html ex_bonne.gif
    */
    template <typename T, typename Parameters>
    struct bonne_ellipsoid : public detail::bonne::base_bonne_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline bonne_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::bonne::setup_bonne(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Bonne (Werner lat_1=90) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
        \par Example
        \image html ex_bonne.gif
    */
    template <typename T, typename Parameters>
    struct bonne_spheroid : public detail::bonne::base_bonne_spheroid<T, Parameters>
    {
        template <typename Params>
        inline bonne_spheroid(Params const& params, Parameters const& par)
        {
            detail::bonne::setup_bonne(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_bonne, bonne_spheroid, bonne_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(bonne_entry, bonne_spheroid, bonne_ellipsoid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(bonne_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(bonne, bonne_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_BONNE_HPP


/* bonne.hpp
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
*/
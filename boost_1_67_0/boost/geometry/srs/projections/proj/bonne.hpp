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
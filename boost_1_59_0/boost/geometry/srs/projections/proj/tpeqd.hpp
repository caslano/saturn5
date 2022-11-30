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

#ifndef BOOST_GEOMETRY_PROJECTIONS_TPEQD_HPP
#define BOOST_GEOMETRY_PROJECTIONS_TPEQD_HPP

#include <boost/geometry/util/math.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/srs/projections/impl/aasincos.hpp>
#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace tpeqd
    {
            template <typename T>
            struct par_tpeqd
            {
                T cp1, sp1, cp2, sp2, ccs, cs, sc, r2z0, z02, dlam2;
                T hz0, thz0, rhshz0, ca, sa, lp, lamc;
            };

            template <typename T, typename Parameters>
            struct base_tpeqd_spheroid
            {
                par_tpeqd<T> m_proj_parm;

                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T t, z1, z2, dl1, dl2, sp, cp;

                    sp = sin(lp_lat);
                    cp = cos(lp_lat);
                    z1 = aacos(this->m_proj_parm.sp1 * sp + this->m_proj_parm.cp1 * cp * cos(dl1 = lp_lon + this->m_proj_parm.dlam2));
                    z2 = aacos(this->m_proj_parm.sp2 * sp + this->m_proj_parm.cp2 * cp * cos(dl2 = lp_lon - this->m_proj_parm.dlam2));
                    z1 *= z1;
                    z2 *= z2;

                    xy_x = this->m_proj_parm.r2z0 * (t = z1 - z2);
                    t = this->m_proj_parm.z02 - t;
                    xy_y = this->m_proj_parm.r2z0 * asqrt(4. * this->m_proj_parm.z02 * z2 - t * t);
                    if ((this->m_proj_parm.ccs * sp - cp * (this->m_proj_parm.cs * sin(dl1) - this->m_proj_parm.sc * sin(dl2))) < 0.)
                        xy_y = -xy_y;
                }

                // INVERSE(s_inverse)  sphere
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T cz1, cz2, s, d, cp, sp;

                    cz1 = cos(boost::math::hypot(xy_y, xy_x + this->m_proj_parm.hz0));
                    cz2 = cos(boost::math::hypot(xy_y, xy_x - this->m_proj_parm.hz0));
                    s = cz1 + cz2;
                    d = cz1 - cz2;
                    lp_lon = - atan2(d, (s * this->m_proj_parm.thz0));
                    lp_lat = aacos(boost::math::hypot(this->m_proj_parm.thz0 * s, d) * this->m_proj_parm.rhshz0);
                    if ( xy_y < 0. )
                        lp_lat = - lp_lat;
                    /* lam--phi now in system relative to P1--P2 base equator */
                    sp = sin(lp_lat);
                    cp = cos(lp_lat);
                    lp_lat = aasin(this->m_proj_parm.sa * sp + this->m_proj_parm.ca * cp * (s = cos(lp_lon -= this->m_proj_parm.lp)));
                    lp_lon = atan2(cp * sin(lp_lon), this->m_proj_parm.sa * cp * s - this->m_proj_parm.ca * sp) + this->m_proj_parm.lamc;
                }

                static inline std::string get_name()
                {
                    return "tpeqd_spheroid";
                }

            };

            // Two Point Equidistant
            template <typename Params, typename Parameters, typename T>
            inline void setup_tpeqd(Params const& params, Parameters& par, par_tpeqd<T>& proj_parm)
            {
                T lam_1, lam_2, phi_1, phi_2, A12, pp;

                /* get control point locations */
                phi_1 = pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1);
                lam_1 = pj_get_param_r<T, srs::spar::lon_1>(params, "lon_1", srs::dpar::lon_1);
                phi_2 = pj_get_param_r<T, srs::spar::lat_2>(params, "lat_2", srs::dpar::lat_2);
                lam_2 = pj_get_param_r<T, srs::spar::lon_2>(params, "lon_2", srs::dpar::lon_2);

                if (phi_1 == phi_2 && lam_1 == lam_2)
                    BOOST_THROW_EXCEPTION( projection_exception(error_control_point_no_dist) );

                par.lam0 = adjlon(0.5 * (lam_1 + lam_2));
                proj_parm.dlam2 = adjlon(lam_2 - lam_1);

                proj_parm.cp1 = cos(phi_1);
                proj_parm.cp2 = cos(phi_2);
                proj_parm.sp1 = sin(phi_1);
                proj_parm.sp2 = sin(phi_2);
                proj_parm.cs = proj_parm.cp1 * proj_parm.sp2;
                proj_parm.sc = proj_parm.sp1 * proj_parm.cp2;
                proj_parm.ccs = proj_parm.cp1 * proj_parm.cp2 * sin(proj_parm.dlam2);
                proj_parm.z02 = aacos(proj_parm.sp1 * proj_parm.sp2 + proj_parm.cp1 * proj_parm.cp2 * cos(proj_parm.dlam2));
                proj_parm.hz0 = .5 * proj_parm.z02;
                A12 = atan2(proj_parm.cp2 * sin(proj_parm.dlam2),
                    proj_parm.cp1 * proj_parm.sp2 - proj_parm.sp1 * proj_parm.cp2 * cos(proj_parm.dlam2));
                proj_parm.ca = cos(pp = aasin(proj_parm.cp1 * sin(A12)));
                proj_parm.sa = sin(pp);
                proj_parm.lp = adjlon(atan2(proj_parm.cp1 * cos(A12), proj_parm.sp1) - proj_parm.hz0);
                proj_parm.dlam2 *= .5;
                proj_parm.lamc = geometry::math::half_pi<T>() - atan2(sin(A12) * proj_parm.sp1, cos(A12)) - proj_parm.dlam2;
                proj_parm.thz0 = tan(proj_parm.hz0);
                proj_parm.rhshz0 = .5 / sin(proj_parm.hz0);
                proj_parm.r2z0 = 0.5 / proj_parm.z02;
                proj_parm.z02 *= proj_parm.z02;

                par.es = 0.;
            }

    }} // namespace detail::tpeqd
    #endif // doxygen

    /*!
        \brief Two Point Equidistant projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
         - lon_1 (degrees)
         - lat_2: Latitude of second standard parallel (degrees)
         - lon_2 (degrees)
        \par Example
        \image html ex_tpeqd.gif
    */
    template <typename T, typename Parameters>
    struct tpeqd_spheroid : public detail::tpeqd::base_tpeqd_spheroid<T, Parameters>
    {
        template <typename Params>
        inline tpeqd_spheroid(Params const& params, Parameters & par)
        {
            detail::tpeqd::setup_tpeqd(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_tpeqd, tpeqd_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(tpeqd_entry, tpeqd_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(tpeqd_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(tpeqd, tpeqd_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_TPEQD_HPP


/* tpeqd.hpp
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
*/
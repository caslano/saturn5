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
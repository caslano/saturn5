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

#ifndef BOOST_GEOMETRY_PROJECTIONS_OEA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_OEA_HPP

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
    namespace detail { namespace oea
    {
            template <typename T>
            struct par_oea
            {
                T    theta;
                T    m, n;
                T    two_r_m, two_r_n, rm, rn, hm, hn;
                T    cp0, sp0;
            };

            template <typename T, typename Parameters>
            struct base_oea_spheroid
            {
                par_oea<T> m_proj_parm;

                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T Az, M, N, cp, sp, cl, shz;

                    cp = cos(lp_lat);
                    sp = sin(lp_lat);
                    cl = cos(lp_lon);
                    Az = aatan2(cp * sin(lp_lon), this->m_proj_parm.cp0 * sp - this->m_proj_parm.sp0 * cp * cl) + this->m_proj_parm.theta;
                    shz = sin(0.5 * aacos(this->m_proj_parm.sp0 * sp + this->m_proj_parm.cp0 * cp * cl));
                    M = aasin(shz * sin(Az));
                    N = aasin(shz * cos(Az) * cos(M) / cos(M * this->m_proj_parm.two_r_m));
                    xy_y = this->m_proj_parm.n * sin(N * this->m_proj_parm.two_r_n);
                    xy_x = this->m_proj_parm.m * sin(M * this->m_proj_parm.two_r_m) * cos(N) / cos(N * this->m_proj_parm.two_r_n);
                }

                // INVERSE(s_inverse)  sphere
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T N, M, xp, yp, z, Az, cz, sz, cAz;

                    N = this->m_proj_parm.hn * aasin(xy_y * this->m_proj_parm.rn);
                    M = this->m_proj_parm.hm * aasin(xy_x * this->m_proj_parm.rm * cos(N * this->m_proj_parm.two_r_n) / cos(N));
                    xp = 2. * sin(M);
                    yp = 2. * sin(N) * cos(M * this->m_proj_parm.two_r_m) / cos(M);
                    cAz = cos(Az = aatan2(xp, yp) - this->m_proj_parm.theta);
                    z = 2. * aasin(0.5 * boost::math::hypot(xp, yp));
                    sz = sin(z);
                    cz = cos(z);
                    lp_lat = aasin(this->m_proj_parm.sp0 * cz + this->m_proj_parm.cp0 * sz * cAz);
                    lp_lon = aatan2(sz * sin(Az),
                        this->m_proj_parm.cp0 * cz - this->m_proj_parm.sp0 * sz * cAz);
                }

                static inline std::string get_name()
                {
                    return "oea_spheroid";
                }

            };

            // Oblated Equal Area
            template <typename Params, typename Parameters, typename T>
            inline void setup_oea(Params const& params, Parameters& par, par_oea<T>& proj_parm)
            {
                if (((proj_parm.n = pj_get_param_f<T, srs::spar::n>(params, "n", srs::dpar::n)) <= 0.) ||
                    ((proj_parm.m = pj_get_param_f<T, srs::spar::m>(params, "m", srs::dpar::m)) <= 0.)) {
                    BOOST_THROW_EXCEPTION( projection_exception(error_invalid_m_or_n) );
                } else {
                    proj_parm.theta = pj_get_param_r<T, srs::spar::theta>(params, "theta", srs::dpar::theta);
                    proj_parm.sp0 = sin(par.phi0);
                    proj_parm.cp0 = cos(par.phi0);
                    proj_parm.rn = 1./ proj_parm.n;
                    proj_parm.rm = 1./ proj_parm.m;
                    proj_parm.two_r_n = 2. * proj_parm.rn;
                    proj_parm.two_r_m = 2. * proj_parm.rm;
                    proj_parm.hm = 0.5 * proj_parm.m;
                    proj_parm.hn = 0.5 * proj_parm.n;
                    par.es = 0.;
                }
            }

    }} // namespace detail::oea
    #endif // doxygen

    /*!
        \brief Oblated Equal Area projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
        \par Projection parameters
         - n (real)
         - m (real)
         - theta: Theta (degrees)
        \par Example
        \image html ex_oea.gif
    */
    template <typename T, typename Parameters>
    struct oea_spheroid : public detail::oea::base_oea_spheroid<T, Parameters>
    {
        template <typename Params>
        inline oea_spheroid(Params const& params, Parameters & par)
        {
            detail::oea::setup_oea(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_oea, oea_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(oea_entry, oea_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(oea_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(oea, oea_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_OEA_HPP


/* oea.hpp
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
*/
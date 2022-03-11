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
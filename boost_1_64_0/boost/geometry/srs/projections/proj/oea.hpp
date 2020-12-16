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
688LGB7teYHD+HmBrTt98nmBLHXAGb3Ka39eIEKipSP49YC7IZP08HDHU17L8wJhBigDAC51FXSFcnee+LxApJnnBSI/2fMCVvm1a4PdfoBux4XqXNL3fmEB2ZBcfsT3n3scKTVH3H/uUJS6XU3+uiclpe603L+x39OTrPdviOgERtSwHRH92aUhukkiavqarvDZFK/p3Dayj0qyv6KfRvb3DEh2TRdtTZpu4j4r+hFvTXzKBU0osB5bHJo9FKMqprIpj9CVDlX74AIHle3fgK/Aui8OTarMaPP//SGVJx6b3CXlGGko9iah7l4VlSuiTt27P6k/cDWLpjN+yTtMu/eE07KYaDHSbyprT0FQmxdaNx+Yo0gaUDSIFJEP6vFCJTYK6iZ1sFroD/KuUAtrFaYpMT6mVTWjNx82LgZ4Mq2fWD1OxhUKHBHBvTzxLWIBX+eV0pQBcrXmGqflkpoRJJuKkYMhSll7gp8DT/xmXp0fBg7EJX0FX1zvffCFXPenmn/N6LPGPlBbZZflXiFCgzRe3X94rC5eA89VRD20tyfygkH5GDi0uZGWHeIWHRLGDkG+YPb8A6tS09ROWv+G9x3rz9YY3SioG6k5uT4JWzdwI8Rww9FODM9DT4nh1lrnsQ73GS5unbDReerHtK4Je5P27ztLoUy94lOMwzpgmK9oVTyLo84JEDue9KqS5p+vFtgvVoI46ly+nMlBFOZOtGww+p7mZn0GXLuywV3mifejhqsnqfp3oLenPPEOyEmIwnLiq/A73kOgCVAOLuJAlou4/0F4PktNvuq23QEXOK5/76pNSolwjVBieLJoHAfF/VLtthr+YncobbkMs43VEI/HtZnH456aMRQDBuIfzCpeeoJskYdCKUM95WIVD8efxyH5iofkrS04JLtwSMarIRn/KO55DpIhWPyt7nqHWvkK1NITWCNrzt4TcXKUsa0533ZOwJTa3d682HQXbZyGQNVweg/8nWCKBJIXu4GTe4jkTiI5KnZefsE7z8+LzWDIr+rkDmzfI6hnPpOj3xHREeNtiMY+meWiPnm5Tk3TC1WfjPwd7QPfs87+eCbfMDTWmJPWG6icT/jThgj8uZUz4KusH0SFZVR1QZ3PmP97Pn+thL9sGMqK/Z74SoDdv1nAgm5DHdWT7z7mdaqF1Pc30xb7bQIah0DtduBHlM7Rw6G3a9xVvoz6C5VGBd+3+VUgKkQGqLgBjKYqGqTB+K+7erT6P/iLuGVcwiN2FLRWvafeZ4WXA+ycC0bsXobySiiyOfvXcgUW8asbllciweSS5IT6+Lk+UMaJOS5LGWuJ86ky2GMdTkul43FilgkRJAilKtFGAW4mG0wVyOaAs/fuFCvftL9qB6Z01C5qHlJqKflCZu5ER6R3mTQe3YSk8QSSxjxFGscuJ9JAVXrKK7R8RgaH1AZuP0nGMu2bZL72Y0KZNm6Tejy1GMf1H49qeyA+GPyNiw9T8Xl68U89LPfz3SCO8MjJzhxj7adc0t83miXRuFU/qrEOLmofF/XiRoei8lVRT8kto5WUsNWRILNnK6um9hOv7oM1yuHqbfbV4girmChaHca3CDygUAUkafYnqFnTcQHpnwemPEPxoXSEm448yJphpB8diudWdWKNqYPk5639c/KXvpQe9H+TqWsztB/CaPpWB3+Is8I3a3lO94th6uLm95834DDhaKy7zXz/eZlSlYVzIO0BZgSiExDRYEbKk7o749j5MuJ4Ucdx/jKa1Be3wek7p+9K8pTinUX5QpzvPsoX0/P15nxHiHyrKJ+b8x3O+S6jfFv1fPW/pXz70jgfYMWD2ajAmsX0jYZ0y0j21p+X+GL2EMfaEv0=
*/
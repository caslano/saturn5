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

#ifndef BOOST_GEOMETRY_PROJECTIONS_TMERC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_TMERC_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/function_overloads.hpp>
#include <boost/geometry/srs/projections/impl/pj_mlfn.hpp>


namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace tmerc
    {

            static const double epsilon10 = 1.e-10;

            template <typename T>
            inline T FC1() { return 1.; }
            template <typename T>
            inline T FC2() { return .5; }
            template <typename T>
            inline T FC3() { return .16666666666666666666666666666666666666; }
            template <typename T>
            inline T FC4() { return .08333333333333333333333333333333333333; }
            template <typename T>
            inline T FC5() { return .05; }
            template <typename T>
            inline T FC6() { return .03333333333333333333333333333333333333; }
            template <typename T>
            inline T FC7() { return .02380952380952380952380952380952380952; }
            template <typename T>
            inline T FC8() { return .01785714285714285714285714285714285714; }

            template <typename T>
            struct par_tmerc
            {
                T    esp;
                T    ml0;
                detail::en<T> en;
            };

            template <typename T, typename Parameters>
            struct base_tmerc_ellipsoid
            {
                par_tmerc<T> m_proj_parm;

                // FORWARD(e_forward)  ellipse
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T FC1 = tmerc::FC1<T>();
                    static const T FC2 = tmerc::FC2<T>();
                    static const T FC3 = tmerc::FC3<T>();
                    static const T FC4 = tmerc::FC4<T>();
                    static const T FC5 = tmerc::FC5<T>();
                    static const T FC6 = tmerc::FC6<T>();
                    static const T FC7 = tmerc::FC7<T>();
                    static const T FC8 = tmerc::FC8<T>();

                    T al, als, n, cosphi, sinphi, t;

                    /*
                     * Fail if our longitude is more than 90 degrees from the
                     * central meridian since the results are essentially garbage.
                     * Is error -20 really an appropriate return value?
                     *
                     *  http://trac.osgeo.org/proj/ticket/5
                     */
                    if( lp_lon < -half_pi || lp_lon > half_pi )
                    {
                        xy_x = HUGE_VAL;
                        xy_y = HUGE_VAL;
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_or_lon_exceed_limit) );
                        return;
                    }

                    sinphi = sin(lp_lat);
                    cosphi = cos(lp_lat);
                    t = fabs(cosphi) > 1e-10 ? sinphi/cosphi : 0.;
                    t *= t;
                    al = cosphi * lp_lon;
                    als = al * al;
                    al /= sqrt(1. - par.es * sinphi * sinphi);
                    n = this->m_proj_parm.esp * cosphi * cosphi;
                    xy_x = par.k0 * al * (FC1 +
                        FC3 * als * (1. - t + n +
                        FC5 * als * (5. + t * (t - 18.) + n * (14. - 58. * t)
                        + FC7 * als * (61. + t * ( t * (179. - t) - 479. ) )
                        )));
                    xy_y = par.k0 * (pj_mlfn(lp_lat, sinphi, cosphi, this->m_proj_parm.en) - this->m_proj_parm.ml0 +
                        sinphi * al * lp_lon * FC2 * ( 1. +
                        FC4 * als * (5. - t + n * (9. + 4. * n) +
                        FC6 * als * (61. + t * (t - 58.) + n * (270. - 330 * t)
                        + FC8 * als * (1385. + t * ( t * (543. - t) - 3111.) )
                        ))));
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T FC1 = tmerc::FC1<T>();
                    static const T FC2 = tmerc::FC2<T>();
                    static const T FC3 = tmerc::FC3<T>();
                    static const T FC4 = tmerc::FC4<T>();
                    static const T FC5 = tmerc::FC5<T>();
                    static const T FC6 = tmerc::FC6<T>();
                    static const T FC7 = tmerc::FC7<T>();
                    static const T FC8 = tmerc::FC8<T>();

                    T n, con, cosphi, d, ds, sinphi, t;

                    lp_lat = pj_inv_mlfn(this->m_proj_parm.ml0 + xy_y / par.k0, par.es, this->m_proj_parm.en);
                    if (fabs(lp_lat) >= half_pi) {
                        lp_lat = xy_y < 0. ? -half_pi : half_pi;
                        lp_lon = 0.;
                    } else {
                        sinphi = sin(lp_lat);
                        cosphi = cos(lp_lat);
                        t = fabs(cosphi) > 1e-10 ? sinphi/cosphi : 0.;
                        n = this->m_proj_parm.esp * cosphi * cosphi;
                        d = xy_x * sqrt(con = 1. - par.es * sinphi * sinphi) / par.k0;
                        con *= t;
                        t *= t;
                        ds = d * d;
                        lp_lat -= (con * ds / (1.-par.es)) * FC2 * (1. -
                            ds * FC4 * (5. + t * (3. - 9. *  n) + n * (1. - 4 * n) -
                            ds * FC6 * (61. + t * (90. - 252. * n +
                                45. * t) + 46. * n
                           - ds * FC8 * (1385. + t * (3633. + t * (4095. + 1574. * t)) )
                            )));
                        lp_lon = d*(FC1 -
                            ds*FC3*( 1. + 2.*t + n -
                            ds*FC5*(5. + t*(28. + 24.*t + 8.*n) + 6.*n
                           - ds * FC7 * (61. + t * (662. + t * (1320. + 720. * t)) )
                        ))) / cosphi;
                    }
                }

                static inline std::string get_name()
                {
                    return "tmerc_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_tmerc_spheroid
            {
                par_tmerc<T> m_proj_parm;

                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T b, cosphi;

                    /*
                     * Fail if our longitude is more than 90 degrees from the
                     * central meridian since the results are essentially garbage.
                     * Is error -20 really an appropriate return value?
                     *
                     *  http://trac.osgeo.org/proj/ticket/5
                     */
                    if( lp_lon < -half_pi || lp_lon > half_pi )
                    {
                        xy_x = HUGE_VAL;
                        xy_y = HUGE_VAL;
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_or_lon_exceed_limit) );
                        return;
                    }

                    cosphi = cos(lp_lat);
                    b = cosphi * sin(lp_lon);
                    if (fabs(fabs(b) - 1.) <= epsilon10)
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );

                    xy_x = this->m_proj_parm.ml0 * log((1. + b) / (1. - b));
                    xy_y = cosphi * cos(lp_lon) / sqrt(1. - b * b);

                    b = fabs( xy_y );
                    if (b >= 1.) {
                        if ((b - 1.) > epsilon10)
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        else xy_y = 0.;
                    } else
                        xy_y = acos(xy_y);

                    if (lp_lat < 0.)
                        xy_y = -xy_y;
                    xy_y = this->m_proj_parm.esp * (xy_y - par.phi0);
                }

                // INVERSE(s_inverse)  sphere
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T h, g;

                    h = exp(xy_x / this->m_proj_parm.esp);
                    g = .5 * (h - 1. / h);
                    h = cos(par.phi0 + xy_y / this->m_proj_parm.esp);
                    lp_lat = asin(sqrt((1. - h * h) / (1. + g * g)));

                    /* Make sure that phi is on the correct hemisphere when false northing is used */
                    if (xy_y < 0. && -lp_lat+par.phi0 < 0.0) lp_lat = -lp_lat;

                    lp_lon = (g != 0.0 || h != 0.0) ? atan2(g, h) : 0.;
                }

                static inline std::string get_name()
                {
                    return "tmerc_spheroid";
                }

            };

            template <typename Parameters, typename T>
            inline void setup(Parameters const& par, par_tmerc<T>& proj_parm)
            {
                if (par.es != 0.0) {
                    proj_parm.en = pj_enfn<T>(par.es);
                    proj_parm.ml0 = pj_mlfn(par.phi0, sin(par.phi0), cos(par.phi0), proj_parm.en);
                    proj_parm.esp = par.es / (1. - par.es);
                } else {
                    proj_parm.esp = par.k0;
                    proj_parm.ml0 = .5 * proj_parm.esp;
                }
            }

    }} // namespace detail::tmerc
    #endif // doxygen

    /*!
        \brief Transverse Mercator projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_tmerc.gif
    */
    template <typename T, typename Parameters>
    struct tmerc_ellipsoid : public detail::tmerc::base_tmerc_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline tmerc_ellipsoid(Params const&, Parameters const& par)
        {
            detail::tmerc::setup(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Transverse Mercator projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_tmerc.gif
    */
    template <typename T, typename Parameters>
    struct tmerc_spheroid : public detail::tmerc::base_tmerc_spheroid<T, Parameters>
    {
        template <typename Params>
        inline tmerc_spheroid(Params const&, Parameters const& par)
        {
            detail::tmerc::setup(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_tmerc, tmerc_spheroid, tmerc_ellipsoid)
        
        // Factory entry(s) - dynamic projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(tmerc_entry, tmerc_spheroid, tmerc_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(tmerc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(tmerc, tmerc_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_TMERC_HPP


/* tmerc.hpp
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
*/
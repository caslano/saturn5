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
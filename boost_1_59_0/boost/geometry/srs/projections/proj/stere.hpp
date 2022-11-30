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

#ifndef BOOST_GEOMETRY_PROJECTIONS_STERE_HPP
#define BOOST_GEOMETRY_PROJECTIONS_STERE_HPP

#include <boost/config.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/pj_tsfn.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace stere
    {
            static const double epsilon10 = 1.e-10;
            static const double tolerance = 1.e-8;
            static const int n_iter = 8;
            static const double conv_tolerance = 1.e-10;

            enum mode_type {
                s_pole = 0,
                n_pole = 1,
                obliq  = 2,
                equit  = 3
            };

            template <typename T>
            struct par_stere
            {
                T   phits;
                T   sinX1;
                T   cosX1;
                T   akm1;
                mode_type mode;
            };

            template <typename T>
            inline T ssfn_(T const& phit, T sinphi, T const& eccen)
            {
                static const T half_pi = detail::half_pi<T>();

                sinphi *= eccen;
                return (tan (.5 * (half_pi + phit)) *
                   math::pow((T(1) - sinphi) / (T(1) + sinphi), T(0.5) * eccen));
            }

            template <typename T, typename Parameters>
            struct base_stere_ellipsoid
            {
                par_stere<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T coslam, sinlam, sinX=0.0, cosX=0.0, X, A = 0.0, sinphi;

                    coslam = cos(lp_lon);
                    sinlam = sin(lp_lon);
                    sinphi = sin(lp_lat);
                    if (this->m_proj_parm.mode == obliq || this->m_proj_parm.mode == equit) {
                        sinX = sin(X = 2. * atan(ssfn_(lp_lat, sinphi, par.e)) - half_pi);
                        cosX = cos(X);
                    }
                    switch (this->m_proj_parm.mode) {
                    case obliq:
                        A = this->m_proj_parm.akm1 / (this->m_proj_parm.cosX1 * (1. + this->m_proj_parm.sinX1 * sinX +
                           this->m_proj_parm.cosX1 * cosX * coslam));
                        xy_y = A * (this->m_proj_parm.cosX1 * sinX - this->m_proj_parm.sinX1 * cosX * coslam);
                        goto xmul; /* but why not just  xy.x = A * cosX; break;  ? */

                    case equit:
                        // TODO: calculate denominator once
                        /* avoid zero division */
                        if (1. + cosX * coslam == 0.0) {
                            xy_y = HUGE_VAL;
                        } else {
                            A = this->m_proj_parm.akm1 / (1. + cosX * coslam);
                            xy_y = A * sinX;
                        }
                xmul:
                        xy_x = A * cosX;
                        break;

                    case s_pole:
                        lp_lat = -lp_lat;
                        coslam = - coslam;
                        sinphi = -sinphi;
                        BOOST_FALLTHROUGH;
                    case n_pole:
                        xy_x = this->m_proj_parm.akm1 * pj_tsfn(lp_lat, sinphi, par.e);
                        xy_y = - xy_x * coslam;
                        break;
                    }

                    xy_x = xy_x * sinlam;
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T cosphi, sinphi, tp=0.0, phi_l=0.0, rho, halfe=0.0, halfpi=0.0;
                    int i;

                    rho = boost::math::hypot(xy_x, xy_y);
                    switch (this->m_proj_parm.mode) {
                    case obliq:
                    case equit:
                        cosphi = cos( tp = 2. * atan2(rho * this->m_proj_parm.cosX1 , this->m_proj_parm.akm1) );
                        sinphi = sin(tp);
                        if( rho == 0.0 )
                            phi_l = asin(cosphi * this->m_proj_parm.sinX1);
                        else
                            phi_l = asin(cosphi * this->m_proj_parm.sinX1 + (xy_y * sinphi * this->m_proj_parm.cosX1 / rho));

                        tp = tan(.5 * (half_pi + phi_l));
                        xy_x *= sinphi;
                        xy_y = rho * this->m_proj_parm.cosX1 * cosphi - xy_y * this->m_proj_parm.sinX1* sinphi;
                        halfpi = half_pi;
                        halfe = .5 * par.e;
                        break;
                    case n_pole:
                        xy_y = -xy_y;
                        BOOST_FALLTHROUGH;
                    case s_pole:
                        phi_l = half_pi - 2. * atan(tp = - rho / this->m_proj_parm.akm1);
                        halfpi = -half_pi;
                        halfe = -.5 * par.e;
                        break;
                    }
                    for (i = n_iter; i--; phi_l = lp_lat) {
                        sinphi = par.e * sin(phi_l);
                        lp_lat = T(2) * atan(tp * math::pow((T(1)+sinphi)/(T(1)-sinphi), halfe)) - halfpi;
                        if (fabs(phi_l - lp_lat) < conv_tolerance) {
                            if (this->m_proj_parm.mode == s_pole)
                                lp_lat = -lp_lat;
                            lp_lon = (xy_x == 0. && xy_y == 0.) ? 0. : atan2(xy_x, xy_y);
                            return;
                        }
                    }
                    BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                }

                static inline std::string get_name()
                {
                    return "stere_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_stere_spheroid
            {
                par_stere<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T half_pi = detail::half_pi<T>();

                    T  sinphi, cosphi, coslam, sinlam;

                    sinphi = sin(lp_lat);
                    cosphi = cos(lp_lat);
                    coslam = cos(lp_lon);
                    sinlam = sin(lp_lon);
                    switch (this->m_proj_parm.mode) {
                    case equit:
                        xy_y = 1. + cosphi * coslam;
                        goto oblcon;
                    case obliq:
                        xy_y = 1. + this->m_proj_parm.sinX1 * sinphi + this->m_proj_parm.cosX1 * cosphi * coslam;
                oblcon:
                        if (xy_y <= epsilon10) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        xy_x = (xy_y = this->m_proj_parm.akm1 / xy_y) * cosphi * sinlam;
                        xy_y *= (this->m_proj_parm.mode == equit) ? sinphi :
                           this->m_proj_parm.cosX1 * sinphi - this->m_proj_parm.sinX1 * cosphi * coslam;
                        break;
                    case n_pole:
                        coslam = - coslam;
                        lp_lat = - lp_lat;
                        BOOST_FALLTHROUGH;
                    case s_pole:
                        if (fabs(lp_lat - half_pi) < tolerance) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        xy_x = sinlam * ( xy_y = this->m_proj_parm.akm1 * tan(fourth_pi + .5 * lp_lat) );
                        xy_y *= coslam;
                        break;
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T  c, rh, sinc, cosc;

                    sinc = sin(c = 2. * atan((rh = boost::math::hypot(xy_x, xy_y)) / this->m_proj_parm.akm1));
                    cosc = cos(c);
                    lp_lon = 0.;

                    switch (this->m_proj_parm.mode) {
                    case equit:
                        if (fabs(rh) <= epsilon10)
                            lp_lat = 0.;
                        else
                            lp_lat = asin(xy_y * sinc / rh);
                        if (cosc != 0. || xy_x != 0.)
                            lp_lon = atan2(xy_x * sinc, cosc * rh);
                        break;
                    case obliq:
                        if (fabs(rh) <= epsilon10)
                            lp_lat = par.phi0;
                        else
                            lp_lat = asin(cosc * this->m_proj_parm.sinX1 + xy_y * sinc * this->m_proj_parm.cosX1 / rh);
                        if ((c = cosc - this->m_proj_parm.sinX1 * sin(lp_lat)) != 0. || xy_x != 0.)
                            lp_lon = atan2(xy_x * sinc * this->m_proj_parm.cosX1, c * rh);
                        break;
                    case n_pole:
                        xy_y = -xy_y;
                        BOOST_FALLTHROUGH;
                    case s_pole:
                        if (fabs(rh) <= epsilon10)
                            lp_lat = par.phi0;
                        else
                            lp_lat = asin(this->m_proj_parm.mode == s_pole ? - cosc : cosc);
                        lp_lon = (xy_x == 0. && xy_y == 0.) ? 0. : atan2(xy_x, xy_y);
                        break;
                    }
                }

                static inline std::string get_name()
                {
                    return "stere_spheroid";
                }

            };

            template <typename Parameters, typename T>
            inline void setup(Parameters const& par, par_stere<T>& proj_parm)  /* general initialization */
            {
                static const T fourth_pi = detail::fourth_pi<T>();
                static const T half_pi = detail::half_pi<T>();

                T t;

                if (fabs((t = fabs(par.phi0)) - half_pi) < epsilon10)
                    proj_parm.mode = par.phi0 < 0. ? s_pole : n_pole;
                else
                    proj_parm.mode = t > epsilon10 ? obliq : equit;
                proj_parm.phits = fabs(proj_parm.phits);

                if (par.es != 0.0) {
                    T X;

                    switch (proj_parm.mode) {
                    case n_pole:
                    case s_pole:
                        if (fabs(proj_parm.phits - half_pi) < epsilon10)
                            proj_parm.akm1 = 2. * par.k0 /
                               sqrt(math::pow(T(1)+par.e,T(1)+par.e)*math::pow(T(1)-par.e,T(1)-par.e));
                        else {
                            proj_parm.akm1 = cos(proj_parm.phits) /
                               pj_tsfn(proj_parm.phits, t = sin(proj_parm.phits), par.e);
                            t *= par.e;
                            proj_parm.akm1 /= sqrt(1. - t * t);
                        }
                        break;
                    case equit:
                    case obliq:
                        t = sin(par.phi0);
                        X = 2. * atan(ssfn_(par.phi0, t, par.e)) - half_pi;
                        t *= par.e;
                        proj_parm.akm1 = 2. * par.k0 * cos(par.phi0) / sqrt(1. - t * t);
                        proj_parm.sinX1 = sin(X);
                        proj_parm.cosX1 = cos(X);
                        break;
                    }
                } else {
                    switch (proj_parm.mode) {
                    case obliq:
                        proj_parm.sinX1 = sin(par.phi0);
                        proj_parm.cosX1 = cos(par.phi0);
                        BOOST_FALLTHROUGH;
                    case equit:
                        proj_parm.akm1 = 2. * par.k0;
                        break;
                    case s_pole:
                    case n_pole:
                        proj_parm.akm1 = fabs(proj_parm.phits - half_pi) >= epsilon10 ?
                           cos(proj_parm.phits) / tan(fourth_pi - .5 * proj_parm.phits) :
                           2. * par.k0 ;
                        break;
                    }
                }
            }


            // Stereographic
            template <typename Params, typename Parameters, typename T>
            inline void setup_stere(Params const& params, Parameters const& par, par_stere<T>& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();

                if (! pj_param_r<srs::spar::lat_ts>(params, "lat_ts", srs::dpar::lat_ts, proj_parm.phits))
                    proj_parm.phits = half_pi;

                setup(par, proj_parm);
            }

            // Universal Polar Stereographic
            template <typename Params, typename Parameters, typename T>
            inline void setup_ups(Params const& params, Parameters& par, par_stere<T>& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();

                /* International Ellipsoid */
                par.phi0 = pj_get_param_b<srs::spar::south>(params, "south", srs::dpar::south) ? -half_pi: half_pi;
                if (par.es == 0.0) {
                    BOOST_THROW_EXCEPTION( projection_exception(error_ellipsoid_use_required) );
                }
                par.k0 = .994;
                par.x0 = 2000000.;
                par.y0 = 2000000.;
                proj_parm.phits = half_pi;
                par.lam0 = 0.;

                setup(par, proj_parm);
            }

    }} // namespace detail::stere
    #endif // doxygen

    /*!
        \brief Stereographic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
        \par Example
        \image html ex_stere.gif
    */
    template <typename T, typename Parameters>
    struct stere_ellipsoid : public detail::stere::base_stere_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline stere_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::stere::setup_stere(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Stereographic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
        \par Example
        \image html ex_stere.gif
    */
    template <typename T, typename Parameters>
    struct stere_spheroid : public detail::stere::base_stere_spheroid<T, Parameters>
    {
        template <typename Params>
        inline stere_spheroid(Params const& params, Parameters const& par)
        {
            detail::stere::setup_stere(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Universal Polar Stereographic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - south: Denotes southern hemisphere UTM zone (boolean)
        \par Example
        \image html ex_ups.gif
    */
    template <typename T, typename Parameters>
    struct ups_ellipsoid : public detail::stere::base_stere_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline ups_ellipsoid(Params const& params, Parameters & par)
        {
            detail::stere::setup_ups(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Universal Polar Stereographic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - south: Denotes southern hemisphere UTM zone (boolean)
        \par Example
        \image html ex_ups.gif
    */
    template <typename T, typename Parameters>
    struct ups_spheroid : public detail::stere::base_stere_spheroid<T, Parameters>
    {
        template <typename Params>
        inline ups_spheroid(Params const& params, Parameters & par)
        {
            detail::stere::setup_ups(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_stere, stere_spheroid, stere_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_ups, ups_spheroid, ups_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(stere_entry, stere_spheroid, stere_ellipsoid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(ups_entry, ups_spheroid, ups_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(stere_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(stere, stere_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(ups, ups_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_STERE_HPP


/* stere.hpp
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
*/
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
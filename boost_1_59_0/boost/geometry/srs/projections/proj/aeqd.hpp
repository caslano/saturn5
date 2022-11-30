// Boost.Geometry - gis-projections (based on PROJ4)

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
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

// Purpose:  Implementation of the aeqd (Azimuthal Equidistant) projection.
// Author:   Gerald Evenden
// Copyright (c) 1995, Gerald Evenden

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_AEQD_HPP
#define BOOST_GEOMETRY_PROJECTIONS_AEQD_HPP


#include <type_traits>

#include <boost/config.hpp>

#include <boost/geometry/formulas/vincenty_direct.hpp>
#include <boost/geometry/formulas/vincenty_inverse.hpp>

#include <boost/geometry/srs/projections/impl/aasincos.hpp>
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
    namespace detail { namespace aeqd
    {

            static const double epsilon10 = 1.e-10;
            static const double tolerance = 1.e-14;
            enum mode_type {
                n_pole = 0,
                s_pole = 1,
                equit  = 2,
                obliq  = 3
            };

            template <typename T>
            struct par_aeqd
            {
                T    sinph0;
                T    cosph0;
                detail::en<T> en;
                T    M1;
                //T    N1;
                T    Mp;
                //T    He;
                //T    G;
                T    b;
                mode_type mode;
            };

            template <typename T, typename Par, typename ProjParm>
            inline void e_forward(T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y, Par const& par, ProjParm const& proj_parm)
            {
                T coslam, cosphi, sinphi, rho;
                //T azi1, s12;
                //T lam1, phi1, lam2, phi2;

                coslam = cos(lp_lon);
                cosphi = cos(lp_lat);
                sinphi = sin(lp_lat);
                switch (proj_parm.mode) {
                case n_pole:
                    coslam = - coslam;
                    BOOST_FALLTHROUGH;
                case s_pole:
                    xy_x = (rho = fabs(proj_parm.Mp - pj_mlfn(lp_lat, sinphi, cosphi, proj_parm.en))) *
                        sin(lp_lon);
                    xy_y = rho * coslam;
                    break;
                case equit:
                case obliq:
                    if (fabs(lp_lon) < epsilon10 && fabs(lp_lat - par.phi0) < epsilon10) {
                        xy_x = xy_y = 0.;
                        break;
                    }

                    //phi1 = par.phi0; lam1 = par.lam0;
                    //phi2 = lp_lat;  lam2 = lp_lon + par.lam0;

                    formula::result_inverse<T> const inv =
                        formula::vincenty_inverse
                            <
                                T, true, true
                            >::apply(par.lam0, par.phi0, lp_lon + par.lam0, lp_lat, srs::spheroid<T>(par.a, proj_parm.b));
                    //azi1 = inv.azimuth; s12 = inv.distance;
                    xy_x = inv.distance * sin(inv.azimuth) / par.a;
                    xy_y = inv.distance * cos(inv.azimuth) / par.a;
                    break;
                }
            }

            template <typename T, typename Par, typename ProjParm>
            inline void e_inverse(T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat, Par const& par, ProjParm const& proj_parm)
            {
                T c;

                if ((c = boost::math::hypot(xy_x, xy_y)) < epsilon10) {
                    lp_lat = par.phi0;
                    lp_lon = 0.;
                        return;
                }
                if (proj_parm.mode == obliq || proj_parm.mode == equit) {
                    T const x2 = xy_x * par.a;
                    T const y2 = xy_y * par.a;
                    //T const lat1 = par.phi0;
                    //T const lon1 = par.lam0;
                    T const azi1 = atan2(x2, y2);
                    T const s12 = sqrt(x2 * x2 + y2 * y2);
                    formula::result_direct<T> const dir =
                        formula::vincenty_direct
                            <
                                T, true
                            >::apply(par.lam0, par.phi0, s12, azi1, srs::spheroid<T>(par.a, proj_parm.b));
                    lp_lat = dir.lat2;
                    lp_lon = dir.lon2;
                    lp_lon -= par.lam0;
                } else { /* Polar */
                    lp_lat = pj_inv_mlfn(proj_parm.mode == n_pole ? proj_parm.Mp - c : proj_parm.Mp + c,
                        par.es, proj_parm.en);
                    lp_lon = atan2(xy_x, proj_parm.mode == n_pole ? -xy_y : xy_y);
                }
            }

            template <typename T, typename Par, typename ProjParm>
            inline void e_guam_fwd(T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y, Par const& par, ProjParm const& proj_parm)
            {
                T cosphi, sinphi, t;

                cosphi = cos(lp_lat);
                sinphi = sin(lp_lat);
                t = 1. / sqrt(1. - par.es * sinphi * sinphi);
                xy_x = lp_lon * cosphi * t;
                xy_y = pj_mlfn(lp_lat, sinphi, cosphi, proj_parm.en) - proj_parm.M1 +
                    .5 * lp_lon * lp_lon * cosphi * sinphi * t;
            }

            template <typename T, typename Par, typename ProjParm>
            inline void e_guam_inv(T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat, Par const& par, ProjParm const& proj_parm)
            {
                T x2, t = 0.0;
                int i;

                x2 = 0.5 * xy_x * xy_x;
                lp_lat = par.phi0;
                for (i = 0; i < 3; ++i) {
                    t = par.e * sin(lp_lat);
                    lp_lat = pj_inv_mlfn(proj_parm.M1 + xy_y -
                        x2 * tan(lp_lat) * (t = sqrt(1. - t * t)), par.es, proj_parm.en);
                }
                lp_lon = xy_x * t / cos(lp_lat);
            }

            template <typename T, typename Par, typename ProjParm>
            inline void s_forward(T const& lp_lon, T lp_lat, T& xy_x, T& xy_y, Par const& /*par*/, ProjParm const& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();
                    
                T coslam, cosphi, sinphi;

                sinphi = sin(lp_lat);
                cosphi = cos(lp_lat);
                coslam = cos(lp_lon);
                switch (proj_parm.mode) {
                case equit:
                    xy_y = cosphi * coslam;
                    goto oblcon;
                case obliq:
                    xy_y = proj_parm.sinph0 * sinphi + proj_parm.cosph0 * cosphi * coslam;
            oblcon:
                    if (fabs(fabs(xy_y) - 1.) < tolerance)
                        if (xy_y < 0.)
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        else
                            xy_x = xy_y = 0.;
                    else {
                        xy_y = acos(xy_y);
                        xy_y /= sin(xy_y);
                        xy_x = xy_y * cosphi * sin(lp_lon);
                        xy_y *= (proj_parm.mode == equit) ? sinphi :
                                proj_parm.cosph0 * sinphi - proj_parm.sinph0 * cosphi * coslam;
                    }
                    break;
                case n_pole:
                    lp_lat = -lp_lat;
                    coslam = -coslam;
                    BOOST_FALLTHROUGH;
                case s_pole:
                    if (fabs(lp_lat - half_pi) < epsilon10)
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    xy_x = (xy_y = (half_pi + lp_lat)) * sin(lp_lon);
                    xy_y *= coslam;
                    break;
                }
            }

            template <typename T, typename Par, typename ProjParm>
            inline void s_inverse(T xy_x, T xy_y, T& lp_lon, T& lp_lat, Par const& par, ProjParm const& proj_parm)
            {
                static const T pi = detail::pi<T>();
                static const T half_pi = detail::half_pi<T>();
                    
                T cosc, c_rh, sinc;

                if ((c_rh = boost::math::hypot(xy_x, xy_y)) > pi) {
                    if (c_rh - epsilon10 > pi)
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    c_rh = pi;
                } else if (c_rh < epsilon10) {
                    lp_lat = par.phi0;
                    lp_lon = 0.;
                        return;
                }
                if (proj_parm.mode == obliq || proj_parm.mode == equit) {
                    sinc = sin(c_rh);
                    cosc = cos(c_rh);
                    if (proj_parm.mode == equit) {
                                    lp_lat = aasin(xy_y * sinc / c_rh);
                        xy_x *= sinc;
                        xy_y = cosc * c_rh;
                    } else {
                        lp_lat = aasin(cosc * proj_parm.sinph0 + xy_y * sinc * proj_parm.cosph0 /
                            c_rh);
                        xy_y = (cosc - proj_parm.sinph0 * sin(lp_lat)) * c_rh;
                        xy_x *= sinc * proj_parm.cosph0;
                    }
                    lp_lon = xy_y == 0. ? 0. : atan2(xy_x, xy_y);
                } else if (proj_parm.mode == n_pole) {
                    lp_lat = half_pi - c_rh;
                    lp_lon = atan2(xy_x, -xy_y);
                } else {
                    lp_lat = c_rh - half_pi;
                    lp_lon = atan2(xy_x, xy_y);
                }
            }

            // Azimuthal Equidistant
            template <typename Params, typename Parameters, typename T>
            inline void setup_aeqd(Params const& params, Parameters& par, par_aeqd<T>& proj_parm, bool is_sphere, bool is_guam)
            {
                static const T half_pi = detail::half_pi<T>();

                par.phi0 = pj_get_param_r<T, srs::spar::lat_0>(params, "lat_0", srs::dpar::lat_0);
                if (fabs(fabs(par.phi0) - half_pi) < epsilon10) {
                    proj_parm.mode = par.phi0 < 0. ? s_pole : n_pole;
                    proj_parm.sinph0 = par.phi0 < 0. ? -1. : 1.;
                    proj_parm.cosph0 = 0.;
                } else if (fabs(par.phi0) < epsilon10) {
                    proj_parm.mode = equit;
                    proj_parm.sinph0 = 0.;
                    proj_parm.cosph0 = 1.;
                } else {
                    proj_parm.mode = obliq;
                    proj_parm.sinph0 = sin(par.phi0);
                    proj_parm.cosph0 = cos(par.phi0);
                }
                if (is_sphere) {
                    /* empty */
                } else {
                    proj_parm.en = pj_enfn<T>(par.es);
                    if (is_guam) {
                        proj_parm.M1 = pj_mlfn(par.phi0, proj_parm.sinph0, proj_parm.cosph0, proj_parm.en);
                    } else {
                        switch (proj_parm.mode) {
                        case n_pole:
                            proj_parm.Mp = pj_mlfn<T>(half_pi, 1., 0., proj_parm.en);
                            break;
                        case s_pole:
                            proj_parm.Mp = pj_mlfn<T>(-half_pi, -1., 0., proj_parm.en);
                            break;
                        case equit:
                        case obliq:
                            //proj_parm.N1 = 1. / sqrt(1. - par.es * proj_parm.sinph0 * proj_parm.sinph0);
                            //proj_parm.G = proj_parm.sinph0 * (proj_parm.He = par.e / sqrt(par.one_es));
                            //proj_parm.He *= proj_parm.cosph0;
                            break;
                        }
                        // Boost.Geometry specific, in proj4 geodesic is initialized at the beginning
                        proj_parm.b = math::sqrt(math::sqr(par.a) * (1. - par.es));
                    }
                }
            }

            template <typename T, typename Parameters>
            struct base_aeqd_e
            {
                par_aeqd<T> m_proj_parm;

                // FORWARD(e_forward)  elliptical
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    e_forward(lp_lon, lp_lat, xy_x, xy_y, par, this->m_proj_parm);
                }

                // INVERSE(e_inverse)  elliptical
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    e_inverse(xy_x, xy_y, lp_lon, lp_lat, par, this->m_proj_parm);
                }

                static inline std::string get_name()
                {
                    return "aeqd_e";
                }

            };

            template <typename T, typename Parameters>
            struct base_aeqd_e_guam
            {
                par_aeqd<T> m_proj_parm;

                // FORWARD(e_guam_fwd)  Guam elliptical
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    e_guam_fwd(lp_lon, lp_lat, xy_x, xy_y, par, this->m_proj_parm);
                }

                // INVERSE(e_guam_inv)  Guam elliptical
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    e_guam_inv(xy_x, xy_y, lp_lon, lp_lat, par, this->m_proj_parm);
                }

                static inline std::string get_name()
                {
                    return "aeqd_e_guam";
                }

            };

            template <typename T, typename Parameters>
            struct base_aeqd_s
            {
                par_aeqd<T> m_proj_parm;

                // FORWARD(s_forward)  spherical
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    s_forward(lp_lon, lp_lat, xy_x, xy_y, par, this->m_proj_parm);
                }

                // INVERSE(s_inverse)  spherical
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    s_inverse(xy_x, xy_y, lp_lon, lp_lat, par, this->m_proj_parm);
                }

                static inline std::string get_name()
                {
                    return "aeqd_s";
                }

            };

    }} // namespace detail::aeqd
    #endif // doxygen

    /*!
        \brief Azimuthal Equidistant projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_0: Latitude of origin (degrees)
         - guam (boolean)
        \par Example
        \image html ex_aeqd.gif
    */
    template <typename T, typename Parameters>
    struct aeqd_e : public detail::aeqd::base_aeqd_e<T, Parameters>
    {
        template <typename Params>
        inline aeqd_e(Params const& params, Parameters & par)
        {
            detail::aeqd::setup_aeqd(params, par, this->m_proj_parm, false, false);
        }
    };

    /*!
        \brief Azimuthal Equidistant projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_0: Latitude of origin (degrees)
         - guam (boolean)
        \par Example
        \image html ex_aeqd.gif
    */
    template <typename T, typename Parameters>
    struct aeqd_e_guam : public detail::aeqd::base_aeqd_e_guam<T, Parameters>
    {
        template <typename Params>
        inline aeqd_e_guam(Params const& params, Parameters & par)
        {
            detail::aeqd::setup_aeqd(params, par, this->m_proj_parm, false, true);
        }
    };

    /*!
        \brief Azimuthal Equidistant projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_0: Latitude of origin (degrees)
         - guam (boolean)
        \par Example
        \image html ex_aeqd.gif
    */
    template <typename T, typename Parameters>
    struct aeqd_s : public detail::aeqd::base_aeqd_s<T, Parameters>
    {
        template <typename Params>
        inline aeqd_s(Params const& params, Parameters & par)
        {
            detail::aeqd::setup_aeqd(params, par, this->m_proj_parm, true, false);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        template <typename BGP, typename CT, typename P>
        struct static_projection_type<srs::spar::proj_aeqd, srs_sphere_tag, BGP, CT, P>
        {
            typedef static_wrapper_fi<aeqd_s<CT, P>, P> type;
        };
        template <typename BGP, typename CT, typename P>
        struct static_projection_type<srs::spar::proj_aeqd, srs_spheroid_tag, BGP, CT, P>
        {
            typedef static_wrapper_fi
                <
                    std::conditional_t
                        <
                            std::is_void
                                <
                                    typename geometry::tuples::find_if
                                        <
                                            BGP,
                                            //srs::par4::detail::is_guam
                                            srs::spar::detail::is_param<srs::spar::guam>::pred
                                        >::type
                                >::value,
                            aeqd_e<CT, P>,
                            aeqd_e_guam<CT, P>
                        >
                    , P
                > type;
        };

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_BEGIN(aeqd_entry)
        {
            bool const guam = pj_get_param_b<srs::spar::guam>(params, "guam", srs::dpar::guam);

            if (parameters.es && ! guam)
                return new dynamic_wrapper_fi<aeqd_e<T, Parameters>, T, Parameters>(params, parameters);
            else if (parameters.es && guam)
                return new dynamic_wrapper_fi<aeqd_e_guam<T, Parameters>, T, Parameters>(params, parameters);
            else
                return new dynamic_wrapper_fi<aeqd_s<T, Parameters>, T, Parameters>(params, parameters);
        }
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_END

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(aeqd_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(aeqd, aeqd_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_AEQD_HPP


/* aeqd.hpp
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
*/
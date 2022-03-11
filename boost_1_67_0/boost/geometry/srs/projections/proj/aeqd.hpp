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

#include <boost/type_traits/is_same.hpp>

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
                    typename boost::mpl::if_c
                        <
                            boost::is_same
                                <
                                    typename geometry::tuples::find_if
                                        <
                                            BGP,
                                            //srs::par4::detail::is_guam
                                            srs::spar::detail::is_param<srs::spar::guam>::pred
                                        >::type,
                                    void
                                >::value,
                            aeqd_e<CT, P>,
                            aeqd_e_guam<CT, P>
                        >::type
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
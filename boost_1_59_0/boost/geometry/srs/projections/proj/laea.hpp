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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LAEA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LAEA_HPP

#include <boost/config.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_auth.hpp>
#include <boost/geometry/srs/projections/impl/pj_qsfn.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace laea
    {
            static const double epsilon10 = 1.e-10;

            enum mode_type {
                n_pole = 0,
                s_pole = 1,
                equit  = 2,
                obliq  = 3
            };

            template <typename T>
            struct par_laea
            {
                T   sinb1;
                T   cosb1;
                T   xmf;
                T   ymf;
                T   mmf;
                T   qp;
                T   dd;
                T   rq;
                detail::apa<T> apa;
                mode_type mode;
            };

            template <typename T, typename Parameters>
            struct base_laea_ellipsoid
            {
                par_laea<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T coslam, sinlam, sinphi, q, sinb=0.0, cosb=0.0, b=0.0;

                    coslam = cos(lp_lon);
                    sinlam = sin(lp_lon);
                    sinphi = sin(lp_lat);
                    q = pj_qsfn(sinphi, par.e, par.one_es);

                    if (this->m_proj_parm.mode == obliq || this->m_proj_parm.mode == equit) {
                        sinb = q / this->m_proj_parm.qp;
                        cosb = sqrt(1. - sinb * sinb);
                    }

                    switch (this->m_proj_parm.mode) {
                    case obliq:
                        b = 1. + this->m_proj_parm.sinb1 * sinb + this->m_proj_parm.cosb1 * cosb * coslam;
                        break;
                    case equit:
                        b = 1. + cosb * coslam;
                        break;
                    case n_pole:
                        b = half_pi + lp_lat;
                        q = this->m_proj_parm.qp - q;
                        break;
                    case s_pole:
                        b = lp_lat - half_pi;
                        q = this->m_proj_parm.qp + q;
                        break;
                    }
                    if (fabs(b) < epsilon10) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }

                    switch (this->m_proj_parm.mode) {
                    case obliq:
                        b = sqrt(2. / b);
                        xy_y = this->m_proj_parm.ymf * b * (this->m_proj_parm.cosb1 * sinb - this->m_proj_parm.sinb1 * cosb * coslam);
                        goto eqcon;
                        break;
                    case equit:
                        b = sqrt(2. / (1. + cosb * coslam));
                        xy_y = b * sinb * this->m_proj_parm.ymf;
                eqcon:
                        xy_x = this->m_proj_parm.xmf * b * cosb * sinlam;
                        break;
                    case n_pole:
                    case s_pole:
                        if (q >= 0.) {
                            b = sqrt(q);
                            xy_x = b * sinlam;
                            xy_y = coslam * (this->m_proj_parm.mode == s_pole ? b : -b);
                        } else
                            xy_x = xy_y = 0.;
                        break;
                    }
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T cCe, sCe, q, rho, ab=0.0;

                    switch (this->m_proj_parm.mode) {
                    case equit:
                    case obliq:
                        xy_x /= this->m_proj_parm.dd;
                        xy_y *=  this->m_proj_parm.dd;
                        rho = boost::math::hypot(xy_x, xy_y);
                        if (rho < epsilon10) {
                            lp_lon = 0.;
                            lp_lat = par.phi0;
                            return;
                        }
                        sCe = 2. * asin(.5 * rho / this->m_proj_parm.rq);
                        cCe = cos(sCe);
                        sCe = sin(sCe);
                        xy_x *= sCe;
                        if (this->m_proj_parm.mode == obliq) {
                            ab = cCe * this->m_proj_parm.sinb1 + xy_y * sCe * this->m_proj_parm.cosb1 / rho;
                            xy_y = rho * this->m_proj_parm.cosb1 * cCe - xy_y * this->m_proj_parm.sinb1 * sCe;
                        } else {
                            ab = xy_y * sCe / rho;
                            xy_y = rho * cCe;
                        }
                        break;
                    case n_pole:
                        xy_y = -xy_y;
                        BOOST_FALLTHROUGH;
                    case s_pole:
                        q = (xy_x * xy_x + xy_y * xy_y);
                        if (q == 0.0) {
                            lp_lon = 0.;
                            lp_lat = par.phi0;
                            return;
                        }
                        ab = 1. - q / this->m_proj_parm.qp;
                        if (this->m_proj_parm.mode == s_pole)
                            ab = - ab;
                        break;
                    }
                    lp_lon = atan2(xy_x, xy_y);
                    lp_lat = pj_authlat(asin(ab), this->m_proj_parm.apa);
                }

                static inline std::string get_name()
                {
                    return "laea_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_laea_spheroid
            {
                par_laea<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    T  coslam, cosphi, sinphi;

                    sinphi = sin(lp_lat);
                    cosphi = cos(lp_lat);
                    coslam = cos(lp_lon);
                    switch (this->m_proj_parm.mode) {
                    case equit:
                        xy_y = 1. + cosphi * coslam;
                        goto oblcon;
                    case obliq:
                        xy_y = 1. + this->m_proj_parm.sinb1 * sinphi + this->m_proj_parm.cosb1 * cosphi * coslam;
                oblcon:
                        if (xy_y <= epsilon10) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        xy_y = sqrt(2. / xy_y);
                        xy_x = xy_y * cosphi * sin(lp_lon);
                        xy_y *= this->m_proj_parm.mode == equit ? sinphi :
                           this->m_proj_parm.cosb1 * sinphi - this->m_proj_parm.sinb1 * cosphi * coslam;
                        break;
                    case n_pole:
                        coslam = -coslam;
                        BOOST_FALLTHROUGH;
                    case s_pole:
                        if (fabs(lp_lat + par.phi0) < epsilon10) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        xy_y = fourth_pi - lp_lat * .5;
                        xy_y = 2. * (this->m_proj_parm.mode == s_pole ? cos(xy_y) : sin(xy_y));
                        xy_x = xy_y * sin(lp_lon);
                        xy_y *= coslam;
                        break;
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T  cosz=0.0, rh, sinz=0.0;

                    rh = boost::math::hypot(xy_x, xy_y);
                    if ((lp_lat = rh * .5 ) > 1.) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    lp_lat = 2. * asin(lp_lat);
                    if (this->m_proj_parm.mode == obliq || this->m_proj_parm.mode == equit) {
                        sinz = sin(lp_lat);
                        cosz = cos(lp_lat);
                    }
                    switch (this->m_proj_parm.mode) {
                    case equit:
                        lp_lat = fabs(rh) <= epsilon10 ? 0. : asin(xy_y * sinz / rh);
                        xy_x *= sinz;
                        xy_y = cosz * rh;
                        break;
                    case obliq:
                        lp_lat = fabs(rh) <= epsilon10 ? par.phi0 :
                           asin(cosz * this->m_proj_parm.sinb1 + xy_y * sinz * this->m_proj_parm.cosb1 / rh);
                        xy_x *= sinz * this->m_proj_parm.cosb1;
                        xy_y = (cosz - sin(lp_lat) * this->m_proj_parm.sinb1) * rh;
                        break;
                    case n_pole:
                        xy_y = -xy_y;
                        lp_lat = half_pi - lp_lat;
                        break;
                    case s_pole:
                        lp_lat -= half_pi;
                        break;
                    }
                    lp_lon = (xy_y == 0. && (this->m_proj_parm.mode == equit || this->m_proj_parm.mode == obliq)) ?
                        0. : atan2(xy_x, xy_y);
                }

                static inline std::string get_name()
                {
                    return "laea_spheroid";
                }

            };

            // Lambert Azimuthal Equal Area
            template <typename Parameters, typename T>
            inline void setup_laea(Parameters& par, par_laea<T>& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();

                T t;

                t = fabs(par.phi0);
                if (fabs(t - half_pi) < epsilon10)
                    proj_parm.mode = par.phi0 < 0. ? s_pole : n_pole;
                else if (fabs(t) < epsilon10)
                    proj_parm.mode = equit;
                else
                    proj_parm.mode = obliq;
                if (par.es != 0.0) {
                    double sinphi;

                    par.e = sqrt(par.es); // TODO : Isn't it already set?
                    proj_parm.qp = pj_qsfn(1., par.e, par.one_es);
                    proj_parm.mmf = .5 / (1. - par.es);
                    proj_parm.apa = pj_authset<T>(par.es);
                    switch (proj_parm.mode) {
                    case n_pole:
                    case s_pole:
                        proj_parm.dd = 1.;
                        break;
                    case equit:
                        proj_parm.dd = 1. / (proj_parm.rq = sqrt(.5 * proj_parm.qp));
                        proj_parm.xmf = 1.;
                        proj_parm.ymf = .5 * proj_parm.qp;
                        break;
                    case obliq:
                        proj_parm.rq = sqrt(.5 * proj_parm.qp);
                        sinphi = sin(par.phi0);
                        proj_parm.sinb1 = pj_qsfn(sinphi, par.e, par.one_es) / proj_parm.qp;
                        proj_parm.cosb1 = sqrt(1. - proj_parm.sinb1 * proj_parm.sinb1);
                        proj_parm.dd = cos(par.phi0) / (sqrt(1. - par.es * sinphi * sinphi) *
                           proj_parm.rq * proj_parm.cosb1);
                        proj_parm.ymf = (proj_parm.xmf = proj_parm.rq) / proj_parm.dd;
                        proj_parm.xmf *= proj_parm.dd;
                        break;
                    }
                } else {
                    if (proj_parm.mode == obliq) {
                        proj_parm.sinb1 = sin(par.phi0);
                        proj_parm.cosb1 = cos(par.phi0);
                    }
                }
            }

    }} // namespace laea
    #endif // doxygen

    /*!
        \brief Lambert Azimuthal Equal Area projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_laea.gif
    */
    template <typename T, typename Parameters>
    struct laea_ellipsoid : public detail::laea::base_laea_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline laea_ellipsoid(Params const& , Parameters & par)
        {
            detail::laea::setup_laea(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Lambert Azimuthal Equal Area projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_laea.gif
    */
    template <typename T, typename Parameters>
    struct laea_spheroid : public detail::laea::base_laea_spheroid<T, Parameters>
    {
        template <typename Params>
        inline laea_spheroid(Params const& , Parameters & par)
        {
            detail::laea::setup_laea(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_laea, laea_spheroid, laea_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(laea_entry, laea_spheroid, laea_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(laea_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(laea, laea_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LAEA_HPP


/* laea.hpp
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
*/
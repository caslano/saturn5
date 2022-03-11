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
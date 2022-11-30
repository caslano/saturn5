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

#ifndef BOOST_GEOMETRY_PROJECTIONS_NSPER_HPP
#define BOOST_GEOMETRY_PROJECTIONS_NSPER_HPP

#include <boost/config.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/math/special_functions/hypot.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace nsper
    {

            static const double epsilon10 = 1.e-10;
            enum mode_type {
                n_pole = 0,
                s_pole = 1,
                equit  = 2,
                obliq  = 3
            };

            template <typename T>
            struct par_nsper
            {
                T   height;
                T   sinph0;
                T   cosph0;
                T   p;
                T   rp;
                T   pn1;
                T   pfact;
                T   h;
                T   cg;
                T   sg;
                T   sw;
                T   cw;
                mode_type mode;
                bool tilt;
            };

            template <typename T, typename Parameters>
            struct base_nsper_spheroid
            {
                par_nsper<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T  coslam, cosphi, sinphi;

                    sinphi = sin(lp_lat);
                    cosphi = cos(lp_lat);
                    coslam = cos(lp_lon);
                    switch (this->m_proj_parm.mode) {
                    case obliq:
                        xy_y = this->m_proj_parm.sinph0 * sinphi + this->m_proj_parm.cosph0 * cosphi * coslam;
                        break;
                    case equit:
                        xy_y = cosphi * coslam;
                        break;
                    case s_pole:
                        xy_y = - sinphi;
                        break;
                    case n_pole:
                        xy_y = sinphi;
                        break;
                    }
                    if (xy_y < this->m_proj_parm.rp) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    xy_y = this->m_proj_parm.pn1 / (this->m_proj_parm.p - xy_y);
                    xy_x = xy_y * cosphi * sin(lp_lon);
                    switch (this->m_proj_parm.mode) {
                    case obliq:
                        xy_y *= (this->m_proj_parm.cosph0 * sinphi -
                           this->m_proj_parm.sinph0 * cosphi * coslam);
                        break;
                    case equit:
                        xy_y *= sinphi;
                        break;
                    case n_pole:
                        coslam = - coslam;
                        BOOST_FALLTHROUGH;
                    case s_pole:
                        xy_y *= cosphi * coslam;
                        break;
                    }
                    if (this->m_proj_parm.tilt) {
                        T yt, ba;

                        yt = xy_y * this->m_proj_parm.cg + xy_x * this->m_proj_parm.sg;
                        ba = 1. / (yt * this->m_proj_parm.sw * this->m_proj_parm.h + this->m_proj_parm.cw);
                        xy_x = (xy_x * this->m_proj_parm.cg - xy_y * this->m_proj_parm.sg) * this->m_proj_parm.cw * ba;
                        xy_y = yt * ba;
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T  rh, cosz, sinz;

                    if (this->m_proj_parm.tilt) {
                        T bm, bq, yt;

                        yt = 1./(this->m_proj_parm.pn1 - xy_y * this->m_proj_parm.sw);
                        bm = this->m_proj_parm.pn1 * xy_x * yt;
                        bq = this->m_proj_parm.pn1 * xy_y * this->m_proj_parm.cw * yt;
                        xy_x = bm * this->m_proj_parm.cg + bq * this->m_proj_parm.sg;
                        xy_y = bq * this->m_proj_parm.cg - bm * this->m_proj_parm.sg;
                    }
                    rh = boost::math::hypot(xy_x, xy_y);
                    if ((sinz = 1. - rh * rh * this->m_proj_parm.pfact) < 0.) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    sinz = (this->m_proj_parm.p - sqrt(sinz)) / (this->m_proj_parm.pn1 / rh + rh / this->m_proj_parm.pn1);
                    cosz = sqrt(1. - sinz * sinz);
                    if (fabs(rh) <= epsilon10) {
                        lp_lon = 0.;
                        lp_lat = par.phi0;
                    } else {
                        switch (this->m_proj_parm.mode) {
                        case obliq:
                            lp_lat = asin(cosz * this->m_proj_parm.sinph0 + xy_y * sinz * this->m_proj_parm.cosph0 / rh);
                            xy_y = (cosz - this->m_proj_parm.sinph0 * sin(lp_lat)) * rh;
                            xy_x *= sinz * this->m_proj_parm.cosph0;
                            break;
                        case equit:
                            lp_lat = asin(xy_y * sinz / rh);
                            xy_y = cosz * rh;
                            xy_x *= sinz;
                            break;
                        case n_pole:
                            lp_lat = asin(cosz);
                            xy_y = -xy_y;
                            break;
                        case s_pole:
                            lp_lat = - asin(cosz);
                            break;
                        }
                        lp_lon = atan2(xy_x, xy_y);
                    }
                }

                static inline std::string get_name()
                {
                    return "nsper_spheroid";
                }

            };

            template <typename Params, typename Parameters, typename T>
            inline void setup(Params const& params, Parameters& par, par_nsper<T>& proj_parm) 
            {
                proj_parm.height = pj_get_param_f<T, srs::spar::h>(params, "h", srs::dpar::h);
                if (proj_parm.height <= 0.)
                    BOOST_THROW_EXCEPTION( projection_exception(error_h_less_than_zero) );

                if (fabs(fabs(par.phi0) - geometry::math::half_pi<T>()) < epsilon10)
                    proj_parm.mode = par.phi0 < 0. ? s_pole : n_pole;
                else if (fabs(par.phi0) < epsilon10)
                    proj_parm.mode = equit;
                else {
                    proj_parm.mode = obliq;
                    proj_parm.sinph0 = sin(par.phi0);
                    proj_parm.cosph0 = cos(par.phi0);
                }
                proj_parm.pn1 = proj_parm.height / par.a; /* normalize by radius */
                proj_parm.p = 1. + proj_parm.pn1;
                proj_parm.rp = 1. / proj_parm.p;
                proj_parm.h = 1. / proj_parm.pn1;
                proj_parm.pfact = (proj_parm.p + 1.) * proj_parm.h;
                par.es = 0.;
            }


            // Near-sided perspective
            template <typename Params, typename Parameters, typename T>
            inline void setup_nsper(Params const& params, Parameters& par, par_nsper<T>& proj_parm)
            {
                proj_parm.tilt = false;

                setup(params, par, proj_parm);
            }

            // Tilted perspective
            template <typename Params, typename Parameters, typename T>
            inline void setup_tpers(Params const& params, Parameters& par, par_nsper<T>& proj_parm)
            {
                T const omega = pj_get_param_r<T, srs::spar::tilt>(params, "tilt", srs::dpar::tilt);
                T const gamma = pj_get_param_r<T, srs::spar::azi>(params, "azi", srs::dpar::azi);
                proj_parm.tilt = true;
                proj_parm.cg = cos(gamma); proj_parm.sg = sin(gamma);
                proj_parm.cw = cos(omega); proj_parm.sw = sin(omega);

                setup(params, par, proj_parm);
            }

    }} // namespace detail::nsper
    #endif // doxygen

    /*!
        \brief Near-sided perspective projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
        \par Projection parameters
         - h: Height
        \par Example
        \image html ex_nsper.gif
    */
    template <typename T, typename Parameters>
    struct nsper_spheroid : public detail::nsper::base_nsper_spheroid<T, Parameters>
    {
        template <typename Params>
        inline nsper_spheroid(Params const& params, Parameters & par)
        {
            detail::nsper::setup_nsper(params, par, this->m_proj_parm);
        }
    };

    /*!
        \brief Tilted perspective projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
        \par Projection parameters
         - tilt: Tilt, or Omega (real)
         - azi: Azimuth (or Gamma) (real)
         - h: Height
        \par Example
        \image html ex_tpers.gif
    */
    template <typename T, typename Parameters>
    struct tpers_spheroid : public detail::nsper::base_nsper_spheroid<T, Parameters>
    {
        template <typename Params>
        inline tpers_spheroid(Params const& params, Parameters & par)
        {
            detail::nsper::setup_tpers(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_nsper, nsper_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_tpers, tpers_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(nsper_entry, nsper_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(tpers_entry, tpers_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(nsper_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(nsper, nsper_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(tpers, tpers_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_NSPER_HPP


/* nsper.hpp
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
*/
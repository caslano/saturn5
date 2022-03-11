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
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ORTHO_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ORTHO_HPP

#include <boost/config.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace ortho
    {

            enum mode_type {
                n_pole = 0,
                s_pole = 1,
                equit  = 2,
                obliq  = 3
            };

            template <typename T>
            struct par_ortho
            {
                T   sinph0;
                T   cosph0;
                mode_type mode;
            };

            static const double epsilon10 = 1.e-10;

            template <typename T, typename Parameters>
            struct base_ortho_spheroid
            {
                par_ortho<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T coslam, cosphi, sinphi;

                    cosphi = cos(lp_lat);
                    coslam = cos(lp_lon);
                    switch (this->m_proj_parm.mode) {
                    case equit:
                        if (cosphi * coslam < - epsilon10) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        xy_y = sin(lp_lat);
                        break;
                    case obliq:
                        if (this->m_proj_parm.sinph0 * (sinphi = sin(lp_lat)) +
                           this->m_proj_parm.cosph0 * cosphi * coslam < - epsilon10) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        xy_y = this->m_proj_parm.cosph0 * sinphi - this->m_proj_parm.sinph0 * cosphi * coslam;
                        break;
                    case n_pole:
                        coslam = - coslam;
                        BOOST_FALLTHROUGH;
                    case s_pole:
                        if (fabs(lp_lat - par.phi0) - epsilon10 > half_pi) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        xy_y = cosphi * coslam;
                        break;
                    }
                    xy_x = cosphi * sin(lp_lon);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T rh, cosc, sinc;

                    if ((sinc = (rh = boost::math::hypot(xy_x, xy_y))) > 1.) {
                        if ((sinc - 1.) > epsilon10) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        sinc = 1.;
                    }
                    cosc = sqrt(1. - sinc * sinc); /* in this range OK */
                    if (fabs(rh) <= epsilon10) {
                        lp_lat = par.phi0;
                        lp_lon = 0.0;
                    } else {
                        switch (this->m_proj_parm.mode) {
                        case n_pole:
                            xy_y = -xy_y;
                            lp_lat = acos(sinc);
                            break;
                        case s_pole:
                            lp_lat = - acos(sinc);
                            break;
                        case equit:
                            lp_lat = xy_y * sinc / rh;
                            xy_x *= sinc;
                            xy_y = cosc * rh;
                            goto sinchk;
                        case obliq:
                            lp_lat = cosc * this->m_proj_parm.sinph0 + xy_y * sinc * this->m_proj_parm.cosph0 /rh;
                            xy_y = (cosc - this->m_proj_parm.sinph0 * lp_lat) * rh;
                            xy_x *= sinc * this->m_proj_parm.cosph0;
                        sinchk:
                            if (fabs(lp_lat) >= 1.)
                                lp_lat = lp_lat < 0. ? -half_pi : half_pi;
                            else
                                lp_lat = asin(lp_lat);
                            break;
                        }
                        lp_lon = (xy_y == 0. && (this->m_proj_parm.mode == obliq || this->m_proj_parm.mode == equit))
                             ? (xy_x == 0. ? 0. : xy_x < 0. ? -half_pi : half_pi)
                                           : atan2(xy_x, xy_y);
                    }
                }

                static inline std::string get_name()
                {
                    return "ortho_spheroid";
                }

            };

            // Orthographic
            template <typename Parameters, typename T>
            inline void setup_ortho(Parameters& par, par_ortho<T>& proj_parm)
            {
                if (fabs(fabs(par.phi0) - geometry::math::half_pi<T>()) <= epsilon10)
                    proj_parm.mode = par.phi0 < 0. ? s_pole : n_pole;
                else if (fabs(par.phi0) > epsilon10) {
                    proj_parm.mode = obliq;
                    proj_parm.sinph0 = sin(par.phi0);
                    proj_parm.cosph0 = cos(par.phi0);
                } else
                    proj_parm.mode = equit;
                par.es = 0.;
            }

    }} // namespace detail::ortho
    #endif // doxygen

    /*!
        \brief Orthographic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
        \par Example
        \image html ex_ortho.gif
    */
    template <typename T, typename Parameters>
    struct ortho_spheroid : public detail::ortho::base_ortho_spheroid<T, Parameters>
    {
        template <typename Params>
        inline ortho_spheroid(Params const& , Parameters & par)
        {
            detail::ortho::setup_ortho(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_ortho, ortho_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(ortho_entry, ortho_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(ortho_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(ortho, ortho_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ORTHO_HPP


/* ortho.hpp
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
*/
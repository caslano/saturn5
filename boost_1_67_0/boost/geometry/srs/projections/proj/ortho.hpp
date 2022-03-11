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
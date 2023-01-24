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
Os9EDlmiBH7eE1+QjR3MPtpfffRhOebOuoT0homhkINrKNsBf1YAws32cDUwO2hdiB4MDtTj3YZcO9b+/A5M4+0ORNduu/wGTA5CN+3yTVgeyNcKuzQGJHWkbQRrMDaqvnb9nQRtuG3oa3A2iHbIO4g28FfKTYt7vthnz0oXsDvoW5VnD3+Tyj1Yrv3pBcLc8eu8I94BK4t+xmMX3DHB077xSoI2EEYqYoITUgLu7ngHn7GH9PqeMq6LX1idjbEi3VgCJjdTvy1M1qL4qR5FHMY+8gX+WCT84sJPQmtFEilgVrUpeIggNxguOb3jXUjBYbUOTzrJXUAlJMEbsxMaQtViKdCdPf/76RN7wBjTDrZTozCD1QNf/IkUSOhoDHaQIAhFgfNzSsFDRe3Om8EXzsHBs81kDo3anXfsE2VBk5c8fE0K3djM85asunRr/LoCNtrHPY6XaI+1NzChW+63zi1zNMzCcmuY4s5K8arRqBHyGb1B0jAi+CM9hiMPytKi5dGyP4+kuV6Ya/EW79cumvAtJ495WA2UOW0HYja5uEQYRFRG5IaBzOZfbZCihBPxXTRLn79LFBQsGfPVd9PVK+b2jYlH/yZ27wQShkmi2zEP0/oxHv1SyEoljspCEysQDZkjRPMJMaYTCMu/CA8u+mZ8X/17Bg/4UL3pJVS9meGdCf/7aOdS/nfIjn9puemL22wKUzTTJuE5Ea/U
*/
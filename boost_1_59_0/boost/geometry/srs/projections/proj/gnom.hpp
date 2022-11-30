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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GNOM_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GNOM_HPP

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
    namespace detail { namespace gnom
    {

            static const double epsilon10 = 1.e-10;
            enum mode_type {
                n_pole = 0,
                s_pole = 1,
                equit  = 2,
                obliq  = 3
            };

            template <typename T>
            struct par_gnom
            {
                T    sinph0;
                T    cosph0;
                mode_type mode;
            };

            template <typename T, typename Parameters>
            struct base_gnom_spheroid
            {
                par_gnom<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T  coslam, cosphi, sinphi;

                    sinphi = sin(lp_lat);
                    cosphi = cos(lp_lat);
                    coslam = cos(lp_lon);

                    switch (this->m_proj_parm.mode) {
                    case equit:
                        xy_y = cosphi * coslam;
                        break;
                    case obliq:
                        xy_y = this->m_proj_parm.sinph0 * sinphi + this->m_proj_parm.cosph0 * cosphi * coslam;
                        break;
                    case s_pole:
                        xy_y = - sinphi;
                        break;
                    case n_pole:
                        xy_y = sinphi;
                        break;
                    }

                    if (xy_y <= epsilon10) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }

                    xy_x = (xy_y = 1. / xy_y) * cosphi * sin(lp_lon);
                    switch (this->m_proj_parm.mode) {
                    case equit:
                        xy_y *= sinphi;
                        break;
                    case obliq:
                        xy_y *= this->m_proj_parm.cosph0 * sinphi - this->m_proj_parm.sinph0 * cosphi * coslam;
                        break;
                    case n_pole:
                        coslam = - coslam;
                        BOOST_FALLTHROUGH;
                    case s_pole:
                        xy_y *= cosphi * coslam;
                        break;
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T  rh, cosz, sinz;

                    rh = boost::math::hypot(xy_x, xy_y);
                    sinz = sin(lp_lat = atan(rh));
                    cosz = sqrt(1. - sinz * sinz);

                    if (fabs(rh) <= epsilon10) {
                        lp_lat = par.phi0;
                        lp_lon = 0.;
                    } else {
                        switch (this->m_proj_parm.mode) {
                        case obliq:
                            lp_lat = cosz * this->m_proj_parm.sinph0 + xy_y * sinz * this->m_proj_parm.cosph0 / rh;
                            if (fabs(lp_lat) >= 1.)
                                lp_lat = lp_lat > 0. ? half_pi : -half_pi;
                            else
                                lp_lat = asin(lp_lat);
                            xy_y = (cosz - this->m_proj_parm.sinph0 * sin(lp_lat)) * rh;
                            xy_x *= sinz * this->m_proj_parm.cosph0;
                            break;
                        case equit:
                            lp_lat = xy_y * sinz / rh;
                            if (fabs(lp_lat) >= 1.)
                                lp_lat = lp_lat > 0. ? half_pi : -half_pi;
                            else
                                lp_lat = asin(lp_lat);
                            xy_y = cosz * rh;
                            xy_x *= sinz;
                            break;
                        case s_pole:
                            lp_lat -= half_pi;
                            break;
                        case n_pole:
                            lp_lat = half_pi - lp_lat;
                            xy_y = -xy_y;
                            break;
                        }
                        lp_lon = atan2(xy_x, xy_y);
                    }
                }

                static inline std::string get_name()
                {
                    return "gnom_spheroid";
                }

            };

            // Gnomonic
            template <typename Parameters, typename T>
            inline void setup_gnom(Parameters& par, par_gnom<T>& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();

                if (fabs(fabs(par.phi0) - half_pi) < epsilon10) {
                    proj_parm.mode = par.phi0 < 0. ? s_pole : n_pole;
                } else if (fabs(par.phi0) < epsilon10) {
                    proj_parm.mode = equit;
                } else {
                    proj_parm.mode = obliq;
                    proj_parm.sinph0 = sin(par.phi0);
                    proj_parm.cosph0 = cos(par.phi0);
                }

                par.es = 0.;
            }

    }} // namespace detail::gnom
    #endif // doxygen

    /*!
        \brief Gnomonic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
        \par Example
        \image html ex_gnom.gif
    */
    template <typename T, typename Parameters>
    struct gnom_spheroid : public detail::gnom::base_gnom_spheroid<T, Parameters>
    {
        template <typename Params>
        inline gnom_spheroid(Params const& , Parameters & par)
        {
            detail::gnom::setup_gnom(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_gnom, gnom_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(gnom_entry, gnom_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(gnom_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(gnom, gnom_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GNOM_HPP


/* gnom.hpp
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
*/
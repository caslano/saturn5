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
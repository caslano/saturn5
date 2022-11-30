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

// Copyright (c) 2003   Gerald I. Evenden

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_STEREA_HPP
#define BOOST_GEOMETRY_PROJECTIONS_STEREA_HPP

#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_gauss.hpp>


namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace sterea
    {

            template <typename T>
            struct par_sterea
            {
                T phic0;
                T cosc0, sinc0;
                T R2;
                gauss<T> en;
            };

            template <typename T, typename Parameters>
            struct base_sterea_ellipsoid
            {
                par_sterea<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T cosc, sinc, cosl_, k;

                    detail::gauss_fwd(m_proj_parm.en, lp_lon, lp_lat);
                    sinc = sin(lp_lat);
                    cosc = cos(lp_lat);
                    cosl_ = cos(lp_lon);
                    k = par.k0 * this->m_proj_parm.R2 / (1. + this->m_proj_parm.sinc0 * sinc + this->m_proj_parm.cosc0 * cosc * cosl_);
                    xy_x = k * cosc * sin(lp_lon);
                    xy_y = k * (this->m_proj_parm.cosc0 * sinc - this->m_proj_parm.sinc0 * cosc * cosl_);
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T rho, c, sinc, cosc;

                    xy_x /= par.k0;
                    xy_y /= par.k0;
                    if((rho = boost::math::hypot(xy_x, xy_y)) != 0.0) {
                        c = 2. * atan2(rho, this->m_proj_parm.R2);
                        sinc = sin(c);
                        cosc = cos(c);
                        lp_lat = asin(cosc * this->m_proj_parm.sinc0 + xy_y * sinc * this->m_proj_parm.cosc0 / rho);
                        lp_lon = atan2(xy_x * sinc, rho * this->m_proj_parm.cosc0 * cosc -
                                        xy_y * this->m_proj_parm.sinc0 * sinc);
                    } else {
                        lp_lat = this->m_proj_parm.phic0;
                        lp_lon = 0.;
                    }
                    detail::gauss_inv(m_proj_parm.en, lp_lon, lp_lat);
                }

                static inline std::string get_name()
                {
                    return "sterea_ellipsoid";
                }

            };

            // Oblique Stereographic Alternative
            template <typename Parameters, typename T>
            inline void setup_sterea(Parameters const& par, par_sterea<T>& proj_parm)
            {
                T R;

                proj_parm.en = detail::gauss_ini(par.e, par.phi0, proj_parm.phic0, R);
                proj_parm.sinc0 = sin(proj_parm.phic0);
                proj_parm.cosc0 = cos(proj_parm.phic0);
                proj_parm.R2 = 2. * R;
            }

    }} // namespace detail::sterea
    #endif // doxygen

    /*!
        \brief Oblique Stereographic Alternative projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_sterea.gif
    */
    template <typename T, typename Parameters>
    struct sterea_ellipsoid : public detail::sterea::base_sterea_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline sterea_ellipsoid(Params const& , Parameters const& par)
        {
            detail::sterea::setup_sterea(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_sterea, sterea_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(sterea_entry, sterea_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(sterea_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(sterea, sterea_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_STEREA_HPP


/* sterea.hpp
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
*/
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
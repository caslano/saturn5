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

// Purpose:  Implementation of the airy (Airy) projection.
// Author:   Gerald Evenden (1995)
//           Thomas Knudsen (2016) - revise/add regression tests
// Copyright (c) 1995, Gerald Evenden

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_AIRY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_AIRY_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace airy
    {

            static const double epsilon = 1.e-10;
            enum mode_type {
                n_pole = 0,
                s_pole = 1,
                equit  = 2,
                obliq  = 3
            };

            template <typename T>
            struct par_airy
            {
                T    p_halfpi;
                T    sinph0;
                T    cosph0;
                T    Cb;
                mode_type mode;
                bool no_cut;    /* do not cut at hemisphere limit */
            };

            template <typename T, typename Parameters>
            struct base_airy_spheroid
            {
                par_airy<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T  sinlam, coslam, cosphi, sinphi, t, s, Krho, cosz;

                    sinlam = sin(lp_lon);
                    coslam = cos(lp_lon);
                    switch (this->m_proj_parm.mode) {
                    case equit:
                    case obliq:
                        sinphi = sin(lp_lat);
                        cosphi = cos(lp_lat);
                        cosz = cosphi * coslam;
                        if (this->m_proj_parm.mode == obliq)
                            cosz = this->m_proj_parm.sinph0 * sinphi + this->m_proj_parm.cosph0 * cosz;
                        if (!this->m_proj_parm.no_cut && cosz < -epsilon) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        if (fabs(s = 1. - cosz) > epsilon) {
                            t = 0.5 * (1. + cosz);
                            Krho = -log(t)/s - this->m_proj_parm.Cb / t;
                        } else
                            Krho = 0.5 - this->m_proj_parm.Cb;
                        xy_x = Krho * cosphi * sinlam;
                        if (this->m_proj_parm.mode == obliq)
                            xy_y = Krho * (this->m_proj_parm.cosph0 * sinphi -
                                this->m_proj_parm.sinph0 * cosphi * coslam);
                        else
                            xy_y = Krho * sinphi;
                        break;
                    case s_pole:
                    case n_pole:
                        lp_lat = fabs(this->m_proj_parm.p_halfpi - lp_lat);
                        if (!this->m_proj_parm.no_cut && (lp_lat - epsilon) > half_pi)
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        if ((lp_lat *= 0.5) > epsilon) {
                            t = tan(lp_lat);
                            Krho = -2.*(log(cos(lp_lat)) / t + t * this->m_proj_parm.Cb);
                            xy_x = Krho * sinlam;
                            xy_y = Krho * coslam;
                            if (this->m_proj_parm.mode == n_pole)
                                xy_y = -xy_y;
                        } else
                            xy_x = xy_y = 0.;
                    }
                }

                static inline std::string get_name()
                {
                    return "airy_spheroid";
                }

            };

            // Airy
            template <typename Params, typename Parameters, typename T>
            inline void setup_airy(Params const& params, Parameters& par, par_airy<T>& proj_parm)
            {
                static const T half_pi = detail::half_pi<T>();

                T beta;

                proj_parm.no_cut = pj_get_param_b<srs::spar::no_cut>(params, "no_cut", srs::dpar::no_cut);
                beta = 0.5 * (half_pi - pj_get_param_r<T, srs::spar::lat_b>(params, "lat_b", srs::dpar::lat_b));
                if (fabs(beta) < epsilon)
                    proj_parm.Cb = -0.5;
                else {
                    proj_parm.Cb = 1./tan(beta);
                    proj_parm.Cb *= proj_parm.Cb * log(cos(beta));
                }

                if (fabs(fabs(par.phi0) - half_pi) < epsilon)
                    if (par.phi0 < 0.) {
                        proj_parm.p_halfpi = -half_pi;
                        proj_parm.mode = s_pole;
                    } else {
                        proj_parm.p_halfpi =  half_pi;
                        proj_parm.mode = n_pole;
                    }
                else {
                    if (fabs(par.phi0) < epsilon)
                        proj_parm.mode = equit;
                    else {
                        proj_parm.mode = obliq;
                        proj_parm.sinph0 = sin(par.phi0);
                        proj_parm.cosph0 = cos(par.phi0);
                    }
                }
                par.es = 0.;
            }

    }} // namespace detail::airy
    #endif // doxygen

    /*!
        \brief Airy projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Projection parameters
         - no_cut: Do not cut at hemisphere limit (boolean)
         - lat_b (degrees)
        \par Example
        \image html ex_airy.gif
    */
    template <typename T, typename Parameters>
    struct airy_spheroid : public detail::airy::base_airy_spheroid<T, Parameters>
    {
        template <typename Params>
        inline airy_spheroid(Params const& params, Parameters & par)
        {
            detail::airy::setup_airy(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_airy, airy_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(airy_entry, airy_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(airy_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(airy, airy_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_AIRY_HPP


/* airy.hpp
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
*/
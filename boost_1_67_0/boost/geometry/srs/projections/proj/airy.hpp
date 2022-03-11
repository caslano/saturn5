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
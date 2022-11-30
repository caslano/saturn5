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

#ifndef BOOST_GEOMETRY_PROJECTIONS_SOMERC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_SOMERC_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/aasincos.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace somerc
    {
            static const double epsilon = 1.e-10;
            static const int n_iter = 6;

            template <typename T>
            struct par_somerc
            {
                T K, c, hlf_e, kR, cosp0, sinp0;
            };

            template <typename T, typename Parameters>
            struct base_somerc_ellipsoid
            {
                par_somerc<T> m_proj_parm;

                // FORWARD(e_forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T half_pi = detail::half_pi<T>();

                    T phip, lamp, phipp, lampp, sp, cp;

                    sp = par.e * sin(lp_lat);
                    phip = 2.* atan( exp( this->m_proj_parm.c * (
                        log(tan(fourth_pi + 0.5 * lp_lat)) - this->m_proj_parm.hlf_e * log((1. + sp)/(1. - sp)))
                        + this->m_proj_parm.K)) - half_pi;
                    lamp = this->m_proj_parm.c * lp_lon;
                    cp = cos(phip);
                    phipp = aasin(this->m_proj_parm.cosp0 * sin(phip) - this->m_proj_parm.sinp0 * cp * cos(lamp));
                    lampp = aasin(cp * sin(lamp) / cos(phipp));
                    xy_x = this->m_proj_parm.kR * lampp;
                    xy_y = this->m_proj_parm.kR * log(tan(fourth_pi + 0.5 * phipp));
                }

                // INVERSE(e_inverse)  ellipsoid & spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    T phip, lamp, phipp, lampp, cp, esp, con, delp;
                    int i;

                    phipp = 2. * (atan(exp(xy_y / this->m_proj_parm.kR)) - fourth_pi);
                    lampp = xy_x / this->m_proj_parm.kR;
                    cp = cos(phipp);
                    phip = aasin(this->m_proj_parm.cosp0 * sin(phipp) + this->m_proj_parm.sinp0 * cp * cos(lampp));
                    lamp = aasin(cp * sin(lampp) / cos(phip));
                    con = (this->m_proj_parm.K - log(tan(fourth_pi + 0.5 * phip)))/this->m_proj_parm.c;
                    for (i = n_iter; i ; --i) {
                        esp = par.e * sin(phip);
                        delp = (con + log(tan(fourth_pi + 0.5 * phip)) - this->m_proj_parm.hlf_e *
                            log((1. + esp)/(1. - esp)) ) *
                            (1. - esp * esp) * cos(phip) * par.rone_es;
                        phip -= delp;
                        if (fabs(delp) < epsilon)
                            break;
                    }
                    if (i) {
                        lp_lat = phip;
                        lp_lon = lamp / this->m_proj_parm.c;
                    } else {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                }

                static inline std::string get_name()
                {
                    return "somerc_ellipsoid";
                }

            };

            // Swiss. Obl. Mercator
            template <typename Parameters, typename T>
            inline void setup_somerc(Parameters const& par, par_somerc<T>& proj_parm)
            {
                static const T fourth_pi = detail::fourth_pi<T>();

                T cp, phip0, sp;

                proj_parm.hlf_e = 0.5 * par.e;
                cp = cos(par.phi0);
                cp *= cp;
                proj_parm.c = sqrt(1 + par.es * cp * cp * par.rone_es);
                sp = sin(par.phi0);
                proj_parm.cosp0 = cos( phip0 = aasin(proj_parm.sinp0 = sp / proj_parm.c) );
                sp *= par.e;
                proj_parm.K = log(tan(fourth_pi + 0.5 * phip0)) - proj_parm.c * (
                    log(tan(fourth_pi + 0.5 * par.phi0)) - proj_parm.hlf_e *
                    log((1. + sp) / (1. - sp)));
                proj_parm.kR = par.k0 * sqrt(par.one_es) / (1. - sp * sp);
            }

    }} // namespace detail::somerc
    #endif // doxygen

    /*!
        \brief Swiss. Obl. Mercator projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Ellipsoid
         - For CH1903
        \par Example
        \image html ex_somerc.gif
    */
    template <typename T, typename Parameters>
    struct somerc_ellipsoid : public detail::somerc::base_somerc_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline somerc_ellipsoid(Params const& , Parameters const& par)
        {
            detail::somerc::setup_somerc(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_somerc, somerc_ellipsoid)
    
        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(somerc_entry, somerc_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(somerc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(somerc, somerc_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_SOMERC_HPP


/* somerc.hpp
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
*/
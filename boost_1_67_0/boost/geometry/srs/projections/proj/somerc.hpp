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
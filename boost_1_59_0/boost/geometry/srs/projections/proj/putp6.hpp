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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PUTP6_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PUTP6_HPP

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
    namespace detail { namespace putp6
    {

            static const double epsilon = 1e-10;
            static const int n_iter = 10;
            static const double CON_POLE = 1.732050807568877;

            template <typename T>
            struct par_putp6
            {
                T C_x, C_y, A, B, D;
            };

            template <typename T, typename Parameters>
            struct base_putp6_spheroid
            {
                par_putp6<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T p, r, V;
                    int i;

                    p = this->m_proj_parm.B * sin(lp_lat);
                    lp_lat *=  1.10265779;
                    for (i = n_iter; i ; --i) {
                        r = sqrt(1. + lp_lat * lp_lat);
                        lp_lat -= V = ( (this->m_proj_parm.A - r) * lp_lat - log(lp_lat + r) - p ) /
                            (this->m_proj_parm.A - 2. * r);
                        if (fabs(V) < epsilon)
                            break;
                    }
                    if (!i)
                        lp_lat = p < 0. ? -CON_POLE : CON_POLE;
                    xy_x = this->m_proj_parm.C_x * lp_lon * (this->m_proj_parm.D - sqrt(1. + lp_lat * lp_lat));
                    xy_y = this->m_proj_parm.C_y * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T r;

                    lp_lat = xy_y / this->m_proj_parm.C_y;
                    r = sqrt(1. + lp_lat * lp_lat);
                    lp_lon = xy_x / (this->m_proj_parm.C_x * (this->m_proj_parm.D - r));
                    lp_lat = aasin(( (this->m_proj_parm.A - r) * lp_lat - log(lp_lat + r) ) / this->m_proj_parm.B);
                }

                static inline std::string get_name()
                {
                    return "putp6_spheroid";
                }

            };
            

            // Putnins P6
            template <typename Parameters, typename T>
            inline void setup_putp6(Parameters& par, par_putp6<T>& proj_parm)
            {
                proj_parm.C_x = 1.01346;
                proj_parm.C_y = 0.91910;
                proj_parm.A   = 4.;
                proj_parm.B   = 2.1471437182129378784;
                proj_parm.D   = 2.;
                
                par.es = 0.;
            }

            // Putnins P6'
            template <typename Parameters, typename T>
            inline void setup_putp6p(Parameters& par, par_putp6<T>& proj_parm)
            {
                proj_parm.C_x = 0.44329;
                proj_parm.C_y = 0.80404;
                proj_parm.A   = 6.;
                proj_parm.B   = 5.61125;
                proj_parm.D   = 3.;
                
                par.es = 0.;
            }

    }} // namespace detail::putp6
    #endif // doxygen

    /*!
        \brief Putnins P6 projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp6.gif
    */
    template <typename T, typename Parameters>
    struct putp6_spheroid : public detail::putp6::base_putp6_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp6_spheroid(Params const& , Parameters & par)
        {
            detail::putp6::setup_putp6(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Putnins P6' projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp6p.gif
    */
    template <typename T, typename Parameters>
    struct putp6p_spheroid : public detail::putp6::base_putp6_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp6p_spheroid(Params const& , Parameters & par)
        {
            detail::putp6::setup_putp6p(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp6, putp6_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp6p, putp6p_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp6_entry, putp6_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp6p_entry, putp6p_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(putp6_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp6, putp6_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp6p, putp6p_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_PUTP6_HPP


/* putp6.hpp
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
*/
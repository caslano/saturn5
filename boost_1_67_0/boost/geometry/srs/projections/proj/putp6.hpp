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
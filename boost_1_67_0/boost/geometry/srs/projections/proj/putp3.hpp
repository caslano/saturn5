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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PUTP3_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PUTP3_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace putp3
    {

            static const double C = 0.79788456;
            static const double RPISQ = 0.1013211836;

            template <typename T>
            struct par_putp3
            {
                T    A;
            };

            template <typename T, typename Parameters>
            struct base_putp3_spheroid
            {
                par_putp3<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = C * lp_lon * (1. - this->m_proj_parm.A * lp_lat * lp_lat);
                    xy_y = C * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y / C;
                    lp_lon = xy_x / (C * (1. - this->m_proj_parm.A * lp_lat * lp_lat));
                }

                static inline std::string get_name()
                {
                    return "putp3_spheroid";
                }

            };


            // Putnins P3
            template <typename Parameters, typename T>
            inline void setup_putp3(Parameters& par, par_putp3<T>& proj_parm)
            {
                proj_parm.A = 4. * RPISQ;
                
                par.es = 0.;
            }

            // Putnins P3'
            template <typename Parameters, typename T>
            inline void setup_putp3p(Parameters& par, par_putp3<T>& proj_parm)
            {
                proj_parm.A = 2. * RPISQ;
                
                par.es = 0.;
            }

    }} // namespace detail::putp3
    #endif // doxygen

    /*!
        \brief Putnins P3 projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp3.gif
    */
    template <typename T, typename Parameters>
    struct putp3_spheroid : public detail::putp3::base_putp3_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp3_spheroid(Params const& , Parameters & par)
        {
            detail::putp3::setup_putp3(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Putnins P3' projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp3p.gif
    */
    template <typename T, typename Parameters>
    struct putp3p_spheroid : public detail::putp3::base_putp3_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp3p_spheroid(Params const& , Parameters & par)
        {
            detail::putp3::setup_putp3p(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp3, putp3_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp3p, putp3p_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp3_entry, putp3_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp3p_entry, putp3p_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(putp3_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp3, putp3_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp3p, putp3p_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_PUTP3_HPP


/* putp3.hpp
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
*/
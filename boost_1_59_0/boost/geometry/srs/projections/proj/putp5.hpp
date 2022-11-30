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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PUTP5_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PUTP5_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace putp5
    {

            static const double C = 1.01346;
            static const double D = 1.2158542;

            template <typename T>
            struct par_putp5
            {
                T    A, B;
            };

            template <typename T, typename Parameters>
            struct base_putp5_spheroid
            {
                par_putp5<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = C * lp_lon * (this->m_proj_parm.A - this->m_proj_parm.B * sqrt(1. + D * lp_lat * lp_lat));
                    xy_y = C * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y / C;
                    lp_lon = xy_x / (C * (this->m_proj_parm.A - this->m_proj_parm.B * sqrt(1. + D * lp_lat * lp_lat)));
                }

                static inline std::string get_name()
                {
                    return "putp5_spheroid";
                }

            };
            

            // Putnins P5
            template <typename Parameters, typename T>
            inline void setup_putp5(Parameters& par, par_putp5<T>& proj_parm)
            {
                proj_parm.A = 2.;
                proj_parm.B = 1.;
                
                par.es = 0.;
            }

            // Putnins P5'
            template <typename Parameters, typename T>
            inline void setup_putp5p(Parameters& par, par_putp5<T>& proj_parm)
            {
                proj_parm.A = 1.5;
                proj_parm.B = 0.5;
                
                par.es = 0.;
            }

    }} // namespace detail::putp5
    #endif // doxygen

    /*!
        \brief Putnins P5 projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp5.gif
    */
    template <typename T, typename Parameters>
    struct putp5_spheroid : public detail::putp5::base_putp5_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp5_spheroid(Params const& , Parameters & par)
        {
            detail::putp5::setup_putp5(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Putnins P5' projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp5p.gif
    */
    template <typename T, typename Parameters>
    struct putp5p_spheroid : public detail::putp5::base_putp5_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp5p_spheroid(Params const& , Parameters & par)
        {
            detail::putp5::setup_putp5p(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp5, putp5_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp5p, putp5p_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp5_entry, putp5_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp5p_entry, putp5p_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(putp5_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp5, putp5_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp5p, putp5p_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_PUTP5_HPP


/* putp5.hpp
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
*/
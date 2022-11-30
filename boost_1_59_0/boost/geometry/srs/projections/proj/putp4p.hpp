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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PUTP4P_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PUTP4P_HPP

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
    namespace detail { namespace putp4p
    {
            template <typename T>
            struct par_putp4p
            {
                T    C_x, C_y;
            };

            template <typename T, typename Parameters>
            struct base_putp4p_spheroid
            {
                par_putp4p<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static T const third = detail::third<T>();

                    lp_lat = aasin(0.883883476 * sin(lp_lat));
                    xy_x = this->m_proj_parm.C_x * lp_lon * cos(lp_lat);
                    xy_x /= cos(lp_lat *= third);
                    xy_y = this->m_proj_parm.C_y * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = aasin(xy_y / this->m_proj_parm.C_y);
                    lp_lon = xy_x * cos(lp_lat) / this->m_proj_parm.C_x;
                    lp_lat *= 3.;
                    lp_lon /= cos(lp_lat);
                    lp_lat = aasin(1.13137085 * sin(lp_lat));
                }

                static inline std::string get_name()
                {
                    return "putp4p_spheroid";
                }

            };


            // Putnins P4'
            template <typename Parameters, typename T>
            inline void setup_putp4p(Parameters& par, par_putp4p<T>& proj_parm)
            {
                proj_parm.C_x = 0.874038744;
                proj_parm.C_y = 3.883251825;
                
                par.es = 0.;
            }

            // Werenskiold I
            template <typename Parameters, typename T>
            inline void setup_weren(Parameters& par, par_putp4p<T>& proj_parm)
            {
                proj_parm.C_x = 1.;
                proj_parm.C_y = 4.442882938;
                
                par.es = 0.;
            }

    }} // namespace detail::putp4p
    #endif // doxygen

    /*!
        \brief Putnins P4' projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp4p.gif
    */
    template <typename T, typename Parameters>
    struct putp4p_spheroid : public detail::putp4p::base_putp4p_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp4p_spheroid(Params const& , Parameters & par)
        {
            detail::putp4p::setup_putp4p(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Werenskiold I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_weren.gif
    */
    template <typename T, typename Parameters>
    struct weren_spheroid : public detail::putp4p::base_putp4p_spheroid<T, Parameters>
    {
        template <typename Params>
        inline weren_spheroid(Params const& , Parameters & par)
        {
            detail::putp4p::setup_weren(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp4p, putp4p_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_weren, weren_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp4p_entry, putp4p_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(weren_entry, weren_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(putp4p_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp4p, putp4p_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(weren, weren_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_PUTP4P_HPP


/* putp4p.hpp
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
*/
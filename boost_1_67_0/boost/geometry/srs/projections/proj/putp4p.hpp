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
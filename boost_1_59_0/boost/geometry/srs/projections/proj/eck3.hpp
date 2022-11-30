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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ECK3_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ECK3_HPP

#include <boost/core/ignore_unused.hpp>

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
    namespace detail { namespace eck3
    {

            template <typename T>
            struct par_eck3
            {
                T C_x, C_y, A, B;
            };

            template <typename T, typename Parameters>
            struct base_eck3_spheroid
            {
                par_eck3<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_y = this->m_proj_parm.C_y * lp_lat;
                    xy_x = this->m_proj_parm.C_x * lp_lon * (this->m_proj_parm.A + asqrt(1. - this->m_proj_parm.B * lp_lat * lp_lat));
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T denominator;
                    lp_lat = xy_y / this->m_proj_parm.C_y;
                    denominator = (this->m_proj_parm.C_x * (this->m_proj_parm.A + asqrt(1. - this->m_proj_parm.B * lp_lat * lp_lat)));
                    if ( denominator == 0.0) {
                        lp_lon = HUGE_VAL;
                        lp_lat = HUGE_VAL;
                    } else
                        lp_lon = xy_x / denominator;
                }

                static inline std::string get_name()
                {
                    return "eck3_spheroid";
                }

            };

            template <typename Parameters>
            inline void setup(Parameters& par)
            {
                par.es = 0.;
            }


            // Eckert III
            template <typename Parameters, typename T>
            inline void setup_eck3(Parameters& par, par_eck3<T>& proj_parm)
            {
                proj_parm.C_x = 0.42223820031577120149;
                proj_parm.C_y = 0.84447640063154240298;
                proj_parm.A = 1.0;
                proj_parm.B = 0.4052847345693510857755;

                setup(par);
            }

            // Putnins P1
            template <typename Parameters, typename T>
            inline void setup_putp1(Parameters& par, par_eck3<T>& proj_parm)
            {
                proj_parm.C_x = 1.89490;
                proj_parm.C_y = 0.94745;
                proj_parm.A = -0.5;
                proj_parm.B = 0.30396355092701331433;

                setup(par);
            }

            // Wagner VI
            template <typename Parameters, typename T>
            inline void setup_wag6(Parameters& par, par_eck3<T>& proj_parm)
            {
                proj_parm.C_x = proj_parm.C_y = 0.94745;
                proj_parm.A = 0.0;
                proj_parm.B = 0.30396355092701331433;

                setup(par);
            }

            // Kavraisky VII
            template <typename Parameters, typename T>
            inline void setup_kav7(Parameters& par, par_eck3<T>& proj_parm)
            {
                /* Defined twice in original code - Using 0.866...,
                 * but leaving the other one here as a safety measure.
                 * proj_parm.C_x = 0.2632401569273184856851; */
                proj_parm.C_x = 0.8660254037844;
                proj_parm.C_y = 1.0;
                proj_parm.A = 0.0;
                proj_parm.B = 0.30396355092701331433;

                setup(par);
            }

    }} // namespace detail::eck3
    #endif // doxygen

    /*!
        \brief Eckert III projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck3.gif
    */
    template <typename T, typename Parameters>
    struct eck3_spheroid : public detail::eck3::base_eck3_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck3_spheroid(Params const& , Parameters & par)
        {
            detail::eck3::setup_eck3(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Putnins P1 projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp1.gif
    */
    template <typename T, typename Parameters>
    struct putp1_spheroid : public detail::eck3::base_eck3_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp1_spheroid(Params const& , Parameters & par)
        {
            detail::eck3::setup_putp1(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Wagner VI projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_wag6.gif
    */
    template <typename T, typename Parameters>
    struct wag6_spheroid : public detail::eck3::base_eck3_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wag6_spheroid(Params const& , Parameters & par)
        {
            detail::eck3::setup_wag6(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Kavraisky VII projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_kav7.gif
    */
    template <typename T, typename Parameters>
    struct kav7_spheroid : public detail::eck3::base_eck3_spheroid<T, Parameters>
    {
        template <typename Params>
        inline kav7_spheroid(Params const& , Parameters & par)
        {
            detail::eck3::setup_kav7(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck3, eck3_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp1, putp1_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wag6, wag6_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_kav7, kav7_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck3_entry, eck3_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp1_entry, putp1_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wag6_entry, wag6_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(kav7_entry, kav7_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eck3_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck3, eck3_entry);
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp1, putp1_entry);
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wag6, wag6_entry);
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(kav7, kav7_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ECK3_HPP


/* eck3.hpp
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
*/
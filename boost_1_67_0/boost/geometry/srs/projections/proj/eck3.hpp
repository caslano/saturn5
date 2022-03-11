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
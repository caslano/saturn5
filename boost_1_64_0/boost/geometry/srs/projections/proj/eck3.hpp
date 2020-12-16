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
inlyJfqyBLl4BN0GHzoT4GfG7p1joM9tjqrFPx+fwljAH0nouH67Oip3IXr/JaU+Yn67CdmbgM9y91vQG/3zwmD0yXfoB/z8ifDa8zOxq89Ghg6gb9ipl2Hnrl7qqEPuZ87hOw5/avEx0AA+XNUHfvfQA6mUOdNRO+InPrIGOwb9EI9s7gOfHxjPvPutp87sAx8cj17AHkhk7vgQ+6rrEPjkFPgV2+v2NGQIHXjvdzxfjXwk0zfG7qZB+D3Y9Ek8+wG5z2SuHdgFW2M58y56/HPm5zlV2C7EUJKZF6oGMOZHYtP1wj8fDi90cdWod7G38YPj0BUfwLu5C1x18xr6tDXz0e/hx+60Hb9sKTZ/Cjybi/5qgF+u/yO6PAV7AZ9y6nnIP/bc7O/xI16jb10ZG2z1J2/DNjyEMYb270LDV/uAk0lbPObifFcd1YCsneLHAjz1AO39DLmceTrzyBTouCPzFmkv0kJS93p8QOavNej1U5g7FjmM91WME/NRj7vwtZDxgU/Tfnz1CvTzi/ugpx7y1M74Vk/3x1aATw5lrn9tHLYGsIvxWX9Kgh8PJD4ATYdXo69z8T+Zg+Neh85PMJf+xlH3dIcn/+KpveGRa+Hta3NpM/1YScypYio8+TbydCU+LPJ6EPS7dxBxuaHYitgks7dGt/bG/imD3pfSx30V/gL66gLsTmInZ5R4qmZ3/G7se8y54HzBTxMYvx0pCx5chlx8ge44hjJ3ZL4ZOQXaHoMuw3+79HeeyrzKUXvjF6UyTqcRPxuCfTkL/XxwFnMWsPXoxV+hb0oZlz9UQ/u16M0fkW9k/KszmFMfwmbIgb+uJZaTio/D3PtKJc/R3afCH/XwxdPw53Lm2HHolJFdmVMnY8fsjw94o6Pu/Au02o46aO/47YlN+P5hPTG1+dADHuvPuG57KPYjfkfaJuRtoaemYjMcMgX/9RZOiv8Fn1u5qraU30cy11N+Gjw9F9qcif3a+1T0N/PQtnejw65kHi2A/8CvoC0vjcB2YoyvbEBu0VtfXsyuI2JXfzoQW4s+vEacogRZuBD6ZyKfp10ELa9x1OBR0JE0nHQzPNv9CspZ4Kju48hzGnPXbZ46H/56uw7b5mDm3F2hiYM+fIoxuwteyCQutT28V4BvQh97EO9LLcGvSYEvvkJ244l54CM1wpe7H0xsYL2jRuzF3D8Y2kPfjYOQjUmc2RmPTYUvUDsBf30Eturx+KH4QQdnEu/CRoE91ck16LZ7sDPr4b97iQfc6qg+B2BbQZeu2HZf41c78MivvsBuPNdT/Zin3yPPrdDo7G2wz4gV7IrsTUIOTryafgxy1TPQMm02vANde2LzfZjFuC/x1P7XQrs0+PogZONt9Nsh6Hv00/3w/+VnIE9nQRP6WUQ9d8N7sz5jzOlHT+Qgbiq217OeumYn6LAM3t3dVd3QNQf1YI5jDtuKOWC7O5gL89Cte9M+PyaYhC0+HNlbR930e+WFzC1rmOMXOsgP7S1FP7yHrX0iMdljsLVmMs656ED8t1zmk2++wQfcF7sHXTlqpav+TEznqQpkaCLlJUD3e5iOpjEHbsI/UejtJdiLyFYh82y/G9EbB8LTu6Evff3I3HL2KEWsCjtnEvMTcbtdcojXwfu1J6Of8ctnYOM/js88+g1Hfc7YfwbtroXuP5Qib13RiX2JqUIPZ29svDto39H+XIEvuQl9g/w9cBRyi+zegi7Zdyvw90HOgV9MHzekELdEXx5P+w7FFlgAXap+BY3hQ7/PLylsjJeRp0psuWfQG5Nok4ss3o+eZK57fRfSoYw5flfZCQ5MBs/gF13N3x++xzyE/fQk89z+c/Cxe2H7LUA334E=
*/
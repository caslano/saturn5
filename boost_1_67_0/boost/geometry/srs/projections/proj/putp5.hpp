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
JpPGYtD84fSVcmwf01XaNmD078GAarnAHzQDBjcEVKHdzktAxMNgr3dqzoMPwKp6V7NPiyEkAwpQtuh6m3jFMB+9iF/42iwasBPmqFSyzgJ6PTJR0+tTGGFhvfqTAlFaG7DHMAS8fUkEVLPmHiOCYx2ASCpNE0ChkEYCZEa/mROoitofSrgnyH/6L9jJLYNMuoucKzYyEUAQXrEqfAXMeMUKhAbkn1LcUKT4lIdZAM5Aftl6aePnV/0oDyhmtc5dtf/o8D89gWsVB4oFkoSHR9ReJSyFilyaWCNOLjqG+hlI0cILJJApDRDgunpw4x8CqpWaQUTPfMn0KNSb7iedgh0W9OOl0JLaIjx7/AAZYkPiLB3qMqCVVKl8todbvNYBjscCIa7Mm6o5pDMm8TzLoe3ak6iw5/RRo4aWCJXqcecMnk2t86C+wwbcKYxWUJvI3DO9lxPMveXmJUYPwL+i3hSlXATjOxVTKfvQ5I4jnUyQSBHaC/FKCOzFHFEQ9f7LGJsJ6k1FSfAxUKKvfmG68R8iUXH9XtV/1FrqhzONMpYChpfyGoEnJUaBGbsSDhHmpD/977+qi+so0vxJZ+k8dzXzZnjD7ydzgTOryJvf/Cwj5bGYriyB61rwJLfgLhej2tinhZq5WTdFgBrZpbDso3hYJxpC7DBNAqayZ8aKKBlwHUaYtIdIQBUVR904GFMxu4UJuQzIgwxkdNBGn70gQzceq3OtTD7mRquk2Zm74VRY/KXeszFMr9wyqwRDNR9aYzcw3MsTQ9dFoOnBrz7waZomcXKzDuVflKviqIbJjkn1igcQwxmfPEG30XmPbSCYeZPbMV+bWAzYk5mTj47Bzb6Dw0r1PaIZfbGGFiz5/PQlRqHub2NF1KTz+QHXVsHbr11gVrZgub1h3i8LyUTxmqMpuHVmFNJwQ9nrTvBR2QCoUOOupKu0vQvvnFhQwy29P6rZjRUp7rhBXffph4Vio715Ko2WlQ4MGGIY1gq/bRJyusB1QU9zAkvgTyUT2ZaU5ZuAQMym7G889djocEV/xOBYXCu20GBlzvQSD9xawVTqFlfXeSt33JcZRPuowrL00nJWUVrejewl+zVoyamWiEoUEuM9az+bZFnMINPTZByQ5LyHW/s6/PKpq5dljl9XxI0J1iGAALwFSiR30F18vRqvY5DWXNmNdo7QbXhguO9gxhlj+WJ5VBZ05ng7CwhKA9L7WuTyLvMurQA1I0U6hRQ0RkBgjwE2ziAgVctuOIarpJHqCRuq1jsx3V/4pBxkFSareFpbxgPdpBRn2Aph0vS0Om52tMPow2AHktKrcYAbhnYnEbr4nQZnRLxrRYGiwqU73ruCevpBzcgfrc76T1So4PCfshiV5gLk0evizDScK2od8fkgeddj4MqtV01v5r3PRxiIGw5mLkLcLVyBv+sCkzXHYfpFPIkaTSV9JOQynZnZdXq53L2bmeICVQ1dbi12W0LzRHP52O+VT+dGSnMt/dDzOKFHl81Pl8030BO1ul2GnFd53p3Gxfse2R+OEUf9MnwiOpowBNoLadBGK0bdlG1DRDciQtpLwQQ1k0SfOLgT21+GyT6Xc0Bi1kX2i9xxFyaPbCPOkOy7stWyFRhnxPWqM/bZBpvBk0YkmcoUV0ojWAY61Qjoan2v10g4kwoMAfOgM5pQjnszo0zWWf9R7A3GZfM3X25pJ/BLkAVpSIs6Tm3FRChwl7A6E/DhJ+JjMu/MOArm5RDumAc9kDmcgk3CbgFQufzG9O9+jBaoNNbY8+9sNmidM9QqFyAVqpkBHFF2yNM7Ratynz7onTzVgDQMl8oiNi2U2bHGeNIMLvC5Z9E8LT/dej9yS6Ti5HgKKO9ET94qr4wpYGxU6dhZMgLJFrqa3eP6OnPX+aCglmoYIIfrXxp1LEqSWhfriIVKmWWuF4bQc6p4swxl0Ie1qpJvlhbdMx5R/OMRmgLytNj03KZqC5J3O8exf18Zne/GEH78X8E5YmdwTSX4cBdab616XKIU6fKu9Qv0uoFajtDHK5tAWzx/vJ/tk2i/EMYfZNeu2WQHjAtUIpoIVWgNojLyPlxXdrt087afB0gU94llW2rVc5GTtN4FeUsooAgSmZs4Br+C4sKvwTkGNbUksy/SDA3UTNhyLAGa4JeBKt07zxivMV6G/MufvZ0mGSAbfca63UWzc5JtKeCqVALQFI4BTLi/VYEQJPFP8s6wAYnDyZrCnqsYbCSnIka5MYWyom9yfyTUkL8jaC106KrrT4XTo58zsRNjCS7Obax1heKfvOOwrgftBrJnD0TlcN+oHud4A3N4tjO6Tuj+ZPcp8IJXXycXTIe6NFZYe4+hUngNHYAh0bE9sHZtSMKNwXYlciXZr4/MNA1iUsdCkJrXBfi1mIf+UYn9BIb4QzDKRyT6QFiKt+bTNRJ//v4Q2DeHbTz1Usa9zKWvfmrxzVh8rLlFu7h/yKAKR7pmRLaGIp3DU5WAR7bygqWUAHzr/K2GkOAh32mY73YmIa0x3Jez2eNMQVwISsAb7pCOtzYUd0pcPRjC6fGZuSafGddVxnQXlBfprXhR8TdVO3BtrxUgdCfgfjCXP/fz77ihrwnpThOdFffTkha95TLg1ULqS4r3fSyz4uykNTdNNXyLN8/XOHJzQlDUkYEJ2KE/SOFJkaHPX4HSWh090Q8WFkUmjI+4KKwgXtuIqL3TanASozwoKX6aytdG4CVHgn3DQ2UU3sfBvUyD/S23DsJptID141kRmj4MCDrfwvyQgLE82WDSnkXCqoZqittoPUzrBVzaAr/u4CWZzuZ36WAaO6Xc8qfP9DhmOcPdayNUfipPkxE61/r3R3NpI9lorPkqek082tGkS50QrGsAmzbgxlC/+6UZfryfBQoYP1hWseDTOHbYT2FSYjxI/rXZYkgIXk7AiFULqrosyL73P7Q2H9x3VpY8AIYmL0U4DX5Yx38+WRJnve3Lr9aVM9jLYWyAwlQR3BznEJXL3XHkNM824m/jrUaCizv/du3/e0S4QnBmudhOqBGhUtTJYAB3gre7dr14Yd34dE6vh6KZOiSmZ5aUY6GDSwt+tt+zmQmuk+ufM8rhQ/SHTooXsHc31gwV9FsnyK93ZN+EAcTqvP4Y7nxFl1nxk5Hk50utgWnFBrNhj1qbRh0/gDM8WehF0Ni8WyfTyMWKQUDPhqbj8SuKRCTzc2u0zkY/xVfrvD5GrTsQ5c/iLUEz4etF85PB/ot17HRWA6pkxlK4BGWWtv5GG5CaweNGPrZLgNyF4+q+VW1HpBEos7vtbIsg1/jMQUGScZj5d/HkXAGuPn+hfDonsMcyvdMjakUg1rTyQq+gUe2Z0XxvRKmT3JYkDu92jnXBTHPOrrB/UrVi5eXmZXIJHaYPapacB6LoQq8UYA6MjBdQTHik0Bh6EESt60baAVe+rFdSe5mFruuV7nFxLuQN6w110hYtkDe7ndmN5BXKXN49cB+qn1I651YTM0u5wLV6OiELvXy2sdwhXiCgmZ4xfyX+uj3eqdSnSxbRDZDWuCVkTebrYyXf1MBoa7hY7+XfO3raeJF3D4ag5vksDm4LGU3X5F4IoyWoRVM4cFDRZX4DLQEZ5Jk+h7PlZxAw6HmKGWEVnai5Fe7XI/etwYrcrNUfF+G9HUFFT0FhOaHJJT6G5iQ1HyUEsReVBCNcQ/RMs+Q+iP4dhNsnyg3f57Ui635tglVuMcxJ7nthbs0E0h5UHZzbkWfe1/WSGK5v4aA3kB9sMSBhS7PpLSwEh5ldGcbnLMv1UXa1+aceHPDp6hAG+w3zZZC4g8nCTx6XVliJfcqZD8f8/bBS2H1jMhaTZBYAnIyqwPaB8JHTLGgaFkQ6UhxUpEF2EWnsXS2mLPMNr3Fl44qcNFHh14InbJ8LEo5W1Axl0fshwcbE/GPHE56a1uHzmeB4mDGcojJMgkPSbvhHhUUVQr9jYmBd3e+RY1NeHqi5Jh4fWJpjktPV2+LvBCg4H5IFyd1EdKMKJkk9PirQfMYF934sUOQ/zlfvjhK5RWQeC6RYtbmCcHaUr5j8h3TC8MHSPio2m7lPCFEy2sw2odybRO2XNV8fc4cwOl3Qsyx4kjBOSw+AmKU9F6zD1e6SC12y2YJlzyVRb4w6eS7sgbLb4QsUJz+kN/GUCHPXCnutjZvCQ4W4aVBm93s5T1mfxErs/Yoaiph1OOrGwexeZ+PpM97YfBcPpZKzYMyWdClhuV6XJLwLufVhHr5A8/6hOjv/5HreQScxD/+RbJBaBcyRBqRWfW5grbn+mxboaKzJvCh8I9Bw0eUKi8OIT9fQpMuY4iKiEzhQ1Ixokvus5vfh0etq8EDDdAguH8YizMryTQc+lfE1Q3Lwn/5jZvOY0BOZBIz8OFGhfwQfY3hJAOEdy225g0yU84pyFwCBbOa1aCtobaCOoQa4sIvIRa1RQQ5nCIPoAIWvSyVX4blbxvqgkh/HkPWEQ6Y74fAO9y1LJYuNR3oBohtJ7mvN3ATNGBkZRhbhwr8C1AYDszJhc93+4A8WMxRPuLqdYTiLU1VNHkJykk0h04Y7FUmA+aCuQoWB6OcT3mze6CjHGaJ0aBIeflJn5XrETA9uxL3DoSVO0BeBApgLMNZLTM/PJfjkYk/szajpGfAQnOpuOc5MOmZaenXH1pfHI+d6lOFXBBSgwGwrZZIN33ziTVm740yOUySvhRUvo8AnoZ0Zk0aoMNbGAObFGDUvZEYlGGKrYRW9obOlpMtimSF3Kc1O71P+FEowqaqaBRVMQ8q0RkxRyvM25zI2w8yiqcxik1r5BYYv64D4sV0WHK7Hg7zq+SK5ISmKC0o3oABG5QIVMgRrolDX45onbrNh1kTpZ4QeWFtUZ4No/+n+Q/4c+5HqD/OdkyJTmJ5Jy7OSsctSU9fJSNP0iXFgUnteF0J36h723uDKx3QbAzW3Z5PS757kTumufR9LDN9700X+jXl9a4z9AnqFoCu2/5D/agEI6raZVPtzbDsSSba/tFPzJd9ZGaoyq+m5ZLNohGqwPTkPgF/0VK3bAiAVqORvFKiOzAfmdru4Q4tfGSP0gZk6FC9qt9/qQ846RS5gWHpccFe+AJdejcB11hOqp4qIqEw2A4s9uP7UBNLWDMn9XNWs6x37lxE5W//kEJFR26CnJK32Q93IjFgykJPksRhJysL6GWHxeH6D0IMEdvrdCuVfeDB5InM6r4hCCGRsbarxRxc07Ug9LXBIXJxL7TPfDqlEa/wXKLnjMwA6aOE0qLVCTOosRTpvHk04tLIFSKotaA1a1svgTXqcTcj5JB6/IDhVcWcvAum6nBKakL9Xbb6ljem3QSUQgGRl1DVWvQPfHLpAPCn5kbxRag/215vvOT4i7qdAzw1+8nBaWEYr9sg3WKUiUyldEEBd78sPnjdbFTl9nxqwuTI6VYRePejoMSJwitoO54BVtae5hOE6R2AHtFxC/KdPFjlfRnNuCMTq3+OaK+SiIGwwRGyBF0E9De0Q4nh1Srt/sktSvuYPgNjHJrYDFmj4JPugFI6pl1SkpVXQvqR+bh6GpsLsnm1+mQzGHr0O8MQrMgOxJ2iuTKbrle/0w9H/ZNuz1/EAFie95Vk3IHWC1WmBi5KaME2SXy+Yx4zNjXjZm7hkdy8G3v89q/KEGvY+SKb7hSiZoLCERt0O2wO4zMTNBFkOLCftLWh2Xf65sdJT97mLDViz3CCJHv2yizQvB2aRReVzpcsFtPQ0SZsyZXcPWMz54wglzrZ/LmLm598y8d1pqNZKpZU2yC18eCO6gbSWU3/MSwCxr+28jSYtRRs4QJydoKd0BErzQEJWSSM/szfmVijjTTLpnGkmO1k+1MTw0xBe08dr6BL5bslnJKkgFEZAlGhCoJgmL+dQwBR0zc9bDxCTMUgLH5b5QjIkSKBWmDF1yDV0UowCfPRoz/UW20OZhIj8Nky+sFvvZsjjAvyX2h3YXXbrJxhyyUctJOir1s0QeoZQl+loN0z2eGWOvAeWqq5Ru65RmW6UxcRR7+AfmFHIYhyfxZLIFyZddJzjGHMeCiyRFCY1oBCsv2V/QMXZ3/CxnFhB2zXvuh3sITjXhoUEK/U6LCSROCQOGvV0VaVZmFzqDjZjkfBjrrT2IdMfwCbf9qKSk3bHBzyIQpQ+u4SX+y9IEju2sjKQHlrRjsh4CgSLcHJMz8qp3NBB5ntVTFbaDHIa/PMihmqdivtF3u9ONa4vM4p2gfH5RjpBCJZzks3atuumHeENx2KlQmqAVccV/arEn9oZHkju9yhnm8lr9RAblCDLhH6/6vgGMjLooeljcphAvR7Tf8N93M0z308ahcgambUQHcmfViTDzIKu0cFBjJx+JKOk89bsxyzxy34WqVem1ixcfTP66wFtIMZhauJiJdr/9HghxB7Y0INI2g2/eWgL2IvNh9KCr6HhSRdEvgJILBvdW/C9VQmZVLnyIZlvwAvbEu7t44WxaFHtj1WnzDjHx70VaJ3IS2MPRme+6Vh+DpGukIMc7MFqewUjGbn7DdCN3j8eQwAgP5X8caXL9mc5tzf+MWl5Ij13/RCm9d5Xxz1xu7dZ0PnyS6m1AYkZhcqVRXVuqhtcvLLE8Lpgk+ZyxAyVU2OW0bvetkgj39lCQd8MhAfH5z36NU/QtctBvpMdO2r80OM2gdjsRsHy/TlmcBuk5PAR0NBtSLD9kRMIrmGzlRITk4IYJaNHW2cwafzLpwuKrHeZkguDu6KMiIagwbtRN/EdshX9NXY4mopviRT0nAwoIABcwMgpgOjGotdtPKhFQv8c8F8lvD3kfe9keziaUVZjehBbd4RnDkUS0BY0pNCW1LnbpbqHAUe8RgAAsTvd0ADEb8Q47Mis/35+AbL1pU352fkJHDrhjR5C4/ljlVPFh4xEcWdiTAhxdON33rAs/Kch5QixNIYK3wHqIZqdhWYncm0Ym53vxKv4xgcHSYV6yzUSVLByk8t7bQPZlfKzhzb2lVE7Fxsco8PDR0uNQct6QlfcBfJB/HKJcUneQtyNKmRQWYiO9y2UB90VfFYmuLW2/yPW0cCrnBwEXCrMNVTyVoKP5yKq3J4kj8yP8gZfchpiS8f/aMNnwHdhE2YQPexUuHArsvt6ahvPLbzFDvcr+Ad1xOfKV+AOzR79gVYcP9BN4iySlnHhT10I4VtKBp7NGgWFoFKy5xpWD0rjVyqoFkMUuYvLDCVd5wmKGu/DlprXt6Kaz/PC7/ojUhlfPVCcy6oX8M+BsQKltepBAbkClHND0gpvZ5AOq67FF8cTFsevSjyGt2Vbw7OnYC7r+MDvIS9bjgteNeMzXovkMi1ta2I1xWpGmOxfzR9cq8fVoBn/ZoSQ0ZWclK5J/vrO2wFPf3Ph6LhNPMIjuZuNtoC7ThGtTqnodlec1YAHBVCIgLH8sct1Lm3e0ErbSHQ+cgNTfrOuumbudDOPzSEScbCpxOh0eb62V8xJTXZvbFLfi5O7z5872nq38zlUaQtcsRuX9h88VYw5nWiw/euoB78fMHZIjShXFNXeE15LvaS181axsRxvNc83zbrn+1a+maz+abxPWBeerxt53B+HodZewjr8YHmkOadjUZT5HN26xsHlh9K6p0/xyeVjtY1ecCzVy9CqOReDvUFs6ZCDcAd/hFTrhOyzgVw4SEM2IhBPAzkxdUtKkLBZN77+UZ63qL79K+0MRBo/xoFrer5OQX+1lfOrdSQNQH1MpTWOWSURAViLR2uD8JVsrL+4bxslZ11z3aoAWB84yP+Ye2ITMRWVN0DXwc0BVq7dsQ1qKlnN3P0VGAH17A/ls94SY/cW8byQS3meLs5IHHxhzEE+YVqMGVy/VMsAo3MJmshklmt8inZoy55guR41Ln1v/wBWwgC7eIfDoKw14l3YvrtU9Z5tyMfwRGfLfqO68DxtkInmQuWug8pG37UHq5NtK0KS3sPkqdnYGNpbQGeK5ox43XAsw10ODS+Ba5KA0mdm1sff+FU4a3+MhOC+R4X5oq2FtuZfHYERE8VtglbwU2dA4OtaOIQHiNMB7mpa528R5JlS7mdkrOyMnNHJ8AFzIwmhwJy9g0V7otAEbpCHWBEAyVoGkOydc557x4q6ZQFuu0Abw6+YRWE+qPqmLsJUSVtNt3wf3LQS5k5lmqDJcgcMIXgUtxAYnowS/pZsiJae+zWLfU5YDg05E7UR18HYKHqyOjSYaQE6qWU+LUT7FZkO4OZt55sfW43Hy4IvV8qBfMv6u5gXgwOcm6H7elr9E6Te8CvZb5I69wIa9RSDZcD9ajm/uQyaDfwac5W5gKFyRrWs1cFjxRnDHl8cLFXcwXX/7jBx9BQ+jGHzImxRO+pJDa4UEPE0B9zegwb1YctBUwYfM5GFAIK0OGvdAoZYRZFofxfDH47tjuHcgAlmS1Yaj2lpF1MRWDmE8pKTYxqRvchh+Oufzn9zXjyfbiijKKxrzKwzQwqx3biAWLqua9pTSNizCRQpFGKxn487NsFljLGMBlqMWoh/BhWJa+m5gzSJijaZ4NSjT1AgBbvm0HeruwiCvtzoiPf0CtrywUCfef9LA7qV7xnRjxsVE9oOnEbXL/znrgvw+of0WMO7ULyRaTxvIDZnBjtSDSqrf/wxTUAGkyTo4wb+V4bQl1y+mOggF6k3AzmVtCNWNx5/4wlHY5B/qIlHVCTeb/KN0vxwZL0y5maXD/bvAleRg5CpnkaEDx61JrL2bIE8kLLk3mwExG7DK8W87pcL2PiKMQrB8u89mlyXTaASIoeksPzajytrMdAYfxpRJVUMjMYB8Wp5pcIDcdVHUQCQgP7gAh7yE1ALgi7IehmcN8K3TR4SQTTPRnKhFBlfZg3VmTCF6Ab7dojGYJnrIWu9ANNGPe9UV3VfPql5rl3UnzyKX37ujdQ9/Bfjz4fnLlLYB/IBB3wHeKseFYIFYJb7M8g0lyfMwDo2ViiswYyzql7aH3KI/cG/5rIfkOWWvpcrsh3g31ngUaOqz/NEyO69QwbAqTFvgBMgyFI4S9w0LfotC3Y2sJVbxtLEt0iaHMUQ4WG+hYcXcOvKJ0AUm0nz+aOYcjh+RySPb6T0nmOth9aGUcfpkGh6962dpCY5b+hkN/T7aHs0MVIuqFYYoXqVCCw04NL8/noltqxLyX76dYVwBxoNiEk=
*/
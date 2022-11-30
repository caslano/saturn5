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

// Copyright (c) 2003, 2006   Gerald I. Evenden

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ROUSS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ROUSS_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/proj_mdist.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace rouss
    {
            template <typename T>
            struct par_rouss
            {
                T s0;
                T A1, A2, A3, A4, A5, A6;
                T B1, B2, B3, B4, B5, B6, B7, B8;
                T C1, C2, C3, C4, C5, C6, C7, C8;
                T D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11;
                mdist<T> en;
            };

            template <typename T, typename Parameters>
            struct base_rouss_ellipsoid
            {
                par_rouss<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T s, al, cp, sp, al2, s2;

                    cp = cos(lp_lat);
                    sp = sin(lp_lat);
                    s = proj_mdist(lp_lat, sp, cp,  this->m_proj_parm.en) - this->m_proj_parm.s0;
                    s2 = s * s;
                    al = lp_lon * cp / sqrt(1. - par.es * sp * sp);
                    al2 = al * al;
                    xy_x = par.k0 * al*(1.+s2*(this->m_proj_parm.A1+s2*this->m_proj_parm.A4)-al2*(this->m_proj_parm.A2+s*this->m_proj_parm.A3+s2*this->m_proj_parm.A5
                                +al2*this->m_proj_parm.A6));
                    xy_y = par.k0 * (al2*(this->m_proj_parm.B1+al2*this->m_proj_parm.B4)+
                        s*(1.+al2*(this->m_proj_parm.B3-al2*this->m_proj_parm.B6)+s2*(this->m_proj_parm.B2+s2*this->m_proj_parm.B8)+
                        s*al2*(this->m_proj_parm.B5+s*this->m_proj_parm.B7)));
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T s, al, x = xy_x / par.k0, y = xy_y / par.k0, x2, y2;

                    x2 = x * x;
                    y2 = y * y;
                    al = x*(1.-this->m_proj_parm.C1*y2+x2*(this->m_proj_parm.C2+this->m_proj_parm.C3*y-this->m_proj_parm.C4*x2+this->m_proj_parm.C5*y2-this->m_proj_parm.C7*x2*y)
                        +y2*(this->m_proj_parm.C6*y2-this->m_proj_parm.C8*x2*y));
                    s = this->m_proj_parm.s0 + y*(1.+y2*(-this->m_proj_parm.D2+this->m_proj_parm.D8*y2))+
                        x2*(-this->m_proj_parm.D1+y*(-this->m_proj_parm.D3+y*(-this->m_proj_parm.D5+y*(-this->m_proj_parm.D7+y*this->m_proj_parm.D11)))+
                        x2*(this->m_proj_parm.D4+y*(this->m_proj_parm.D6+y*this->m_proj_parm.D10)-x2*this->m_proj_parm.D9));
                    lp_lat=proj_inv_mdist(s, this->m_proj_parm.en);
                    s = sin(lp_lat);
                    lp_lon=al * sqrt(1. - par.es * s * s)/cos(lp_lat);
                }

                static inline std::string get_name()
                {
                    return "rouss_ellipsoid";
                }

            };

            // Roussilhe Stereographic
            template <typename Parameters, typename T>
            inline void setup_rouss(Parameters const& par, par_rouss<T>& proj_parm)
            {
                T N0, es2, t, t2, R_R0_2, R_R0_4;

                if (!proj_mdist_ini(par.es, proj_parm.en))
                    BOOST_THROW_EXCEPTION( projection_exception(0) );

                es2 = sin(par.phi0);
                proj_parm.s0 = proj_mdist(par.phi0, es2, cos(par.phi0), proj_parm.en);
                t = 1. - (es2 = par.es * es2 * es2);
                N0 = 1./sqrt(t);
                R_R0_2 = t * t / par.one_es;
                R_R0_4 = R_R0_2 * R_R0_2;
                t = tan(par.phi0);
                t2 = t * t;
                proj_parm.C1 = proj_parm.A1 = R_R0_2 / 4.;
                proj_parm.C2 = proj_parm.A2 = R_R0_2 * (2 * t2 - 1. - 2. * es2) / 12.;
                proj_parm.A3 = R_R0_2 * t * (1. + 4. * t2)/ ( 12. * N0);
                proj_parm.A4 = R_R0_4 / 24.;
                proj_parm.A5 = R_R0_4 * ( -1. + t2 * (11. + 12. * t2))/24.;
                proj_parm.A6 = R_R0_4 * ( -2. + t2 * (11. - 2. * t2))/240.;
                proj_parm.B1 = t / (2. * N0);
                proj_parm.B2 = R_R0_2 / 12.;
                proj_parm.B3 = R_R0_2 * (1. + 2. * t2 - 2. * es2)/4.;
                proj_parm.B4 = R_R0_2 * t * (2. - t2)/(24. * N0);
                proj_parm.B5 = R_R0_2 * t * (5. + 4.* t2)/(8. * N0);
                proj_parm.B6 = R_R0_4 * (-2. + t2 * (-5. + 6. * t2))/48.;
                proj_parm.B7 = R_R0_4 * (5. + t2 * (19. + 12. * t2))/24.;
                proj_parm.B8 = R_R0_4 / 120.;
                proj_parm.C3 = R_R0_2 * t * (1. + t2)/(3. * N0);
                proj_parm.C4 = R_R0_4 * (-3. + t2 * (34. + 22. * t2))/240.;
                proj_parm.C5 = R_R0_4 * (4. + t2 * (13. + 12. * t2))/24.;
                proj_parm.C6 = R_R0_4 / 16.;
                proj_parm.C7 = R_R0_4 * t * (11. + t2 * (33. + t2 * 16.))/(48. * N0);
                proj_parm.C8 = R_R0_4 * t * (1. + t2 * 4.)/(36. * N0);
                proj_parm.D1 = t / (2. * N0);
                proj_parm.D2 = R_R0_2 / 12.;
                proj_parm.D3 = R_R0_2 * (2 * t2 + 1. - 2. * es2) / 4.;
                proj_parm.D4 = R_R0_2 * t * (1. + t2)/(8. * N0);
                proj_parm.D5 = R_R0_2 * t * (1. + t2 * 2.)/(4. * N0);
                proj_parm.D6 = R_R0_4 * (1. + t2 * (6. + t2 * 6.))/16.;
                proj_parm.D7 = R_R0_4 * t2 * (3. + t2 * 4.)/8.;
                proj_parm.D8 = R_R0_4 / 80.;
                proj_parm.D9 = R_R0_4 * t * (-21. + t2 * (178. - t2 * 26.))/720.;
                proj_parm.D10 = R_R0_4 * t * (29. + t2 * (86. + t2 * 48.))/(96. * N0);
                proj_parm.D11 = R_R0_4 * t * (37. + t2 * 44.)/(96. * N0);
            }

    }} // namespace detail::rouss
    #endif // doxygen

    /*!
        \brief Roussilhe Stereographic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Azimuthal
         - Ellipsoid
        \par Example
        \image html ex_rouss.gif
    */
    template <typename T, typename Parameters>
    struct rouss_ellipsoid : public detail::rouss::base_rouss_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline rouss_ellipsoid(Params const& , Parameters const& par)
        {
            detail::rouss::setup_rouss(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_rouss, rouss_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(rouss_entry, rouss_ellipsoid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(rouss_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(rouss, rouss_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ROUSS_HPP


/* rouss.hpp
VhTL4WeUAreZdfcaUy+6Ym0X+Fv/fQfm4U/BAtcVRnjj59jLf7Dr9X5DD/zmvzdBaPF7MIkZoJbRpVYWVd5NynVB3tzfGwlkCQARw0hrJrAOQBFNeoQtT6KxRtyYs0s+FxGBNIlera31a+m0XW8IavLDzLxc05M18bxpzrv21p4zf3P3g7yNU296MJtq2cQKZnBVnUm1Jjv8vAB6Ec0cAwK0pkJ8q9hcrGPTG19YAvDmsyPMfRL7d6Tok1CYgDqutcPXLb0PYDz8SxQ1A67iN9nIAWcDHxIjrSqnruaXz7BEW8VYmgBoRzzMW5D+U8glDjVOHV7N+oLLYJgwSR8pnSBhLiA2ce+wFr7wTVxP60I0fg1ZZRfrqzsLLRELU12146q8x7knFvVbk6hWWiOPYTjh4fHjCxR3pfvWA6aGz0BcL4rsobOYkT4pgXdEaTKOycBmpJlph8L6UKwMVsiowa5io0ggiWIoisrK6OIUcW4Ye/mKl5h1g3r9D+zephTbQ64Tca0VLbmrqtQB3PZReaqJih06H+Lt55llu7nqDVwBo0BvEKMY+hx7Lw/r/vLzNqRpzZBuJ2DFtG0LeseU0Hb7ZHPNwP3CDJn5+7OVwheif+xtKMB95+MSDcV7oO84Ek5GBzhCpmGkGqXciTTGdKd41pztdOFSf2b7C6rwqpSnys/eLvK3l1V9yuOjk0dAS6Rjw+zG4qCUY+du7uBPalMNszWc/eTxzRIXxWaWy1SboRo2UjmoTMJgtv45zo9AEOl5x/oLPD40WG1eOvsgdoyQ5GMqreQAbpEEmqsgkmmnicLm7ckkyNwBZwMXdhYYlbYmw72NaH8U0YEUW2fL22NocsuAypQwTyyOaYtJmyFWU4kbxEFTL7sTPk2ow4tNh7bfvvY9lQjrtF8SlqvBViPQ8BrG+B2VJGDecoDH8W5NbE+7zpaUWVClGJxq3m58T2HgMYdleX7LoGeX/E0IeHyhshq3SIbD4qHyMj05Kk2z+pSDdAYFkrFewXyNQO3tcnxj0L3gDTpdBYB2Dqsz+Lp4RcvTAjg70Mn0AJhOZ1bCDbmzm9VS+oTRd7nqNjTaMAUtExyXoy5+wwPUOw6Qdslks69E42E/UzsDCvxDW7D8QwnFDxujdSnrMNh5LhmNmKhW7vsaU6EAyCWM4IugY8WNBNuay3g//brcHxVKnI8/T4yyFB/xPBKl5ZIgBeEX/K2ACRBA4A+1j88gkfCHfx/l9aLvR9bZg9pmJqExr7HRJZiAlUVW9A/Q8q9FgS4J0CFdfow8YoU/L2KyfL6sbs1fFZZXNJxk7KJj4KfuobkOV8Erl/Me8rJ9rXpsSvZI0pOmSgWO3vXujKl3Zra6QOPuyrNcA5pgICsceac/enuw+u1qioel529x9u5suADVLhXnpFFm6/pjdeet7Km0x8SSyoS7bflU7Tagg+/W2KbuZeEa6rMmcpXTbz1uGqrzJQ+sAuSIKOXnnqsYSBCGhJkckwcla6IAbU1f+hD0TQQC7JKm2/34XNi5OB9ot4T48TVwTzUUWcSabclN2B0EZhm5ad9aEJTHr7r63LV+Xqu80TS+Jgd0Q8JG4+rh/v7dl+/F4dAbQPeWvRkD3e2Bnh5iUDh3V5wrK/ccPVPl9GU/1C75liFmueM0K3c4P9pElJN1BU4nywlgdIbYkax1I3uNfAx42kq5h0D3Udt1tE1PzXyXQkaOKYcvZlLuFTJWgW3B2KcDcKnKPEEcz5t7awXejHZPa6t5WneXh/0xMLwLn7nGv0U0qziGb1Czr/lFsy/t+dn2rStloG5oKGdZvA8/ruvMr9Oq/S20d0R5b+uA3J0EksMnh+ftKbxAoWf1DTGMwOwdlx8ziXvqIU6EmR4i6EgEUjIMLHpdf7thgujTDoe0MnQmhQRZMwEEfJ3fQzR12jHQBO3NJdokmyTb8GB23ZH8YKY+30cikhPXYJA2SDOrGhbsmG3JAV20HF9VAdfyitrSKtzEnHaGckNmxq8KRnRX5ABWh0GCPLqING1z6FBBeGBwH2dYaDdGIW22aL/agFMdNXPg+JQV+A/PMn8678Kvj5jgEEeEjfD8y3MD1p55VS4OWlbZfQppLtTOmmW8UPkRgwbBJv+et7vIBudbBruE9BAGUakybav/oaY51CDLksLcLHNAvjRCQzpiDHBGeZXNqMiBZhXCPwDCzUH62t2eJx3ZBBATFForGNewHhIhitugPM2I7HdrL2xLTNUbr4B3mNPHGFD2Oy1Vgga0qXT2nmXCylF6VCzVcxprDGk3YwpqFtKv/M5Xw4ugijXaQAxj4Z/tGxYH8OCT/urdD8P2+NkPTRrNISVEX5hepQhunxToLkWQNtzWbC9rmE9fFkKgQ952zjpP0TM7aQSZgUJz4Wc5m5PSwyHIkHSUFeiuvpfrxouojIcFqoLvFINRFMVJukbnZt6Inkz8FyROT7Woj0foIqxp5ejqRBMH8wLuVK5iiXrwEcsssmdlU304x2lcCAbcPDqlhrhxcgmT/vbVPvGr+qo7F++9QvjDLs7YVUjzkfQ6UT4pySGJcObII2U6/DxsZoZh7q9FcVWf+C9FHnPsSfpIddnpuvTb2w9kZFSqqSb/oXFDjGmtBvAhdapTqnTCDsOMrLtPbCMBrgXEn3OTzCQE96kI2F58h++wxSEOyQmKUg3tHKPoQTaFms9mV296U5u0UicNaUb0n5CLhSl3BhL6x9cwZtXrrB/Tc1LQoIbSnN+eLx7XpbL47Ren3kuJz9LT/ffc8T1bupStx4GPo3TC7JvP5wo8pXJmzau9I/077NJyl6dxV7NlFqHCWw7To4ZKp9WsQw6T5gxaZKqQdmJKkoRFS8i+FMjtbUBepFmrqw7W+zvtIwDjR2McVSBq5ba2tMZc4XAzjOmkAedwjAToskVW2pekf1xsqawKL4xnMg4mOmEv7CGOHP20qriDEdc0unE4/XDjxRw9IJYFofYhmIdHyP7KyGhPUwLi3M7ZFbzT287y6DyBq7h0vu1yUTLEOr81CNU0KV9vjrWwk2tig8VZVFY4xZrG0Pp141ahlyx/8fsB8Myl1kEQmIrpc9ptbizP6BqYQyrLwi9rylRnzoO65c+EWjfWXFow8HO1fMDOlMgQjnlKF0pXaJ2T9h1rN/tXRdWfp/Z4lIf6NpFR/5n3SZh3W7FQ/L8S7eH2r6qd51/5N7ZhbpMLzF2jQqiLWFYsJI9MAuLYhd7K6b4ZYzBRHv/qlDsdfj9H7rBhlFkFnMJ/KV7GU5US/HKwkjeYhD94gT/qV62zTjVDeUSHdI8JOXj/BKx/XZRRnHbFanWUkVcoZ0lMVdLj0KDlhkF3SQkHirunjfo2Zpk9/mimA/EzTGgF77+KuDyWIBqKFVqCIq9+pKFR4Q4qJbVgpIsYfQIid+W+pU1cR9dqqvAcrOuhavalBBTDOgGyLLuHHA66vtHJHVTDMZzQXzswkC/N83WuHRfpJUepxD/TKbYCq92NPSHZwX6rKdXlOwl8dyju2MRWKtR8D/nIQSiUIL7dBQVB61mDS1qHIj0sUh45IBzMI5r9sw02hXWJjQPY3Q/BwAhfJb+FzUp5PNu/SXBajeEqOS0MZtkAYutj7lR7wIR4lr+LDCMAIKHClVqVMFJFTWqLJY7HaIiP6WULXRYXNt62CTdSMQARKYAAF8ZTlh4Woh14R4mge5qsFLQ3IJkZ5MbCNUd3K//BUwxHw+8M6NVrFZklhtR+R+Bao2kswqAWhdtajJFOAof2bVfnkHwWt1G5jjlYqjOZnCZhdVyXXLgUUIbXZ/BpqQot2EzwlukrLKigwfaxUVFznmoTdDa+kY7BkXVF7pB8OqRyJXnBiMS3uh/FAiKHjPaTCV3ycD0OVHQVbgTD4bgRonPVX8hltOMbaMbfOWPFbUhSw+zN3Im1RFE2GMOZNwvDDvRODxBjuz78u4YJQ3Qd4pMWcwjCeN+rGxFHoqSJ3Yk7LffDpiZmrAQBusLlzEpPPQfuG/jTDKE8mBCNnE8k+EoC81WPHDG6UIIV7nHbsO7R2JzWEfwowyoBcmurLe78+jhUen98VN00or/sYdHvE4kvIUnb5oKzRYOGOZU1GFU2cK2gfYRRg9gAVYeeq5wIEBiQweVyWnh+oqp4Q/0aKRWayZYVIpBhbQ6e+yUrny2sFzWiP1yQtSRVQdEOOr5UWH+uA24QkfmUWaZ7WoJLWhuzKtaa3RZR4M7fvwsCu0vhT9c44PBggDalk6dSYijdK9i+58CW/u1auXoDAVMMFuEFj5HiVkBx4Ncl9QQyGfy1CnwVQdrq6GiwmpExgU/qRikVY9ykEwPLQfXmFAPVzAfxelkX3qGKlHfs5NpKEYGmzFW/oCNe+cxmArcV++IeEUHxnzY+30y5d0Qe9wFBwtLfsBrbfqMG97uW+wSj4EQJDcw11M0eY9Q04XKpkm0C1qel6roODzaAK/fKvcfZ7aEkUlRKZeb4tKXWk+/K3dw0JDMw9ysABCz700YL099wSrxQd8S34WSxl6xgNEnFnZZtVQrUoSnHuYDTqqUlbMdU7G7Qi+thJAHkrRszXrJbPX2TDLi1atyEjiT91pKkiB6eRSaFG7QHSqS+wFrQ6GVPDBkK+FBfr3UA+DVfiC37UwfUINH3xX5PI+LKpnmmKeWOkobHymCjtt/tIW51H6A8IuK2W5IhbCBIyaeKGr27aTAldwLVE2AWHunpHrv3IeTiXSf5GB8ynTHJy8yDVPNGkuUO83X5azigw3EfQ0rdwTrvLJZ54q2CGNlWAIAsIMaiINIJOExThUC9CYdhMznJi+WJesTdY5nUijP/8LlvmvESWF2Wfir9Y4chCu3QzuzNi5mc6pbMZX7QVP03xDz1m5XbCcAtulICUGIcYNAIc6EetA6MFGq1BCdUrM11D6Mu9sccXEEqprYn+1C7oa2zIAkcSFdM/Am2OTT9Nrzda6EaJTiQCchFLVPOoBuVR6lqOxLgmeLtotlZcwG3iUOga9JzxDWhn2P5GChfheJRAjkqtsWyg8+elw1NYwfJdDADhNCF2Mv3Kk5brBQw1vnPOYZtSSZc8lTg/1i6h+BAuCUKwLFt27Zt27Zt204mNia2bU9s27b151W9xbe6y65bfc6qHWB8bdOjYqGfTzfa6qY5sMonEr5zv9OU9IHX3XHEmRWzKft2h/aAN5LMcCXesZTuW1W4yu33MQ36EDuOB+SjZE9xeXG3XVP/ndBe42ydGlx3oskob996+ymmpDuNtZZ4T2XuBrJWeyjLqvQymq6z2e9nufNRAUWhDkm3xQYu++vuFFJE40P36xm7MbCWzEQBVFtOYF19caY/6kzLEXfTEmrb2uMN66fBEKJw2mU9JgpZd/9DpP22koOZAuEeMDUdA5Vtd6LAM8wehksvi1eEsgD4U2yr9S6C7g2sONG1OQYCxUvrlVkmX8buskeW4JU0cJZy4gTEmXD0yrHdnhb4GY82UbcnrrGNqkzu9JLZFcEPGl0oqzG/2iLPS/1PAFKi5JDykFSjlBkNuy7j3hfE1q0s1IVZIjCzUyQHdzMdNXCQZ7gpLEV2UmakpTlg10zuU8FI94t+dsr6tT6d36jZxnRPvMLRv+SvI6wce2DY46JwO5rGQWiH1FWq2QBZeFYc6YfWuJyykhri3a6k8PNNi+2KoAXb3MMQLkTBVOJcWLVbzLfJ8aoucxgr+bhJfixa604euKVf0/Vrts4XAAOs6LEyEuH350+F4o+8F8ogP9CHvTe4JHjevv8tMPjca20b5cT4H7XV8/TBxq3QghIHJUlsYlZPS2fR6zuhCtyETNlFNk0pFNGNM1r+IF1jmel/sIgKZWMoG1SSgeeANMgDibQuskdtNFND67AqoYrL9ST13KFnpTH1WQ37lBwH43YHhIAM8Dmd+sya7DAkYxbpXuGjAD+/FWTfafwmHBemXQHBil+pXRd/qH9Z114W4afZXR0g/2+Ti8DaNO4BbiZzJewg+f7IDS56fys0Tj6iJBRI3cQe7RPO+L3dbx0+IGjjD22AfcKeXFYDB2K5CAC+hLXVHcTNsrozhoOsihYAaP3ClxsDyLVQQjDnU0kyJIUW7Ygap1a/+1dcTIcrijSOFYmP/FoSFUpaDTf/lNA7ECSFYswQl8mA7p+fuTIMJ2qoEh2IYyUICKManEg+EAT5R9TebP48Q8fzJJ8t0ZNtTNgOsXfGsDmFyth4PFyUPEtJp+VEpeLPUhZDsgptdjeFCnWL58XawcT72Ni40uG2i9JXT/qL8bg+i4cEMBzn5Z8gN/lrH9w46M1vS1xsfnr6dWe61JaPCxL1Ou6OBDgLRqskpHx71Rz9mG9z0weRoxLauZs7VCnbUMjEakfvEHU6BO+Um8sEP6tMOt7hUGa/4LQdrlf3q25Fzz9hXCsTbLplqK5MjAY1XSzxmUy0xlO2080CE3QgUQ4bkxkoZdyj/r5T7D7u2vf9Mjq8yOgjN+YszO/n65Rn+vTIjbeCcLRSQqqjVq9GZppYL34dEb76PKVwhqG+Col/v2EAR8JjShzbv2MT7HC3Y+cYGxeu8IQ6dhOTKv6hFddKzlxXim+8BtSa2+Ela/sHh9eH5a1l/3hWu3++9Gci0eJkHufNi6ytL7zSzAxFAT6EIuSutTLmcJX1A/hryyDUodP13/miVsH1kDwZZ2KTG6J/EH/wF6iGOVmSXrQDBiGrM/WWGuP8NNyykxUF8Yj34+uMs7QHuMSKZVnPcO1uEsioppPtRMK9ODJv0HGWYHs7FOkMH+5cL5aKy0+8HqS46YLE48ELncu3welwYuc/K4T6l3CjjHVH464n2M+FbqMQfx+GUW7TK2GXP/418HgMS0Xdjo4PG+WI850wjwS5qIoooJ4Pv2NRKwhZGdforu4fMINwe1aF++pTmNi12JqnUv/Gn2lP+iKO+xmh5Fcs+PS/7RTK/rb3Fi8pYZ22eD+N76mYgJZbrgUp1R5i3iOBOuc/M94dW/fKron3LmiIyCfuWwUBekkHgegxFvEV61Ss5XvHgDmNk0wzAu21VhfCvraK28LWpnEoH1aSYE+kTE7aHIS7/Ik5t6n0o6BhfhBSGCGOD+cDvOXllpracX/ydclLtaeCrLbX9OTLA13iNku8EGzAAjVneYvtdADk+Z2dBb3VFReuFsrpo4s/NpT3Tjz5XSBlgN0ajiO3EvLw0FC6U8JZ4vXtePIoeDfBbcL1puHDgQAEJ8OM00Hxu66HIrFkPN5f/ZmZjVVMTE7u+SZPnZ7SZfhhY+/VgHsD0Bbti+c19x4KyjwswcM9T/dGUkjHfJDiPorAKEVFwBKXAVE/R0PfdN/0N1ctYWVtnp34r4KR6Mnooh8uX4ccaA6gJlOiTj+8Pf5R3UcbWjo+3oBLLyjQAwNqwJMyA22vaZZYzBRx3uxPHBNnr6+pMM6ML66mB990WhABbc+hFqfuOIO0YxCe8zedGdp7b42ND2a81YcKPtnIM0lASsBSgo7e64t6RobFuVY2R9rq62cuff0SfY36+fVEKdIu/qudXS+mmtqLgkiOjy/Tl11B/O2NvaPQQM8PLPWCffetH5uHXY1/GBHjXzhDf9o08TaP/Fj2NQH1Ve30HgACgJPL
*/
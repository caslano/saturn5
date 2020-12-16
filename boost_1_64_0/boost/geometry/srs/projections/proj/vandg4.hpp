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

#ifndef BOOST_GEOMETRY_PROJECTIONS_VANDG4_HPP
#define BOOST_GEOMETRY_PROJECTIONS_VANDG4_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace vandg4
    {

            static const double tolerance = 1e-10;

            template <typename T, typename Parameters>
            struct base_vandg4_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T two_div_pi = detail::two_div_pi<T>();

                    T x1, t, bt, ct, ft, bt2, ct2, dt, dt2;

                    if (fabs(lp_lat) < tolerance) {
                        xy_x = lp_lon;
                        xy_y = 0.;
                    } else if (fabs(lp_lon) < tolerance || fabs(fabs(lp_lat) - half_pi) < tolerance) {
                        xy_x = 0.;
                        xy_y = lp_lat;
                    } else {
                        bt = fabs(two_div_pi * lp_lat);
                        bt2 = bt * bt;
                        ct = 0.5 * (bt * (8. - bt * (2. + bt2)) - 5.)
                            / (bt2 * (bt - 1.));
                        ct2 = ct * ct;
                        dt = two_div_pi * lp_lon;
                        dt = dt + 1. / dt;
                        dt = sqrt(dt * dt - 4.);
                        if ((fabs(lp_lon) - half_pi) < 0.) dt = -dt;
                        dt2 = dt * dt;
                        x1 = bt + ct; x1 *= x1;
                        t = bt + 3.*ct;
                        ft = x1 * (bt2 + ct2 * dt2 - 1.) + (1.-bt2) * (
                            bt2 * (t * t + 4. * ct2) +
                            ct2 * (12. * bt * ct + 4. * ct2) );
                        x1 = (dt*(x1 + ct2 - 1.) + 2.*sqrt(ft)) /
                            (4.* x1 + dt2);
                        xy_x = half_pi * x1;
                        xy_y = half_pi * sqrt(1. + dt * fabs(x1) - x1 * x1);
                        if (lp_lon < 0.) xy_x = -xy_x;
                        if (lp_lat < 0.) xy_y = -xy_y;
                    }
                }

                static inline std::string get_name()
                {
                    return "vandg4_spheroid";
                }

            };

            // van der Grinten IV
            template <typename Parameters>
            inline void setup_vandg4(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::vandg4
    #endif // doxygen

    /*!
        \brief van der Grinten IV projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_vandg4.gif
    */
    template <typename T, typename Parameters>
    struct vandg4_spheroid : public detail::vandg4::base_vandg4_spheroid<T, Parameters>
    {
        template <typename Params>
        inline vandg4_spheroid(Params const& , Parameters & par)
        {
            detail::vandg4::setup_vandg4(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_vandg4, vandg4_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(vandg4_entry, vandg4_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(vandg4_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(vandg4, vandg4_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_VANDG4_HPP


/* vandg4.hpp
82GZC44kYa37CrwF1mwbkIa5B+m7nYb51CNtpIqxbcZAw8N2pVq2+V7z/0rkn8L5Y8sSsuXc089LSv9wanqV9kxFW9FnGzF1YsNgpO5EN+pc8vfm/ITnfonHNT32ptbYgDEbUBW4toP9ikiYC/D8gyEd/v3spcGwLu+s5wk1CM84DaoLLky0IyGBVeR/pxSvShfaTbzt6yVsUhTdJhLp+ArWrHSLGS7tMnW9SpBDlA69WTuypbxP4PZHXhKJIfK8FuUB2oodg5pyNnde2MxLpDwdUG0zAkrA26zDcRSU82HJFxO2p4S0/GtqlcTgdxssRhnLbm9PoEct40pMk541LEN+OYf4Q6n36YlNG5GucAhu1kScYn8dptPHX7TTffPSiBxOlJCY6pdextcCXYEPK+UoE3Q2KWqQJDiWU/vDq2H6P+ovyUzr3N2qZYOOTduzni9MF0UcmEgNxF4WSXJoRN0POpwyVy+MPQz2pRRMn6yOV0CCHDgcA7FOvwRvS7KHbdillaquJezQ2xTsIVHUxbpL49gDAjdYQryVD6KZQW+3J8A+840BGWyfyYz7Lx+1J9reUEu35Z/A5+/V5+zt8PmU+rwTPx9Rnzs+hc/lzmc7fN6iPjM/hs/r1Odd/2xPxGfxe8sX8H5JhwYmXTlVT+h18VA8h79u3w15jjDySNiaoRy4ZYTWOCXMeX70GeSxhQXwRQs/75/h2QTF/zv89cPfXvAMhedweELwbOrgmQzPefBcCs/dAzL2kyVoej9tfmtoV+2fL9ufp3Jsf18BzGJ1MXypm1CQM/vk8DRfATT78Leo2fMHimZvDlk236aurjsZ0uzxw5/+zZ4g/OnVbNtod8uL9k7NQWHpTbPjwrfzMzx5A92fGMR9Cs8ueLzwnQ3PAQO/Wn0ljez6z/cyBrDj94h2wj/9ot3i+U3KX9tC7EDdnO/bPtI6R7r4fa74Tdu0ZHK6Rw/FPwdGp+GfPoF6tDbE18GB+gc9/FoQqO+GZv+DlX3Uwx+0J1AZnk16g7aAihgBQxT2HAfwV+ITmgq2YZqtarBdbmZ+WZqaCa3PAE71zsc6pF8xpPs9yoBum/AoSncGtWHxkoffmkHKYiySD6DEyL2EQMXP7XCEBzTjO982aIeR/P7E+0x3FitLDor35PB7zPCMZvsrbgO/9C+pP2z/Zxo8ObFedoVBgRvqNJZ885/byXS+x9AMNJ3fPkSyZrZYDIne5F6H4o6ED4DHtY0EoGll6inqGTIRlWCxQadu3t9TphyZlDrD0zjH2/j2m7QyeWQPUtaKsun5fm2+pp5UzOtTAKrelev0rpyPqHd9Nz3UfLD0QGfcPw9llz2I54XNUO/zCjI8a+DZCc9Q+C6C52x4YvB4spJ/VpbthT8+/srIynzhv+WXvBSavD2NDloXU8wK7hW+2eP00Pc30+yx/GDVM1U9BrAeK7SAP/8DAs7QAmZ8DAHHawG170PA4VpAP1wUFGgB/TFFdy2g8gONSwcGeAYAJbd18BTBUwLPqfBMgycKz7yDv9r8s5fzG9s/VtUboepVByKpetkmvyBww0xbqMLQgvg1HvVjh9Oozx3OdUuuTa2qnuIyjR49PNLI6HIb/htlszP/3MC8NUnq77rmGogE5WGj5vIQGGXVVcLFYA2A4RNcpxohNoQES2i7p2mkZ/2tPYF7kSrWXn73E9yLrMM096q9yLjfWB68lg4CJL39FL2tuKjomRr+AIaPdqE8ehCWrLNT9r4qTxXOiodbouxVLlAnY4rumsvGSt62LaVtW2c+nVoNR3oH1WIFQ6QDZYCC0gVpIzICTvRBKvoD/O9h+G9PMDbgf40pjdPiRUIGIOxjnWw=
*/
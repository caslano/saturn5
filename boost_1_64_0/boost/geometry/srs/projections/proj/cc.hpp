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

#ifndef BOOST_GEOMETRY_PROJECTIONS_CC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CC_HPP

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
    namespace detail { namespace cc
    {

            static const double epsilon10 = 1.e-10;
            
            template <typename T, typename Parameters>
            struct base_cc_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    if (fabs(fabs(lp_lat) - half_pi) <= epsilon10) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    xy_x = lp_lon;
                    xy_y = tan(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = atan(xy_y);
                    lp_lon = xy_x;
                }

                static inline std::string get_name()
                {
                    return "cc_spheroid";
                }

            };

            // Central Cylindrical
            template <typename Parameters>
            inline void setup_cc(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::cc
    #endif // doxygen

    /*!
        \brief Central Cylindrical projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_cc.gif
    */
    template <typename T, typename Parameters>
    struct cc_spheroid : public detail::cc::base_cc_spheroid<T, Parameters>
    {
        template <typename Params>
        inline cc_spheroid(Params const& , Parameters & par)
        {
            detail::cc::setup_cc(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_cc, cc_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(cc_entry, cc_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(cc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(cc, cc_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_CC_HPP


/* cc.hpp
b9oQhu1obmOJGVx7/xnVCySdK2gH9lY7eNZ+z/bxZSdUB9qhKSHLLbUQW16l17wd7aK3RQ+5jQ48+a44iSd20Jq69xgWOR688s6IWXDzfdP4pUTj12LZN7GHGcLxIk/IPmX+hdkRo4Kt0YHyuVN6RcT4RY2ayADd2i6bZoWYcVZ7Q2rFloNl3btHl2WToJkMCRHSlprmYH+ObBOvOa3ionEDpKYdHq3VK4nURr2yQl8tNJaJPfXRbUR3olNbKS+Ko1utG1vYsq9b77PcEz7JzHcRY6NnWo6UEBoO3G2DPy9qLPWsKzOYM+/g23dzGVrKOzQDo1zu7dCvSIx6j5EkuI4VR5cXJT7iHPsweX95uBQidUe+tv/FWYngmqE1DWX14MlzSHrNVNRn+U0PDjVxDfMGPIEs9GFwL7zxhTSSdeWsOPc+zNZb8AC7+WQ/9x5mx6/T5kpboJDnaXPDJ/C88XGKgM8O3t8U3Adh4CUhvLg6sbiiut22lJXQGsPrZVZbEsKjUNUlbDovra3xjfN2yiuvQbwi77SlmOANiIENKe8f03WmBe9ay/QfGtpU8MzOL/lzRVQbgt2JtchIFRtP22svi8Ht0ogRl/buMM3DOJf4JfKYhs3nMs5mLI16a0/KtP4hrn4UO17VUm6seUd6xzH9XKvlAtMxCs/UW6/lK7FpFxGCrfflmLFp1PT3342a4R87FL7ZKp5xnxnKyG858XOzLqbltr5oZZm58F3aVvq5VnwGxdiG4qyY2HtdJfZNrx0m1jV9xSVo9VZ/S6dbHCHr+Y2t//Vot/pcS29cq8+1RIn+HmToHCiyINSn+xx953xgpYh3H4djoN8dG4yCkfVDhOxIuTt0mLy3CXVdVFfVpIvHRa2n+Vs48fPl0pu0qYP3AxVVlhSmhBhaD8vYD72rYau1dbxdjMsfdJuCxcWI+I58r+dhgc4LZiPDb0dovVaBYvPLtfQgx0DWltXViHNYYRn1QXj1wBitjwngejCC3sR053Eizwq5vyKAm+3cgcKV7V0XtKH5Ht+TrfmrkQ5L3jtV6jZq1OMTrTuDdpobwU0Zu0fgSJqfbtURpc+l7wrva57RA6SHewv9RN9liPATP4qMpZ2pfTIOqFRBwaLyKvjHH3rBq2cbnPAEWVljmR+bqamzzqOtN3iByWP74AbvHIPHS+otLDm/nNJf4wVuhDGfTY5KqG32lJgy0TRaIZj+CB/pQoEXIvlRypplUPxAy2e08FFg9fVlvg6T5ZozugIvMPWqKowPKvt0qcGrbxGl0O/rNG3NaMI1x7r03o+yUtMEWfZlIj4imlsq2xHcvwze9tsyh7jEttUWxyF4i2dUXOsHK64l5xLm64Zg5IpKLD/Y7GE2M7C/bFleBz2MLF9Le2Pn80zMNKKcmhqj3HR5UlddTzlAzf5Ys6dDly/WQ/Xr2k0hW0ojf0N2hAx2GRC55zAWa8FDKmr2DoFbzTPzLjWjf243z4JzBoF2krbNHTwPbKmi6nDRg+KDA03TxBldG6dJlYPURhxCRm6MX9dKbEYPyJbGZoIqTNmt4unS24/hhHgdj+FofCuG0yp+lKcLfrvtxttts9wIL7ZtuknvfbMVn7HHpOPxGY0fGZ+ReWiLRBJBFSte0IE84ZCC24E2NcV0xrWNa2I0VvzFwut4/CVsavvxlwhn28Ztk2RtxWq0HLaGI6N6VmzD7nfHYxsav0Vso5lO5sxuE6I9/jZelPhIvL9rHR0EGIg0yMCDoDtzppxTfIuKzuvbT+ZqfpLzK+tNAZY0uApXEVxhx6A+l2707T3NfLZa7TnFnt9nngdbypqeG13+AM+5d1n6TebZgzybOz8l1ZwkEHM=
*/
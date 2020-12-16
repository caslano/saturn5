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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ECK5_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ECK5_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace eck5
    {

            static const double XF  = 0.44101277172455148219;
            static const double RXF = 2.26750802723822639137;
            static const double YF  = 0.88202554344910296438;
            static const double RYF = 1.13375401361911319568;

            template <typename T, typename Parameters>
            struct base_eck5_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = XF * (1. + cos(lp_lat)) * lp_lon;
                    xy_y = YF * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lon = RXF * xy_x / (1. + cos( lp_lat = RYF * xy_y));
                }

                static inline std::string get_name()
                {
                    return "eck5_spheroid";
                }

            };

            // Eckert V
            template <typename Parameters>
            inline void setup_eck5(Parameters& par)
            {
                par.es = 0.0;
            }

    }} // namespace detail::eck5
    #endif // doxygen

    /*!
        \brief Eckert V projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck5.gif
    */
    template <typename T, typename Parameters>
    struct eck5_spheroid : public detail::eck5::base_eck5_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck5_spheroid(Params const& , Parameters & par)
        {
            detail::eck5::setup_eck5(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck5, eck5_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck5_entry, eck5_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eck5_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck5, eck5_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ECK5_HPP


/* eck5.hpp
04ABUnfkCJrqvNmukIW+YZtHirwL+oZtvl7Almg8KR81GpYoYKuA7dAFHaYE7YHtDaxWjMfhum/TBN5Zurz9leBdYMf58R8BuxzYncB2FLCrdd5FAnYtsG26Nh/L6zWtsgXsNk2X3QRd7gM21cr7qs67r4C9DuwP4O0kYCP7heWNFLppdL9wzKcLvLh+Ia3uEbDx/cJ+5AjYBA0rF7BkYDdTb7KATe4X0upRAZuu6/1cwNJ0+/JdIVv9/L6BK/DKgW21Fbwrxu1cnfcGAftTv1A33SJglwPbi7xS5/w1or/3RbT5YV3eTQK2SdNgrIC9FdGP9zRskYB9CMzmyc3A4KFm/f0uIm+f/iEN3vf7Jt41mDajgAtiqutrGjkpGf6sr5wYXPg3MWFSwqT4ZRNX1nM9zFTzbPWU5In13DFTVjpRv7FcY6iMWJlc8FWg8y1KLcgPDqnNz+NnQvKkhPhJiZN5Etz4P7emvmEJlzSuJpVUhnf+j9flTJpUwD9dr25NAT/JWFPIt3+urfhf34+CGh4XhlfOBBf8b9Z1TMz8F9Yy6l9amrhIzi5VUq+dx02lNLvbPW1BTnp2Xl5W4cK89MKUnByueJoHNC1vQXhHlLkpSaDmz81NT0nLE5DsBYVpS7NT5memFqZnz+FKKPEsJzOVv0JwHjeRzSyIo5WymaadpbyTyqJNB4gT3JpWUFZdXlFdVj8xoTChIC5WfbsVmjsTf0nNPPYrW5yk70Hyb3Gqjzc3Hemb2gQx8pbmGbpGXzKWBQXTMvnZdCFYeurC3PSAwuk5XOPG1VM8WpidmbogLd1HMj/np4VXwe1dMSq487OjgpqSnzU/I7XZ/ZE+m2xBCTH2jEudUcArcMrriqpGZVRUci38TqunTdm56drAUfMqOJifnZ6fsYQbtwqSJ02ZlNCUu6CxKq6jJSTEm1w0In5SwuT4KUmT4oOz1L+8kOSk6X4h4VirAdxB5fsbvp1bSNqfVEQ6C31RzPc/Xc8/019dRPA2IErJT5V3Uu1N6/Yh+Vb7vqQSUuxdPYOYK2Zzx9wyX8mKdxMM0fDqslWFxY3LlpXV+Qj+2xirec2Bomwrv8YKzt/rZ8NiZagREeXKApvaM0I/r22sb3aHw/a9dT11ZWUSPqp5eeYdeKOBI2I+3LwfqbpfCOPFR031Bqrf14FROEUlvOJIo8g6++q2lDTUVQJvQYv6ptJFuXHhM93n2jVUUF/vn1GvKFXmXZZNtGSwg9dPi/fv7aifBS+RK2ooku8D3Fn31S636fkRfWN11y9vbICTqmW7x+uyq8oaltfompuefd07KNvkk3TYxdB+dYOETwBeWA9xyqqTEsT7a4ZSFm0w770LCGg9p7wWz094iXUB1k1eY/3qyGri9xcRc7ibNQyc3Jk4KS/cRzyRNcVXLiEmV8Helc+w24mXfsXe6nLWSBrYN372W6y1YBSe9jWx9iE8w5DvS7y59jZitv3hly6OGsU+kvnE8JcSb1z7I2fzWVd85S/URez+EWJQV05mrWgs67Zrsbc+xhb7O/GVStYDWMvdtYF95FdCa/Y1XH4l+yLvJy53PM9G017KmrHaU317sjfTY98465Qfs2Z6Fet5NcTcG9YR216GP8haYM73rGHfQDyPtct3WA+ZRT1VGKnnEbtezF6fTYOJDVZ67MFl//xHrOExtmnEvt4mFlnnwkNdaceXxFGIl29gb+Oh71Pf36AP8fA6yn6cuHzl6+xNYQ/rRex7WFrHWuAm4s6s6ZZA19tOIy9lH42zMfwvHnYQe8b/Dm4x+yLewzdJDOIwwecYvn1j1Pd703ACfZ/zVvrh+0k7sU/Ht7sbzmc9sD/57iT+xyg=
*/
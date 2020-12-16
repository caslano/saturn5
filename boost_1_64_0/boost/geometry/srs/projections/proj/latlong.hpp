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

// Purpose:  Stub projection implementation for lat/long coordinates. We
//           don't actually change the coordinates, but we want proj=latlong
//           to act sort of like a projection.
// Author:   Frank Warmerdam, warmerdam@pobox.com
// Copyright (c) 2000, Frank Warmerdam

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LATLONG_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LATLONG_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>


namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace latlong
    {

            /* very loosely based upon DMA code by Bradford W. Drew */

            template <typename T, typename Parameters>
            struct base_latlong_other
            {
                // FORWARD(forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    // TODO: in the original code a is not used
                    // different mechanism is probably used instead
                    xy_x = lp_lon / par.a;
                    xy_y = lp_lat / par.a;
                }

                // INVERSE(inverse)
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    // TODO: in the original code a is not used
                    // different mechanism is probably used instead
                    lp_lat = xy_y * par.a;
                    lp_lon = xy_x * par.a;
                }

                static inline std::string get_name()
                {
                    return "latlong_other";
                }

            };

            // Lat/long (Geodetic)
            template <typename Parameters>
            inline void setup_latlong(Parameters& par)
            {
                    par.is_latlong = 1;
                    par.x0 = 0.0;
                    par.y0 = 0.0;
            }

    }} // namespace detail::latlong
    #endif // doxygen

    /*!
        \brief Lat/long (Geodetic) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Example
        \image html ex_latlong.gif
    */
    template <typename T, typename Parameters>
    struct latlong_other : public detail::latlong::base_latlong_other<T, Parameters>
    {
        template <typename Params>
        inline latlong_other(Params const& , Parameters & par)
        {
            detail::latlong::setup_latlong(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_lonlat, latlong_other)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_latlon, latlong_other)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_latlong, latlong_other)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_longlat, latlong_other)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(latlong_entry, latlong_other)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(latlong_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(lonlat, latlong_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(latlon, latlong_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(latlong, latlong_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(longlat, latlong_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LATLONG_HPP


/* latlong.hpp
czvPuedLvBWkznHiOMpJ9JEDnZnhqwZbKrtVR8nWz+ttvPXT0qa2fvQpT779lIe1cx2nOtRZJ7dkQiM+QO/NhOYT9CYNjdf/GN/YiFfntvhyolcAkPpa73BjhHtM73ArCXe4kzM/QI4bdvMfD4/x/Bj2wH6O5/d4PsQzA5mTh6cazxo838fjCe3Rz2tcPu3wh0Lo1EN9n/2P/dz2E5uoEl1YKZVIVj9A4NtxsI+opdiXhK/6pB/VJXyT/veRUpnqnuPKtONZU5msk7XKmF2Cr1LtPzyUK3LoL5vto+VmS2HsON5SWN9P3x1x2izZs+OJZlRReEQozGcKpU4Kv9mfKZypKEQTSwqC4srcszN6YdUn855dMZFuE9JDXzZ7dhbpRpAWmkeDpsypdoastaVpQti0iwDDCddMxNRy8WGEpBh/LjHe9pLZsbNiHCyJWZUdiVoymf26i0J6hacmhButDZ/XJYbSl1wyfNNYjmEKght52DvG6WtFSY9TEfmtEPn4RbNfZxG5SIi81VfLJp0FCtZxVV/4PdPXloRgkd+o5dGqq9hv36+L0cKrgZY2N5hAFndowq3UEdXCz17XqPTKKfVqc7dfHN/J2cAiR4msP0Wz5ENJyiGclGOdZbwhwkkZiXBqA2B67dcsxtt5uzAPbnWi355IlFNJgwGSDrYl6lWvTf4y8ZgNq8iGtduBdTOwUhe5R9ch28XfAIqFQJEATmTb8iw6sx1Iu21IRRbSweW6Eh9k3yCpj/oB2s+ArLrWxD4fB10LBYc/itp2hUAeJqXx5kLZF0s+4u4dUd7rbeRN/67xqIunHJk8gPfRvrbN3sh4oy8xc7QNtqWeYM4mEUweEbRV9umvp9NHpuG6bLCBTQSsYbd3AdeWogGih7SNast5ztpyKSIjI+YBYmqqMPXa80GL+kdjgtZq2y7+V6XXvqp5TZNY1j9vNmWtWHIllibEklyCP00LvfBzv06neZxzLZONACfLAz1mqEvQKAUdFHCpBJvIZ5dsUwDkaMjSrteoz8eK6RPjzHy1JbNRb8ngLICazi2z0cjv9ffQM5iQqLPrKxBiqY7cvu0CFEPH3GHXchzQK/yE1iXOuacDZ4ohaW27dB2CqH7o04v9rtD6EeEXfIpw9yTHD0Kmfp+FJwnXysWpWxMPloNOnPy4DLpNzK0nAfdsg9sTi5cSepGqAQ61qVMS215Lp81K3C6eul2vxlXV/apU3Td/7jIan7IfV93nvK48EKXE04hHS9suEFJr3Uj1EVJXUOdf53Vh+UA08Q3sGpc18qqqbfahU/u6dEEgw13QviIZ+4ORwSxmf/1LkU2xa1VpozYUvbWBvtFZiBfNRE4/5aENdBffo06E78aeaCw/HlhXEI0RLr5v4WA3dX7PKT+qq8rw7ZNAYAI8N7h4nk2e/axp87InmvB6fLX3ceyjPOH1HITnoae9nlOe9HouwfPHp7DngecGDGHHbvF6nsd7Hp4LcW1FO56P8ByFOWMKsMO3Yp6NZy2en+D5M54hoBXFMwdPE5564N6Gpw3PGYjrYdCeALp98bwBmMc71jdWfv6xvfsF8ASD5OrT1w4XAzjkGhgemzeIHIP3GTt2yNCxw4bnj1BItH+iA2Af5dm9v72//8VfS2QkmrmrvFLx8SKvRItDtTFbhM54tZplfVvvJiQuOQGILiJBHw/LUlMFnH6ukkXPZaMDnoWOnjs1zJKUeuaFTEmpXDmEPbTdkpQaMqQ7SakBIinlbc+SlGofmimlNFCIv7TFkpR6aB8tjHRqLFPyKU/Q79hiST417ZNJc5AgLdtiST7NNTQfw+yg9OFhwuJZQNm8GwgOaaj9NZfIsdWfUg8=
*/
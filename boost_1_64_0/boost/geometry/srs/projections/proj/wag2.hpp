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

#ifndef BOOST_GEOMETRY_PROJECTIONS_WAG2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WAG2_HPP

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
    namespace detail { namespace wag2
    {

            static const double C_x = 0.92483;
            static const double C_y = 1.38725;
            static const double C_p1 = 0.88022;
            static const double C_p2 = 0.88550;

            template <typename T, typename Parameters>
            struct base_wag2_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    lp_lat = aasin(C_p1 * sin(C_p2 * lp_lat));
                    xy_x = C_x * lp_lon * cos(lp_lat);
                    xy_y = C_y * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y / C_y;
                    lp_lon = xy_x / (C_x * cos(lp_lat));
                    lp_lat = aasin(sin(lp_lat) / C_p1) / C_p2;
                }

                static inline std::string get_name()
                {
                    return "wag2_spheroid";
                }

            };

            // Wagner II
            template <typename Parameters>
            inline void setup_wag2(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::wag2
    #endif // doxygen

    /*!
        \brief Wagner II projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_wag2.gif
    */
    template <typename T, typename Parameters>
    struct wag2_spheroid : public detail::wag2::base_wag2_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wag2_spheroid(Params const& , Parameters & par)
        {
            detail::wag2::setup_wag2(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wag2, wag2_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wag2_entry, wag2_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(wag2_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wag2, wag2_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_WAG2_HPP


/* wag2.hpp
/VW2RXTyHaN7VHWX0fkyOj4rPq7DuLPiBymCuqcQFB9f0pxttu2d72HbKs30RR9h22432/acX1setkMA3nh1YYbnLnjuOCTD82t48odleG6F5zh4fgHPi/B4/C4/CrRsry8jE9+yXvhm/jRWG/sgjbUp8ILnbIe/LtjEvKD6MOIFxYcJXsAT7L2YkueyHt1Vf5mvhVrK618wdsS77QlOcYm9h4mZ91DKL5cPc1QNZBDV8Xa4dzyf5BRdJY4DyReD/Oqp6PDZciHQDt/G8Ydh4iuK0Q6kgQakwfg1Q1sV8EoASc2r2zKFJ3xO2guThpjGPj6TvDyMK+S4rl4zrreBsI8ifaJDcIRI7CnTDFJphqgV90qGqtLkqTSWSrPE5jQ6ZtOfhEnBOn0VZVZegVvjnvmObNwFVN50K5gZwdTUoIkyqEAFHWGQkcUrp4Fu1Dz/tqBGTc03jMjw3ALPT+HZAM9hh2Z4xsHzd3hGj8zwnA7PdHhmwfMaPF3h+Ts8u+EZBb3eYwWSf8Q7svyd6CO7c06Xri9883+0fjOMAsLeEIQ0YUij5Zg20NAe3ioiSvxr96bv0pYBgXopOvSLkSePFHUzkvpgDFZSSMoApUgjOS8nSjpKHgRYBR1F4uo+S3Wor7Kp089/tmnyEhOnkpdsyQTMR9BbmIcvJw7yGmIjMceeED8EikhGFJQ2H9I69KajN3C537g51u5odaavtlgq33H6Bj195uPu6TnpOZw09qfHjFQmvGId3gqZcm/6T8hk6rsbVE63X1L2Z/5G2Z3co2XuvddXw980erf/UuTbM74pyfie/mXa+PJ0fPXp4Xt3axK+U/eCj7P9nLPFhsnUruXfqpf/F+m112SZSVE0SNV4OvrS7in5l7phdqN383savVc8llb9reA8DrZuJjb3+yJIaWpYrpCp5hkMjC500U1MnxQHQ+ueLGDdDhk0etVNNTarIiewaTVffxRbC55PgUXwvUY359Dy+eCtuHxejcvne5QTtv6gAkKULYjLcxifh8mEGU6BqkZQ00oLxsJ0+tlH4aankfUQ3NsY7h/eQ7i3m3CffUSHO5rhPuyDGP+uROrVS3cxqHoCVWKCutoAFWFQ03xOjQTqn7U0gte9bRCM1w+hJU85mQM9TmmUMQ/GvQT64kdySF/sA/yoYqpAlPptP4YgCBRJUOnivtruJmltT0HLJOdaV7PQ5kaMd5ULbpvhL0CN1YFIMUx01+8SrpiLOXzB62RmdQxfdNm7pNlm3Z3Mt/s1iu+P8VAL18ndE8d+uJlMmWaYBJq0QW3/love6V0sOpUsNvPnlksZIIp+HZeurRVemNiilJqjVFRwvlJJ2dc21mJM21/B8ip+WnK2DIxLzlHbirSwzlI1+5Y/Y3FT2mOk2L+MLWU7ryKV4bd/TNB5TmhrZ3D10Nz9hnxFULvgAQptdetidnipCKu6CkMS60UA3TlYdZEkHU93I6gjsWO/wR37wXewY59pGR373of0jl2I1OK87cYBWLKNVxWbtNTtOL3qXCbGoe4kdWnVnVtIZk6UfMCUDCRKqkxK8gxKTkdc/8T/1kKbqKo50DmntQAQhfmGSxxa/E4e5BXqrD+1J/hEE9+/eILyghmOnbaDmmoskvU5k3Xj2y4jv/bB5JEfv6DtMKBJteGf36SRM2usmYyMNboQ4FEEOGQCLgTA8V7y6jYiioxvyVcV0zjqM3LGW/sMMud9MOn79rcffyn+H/9Cc6TuQQwM4yo1cb25bua17/HSEUEej0v5WYSfVQciNNuBNhNeDaHuCbB9/JI6cY306jcdeQtI/Ww+ZL3UUcmZHlDDXgrf6LibWLHSIvM9vj1dZqkmGjs=
*/
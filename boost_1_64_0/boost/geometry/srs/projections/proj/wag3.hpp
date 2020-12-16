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

#ifndef BOOST_GEOMETRY_PROJECTIONS_WAG3_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WAG3_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace wag3
    {
            template <typename T>
            struct par_wag3
            {
                T    C_x;
            };

            template <typename T, typename Parameters>
            struct base_wag3_spheroid
            {
                par_wag3<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T two_thirds = detail::two_thirds<T>();

                    xy_x = this->m_proj_parm.C_x * lp_lon * cos(two_thirds * lp_lat);
                    xy_y = lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T two_thirds = detail::two_thirds<T>();

                    lp_lat = xy_y;
                    lp_lon = xy_x / (this->m_proj_parm.C_x * cos(two_thirds * lp_lat));
                }

                static inline std::string get_name()
                {
                    return "wag3_spheroid";
                }

            };

            // Wagner III
            template <typename Params, typename Parameters, typename T>
            inline void setup_wag3(Params const& params, Parameters& par, par_wag3<T>& proj_parm)
            {
                T const ts = pj_get_param_r<T, srs::spar::lat_ts>(params, "lat_ts", srs::dpar::lat_ts);
                proj_parm.C_x = cos(ts) / cos(2.*ts/3.);
                par.es = 0.;
            }

    }} // namespace detail::wag3
    #endif // doxygen

    /*!
        \brief Wagner III projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
        \par Example
        \image html ex_wag3.gif
    */
    template <typename T, typename Parameters>
    struct wag3_spheroid : public detail::wag3::base_wag3_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wag3_spheroid(Params const& params, Parameters & par)
        {
            detail::wag3::setup_wag3(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wag3, wag3_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wag3_entry, wag3_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(wag3_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wag3, wag3_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_WAG3_HPP


/* wag3.hpp
9NaST1sEShNY1VgAWBv8hlmRRk/rDhf3sfngB9ZIk+RF1iWNkcCWCaQi2OugDU+D9MzHuTQLK2wejfkxzyvSuYbpoaRQeQcIsocSO85bG6l5//FrqG/Zx3b6sj/tFsulf+b25ZtnHS6ObcQXWpphklF27NJXOaGr5DduMXZsp9jsh6+yMYxxYrMSbY6KGnpYyntMMdt7KEe+dCexNkebgjcbp0X8UiRE8GR1NZnpKNT3v0Wog5RIrmiKASU5/0FLnmqT1tNe5gzYrB3ewoKR6VzAQnjcioa9AG5LtjUToXKTRDYOogROPb4mpivpEpCnrUD92UCGuskfqQtT3YX5TOPVcFPGOPgKLBhDju5k+GIIR3AVLIOqiO2CGRa+Q65VPt3LdIeQbrAS26iOAR35Ux70hyCT2pxFM9p5f8IZLQtntKgSg5++Ag5o/dhKq48JT+PT0CrXqyouxE3i7j465O472qxXWrlycbtAcZtUoVRjBLXvYNsjMJPvE7nlGrnBPZEbTItcB7XpyLqL1suZyQzF6v8bV/+WzbSgMKv/NVBIxPNTVm6oL7KUxDLgXCb6MjKp/5trOb/0T5s/i/9I/NWYE/imfBxiajoYjS1VzHaJR7ymWqpKtdSh90gr4CteIs18xj5Y6TM9MYSz8lVBT8aHv/DKq3TIKa2aARQrYf7BYxNtX5B26BlyWoACqAi6Ezb2MnP1CcCDJsCGvxb+kB/FHtiDtpEt7kayfznOz7ubCSXN93amfVzJH3kLe99yy6Otv6ucrFdx1mw/vD8ItcHen89fyW9h3tdG/bw9Z87zYGeq0PdeVYv0h1SFvnE3cJ66LOnHgLgq77PMMn3xCu1FMtrOcNLScGHPY3i/znLySxN7cCPz4nIkodwDWQqypOFmsNijJPvlsZ8BTHkdPNQTwhkHn9cGOPpDiG6LZaaQxrGXMUEi7VpM+ySk5c/H4dMpgemgP7OpBbnRlPCCej9P6xtlUlqptS+TK7XpBE9BqaY22NOkX6T5qchjNfkdPAEVKv+46oatYOkC3sBg3SEsBV55pkAYOA3hJRHgnYIsb/i+Qo9xX+FXDDRWH0XGbWgqxLxOMI1aYb5P+dkw1SVduJE3gmDqusaXVAMrmX1TQ/zVh6KOrTxE+m+yPTxN3/hjyQwuuJffwrFz7xPUt8UgE1XcnIy2e+GdU15zF83kkbZXsPdfeI9F43ghI6e/sTkiCS5c1C1Lj0IgeKOE/o+glDOPHYBKpgH2Ip1g4XHjhY6hK8zuVI6+Prx1B4Y2rRBYFrIZIcgtEeQuacY35R9xicz7llfHu97CGsnl7osEtCCRjRAsm4ZVayxvnI5v8d4aA6skV3HN7HtnehM8rTvyaNqlFmsw78N0g1m5Z5iVTfDAnmSfYEb3DDPaBA8sHPYJZvWeYVY3wdMxQNXr1Rd2l6Ueqn1t7LIAudM6Z6DkUhbk7hF5/5hK9zZIPCmGPuUKmBdZUyR/KCtdIPYLRdyNzrtXdIVXhFlfcXL25BxjZI573XNgOi6NNk5pQ7dEhYZjvSSUqXTkhr0fERaO332PiJ+gNNQvL5Pj8UWITJ1KmxiIRs2XZiu4FkwzHyxdfbKai+timR1esiri07tYVaA2l6HFBj+Te93+Jc3DWF575ouSif3udsGw4keVNI/k2PEq9qe3SxY39y5ZpVczA+HlwKXrcTmAnxvFrVPn/6Edb52Kfbs2/fb31X6a7WH1c0q/FokdDH1Ou3GfV+1X8yKz5nm1ap+lFpmz4UAfZ33yd7RqP5EGEwdFAZpc+tcykPFuQEYrILMByP64Plj3/76ho/3Jmq6GxIrpHJFJdC5+TtE5W9F54xI5ZP/wDNE=
*/
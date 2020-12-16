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

#ifndef BOOST_GEOMETRY_PROJECTIONS_WINK1_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WINK1_HPP

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
    namespace detail { namespace wink1
    {

            template <typename T>
            struct par_wink1
            {
                T    cosphi1;
            };

            template <typename T, typename Parameters>
            struct base_wink1_spheroid
            {
                par_wink1<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = .5 * lp_lon * (this->m_proj_parm.cosphi1 + cos(lp_lat));
                    xy_y = lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y;
                    lp_lon = 2. * xy_x / (this->m_proj_parm.cosphi1 + cos(lp_lat));
                }

                static inline std::string get_name()
                {
                    return "wink1_spheroid";
                }

            };

            // Winkel I
            template <typename Params, typename Parameters, typename T>
            inline void setup_wink1(Params const& params, Parameters& par, par_wink1<T>& proj_parm)
            {
                proj_parm.cosphi1 = cos(pj_get_param_r<T, srs::spar::lat_ts>(params, "lat_ts", srs::dpar::lat_ts));
                par.es = 0.;
            }

    }} // namespace detail::wink1
    #endif // doxygen

    /*!
        \brief Winkel I projection
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
        \image html ex_wink1.gif
    */
    template <typename T, typename Parameters>
    struct wink1_spheroid : public detail::wink1::base_wink1_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wink1_spheroid(Params const& params, Parameters & par)
        {
            detail::wink1::setup_wink1(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wink1, wink1_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wink1_entry, wink1_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(wink1_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wink1, wink1_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_WINK1_HPP


/* wink1.hpp
5ieBVTyAGizDlqVtsMwXmLfWk7Qk/SUEJA/NDpX+yQnTqVeU7asyVlMZqxWcJ3yc126anwMAJdzhreMg1ZxeBAk2yEZx4qvjp0l2sUdqZaJ0KaX0FKUY4uuNUgwwDeC4tHrbsbBQMNYfv8BUTLfXoFsvjBmIEoryBr97RCQ5glUVhu6qOHbEw3iXxrQskkv/ZLXtqMlyai1jk0f5k4tBTI472fE287yl/MlilI452zmlrJpg172KnsZf4jLYXLbM4mGdsdplWO+qgWF9BOAym0To6JYqecM7tRbW8k1PpzJz1f6oMX5Il1xx1tki6w17yTo/NesEynotm0OJut+oaOrPsWr821rtlopZgq6oV/CeuoG0lLSFvp5r5cNfuSzmts7VttB5vCgq6rC/Y2Q6/Vws4YqkidBeJi61NY6P1Fcki5juI4nunSbdI4Hu+KUucEMIbk2OtptluY4B+Q6G/ObjLv3klWsB8gFci3fOlSqZKQg3tMbWd8lrV7YneDNSUYNj434eGzc8ro2NbXOktOhkgKWyPvWwVNb4LVbWPP4rUtbkWd8qa779ffv79vfv/CXdHL7iYakjKir0sK2MNzDvPFsYawl1SmDeTy0R4izFqy02bvIYMcopIL4jojAscmtUOFnfLsSseNiNrvSoGqVfm/FDVsMc/QjyZ2TNa65S/HksfLf9EGijfHN6CnuyQh8uM73Sc4kMhWyMNDb0QSikIKtS3j16y2YVP32FoYjgzc41TMjjDyMhrR6DkAergZD3VJWYJ8vyJQ1QRw1AFR2cAeB0mCFT3GJerByRkmpK3XROGRMLMZ9OMRywktVsKsOiAeENMSqPpw3VUikYYte6nmVBikLtiHbVQdIibxPUFnx3ka3StkuiZi8v10zQLPC+ew8m5hr7CdfYdT/HGnvHrLErZ0ONPcZtXOETPc0XmHcjvGrgXvx9QllNJjewD2nBgrBJ5WTcdMyMkl3vrxmz3w1zYhZM6gWY6ilO9c5DmOotM9XrmIrx8UWeNtv8mjeoMJHPLhfdKfbx/e2Jr/+K+K/1l3R8J/ozR0deVz1duKUJJnnBqTpYaravf4D6R1f+evo+UpvNZk8PlfEfcGYljsQhKUwJJmVTYx3+oFqn1ajGGlFlSb9zDHCodjVqDwNjhBLsRwdu2nkm0n5Me4ArRI5kfKlQei6l9+KISl1JFBsOxdCP0dKK/Qou99E/U0qvqx3+B9bqalR+JGwQH3UM2oSPFRYuaUKkFuCbvBOjk53a0H4IgSDzUWlfvFoYPsJDfhKYrOuYrPsfQLLeMMm6ayaTdRhCPMvHiJtp7N2HPnJ3BKv688btYBhwRw/3CnHX2CBmGGHJcrhvEq7GM7MsYm7waLAXL0soNkVysy1oMo5oHOnKEmFbi4vw7J84hsaJqoCqggcgW7wHhno0YIsx9CSqGjBn/uuPKW8ZqYiuGajI5Y6LgswyCFu/0fZoWky9nkNeZnNjFfnP3I3kc+X+git34kqs3LvNyg1eYXkUVbttuQV+70pqpqlN8IyDqpw7REG+cUUiMR6C53ZTQbMhKCyxPcHY/vxTxNbJMrC9fLmG7WaUcQJscb1CtQKXd5dD+1MMbcFPXWiv16GV2LKdNQkpbpXYwsbL6oPNmC8b8jm3PRKa3zGaoYQmZKI5iNFwTf/JInh0syibyuVADaKMWNtfE1aOfQoyy7K8yEha76fdsomkuVJDUqWEdqfN5kNBeDkeduxoD3zbhG/Z+PYKdvZZWIslzZuzaZN4AYAH6/51ADBZa5j/OlPwnftdRv8ROgWfeFTbqLvZK2IzgBq+3gIFYbK2hXO2S5K5RV2LX6q7xDKDbnwv8a05SFU=
*/
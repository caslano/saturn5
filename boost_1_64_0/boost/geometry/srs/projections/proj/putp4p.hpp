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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PUTP4P_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PUTP4P_HPP

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
    namespace detail { namespace putp4p
    {
            template <typename T>
            struct par_putp4p
            {
                T    C_x, C_y;
            };

            template <typename T, typename Parameters>
            struct base_putp4p_spheroid
            {
                par_putp4p<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static T const third = detail::third<T>();

                    lp_lat = aasin(0.883883476 * sin(lp_lat));
                    xy_x = this->m_proj_parm.C_x * lp_lon * cos(lp_lat);
                    xy_x /= cos(lp_lat *= third);
                    xy_y = this->m_proj_parm.C_y * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = aasin(xy_y / this->m_proj_parm.C_y);
                    lp_lon = xy_x * cos(lp_lat) / this->m_proj_parm.C_x;
                    lp_lat *= 3.;
                    lp_lon /= cos(lp_lat);
                    lp_lat = aasin(1.13137085 * sin(lp_lat));
                }

                static inline std::string get_name()
                {
                    return "putp4p_spheroid";
                }

            };


            // Putnins P4'
            template <typename Parameters, typename T>
            inline void setup_putp4p(Parameters& par, par_putp4p<T>& proj_parm)
            {
                proj_parm.C_x = 0.874038744;
                proj_parm.C_y = 3.883251825;
                
                par.es = 0.;
            }

            // Werenskiold I
            template <typename Parameters, typename T>
            inline void setup_weren(Parameters& par, par_putp4p<T>& proj_parm)
            {
                proj_parm.C_x = 1.;
                proj_parm.C_y = 4.442882938;
                
                par.es = 0.;
            }

    }} // namespace detail::putp4p
    #endif // doxygen

    /*!
        \brief Putnins P4' projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp4p.gif
    */
    template <typename T, typename Parameters>
    struct putp4p_spheroid : public detail::putp4p::base_putp4p_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp4p_spheroid(Params const& , Parameters & par)
        {
            detail::putp4p::setup_putp4p(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Werenskiold I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_weren.gif
    */
    template <typename T, typename Parameters>
    struct weren_spheroid : public detail::putp4p::base_putp4p_spheroid<T, Parameters>
    {
        template <typename Params>
        inline weren_spheroid(Params const& , Parameters & par)
        {
            detail::putp4p::setup_weren(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp4p, putp4p_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_weren, weren_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp4p_entry, putp4p_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(weren_entry, weren_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(putp4p_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp4p, putp4p_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(weren, weren_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_PUTP4P_HPP


/* putp4p.hpp
BSrtDnNp50MpRgxQ2CEK3GGjFyRWNrQpP8opMVPU87PTAYjM3zzxcxzK4c6pH0GtGeSE6dXhCcVvzoeqY+t6OlYtZHyMeVi6mW+HoH08jLg7pMeTxbJ8jOhndgGU7P37MjFf+dTwz0n6VDOfqXlngppqtWqKPDyMpsi5jlMkBFPkI4By6uVjTnOgjFu4pClUUp5eUi6X9KnLag5mfANojLHD5IhtPo2nVXcObjxN3BKdZk6kcao2jMas0rJ8mkgDnaq7PeI0kULCu8UFTnPv7Iis1bBIk/Mo/LOfR877n+to0iTcChp1J0NT1a6on1pP+a6f9x5m3Ep5rRIPqxWVTz0MacaFgwLS2DqMx/QPQ7XHVPiEd5GH9T8uVSe8d039D8hQ31bc/C1MvPmLGouGmoe8SxnTJ8V0yNMxPYGYXhRnxSK6Wh64k1FUnepw7ixhXPcRrnQd16WIawrgMnstOyq3RBVUWjlTZLyLiq/C+DJBqcbFeVht01kVkW5gTg8NaS/x0hsu1Qr1pOv4qBfvoadyAYuu4lTANwgUriX6+g0up5b7hmmvSpVNMsum9b0Q8Z9vLT0+RZTeS0tX5XfUyu/EEonTYYIpA5mh9WWwDTDuPsXrEp7BcmuNbDJ/rmxIL++MEYc3BjA0ubytcfQQOOpqlqIRmhXcgEtO8v6Pm4Ym2d/YJTG/v8Zifng39sgQmLjTgrxdVa57jqcwQaGZjzjP5QjzM4wMMi8OXoHPnqfsiFH8NNevG5pNhxI3pNa+XFJhvNr0VGo+2Kg2nFFyTw3Xmb8eT14mG4CejIyIcPzTsv6k8s5PsbwMLq8Ky7t9GJeXkr0rbbO/nuy8zVZUoVT85VmLRVpErFD6/Iuo9IFQWaPPMG/SZ5rs5U/9keW34/KfATTGklNaVD77f7rKfARTcW73r5QDhqoo6od8AaRumgSQv9Cvu7qsnuXKcnheD4aYsr4AKx0+Ht2OsYapqao18X6cr7yPDe87iBf2DRmMzyyhPECQjPWRDIDigrsy9s6AXbaC3ntWImfmxUcrHvUyQIJjgX+zdyTgURbX3X83ZMOVAAkE5VjOhCuEQ11qwKRGXDXWqCgRUeOFUVGpJBgVITFBEgMKiApeoCCCV7EiBkQNoBBvxNpiWywe6MZtlXpGg27fMTP/zO4fEjza2rofQ+af470315uZN2/eXC4iklXEGt4X9I/JsQAi0KjMkfWzAhAjiM0PiGzdSKPJG+4RTqWomjK6U19H0dXl+BFeZNTnKmaOB2nr8cf4RS1XP7/YweZcPrAGv76atMj2Y4F6xVUW460xQu+LWu6xFH7IFKYwFXZiV96wpkNX/W2GPKY7AlKibMxONwDSGaArx3i+12KNyqbMyKodpnP8Po53tmfLG2H5NnbuVmf5++NFVIH2i7UBcf88xWDczvwXR+qB4oMtxOe3wv53Hn4GAdMB44MtxOcfOL6Karo1/KbiIjVLBrH/KF3AEi+t6tpP9OLr7Liq66uUh2pG0lHKRM51N3YNtO6I2a7hbG+ejtlOcBvZJkA2ztL1cD44su3ZIc3uH+Ep9mbqo7bl+jDS1x1k+n3NpY8SsidPUcd1fu7QJGn0Q4eWwm7kntXBXJDpt0YqrDVl7YX6fbi4hgRLSvDj1knWmVdTHXQzC/BvZFu09aFceGuMCIJ3nf4AsWwPt19O7ccWKUT5TqM57dwG2Ix+mekhQ3BueW+dZf+MBg2jCm2xbL6re85hHpc0GOjbmCnsoz8wwg7N2ugXoQsplLky3U3+1UgPoh810g4nDc+qLi4VsIve0oMA2LsztZMmeFVsI8UO90BsI8dmyVhpoH4QxIpzDjKMzfpoTZy6o5Y=
*/
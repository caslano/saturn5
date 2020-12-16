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

#ifndef BOOST_GEOMETRY_PROJECTIONS_BACON_HPP
#define BOOST_GEOMETRY_PROJECTIONS_BACON_HPP

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
    namespace detail { namespace bacon
    {

            //static const double half_pi_sqr = 2.46740110027233965467;
            static const double epsilon = 1e-10;

            struct par_bacon
            {
                bool bacn;
                bool ortl;
            };

            template <typename T, typename Parameters>
            struct base_bacon_spheroid
            {
                par_bacon m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T half_pi_sqr = detail::half_pi_sqr<T>();

                    T ax, f;

                    xy_y = this->m_proj_parm.bacn ? half_pi * sin(lp_lat) : lp_lat;
                    if ((ax = fabs(lp_lon)) >= epsilon) {
                        if (this->m_proj_parm.ortl && ax >= half_pi)
                            xy_x = sqrt(half_pi_sqr - lp_lat * lp_lat + epsilon) + ax - half_pi;
                        else {
                            f = 0.5 * (half_pi_sqr / ax + ax);
                            xy_x = ax - f + sqrt(f * f - xy_y * xy_y);
                        }
                        if (lp_lon < 0.) xy_x = - xy_x;
                    } else
                        xy_x = 0.;
                }

                static inline std::string get_name()
                {
                    return "bacon_spheroid";
                }

            };

            // Apian Globular I
            template <typename Parameters>
            inline void setup_apian(Parameters& par, par_bacon& proj_parm)
            {
                proj_parm.bacn = proj_parm.ortl = false;
                par.es = 0.;
            }

            // Ortelius Oval
            template <typename Parameters>
            inline void setup_ortel(Parameters& par, par_bacon& proj_parm)
            {
                proj_parm.bacn = false;
                proj_parm.ortl = true;
                par.es = 0.;
            }

            // Bacon Globular
            template <typename Parameters>
            inline void setup_bacon(Parameters& par, par_bacon& proj_parm)
            {
                proj_parm.bacn = true;
                proj_parm.ortl = false;
                par.es = 0.;
            }

    }} // namespace detail::bacon
    #endif // doxygen

    /*!
        \brief Apian Globular I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_apian.gif
    */
    template <typename T, typename Parameters>
    struct apian_spheroid : public detail::bacon::base_bacon_spheroid<T, Parameters>
    {
        template <typename Params>
        inline apian_spheroid(Params const& , Parameters & par)
        {
            detail::bacon::setup_apian(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Ortelius Oval projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_ortel.gif
    */
    template <typename T, typename Parameters>
    struct ortel_spheroid : public detail::bacon::base_bacon_spheroid<T, Parameters>
    {
        template <typename Params>
        inline ortel_spheroid(Params const& , Parameters & par)
        {
            detail::bacon::setup_ortel(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Bacon Globular projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_bacon.gif
    */
    template <typename T, typename Parameters>
    struct bacon_spheroid : public detail::bacon::base_bacon_spheroid<T, Parameters>
    {
        template <typename Params>
        inline bacon_spheroid(Params const& , Parameters & par)
        {
            detail::bacon::setup_bacon(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_apian, apian_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_bacon, bacon_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_ortel, ortel_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(apian_entry, apian_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(ortel_entry, ortel_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(bacon_entry, bacon_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(bacon_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(apian, apian_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(ortel, ortel_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(bacon, bacon_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_BACON_HPP


/* bacon.hpp
12+EKOutzlA+VDedsXJw0J7cziPsPqw4c82rLoIffwWOCxufsFmiPvo8ieNrbIs3UeDFXTxhX3cHryf4ZNOOMx67h5Qn4PWRmHHNO2sPJRCKE0IqH0jmwqaPSOYHisuqzL3G4PbUnYN0Ddq75k57xFXWluwLTOYrfEIQTjeySybWZJZoA/wULGtDnbZ0aoU20sJ1cuLLgNwSsxL6tph6lSULfJeVkFy3IMZWAlwVsdiWDDpaFvxSCk6yY9SXgP05W8K00rawOYbW1LALn+i3zJmPTdaIOS9wcfDXpf9V4cBNOsnOrdL0H8THk2wsYHFIvOptLb/B6hqew/DDh/pVyTarRlhdXjOnqqSA0x+dWJS2OtFvtem3JRoWTK0Xxq73MnBamlPnL+1JSPDM/Dmp+e6wU9ceaRO0q0upbzFs/w1OG67f25RSPzXHFnHrmpO3dh82pa6BCp5rNfQJ0gs2ThJrq5Y9UR6nXOTvkj5HqowBsnwo65COiDQK2+/W02C5Dl2irs9eYq9Tw+AZLoK3JA4JOjnPw0bY+ywy+2Dh7r1tncGXcOpLfnT3vI/sDo/IvaqjHbi7b32MgSeuQbt5qmO712+yWS9Bi7XgyZyhnKx9M8SlRYfOEHr2HA1wPCdNbLkGJ6WMIXX+v0uB2aZtn3sB50yhf2G/JRw3r2ZYHX6KMz+5Z7BpOiSyg+BJerp4plN5dvW07nQ3WOask2jzdKmj2STGR8BNTY7R3j8PWgMh02fJsfkSb2l/toG5ua1zR4jcmOJN3wTH5fqcJ3FQ9jIGXrSdqy/VzkbqGp5v+vaJaUYgxi3H4MYFf0yZk6kr4JeMkC8yxfXmvaTZZUl9HgYpUgcLSbt7hVNfdS/n92B20PxS7xNeKcbv3g++2s69NYVuf6LczUnyo1by0PHZznqb/KDNQQoeutbx62ydFqyCyWGJs2w94txgxiZZ15WDP6fRG+wohVuFf3eTwUu8KFVZUFWwQE843NnRbHoWcnhzkLxa0y3uRgfi5WplLdu7Pbg9Q8nknO9MN848z67H3YFtGTI5a3dvYHv+cRnSXNoDo2+ZrwytAt9PS+tUsdbz9r6t5WOjJbRDhQ/JbrK9S5G+nZDOJwp/cintrVKjgDGFv0e59PeAiTqLTB2zu27rPCjrOLA3B5k6WF8jAzpOepk6lw4gMwLOYM8v+48pe0GV9Tp2IrvTLXZ6LTB2eof2xeYkDwbXxSL6DY4kH7xreJ9jyR3RumgLNswo7OSc3gfH2SS16/RhKqwpwehtkSTOJ+DI/DobjLoRqbc+696O3igbn7Yf05x55zA9ntl8B0/qwfXd8TS8h3ktX+W08Xl3HMvnwXB7pJY2AvvhYGeYyCYpg18auD6TgSqXx1Ldu7Vf+f6bRbc0DobrkEvave+AKwAjNVsc8tyLPE/pZ0zHC3lWsYHelOIAnRyjfHfpezkXrT01uazu/MGBB8w1ZU/tp/Sxix33z06bMg+80YHZOFHAHZgdqzdS1FWaOGiwgi+zwNdb1ASlpNRqZd5Y2s/YYPBUdRN7ThA0JsWblsxyHfvSl1xnmcvsP1LEB47fMsCpp/Lbol33HQENtm+ijTS0WsPpDEGnszcxbqOok3u6tJN8Kyjc4uf3U/drtx0p8vcq/6w5XamtZDuDXBzNcFr3WFoMAYfXlcvKS8wBF8nvwFpw7dvVWXe9xeSlgXWEI+K8w3aGhlaknfzCiFT6A0zWzXHrOu/kjHLhNsnQ05kWLeWWD0e7baSmb9KPxV9uO48dHV4hSrR6bycHJs+l2L1HB8fEolYOCocouGYVbUZtrm9kYt8ZiK/hkvtTwISdYX1aVqMSWuTZsYmpOFg8fQQ=
*/
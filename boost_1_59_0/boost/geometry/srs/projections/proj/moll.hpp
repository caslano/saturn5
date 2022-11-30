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

#ifndef BOOST_GEOMETRY_PROJECTIONS_MOLL_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MOLL_HPP

#include <boost/geometry/util/math.hpp>

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
    namespace detail { namespace moll
    {

            static const int max_iter = 10;
            static const double loop_tol = 1e-7;

            template <typename T>
            struct par_moll
            {
                T    C_x, C_y, C_p;
            };

            template <typename T, typename Parameters>
            struct base_moll_spheroid
            {
                par_moll<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T k, V;
                    int i;

                    k = this->m_proj_parm.C_p * sin(lp_lat);
                    for (i = max_iter; i ; --i) {
                        lp_lat -= V = (lp_lat + sin(lp_lat) - k) /
                            (1. + cos(lp_lat));
                        if (fabs(V) < loop_tol)
                            break;
                    }
                    if (!i)
                        lp_lat = (lp_lat < 0.) ? -half_pi : half_pi;
                    else
                        lp_lat *= 0.5;
                    xy_x = this->m_proj_parm.C_x * lp_lon * cos(lp_lat);
                    xy_y = this->m_proj_parm.C_y * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T pi = detail::pi<T>();

                    lp_lat = aasin(xy_y / this->m_proj_parm.C_y);
                    lp_lon = xy_x / (this->m_proj_parm.C_x * cos(lp_lat));
                    if (fabs(lp_lon) < pi) {
                        lp_lat += lp_lat;
                        lp_lat = aasin((lp_lat + sin(lp_lat)) / this->m_proj_parm.C_p);
                    } else {
                        lp_lon = lp_lat = HUGE_VAL;
                    }
                }

                static inline std::string get_name()
                {
                    return "moll_spheroid";
                }

            };

            template <typename Parameters, typename T>
            inline void setup(Parameters& par, par_moll<T>& proj_parm, T const& p) 
            {
                T r, sp, p2 = p + p;

                par.es = 0;
                sp = sin(p);
                r = sqrt(geometry::math::two_pi<T>() * sp / (p2 + sin(p2)));

                proj_parm.C_x = 2. * r / geometry::math::pi<T>();
                proj_parm.C_y = r / sp;
                proj_parm.C_p = p2 + sin(p2);
            }


            // Mollweide
            template <typename Parameters, typename T>
            inline void setup_moll(Parameters& par, par_moll<T>& proj_parm)
            {
                setup(par, proj_parm, geometry::math::half_pi<T>());
            }

            // Wagner IV
            template <typename Parameters, typename T>
            inline void setup_wag4(Parameters& par, par_moll<T>& proj_parm)
            {
                setup(par, proj_parm, geometry::math::pi<T>()/3.);
            }

            // Wagner V
            template <typename Parameters, typename T>
            inline void setup_wag5(Parameters& par, par_moll<T>& proj_parm)
            {
                par.es = 0;
                proj_parm.C_x = 0.90977;
                proj_parm.C_y = 1.65014;
                proj_parm.C_p = 3.00896;
            }

    }} // namespace detail::moll
    #endif // doxygen

    /*!
        \brief Mollweide projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_moll.gif
    */
    template <typename T, typename Parameters>
    struct moll_spheroid : public detail::moll::base_moll_spheroid<T, Parameters>
    {
        template <typename Params>
        inline moll_spheroid(Params const& , Parameters & par)
        {
            detail::moll::setup_moll(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Wagner IV projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_wag4.gif
    */
    template <typename T, typename Parameters>
    struct wag4_spheroid : public detail::moll::base_moll_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wag4_spheroid(Params const& , Parameters & par)
        {
            detail::moll::setup_wag4(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Wagner V projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_wag5.gif
    */
    template <typename T, typename Parameters>
    struct wag5_spheroid : public detail::moll::base_moll_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wag5_spheroid(Params const& , Parameters & par)
        {
            detail::moll::setup_wag5(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_moll, moll_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wag4, wag4_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wag5, wag5_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(moll_entry, moll_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wag4_entry, wag4_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wag5_entry, wag5_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(moll_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(moll, moll_entry);
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wag4, wag4_entry);
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wag5, wag5_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MOLL_HPP


/* moll.hpp
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
*/
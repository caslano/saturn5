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
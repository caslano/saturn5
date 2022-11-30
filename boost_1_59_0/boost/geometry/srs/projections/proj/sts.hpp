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

#ifndef BOOST_GEOMETRY_PROJECTIONS_STS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_STS_HPP

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
    namespace detail { namespace sts
    {
            template <typename T>
            struct par_sts
            {
                T C_x, C_y, C_p;
                bool tan_mode;
            };

            template <typename T, typename Parameters>
            struct base_sts_spheroid
            {
                par_sts<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T c;

                    xy_x = this->m_proj_parm.C_x * lp_lon * cos(lp_lat);
                    xy_y = this->m_proj_parm.C_y;
                    lp_lat *= this->m_proj_parm.C_p;
                    c = cos(lp_lat);
                    if (this->m_proj_parm.tan_mode) {
                        xy_x *= c * c;
                        xy_y *= tan(lp_lat);
                    } else {
                        xy_x /= c;
                        xy_y *= sin(lp_lat);
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T c;

                    xy_y /= this->m_proj_parm.C_y;
                    c = cos(lp_lat = this->m_proj_parm.tan_mode ? atan(xy_y) : aasin(xy_y));
                    lp_lat /= this->m_proj_parm.C_p;
                    lp_lon = xy_x / (this->m_proj_parm.C_x * cos(lp_lat));
                    if (this->m_proj_parm.tan_mode)
                        lp_lon /= c * c;
                    else
                        lp_lon *= c;
                }

                static inline std::string get_name()
                {
                    return "sts_spheroid";
                }

            };

            template <typename Parameters, typename T>
            inline void setup(Parameters& par, par_sts<T>& proj_parm, T const& p, T const& q, bool mode) 
            {
                par.es = 0.;
                proj_parm.C_x = q / p;
                proj_parm.C_y = p;
                proj_parm.C_p = 1/ q;
                proj_parm.tan_mode = mode;
            }


            // Foucaut
            template <typename Parameters, typename T>
            inline void setup_fouc(Parameters& par, par_sts<T>& proj_parm)
            {
                setup(par, proj_parm, 2., 2., true);
            }

            // Kavraisky V
            template <typename Parameters, typename T>
            inline void setup_kav5(Parameters& par, par_sts<T>& proj_parm)
            {
                setup(par, proj_parm, 1.50488, 1.35439, false);
            }

            // Quartic Authalic
            template <typename Parameters, typename T>
            inline void setup_qua_aut(Parameters& par, par_sts<T>& proj_parm)
            {
                setup(par, proj_parm, 2., 2., false);
            }

            // McBryde-Thomas Flat-Polar Sine (No. 1)
            template <typename Parameters, typename T>
            inline void setup_mbt_s(Parameters& par, par_sts<T>& proj_parm)
            {
                setup(par, proj_parm, 1.48875, 1.36509, false);
            }

    }} // namespace detail::sts
    #endif // doxygen

    /*!
        \brief Kavraisky V projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_kav5.gif
    */
    template <typename T, typename Parameters>
    struct kav5_spheroid : public detail::sts::base_sts_spheroid<T, Parameters>
    {
        template <typename Params>
        inline kav5_spheroid(Params const& , Parameters & par)
        {
            detail::sts::setup_kav5(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Quartic Authalic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_qua_aut.gif
    */
    template <typename T, typename Parameters>
    struct qua_aut_spheroid : public detail::sts::base_sts_spheroid<T, Parameters>
    {
        template <typename Params>
        inline qua_aut_spheroid(Params const& , Parameters & par)
        {
            detail::sts::setup_qua_aut(par, this->m_proj_parm);
        }
    };

    /*!
        \brief McBryde-Thomas Flat-Polar Sine (No. 1) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_mbt_s.gif
    */
    template <typename T, typename Parameters>
    struct mbt_s_spheroid : public detail::sts::base_sts_spheroid<T, Parameters>
    {
        template <typename Params>
        inline mbt_s_spheroid(Params const& , Parameters & par)
        {
            detail::sts::setup_mbt_s(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Foucaut projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_fouc.gif
    */
    template <typename T, typename Parameters>
    struct fouc_spheroid : public detail::sts::base_sts_spheroid<T, Parameters>
    {
        template <typename Params>
        inline fouc_spheroid(Params const& , Parameters & par)
        {
            detail::sts::setup_fouc(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_kav5, kav5_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_qua_aut, qua_aut_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mbt_s, mbt_s_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_fouc, fouc_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(kav5_entry, kav5_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(qua_aut_entry, qua_aut_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mbt_s_entry, mbt_s_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(fouc_entry, fouc_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(sts_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(kav5, kav5_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(qua_aut, qua_aut_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mbt_s, mbt_s_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(fouc, fouc_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_STS_HPP


/* sts.hpp
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
*/
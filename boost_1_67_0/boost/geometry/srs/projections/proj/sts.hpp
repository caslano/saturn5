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
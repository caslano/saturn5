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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GOODE_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GOODE_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/proj/gn_sinu.hpp>
#include <boost/geometry/srs/projections/proj/moll.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace goode
    {

            static const double Y_COR = 0.05280;
            static const double PHI_LIM = .71093078197902358062;

            // TODO: It would be possible to further decrease the size of par_goode
            // because spherical sinu and moll has constant parameters.

            template <typename T, typename Par>
            struct par_goode
            {
                sinu_spheroid<T, Par>    sinu;
                moll_spheroid<T, Par>    moll;
                
                // NOTE: It is ok to share parameters between projections because
                // the only member that is modified in the constructors of
                // spherical sinu and moll projections is es = 0 which is set
                // below in setup_goode() anyway.
                // Moreover in these projections parameters are not used
                // in fwd() nor inv().

                template <typename Params>
                par_goode(Params const& params, Par & par)
                    : sinu(params, par)
                    , moll(params, par)
                {}
            };

            template <typename T, typename Par>
            inline void s_forward(T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y,
                                  Par const& par, par_goode<T, Par> const& proj_par)
            {
                if (fabs(lp_lat) <= PHI_LIM)
                    proj_par.sinu.fwd(par, lp_lon, lp_lat, xy_x, xy_y);
                else {
                    proj_par.moll.fwd(par, lp_lon, lp_lat, xy_x, xy_y);
                    xy_y -= lp_lat >= 0.0 ? Y_COR : -Y_COR;
                }
            }

            template <typename T, typename Par>
            inline void s_inverse(T const& xy_x, T xy_y, T& lp_lon, T& lp_lat,
                                  Par const& par, par_goode<T, Par> const& proj_par)
            {
                if (fabs(xy_y) <= PHI_LIM)
                    proj_par.sinu.inv(par, xy_x, xy_y, lp_lon, lp_lat);
                else {
                    xy_y += xy_y >= 0.0 ? Y_COR : -Y_COR;
                    proj_par.moll.inv(par, xy_x, xy_y, lp_lon, lp_lat);
                }
            }

            // Goode Homolosine
            template <typename Par>
            inline Par& setup_goode(Par& par)
            {
                par.es = 0.;

                // NOTE: The following explicit initialization of sinu projection
                // is not needed because setup_goode() is called before proj_par.sinu
                // is constructed and m_par of parent projection is used.

                //proj_par.sinu.m_par.es = 0.;
                //detail::gn_sinu::setup_sinu(proj_par.sinu.m_par, proj_par.sinu.m_proj_parm);

                return par;
            }

    }} // namespace detail::goode
    #endif // doxygen

    /*!
        \brief Goode Homolosine projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_goode.gif
    */
    template <typename T, typename Parameters>
    struct goode_spheroid
    {
        detail::goode::par_goode<T, Parameters> m_proj_parm;

        template <typename Params>
        inline goode_spheroid(Params const& params, Parameters & par)
            : m_proj_parm(params, detail::goode::setup_goode(par))
        {}

        // FORWARD(s_forward)  spheroid
        // Project coordinates from geographic (lon, lat) to cartesian (x, y)
        inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
        {
            detail::goode::s_forward(lp_lon, lp_lat, xy_x, xy_y, par, this->m_proj_parm);
        }

        // INVERSE(s_inverse)  spheroid
        // Project coordinates from cartesian (x, y) to geographic (lon, lat)
        inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
        {
            detail::goode::s_inverse(xy_x, xy_y, lp_lon, lp_lat, par, this->m_proj_parm);
        }

        static inline std::string get_name()
        {
            return "goode_spheroid";
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_goode, goode_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(goode_entry, goode_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(goode_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(goode, goode_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GOODE_HPP


/* goode.hpp
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
*/
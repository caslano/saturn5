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
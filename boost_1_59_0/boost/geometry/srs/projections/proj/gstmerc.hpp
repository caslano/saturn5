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

#ifndef BOOST_GEOMETRY_PROJECTIONS_GSTMERC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GSTMERC_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_phi2.hpp>
#include <boost/geometry/srs/projections/impl/pj_tsfn.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace gstmerc
    {
            template <typename T>
            struct par_gstmerc
            {
                T lamc;
                T phic;
                T c;
                T n1;
                T n2;
                T XS;
                T YS;
            };

            template <typename T, typename Parameters>
            struct base_gstmerc_spheroid
            {
                par_gstmerc<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T L, Ls, sinLs1, Ls1;

                    L= this->m_proj_parm.n1*lp_lon;
                    Ls= this->m_proj_parm.c+this->m_proj_parm.n1*log(pj_tsfn(-1.0*lp_lat,-1.0*sin(lp_lat), par.e));
                    sinLs1= sin(L)/cosh(Ls);
                    Ls1= log(pj_tsfn(-1.0*asin(sinLs1),0.0,0.0));
                    xy_x= (this->m_proj_parm.XS + this->m_proj_parm.n2*Ls1) * par.ra;
                    xy_y= (this->m_proj_parm.YS + this->m_proj_parm.n2*atan(sinh(Ls)/cos(L))) * par.ra;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T L, LC, sinC;

                    L= atan(sinh((xy_x * par.a - this->m_proj_parm.XS)/this->m_proj_parm.n2)/cos((xy_y * par.a - this->m_proj_parm.YS)/this->m_proj_parm.n2));
                    sinC= sin((xy_y * par.a - this->m_proj_parm.YS)/this->m_proj_parm.n2)/cosh((xy_x * par.a - this->m_proj_parm.XS)/this->m_proj_parm.n2);
                    LC= log(pj_tsfn(-1.0*asin(sinC),0.0,0.0));
                    lp_lon= L/this->m_proj_parm.n1;
                    lp_lat= -1.0*pj_phi2(exp((LC-this->m_proj_parm.c)/this->m_proj_parm.n1), par.e);
                }

                static inline std::string get_name()
                {
                    return "gstmerc_spheroid";
                }

            };

            // Gauss-Schreiber Transverse Mercator (aka Gauss-Laborde Reunion)
            template <typename Parameters, typename T>
            inline void setup_gstmerc(Parameters const& par, par_gstmerc<T>& proj_parm)
            {
                proj_parm.lamc= par.lam0;
                proj_parm.n1= sqrt(T(1)+par.es*math::pow(cos(par.phi0),4)/(T(1)-par.es));
                proj_parm.phic= asin(sin(par.phi0)/proj_parm.n1);
                proj_parm.c= log(pj_tsfn(-1.0*proj_parm.phic,0.0,0.0))
                           - proj_parm.n1*log(pj_tsfn(-1.0*par.phi0,-1.0*sin(par.phi0),par.e));
                proj_parm.n2= par.k0*par.a*sqrt(1.0-par.es)/(1.0-par.es*sin(par.phi0)*sin(par.phi0));
                proj_parm.XS= 0;/* -par.x0 */
                proj_parm.YS= -1.0*proj_parm.n2*proj_parm.phic;/* -par.y0 */
            }

    }} // namespace detail::gstmerc
    #endif // doxygen

    /*!
        \brief Gauss-Schreiber Transverse Mercator (aka Gauss-Laborde Reunion) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Ellipsoid
        \par Projection parameters
         - lat_0: Latitude of origin
         - lon_0: Central meridian
         - k_0: Scale factor
        \par Example
        \image html ex_gstmerc.gif
    */
    template <typename T, typename Parameters>
    struct gstmerc_spheroid : public detail::gstmerc::base_gstmerc_spheroid<T, Parameters>
    {
        template <typename Params>
        inline gstmerc_spheroid(Params const& , Parameters const& par)
        {
            detail::gstmerc::setup_gstmerc(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_gstmerc, gstmerc_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(gstmerc_entry, gstmerc_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(gstmerc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(gstmerc, gstmerc_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GSTMERC_HPP


/* gstmerc.hpp
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
*/
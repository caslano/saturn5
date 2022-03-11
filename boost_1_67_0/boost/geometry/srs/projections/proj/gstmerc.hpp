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
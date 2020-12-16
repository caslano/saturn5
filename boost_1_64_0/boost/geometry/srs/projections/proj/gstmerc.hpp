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
yb9ms615f3Ryrr7Vts4Rv19ldl1xptigzXHFDrM32+h1RjnZJl2rMg0zL42WlDlmylxGGakoh+iUQ81RjDB7R5m9Y5lXFzff5C+tSSbmmwepffw2z57BwmM6mRqVGSl+NJ0CPDxQ/hpA1xzpsv5RMimtZLvWXXEcsebSk/zBgBN8eHk5DLc+2dxlFkck9T3D2U+dcbleyOL0Bj+2VFeciJywNJIX8waEmTzD+dD6y1hUJmFTSjdYiLG1MBY1hVnBGFFlwjsTakhK/mXqfJBNlaE4Y5poSAT5k1k9Z8erpnZw3oIPW4JOLp1hwZKx3Vzr3jMQhxIzrIwIzo/KHP28bGlRd811MllgTD/nJ9SxKBlXMyn9/iZX6GlpUZI2TYd/i8YnVPl2zjmh8uW/fzPIfJ7CfI35Xf3EvvxGw68whS8KCH9p6PDZoe4THWngxGblyx3xcufseUZ7pudVYUuVJ/deoX6g8g+yXtBrAOIpz4w3mJFsdSEs24aT5fef8IWoBn1YMVDXB1ZMnZjT7Ujy17trUGNSeI2ZYRl6crpirv/GW4TLV9Bg9Tjy2Qzyudk6C5ozXO25ny3bw/GddBxgDl8bXH5RvDYaG8bhuJ0ciXBMI0cMHFfDcVyRDfGXDziJ+Dc/L+J/83kR/7vPi/g/ej6s+EPm1xrEvinc/RKVcZD+DafcL9Gsk9ovsZgvgrk0MT0iL5ocJQDZ4utQC1cO1rFwYGJjJ8L2gHNqO7dY+d8RR2pQAhGz2Z5whPdtpTmQGiD0X2SJH8hmR87KJkJa4toex/ZD1OMDNoza07kPZozebgIICx98BkWHO2w8lDyDMgEVbQI/gzLB6zawABUTunwZJJnaCTe9I9adxlhvGGDcF3JFE1Zps/nhFU+cPLxykc5TP3oiLhcDYbFZQP0ACofox0kONOcHUC4MIqXOcoE60MCW2dz4InEu+HMYpksgu6XN+VmLB/CVWxbodEopX7h0YY1oFwKKpMD3vhYie7fz1aTKULitfEmvlHFh5dW68E8QaIZQE9Vhp28OLn6b0Vjx9s1mPfdc+i1/bXaU94tY/rv+w2axgxUb+ez9tlVqei5fP//TDNNzq2ODxKsrJtEtMoVCUv28lIjcfF4qT+wP1eS5llH8VK+/HjvrYfzF7zxUxcCpn5sepUJFwMPpbtlCShC/WF7FQBuGK5zJ3gYAWCpdQ8KRZIyDDo+TL1Yc9RhD24AjaoNi8T4eRt2cSWAy3cdLfNRJJp4fsS3bGpTuCahBJr3mq8FKrUyHRNyOfDFtUKII9INBH9i5YtfbxSEiOXGMQ0SBtGtAI2fJ+SEipzpElM8PETnVIaL8GAOA0+ou3QLqO5rnYQWRFlB69oo+XtbbS70R7NBEfZw4GMLnDuayrCq3cKNZtpl86OkZ81GUGc7XsMAVcyOXWWWuiMNcYfNSNW5fP9ryHl94G+fDprPZLP+NiuQO3IAI3viB3sIWCjgRQLYwaJP76jCkL6I5+VldjPG+rh1LDF+mEv8kMgN+hWZwlLQxCB2uCcrAMey01FxO4K5l+Fu2EE18pZXTKJh7gWi87gB2BcfS/jBmu1APA8LTItoxGj2RVP0U2RWyRFH7IhfzO85VBvfpqR8oO12ce3xaHSjT7d4f42H3Xo5EXt6kFKQskoSVormH0vddiLggtVwdOGPSkkjlXB0iKfWeKZnRSs/0bChjSJ7EAAPLSk6L5D91tYwbtRzU6IdFfish5rIMjEDuu7eoAorQ82/e3HieBQsE88GwAveRFSC555uOsLnfkdnE97Top9dWIacCsiECbZ6MRRWjLpiURSjAcVPPZmxcHYMjcQZE4j38izJ1wSffsplN4Es=
*/
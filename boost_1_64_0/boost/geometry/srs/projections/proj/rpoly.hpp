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

#ifndef BOOST_GEOMETRY_PROJECTIONS_RPOLY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_RPOLY_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace rpoly
    {

            static const double epsilon = 1e-9;

            template <typename T>
            struct par_rpoly
            {
                T    phi1;
                T    fxa;
                T    fxb;
                bool mode; // TODO: Not really needed
            };

            template <typename T, typename Parameters>
            struct base_rpoly_spheroid
            {
                par_rpoly<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T fa;

                    if (this->m_proj_parm.mode)
                        fa = tan(lp_lon * this->m_proj_parm.fxb) * this->m_proj_parm.fxa;
                    else
                        fa = 0.5 * lp_lon;
                    if (fabs(lp_lat) < epsilon) {
                        xy_x = fa + fa;
                        xy_y = - par.phi0;
                    } else {
                        xy_y = 1. / tan(lp_lat);
                        xy_x = sin(fa = 2. * atan(fa * sin(lp_lat))) * xy_y;
                        xy_y = lp_lat - par.phi0 + (1. - cos(fa)) * xy_y;
                    }
                }

                static inline std::string get_name()
                {
                    return "rpoly_spheroid";
                }

            };

            // Rectangular Polyconic
            template <typename Params, typename Parameters, typename T>
            inline void setup_rpoly(Params const& params, Parameters& par, par_rpoly<T>& proj_parm)
            {
                proj_parm.phi1 = fabs(pj_get_param_r<T, srs::spar::lat_ts>(params, "lat_ts", srs::dpar::lat_ts));
                if ((proj_parm.mode = (proj_parm.phi1 > epsilon)))
                {
                    proj_parm.fxb = 0.5 * sin(proj_parm.phi1);
                    proj_parm.fxa = 0.5 / proj_parm.fxb;
                }
                par.es = 0.;
            }

    }} // namespace detail::rpoly
    #endif // doxygen

    /*!
        \brief Rectangular Polyconic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - no inverse
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
        \par Example
        \image html ex_rpoly.gif
    */
    template <typename T, typename Parameters>
    struct rpoly_spheroid : public detail::rpoly::base_rpoly_spheroid<T, Parameters>
    {
        template <typename Params>
        inline rpoly_spheroid(Params const& params, Parameters & par)
        {
            detail::rpoly::setup_rpoly(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_rpoly, rpoly_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(rpoly_entry, rpoly_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(rpoly_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(rpoly, rpoly_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_RPOLY_HPP


/* rpoly.hpp
sren4uAML+j6NCFODfghjzdP5g9dNmll5MV/tY3Sn9d4KH5KbFlLR0OS0ekCRew7Ho2+MTbZwa7SDFmhw9iDYvMvtXEoYNtPpU6ALbJWb4j1ItNvZAR+fq1R6uEo5PCXO9B22lDOvaOyDhrrC0Fcxebpx7+vnKZPLXs4iyCE4LfBre+p2GWmDQkLjvUTEryeDVZH+kTCKH5RD30I1R0HsD1afMiXIJs8kBt3d+qh5sWvSx/EPAwcx4hiyH0yZLbzw+6lxBHmauZ7kE8HNOmY7klCJyd5Fg6i77SEU7oPkZuZOV+rGPTgEkyNpODXObVjdWjXoGJA4D9nQBnKXQABU8XLmin3tu1rRnteXg0bR/U3IhU7q0BItk+ojqgr/x87l79XRVEymXS2bmzs9qDTguMaFMHSooadGVgn69Wyon3f3jaaFPHDP5Ov/ypj0VE01XSGLWT6p392PPkcuFz7bK7D1NqxE3RhNR9aBx09it+3BKwiHinpf1EbMQ8aPYohkFKhkZJP5nv+I3qShpRya6QOhIC+KkskWoOW20+O9K5MpIPkJ/nT5XjPSQ==
*/
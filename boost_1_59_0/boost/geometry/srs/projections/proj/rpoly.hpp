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
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
*/
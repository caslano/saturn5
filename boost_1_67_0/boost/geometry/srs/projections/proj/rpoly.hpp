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
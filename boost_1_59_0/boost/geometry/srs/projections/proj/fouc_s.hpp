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

#ifndef BOOST_GEOMETRY_PROJECTIONS_FOUC_S_HPP
#define BOOST_GEOMETRY_PROJECTIONS_FOUC_S_HPP

#include <boost/geometry/srs/projections/impl/aasincos.hpp>
#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace fouc_s
    {

            static const int max_iter = 10;
            static const double loop_tol = 1e-7;

            template <typename T>
            struct par_fouc_s
            {
                T n, n1;
            };

            template <typename T, typename Parameters>
            struct base_fouc_s_spheroid
            {
                par_fouc_s<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T t;

                    t = cos(lp_lat);
                    xy_x = lp_lon * t / (this->m_proj_parm.n + this->m_proj_parm.n1 * t);
                    xy_y = this->m_proj_parm.n * lp_lat + this->m_proj_parm.n1 * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static T const half_pi = detail::half_pi<T>();

                    T V;
                    int i;

                    if (this->m_proj_parm.n != 0.0) {
                        lp_lat = xy_y;
                        for (i = max_iter; i ; --i) {
                            lp_lat -= V = (this->m_proj_parm.n * lp_lat + this->m_proj_parm.n1 * sin(lp_lat) - xy_y ) /
                                (this->m_proj_parm.n + this->m_proj_parm.n1 * cos(lp_lat));
                            if (fabs(V) < loop_tol)
                                break;
                        }
                        if (!i)
                            lp_lat = xy_y < 0. ? -half_pi : half_pi;
                    } else
                        lp_lat = aasin(xy_y);
                    V = cos(lp_lat);
                    lp_lon = xy_x * (this->m_proj_parm.n + this->m_proj_parm.n1 * V) / V;
                }

                static inline std::string get_name()
                {
                    return "fouc_s_spheroid";
                }

            };

            // Foucaut Sinusoidal
            template <typename Params, typename Parameters, typename T>
            inline void setup_fouc_s(Params const& params, Parameters& par, par_fouc_s<T>& proj_parm)
            {
                proj_parm.n = pj_get_param_f<T, srs::spar::n>(params, "n", srs::dpar::n);
                if ((proj_parm.n < 0.) || (proj_parm.n > 1.))
                    BOOST_THROW_EXCEPTION( projection_exception(error_n_out_of_range) );

                proj_parm.n1 = 1. - proj_parm.n;
                par.es = 0;
            }

    }} // namespace detail::fouc_s
    #endif // doxygen

    /*!
        \brief Foucaut Sinusoidal projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Projection parameters
         - n (real)
        \par Example
        \image html ex_fouc_s.gif
    */
    template <typename T, typename Parameters>
    struct fouc_s_spheroid : public detail::fouc_s::base_fouc_s_spheroid<T, Parameters>
    {
        template <typename Params>
        inline fouc_s_spheroid(Params const& params, Parameters & par)
        {
            detail::fouc_s::setup_fouc_s(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_fouc_s, fouc_s_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(fouc_s_entry, fouc_s_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(fouc_s_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(fouc_s, fouc_s_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_FOUC_S_HPP


/* fouc_s.hpp
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
*/
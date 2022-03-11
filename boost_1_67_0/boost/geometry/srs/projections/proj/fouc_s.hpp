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
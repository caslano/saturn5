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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LAGRNG_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LAGRNG_HPP

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
    namespace detail { namespace lagrng
    {

            static const double tolerance = 1e-10;

            template <typename T>
            struct par_lagrng
            {
                T    a1;
                T    rw;
                T    hrw;
            };

            template <typename T, typename Parameters>
            struct base_lagrng_spheroid
            {
                par_lagrng<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T v, c;

                    if (fabs(fabs(lp_lat) - half_pi) < tolerance) {
                        xy_x = 0;
                        xy_y = lp_lat < 0 ? -2. : 2.;
                    } else {
                        lp_lat = sin(lp_lat);
                        v = this->m_proj_parm.a1 * math::pow((T(1) + lp_lat)/(T(1) - lp_lat), this->m_proj_parm.hrw);
                        if ((c = 0.5 * (v + 1./v) + cos(lp_lon *= this->m_proj_parm.rw)) < tolerance) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        xy_x = 2. * sin(lp_lon) / c;
                        xy_y = (v - 1./v) / c;
                    }
                }

                static inline std::string get_name()
                {
                    return "lagrng_spheroid";
                }

            };

            // Lagrange
            template <typename Params, typename Parameters, typename T>
            inline void setup_lagrng(Params const& params, Parameters& par, par_lagrng<T>& proj_parm)
            {
                T phi1;

                proj_parm.rw = 0.0;
                bool is_w_set = pj_param_f<srs::spar::w>(params, "W", srs::dpar::w, proj_parm.rw);
                
                // Boost.Geometry specific, set default parameters manually
                if (! is_w_set) {
                    bool const use_defaults = ! pj_get_param_b<srs::spar::no_defs>(params, "no_defs", srs::dpar::no_defs);
                    if (use_defaults) {
                        proj_parm.rw = 2;
                    }
                }

                if (proj_parm.rw <= 0)
                    BOOST_THROW_EXCEPTION( projection_exception(error_w_or_m_zero_or_less) );

                proj_parm.rw = 1. / proj_parm.rw;
                proj_parm.hrw = 0.5 * proj_parm.rw;
                phi1 = pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1);
                if (fabs(fabs(phi1 = sin(phi1)) - 1.) < tolerance)
                    BOOST_THROW_EXCEPTION( projection_exception(error_lat_larger_than_90) );

                proj_parm.a1 = math::pow((T(1) - phi1)/(T(1) + phi1), proj_parm.hrw);

                par.es = 0.;
            }

    }} // namespace detail::lagrng
    #endif // doxygen

    /*!
        \brief Lagrange projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Projection parameters
         - W (real)
         - lat_1: Latitude of first standard parallel (degrees)
        \par Example
        \image html ex_lagrng.gif
    */
    template <typename T, typename Parameters>
    struct lagrng_spheroid : public detail::lagrng::base_lagrng_spheroid<T, Parameters>
    {
        template <typename Params>
        inline lagrng_spheroid(Params const& params, Parameters & par)
        {
            detail::lagrng::setup_lagrng(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_lagrng, lagrng_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(lagrng_entry, lagrng_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(lagrng_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(lagrng, lagrng_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LAGRNG_HPP


/* lagrng.hpp
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
*/
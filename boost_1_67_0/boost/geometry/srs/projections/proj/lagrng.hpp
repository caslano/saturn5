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
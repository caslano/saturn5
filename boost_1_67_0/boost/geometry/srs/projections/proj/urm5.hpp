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

#ifndef BOOST_GEOMETRY_PROJECTIONS_URM5_HPP
#define BOOST_GEOMETRY_PROJECTIONS_URM5_HPP

#include <boost/geometry/srs/projections/impl/aasincos.hpp>
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
    namespace detail { namespace urm5
    {
            template <typename T>
            struct par_urm5
            {
                T m, rmn, q3, n;
            };

            template <typename T, typename Parameters>
            struct base_urm5_spheroid
            {
                par_urm5<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const&, T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T t;

                    t = lp_lat = aasin(this->m_proj_parm.n * sin(lp_lat));
                    xy_x = this->m_proj_parm.m * lp_lon * cos(lp_lat);
                    t *= t;
                    xy_y = lp_lat * (1. + t * this->m_proj_parm.q3) * this->m_proj_parm.rmn;
                }

                static inline std::string get_name()
                {
                    return "urm5_spheroid";
                }

            };

            // Urmaev V
            template <typename Params, typename Parameters, typename T>
            inline void setup_urm5(Params const& params, Parameters& par, par_urm5<T>& proj_parm)
            {
                T alpha, t;

                if (pj_param_f<srs::spar::n>(params, "n", srs::dpar::n, proj_parm.n)) {
                    if (proj_parm.n <= 0. || proj_parm.n > 1.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_n_out_of_range) );
                } else {
                    BOOST_THROW_EXCEPTION( projection_exception(error_n_out_of_range) );
                }
                proj_parm.q3 = pj_get_param_f<T, srs::spar::q>(params, "q", srs::dpar::q) / 3.;
                alpha = pj_get_param_r<T, srs::spar::alpha>(params, "alpha", srs::dpar::alpha);
                t = proj_parm.n * sin(alpha);
                proj_parm.m = cos(alpha) / sqrt(1. - t * t);
                proj_parm.rmn = 1. / (proj_parm.m * proj_parm.n);

                par.es = 0.;
            }

    }} // namespace detail::urm5
    #endif // doxygen

    /*!
        \brief Urmaev V projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
         - no inverse
        \par Projection parameters
         - n (real)
         - q (real)
         - alpha: Alpha (degrees)
        \par Example
        \image html ex_urm5.gif
    */
    template <typename T, typename Parameters>
    struct urm5_spheroid : public detail::urm5::base_urm5_spheroid<T, Parameters>
    {
        template <typename Params>
        inline urm5_spheroid(Params const& params, Parameters & par)
        {
            detail::urm5::setup_urm5(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_urm5, urm5_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(urm5_entry, urm5_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(urm5_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(urm5, urm5_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_URM5_HPP


/* urm5.hpp
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
*/
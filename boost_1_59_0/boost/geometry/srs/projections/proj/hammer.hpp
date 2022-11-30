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

#ifndef BOOST_GEOMETRY_PROJECTIONS_HAMMER_HPP
#define BOOST_GEOMETRY_PROJECTIONS_HAMMER_HPP

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
    namespace detail { namespace hammer
    {
            static const double epsilon = 1.0e-10;

            template <typename T>
            struct par_hammer
            {
                T w;
                T m, rm;
            };

            template <typename T, typename Parameters>
            struct base_hammer_spheroid
            {
                par_hammer<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T cosphi, d;

                    d = sqrt(2./(1. + (cosphi = cos(lp_lat)) * cos(lp_lon *= this->m_proj_parm.w)));
                    xy_x = this->m_proj_parm.m * d * cosphi * sin(lp_lon);
                    xy_y = this->m_proj_parm.rm * d * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T z;

                    z = sqrt(1. - 0.25*this->m_proj_parm.w*this->m_proj_parm.w*xy_x*xy_x - 0.25*xy_y*xy_y);
                    if (geometry::math::abs(2.*z*z-1.) < epsilon) {
                        lp_lon = HUGE_VAL;
                        lp_lat = HUGE_VAL;
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_or_lon_exceed_limit) );
                    } else {
                        lp_lon = aatan2(this->m_proj_parm.w * xy_x * z,2. * z * z - 1)/this->m_proj_parm.w;
                        lp_lat = aasin(z * xy_y);
                    }
                }

                static inline std::string get_name()
                {
                    return "hammer_spheroid";
                }

            };

            // Hammer & Eckert-Greifendorff
            template <typename Params, typename Parameters, typename T>
            inline void setup_hammer(Params const& params, Parameters& par, par_hammer<T>& proj_parm)
            {
                T tmp;

                if (pj_param_f<srs::spar::w>(params, "W", srs::dpar::w, tmp)) {
                    if ((proj_parm.w = fabs(tmp)) <= 0.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_w_or_m_zero_or_less) );
                } else
                    proj_parm.w = .5;
                if (pj_param_f<srs::spar::m>(params, "M", srs::dpar::m, tmp)) {
                    if ((proj_parm.m = fabs(tmp)) <= 0.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_w_or_m_zero_or_less) );
                } else
                    proj_parm.m = 1.;

                proj_parm.rm = 1. / proj_parm.m;
                proj_parm.m /= proj_parm.w;

                par.es = 0.;
            }

    }} // namespace detail::hammer
    #endif // doxygen

    /*!
        \brief Hammer & Eckert-Greifendorff projection
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
         - M (real)
        \par Example
        \image html ex_hammer.gif
    */
    template <typename T, typename Parameters>
    struct hammer_spheroid : public detail::hammer::base_hammer_spheroid<T, Parameters>
    {
        template <typename Params>
        inline hammer_spheroid(Params const& params, Parameters & par)
        {
            detail::hammer::setup_hammer(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_hammer, hammer_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(hammer_entry, hammer_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(hammer_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(hammer, hammer_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_HAMMER_HPP


/* hammer.hpp
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
*/
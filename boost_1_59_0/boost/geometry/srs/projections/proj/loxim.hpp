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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LOXIM_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LOXIM_HPP

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
    namespace detail { namespace loxim
    {
            static const double epsilon = 1e-8;

            template <typename T>
            struct par_loxim
            {
                T phi1;
                T cosphi1;
                T tanphi1;
            };

            template <typename T, typename Parameters>
            struct base_loxim_spheroid
            {
                par_loxim<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T half_pi = detail::half_pi<T>();

                    xy_y = lp_lat - this->m_proj_parm.phi1;
                    if (fabs(xy_y) < epsilon)
                        xy_x = lp_lon * this->m_proj_parm.cosphi1;
                    else {
                        xy_x = fourth_pi + 0.5 * lp_lat;
                        if (fabs(xy_x) < epsilon || fabs(fabs(xy_x) - half_pi) < epsilon)
                            xy_x = 0.;
                        else
                            xy_x = lp_lon * xy_y / log( tan(xy_x) / this->m_proj_parm.tanphi1 );
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const&, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();
                    static const T half_pi = detail::half_pi<T>();

                    lp_lat = xy_y + this->m_proj_parm.phi1;
                    if (fabs(xy_y) < epsilon) {
                        lp_lon = xy_x / this->m_proj_parm.cosphi1;
                    } else {
                        lp_lon = fourth_pi + 0.5 * lp_lat;
                        if (fabs(lp_lon) < epsilon || fabs(fabs(lp_lon) - half_pi) < epsilon)
                            lp_lon = 0.;
                        else
                            lp_lon = xy_x * log( tan(lp_lon) / this->m_proj_parm.tanphi1 ) / xy_y ;
                    }
                }

                static inline std::string get_name()
                {
                    return "loxim_spheroid";
                }

            };

            // Loximuthal
            template <typename Params, typename Parameters, typename T>
            inline void setup_loxim(Params const& params, Parameters& par, par_loxim<T>& proj_parm)
            {
                static const T fourth_pi = detail::fourth_pi<T>();

                proj_parm.phi1 = pj_get_param_r<T, srs::spar::lat_1>(params, "lat_1", srs::dpar::lat_1);
                proj_parm.cosphi1 = cos(proj_parm.phi1);
                if (proj_parm.cosphi1 < epsilon)
                    BOOST_THROW_EXCEPTION( projection_exception(error_lat_larger_than_90) );

                proj_parm.tanphi1 = tan(fourth_pi + 0.5 * proj_parm.phi1);

                par.es = 0.;
            }

    }} // namespace detail::loxim
    #endif // doxygen

    /*!
        \brief Loximuthal projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Projection parameters
         - lat_1: Latitude of first standard parallel (degrees)
        \par Example
        \image html ex_loxim.gif
    */
    template <typename T, typename Parameters>
    struct loxim_spheroid : public detail::loxim::base_loxim_spheroid<T, Parameters>
    {
        template <typename Params>
        inline loxim_spheroid(Params const& params, Parameters & par)
        {
            detail::loxim::setup_loxim(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_loxim, loxim_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(loxim_entry, loxim_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(loxim_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(loxim, loxim_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LOXIM_HPP


/* loxim.hpp
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
*/
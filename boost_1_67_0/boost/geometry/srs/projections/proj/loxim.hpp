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
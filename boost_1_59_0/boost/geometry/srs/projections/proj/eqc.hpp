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

#ifndef BOOST_GEOMETRY_PROJECTIONS_EQC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_EQC_HPP

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
    namespace detail { namespace eqc
    {
            template <typename T>
            struct par_eqc
            {
                T rc;
            };

            template <typename T, typename Parameters>
            struct base_eqc_spheroid
            {
                par_eqc<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = this->m_proj_parm.rc * lp_lon;
                    xy_y = lp_lat - par.phi0;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lon = xy_x / this->m_proj_parm.rc;
                    lp_lat = xy_y + par.phi0;
                }

                static inline std::string get_name()
                {
                    return "eqc_spheroid";
                }

            };

            // Equidistant Cylindrical (Plate Caree)
            template <typename Params, typename Parameters, typename T>
            inline void setup_eqc(Params const& params, Parameters& par, par_eqc<T>& proj_parm)
            {
                proj_parm.rc = cos(pj_get_param_r<T, srs::spar::lat_ts>(params, "lat_ts", srs::dpar::lat_ts));
                if (proj_parm.rc <= 0.)
                    BOOST_THROW_EXCEPTION( projection_exception(error_lat_ts_larger_than_90) );
                par.es = 0.;
            }

    }} // namespace detail::eqc
    #endif // doxygen

    /*!
        \brief Equidistant Cylindrical (Plate Caree) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
         - lat_0: Latitude of origin
        \par Example
        \image html ex_eqc.gif
    */
    template <typename T, typename Parameters>
    struct eqc_spheroid : public detail::eqc::base_eqc_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eqc_spheroid(Params const& params, Parameters & par)
        {
            detail::eqc::setup_eqc(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eqc, eqc_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eqc_entry, eqc_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eqc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eqc, eqc_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_EQC_HPP


/* eqc.hpp
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
*/
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
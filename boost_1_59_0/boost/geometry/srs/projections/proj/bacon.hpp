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

#ifndef BOOST_GEOMETRY_PROJECTIONS_BACON_HPP
#define BOOST_GEOMETRY_PROJECTIONS_BACON_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace bacon
    {

            //static const double half_pi_sqr = 2.46740110027233965467;
            static const double epsilon = 1e-10;

            struct par_bacon
            {
                bool bacn;
                bool ortl;
            };

            template <typename T, typename Parameters>
            struct base_bacon_spheroid
            {
                par_bacon m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T half_pi_sqr = detail::half_pi_sqr<T>();

                    T ax, f;

                    xy_y = this->m_proj_parm.bacn ? half_pi * sin(lp_lat) : lp_lat;
                    if ((ax = fabs(lp_lon)) >= epsilon) {
                        if (this->m_proj_parm.ortl && ax >= half_pi)
                            xy_x = sqrt(half_pi_sqr - lp_lat * lp_lat + epsilon) + ax - half_pi;
                        else {
                            f = 0.5 * (half_pi_sqr / ax + ax);
                            xy_x = ax - f + sqrt(f * f - xy_y * xy_y);
                        }
                        if (lp_lon < 0.) xy_x = - xy_x;
                    } else
                        xy_x = 0.;
                }

                static inline std::string get_name()
                {
                    return "bacon_spheroid";
                }

            };

            // Apian Globular I
            template <typename Parameters>
            inline void setup_apian(Parameters& par, par_bacon& proj_parm)
            {
                proj_parm.bacn = proj_parm.ortl = false;
                par.es = 0.;
            }

            // Ortelius Oval
            template <typename Parameters>
            inline void setup_ortel(Parameters& par, par_bacon& proj_parm)
            {
                proj_parm.bacn = false;
                proj_parm.ortl = true;
                par.es = 0.;
            }

            // Bacon Globular
            template <typename Parameters>
            inline void setup_bacon(Parameters& par, par_bacon& proj_parm)
            {
                proj_parm.bacn = true;
                proj_parm.ortl = false;
                par.es = 0.;
            }

    }} // namespace detail::bacon
    #endif // doxygen

    /*!
        \brief Apian Globular I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_apian.gif
    */
    template <typename T, typename Parameters>
    struct apian_spheroid : public detail::bacon::base_bacon_spheroid<T, Parameters>
    {
        template <typename Params>
        inline apian_spheroid(Params const& , Parameters & par)
        {
            detail::bacon::setup_apian(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Ortelius Oval projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_ortel.gif
    */
    template <typename T, typename Parameters>
    struct ortel_spheroid : public detail::bacon::base_bacon_spheroid<T, Parameters>
    {
        template <typename Params>
        inline ortel_spheroid(Params const& , Parameters & par)
        {
            detail::bacon::setup_ortel(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Bacon Globular projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_bacon.gif
    */
    template <typename T, typename Parameters>
    struct bacon_spheroid : public detail::bacon::base_bacon_spheroid<T, Parameters>
    {
        template <typename Params>
        inline bacon_spheroid(Params const& , Parameters & par)
        {
            detail::bacon::setup_bacon(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_apian, apian_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_bacon, bacon_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_ortel, ortel_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(apian_entry, apian_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(ortel_entry, ortel_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(bacon_entry, bacon_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(bacon_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(apian, apian_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(ortel, ortel_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(bacon, bacon_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_BACON_HPP


/* bacon.hpp
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
*/
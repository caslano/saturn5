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
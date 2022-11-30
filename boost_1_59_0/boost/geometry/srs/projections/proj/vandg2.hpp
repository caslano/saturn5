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

#ifndef BOOST_GEOMETRY_PROJECTIONS_VANDG2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_VANDG2_HPP

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
    namespace detail { namespace vandg2
    {

            static const double tolerance = 1e-10;

            struct par_vandg2
            {
                bool    vdg3;
            };

            template <typename T, typename Parameters>
            struct base_vandg2_spheroid
            {
                par_vandg2 m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T pi = detail::pi<T>();
                    static const T two_div_pi = detail::two_div_pi<T>();

                    T x1, at, bt, ct;

                    bt = fabs(two_div_pi * lp_lat);
                    if ((ct = 1. - bt * bt) < 0.)
                        ct = 0.;
                    else
                        ct = sqrt(ct);
                    if (fabs(lp_lon) < tolerance) {
                        xy_x = 0.;
                        xy_y = pi * (lp_lat < 0. ? -bt : bt) / (1. + ct);
                    } else {
                        at = 0.5 * fabs(pi / lp_lon - lp_lon / pi);
                        if (this->m_proj_parm.vdg3) {
                            x1 = bt / (1. + ct);
                            xy_x = pi * (sqrt(at * at + 1. - x1 * x1) - at);
                            xy_y = pi * x1;
                        } else {
                            x1 = (ct * sqrt(1. + at * at) - at * ct * ct) /
                                (1. + at * at * bt * bt);
                            xy_x = pi * x1;
                            xy_y = pi * sqrt(1. - x1 * (x1 + 2. * at) + tolerance);
                        }
                        if ( lp_lon < 0.) xy_x = -xy_x;
                        if ( lp_lat < 0.) xy_y = -xy_y;
                    }
                }

                static inline std::string get_name()
                {
                    return "vandg2_spheroid";
                }

            };

            // van der Grinten II
            inline void setup_vandg2(par_vandg2& proj_parm)
            {
                proj_parm.vdg3 = false;
            }

            // van der Grinten III
            template <typename Parameters>
            inline void setup_vandg3(Parameters& par, par_vandg2& proj_parm)
            {
                proj_parm.vdg3 = true;
                par.es = 0.;
            }

    }} // namespace detail::vandg2
    #endif // doxygen

    /*!
        \brief van der Grinten II projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_vandg2.gif
    */
    template <typename T, typename Parameters>
    struct vandg2_spheroid : public detail::vandg2::base_vandg2_spheroid<T, Parameters>
    {
        template <typename Params>
        inline vandg2_spheroid(Params const& , Parameters const& )
        {
            detail::vandg2::setup_vandg2(this->m_proj_parm);
        }
    };

    /*!
        \brief van der Grinten III projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_vandg3.gif
    */
    template <typename T, typename Parameters>
    struct vandg3_spheroid : public detail::vandg2::base_vandg2_spheroid<T, Parameters>
    {
        template <typename Params>
        inline vandg3_spheroid(Params const& , Parameters & par)
        {
            detail::vandg2::setup_vandg3(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_vandg2, vandg2_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_vandg3, vandg3_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(vandg2_entry, vandg2_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(vandg3_entry, vandg3_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(vandg2_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(vandg2, vandg2_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(vandg3, vandg3_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_VANDG2_HPP


/* vandg2.hpp
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
*/
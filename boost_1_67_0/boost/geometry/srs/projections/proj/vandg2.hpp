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
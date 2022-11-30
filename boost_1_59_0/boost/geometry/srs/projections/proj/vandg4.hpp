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

#ifndef BOOST_GEOMETRY_PROJECTIONS_VANDG4_HPP
#define BOOST_GEOMETRY_PROJECTIONS_VANDG4_HPP

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
    namespace detail { namespace vandg4
    {

            static const double tolerance = 1e-10;

            template <typename T, typename Parameters>
            struct base_vandg4_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T two_div_pi = detail::two_div_pi<T>();

                    T x1, t, bt, ct, ft, bt2, ct2, dt, dt2;

                    if (fabs(lp_lat) < tolerance) {
                        xy_x = lp_lon;
                        xy_y = 0.;
                    } else if (fabs(lp_lon) < tolerance || fabs(fabs(lp_lat) - half_pi) < tolerance) {
                        xy_x = 0.;
                        xy_y = lp_lat;
                    } else {
                        bt = fabs(two_div_pi * lp_lat);
                        bt2 = bt * bt;
                        ct = 0.5 * (bt * (8. - bt * (2. + bt2)) - 5.)
                            / (bt2 * (bt - 1.));
                        ct2 = ct * ct;
                        dt = two_div_pi * lp_lon;
                        dt = dt + 1. / dt;
                        dt = sqrt(dt * dt - 4.);
                        if ((fabs(lp_lon) - half_pi) < 0.) dt = -dt;
                        dt2 = dt * dt;
                        x1 = bt + ct; x1 *= x1;
                        t = bt + 3.*ct;
                        ft = x1 * (bt2 + ct2 * dt2 - 1.) + (1.-bt2) * (
                            bt2 * (t * t + 4. * ct2) +
                            ct2 * (12. * bt * ct + 4. * ct2) );
                        x1 = (dt*(x1 + ct2 - 1.) + 2.*sqrt(ft)) /
                            (4.* x1 + dt2);
                        xy_x = half_pi * x1;
                        xy_y = half_pi * sqrt(1. + dt * fabs(x1) - x1 * x1);
                        if (lp_lon < 0.) xy_x = -xy_x;
                        if (lp_lat < 0.) xy_y = -xy_y;
                    }
                }

                static inline std::string get_name()
                {
                    return "vandg4_spheroid";
                }

            };

            // van der Grinten IV
            template <typename Parameters>
            inline void setup_vandg4(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::vandg4
    #endif // doxygen

    /*!
        \brief van der Grinten IV projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_vandg4.gif
    */
    template <typename T, typename Parameters>
    struct vandg4_spheroid : public detail::vandg4::base_vandg4_spheroid<T, Parameters>
    {
        template <typename Params>
        inline vandg4_spheroid(Params const& , Parameters & par)
        {
            detail::vandg4::setup_vandg4(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_vandg4, vandg4_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(vandg4_entry, vandg4_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(vandg4_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(vandg4, vandg4_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_VANDG4_HPP


/* vandg4.hpp
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
*/
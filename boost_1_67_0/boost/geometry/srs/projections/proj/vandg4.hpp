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
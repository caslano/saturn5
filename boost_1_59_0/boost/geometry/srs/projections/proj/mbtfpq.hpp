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

#ifndef BOOST_GEOMETRY_PROJECTIONS_MBTFPQ_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MBTFPQ_HPP

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
    namespace detail { namespace mbtfpq
    {

            static const int n_iter = 20;
            static const double epsilon = 1e-7;
            static const double one_plus_tol = 1.000001;
            static const double C = 1.70710678118654752440;
            static const double RC = 0.58578643762690495119;
            static const double FYC = 1.87475828462269495505;
            static const double RYC = 0.53340209679417701685;
            static const double FXC = 0.31245971410378249250;
            static const double RXC = 3.20041258076506210122;

            template <typename T, typename Parameters>
            struct base_mbtfpq_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T th1, c;
                    int i;

                    c = C * sin(lp_lat);
                    for (i = n_iter; i; --i) {
                        lp_lat -= th1 = (sin(.5*lp_lat) + sin(lp_lat) - c) /
                            (.5*cos(.5*lp_lat)  + cos(lp_lat));
                        if (fabs(th1) < epsilon) break;
                    }
                    xy_x = FXC * lp_lon * (1.0 + 2. * cos(lp_lat)/cos(0.5 * lp_lat));
                    xy_y = FYC * sin(0.5 * lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T pi = detail::pi<T>();
                    static const T half_pi = detail::half_pi<T>();

                    T t;

                    lp_lat = RYC * xy_y;
                    if (fabs(lp_lat) > 1.) {
                        if (fabs(lp_lat) > one_plus_tol) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else if (lp_lat < 0.) {
                            t = -1.; lp_lat = -pi;
                        } else {
                            t = 1.; lp_lat = pi;
                        }
                    } else
                        lp_lat = 2. * asin(t = lp_lat);
                    lp_lon = RXC * xy_x / (1. + 2. * cos(lp_lat)/cos(0.5 * lp_lat));
                    lp_lat = RC * (t + sin(lp_lat));
                    if (fabs(lp_lat) > 1.)
                        if (fabs(lp_lat) > one_plus_tol) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else
                            lp_lat = lp_lat < 0. ? -half_pi : half_pi;
                    else
                        lp_lat = asin(lp_lat);
                }

                static inline std::string get_name()
                {
                    return "mbtfpq_spheroid";
                }

            };

            // McBryde-Thomas Flat-Polar Quartic
            template <typename Parameters>
            inline void setup_mbtfpq(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::mbtfpq
    #endif // doxygen

    /*!
        \brief McBryde-Thomas Flat-Polar Quartic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_mbtfpq.gif
    */
    template <typename T, typename Parameters>
    struct mbtfpq_spheroid : public detail::mbtfpq::base_mbtfpq_spheroid<T, Parameters>
    {
        template <typename Params>
        inline mbtfpq_spheroid(Params const& , Parameters & par)
        {
            detail::mbtfpq::setup_mbtfpq(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mbtfpq, mbtfpq_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mbtfpq_entry, mbtfpq_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(mbtfpq_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mbtfpq, mbtfpq_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MBTFPQ_HPP


/* mbtfpq.hpp
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
*/
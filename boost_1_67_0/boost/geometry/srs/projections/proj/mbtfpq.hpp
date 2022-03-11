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
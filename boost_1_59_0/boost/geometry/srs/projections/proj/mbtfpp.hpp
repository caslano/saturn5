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

#ifndef BOOST_GEOMETRY_PROJECTIONS_MBTFPP_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MBTFPP_HPP

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
    namespace detail { namespace mbtfpp
    {

            static const double CS_ = .95257934441568037152;
            static const double FXC = .92582009977255146156;
            static const double FYC = 3.40168025708304504493;
            //static const double C23 = .66666666666666666666;
            //static const double C13 = .33333333333333333333;
            static const double one_plus_eps = 1.0000001;

            template <typename T, typename Parameters>
            struct base_mbtfpp_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T C23 = detail::two_thirds<T>();
                    static const T C13 = detail::third<T>();

                    lp_lat = asin(CS_ * sin(lp_lat));
                    xy_x = FXC * lp_lon * (2. * cos(C23 * lp_lat) - 1.);
                    xy_y = FYC * sin(C13 * lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T C23 = detail::two_thirds<T>();

                    lp_lat = xy_y / FYC;
                    if (fabs(lp_lat) >= 1.) {
                        if (fabs(lp_lat) > one_plus_eps) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else {
                            lp_lat = (lp_lat < 0.) ? -half_pi : half_pi;
                        }
                    } else
                        lp_lat = asin(lp_lat);

                    lp_lon = xy_x / ( FXC * (2. * cos(C23 * (lp_lat *= 3.)) - 1.) );
                    if (fabs(lp_lat = sin(lp_lat) / CS_) >= 1.) {
                        if (fabs(lp_lat) > one_plus_eps) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else {
                            lp_lat = (lp_lat < 0.) ? -half_pi : half_pi;
                        }
                    } else
                        lp_lat = asin(lp_lat);
                }

                static inline std::string get_name()
                {
                    return "mbtfpp_spheroid";
                }

            };

            // McBride-Thomas Flat-Polar Parabolic
            template <typename Parameters>
            inline void setup_mbtfpp(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::mbtfpp
    #endif // doxygen

    /*!
        \brief McBride-Thomas Flat-Polar Parabolic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_mbtfpp.gif
    */
    template <typename T, typename Parameters>
    struct mbtfpp_spheroid : public detail::mbtfpp::base_mbtfpp_spheroid<T, Parameters>
    {
        template <typename Params>
        inline mbtfpp_spheroid(Params const& , Parameters & par)
        {
            detail::mbtfpp::setup_mbtfpp(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mbtfpp, mbtfpp_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mbtfpp_entry, mbtfpp_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(mbtfpp_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mbtfpp, mbtfpp_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MBTFPP_HPP


/* mbtfpp.hpp
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
*/
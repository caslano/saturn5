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
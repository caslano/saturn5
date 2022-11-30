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

#ifndef BOOST_GEOMETRY_PROJECTIONS_HATANO_HPP
#define BOOST_GEOMETRY_PROJECTIONS_HATANO_HPP

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
    namespace detail { namespace hatano
    {

            static const int n_iter = 20;
            static const double epsilon = 1e-7;
            static const double one_plus_tol = 1.000001;
            static const double CN_ = 2.67595;
            static const double CS_ = 2.43763;
            static const double RCN = 0.37369906014686373063;
            static const double RCS = 0.41023453108141924738;
            static const double FYCN = 1.75859;
            static const double FYCS = 1.93052;
            static const double RYCN = 0.56863737426006061674;
            static const double RYCS = 0.51799515156538134803;
            static const double FXC = 0.85;
            static const double RXC = 1.17647058823529411764;

            template <typename T, typename Parameters>
            struct base_hatano_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T th1, c;
                    int i;

                    c = sin(lp_lat) * (lp_lat < 0. ? CS_ : CN_);
                    for (i = n_iter; i; --i) {
                        lp_lat -= th1 = (lp_lat + sin(lp_lat) - c) / (1. + cos(lp_lat));
                        if (fabs(th1) < epsilon) break;
                    }
                    xy_x = FXC * lp_lon * cos(lp_lat *= .5);
                    xy_y = sin(lp_lat) * (lp_lat < 0. ? FYCS : FYCN);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static T const half_pi = detail::half_pi<T>();

                    T th;

                    th = xy_y * ( xy_y < 0. ? RYCS : RYCN);
                    if (fabs(th) > 1.) {
                        if (fabs(th) > one_plus_tol) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else {
                            th = th > 0. ? half_pi : - half_pi;
                        }
                    } else {
                        th = asin(th);
                    }

                    lp_lon = RXC * xy_x / cos(th);
                    th += th;
                    lp_lat = (th + sin(th)) * (xy_y < 0. ? RCS : RCN);
                    if (fabs(lp_lat) > 1.) {
                        if (fabs(lp_lat) > one_plus_tol) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else {
                            lp_lat = lp_lat > 0. ? half_pi : - half_pi;
                        }
                    } else {
                        lp_lat = asin(lp_lat);
                    }
                }

                static inline std::string get_name()
                {
                    return "hatano_spheroid";
                }

            };

            // Hatano Asymmetrical Equal Area
            template <typename Parameters>
            inline void setup_hatano(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::hatano
    #endif // doxygen

    /*!
        \brief Hatano Asymmetrical Equal Area projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_hatano.gif
    */
    template <typename T, typename Parameters>
    struct hatano_spheroid : public detail::hatano::base_hatano_spheroid<T, Parameters>
    {
        template <typename Params>
        inline hatano_spheroid(Params const& , Parameters & par)
        {
            detail::hatano::setup_hatano(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_hatano, hatano_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(hatano_entry, hatano_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(hatano_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(hatano, hatano_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_HATANO_HPP


/* hatano.hpp
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
*/
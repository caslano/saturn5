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
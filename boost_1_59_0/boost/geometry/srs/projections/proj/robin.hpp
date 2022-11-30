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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ROBIN_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ROBIN_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/function_overloads.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace robin
    {

            static const double FXC = 0.8487;
            static const double FYC = 1.3523;
            static const double C1 = 11.45915590261646417544;
            static const double RC1 = 0.08726646259971647884;
            static const int n_nodes = 18;
            static const double one_plus_eps = 1.000001;
            static const double epsilon = 1e-8;
            /* Not sure at all of the appropriate number for max_iter... */
            static const int max_iter = 100;

            /*
            note: following terms based upon 5 deg. intervals in degrees.

            Some background on these coefficients is available at:

            http://article.gmane.org/gmane.comp.gis.proj-4.devel/6039
            http://trac.osgeo.org/proj/ticket/113
            */

            template <typename T>
            struct coefs {
                T c0, c1, c2, c3;
            };

            template <typename T>
            inline const coefs<T> * coefs_x()
            {
                static const coefs<T> result[] = {
                    {1.0, 2.2199e-17, -7.15515e-05, 3.1103e-06},
                    {0.9986, -0.000482243, -2.4897e-05, -1.3309e-06},
                    {0.9954, -0.00083103, -4.48605e-05, -9.86701e-07},
                    {0.99, -0.00135364, -5.9661e-05, 3.6777e-06},
                    {0.9822, -0.00167442, -4.49547e-06, -5.72411e-06},
                    {0.973, -0.00214868, -9.03571e-05, 1.8736e-08},
                    {0.96, -0.00305085, -9.00761e-05, 1.64917e-06},
                    {0.9427, -0.00382792, -6.53386e-05, -2.6154e-06},
                    {0.9216, -0.00467746, -0.00010457, 4.81243e-06},
                    {0.8962, -0.00536223, -3.23831e-05, -5.43432e-06},
                    {0.8679, -0.00609363, -0.000113898, 3.32484e-06},
                    {0.835, -0.00698325, -6.40253e-05, 9.34959e-07},
                    {0.7986, -0.00755338, -5.00009e-05, 9.35324e-07},
                    {0.7597, -0.00798324, -3.5971e-05, -2.27626e-06},
                    {0.7186, -0.00851367, -7.01149e-05, -8.6303e-06},
                    {0.6732, -0.00986209, -0.000199569, 1.91974e-05},
                    {0.6213, -0.010418, 8.83923e-05, 6.24051e-06},
                    {0.5722, -0.00906601, 0.000182, 6.24051e-06},
                    {0.5322, -0.00677797, 0.000275608, 6.24051e-06}
                };
                return result;
            }

            template <typename T>
            inline const coefs<T> * coefs_y()
            {
                static const coefs<T> result[] = {
                    {-5.20417e-18, 0.0124, 1.21431e-18, -8.45284e-11},
                    {0.062, 0.0124, -1.26793e-09, 4.22642e-10},
                    {0.124, 0.0124, 5.07171e-09, -1.60604e-09},
                    {0.186, 0.0123999, -1.90189e-08, 6.00152e-09},
                    {0.248, 0.0124002, 7.10039e-08, -2.24e-08},
                    {0.31, 0.0123992, -2.64997e-07, 8.35986e-08},
                    {0.372, 0.0124029, 9.88983e-07, -3.11994e-07},
                    {0.434, 0.0123893, -3.69093e-06, -4.35621e-07},
                    {0.4958, 0.0123198, -1.02252e-05, -3.45523e-07},
                    {0.5571, 0.0121916, -1.54081e-05, -5.82288e-07},
                    {0.6176, 0.0119938, -2.41424e-05, -5.25327e-07},
                    {0.6769, 0.011713, -3.20223e-05, -5.16405e-07},
                    {0.7346, 0.0113541, -3.97684e-05, -6.09052e-07},
                    {0.7903, 0.0109107, -4.89042e-05, -1.04739e-06},
                    {0.8435, 0.0103431, -6.4615e-05, -1.40374e-09},
                    {0.8936, 0.00969686, -6.4636e-05, -8.547e-06},
                    {0.9394, 0.00840947, -0.000192841, -4.2106e-06},
                    {0.9761, 0.00616527, -0.000256, -4.2106e-06},
                    {1.0, 0.00328947, -0.000319159, -4.2106e-06}
                };
                return result;
            }

            template <typename T, typename Parameters>
            struct base_robin_spheroid
            {
                inline T v(coefs<T> const& c, T const& z) const
                { return (c.c0 + z * (c.c1 + z * (c.c2 + z * c.c3))); }
                inline T dv(coefs<T> const& c, T const&  z) const
                { return (c.c1 + z * (c.c2 + c.c2 + z * 3. * c.c3)); }

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    int i;
                    T dphi;

                    i = int_floor((dphi = fabs(lp_lat)) * C1);
                    if (i < 0) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    if (i >= n_nodes) i = n_nodes - 1;
                    dphi = geometry::math::r2d<T>() * (dphi - RC1 * i);
                    xy_x = v(coefs_x<T>()[i], dphi) * FXC * lp_lon;
                    xy_y = v(coefs_y<T>()[i], dphi) * FYC;
                    if (lp_lat < 0.) xy_y = -xy_y;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    const coefs<T> * coefs_x = robin::coefs_x<T>();
                    const coefs<T> * coefs_y = robin::coefs_y<T>();

                    int i;
                    T t, t1;
                    coefs<T> coefs_t;
                    int iters;

                    lp_lon = xy_x / FXC;
                    lp_lat = fabs(xy_y / FYC);
                    if (lp_lat >= 1.) { /* simple pathologic cases */
                        if (lp_lat > one_plus_eps) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        } else {
                            lp_lat = xy_y < 0. ? -half_pi : half_pi;
                            lp_lon /= coefs_x[n_nodes].c0;
                        }
                    } else { /* general problem */
                        /* in Y space, reduce to table interval */
                        i = int_floor(lp_lat * n_nodes);
                        if( i < 0 || i >= n_nodes ) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        for (;;) {
                            if (coefs_y[i].c0 > lp_lat) --i;
                            else if (coefs_y[i+1].c0 <= lp_lat) ++i;
                            else break;
                        }
                        coefs_t = coefs_y[i];
                        /* first guess, linear interp */
                        t = 5. * (lp_lat - coefs_t.c0)/(coefs_y[i+1].c0 - coefs_t.c0);
                        /* make into root */
                        coefs_t.c0 = (T)(coefs_t.c0 - lp_lat);
                        for (iters = max_iter; iters ; --iters) { /* Newton-Raphson */
                            t -= t1 = v(coefs_t,t) / dv(coefs_t,t);
                            if (fabs(t1) < epsilon)
                                break;
                        }
                        if( iters == 0 )
                            BOOST_THROW_EXCEPTION( projection_exception(error_non_convergent) );
                        lp_lat = (5 * i + t) * geometry::math::d2r<T>();
                        if (xy_y < 0.) lp_lat = -lp_lat;
                        lp_lon /= v(coefs_x[i], t);
                    }
                }

                static inline std::string get_name()
                {
                    return "robin_spheroid";
                }

            };

            // Robinson
            template <typename Parameters>
            inline void setup_robin(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::robin
    #endif // doxygen

    /*!
        \brief Robinson projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_robin.gif
    */
    template <typename T, typename Parameters>
    struct robin_spheroid : public detail::robin::base_robin_spheroid<T, Parameters>
    {
        template <typename Params>
        inline robin_spheroid(Params const& , Parameters & par)
        {
            detail::robin::setup_robin(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_robin, robin_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(robin_entry, robin_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(robin_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(robin, robin_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ROBIN_HPP


/* robin.hpp
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
*/
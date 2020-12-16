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

#ifndef BOOST_GEOMETRY_PROJECTIONS_POLY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_POLY_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_mlfn.hpp>
#include <boost/geometry/srs/projections/impl/pj_msfn.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace poly
    {

            static const double tolerance = 1e-10;
            static const double conv_tolerance = 1e-10;
            static const int n_iter = 10;
            static const int i_iter = 20;
            static const double i_tolerance = 1.e-12;

            template <typename T>
            struct par_poly
            {
                T ml0;
                detail::en<T> en;
            };

            template <typename T, typename Parameters>
            struct base_poly_ellipsoid
            {
                par_poly<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T  ms, sp, cp;

                    if (fabs(lp_lat) <= tolerance) {
                        xy_x = lp_lon;
                        xy_y = -this->m_proj_parm.ml0;
                    } else {
                        sp = sin(lp_lat);
                        ms = fabs(cp = cos(lp_lat)) > tolerance ? pj_msfn(sp, cp, par.es) / sp : 0.;
                        xy_x = ms * sin(lp_lon *= sp);
                        xy_y = (pj_mlfn(lp_lat, sp, cp, this->m_proj_parm.en) - this->m_proj_parm.ml0) + ms * (1. - cos(lp_lon));
                    }
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    xy_y += this->m_proj_parm.ml0;
                    if (fabs(xy_y) <= tolerance) {
                        lp_lon = xy_x;
                        lp_lat = 0.;
                    } else {
                        T r, c, sp, cp, s2ph, ml, mlb, mlp, dPhi;
                        int i;

                        r = xy_y * xy_y + xy_x * xy_x;
                        for (lp_lat = xy_y, i = i_iter; i ; --i) {
                            sp = sin(lp_lat);
                            s2ph = sp * ( cp = cos(lp_lat));
                            if (fabs(cp) < i_tolerance) {
                                BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                            }
                            c = sp * (mlp = sqrt(1. - par.es * sp * sp)) / cp;
                            ml = pj_mlfn(lp_lat, sp, cp, this->m_proj_parm.en);
                            mlb = ml * ml + r;
                            mlp = par.one_es / (mlp * mlp * mlp);
                            lp_lat += ( dPhi =
                                ( ml + ml + c * mlb - 2. * xy_y * (c * ml + 1.) ) / (
                                par.es * s2ph * (mlb - 2. * xy_y * ml) / c +
                                2.* (xy_y - ml) * (c * mlp - 1. / s2ph) - mlp - mlp ));
                            if (fabs(dPhi) <= i_tolerance)
                                break;
                        }
                        if (!i) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        c = sin(lp_lat);
                        lp_lon = asin(xy_x * tan(lp_lat) * sqrt(1. - par.es * c * c)) / sin(lp_lat);
                    }
                }

                static inline std::string get_name()
                {
                    return "poly_ellipsoid";
                }

            };

            template <typename T, typename Parameters>
            struct base_poly_spheroid
            {
                par_poly<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T  cot, E;

                    if (fabs(lp_lat) <= tolerance) {
                        xy_x = lp_lon;
                        xy_y = this->m_proj_parm.ml0;
                    } else {
                        cot = 1. / tan(lp_lat);
                        xy_x = sin(E = lp_lon * sin(lp_lat)) * cot;
                        xy_y = lp_lat - par.phi0 + cot * (1. - cos(E));
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T B, dphi, tp;
                    int i;

                    if (fabs(xy_y = par.phi0 + xy_y) <= tolerance) {
                        lp_lon = xy_x;
                        lp_lat = 0.;
                    } else {
                        lp_lat = xy_y;
                        B = xy_x * xy_x + xy_y * xy_y;
                        i = n_iter;
                        do {
                            tp = tan(lp_lat);
                            lp_lat -= (dphi = (xy_y * (lp_lat * tp + 1.) - lp_lat -
                                .5 * ( lp_lat * lp_lat + B) * tp) /
                                ((lp_lat - xy_y) / tp - 1.));
                        } while (fabs(dphi) > conv_tolerance && --i);
                        if (! i) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        lp_lon = asin(xy_x * tan(lp_lat)) / sin(lp_lat);
                    }
                }

                static inline std::string get_name()
                {
                    return "poly_spheroid";
                }

            };

            // Polyconic (American)
            template <typename Parameters, typename T>
            inline void setup_poly(Parameters const& par, par_poly<T>& proj_parm)
            {
                if (par.es != 0.0) {
                    proj_parm.en = pj_enfn<T>(par.es);
                    proj_parm.ml0 = pj_mlfn(par.phi0, sin(par.phi0), cos(par.phi0), proj_parm.en);
                } else {
                    proj_parm.ml0 = -par.phi0;
                }
            }

    }} // namespace detail::poly
    #endif // doxygen

    /*!
        \brief Polyconic (American) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_poly.gif
    */
    template <typename T, typename Parameters>
    struct poly_ellipsoid : public detail::poly::base_poly_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline poly_ellipsoid(Params const& , Parameters const& par)
        {
            detail::poly::setup_poly(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Polyconic (American) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Conic
         - Spheroid
         - Ellipsoid
        \par Example
        \image html ex_poly.gif
    */
    template <typename T, typename Parameters>
    struct poly_spheroid : public detail::poly::base_poly_spheroid<T, Parameters>
    {
        template <typename Params>
        inline poly_spheroid(Params const& , Parameters const& par)
        {
            detail::poly::setup_poly(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(srs::spar::proj_poly, poly_spheroid, poly_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI2(poly_entry, poly_spheroid, poly_ellipsoid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(poly_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(poly, poly_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_POLY_HPP


/* poly.hpp
w+PkleR8azHAKNHeTnuj+uaVUEkrDKtP34mJ4lXlKDrO0jJ1hpZhNeQVwLXWmg+B7/LxGMM8qLPe0hLkUPGOemSZ5K30ztrJ+F95NzBY2eqF1O1aw85+vDVd9CSfL7wfyH1cs+pQTFA9KCJjEq1YomzFEsV86oKhUMGnaTpsuTbsYQ9izxdv4w6VKeKl3fKjLaAxqsgvZIx8M/u5PY2NoFYpJdrrsXK8pkSpX0mf56u9KPWedQLF8LPF/dQbcPg6L1A2aM8N8lzXEf94p3niAt81WMboGbpZNJnnFrEvnN8uVcLshYruj5gGGmntkP0gEnuVn4Uqk+Km8syUa3x/IxRh2rh8SUHOpmSYCyuUF+K3KZ012YzXH8U5XmekPwR/l0Yn1Ri0jm1n0NVW0P1PsJl4kcUO5vcAAI/gknlOGTdq6z3YqO16o0aXe+GlIFkrcJCMohx1xs+VCY0LcVAV656pJDVcnUOgNEq4qYPMwb6nTxd+Zf5311nr+78rzaNbY+fln6cleY8uxvBiY+2JR/JiD7P1wLAlVhuGE6d6VSjbuLUcjVhWMGAXAOSjYoepye+O8ae0rgNrzJec01ldfxY9bCsv9kAJHQEAv69uQyrnQfZ/8yg1SjgSYhM9v7vp2wDO9YTItSBtso8altYG/2S+Be0zxsMqlYr/MMI0wVL+wJ3CNrOZ2whL1jBn5TyLrxOFJtH/+Z1d/+c6b4v8cVWR/xPGohR+2QUwK1qTlLh8EH4i9xWMaBHfql1zN9LsqUizt5r671OAEQ3zWLTGrxe6mSVsOsD6rUsZxdGEYoqO4gJAUUDKkfwmB8Cs9ZC7DsS9BxnaAegtq9lSWv02N9U8goC0wtcV0xLAjeAbmzn0SWIoZoaLKYIv3lb/FtxF9EGgpRTnkjAcZr3fR3htL8aLqPvZn3zZIVycH4uTiRM5MUcm+jARhQyM5yusPtS2VC5hJbJSRXwDXyrsukrFS1A1QUqUoMHoYEgLVG6Rd5cFmL2aIMQ94vvL6dIoH/on3xW4A98gxc8f2Cjyae7+xxdh91fr3f/OtcB16dbmGYa6haAq3BrUHwGKS+Sa40ktbRVA4ndYpFAghGsWJFiGdCIE17ZBNLuxsI71fvXQQ48Hud4i9Pv9jdSCmzLkih/345c40kdBgzXpK4A/35/1/m+54McnL7k5jSzDQ8i41KVDpvJEzCKTtOkARj5zApWb6cALnyDpzSzCePMhsrzY0dznNXcyWw+jVO7Sq72EO8S4Nct7ApKTLDR1FGIO0awKo1JzXuwYRngtIWznNjoBsgSgYxnoDAIqcPuNfZNhpJfkxXI44XhZHVpldkBifTeYBHmxAZyeRemZt81OA7qfjLVN+zV8ww8/r8fP1pBgb0tV3riU9L8e0jatisWdMtVLav9VFLlY/GVdc6MzJQpzrWLD/z3pQ5TyZQ+TYx4TWs+FSGiYeV2VIrSCyZIcT2Wo7+5AqFk61BGTmWdWCTvEhZJn3oQ9+yZ8cum3/bMRdmy8tbwK/svOi0U5y7I72CQlchVWNy2rIo3fqYDvTPwm+lOzJSpmSxRm4r6beCZGA5UTPTwTozgTX7tJzUTB/qJciV9iJViKQ/8VBlVnGcDiifEhZKnxTgN2VuCOW4QMsFR02GgXnytvx66YqXdF96tkh41lqFcIqlyH+vZKKEiyU8mm9o7xcSTyU+iTOsi51kfHFUBafzs5XzmP+6v0dgFLE7hwsnIr6xZ7fjqYot0JNyXYoPd8MC92IWM64nbu+VcmKRx5fnlw8COWzvIwqtx082qthqNQDEchD9lg+ApU7mRLiUIuv+Y77HTe/2IFCoNcljeP2Pf0dcdqB4eov7E=
*/
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
FjHaPrnbH/LTk/Pdd9N1yRvvGNmeDcS18SWGsdFgBJ0P99Hp+wl/bkB8u5NJm6/PfUwjBQwNpjOOAixlzgxGIrwDt4mTFxOI3Wgn++4UAAAs/9OufI7pynJ4dJBR8Jv+z1XTpqbQ6ybjBhJqUVzSfzc/vkE0o1b77ppvotoeDjKTEsXUY5+bvrWaaatS0vrQFmcRePWBROPnIovGxteJ2f7UO+iPVqkXQUJnqliCXMMTeYsYke+PdIZfpugvKtdzqCcoemcK4M83Xw9F2dYZcxCbKSdE1aYInxZQmZrQyglwGou+gZYcKnp8NDuqteV5XiUgOlBawyqt0te/P/Vz8TWqpnWsdPlz255gwTWFaGxLSp2edlvS6NBtSvcH+YMDxuOnM/O+AhVUVEKokLYUl8vzCVmchVPXW55cgZf3e0/bWxcvtFeO6d6lO/mdvJDhuHuz+I61giJ5/iroUQJxhB2tTlhMySBThYyISxzt0IpSspTLIP/MJ25Js2c3Kvk+iSJLn2oF1VCvs7nOPZyEuBsJA5+detATHwjfaP/zJ2Z+PkTxKgvV0j7ZnndvLnr1R56f2JNBSzJL8aI3FSFaqoq6yrJhL8c6CzR/JZWcGb95bPT0vVq46X85vQlWtWuTAnN3bd6V3jc9YUootXDVKV6U/GIGu+2cT/eKL8qNqMEjaKngTgHrW5MBzmQ1PaO3ZXcSI63eOJOmXT6FpnRcLGgu2Lqmhul/SsgnbOY5JFnZfSgC5Eo4ROtNFmo/LllQ8Az422sk9lbErp5WuEoJv2c97DNoafQVCfgdxGcW+qi45nE9ZZ97ecMUv76f2FQ8vtPmWcxjVWiRz4h7mgTR872qdyN9jr/eljJsUIvrYu49rmScNny/658dX/GeQ8qadQZ3Ulz0enekcTKEz6Xq7YZYVjpHDX2i6Iubudl3qZ3FhGIxj0vs/sBdYQVYo/fDNCl508DObcNxTj3/bypFgloHU+Ryqy35P6SOCkb50788mDV6xXSwgxY8jXSTkD87lmRFKoUFQRf6hf2TdCPmmmuPmH80MKqpz9d8Ebc7v14LmdfGsPgGsCWVX78Z72jqeyD2wOoN8xcy9lms171Mq+yG26EZnmFTOX2mgXbWZ8uNJMmpL4c+OxCgtl6KShwKrHJevY+UlXvijUa+mLBEPeGGKx9ZOdNKLjqY/lcXeWQZ1qKlNLv5R1bd51GyKUyLSa9jBD/jXV6S5fPhJePBKVsy+U31+46me5E/zc5rnYeYev0uk/z2iRiZR8aU7lr5GWfCkv0Lk9NkAw/8adq2eJ235RwpNRiGH9tZvCtO/FfVSNJyyYXEKr5TRXBuGo74pM4g0h64LLY5wEpkQlhlyjsE+Tskua6j9L04xO6SxKw2FXJ9+qOQafhrJrLikZEzixBzZsvIq8ODSd+u9SstKZeMF31Mks9//KYYZacJeR6kx8S/0brSrZvh/5DlY++c2NIf8jygyHJKHvu0TG+JvMLmB7diVDH7gHsZT2L5ToLn1bGhikaywEWV9xqHTz7ukU3enE0bg4moiTvzvbIF362XntlB+5mIBLFArk58TjF+Jf2HmoX0SPyZz5YXO2xMKbD37NnSQTbkRpXU7aB44kToaont832Le5TvFOii+z5aG9R8vlefFfc1fmT56BPojp2G0jv4L88HczJ2bqPBhVaUn6xSJzvLkkuqaLgRVnc2nV6lgFBUuqYztc6PS74rC886+Qk4Kz8PmOXXfpi3+bS00q8CTelvLV/64nZ6Lh/zTef9iYzXEpHRTq+kZiQ9w/CfR/LeK07J/QB6zQQzbPX2dBiDFIax9RWZZjT3VPgC5LebhX3Q5Ewooel6Ll83ib6Kwc3xrL8vozUndi5u8dfk9DHS7nF6yOUuv70p2s1XzXKpCZhuu+J6kcFfG8aStluUdC/qS95TYQfOXfGlPKrJVyekMVXSgT70W7DvIdjgJGPlKGQGKoBdlVCc4frsLCNRQ2418GzpMbvbr/AE04gU6S+zj4P0s/A5/z0UIqSJkRqyNMJkzj7/VhrPff5RSPS7L0fpbG1K/IUb9wDFgXlMTeRuu+bLjOPWOr73Uh65WapRjCv7xviPM5RCcmNJn2QEAw/P+gh/W0vYUHo/ICyDMd68mceYKaoJptmIptVadS0wG4fpDqWCY1NsJ6WuqVl4MvaO6vfqfaOfXqzfJzTcRTK90ndo3Tm+bq7tJp5Ul4tuMAsopz3+FH9/e9NHD2Y5iJe8I0klKl+Swki5WM38cnTDbKyPyXp3dUBoPbyeV37yYp5HUn+rrM84jfmg4flAQ2+V/dC9z85/3M6K7rKuXC5afnoeWnJOs1rs9YCPryeA65XqiV3h4rIk/p6LIpsudaSyM4ZClo6XuyTUqCrAR7TPyX5exI5+U63ZYrvfrdXdkKCXc3HHsWv962+z3mbXp6DxWwlDH7dfUmDvTTdGKucPDEY5vux7y/O0tuN58RUtVXMvknVgZTRl2//JvgTPDF3PncduSbnfZfa7t7Uue3Di/OSZmj/i9r43vIyepJhj0P/AeKjp2WDks6pt9Bd8qXLGmUUm9unx/KBymY6EjeuNnzGtIb0h+nbL0Mqd9LW6whSFJAEkuuhDUvqFp2TMyB3tte/Wxq7PK+ft9lR/qUd7KDUsKRvgjlN/M3syfzCg/xn/xKoY3LEeuhpbbVL+ivsiu8nhIzJW0IcuYthh6dvl+mzvg80KPQ9Rg4b1FemDb+5l709H4PihAbmwiyWycvOwkyt82AqLbi16hvPmYY76Ex8HAdC9X/+5DHznKWJ94dnplcx65BGeN8jJlMw5wpEwfVYuzsKZVNMnosepdKxFL7jwLqewrd8Nujn40+N+4Wytm7o/7ve0hY+OwVnVfzcsfwo+6TyZY2R73KVA4pw3Z9r2u97MJ0jtpwECX6tFiBM/ar8BkWs7TaXBDPYobe/EL/YtdO/DMqc/MHH+NhUc8vzwwGPA5Ngui0miQfaAlWFAjnHeb36lfSOBBijGfnhbdk011BUbXPl4tzmKlKj11nFsKIdbq6RNZ3pY1J0chvZnYnkHjbmb3Bs8zaOm7wOGkycUGz89jzzTCH3+/KRxoYJkD0Wr0GViMTSU2v34Rqc/6VN3Yup4Rur4ke7vY96ybT8vwtAYC/mX75MptS44a7/9L6rGgyNY0UJLhKobz0DttoklZ+XvjvBTxiRd1oEusExPwsZOfISWgIgpDXbiSFfTOWA7Gl6nVCOR01XVoIONcwYLpR082lKbf7879rM6/eJFHmfdzfQUUd7D22q7ByefJK8i23jojzv9ZNcDjxuOxywmWL2KVC6S/5L5DGJaPwgbBurZND354jEoSafjuSZ1s/b3FN0WxJNzCH5rOcBb2J++/zzcZ698yA6d50Z/h9VeFKOU3ZzvXxol92TqzK7Rr7hOIfA/Tljj+gjtjmOSb5OzF+ZW5WKda0Kge7axr02HxPdXg1c0gDpfB6XyLE9u/Au7FBJCVtPzahvG6ge8P2GRDYxI0dzQwKvWUcnum9/0E3oUI1LSa/E9BQ8KFIfF5HZlo71aWApdVAWtFgNSh4oNlj6GLD8n4Xxo8djvLybmIJFxM7I2K4V31ov1wWE6Y5KY/GVvJt76jMYsoeoyJSaOjIrRlPbPRp+Wq5WbFghiRFkW1PcWL8Si5sh1BtsQpmEWTZS4ax1o3rXVr2ogw3PmPtFSmuo8NlwgDeEZNsYH/Ym6dWqcdchV3elBfshw+PQJ3vLDld5o8/3DIwcHWDi2afDVPO57BGh54MfWSUfEd36DnPP0XBN1Vfmsyx474u1QztkyP01+idCBjhipUeb+32ZKE2d517rVJtVlibC+KueBuKJK+iCEcIsgy38WvGL3JgJ+F1MyRKtddsROuCRMiK3a1Xv2mYx/TBOXC7z++LjVhXID+19WwVHQ4sbFK3LTUR0TeXb1l7n07nnIoWV7eoz82wp2ggH+XdikKDamLKv+h2lhRIVbo96mLz9fhS7wK2LwAy95dn9zvyrcS83knEen6vUAOZ7y0FuD6Y48vrmYJOrDSXXuGa37Z+1MqJC/ML6XtywEQ6ebaE4zQknzVnNV/u3N9+XWLxUCwbajsxEFHI0OO7Fk5z2RDEIvYeIsbfW0Qk3lS9+2ipKpnMlKnMJtmSNO7he4yri5P1VVeL9qSf+f9O+QJZ2uF1k7hb8NbyWNmt9XRJfFNMsrXzdMXHOHvriXE19bfwPJ//H56cGzTskq1s8KsiJ99gcH6R7C7vnG4nLh/dtLywVF0j/zjAVdW7KqRNa03TMPW+/V9o0WVWy/3fhvwdprJFHntdh+atpqN6Xy4AHmMHr0t7Pfdy6TON0ur3jx2hCzkydl5I8H6ZIeHKw/OeoVk/rxspBDvKXrz+SXNuHe+1xts++GZHeQQFAaZEUkyuIhzcL3wZ8tSptW3fHT66MatlHPjcJE8swYBM+quX7ezrcvz5PxGDZKly2fMsyUbnpa5iHro4eMZH/BHfO2Lkoqp+VQbQld7EA7yEnFGMLkwsdid2qnURN05w7zg/JJAVQCI8NTlnCO8ANqf+/EQy56VSgU2b5MbJej8rznacF6a2O9Q79XynNTGPqB1o1KY290f+sIS3iWGJ8ZnVXA6YS/XL11vVbM6FzzE53L9O6qRfuUGtkbTiLfXSGvo49pr62YEmN9DAThGZFf7HajXkd4aEL1qa/fpTzARVSQOHCddtXUI4c8VOs+USTmI7H24L5fYbGCnj7lo43MSFX9/DWr/Cv25rSTw6X/ZJk8H4/jNQ+kxpvD3vJjvicWvpSLqUJmjY1R73ot3bVyrV00337owP2CZjr3pRs4eK385w2rUInVfzxiDtRmd5Qf7jws2ek8GG/t1oks67/+/Up2frwqSW+RXSD8XK58XeHH8xXerSU79g254LsvJnmCXqzXq7VO8fUzRK9+N7GTYzpi83mBCvZXORi3J4n6kUtw/jRh+Nj/xyxvP9mmn32KFMvhd3oyKndvEdB7eCvK2XCDaIR0c3Z5gA/js4g19dpPuNtTX9t24z77tqDaanYuuGnuqj7/3qdvqw/KGufdXIz+4hY7iR8YnHpeP0oc9W8w7r+0sDCwlJaFJ2wUeTY2iEi/f8B2JgdhISrfTnrR/+y3oD3b5757N18zVaopweA3qRPHmjKnc7/ktPaVv/cBwqJvSYQtKhMpiwp2X0Z9RZHjMmyVGZNkoofdGZ7arIjBtFF+Z67P3RCPvsX22oMTUhMBFZBP0RTY6jjzHZHjTBN7RoINT/0l/0M2lz2p1zwWBalGD907ut/34Thy3MSID+Q+isreUjDHELqo5WTapfhUXx77qHazgn906nz48bmrqTx9rE6yBQIhxN45Jf1CTk7J8JAvHfiLfDdnOyLuQtX9paPvhIdedYEAu5mNJBu+s0ON62iipVPjDXsEieBi6ALOzQR8pczcpVzmSNdkESooy8/d4AhSBuB/L7ikzJ5IucjStEuAHrKdS6g+3YjjAwoB+YhcrHu2T1cjqJyULq9TCfGmgSXuEEWcp6aEuDXxSbUotLaC3ZFlj6S78irb6Wl3S5x3E0jCi4U7uLaeks4951FlISOd+89H7eAIznv+D/U5QVm1EMeQWvaJ8k+IPqISyJpEV3DdD26JOohx78M3gwgGGiXDj05xhuCHTkLtOaF1dutHDxGPIbVTZaB/9jJNdf50NGDciXn3VERQR2XxtohgvAyE6owZoUrilKh2lJodwCfIM9Y5R1MLiKj1gGVZ2i9AI2zweFMV/t/HECWHwMpeU7qN1l6kzatufNpVBQ5EGwk7JBWH89ZAS0/DbhCQbdKrQ04E6BI8MyINbV9tPYbEzQQgiI8gQ+zKlSNQL5vFVNe98WA8aBtC55L6sMZQx3AXuQMRDNhG5m4LwanCYfx3ikMDQCGlPiW0pbUiQBA+jRAOS6dkfYgWYDxSPQ3Dm4swH2pgOwyF9WPBldyE7gM1HJh+KMvGg2PvEbadS3+1NygmWh8RA77ak0WcQZ4e4HnWH3Qoj7XRk5pD9aMg7Mr/dmvGAhGhMRD9NyLIdcjYpS8Vt4ZDhtKdBVpuqErcQ/hFyIUsYm7ljLLyJhkHYPC0Kjdmty2QzBBt/LPxRsRtTtKnl6oS5tD7NI6rGxBXqj3TSUMOfV2BSJje7uw/qeBwmUPSPcVKLtKT2U3QIalw2hnIsOHf7Q/tAvIa/DAVRnNUQEB+p1yo6wUXr0ZAtthF7pPUOHYTpcj9tSYAxNfUhC1bgiB0j7ikZA1+aWYB6zYrZWk3jIUAm8Cq5b+nFlrHyyDgFEBVQTfgdBZihEX8JhuzqvcFr7d+LVnnfeaOEEwUd40//WcVClGTW6r5T10rvOlvMaveVwlG+POdjKoTIY35ToZVibKE+RoSI26t3Hm6lhRzK9Pu6Vp8060l3e+IRSM+14CQW6IV8e1y9OTpDMkI9U6Gk9AYZJkBGMoP7IbDrdx9bxAob5nnkcsqr1F3x9BG82eZ0HUtnnFSQRo1CRAnadsuEtR5n+ey8r755VM6Y5Jqs1uYF3FrgfRbEDqg2QHPooPnuWybp/MLB5zCWzEK4UqpsCHCOwqGhntd+GSEB0MN9Cz0858PY0pnWYMtDTSIIC0YCt0C/QpesWTHv7fzEXHyGaVFa+BAxFuQNCysXAMTIIWrCIDumBGdin2Zv6tqzjMEp7/leIybL2qjRWN8wyxQPyJ3aDE3W/dOavzv1Pjrg4FfM3PE7cN0oFu1oOwEYm7h9d2ATy9mN9jgK68kVAZ8fQf9AsOBHAI1gbT+LPbmO+B3G96AIk3KtgCUUpTyKqpgNvRX2ZbAUUUVnHwaw0OQyH+RXQcnHroLX3G50FoYEwQFjYJks2Mt2gzCouHHjf1/L3P9/3nn0TRpHQdAT1DgG8ePX3+Hz8nDpXBxr6rgIhiXY9zBDcyPPvImygwLu29KhPJ71z61BLf2h3KRrj1+CDKMAZ1kkCI2qUBDAqDseGCFNNCa5oSCE6JIsWy00T51/oTmSoIQYE7KAaG5IQHki4BcnHIkjOEtpsMHcFiub/iOgZwx81xGOfhAY25oKZJVPh08uDrHwhKxh4ogn7egOVL1myEOkJ3lm6xV0h5fUWnQpywixPHcu8sdZVgyLB1iTkgLyC61uEuKJ4M//xsI6gPN0ZpDr74D35fMvpTjcpaQppiKi4CPh7T3HwXX7HwYg51mDXDUnT0BBZsRZR8QIa5fgTQXQa5DDIi7/CCOFlB7oAnIewpsrgdGqN4Bce4FaEmCUjKxgJyZQUZgOzUOJE/7+QlVgNKl+g10Ryz0DEzxdPW0Yu4PjGwYCBx/AsAnG27JawAeBw0zpiDTHdDaCQhEaQYS9SHKRlEgSLrNpmlA+UJjKEeS9pwoUPieaqAbBLF3G6Q8SoBnyd0ndc21BB1CRriUzDzaaTGAJzRu4Q+swNnjUOPixvxfoD+T8NlymYIpXyA9LJAN0Zrgk3IqECAAaghVP1QHVzbTIpKgoORWcIMr5R+MJig9VD+r5svlMska09ZdaB8BOepf0iGHMGrDldC242f/yTiFKYIEaTGQ53+DUNhZ5zJc1jSP6lHYB/HWk6w7qwLKkJM28shZFIgs2MK/XRfk3AdaI5CBCsX/1ROw64UoyFqbC7kHRkjXcGZQqIyGAShJwDJx+tgMHeRJOJBbC7saVMHHqhhGQSCr6LC53Y8iQePzwMudgxlKCX+i7b+s4TbdDiA105xetzY3kPcT8NoZXfFFdlXL3S1S8kbAkDP5XXAxeeD3Hj5NeDRYHLjgOLmL/zX273Jbq7+Gu62ejeIeAAgR4Z9X0ZrOh+qiOSmKX6402sBrqkQgjJnKKYwrEqJN460L6pnIRAI/TozpjIHqjBVWWnxpqqurN/lh0oHp/3R1pbniIWjwXMbRandIrPVj8OtzABkbBL9fR5WUZamt6XKgPtyzowfRXv59obStfRgbYgE/NwJ1Jmrf1DicoOD8eAPXQ8SB2oLl6igxfojVdcGb7HC5GzoChnVmGTJbwG//AR7cOLiZSwJ7bB+PSKdvlhmRnwJod/f234Huc/feuwDdngLF6ZK34/lnQ3ePKRx4diAgYcJw08WkbDHN574wtQWQq7qlap0u6PANPhNmLEMQjnqWYhoFPsC/D6hnPqy/Rh5yfyyv/F+l2PEj5NgS5jOQn2gQDs2pD0H308CCTqDsImZp+CQMXwEcNRK/KUU4dG2+A/WnEHG/J0NUioJa2IqwKvzb0VgVWdL2RhBBBjY449H+juAJXwG2ScDSh5A9xRNOwH2LDQhDwY84QH1A0ydQsaG2h2yStoLs71oAYAoBOBXfkYXuP4LIgKQ4QbIe1AhGvXF0UPIYOii1CNtuok015oVrlACMFJwUG5JgbtNZZ4XxYVfqyir3ZEBrxidKwIUPlG+PC6j1AClqwa7Ipb1wXtQjf09R2h5gPTxYPKj35ssxaE8Wkv0JgtCt28O2D4LCzVSi6RPP4NGN3LKkjttmVdKk+HeAHgJLC3rD8Q+dxWw9MNaAYbGSTdjH37tapexsojbfcntDuGJBrl92iYJ1HIdRIPMtcgSXr7J2D83CbhTb3U7CpdCddEjbrhmu7wa68a/0jrmZUwJsU9JZdOcXhLAP/5x7JfSQfJqSSbuMLi0y8hSTCVkLy6R0Dd2FqIMqW0kR+VBQr6m2IqJu8kV9zH/wx5Tk0IU/WQ1nsVho2FWXhAo4Eny22gfUOrRpH2qYoE1uDWcFHv3L8IcXxEoscTQqfFLMVC9uce8R24vOKZAgjOhBskqIulydqoATAdNJnF7Z+c25DH6ddewKh4+lVrOc5QHVu3JcPSS4mKCqyVYeAjbbIG9RsnIIMmP0xX/BZ/7XvcYg/2HUse4bGm+jq4OeS2jtwK98FJZxliAKN3wcDrhJAZbIPig2CdaycqD3ry+KJe4tBNnuL6RQCpatXmfuOE/5i3MA0EJwnFFEMYTw1ghL3Gm5tRm7elKBhxDUQczUW5Ca1ZPY8uB95G8XrFi5CQaXdITZIXq46+z9FYRCXZOmAPbvdDHb7IQ9jhMjfJI2fnaz3eUSmIi+gpJdAFsFZn6iZMcAdQa7B9gB3aFNZXuMBZSrsyzRaKF/HOLR7nJSqPtlrgLXfroaAeTvScMPDpQoA284QKM=
*/
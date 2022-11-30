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

#ifndef BOOST_GEOMETRY_PROJECTIONS_VANDG_HPP
#define BOOST_GEOMETRY_PROJECTIONS_VANDG_HPP

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
    namespace detail { namespace vandg
    {

            static const double tolerance = 1.e-10;

            template <typename T>
            inline T C2_27() { return .07407407407407407407407407407407; }
            template <typename T>
            inline T PI4_3() { return boost::math::constants::four_thirds_pi<T>(); }
            template <typename T>
            inline T TPISQ() { return 19.739208802178717237668981999752; }
            template <typename T>
            inline T HPISQ() { return 4.9348022005446793094172454999381; }

            template <typename T, typename Parameters>
            struct base_vandg_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T pi = detail::pi<T>();

                    T  al, al2, g, g2, p2;

                    p2 = fabs(lp_lat / half_pi);
                    if ((p2 - tolerance) > 1.) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    if (p2 > 1.)
                        p2 = 1.;
                    if (fabs(lp_lat) <= tolerance) {
                        xy_x = lp_lon;
                        xy_y = 0.;
                    } else if (fabs(lp_lon) <= tolerance || fabs(p2 - 1.) < tolerance) {
                        xy_x = 0.;
                        xy_y = pi * tan(.5 * asin(p2));
                        if (lp_lat < 0.) xy_y = -xy_y;
                    } else {
                        al = .5 * fabs(pi / lp_lon - lp_lon / pi);
                        al2 = al * al;
                        g = sqrt(1. - p2 * p2);
                        g = g / (p2 + g - 1.);
                        g2 = g * g;
                        p2 = g * (2. / p2 - 1.);
                        p2 = p2 * p2;
                        xy_x = g - p2; g = p2 + al2;
                        xy_x = pi * (al * xy_x + sqrt(al2 * xy_x * xy_x - g * (g2 - p2))) / g;
                        if (lp_lon < 0.) xy_x = -xy_x;
                        xy_y = fabs(xy_x / pi);
                        xy_y = 1. - xy_y * (xy_y + 2. * al);
                        if (xy_y < -tolerance) {
                            BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                        }
                        if (xy_y < 0.)
                            xy_y = 0.;
                        else
                            xy_y = sqrt(xy_y) * (lp_lat < 0. ? -pi : pi);
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T pi = detail::pi<T>();
                    static const T pi_sqr = detail::pi_sqr<T>();
                    static const T third = detail::third<T>();
                    static const T two_pi = detail::two_pi<T>();

                    static const T C2_27 = vandg::C2_27<T>();
                    static const T PI4_3 = vandg::PI4_3<T>();                    
                    static const T TPISQ = vandg::TPISQ<T>();
                    static const T HPISQ = vandg::HPISQ<T>();
                    
                    T t, c0, c1, c2, c3, al, r2, r, m, d, ay, x2, y2;

                    x2 = xy_x * xy_x;
                    if ((ay = fabs(xy_y)) < tolerance) {
                        lp_lat = 0.;
                        t = x2 * x2 + TPISQ * (x2 + HPISQ);
                        lp_lon = fabs(xy_x) <= tolerance ? 0. :
                           .5 * (x2 - pi_sqr + sqrt(t)) / xy_x;
                            return;
                    }
                    y2 = xy_y * xy_y;
                    r = x2 + y2;    r2 = r * r;
                    c1 = - pi * ay * (r + pi_sqr);
                    c3 = r2 + two_pi * (ay * r + pi * (y2 + pi * (ay + half_pi)));
                    c2 = c1 + pi_sqr * (r - 3. *  y2);
                    c0 = pi * ay;
                    c2 /= c3;
                    al = c1 / c3 - third * c2 * c2;
                    m = 2. * sqrt(-third * al);
                    d = C2_27 * c2 * c2 * c2 + (c0 * c0 - third * c2 * c1) / c3;
                    if (((t = fabs(d = 3. * d / (al * m))) - tolerance) <= 1.) {
                        d = t > 1. ? (d > 0. ? 0. : pi) : acos(d);
                        lp_lat = pi * (m * cos(d * third + PI4_3) - third * c2);
                        if (xy_y < 0.) lp_lat = -lp_lat;
                        t = r2 + TPISQ * (x2 - y2 + HPISQ);
                        lp_lon = fabs(xy_x) <= tolerance ? 0. :
                           .5 * (r - pi_sqr + (t <= 0. ? 0. : sqrt(t))) / xy_x;
                    } else {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                }

                static inline std::string get_name()
                {
                    return "vandg_spheroid";
                }

            };

            // van der Grinten (I)
            template <typename Parameters>
            inline void setup_vandg(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::vandg
    #endif // doxygen

    /*!
        \brief van der Grinten (I) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
        \par Example
        \image html ex_vandg.gif
    */
    template <typename T, typename Parameters>
    struct vandg_spheroid : public detail::vandg::base_vandg_spheroid<T, Parameters>
    {
        template <typename Params>
        inline vandg_spheroid(Params const& , Parameters & par)
        {
            detail::vandg::setup_vandg(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_vandg, vandg_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(vandg_entry, vandg_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(vandg_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(vandg, vandg_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_VANDG_HPP


/* vandg.hpp
0DzcUNsK+i+msM8VraBlVXwa5c/uy9zv6GHdU/MXyDgx4gKWNToCK3xxFnrbf0JfczmU0NR9ROexIjZVp8DNbxpXTis7v+c+pIEOVZfApPP4VyO68Ybhis+fIZ79YaIeY4TfGUs0tsxcRt93JL7gu+kM95ZDSkttZldCFpMyxarzYIUoYAdl0etMTUf5w4ioZCbhCVc8BH2bun5FJAse8KW9vJ5RoII8OONAepVmcZYzZf4nHaMD3f1QzxZI+v94ub8Il9yZnIEvnLr9v9U9h4c78l+qcuqraNK2hT87wOEA2Y7NdYfzvT3kloK9Yq8z7fslH4Q8IvGlrkbMHy/Caguqmjbn+sD4OWZmEL3lI+n5LX7E5GrLIdlGvpaerTVSH10fqMMkdmhPxA7gRyDV6GizXlIlu5/y2CFoVFsJ68CUZUI9VNQmiNhEmiGjAFcsPoLVrK+cyWH37vd39S8OY5JC9cFt/Lx8lVde60NvvhQbP8RTnlg8ykZKr4FDKBaJpD5j2+yVzoOPv2sSKPe1SMI4XY3mUNdvJENctgs9fufqO/l4PhmLKmUwO17HGvf5O4oc3sustVIGoUbKnXzKOfb0AZwmfGCnoMz/Q4/oaclJWbG2fAR/YlKaPn8xKOvdUAdIOnfi2iKUb4N++oK9KxA+f6JT4fP7kkppMvYJh2Xjyj5Wu1FxtIELfBRS78acSl0KE6s8tCqT4pXHe41jT8W8Ou6hnZ1L5sTbA9gsAl/9VWuhsc5I6IPFhVX2/0cAadw/rK2DFDrfnu3W7QgFt/tPfETM8rgdju+tJP23uRWROwtPvmXpzRh366G5bCqe1f6Y/SBQmma0qOR17iI1Y9PiGRmeUmmL9Ohyhw++6HcDp62LAahSUNpAlHp0ZOM+p9j/WcxqeG6AAM6SSR3+8KS2TldQ1vKtqQNODs5XPY+byxTYHpb/80orw3zA/ToqVydNNWhCMOzuzsqZ/a1oFIGarVIWNku8psDoDf9hII0BPXvDd26sV8gaTHv7x7hbvqsB9erjlM3AhGpsyKpm15vL5j0YKgexyTt0O309nan/Z7pHV04AfOS9UJB+88hijb/KffDGgSp30Mpu/3RFyjFW7RDTuQzR2OaA9RrkI55/OhfxMtvUuqHNubFdW2H1suFxy1Hn+kaC/Ernm9T9YIBLK4rxUOEOjqKXX6PrVOg9RYrHybof2vcIcnS7hplrsAk/6U48U/8/wCOLHhXGNoeKcPwb5VDPoXuyp96hzh/vd5UaNqxIbrCJ3pNOmXxtLMVIZVoFrLrv/uxaONX/cm2yl3tS22R6hCCyeNCuofWHXOo3jwMO/2vrOrjOevd1yncsBs13ss7GMH2cyN4fa/HfjOoJWwIv1vIYcl0H1zcwXkF//yh2YcxlWutvq8x2HIviOFEd566lLTAzJqYm61y/skw5i1y2Z8OQnaKYuJDUIJ9NbyGGnCAoaTQfmpxtlT8TSA5o9LJjC9VSEDKP+yYmbnbhryUXxSuXxDTBrrAXG+QvOPxPq1u62I8LFOYlNvTXVnG5zeRoZAgVecl/i1/5ImEfVp3LDo4RfEOQhVYSLryOj2iffrq4Vf8jxI67sbOGQiNd6igDP3kEjEXOlFvuA4/H13xie/qyEqMpEITNPXFIDru6r0CbBJXAR0ZdJkTuWrUVyBEZT9OgsEB8BLUt+DK00Okfx7Iou4jgldKcoiG4ydDr7D+tmt8MaTb75I1eNnw2WIZIz9cGIkfxUfUoCqGugHGaDIuCEg4MiCg3+xx40HrGoil0+CPXBnF4bLLelrlB0U5KJ0DYel1TwjvuCM7AmkEEUPKIJApsjlS3paB/4iwtIHQdT2tZAWq1TUHUlrWeyxfsu95jkxj/FAdnB2DUTzzIkcAOo3lCGhBfdBJYX2HL1izpa3BJMRMHu5nRZlmAobaVA5edUHE4a3vVMDAGYXjccEz/DbdHS8YM7dLRKQOmbmbAI6gxHeJlBMun7MCI76r+8OPa7EqX8YM72PtPfxc41qlm7L65Q3jF47vFVJ0GbwXMbjtF/pixDuGxC6HTFkFT5xVFg7jJ2+wKv+Qt+uQxNnUy4P5QDdH/6HNb8BP/4GM3/fw6bn3m3oSRHFRaoXSwjHoPRlciRBC6ju8lQqC7o8zYIvAzmXwZgvd26cMJyT9/8Yt96um76kGr9YLLRuirffMveOKeoTz1/GidwoojehrvltsJsT9mcu6iHNlb00YevxBhhNS1JSnphak8JvJj4n4xp95NqJ58PSx/u+Ofh/fz8Z/S7OO67j7vbL1jvpV/+rb9Sj5xW41f5nMfvP5XpTD7rcH8uwqQwf6f9y7D70K9/LUJ5Z5X6tPSAua61qK1F0VYX5d108NCKK7Jops2A9y0lo+kgAdMhvPg+y2jhRhxjKvLOpX9vskR0JE86ecdjm5Egxu8fYvK1uv99bEteCM91HGiK2qp8VNF4alD/ZQgkqI3ZpqeiMkaahWMnLEeTShHk97OeTshMUR0N0vJ/ngKaVfyWhzz7ulQ+OddeuOQV8AN070JdK3oqtnVg5QxhMcOPqDHf1Q9laXBZRgPLldWz3Sj23bztWvdbKgLn0RL8jOXQu7RHRbwuQvLUV3lrXNsG3AsuhiboA2+qApentwRPtvdkePzeqDNGSDobsrUfZd2HHvx7IyWWLEe2YKOQvC2FuTcSH4GrqD2zCr84qG4aMprVARYU0bq7LZTiE4etbCHIcd7KT+hbiBT80UN39sGL1t7Ix7ZzNxZi9idP1y2UMuAmf1cqptsV/7IVXG26bwDmVUjrXi9kJZbRAuVl4P0lfhpaP8RR+tJWuKrc+dEJdIohUHjtG2WbFLmOhU+KWJs9qhWOOuADx8CIZ2bveKdDh/Mg5OFXJNt53fNPafskRLSZSsyhBfvv++A5oneXUO6l9MVh8sNsU110jV1OZoq9pYkozw60uDN4dOlVVGttx/c1Qq1UuS/+cY1WAC/3fHxD4VvWu7f2UixIIbsdXXkd/BgZ0ic1KvADX8e5Djd5gxPNMymoc3LpaW052npkudY5LI0CAhRtARci4gP7Jkm7ZfLTV4iaxJyLVubS0m0umvjoemZRhkciL0o+b62n5fWgHCLjkFpJi8OqML4A5N+LUrItoEjK3FAKuuG1E9mKOAe6HwQpz9lzZbO0eI0/SuEH4wNeaJsJ0lCF9yEDm76cCkfXD2MQRXMhcuqzhtjnxlE2/RULOW6wifZ35Dx9NWUpIYr9sI+aF2MZc7E4MFO02jvko3h7RwlMDU21YXWRjfHyHnqjqZabG6fevHYAM+iFJkgDl2fwi29MDbyjVs1E83Tci6zyFw/phNIwlKWtVEPr9S02p0ARuMT0e+5Y5mJMB8p5k7xu6FA+aGhJZQoZmow55gIKVRUDT6Qa+6c06CA6U99TVqXgFb9ArZ8nc1oo1IBX5+Plo6i1X1GHnkLFJ0fFgo9V8nLeXORtZSLcsb03pT4eklZ+zempQObjwVpR8hE5CIBWiHI8aAr3dsLotvg0QrHrCJubfIA60lkGh7pQnfN5GwVwkAhvlJq2zQ/H/h6IRJ2aPBTkrH9Eiiil11WUu3KqdMvbe5boNdG0gZEAty8f4I49VxP2VvbIWd68ZDcE1+ghKpH8Trzg+itNrgBkmP8Lc8zu/ffGwLPCtbtkopppqWUSBUslJ5WBUXWfQemalDfJ8i/V8oSJV7nurty4jecOztgseLhMOoOOSnjcyiFRam4fzKySjbb+bY0vaFCS71IcJoKabewdO45LrFm9S/F94Fx25TUxPagvsuQoMCXRVsYas+AvWG3fH4dEDKsDVF0O6T5n+nfBjfLOXOZM52SAcoYA5RLc44VsindYQ9RBK49bspWLL3B0sYLqjOVWW9d0VmhiK3Cr8uBKNZjA6yjHwFkVvZiWxVyvsALZFFM5E9Hdgl0/5CzxBIwlZiji6ESmsPGHpGZxNDCNlWgq9wNSWodDYYbKDlTUl8ZcDiUmgyX7JZw5GM8sQCZQUb+DYvdIa4U4XOz0LYOkeelxH6o/fPTzGm1fVns0FLbLJ1dPE/j/E+2t6qlEm0zP+Bf2VszVMNEwu5GNpZQWmWPBqSO+coTRk7Kt7T7GJRNriKWBIKf5lvh4NrShh8iIZ3Vmfm4VdtAazqqclUVWs01hO01rGJC/E/aq70MLR0X/NS6qDvKxn8wI6rJoGrBh6DKE8GF6zIE/YMqIZirKr+qLTlJAEKq7HeLoZdYdMRxNNvU2oIamFpyyhYmQnyHtNDcluO2V0H/4FS0TXniBY5+zu+Qqf47vdT8opeb21on0IGqS8pBrb2RFsbLoL9GrCK+BG9eMJLVZmgNUhkGO7MF5xlwiiVookOdNSjO/XpZbBTqJZIK1WC+irvusnkSoZoEdvE1NtNZoxkwm/SgPGS4NK3Th4/r6UqqHB+q0ayu9pdG2cezjsBMmCfeYghCbf0PW+REBRuaKspgiBt3pGTqKKQ9EwXHuvyHgywidCQdrRU2TH+LoBumiIxWIHiW/HnnKMahX6n0n9yv2n8/7aadQ4iZ1VSVdnwsyWC+GJMOGntvQJ7pGBNcNfsc2kqUNoixgQf8V987JB8/uB+9yB81axAWiGNU/t9Z/P8hzdb3Dx+B0LZzG35QPPfLeFMU+5GilBYUBdvskY3PRyveeMD0K2UYVWCH3Bp/arcNPJ+ZcspSvIV++bR/dNv26nK/HMt7P313V/yKbbrpPzu9fL54ze7mdc+RY6I6DHhauCauRF9WNREOmBUXaHWvqdVvMJ/o1o7OjRgM6ihuNlAOnOaFVimJi+3OpoL8ZrX+fOL/vr5W6vNL/7bfSH/WBU2OZx9aBJz69b5wHXgWxeXmf8aOnKtlYepe7G+bx7L9OKKPvsE9rnzIltdEpLgXaeGHjonpt+2lFTy+qU6DHL9d8upYw5en41DubnuvffKDhe2+dH+nPVMtP/tm/gZep6O+eRzOHX4mH9j87otBhA39w7tutW/Pt8FQJZ0OT0LaRoXEhkjj5oHke19NNhok/ueXbNGu62yXBp6XjMTceKhNVSUBdp8VVnnXdd5b4P+LKe6p16P1WcK5EzlEnsGz4/qbRhITUpcNxn6KlFsPOLEAOLFs9tVC3JhaBiaqWVSw1hu2y+991hMDoviv7CqqsEzxo/ch0xZblAD9H9ch3xZo/utokMPkxGKsm9EmG0BJm2nxdZgLX/gBLm/3BpXeVX9X5aRM+E7q1jDtQ6u89rbTtC8KTk2No+NGEVoH+wqDJf4h9VassqZddcwkVU/zJEbV5zPMzuXw4KpT3HVS7FUpjQud90WKjZPVAJpaw4iW2eRjDoqrZ6lbHsUssZqo/QS2Knby9OyDHTZtL7aerTPxEpeTvChTDqn4Q8y2aZX6V/3YESOVnbHKuiiNAwEhvQIwKkaSmCf6qJOwzSr7XWniQJxNJKzCNZlmEtaT23EpmV5hWR4ijBwH73TsfxNXHhF4vM2JtTHdV5vy14mwvpwis7HCXEcQe6XIRDuFYPiuiOS0M8/1By7SnF3/TFnq4scscnpcpPQSNAzNRcPMHHwcqK9sbnRZbzkuGii7UxrE6SrRB9Xf1IfxOCohhqL5NqWqzlbZFtK+mkLXsiR4HdX9eYqOVU01tWgE0lu1GLi5rU+6aEJl4zKziF9Z9Y0hwcA5LUlM+nudjUmsDtBpr1Lkv87eSMsoZDi1i8YEi/sknA4gqf01GuGdcypW8Lc/p8yx+xoPGU44yLd1tQtn+EyGRY6YxyREV4zn1aSsZE/UmB6wnyxzenfRvHgBZxPK4mdTpCi+E/mfH1P6OASwx8kcLZf6C3k3ZceN0MINbTPgk5i3ZXNmaol7h8t/3MfMhXY1+rPJ1L3ytQzm7DhZvewN3Dbe+zXM2bj9rvaeoaOPV5/0kWrbRuBNN/xeICYRVcl1jr5us7zrsVKELgGifAhX6IHXLASDwhVGvzs/T20RhNNk3+z6H6UzAww9HmmGzR53taOtzOs3V5jpVPPgCP7Jdknxva849PrpXmERe5mug5q5SGezwiXzm4T4AG2ujQocETMEPoX64xt2boMSIYSkCvQhP5ooMbZmzrIxhoarwp819WliFmlsd1tzUD+jDJmXNkla9unWam06MflFQoIB+G981Wn5a51tMSmAQtwfrSd0qZUIuIrAfE1YlpNfqYZGbezhuPM19MaqKFXmsQa9LDUj98ubYg2lvX4Z3lSODXMw1kx7fOHxFRsq215lb/9n3o5Vtfsiwtm1jFYv5RPaov1fBYGf6pjfG6aUSCgrXmbl6+G8sFFvPHBeuC5VDIlzv8+9Bhd+oMbCclOrUCjGOX5lMKm94OWufkPmf2fNhusd5GtB8CeOi3Gi6SDW8KaPfLrO+EatoGU7QE+CJ/vyl5BMy1QZNBe0OucUBKEMLHNCd7DJ4c0t70RQzm1EoSNSP9z4Ls7WHNd6ltbUcq7L7Lnp3mlq9HXL3qqfvQG/rU30ZRfbL9p2/5RpE9Rn4uJeIhIA1WHsJ/uX+eGdW+doQr7U+sASK2BrSJ8k7rphsUcJzXL2tTBvKKmthvOO86WSQ++S3o5f2x3sD8vaaZrcQAds761fFpd3u/J1U4FGRbkbbXKxv9Q49Nfcs0lCPKGC2VBz7+55SBqincNMxwnOvQvEFbbowkhyVet1FlsCdVOIM7ZVgVhUkVv3bx1mqu+g1aMLFf7js2g7E93k6+6venaZEVY9nMGDNuTUN0H3gcvfFw1UVnjzssSOe0CNbgz08ocuh/WuTzHTK6USGeR4USooWVT0cRoZBG0hbkkZuOt+w8wKm5ganiF1fU6ovKZmCFFUuF9l0tDIWO/q/8AhtrXDRwhxp//Vv4302GYsOtHY+IoSgPIaFtRyneu2DFkQjVNyKECdlZjxCV2aKW7DjClbxI25LpU7onJpF8mWU3vRh9TBgT76VcNA6W1nZqgNx8wlCJJXVpw8oTyqusv/QNQK/2Erj+0h5mxJQPOsbMxE8DiD+yAZnqzPLzDe3qjWLFhrrekxhnTAIKXVzdij/lQfdEApfnDX65V3ZxFA5jIujgPlcjkyWblCWpl+nvq8I5oJTlfFlvcCltgTC4SCX538xF/0bshzlWX3kiXCQju8n1J9G2w7hr//3Ir5/V52NxA0uqDtvPf7vT/Xz3ZJBqUn1OtUmvX6hw9lArt4yiN+1KJXLGgjZZNxs+pTzzHj9Zv0qqwLJNdtc1uvHzf+oQf7Y6HcOJ6bMNSH/fTm0ZnzUh+7Vk9TqpmjG9SqR+rtw30So8Pzya0Vs9FDAe9njpEhLcCS8eBSeMP9xl8nI+GGi87Yllp/99sSe+oXFzb24fcaR3Do/xijfLMGA/FlNpcTI470EyfIy3yeIvYIYoQDYYRU3yoxA1MVrOQ4aGuMYFCEPLwnffzqB7wlY7uSZf7/XwduK0fT6f5H//Fqs9lqs7nddH2z/re2erVy/q/OtPFim21bmZmQnJnWszrVufZWN1YhVSXGDDFTUer9goTwYwcZycP5QSV58vJ7cffz8YkhXn6l/6LumXAffHZdcOisvHM33EzIysqKf63vvq5e9awZ/b7K3SN184H1y/VyJHNHdjgtmyxJe7k53UDYv7T7
*/
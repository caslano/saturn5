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

#ifndef BOOST_GEOMETRY_PROJECTIONS_MBT_FPS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_MBT_FPS_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/aasincos.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace mbt_fps
    {

            static const int max_iter = 10;
            static const double loop_tol = 1e-7;
            static const double C1 = 0.45503;
            static const double C2 = 1.36509;
            static const double C3 = 1.41546;
            static const double C_x = 0.22248;
            static const double C_y = 1.44492;
            //static const double C1_2 = 0.33333333333333333333333333;

            template <typename T>
            inline T C1_2() { return detail::third<T>(); }

            template <typename T, typename Parameters>
            struct base_mbt_fps_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T C1_2 = mbt_fps::C1_2<T>();

                    T k, V, t;
                    int i;

                    k = C3 * sin(lp_lat);
                    for (i = max_iter; i ; --i) {
                        t = lp_lat / C2;
                        lp_lat -= V = (C1 * sin(t) + sin(lp_lat) - k) /
                            (C1_2 * cos(t) + cos(lp_lat));
                        if (fabs(V) < loop_tol)
                            break;
                    }
                    t = lp_lat / C2;
                    xy_x = C_x * lp_lon * (1. + 3. * cos(lp_lat)/cos(t) );
                    xy_y = C_y * sin(t);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const&, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T t;

                    lp_lat = C2 * (t = aasin(xy_y / C_y));
                    lp_lon = xy_x / (C_x * (1. + 3. * cos(lp_lat)/cos(t)));
                    lp_lat = aasin((C1 * sin(t) + sin(lp_lat)) / C3);
                }

                static inline std::string get_name()
                {
                    return "mbt_fps_spheroid";
                }

            };

            // McBryde-Thomas Flat-Pole Sine (No. 2)
            template <typename Parameters>
            inline void setup_mbt_fps(Parameters& par)
            {
                par.es = 0;
            }

    }} // namespace detail::mbt_fps
    #endif // doxygen

    /*!
        \brief McBryde-Thomas Flat-Pole Sine (No. 2) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_mbt_fps.gif
    */
    template <typename T, typename Parameters>
    struct mbt_fps_spheroid : public detail::mbt_fps::base_mbt_fps_spheroid<T, Parameters>
    {
        template <typename Params>
        inline mbt_fps_spheroid(Params const& , Parameters & par)
        {
            detail::mbt_fps::setup_mbt_fps(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_mbt_fps, mbt_fps_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(mbt_fps_entry, mbt_fps_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(mbt_fps_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(mbt_fps, mbt_fps_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_MBT_FPS_HPP


/* mbt_fps.hpp
6Wj3Mvwz0gHghdhBtjsaBrzZoZsR7vl2TEe9szng/fK3fkWcGQUyoV7YqVU3f+wovuu+OLMQ2LOuI+YNd37xhl6nehM7xXG0Zdlg1c470rOrGXKBTRfS2CBnvsmrBk8sSVRVs84b6ZN52pfC/bIc/AP80LX3Wqu/R9rNVVZynXlRHpE1gH4VESwr1PvN56jgwPNJHXRzqzOy4+Btn+eZMl9fVug8wgRyuMGGVKkyokMw/VlsCgAELPvTNVqF7p+S++UWtSvCSOwFevKrO6lydTLVxuRgxULaadEa9s5nPpk2K4TcjKMl+tAaACQBZzzfwzNygJXvziqVi8mdZMy/HPf0/5wiTqOL/uLnGqS3LYazaGYsl++lrvCzJN/TCrPBadoXkPfoK6x9NGe/ZQyuHv+l/SU6ojunyzXfke0Ok++a3pOyvKjtJ+TY1x7TzZPAvc+oknkilwiCS5tlxSVqNMBICHi2jLJGVBQdAR8Q7ihovoo3wkI5RWMxXp954eT+Xt+sBW+ZFIxI76IZzejmaMTjqUMg2e6+7EbMv1GlMmcaBetjyZGP2EGBMil2ceuyzrk71SanR4KAQnhNeKYcxu712jftMTz4PZDR5UE3KUKEAx7qcJlfHvlh/rhcbpO+3jJwfHobzzGzkPwNtiFHH7yXcQdpXrhxPCReWNub3h2E3lK5QbeRYzys8YHSq+sii8VWEwqo8tgTXqs9p2XCF74MirwmDD3puCdtYpjT9bwqVf8g5xScKRuUdxhwSPwpn/8kZgvO8qIrzTRzZ/EfwzzucOnVAKch292Itwvho7fyVwKimKP2i3NN+vohPBWmYSX0J3iz+gQEbzlsbtZvOb2VR+qvmEczPxsnPH/tyKCclrJ8A2YpNscGr5EpuOp4JccH8ThlR1MeMNZjjSZu0uk8ayxbSOwVRaeAykwqNxp8dpeALCadHgsnlClCR20eo/vI+ZWfmBZ6QKKQdqIhDBiUuU5fVd95+wO+0qykH/Jvu8mtH0r1/sXSf3IBIkThLI0SDfqbc/83B6U2ZSsVlfb1CLrh4gYz0yPqnA6wF1RP90o+bseJN4gNBDgtujof5ZNJ/8/0KW1qx+GJ9ZUz4Zb6YEQkSeI9ppC+03A+/N7JzbXzy9hKxVJ+/vvKx1xErG0ImVJwN1G9/7Vw8cGNagKPLVKlMwmsDZydu4jMt8KDjR9v3M1nLgdDy+lZP68h6DZcaQV1zztvoHkS8mQLecBywPaBCCP3WFNWKn9s6pstM9t8Qp7wo3Sl79Dptn6K5DUFdOIwY9yFVdDSGfsgbW3vLU5hdLq0A598Y/dnEaHvwakKQkuLWiuhBPTEWjm5u1PSoeHcym7/xpk4pf4X4zKVtVCIYDFmjjiRkUct/dTXoPt+932TeVaXUkPExSlzgf0VezNWHKg8mNAROyxQsv4dfKPF0pEmQ1kzbPg3yLGwRkTfjPWWKIXtn32IjmO1bdiv6l6xjyAZIW1cfhmobvBin6HvMZWmxaa+8ZWeYPgAFhL09NFGQBQ1YoJQCsZ7ze20Sk0pOR7qSPJDh+ekqm+sLAWmWWKbpbM8uNX7nPHosNw1piAGE+M6mQ26Jj2KtdHqpJMSPadzL5F7We5I9VaiGzoQrC8oo9WwejumERYfP+xVuy4YARdTjnjR7F0T2zsM2+ydYFXbnZckSGr5uz84M1lQONepLO2weQfl5FJAsMDemedUzrlbrDTHwZtoPV+rKcHfJTTD1Vh5kRc/ubpK/m1fcPCYgLFMtXz/pMVKGLaovIxgpbeAeGmMN7Dr0rcXvHygZG2afOgR1wZ58904d9trr550jafr+WH6jDoJyGAnyjx76gQEQhNoBVjfWyhTk0iE9GrBBHAcnECY9I58OqCko67eHU8318Y9PAk0PkQ+/Pr18KYX4HVIxSlcvOA+zsrCQgUv1ukL/Ed8MxAdAkThihKlaVrDblCgyndMem63xvqdtWnbksWgpFkbsQyu3j/9cENe6qEnGCnn8Clr2rda4PuWHdVYyxGx5kBDtBrCut9JaR0KL0SPZOlsMAWZuutBhxeiNOMr4nkxISWckMetrgLWoYO4/yamk8u9LhW2uVSeHe90eP5d78oE58aMrM9hDFznzoyPxULnhVdsn+6iUDDHXZtgY9p1DwjF+9nRpxn1tDoW5pUMkFC/F3jbgAss6CbdmN2jGMkPGYXUmjCiopXl7tIcoSgO6vdCWpt34bl1bj8y7tyD6ortBkVR+oBn1XAa8Cz6FfSqC6oZXN052WCqbUQKDc1Z+7Fmtqkn0/YYe3GsSAuuu2Il2z5ZMbwDlMmXIfPMgEn9uTYzFNX9LPogSuhe/ov7xNGe3I9rOByVbpq13ZrVZNmvMtuWCqW9kDQCStTt6Dx1yKSLyWiysO6dny3j/RWlQC9gSTaM0uiYML+BUrI1C8PiiaO6FRi0RAaiSsSnN3kb+1PEuV3INtuxmxu+WaawHDPVo9rnKYTSM0wl6eGsNuW3W8s81G3PClY0v3IxmwMakvM913s0f7NWpxrdbRsIEZ2Cm3Vn5ps+gWhsq/kwmO9ByXpp0E08uOlE94L/ON9GPshP3GrLVJBe116pJS/dK8O77w9KknNf5Q2EQLfOHh3m5myYVF1W4xQ+QEARhVWq7PNbgIQtoXbTTsyLEVoFpnfso5sU2N4LLyKGhi8nZMXZGZp/wdUCm8Ec7phM3RUdas/xRYK5jpkih6V7fpmwdmKVBlxoKmsmR+j8iKpqcD37AXs0SNY+05ks3DCN9ybiGtOoUToAuoiHGQSPdGdOSBvyOe+kQz8IcY3lBatlOfoU1CCFZymEKF71I1msuMvZl967tyALe582j3RHIan+MgRpQamW+RHjn3g2YvVujOs5e9xJ/Ia5RsmfxIEJPWuC3U6YC8BXXCF1+aMCCHAw/KrL7AtToH61TgK3kfdChS/c07AgrfHm86sqS5nXGLrXerZR3xZOjT7dPQv/S7weQRFQdlnET8+crHTrptPArDGTJOvJ5nUDynq03NkdMt1Qy0ci5nJA36HEyxkAZ15CnRsw7tPS3JWeBmumlWl/v0cvTZXSTbkvj+UFZwkcOjnPBVtm9L5qzxtbTiNjGq/w5fay3vrTYO9g1MXobsmqhfJZJknkw3/kohyhUPQhaPcpNg125F+v6EZ9PI5Fi/gmm+BsJ+v6ePZY5dj4Lc5ehBOm6yhoYVx7LWx9q6JG2hQ4rfeV+LJfycDnQPVwtqAOjXE068QDaz+z8OipADjN63l8SjOLsa27W2uNyud5yOFjPje2rALWtT/5wVFc/VRxneo6ejz+HjuGboHJsfMqQ95rMQT8rBG8Dgohb7sV6NX/6atLFGkuISRAI38qdaokrmuL7LN2sZ7MH+OQmefzLxUJP+O1bgmRmVAmES8jab7ZY4pDT5SN4GsFYApK6+fFDYvgPcPPGXYlnNxTr0L5BNrNoRDZ41wUp1sN/HGHMxdl34HfKXvmJRuSJZUEcuiz8WMXQbgf4zsEW9Y4vRbsg1cVnadscXYunbx41sAj9AcSV2F1iptaHZ3NtS6Q8O1KlMnYTF5PK1J1JJ/fbqo9O/VbwP377lVwsAHVJkB/vpBfOE00yFPhQmE8CXv3eP5aI2ngCYLU/vRhrcLvPuM/PANFAqXo/Nf+nJNqCRbAK3YLsY4CUBn+3cqzHGPIRYZ6AAPGB/WbQ2tflJfEa0SlOuG3R/xjr4tde4ywghE5qixBR6XYOvRcKDKC1eSP3EJfcionwEufECQblTjvwLaG/klqLl93zN3HrVZ4NXdmz/Ixz1jCZ15ZGP6N9h+xm9NjW1mjgZIUkfErwlhx4NHq3HAQ3d2K54IXuBoYHOYSsUbZle6IGWzALmouiB72YbcO268XFtvkW0DgwxoBXYGvotos5QwftjqDKn1rAXllAsui3XV5h+jy3stCvYK5wgab4KxC4QKWAqZCqPyU/BUvKHjhYgHE6+8FyZ0snkB+UaM3DD9zTW3kub0U7BuwKwh4VDSCBuSduD0g387jKVbbbFoVHNiCEbwOSzv3/JtMzBmD/RGeIXgdWoUJm/20+DTNef6ZCVID7ssWFk55t+TAqXQQBWmyTQc35OmzRtOWQLZ3n6iDt/ge0gZPu5OB+Waa7wtgH8tCEwW1pU23Zb4+B7H6/VfjQTqeJl3yhwld/kqv77+5cl2z3wvvABiPZRHGgeXD3fZ7ysF3dMoXJqvB6ioNrreSmafG6O529kThKIyrJwZs/VXiJYfWH3f+ZmZpDtELMKmcLkggiWz0FdQUsnjWFd7aH2jhLeSBSE2n1bMy+hYhdesQaQeoSvq4AXwucpRAiEAtLBx7KYxUJIN6vnAhlT3vsnv3GJoHbg/5vXAtQ64qbj9TZNJQRizFmaP87Z7s/ICvvbvSdEvgxFQpQmOFsBbv5ZqkPGvn/LW0mXVIOiNM74Ky/qdsPrXzst1uZfZ1VXgn05F4iYVZDjEzYoDD4mXDRl7PctiU0cKAONTLWwmzPjnanfFJD0sVhmyuIK174NZCNOiYvWl94SM3tXel/geRqLSVPuApxr6F+PGnx/ancuW73DOGgm9mGNuQXGj2OjICn6lft8dCJkGe66UwgmMRKPMY/xQDrc9d2NMRSO9w8Cxqtawp6nEJVlV19fgsCkE5KZGf4avM1+kEduqhJP5jASuYdMXhAhdQzXte/ohR5+3cxKYuLHvD3uvlWNv3UIiWe+Dt0PYykrl+Xq84PhXacUVkg12vonLet/TS+zPext0YpIqsGDkkN1/3gA8U1vcTR4S/wJdHAyHYxHH0rZREz0kZOte4vt4eVcoY0NB8oC3DmNSDy/TAgF9wcZzHXD7BLb+Rf/oLCWma7nbXczlgc9Ym9nRpnRQqeOZO410fojFrnafJQDRd4/br7lczPqF/c6iRAdnqTXV/IneBpM+n5mmT+VFE96R4GQ31YFa5+b9NWMzUwkBn872zMeHop5Avj8LR2vwu2lNcnQVuF8jdXpsj/rbrBDEHp9d1pO/6wsWFld+9vR+z3rFop8fTosndvASL3lknijupBDTABUhHjbCjh1Werc+r4HdneVzcOJxVu6Dut/CwiJgIWFVvgZ3PNdWvoWYy2lddfOOOV/vv+lrobAJv2Gy1VcJGzEOxyHyWafrJQTomFBFk+xgaPsXhZ59R3sotT5SoiTjWoZCU+MB4c7P4WpL3G5tZxEAa3pLxiKs2KNY1ApAmyE6I+8ORXxe9eyzwZIDoiNdPL0y+dgvqLCu2z1E+ElRizOTf6n6JTJp0Zy1Gp5/I6mI264yUJyeVW6nafllvOb6KhMNV7vYCL6UN0IPPhkQOEzkTPzaHbelOMpAZ4R++WEmDJZfXrlaxHn1+H0M+UnlSpvMTy20fX3K8My+o6DWq2lW5/iVtfzltf9PWXzGTo20n18P8VNyuSkOB9p1mK58S3F9502ogCau0G1Y6kiPAuh0qnmDouVW27CYAtWyxjTSUzCWAJjUyz2TrDqlZgbez3Q4tbg/sWC0o+YEo3kkiwHCYfu68KXiPf973xrycx8poZ0HgK3y/CKsqMRknxe3uwCcf/NgvEX0LNlMitfZ1bzCFYp7/Slw/xTTaC2aJDS9sI7kpkBpLJVQwIV015OmcwcwpAslfiva3h2qqxCOtL0KTx0TPZoRmH5SUxb4df1tFXm7QhqqfFgrMt4diuDuGaxP82I0RyMpq/4tAEwnhi9jM9cpxfX1Ma7/bynAhnol6KPN8fs6jW/Z8Ru57TNldy7/JF4DlTt2Pad753DKZoiB6HI+NrPDFR14I6BZyDgFgAAI5yTrnjQPVlyJwLtrpRFT6N16u7eB5j8htUgOANLZ0FEcmI/Ib/CGCscn+efzFaCws45+sFg9VpQo71tzdbjE7WWiWlhRGrecoCppZjAYaEyPwfXTMGLYZuh/rq9lpqIBK1cq0bRwh55DM8KjgixdDez81FxT4pHk7UPbw5MHjFwq5E7xuDzqPAJxxP6ocH4D4xF0YGT4KOghiE5lU+74uXsAYFpw0QsvvPFfC6medsr4xAdlGCQiwrhV6e/VeEho5OO6ZiKFj5AMB/kt4g2+5LzkVM8gv+Mj+02UapSd+BYnEz9de5HTVpv3Bx+3LBuzxYbM47etOvenv/Xq8qsxaDJv0uvTs7Yoq4ZYrgWYTOxdNl7flBXpaIRs29G3VULY81q6nNkcP0NLDYnzlOUhje3YkrwqjeKJtWHVWZ1dVpvRfUGmzvagNjLhuzweuLg1MZx6VN1TRr9TqJU5kaiJ7L+n3s5sMI46VyEp8aZkLUuYFOTeD5XXPpfQ9CqWHK4EXTyoT4DqLvuyXD6xzpdtv3/ttruz5ZUFTe2UPNTE5GYQk+gv8RSWS89T1PfWHVlgGVLvi4lW7gv4NaQGrUt3NppWb3f78aToOzg22Ekuxbge9/xqlmVKZtpntXjdSTBlL2Y6ZFQanxu4XLiTHO/8Cb/JqR8WMKNlJTbUP/por8pVOapy6pu8x8+pY3ARI3MKjRtVJIjjvObdpo6vuroEEh+KXYxtfZPzUYiJHdP6C6TEZ0owF3nmvr5bRp/Kpa+9yNXYQQHaeO5ZXd9+t9rkNZeg3rJcIkUUK2rhrzK6niAQaALKIN7gczH7n1+wSZMVOsbubJRDy6yrM2Q89ohouLER8vOK7G6prvjPtrdiD1/mYEUko+15XW/aB0AYwvClTxH+bkOApq4iNtipL41fhdAHlrewVADM/LAwOB7srEPkvWA19jLFVkPnngcDcyg3L5bcFjEo0p8OY+/yLU6IT/BdNMFpjnZAx4HXL1yUjb90MWR26kXijyXgb/bT5cTO9Y2AuDTSZ+RHsHhFOuDCLCpTmmKO2i7M1/iEJb69sLcFCu2VCm4h4tYPutTb8jvWOWp/+EHQCxpo78bs23zo4W+ggMws38yK4h0RfZW3oLWFnXBMKC/f+qTdv09MebIFWb/8Fb2G2qbuFmFme3Ct9v7IGlNW44lyAc72vkiKq5LK5dRLUZgw8uJEaAnV47Qj18WcznAD/h6dR1TZxIx4zCIYjF7t7txv5eFrVQMc8BqKeNHFsvHHDcKB4yTMraTUJkC35LRJu4xpiZJs9hNVrb62QiY6m10DjESCYrcFnO1HjS7cTjtXygF1HWR0WPzNMezHB8YvdJ1ISm2qP85MdQ5miGm0xoAXBPzK0MvUNwtfee/KFzxi5+caz20w9NPwBr7rnSrDNJsuIPt96qQIzfZoQdUpsQmdUlMmrMHSw3JhXWOTLkcTJJ53lM3F45xqiOqbf9LiEO8oxOZkLQXw+2udpAXcnddd/HdyYEDo2fYhqoRBXdtqGuIqi0YpzmyymPTQ4a/rALzb9XwccD3pAYBRYsHeNGKHXrOmzrzuGzKit2HQkc1SHGGq6P4+jYF7UYSchNb8SOUdkMl4L964X8Dmh7a0pY43BiecUPH2rYiJaeCKeK75+jEnxybE8DnGE9ObTm4R0OnlZ5LbIsbHcYS5EIZcd7iqpC+znu32yLCR0Qb42twFZEwk/T3w2QjQ9UsX6HYZcIC3Ho0ouC/2tzs/BXnzljjs4lgkfccuxDJsTCgEtR9v9tQp4sUYp03unleitrkLN4ALOxMZiE7OK/3nsL1rArTFkZ5biHMx/h2Afe3SiqebXQ6pFozY9bbsD+WLrA6ThKCtRVCJJu3KyMmqTOtpx00pf6WHPkGM2BOAl1HncPHi+fWdGXiTfCLW4EHNc+057cvgeEctYFO9WdynbvcJvy2Qnz4VRUPoA5CTjtroYjYl36Mt4jb9egtDXegttoguWVDK/sgX7l1qqxIdXDodnXRKlbgTiu9VD1vlliDXsMtd0huGoHL1qzrLzGrAdKr5U+ZFIGRW3JAaxuYkvGzkuBbOWN+OSOcSuCur7UKEF/CO2CCVm0OltH/U0WA6qyCbIkMi5C6INERfY5+8iZjQysyJzAlEBfRMMVgTPsgzXzNvlRIteIpvbriCU5J9dHJUxDYzxr2oFI//Z7IZAHAso4IObq/qF/MvquOWuhXGu0l4fqvuyYP/BuFlXfGFK8Z3punoKLVfE6jo3t7yXmpXl3oFhjsl1qKUGOL22XShBURNc/OKYbCipiQeiT3YbGrXiw5Rq3cldkIL/3p0kH4NNH0Liy5HaisHdxZ1R3TJFIb1DSG+d62iR/UWDZNcl+lyZrbmz1zV1Ijuhd1Mifqx2jQZN3FTY+UDe6IhyAD0Ghl6eKpXsKYrvUouFIvevQZNs64taZ/wOAhfN4qvizW+0KvC/npf3MxD8WV3QjMm9Go65FZO4IkmjVSy5Nu55BKhM6cxtbFR7QLF37iz/uFquX4A5Q0P5HhhFLAVGDm+xz8D0isd+hk1Sk5rfUKO66YooZ6dh/EwzLg7Ii3VmJB8YT2ruseENt67CmiwCGgDvwNU+ql2AKHlXCG+WPQ5S5Fs5bzQDArGjCroU3Miowxt95aTRBj5cnxnoSMthCb26pSYKx37TDSSptAD5yMm82LUqeaGEqMVgZ3uDEqMG0ZGOityusvIF0KEyuqgPEcVeQaAy8Om+wWDS5DvuQf/vDc13ZG6c6Dy5klaMmZgA5uzFulWAaVrYZ3+s0E0+owM3srAmZDcGlUeqm6TNwJTUmoQJlvxtm0ziZUp+1k4BdzVP/XfAELZdAbokghOW35YUGzPLFexyw0tDHuYJsqsIVyGPpR7rObLLdHXYULzc0tcCWeMOaxdqm8KqbswyeWJL41dHdPK++xTkX9HqO3EoJ/dSKbiefN6nQn5m5vvDHFXXE68qXodCCwj/cp/UrAIjOly7vce0c2C4970ERxHhWRvPU9LCxcujTVaYnGx1hG3eUNA5f3KpJq9DVyPk5SL8Wsq2kwMxlTJDoR7B9+Vpoax2XPx6t4SRV4qqF4fV62ii0LCsjKIfRbSwIe4jwKgbhfI/MakXWMH6xMgwyP5zILX8b9hvr59UyQN1xkqzpCQlSlq//zLcAMZkU9U98NTDLoC5MPXHsvBTI5iVYe5MX1igcgzY7KjD22BevZk1d3D0UQXRC1C6jsqSupoImm081k7bcJTC7AqfDqKKBGGPSDei/EUu0XFfS5jeAHuMSl56EQ5QCP0rRb3yjU03Z3g0l+glTmc+ZnwlnMlOMxikLusOJW6NTfcKidE=
*/
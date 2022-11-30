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

// Purpose:  Implementation of the krovak (Krovak) projection.
//           Definition: http://www.ihsenergy.com/epsg/guid7.html#1.4.3
// Author:   Thomas Flemming, tf@ttqv.com
// Copyright (c) 2001, Thomas Flemming, tf@ttqv.com

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_KROVAK_HPP
#define BOOST_GEOMETRY_PROJECTIONS_KROVAK_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace krovak
    {
            static double epsilon = 1e-15;
            static double S45 = 0.785398163397448;  /* 45 deg */
            static double S90 = 1.570796326794896;  /* 90 deg */
            static double UQ  = 1.04216856380474;   /* DU(2, 59, 42, 42.69689) */
            static double S0  = 1.37008346281555;   /* Latitude of pseudo standard parallel 78deg 30'00" N */
            /* Not sure at all of the appropriate number for max_iter... */
            static int max_iter = 100;

            template <typename T>
            struct par_krovak
            {
                T alpha;
                T k;
                T n;
                T rho0;
                T ad;
                int czech;
            };

            /**
               NOTES: According to EPSG the full Krovak projection method should have
                      the following parameters.  Within PROJ.4 the azimuth, and pseudo
                      standard parallel are hardcoded in the algorithm and can't be
                      altered from outside.  The others all have defaults to match the
                      common usage with Krovak projection.

              lat_0 = latitude of centre of the projection

              lon_0 = longitude of centre of the projection

              ** = azimuth (true) of the centre line passing through the centre of the projection

              ** = latitude of pseudo standard parallel

              k  = scale factor on the pseudo standard parallel

              x_0 = False Easting of the centre of the projection at the apex of the cone

              y_0 = False Northing of the centre of the projection at the apex of the cone

             **/

            template <typename T, typename Parameters>
            struct base_krovak_ellipsoid
            {
                par_krovak<T> m_proj_parm;

                // FORWARD(e_forward)  ellipsoid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T gfi, u, deltav, s, d, eps, rho;

                    gfi = math::pow( (T(1) + par.e * sin(lp_lat)) / (T(1) - par.e * sin(lp_lat)), this->m_proj_parm.alpha * par.e / T(2));

                    u = 2. * (atan(this->m_proj_parm.k * math::pow( tan(lp_lat / T(2) + S45), this->m_proj_parm.alpha) / gfi)-S45);
                    deltav = -lp_lon * this->m_proj_parm.alpha;

                    s = asin(cos(this->m_proj_parm.ad) * sin(u) + sin(this->m_proj_parm.ad) * cos(u) * cos(deltav));
                    d = asin(cos(u) * sin(deltav) / cos(s));

                    eps = this->m_proj_parm.n * d;
                    rho = this->m_proj_parm.rho0 * math::pow(tan(S0 / T(2) + S45) , this->m_proj_parm.n) / math::pow(tan(s / T(2) + S45) , this->m_proj_parm.n);

                    xy_y = rho * cos(eps);
                    xy_x = rho * sin(eps);

                    xy_y *= this->m_proj_parm.czech;
                    xy_x *= this->m_proj_parm.czech;
                }

                // INVERSE(e_inverse)  ellipsoid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    T u, deltav, s, d, eps, rho, fi1, xy0;
                    int i;

                    // TODO: replace with std::swap()
                    xy0 = xy_x;
                    xy_x = xy_y;
                    xy_y = xy0;

                    xy_x *= this->m_proj_parm.czech;
                    xy_y *= this->m_proj_parm.czech;

                    rho = sqrt(xy_x * xy_x + xy_y * xy_y);
                    eps = atan2(xy_y, xy_x);

                    d = eps / sin(S0);
                    s = T(2) * (atan(math::pow(this->m_proj_parm.rho0 / rho, T(1) / this->m_proj_parm.n) * tan(S0 / T(2) + S45)) - S45);

                    u = asin(cos(this->m_proj_parm.ad) * sin(s) - sin(this->m_proj_parm.ad) * cos(s) * cos(d));
                    deltav = asin(cos(s) * sin(d) / cos(u));

                    lp_lon = par.lam0 - deltav / this->m_proj_parm.alpha;

                    /* ITERATION FOR lp_lat */
                    fi1 = u;

                    for (i = max_iter; i ; --i) {
                        lp_lat = T(2) * ( atan( math::pow( this->m_proj_parm.k, T(-1) / this->m_proj_parm.alpha)  *
                                              math::pow( tan(u / T(2) + S45) , T(1) / this->m_proj_parm.alpha)  *
                                              math::pow( (T(1) + par.e * sin(fi1)) / (T(1) - par.e * sin(fi1)) , par.e / T(2))
                                            )  - S45);

                        if (fabs(fi1 - lp_lat) < epsilon)
                            break;
                        fi1 = lp_lat;
                    }
                    if( i == 0 )
                        BOOST_THROW_EXCEPTION( projection_exception(error_non_convergent) );

                   lp_lon -= par.lam0;
                }

                static inline std::string get_name()
                {
                    return "krovak_ellipsoid";
                }

            };

            // Krovak
            template <typename Params, typename Parameters, typename T>
            inline void setup_krovak(Params const& params, Parameters& par, par_krovak<T>& proj_parm)
            {
                T u0, n0, g;

                /* we want Bessel as fixed ellipsoid */
                par.a = 6377397.155;
                par.es = 0.006674372230614;
                par.e = sqrt(par.es);

                /* if latitude of projection center is not set, use 49d30'N */
                if (!pj_param_exists<srs::spar::lat_0>(params, "lat_0", srs::dpar::lat_0))
                    par.phi0 = 0.863937979737193;

                /* if center long is not set use 42d30'E of Ferro - 17d40' for Ferro */
                /* that will correspond to using longitudes relative to greenwich    */
                /* as input and output, instead of lat/long relative to Ferro */
                if (!pj_param_exists<srs::spar::lon_0>(params, "lon_0", srs::dpar::lon_0))
                    par.lam0 = 0.7417649320975901 - 0.308341501185665;

                /* if scale not set default to 0.9999 */
                if (!pj_param_exists<srs::spar::k>(params, "k", srs::dpar::k))
                    par.k0 = 0.9999;

                proj_parm.czech = 1;
                if( !pj_param_exists<srs::spar::czech>(params, "czech", srs::dpar::czech) )
                    proj_parm.czech = -1;

                /* Set up shared parameters between forward and inverse */
                proj_parm.alpha = sqrt(T(1) + (par.es * math::pow(cos(par.phi0), 4)) / (T(1) - par.es));
                u0 = asin(sin(par.phi0) / proj_parm.alpha);
                g = math::pow( (T(1) + par.e * sin(par.phi0)) / (T(1) - par.e * sin(par.phi0)) , proj_parm.alpha * par.e / T(2) );
                proj_parm.k = tan( u0 / 2. + S45) / math::pow(tan(par.phi0 / T(2) + S45) , proj_parm.alpha) * g;
                n0 = sqrt(T(1) - par.es) / (T(1) - par.es * math::pow(sin(par.phi0), 2));
                proj_parm.n = sin(S0);
                proj_parm.rho0 = par.k0 * n0 / tan(S0);
                proj_parm.ad = S90 - UQ;
            }

    }} // namespace detail::krovak
    #endif // doxygen

    /*!
        \brief Krovak projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Ellipsoid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
         - lat_0: Latitude of origin
         - lon_0: Central meridian
         - k: Scale factor on the pseudo standard parallel
        \par Example
        \image html ex_krovak.gif
    */
    template <typename T, typename Parameters>
    struct krovak_ellipsoid : public detail::krovak::base_krovak_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline krovak_ellipsoid(Params const& params, Parameters & par)
        {
            detail::krovak::setup_krovak(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_krovak, krovak_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(krovak_entry, krovak_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(krovak_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(krovak, krovak_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_KROVAK_HPP


/* krovak.hpp
VO/kxz/vMPQA9+oWcCEYWMj1l67p/pZ52TdID7xfrbhHJWnJPCbuHJqjkveMHdm9ywCx0/2ahaqjuIutnepqhN1oqtyt5UB58DN9xlWMlkHgrdA9CBXuKZK7VrDxvk+RTQTxIb15lN6WPX9uEBpd923xzV+gxdcpM59ADiE6xdYAWUDKz3VQbRL/MRw80lxQuQS8QqUAkB7y3ufBYq4n2RL1kKcJ18Y0wp7tuN0uH81ytakN4v7AVHk3CLh1O9/cYBzNmP2geVuvf6mhSbaSw9joQV4yPa0h65fMf9zjZezyOIuMrNvWbM3q8D5iCLUVT79W5DsoO3oxAjVf3HVsZsg3JlDUbO67thMmMaZzy6ZJmlahVC0LQFK7MAVzkc21iFDe/ZWHnFJS5IqmD924jFWz53E8Jw2nTtx75KwrE46S/ihsPRbPL2I407ceXMYBaK7iJi/dq9klmpGvokyQukWRoMlT60Du24a07jSZZo31dMpSA8jTdxt7jJ37LEsaJfYxGqaAgLmmUkuhCITrJDYpB6ZgjYm+0OCftZc3qrWhoLSvmlqNUT2vqNZnQWa7PHc1Z9ChK6FRe8IzNvP2ENvmpbMf6zx8XJBdwjsMSjkqNrwGlq3ASUpuijan3o8K3NhC/KBe+K7fptBrzGYZALwLpfgJCHcMMeRpU9fgpxVuIzPmJzHzW3RaoNLPuLxsQNIE3QREW9jAFR5CrJ1BzQW2v1MynJ8DhL+vc/Zl9WV3yEmIAAAs/9NcIryX8WVHtv6jd+MPBhwU4wdRO0otRPch9fKPVXslQ3xMmLUkB3jbDMUJs0CpvLZBxPOqpkfOkmxwbwTkwH8cDM4AgrFNI7Zct1LI6QMBnLV+1WvBj1Ca17EvQA1YtwivOyN8fwNk5JqZG7QdxjKoUqp/chYTmymvHm3EvHYV6+BoTXUPQ6rtioeY1K5s4zH2Nb0ItTLWwW3nWASFBbMVxmCLhifUqFgFr9eiBWUVNP4+El6pqkct7XH3amAHXLk+8t260HVVxOKHmtrvH0f3mQjDhF152i6m67mX1AJ7dU4TdqTy+fwi7RVADCDgPXX8UIbZmWJtCHK/QtsMeCU+77QFrjz9d7zR87DO9DY4hC0FL9Jtf91Lv5tMd1u+KwgMfZYEFQsTedekHjg6yNXhIJFSdjVIwCeR4OghYhReNFWOagiTnriGw4Wgc2N/wcXALJwkWxdVxvIEbIcpS/bkJJ8NYzgjcZA4MI77x9lJ1fKc/W4/SZRO9WESfn1rk6fRTfGWCI+Du2Iwxxlry9B027ZE0U1TByTxoecOixJGliTdWf+yklIwU++vDraiy81FdMGDcKtJTIYtFyxbV/cQdmogOhlcIQ5r6EQ+QXaKKS0M1cd8XCVqgSd80t8nfiSGPXuFFSMIMtfYo5e5LUUiW/1rxj/jddHq/kArfOyFLSW0Fim3kLYWatuO9sIdORdGP5z5HpLOM0nEHYhIaQlI6EAbXVu2o/cEC2RWJVsKkyhEoXg4/LNx1Bj2IeAvxk6zi9nI5Cf+GOKF9X3RwYUoc4pdiCEjDyov3K59LR3KsRLbq0WP/51k7nfonQ/PqwNzOicyagYPmqPkT7ZQZ/nCvbfEfEUL7zAyDMx1GA1D6Gam75MUP6dKobsSeiaQ0hhRHHiBF/gmSjS+IPshnaG1Wm3tpuY1wlwJe2mS+MWqqZypS9tJYuybGM7C83s1jlnpnAAGoIlqk7xcESevYEJoGOboj5MKcanXCCZYXw63tgM6oQ3l23gWn5N3dCVK4DW2l8IQv4GPYBK4CIUB1r0rkUaDhJebHQrL1KfDNn6Ji3vOLEtcJOBV1/uhKQgeB+imCBvwlPKwL9r2b/MnE8WQf8tfGxbkhJI+XjfatLPD5gRIeXRnPK5HLZfOq58gjO2Az8EEDeI6XmJybBmFOOcnCAS0rg/c09iCmVJbb1lt+Wc6KqGotmQQ07hfMJej//F7OyBBr5biaUg3bPRrcQmaXWH2KMQVsNItJsu8so0XF+HndwWniE2j/ZNZBycmBMALBqR7PoUPIyJmGFRvLXQ349T3DCvF9cFTNdGKAy9jrhlO93AoGo8PwzAstJAGHiVtQ+lC49to/VVquJ5FIEKfyw7LWX2WlU3YpEE3fUY3VFzMt+EFlQ7ZjP4edpO6GXveoaBSbKhD7K3xyNv0lrfhLWZ1k4KQIZ8ti2Q4obCy7k30gGuITKIU/xjs/8cwIZsu34ZWcV5TLYCqSh6MSfHHmpG3uttIOq63ABNI3dDCjPcKX+hiR4IybCXegjEH1w1On1wgZN3HW+OCl3bRRtbx/c9qy+/VXIuIrgdthq2SCCXLY8iTQru/zYbUBJES5iEZb68XxO6j1Uvp51mE2R+vDjkBfMir+VwDsdGEBcelGAcL0paOubV9EBETxbdWJ/v3MYStzIjiM6jovbcHD95Sfbp8uaCRgglba/cQbowxGbFAapJUR3Fq5SBdooOfPLZRwmGZUTZrUT4KAeAUIG+1qPCoyqJkYP6kZbsN8nUAYi5rRIdqVyNvDtnNpur8eIjpQZ7HSrm2ppXny2RecybPOf/0Gp+7ylRpfE2G6/vLx/7Lyxt0jyc0cCrSjNKkNs6UN9SNV0Agq9S4KA+buksKaNbdPNBAYNqKXvMI/6Mu5/cBvlBnZM6wq4FMtxgUqUEJ/UIgWpdqix/TrDGKUXU9IMEWc2hcFdLDMumyhakxLzB0DA1shKS3flTFG+gLE8sDmbnRZuhKMMbY6sdF24EtFHOr1YCmh5GiY3m/9cWMHoS18+ZX14B/mLSQX0WaMNNxhb6GpBj+UCv4H4/evHxRD81czLCX1bEI8kpkk8hPxZ18yG0QNstCSHJjliLllJg0SfNVWL6kxCw2+tZnQ0CuemKS/PJXSCH8nugcUTPXgWNLA85S1EEM5L3BKgb+arBeIS9kjpS561q+yqtQOgxON57gQ6vvBDi8K+cjjmSgskQ0ddlzLFjtfeVPOWdrC6zhk9Xo/MdjduPwYC0KGWT8u4HirKKaJUa68dg9cfnv9UbEDN8VW7lN1j8pMFyfhp+D2r1hud5G7pkggiPqjfJySTIcW2Oaywv6LZHDfmhx7SWRAf5Fx1Vhu+hqGeydZDCbw1RY2/NiGDmyB66Nrofu1UPOca6mdo5UzbbreJnCGSR7mX9rkTDJz8P4ucXpYVcORxSJLXBkG8zLQXFItSH4l6g3PTU1Q69Xs4Wx45I03xcV9mk95nbvTU3BBebvTQ2DyjTfG+YjPkGJbkGH7YClp769JbbiRaPCWLlNka+z4Zr2MMwhb5bXBJlawKImzu77q6XX9/2PKvj9YWCMyF+ZgJmKRWvQ8YzYxlRbSjqtZbDoPUGjkenhLjV4PPPdtK+wpKQv+LM7Aj6KY4hJnKF0iBtt8syFAtzLJDqiy7jM8Igmqby1ifF6zkK4j9LVpmWlRIau50C+OxSJqo4haOL71kaJJarMWJn7bVESRgYSI3cpqKRMqmQAknRhwytWocLjm7NGelaN4w4TIoXjeozQ4ZzGdQWMfaOMGCkYnejDAdY97VxHIyBno1OKTfDKLb7/omDApDsKi66tkGNK8hvKz50ZJuJp1lSJng/Q7swz6eQNfyWI+pwZBsUQoZOEC5PVp43WcX2fsJpfOCa5k7suTjJwKesvKspBgjIRbGkYdRCn91oLtLgbhpJqDif0QsJ4xP+ZywyoEVf6OiJwxtAOixPL/MMJ4FeI5DAP9g0O6NUcjKOQyrfpelOQUzEYdnumEi7CuDCVASAcLLqoxAolBh/RsK5htwO7peAUFUd2PzLHRRN21G7EBwkBIVDZDME20+JDM/OObDbWyotzoCQH7wFvT/UsDilguHUUgEvswUbB2QgmVQ1cvK9x7QnRt26jbuC5atnMral3zq2Pu1DuOde6GRN5BACKUXWz+tx3IIbD/cHqfjXlypkl8wtAE0IUn7ilG+Lf600Sbl6TJHW4cksMPwZMCRwuixuWmJYgcbh6S2x3MUYc6vEwn8d5yH0mwLdiGcz9fQ4Hf2XVwv4cyBf1ImihLV19mToIWM01KkhFcZTGB6dljLLUqRMv8OQAKhRMDHVP1N18+XbcSoJf2NDZRdcIkhWwLFgHPcVRvqIeyTLf3b/oHvNSzIDZ+BQJCUvg+ffKsDzmF/aZAEmVanV33bDuettT8wQcdbPRY/VaGFPch3imoimC+cxF7YyCOsdpmSQWedXeiI6LYvHfYKuzT8xvFGtAcNAur5F0/pxyhsIouu7oXf22WxoGJq8sXgjyvsOa+d0aua4MtOlsorQMQ6rQbeAehILvhJoiLJBf309+ka99EZt605bZ14OWUZt+hK3kBZ0xCDGC+6LJ6zRz+CW/pHhpyA8IdlEYV/yzQofJl+NB7ZXrSDsAjdlIk7CCDqpC7x6YuTRRCrRPADWTL8wpOZ5u5PjXPbGh0t/Xforx4qoGYdkeoKZj5oK01rnPns5UZHA5p8w2NJf+IoR6HTHQZefaRSekGnlSFAIS8ZfTa13AJQbVS7N4HMRXzY0VInYzY7Pu711WRbge2Go4FrQp0K+0sPZH0UMc5Orx3S2W/13jMu0Vq2UZZMQZH8XpojvKzWj/EEdKVKBrs2lr4psj0acfU/4KrEC7G85FKFT5YRuLPv3kBkSng9j///WJZB0YbeSTVT39kZSuiUr9d5lIUzpNUnNrqsALIIz5w0NZy/KMw9ZUjZtJz5AXoxL0sZsbN6avXh+PqelHIqlmxmigmi9Hqp5TFcjuBJ7O/PTy+P3uM26mIdgpWYYfX4Lr2e88p1mn3LNss1Pv5kFKZKEKwn32MZHTCAEBQ3yVN0YE0IL4V5hD3+4H8t41hMIGq3GoJgoBoQEAkl+VZhut353RJVWY4x8Lbjmb2gbMPQm3K7l50dpqRDtPANtD1wXKbDXtn5BjPCgPo1Z1J15RS00DogixCkAouc5G/l1Q3WczqWfD1g1H9q9zo4HTMf1XQ1jrlLEOVXrpbqf2Nk7sPaP22X62e4ZMSTVqIuJpw/ruWO1N3TGjiuHhyztNH08Z3KSwicDjJi+6J1THs2hPaZR7Xwv7e2LWU2iYSL35lcBqq+FBZ51Io3OLzvtKI5tuHCJ175IbHHRZAMIfnkjIB1/R9+mAGLx454Rdhd5pe++LoBMVbA1rYj4KLXca/q3jgDn58VfXe8Jcol0tlmVU8l5MJwgOiTTKws8MW7tgE5zKzZFB0YtY06z45vOauFF3xj6iSTNS1Pd7pWbmbh4+E4RU96A5bINXXs3q/td7gE2zIE5hwSNOOCRt35Yp/fPtQQNsBQtmqcr4t/O+NVL0ZmVcLctil0XC4vydU51F8F6HJlHPhdA7duvBKPjqp7hS/rUP2zWWYQTbI798Erk2iZLcufXhRQyVX1EOm4fHXAVO7u3BybmgnCXtuVPm+wbObXS4Jo7i53AmygZIDhyX8b/gOe29mDANHfd2qvCwCL9xIeCTAt57X85AlwQArD+AKwIHxmVU7pyBSLJQjiuMTdXzTTcb9ePzSplpWDuZynq9sSFdAqmVMTVPnJTwbH8TnVjNyAv0GpEimkJXjZBoZ6WWqj4Zxf31dvQDms4ZSuI2N97eh2nYUlgbRB3QOGAC5id4FxwsYs8x806WlfwsAJ1fuEXmdqnZjmiiwHSGuFhSgSI8qREgPRmX4KRh2EsF0oA3jsKmP8BI7h0Mm5CrfW2EMImQGllgGfdutuom8jDua+3WrHP9H5J+B7ZXlGrLle5baLkty36wqIAr7TWUdxpQ36GXvRB3x+ZuifXORfZr+xNpQNEGs1XsdU5vD80lNJGFb8keeRYIKOVPmIiwbmGrAjzeaLTZAhA3yojXLVYGtSbuk9tZz+LNR/TSZRnKtKiWlHGoMtqnZjuK6/uVhBF7kiyu1Jkc+ZwE7DgII4wjw3lwreZqmtymc3UtILOFptYG7c6AmfT+jBcPa1HIhRuuGacOIZtdoY3gHu/ctrI9Op6fg8rxZjHgE2DOJC3WXw0EcsnzfVlBuuzu6SV3U3k5Vjbc1XSR/DaqEmtboCwGVHGhRtwvdv5VO5oBYxu93ZJKQBy7L6IckTL4LFawpXitf9j+DQl2XYfhI2Xc/DgZTdzlnWVSZzmSSDwvxm8tT91+2ONVnIg3fFkFJkzOxadNpNeGI6eXHdUF1qrcaSyxMyz2GkYb1Q4SO7Lh5Rq7zDFOsTHcYGyGIeiPz2LimqzXNEMPOlxv68j3ImUjWYwttbvPAwEiUyv9hx912W9Y2QvZXry3YvYCCanIrTlnEwJfLr4C8wnI7nhwwPkdHmyfffkZK5v/OqCD0PC09xrQ6tI8N69xhdyAOdnXqLtk8Jy1UHpkwKYwa899O5LDOI5XZhe7Qx+3peiNaqbqQYCvLP1vYl1YGmtdD3+RizmtqXYqV2sjVupJZmoJjBG8I3/7IYmnR/FGBOfqFn5hWBNBipxENn4HdOUiR1fm0hL2ZRbYv9S9OWCIXZjLhycpBBiZO8PHYGE9IR7WJT/OGb05DSkJFnrfLLJjcpnY9ivwO7Jjj7HBqH+/CXjPbU4Xm358emzRy9IcRAKXZkvkAnAuuqG5kPwj247WlxyuE01ryfFa/zUMholzjobhO80KFF8n3Wb7kChT+j0LTaoj3uWFuqchMmNu8DNHALwx049lMWdC8roSpBsVkY1YACCgKwlDpCOW/5NW04FxhAC4cpLyeDvjt5kIuKWW8z/IenNu3MbTcH0FTC1i4w6t4yHfOgvc+AUAmw4FnMgFpo+ien5/QybOj2zmMIZiLfXGZ32x8gKn8mgCeUEnUOCn97ND2V2fTGUupQ53iSGABQzzDAiTwJHLcxD+crycoCuCf6VW1WlDfMIVAAnFOitrB3XEgBAEsePBFXw4nCj6R6Dt+DMM4yWqqPhb3lYscEQhLGN+f1xEOr88lRhqvuf1vKwCB1RgZCZlNDQQ8F2PBbL0HtZpj/xvUb4bGIztYJ8kJhAXOt8epw/SfqGkLYi5ghSaIPcHUNeKi47+Ph1ABHeb5mLQefjbpbgYSmwud+x9Sd4TH6KQEz/8gYjE5l2iG0ejD475gCm/rVh79BE74V/lL0wXp8avkA78+m6I0Ix/wf0eBdHDApFFExhKe+mN+ID1kQfwPye6W3Y+JavbS6VxUfC5mgaOoJDl7IqjojeM0+mHk0ftrIursaGOPZ8JC1Y7kfaRshujhkQ0pUuPe58FhlXYs0q0dyrx9wRWDwvQTX/mC2Rg3yH12mH9ztNuCDHv6qDSBpFUGDCyd1fOzUGm8fZ4Ac92GNBVlMxeB91GzTsTaw/2YpTt6Br8o8YCpOO4NZzOxwx1Ou9dRf30MBieaBoLt5kTUhtc/5D6uD34VlSjjLinnsYzo68zd0yWHXZ/TrXzoL3oH4R9OcSGJ2ZOlhjjnVrSXV1WuDelx60vGe50nHrq45+SZ4fGBuE7S9ROF9NAgyCP1Qcq52NwbfFZX/tMsqX+zC+r9mxRx8cq1l5vjg38TsTXAnWhLspDCTaMkOXcwmXU5qDOBXUj9BH26m/T2Rlhu1r28L719WUzf1hWF6Zf6hqQhp4GGF8fK6pvdyO631Yo3/g5BqvQ1KpWxuOjgTSP
*/
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_HAMMER_HPP
#define BOOST_GEOMETRY_PROJECTIONS_HAMMER_HPP

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
    namespace detail { namespace hammer
    {
            static const double epsilon = 1.0e-10;

            template <typename T>
            struct par_hammer
            {
                T w;
                T m, rm;
            };

            template <typename T, typename Parameters>
            struct base_hammer_spheroid
            {
                par_hammer<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T cosphi, d;

                    d = sqrt(2./(1. + (cosphi = cos(lp_lat)) * cos(lp_lon *= this->m_proj_parm.w)));
                    xy_x = this->m_proj_parm.m * d * cosphi * sin(lp_lon);
                    xy_y = this->m_proj_parm.rm * d * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T z;

                    z = sqrt(1. - 0.25*this->m_proj_parm.w*this->m_proj_parm.w*xy_x*xy_x - 0.25*xy_y*xy_y);
                    if (geometry::math::abs(2.*z*z-1.) < epsilon) {
                        lp_lon = HUGE_VAL;
                        lp_lat = HUGE_VAL;
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_or_lon_exceed_limit) );
                    } else {
                        lp_lon = aatan2(this->m_proj_parm.w * xy_x * z,2. * z * z - 1)/this->m_proj_parm.w;
                        lp_lat = aasin(z * xy_y);
                    }
                }

                static inline std::string get_name()
                {
                    return "hammer_spheroid";
                }

            };

            // Hammer & Eckert-Greifendorff
            template <typename Params, typename Parameters, typename T>
            inline void setup_hammer(Params const& params, Parameters& par, par_hammer<T>& proj_parm)
            {
                T tmp;

                if (pj_param_f<srs::spar::w>(params, "W", srs::dpar::w, tmp)) {
                    if ((proj_parm.w = fabs(tmp)) <= 0.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_w_or_m_zero_or_less) );
                } else
                    proj_parm.w = .5;
                if (pj_param_f<srs::spar::m>(params, "M", srs::dpar::m, tmp)) {
                    if ((proj_parm.m = fabs(tmp)) <= 0.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_w_or_m_zero_or_less) );
                } else
                    proj_parm.m = 1.;

                proj_parm.rm = 1. / proj_parm.m;
                proj_parm.m /= proj_parm.w;

                par.es = 0.;
            }

    }} // namespace detail::hammer
    #endif // doxygen

    /*!
        \brief Hammer & Eckert-Greifendorff projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Projection parameters
         - W (real)
         - M (real)
        \par Example
        \image html ex_hammer.gif
    */
    template <typename T, typename Parameters>
    struct hammer_spheroid : public detail::hammer::base_hammer_spheroid<T, Parameters>
    {
        template <typename Params>
        inline hammer_spheroid(Params const& params, Parameters & par)
        {
            detail::hammer::setup_hammer(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_hammer, hammer_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(hammer_entry, hammer_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(hammer_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(hammer, hammer_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_HAMMER_HPP


/* hammer.hpp
tqTvLhEV6W7gc32H7Dzf8gmwsbmlD/CqGIQVYFt5+dB+ETSrtCRoaaPZyYNvvA4oFXfGNHoxdqftz8fkQk6EsoDHckeBwifnOwzMwtsp+T4r4yHAZop4pwGsg4hr4P29op65Tml7258z5mEVkLWcClj80pJCPwwWyhAQA0j95OyYZ3BVM14HClZpltiF1fehH+dH2fySvp964f0lqXCx1nbES7vybnJ1o4KTZ+1DxYNeufIuzg8bqQsYB1G+jleYELe5Sn64ivPFqapCIzMiValLyzB2NSFxyRSc/dY1fmSdFMgjZWY7roVnjSm3t4P+RsCxCO6BwCcSelwV7mVNxV62cZKPhfI8GUT6zhddA+ai8yz4uwmBosys9+uZ27v4UvdyX8Ids9TXDYPlITod4zDC+PkgWs0CPPawf9n/po6tok7tde+wsgJ3Hc4Q7eSPzk4xM60SqKe7DwLPF0snbYKYOYdFnDHwfHgUkFR/zdSjdjCVzD2YpJFMOWOglhrI4FArTDrHn1XhjgnSJcVcZwwmT6ZXRpz66s9JZZoG+p0xaJUAXlnQyuO5Ejxc2gzUU+FRlbHYax+Q+caBtPsMHn/PBPOt4CuCA/50QFT4ZMq/c+bggFsdWRQi4M6qKylCzVH13VT8hALwiEvsUNFJDmiYz9oV+8Sc1DVhMbJ7pC2GxMw3y52zY3BdmZ9rI7pPfRqU0mxIk2tUaJfFhpNVMQpocTpjuw0+YFlVwEf86ETlHRMRwKuYhEUuWVYFvaij60FFOlmqdjffeiiDNrKZHm2DMC03haWN6Kgn04uXRLu5+tBo3SUlSkF9MonVWOBEbBITXbfKwXxoZdUtzBoMz7HDoImlvNVLy05633OH515XcAIs4b0HArb/uYKhxKeJuY4Rc2/Vi3Ofs5P1qrq3UanKoeopjKGutiMY1Z6SW55HpO/15tMIAuGG9J+3HORNVSzATuZ53l5m9CEK2esHl5p4bNFamfhwFzkl2HEWZAmiXfccT3nz23MXebmB34OAoAj6735kYF+Kt43nJWpuD6IRfYCip0V/W5gMVpAcjG49hl+7lK0JrzdgqO6HybTiJYcb5mbalR7oZ60kxlEl0uZwsasf6awiBpCfDNkiReV/Rkj0yREgD8jxFJzhML/mAK+CivjevLfQOAd5fJSEHZ2gBB3NiWT5ROg0cbpgRp4diTONlofU27ena5j+DSA3T+dUdNNFguDUtrAiMb2KWi/uknKGPyPj9RAlUrYndCKIk36GQwYQVRq52mg/spU5bmjnWzua1sJjLs5bMy8Eg95ug0zDXWBKxmNo25//qC8cc24BRArOQbsLDb5V9zh3Iu4L8M3t3pMasH3Cq5kMVf5LgrQr6rs80oVz3zdTL/z2sNLo1H3L5y15jQpNZu6TaWJXORNYCaOPawFuueyYkdcbViYSdgnr3ZL5cb34BTVug2Fn/rDRX9qgRhlvYRoooOE+iBPyayhJ4PQ0sFiu3cksHQKxVrDe9j+KS73H7SM0m9guE5jypvbvlfE3hRAALmeiX97xQekOlzKlzDlqra9wssMxRsdvUKKGVm9xT4oaFpfIVUUvV4ndaqXfq854erBL/M4K9BPZLLx6cI4N2UmBgq0vf0ewzIocDiuXmRO/UNsKtwdCQssBJvmeg8opDJmDW7LwIyf69/tmsYJBc8LYjq3EpA+IVbcbLGTz/U/C4H3ToD1ufHbS8t4p2DCx+8JGiyoPNTlKEU1HPd6yXgAvWgGtZsaDdKJWrkvVt2LJNumkmxjrsUc4TWgicHl7XuK9nialJaaBb41WClV/UevdIASmIoJSlYIdj09ATwSyIvgTqvZl7IRjvVENZ6LtRv8EhGU4R+gMJIoJYB8W4hDMm+0Yydn7FqowwugGPms8Hk2a1qgiZS8kyrmYawYOiGUN7+1wECnH4r4ktacDVsIshj8wTI3sv9iGKvdQN7JAqwSC0tSOtEAHllgOmVYAVTxQ8N9FXMTDmRbnS4/TmPasxYIs4iTBuxGnegFt7AW28bwM8+Xvez3HnQgy1QuAGBBilA/7zHq43bZENNxbb+d1NtALim2GBDZSZEgwWZ0DqzcBv1vsh/kAN4kICS8MvSuXl6nBqe3zTXozUNPYMovwT+7W0RQdHaqltZiGp+LfmOG0yZEEYGnQ+jB1V+9w5NdqEqCmdfH1vWhhzonBbyYToTNTVxKTR5KZkJDCGuJg7dWdvEhsEiOk34RwzcQQGdNTLdKop4ztggR/Sx3RVh+0GZ19sJO4Pmvhnh2kPvmTq8qNwxWoRKOX1G+/KrPYla9VgR4mnkudLviScbduk6t+nDBKRwy3OU09Ti2PPjLiyE1Dw51bQuXzkgr/yW+UoppHJx5rTVPW4kJ51aEm0u9XPhikEmMyA+ici7Kc2WYwLvdAZMInLj/hy3U08Y4VN9op4CnElM+irP5XbbXZq/26zsmqWip4XEIXIbaYL0wjJHt0thYkfyG8oMNqQUhlkgnxeUXIy0TPh7Xnw0TKiwc9hXUUam9qPKVV6F9CtXUa6LAwhQriSXtn6KyDuodAJLagzNtLCBpIfbEPxt9BToIKeyQyV8HDtONff5FsiHEGz7Crg1A3gUOtX/ugNzQMaj3hw1ObuYmGH8gfICKNAFGfeeik8tMUt9z+F2iLDjTNV3jPDB1qqhy7Qw+qH6Zil1v/NcBveZGM51HSYf7e0WQ/9sYKjEj8oVJ73wdjPF+VAzElozdYVQ3tWdTeBLNeX/rw6Nk8WPfTqKYgmsNx+jJpHL84bgzUEyVrb+jy6OQy8uz6UtOUKlA1tintwdJCFAVoGiOPjncJmrfIOIZ62/5WEykquLaAbJ+NgeCkTsSG7e14JLBW0FFaFqErjpL0vlgzeTDNsihwmeTDxGvoXHGW/7QbsnRVfLTd0S3M1j4V2NaBF6LzSJ+S9kaFqSYB5UOz+jhA2/J8n0Y5YcZp+AqvmYVIE145dpcRXF696mhXk2lvGz+irl2j7UDElnMZR/WUaBZTJ6dwDELRTPv6/PPypNRxtTzeikw2YqBogMDcmgf8gd1hEBTycKN1u9Rdt96uX9u41Yq3PuRwZJhByeXB6vGgqweX6PMK/5LES5aZHcRWFznnoJ4HZDLyJ0JfK5v7afWf8L0e5bI56RgDWlDs3dq9FWTbE4SezxqIzZ/qs1bBj+71Ka4ArBN6eAG8ZldimFzpyYvu2peE+7YprmhLZ6LJcJ6ZabH9bJykz4JpdH7qRN4pT6A1IdgRHH0+9kzc/la/ywZumb6ZQLWI21c5y4iAuXUGuCeG3vjHuwS18/2vgAKzJo4xeT6uwiMV1CgD82MpTvCj9WaqiQGdBLtJvo8WBGZc08zrZ97bFcIt6qFW9FhT/ldlDVkj0sSDobslEZwo3tjfooORjlS0FAwNkDAGpAILHjSHFU92h3bnDKTP0uIbblgIoOptzHUVIrh89uLqnwOXJ1L/67XxDv1/+Eq6C9fGmmOjuJO2kLANN5XMuZGnDcpDWd5nAbuE/FcIeqovSublNupJD8ukgJsSR/fGveEVy1ouhrKjlk4pGq6wyoUClD15YHwsz76LWzgc/53zVlEpzm/y7qVjd8Z1FFrL5dmsURbZqNc9DCinyb0ItwFEN3Ucpmo8VkjHu1bqeymACEmmr2kwHqLc205furHVfeh3N4ADkxTSz7g+QcMfgO3eI89Df62n6a00moL4I+mwgcwN1MD+t3wYUDW/kt9Ggpp2/xx2D6Hd3G4yDa7gti7s3gCiW1oujmBQEkwaSgWqYHECeXz6gWzYWZO/HYtyOz37D4ND2TBU5jkCLcXcubZs/glienZozXh8TauNXJimDaDi4GOtQpqSMRxdJbC2AqQqkJqWCrcDChCbN3elXAm6HdutBr1Und+yvLnSefrUosQMGDfJR+vDSHhFyrOjvuBS0jPCtlxLlL4Hu3J1nxLMco2Wz393+rG9SmIqHNgADOA4g4B0/YsSwOjWBi6jMfkoALe9wwLiut8YA6zFkqzlBaIFtGWRTRg5ABd+iskZT6IoSILJDfq0V1j1H2UP/RInuoclBP+DKJ4vorMCCIYp18UOk2INVbhZBO96w/u4oMXP9vW+cWXjqwWWlql7JDaIi59x6VdkQyCggME+xwge52nOPZ6U4V37xfRMsNEPLKzInRvabNmWCNq9HRdSLUfr0ogyTaByMFZQt5cldAFtdMRjKkoEWIM30hMxYuRJ0oPEB+836DzMMqGRB5xj8olycJ14NcNTSzrXULS65EhHO+5Nqrc0ZK7lI52jSnrPE6t68zzuVSO1sJ4b6OXpm32q6X9YAf9OzTBQMYhYYnMGBZb6oDDFU2N4gUU0ih88uzXl8Qkt+5eYGLIttMjS+436M8rshKeCZgWmoMnQEU8W16nJUubBYztXEVAGGUmcY4yrf7XYcFJPNc4YfzHYVp03nVVwq+Dc2P7VEa4ZaDxVEPOXEQWpHnPQf9SZNpUKTCwoOBZLCnRE4qAqFVptbizDzpeb0dVAYohXtk8VFgPb3hBlnRnLzLo52JdqlKrO6fCFyPtvh1j+JH/Q7EW3KXjemzbgWM/4K9d7I8X4teQygJpBIl+3o8nf/wc8QDqMlYCMRENziCk2707jnmTd9B5ua9Lf0a+7upQPARA3klpfZ62opIQkztL9n9GxtLWtfxNYoKTtfsR7WPZCOupwIcCQ8r/AWscY+dhZ2/tGDRhO6ZfYZ4wP4n/Nwvfj/wFp9CnVEf73XUXwTfVIaTkzqf8PvP6z5HFqNi+oLtS7k4fRNrtJ0zUe0rOnrHMWUFGT0FDwzNH77yLKjQSuCXy0G/vqfJgzzAZb5oSdOUdpiCivWMR7S9+BaLLXbDvk+WRI9szl+stbX+9K/gNiHDOr46AvNoAAUQZyobTsVc9RlVOJOFk/DDeXGMADivOADRibdCk3PoU9vQc65zbd1UlK3ifJ0rS6BM34sMUMFb4H5QcOvx3skm3UjoycnKcnUNufmZGyIqCyTrlTeNb2KuiybppWkt5aWYRrSa4q0T0U7nYTtyiTdjt0++SFVe31/E9ZKXGXyZYstQflStzpBsSL6nmYlEfueFNTQmUpnj8Xxb1NVZcht88d3zyzrx0eFc9K87HHJOh5fyT8MbazMRDzAoX+mlEQWMed/uJnOKcbLvPkaRKs+kFA/TLfnj0/vxNpZiXFp0CBZkbBRzdfuLwXb6VMf3UqJsE2+gB3vW5dUQSxm/NTTtTVXvD1q+Opg1fcVm2Z7Qf9k57Jil8XnCP3F7hTVJxGGlxG3wuYQalEcwpb/kvXYLEwNd2MkIWffAfToXvehnlzMYIKog3FOa2il2wXNJmc17Sm/BTliG5BUk9tGzYIhjgbLwhvdqta3xQX3IVP70R941q2V8HuTXF/B5NNavDACq0J36yWjGWtwxMzXNv2YNV5EAnzNwgENE+UxVG/3VAwqKDnzbxNww1kp2Lkv5QOZ2wiv2cNNx6wGWMQLZ8CGJ/VYyfeS4rzBl599fIEqxB5D3IkeBbsFzCZB7+2eb7VF2/u7nqx3v/8RLptAE41VM9aPGFCUEJef378VvXQ148ZxkFfWi76UvmKMyTO+DWR3ggBEYFe7ov6kmxJNOsITwwpZu8GkAVYOrNnUJTsjkPeEn6TDjFz37+zKYoQlD7Jfs+/0mYL2s7qpMEKwvmtcO7l+jbx5Z7lflEALbVx9tIu1uGk0wk0pW9DpnwaalIfRBkqrCOcTwGiZBcepxi3Fx3YKRTbz+G1GXcXrEjz8wfzftmJDm+5qg4sRg5lW2Wo4Un1zSfT1eSwV043bdb9LKr9ctskxEV8O7QDCQQPF6QBIF4fsT5TYZjyU5dYt8Tf0aOQjzTs5MJ3d/6d9JsD1ymp7v4ehfe7MP5j5SQX5wNC4PvpxXsbM01vivOFvuGOU3QJOfO6o7xHA2uf8PIKePuxeyk4siHxhQsJq6nEnulP5TFA1G5w6AW0KOh9ooc4hLHC7bsd9WxhuU4/eYl1Xf0IBVLbBdUEcGaauvKKn6nv5xqE61Xd71GsGkXDQcvTlIW/8YNhwld+ynNuH9zFpoGeXAHdnWfNR3S/JqT+aQhOfIjD1PombX539v2Yfeitor7qsWj1+ZAHKxTuEQ0457jzUf6NRJjbN3ayKBob7JspuZHXbnJM9AJsWxzz3toC6N1O6DmwOxM5w2Wi8uJ4nvdI8hYPI5Lqhcf3f2n4/BIxVx38wjWrw79bqUDleB6tTpodz4zQ+tFi3/tHHWSY2zSQpxSVs2K10lF++UDbN5hFc7pyeHtzSeJKQiZ4Qxv5r6RwFdFu8BrFDNfoIFH537d8U0JbSaPSlXQ8y9gg3X8vVb5dlwa+1N01zZbKtVyoM5Zq6psrKRfx5pYML3Qq0LSWhmBZxup54zr5s8xVT0orFkcrg5CXzRFPR6VeUUaAaCuvEqUlog2tMXPHJ32sGFri1l6sK3Birle6LQAQfhgA4VZaNlds47jBrc4IjzZLkw91PTa4sXW0vA+fWi6Z7AMuBoa30f1m/wKMh7YruYP2GoiJjLwn9jHlui1m+Zx96c+t0+fpjSAojcxWuikN7lG3Xj+rLfXolBel0/28gy4Y/EtPZc+qvh5mY1UASmO1rb2GvsWTDcpAuMm80ZGsvXTv8aqt2mDqgt5UPBWfHIGU8fNybdveR42qqwPVAwJ8kwJiO/YhYKyUnsisPDBIM2Z3kaccRxopt2Ut4avAaUr9dlLiMTL2IfZhOVsr5y4ax/w8PfAykwxI1/7DDajgBdVS47cdo+LVlEozG5aG9gJ9Yucu+jFZmROeoIlEjIJ1n/S9mTwOFDD2q13jAW7UQqnNuPNHIzmoZ8Ao6T1dRYypIWDUdyaW7EXRWDTsp2sczPQorsQxhVjEnOkWU8XSBF4GJXSd3MO6d8Pw6cgF0rNH9BA3dp3fOO/Zrcm4Ex0QEchMZrbl2qBzPQLU4cOeC2Hofh+jza2/Z8cTqapGrOu8d1C1sFPIHDxe5bYVVsbfmgt79UDZHNM/qL/JWTrGVAokBB8Lruu5nUs9GDtXpNgCH0D+UeLaQPbsyPO0YKW6gcMPW6nCAdsOlpn/b39Mlu2A69Yrt7MTvvPxSncHJHD52PINo3nZy6xIJvcCwT1HrRr7pWrH+xVAD3UhwOGag7Im82WXpoS3KhYhQLFcCtyEfCOXk8ZCaPf+XUdtmyxJqoGtqluhEfs9aAqcpsQyOvNo7RcNpeYE0z3H7btZ3OGbyhxB6XZziIJET1dAbx86diexViuGKRy8ThPbmSyqXOrCiC63xNmkYzPH5acBZje51sh/u9geqKdtA7fxP8rt4uax3qgSJBGv71o6AskSYAl7Qbu+MgFtSxMV9RdccTSUEDBZJPAygxLWR4cepKEjBHd9YisaSZJ47k+kh0ko2tsNnR79cLSTdtPeMkHO6M6TjUVgAUrK8131QIMV8NRmLIUNJSwL0eZc3S4sia4NF398B8MM3eRWSfkvfKkqUCaAkDYwv49CUQullKMaN9lyuZY2sj7I7+oaZ27lzCb/7b2h8INqMPY+d8joAiBVj6S5LoTR9/E2Z7cVXbOOMb3oSgw8NGnwH3M75VZptg+yxonDNYNdHbuOF8LZzmz39aDRiOOnK6DiRV0xHPEaRQuwzmbVGgFpPQtW8O+ai1azWnFqfIV9aCh15f49k3rerTi9w+vFdBU7YCRLabhawaVb6/qbJ/mtrVkj71uFcXPiga3S4ryaqJAbIUfPLbXD0Uje1HSgOxvoya3HKeOiilIkhny2xG6O0jJX/9LbOQaJxedYYC/cOq9RapId9exIgE0cetiOdZdeZvyhoKCGqzhBEb4+EJT8upWnBcmFkC01d2zXw5UaxkvRV/DAd3HBJemAOZlSYZcFEjPi8AmxOMS7GBUrNmwj8lmJMz8/wLl0hK4e/JT8qgK7GtOsALZccXC1TEHGo8kV5xg2LhV7CX3eS8Sw1NrguPs0PyTEIKlReCeR994R9VPY83XICoqZXE0czHr5NZpSm7HKfHiUmvgIVJPzrOZ3bMx+S3Fv3TBg7+DRYjU7TJ5G/JIx8de6s+sro+H+w090sLQzx4f+uQIGdXdA7hNnzdV0BVjFwmcnfTrpEFEXTf8PqnquQk0XjIGi+7g0jcY98InnCVG8ds6DMtQfPzc5fhZSP/gjGjtdo49jij0/fk0fMtJoFobczgZvWfbnICYRF/Qm7XMzA6kuAWZVaa9lpR76Fy6XgIyZezT3HNBej0SwF/w999TkrbB8+vM39nZbDSciFoDxnPgKPfTOWhsxD0NC7oiqiVCsoyaJCmu5NDYnlUgupRl24p5AsVilwzF22FEpVwRYg5Xi04wVnqhMs/+WukFHSHchQXcLRB+FquKFbsMd1ln0nosOT1cw5umABhgLrCiQhJ/JT2FLugvei0yl4LuqPzh2NJPNZiaZxzD407s1S9fFE7o/w5axQWqfht/iPaPMo8h/gCGg8WPm5cLfsEmriYDRvtr04yDm06W2H38O12XnoY377o22qvxfWccitdYI3Rvmo7LYxRfC0M2QOIN41mj2tBWMqlRinrEZ1hKGrxyfjtyzqhV/dxCIYCemFUhJ9dD22T1wQXexobqLoLzfJqZXszIFAAQs+9NUgmsTSLWSLqiF54roJ5iFi16Q2CdYDmNULq/5M+UJr3in6HFyT3FXPoHIiNxkfRe92TA6tVItfzhSVdClFjJoUpJn2NoUXisZP8lTck+Z23xwOltvrI2MHisNG4IVFjeKbOj3set/EfrvGeufyclJfHW2VrdXYZ7iGyiIjGgchmMeIfS3xgR05oEc/307Gn0I5Fa1BQJkRcIINXrh5r1r83tm9xs9okySwDyL3phDz/QD6/v+B/Y4deHmZfu6CQXlbXygLP6u4J3yTvqAPER0eE/1fdpg16+5tTFf3nq6eug4GMmOCQYKgJ5GLsGLPRTVRmJkXGgdj7D189iHsfYwi13QOqaELZhTeWQY7QCFDXdYYLjPhzJp9FwMcjkdQmSjHeqLeVVW9ABAdVu5MFJ1EL1e0qebH//V+X6TBnAG+03udG5dQ97i6o2Cpf/LkLls9GEyszILXyyEPEV+hbt/ocoHnti/L1YSlUPi5PuA8Swe4sCdk3M8cg+aj8OIHoU=
*/
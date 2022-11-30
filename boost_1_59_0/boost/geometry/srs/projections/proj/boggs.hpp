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

#ifndef BOOST_GEOMETRY_PROJECTIONS_BOGGS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_BOGGS_HPP

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
    namespace detail { namespace boggs
    {

            static const int n_iter = 20;
            static const double epsilon = 1e-7;
            static const double FXC = 2.00276;
            static const double FXC2 = 1.11072;
            static const double FYC = 0.49931;

            template <typename T, typename Parameters>
            struct base_boggs_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T pi = detail::pi<T>();
                    static const T root_two = boost::math::constants::root_two<T>();

                    T theta, th1, c;
                    int i;

                    theta = lp_lat;
                    if (fabs(fabs(lp_lat) - half_pi) < epsilon)
                        xy_x = 0.;
                    else {
                        c = sin(theta) * pi;
                        for (i = n_iter; i; --i) {
                            theta -= th1 = (theta + sin(theta) - c) /
                                (1. + cos(theta));
                            if (fabs(th1) < epsilon) break;
                        }
                        theta *= 0.5;
                        xy_x = FXC * lp_lon / (1. / cos(lp_lat) + FXC2 / cos(theta));
                    }
                    xy_y = FYC * (lp_lat + root_two * sin(theta));
                }

                static inline std::string get_name()
                {
                    return "boggs_spheroid";
                }

            };

            // Boggs Eumorphic
            template <typename Parameters>
            inline void setup_boggs(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::boggs
    #endif // doxygen

    /*!
        \brief Boggs Eumorphic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - no inverse
         - Spheroid
        \par Example
        \image html ex_boggs.gif
    */
    template <typename T, typename Parameters>
    struct boggs_spheroid : public detail::boggs::base_boggs_spheroid<T, Parameters>
    {
        template <typename Params>
        inline boggs_spheroid(Params const& , Parameters & par)
        {
            detail::boggs::setup_boggs(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_boggs, boggs_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(boggs_entry, boggs_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(boggs_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(boggs, boggs_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_BOGGS_HPP


/* boggs.hpp
UhU1WDja2RHpSEjQMtbadck7hf67X2PrDPkbpAXo8vYPNNMF6ADSCTswesdIcjeSpkHXYdcwsE0VfQnESDd9YYRjo/oGI0sQoSWAUO7mMNMlyXshuggaMO9CIIg38XRk/weaISwy6PTUpWTQtRrz9gi4SjvYYelgIdThCQ80/pA5TBlQLDs00jmhU0rLXb3M+7a72iLn7MONJzq9o7/4lxT2QGJBLeNpHkQ8ww/Pz/LnXOjC55EKPUzgWtLaK1uZXDdCDOUglDpJTGmuE2Bm4X2gDY988QBPDyc1xg9YX0wZkLCDbTA61GIJ416n5vcHcSGsRh251JtWSg7omaVOSHXQ3s+5EoBXkrq9EvMdiju9yexOz6yskSwC/LMJkCGzVrlH0CfdErN17yojvMxq2wACv9It1np65GXAmvC7sG0jvMSnPP1NTlsDf2NtxXCRUUm5osl3Ko0AOSyGUjRZyoymws5Flux86wKgbaRYshCol+Ts0LwSOvM9DLg4BSx7PyTOj3glpx/KzA8ClWQpFz5Z2LXfYj6K5XlkpeTEizGoRxJgcVxUrmVUwU6nnN9PerySIzxZXSnZoikA2C6YGiXMaxesrTY8aMZH+XrcLSytw/vDkECvHwB6QdXldDrSAUimb9vHu4bLr0MO9RcWC7vKG2jt5bYVwN/ij/rh3vWA6SOkbQ+S5SY1zbp3ibmWhaVFfyjVXwXZr34tOUbnfQNKbEGFdlh/eqx7t+Khfy3bTGLGHMhIYuT+tTg4XmMeyc3wS93xJOuutWQHO2jBK48NZtjWABKtj0AbV3FcSb03Oo8+VIKm50Dnz5Iu2uwKi+YpyJOJymFofvR68nbNuJjFMPZCWt2FLdsb1mCcAcG/beDnCddqB9UWCVEpDwT1F/5Ii/QCvFmDoS0EPD1CVJrsJJyJ4wqnrFfKt+71OeDbTnwSfOXCjIYvh+wnQbGWCGqFJJOgGb4aaoF31sJDIzxMJcfwsRkebbVQMXporyVL7EqHo1bdIzEeDK/x7C7SKMk4Eaz7g+nW/UumWvevEq3777eYDkAG7BPAcgcTG73SfK3eaXpDfUpCMgAcTFZ3smZpGbkwrvjobHKa191E5ijfcpqVLvRiDgyXH+JHcmpMvbdVO6EJTsgr6U49iyUntT+JrqHavguzBCpoQ8grpRz4zIdPdq0bSCBb8tm3tfVF7IbUSNGQ0oVEyoMG2DxvWLez7km17q0xK2slW6rSlQqp3q8ZBMPW8CKCP+bjpO6yBbBO+JlD03/4ucbmWP5Q6OPl8w4ZAFRETjUAx4XkaHYokzaXgBzATnozSYXkVZkPmyI7zAKpVq0yo/Z7kQNv4ZCJsClt/R4e4wPYPFfvbT7nNkB6RGOzxYH8OMJpVurHrZGQTtgBoRm+0asoYOYPICR6bz1eEBRLds475h2y7j19off6Xpj1Ra7huT1dLYxOBlWWbG4ZunDn77D9xVJWyEDP/Y2HevgZdiHwEmQTkuswZ0xAxUyYZ+y8uRzH4VPYw9pdLi0Y4UCxu4tJUV2QnkUXqVADzLRAyIAKH7eCVDgDj6IAZIW2QdIy9uDZEaCsbt/Dq8uMPIYM2k8fmItBCYCSter2JznDmK9uf4o/ZatMtxlI5hTkdIDm1DJewwuIYbmUFErQklzXsGooBJIU6Y0V6LnvMMpm4m3EuzejpTTZyeeRiu4OMXDKCsIJ7DpCW94EtgDcyYn15SpO2DFGX5hgJkCWmYO0YSHeRMEifPd9GDLAIujWSOax8mHvhyAf4pUPrV16Vfnw3mmQ9m80RUg6pX0aVRlOf8gPPQa6U0fYoUd3odm268EG5ozDzrxyiGqzo7swM53FS0aBxIh1eLplsVsY5Dv/dj85qhY62cXMG8gz55DwAFnmdGmeY3IqY3AAztn25Tp2Kz0AQoqdpoz3NeaIn9ikBujxbw9p49yYfQOVCD85lzikQXy5YzwncES9Fpjc1F0wrHWnYivoV+CRPvfhuKoeEV3tUQdZJjJeakUhwMAuMFDvEFVg+sbdPrBbGtxr9SyBjl4sRqdE/Ogi5GP3V3VHHB/DZ24g8oiZReHd8MtzGuqlTnSEk6x4n7x9SqFN40HfGQftOlGDqqSwsaHZl87BrulecmDC1Q/9ssBk+eIJBtKYaOOJjyYn1v0Pbti24oZNXj+ksV1ZrFDT4icq9PZv4Vs5rVtoB1InlJihK16/d3sDrf0gRQhJ1Ay5xgy4FPozEECp69z4Dtb75MeLh7W/E5C2tDxue493Rwnz+2/t/5z5u5kM0m85zW+Ncnc3n0QX0+3743rbC4NaiVge8Y3QGzFD0wh3gvH+03qXJPsZYhrchWL4zbGxT2D7qeP6v/nDWrIa4KhLq11f5NJKt4kBqRMd8bel5Atbo99Rq2PuGvOGNbo+TPH3H2zwq9Uj2jQQ7D2djQvcczB4A17vHuXHYNGuoEvDIhlkJlOTKddyPse7wSWeZvO66CptkVqjW1JB8nJ1DhRN5UWJLxY3b4VZvgln+fn3U9BPlXIrO7h2teNWKz/5cOSOJej4LjU6DeRo2nOvprX1PMymqqjcLUAr8CgvOgl4A8qirnYa6EsZf736qetEkFzEIyje5sXuSlEe8hyQB8uJA2/nXIfdAQnmmvWJjkAwUjzJWOrXym2kp1WTpytddjzFZlaaXTn3Lw9/QjpR8z+J9LjYhdPrEDZ9L/MDrdy69y8d0am1qj/70Uqb8r5hh//ORyvtapWTVDt3+F2k0qFW2WEcqX4zqbSgZoqkFs1n3nC4WxyH6s/qzs/EJq3wXJTT4Rmj3uIoqcz0vCWnKUWZsJJaxoT6K4d+IT2eCzxu04VOwSmghnAq8MMNsGOoh6Ui+rB1byfGNV9RJH8dQ6vnFcn3KnRzuBIvXo7Jy/DKFEbBShgFpZoN+71bdhMxqC2C/tN/36aPg5tgjL2EQB2sjun6axHJheuSejfgANNbztj2Psa/vHAShJtJzMzuOKzeq1Yk3IiVB7UNdvI1fIu6uQ5Xr1pjxyeRb1HVGgf+sqk1IlPbVWvg0ZJ8IhKpRFuS10RBaGmXr4MVMQOlw/vtD7dnw3oq2mvV1BcMUeOd47wXYbEu2sqLTcciy7AIlDCbCsWrOEYsZ15Y3Kss1u17WZQkdii2BLZeW/NEQ/hukBpJhcNGvA4Qp8WI12hSzo7Apgb/54kmeR1mkE1m0yfyP8H4lR9EYmG7YQJEKyHRutdrsiuxKfI0JTZJtrDsDrNpoxi9/dqwhfDMeGbUOYdWO+z0fbxMZsGQlM5szxKL9V8wMvP4aErJ4/em2SAjVIqqrRZGJh/BdjZ8HWzgwth0gjAXH7DmcWNWLcrMLXHCvr0yUx++MMQ9n7DxalTrRRjLfOg2WMbemWWP0RQGqd/VSz6H1bTpFLCqdDZt+9HxsueS/Clyqp6yuqc4p+pBTnXG1f6b37irzzRuJL6ekFEN96nVx9XqsyvUarqvZdGqhkjTwDPPRCrPlkUqj5fBQ19ZyPAMG7AWKI3hic825OD5APGjsZuRnPS8vn4GsVn3V9w5nzSdUu27FsP0j54lyKTTS3mnQSl//KkHTyLjbO5MQkHvzoMpoz6dQ3VtrXgXcOVvKbi93rcWmhBp2vkMnilbnrE+0f7MM12+j5mCAG8y5BPQLexZVMAqOVvK2LMaHsG7JpvqO+TpamJXGoCIp2u0+kP9z6RgHGsaWW+HUWZt/R67GDwiREqOlNbtBBhMrQaBoKbDptu4u9gjo03QgSa1qbu/FL18+I4A+csdZYFIuaUMycfCuLLCw5tmoAg9C7OxMv0WeOwqyMTNtUXnDmb4bVAe6hGA0eeg/g0psCSz+/zFUaYytVz19aCi8Wu0L497aG47/gjyfVh9kdbh6yegyJaC/t+Y0RTwIEagRdurwXxcPgpsuhNw4FUlbfTxPDzlZi/abl3HoSqbbQIePfbEj8l/BvWovj503HTcs9RiVZahq4UCWxesNA8fziYFdlMH8aNOuKdcsm5HRw21SoN9irXlerzMXOpULhrDflJClQ6T8t4I+UTpSINv1wnVb4PCKiT4qNnkOwLbhIvWl4tmlZXC/5mlWr3NurfIDt+iWnmK+PpoEM/dwqf6X0QFvIuGcJhUHn8FOWrtJNhXLYXN7pFur8GGzSFLAb90A1lvNw1i4BJ6AZEuoSRgixSLWlFIuHB87qHSiDfdpJacsr68bBZUumxmqXXvMjvwkUhDmvLhSFkpcF61ieGnNh0ig/24P9va9LEQ9qGG6HCk8ulIyVPdvqdUdLHp+zmGB1XDT6vhZ+l8wNUdflpOY4M7mu4OPytb9jXqA/0ZNsCh/88IITt0URr138PiipxJ6p+X6CdfHe2frvV6/zSdEWBX2nQcFuUMEu6ZuC5r621kIbPveFsLH1S+aRO0t5f3u65oWiS8E+YkbGciDWbiO/4MsHjABCgXmvIA7PwNSMQEBTfbTTHVdwQ2fHaYYfRlIydg0KaFzzAaIgWRgEiv+jTl3EiglNHyfqTl/TNLy9AFR+UhEoO+gznIqBhup29d0LT+hYCNda/frnw+JfzPCTJMovfdPYEML9CP3KNkeFNOIsMtjAzWlnSmg3gVUvQPQj37snyrGlhsx33b8AjD83bYpOXb2MB9hZ1xuIvs4XRSZEORB3g4Nr0p0fA/Mj1jGoFtGrnfhq0ejHgXYKtDQsSfpvz3SJlayVtX2W59OTgrUAb/Z5ZB00uRAth8emYYb4COQJ2Kry9HlUUzu8bKXNz/Szx89QjhQDkd/AyPkQ+1tm8qAMlys2WDY2yjlkCrlns2W9b979W6WOcDy5e3tvdfxONJU1e+2aB8E68SKBB3Mh3IYzxARBnyebonF2TIzA06LykQWeTmW6Fa6/ZXL4+n52jV/T9hpr00hEaPx1m8BwrVai7UfKjsobs/w3sE5aAd+OAUwFOPObvZthwwjWvIT+CqXfSXp0e3vlsbMoVAUL6F1FtcGggxdpJvJ+lKu+gWZcsSpT3bc2Xd0J3t0RvUr0ZnEZj7j6BBNUmPeLM1z6GNH8w7qqa/YIhbNT2HLEI2h8xVnc+hLBj+7DkmjplDxqpO695DysWiLbPks/BrHjzP2JimSZEVG7c0hMSqzm39zDrQcZ+ccZ987D5UeoFc8uT7ZPE+OSUK621+5wOQ16h/XEkfY9LngaR38fSg/omXj/+Ob3G0jZZEJ2+UYA4vH3WXvhz3DPvfQW0DCzv89gdLVXRs4+DHAnrXbNAvttl+IkffT+CRQdMIX2ZOfxWWmYN2tdASnYEbiy2LYFAsaOAbC7TGsiRtLWz61uLSOynjI7kxhyT6tqKOiNxldGIfpU3D5bVhGu5U5gaoeB7vT2C91c0NEktrdD5JxUELoi+kaIvIMhsJWOjXzrOrKdhELU8eMqvi0XPbduwaY+1SztyXFxVc0pRl89FGxaV1p57axQxU1OYsFilbD5zNTxLZqZPa7FebK9TmKrV5pdq8Wm1eozbXq82yug8PMtV9O9l/doa5jx1h7nuS/X+K/f85u/pTYIu771n2Ag+Tu7fjfQ0T//YdZL8Pwf8jux9s6N5+BJ6G2NNxeKp/HJ9OwdNT7KkHnl5jT2fg6RQ8hWzd289iGXiO/BQN/YPd2/sw0CJQuLx7O4XHHHiMe8WxoMdoE3MLXf3/aEobsrQ1fw/G15f+zE9yKKde3IimEA+NumURFQVNasNa8lMkiudd2GO9QX8yTxDiBjPkKHXOwJBJqyOF+ahwPtOKv9aQo3VDOasaaBr+fBnpCm9yFsCbz6Yi/JVM1ZarpTWvJIUViV2VHX7EEypIYVVyxipS6IffcwgGcAB5rNBPRNR3K3WwR57JH9n+PDu0ZDs28tM9HPMvk6UO9bE9XFsMgGS4mTGQPCV+/h8s1/zmeLvcrM/lmwg7m4Tss/TsVrKVZbcFA+SQViYCqRihmmXZpBXJaGRWOVAWYb27Hy2AgmgAhLhNa22HPW31AH3Ab2Q+NTHgWYR1PuYxJ+UZpIv8zEjIRHyDo/OByZB4yxh/EXkMhyA78Js6zSCQ7TjI0RvK2SmJYNel+Zc0Ov9U/BgolNlW9Th0/FdOYseTZbnzlmWTwrx5hTlqyQC6Te/B0GxfPWMWeEDIAT+8ommD6LPDz6xOnujg/l9zYMaK2FjWA142/Rewfki8LILmzInDqGIwsk2+AbUwF4Mb+wbVwjxXO6zuP2rnmuM9ZJDeA1XDWvHdk2MOrsZtm2z6jXiTqPpgaXKg7TEaO/YxY0c0PzobNz86y8yPJGZ+1MfMjzLndYCcS0pi815XS85AraWRkuNofQJyOK50qeVBchTkUc1fldjbBPZONL7MGsWIRdaDpdymNp0hTZmwn0Qj0CbYy0jkOrWphzTND2rhLOUhCit1T7evj9vBOAE9ELWg6kAk3BeATca/Hkk2+Tz78lVNnlBXcdpVbZ607x9JNnpKunzyZSYun5SB3OS7Jq9UxC+ayGnGR9XNktooOeCTCSM7VS3IUqvW0l/NPq+521YDowvPoCceNSTt3NDPObdoIm/Ik8kMv/Z95HJRO9oxmeJ2TBZtN3JBvLHydFt3howsMOZmP2wFQShJoaY70UZJwjuugvmuds8FliB/SHwwwcK1wUixlEP//bRZiFRIjjLAroIUxKd/ETTC4Wc5Pv0fdP1ENpjxJskEr1VZktitmVfKNHXhRU9kc3ZElpwooSvFkl+Dctn0EECO3oYeTsVEcSxq6jC9jcXVijEFSUF9d0GdIJgELmikwS8D+2XGX9secoAE9TEpqJvrc+BlqUEtWCvPiyg42/2RgnwMJP3dSUCOgtURBXmFn/FLeLuGvV0TUfrYW+SZ8HYZhh16Q1WQk9Jc3CRh4yObK4J1p7hWMOydkbRd1p0KHon58BzfBntRUyB0ibyh+ddEK8lCtI5oExRN8wMS2RiawBQS9HQsDvO1kL26nPzK1SY0AS7xIlYyDZ+YZUW81sZppMAJCFbV0yvp0PfVrmGSBvv0uOrxXdr61XqzMS6Wtn4NeYOvEB/gzxfZCvEGXyFOYsTYAr+6frW6fo3KkziU9X63LNkbFwCUaosguMN2VNi3ExNgy9XlgRXMuEUQtoqTC9YG/AF4//0d+m00KYaBnnQT9EH1qDFZObOOkIJs977M6Vc6JHrP80DlVLQ71nY/y0LCO8lib3Q66SHHId8c8l2RCO6NZvk6mAofQU4D2k+YV7naa/JXdFLXHRghSP6wXOnIp+v/TUMrzl0HUYlD33S/PcbnBnPx0A4LFot3eRdGj6jzwvIRwJCFooqpNjx8iXmuNFaxGF42Itatgb4PsKUQtiC2qBvddtS15IwWG0kqdhMrNsIU1HlJLJqJRUfi4tmqmglaE8A8bqlsHb253pp0c+2VGsZeW+9OXFsjQWHBwAP4uOWk8yuwP62Q7GV15kWrGtSVUiZUi5e5uO5Zd/zCwFjCSsmOU79TPhZhshRUks3XU3bNzRZMvNplc74bEvP5lXAufCrgsxo+a+h1QSNeFz/JpRmAto00OCEl33PJ2oLut0gazHtHqfbi7l0Ymzmg7cawLbX6lSNR9sDrSV4pX+kUlUv5647r+evyYW+EljgsO4wrJ3+NBnkq3oymXSUx
*/
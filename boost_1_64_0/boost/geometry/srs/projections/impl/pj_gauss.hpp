// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_GAUSS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_GAUSS_HPP


#include <boost/geometry/srs/projections/constants.hpp>
#include <boost/geometry/srs/projections/exception.hpp>


namespace boost { namespace geometry { namespace projections {

namespace detail {


template <typename T>
struct gauss
{
    T C;
    T K;
    T e;
    T ratexp;
};

template <typename T>
inline T srat(T const& esinp, T const& exp)
{
    return (math::pow((T(1) - esinp) / (T(1) + esinp), exp));
}

template <typename T>
inline gauss<T> gauss_ini(T const& e, T const& phi0, T& chi, T& rc)
{
    static const T fourth_pi = detail::fourth_pi<T>();

    using std::asin;
    using std::cos;
    using std::sin;
    using std::sqrt;
    using std::tan;

    T sphi = 0;
    T cphi = 0;
    T es = 0;

    gauss<T> en;
    es = e * e;
    en.e = e;
    sphi = sin(phi0);
    cphi = cos(phi0);
    cphi *= cphi;

    rc = sqrt(1.0 - es) / (1.0 - es * sphi * sphi);
    en.C = sqrt(1.0 + es * cphi * cphi / (1.0 - es));
    chi = asin(sphi / en.C);
    en.ratexp = 0.5 * en.C * e;
    en.K = tan(0.5 * chi + fourth_pi)
           / (math::pow(tan(T(0.5) * phi0 + fourth_pi), en.C) * srat(en.e * sphi, en.ratexp));

    return en;
}

template <typename T>
inline void gauss_fwd(gauss<T> const& en, T& lam, T& phi)
{
    static const T fourth_pi = detail::fourth_pi<T>();
    static const T half_pi = detail::half_pi<T>();

    phi = T(2) * atan(en.K * math::pow(tan(T(0.5) * phi + fourth_pi), en.C)
          * srat(en.e * sin(phi), en.ratexp) ) - half_pi;

    lam *= en.C;
}

template <typename T>
inline void gauss_inv(gauss<T> const& en, T& lam, T& phi)
{
    static const int max_iter = 20;
    static const T fourth_pi = detail::fourth_pi<T>();
    static const T half_pi = detail::half_pi<T>();
    static const T del_tol = 1e-14;

    lam /= en.C;
    const T num = math::pow(tan(T(0.5) * phi + fourth_pi) / en.K, T(1) / en.C);

    int i = 0;
    for (i = max_iter; i; --i)
    {
        const T elp_phi = 2.0 * atan(num * srat(en.e * sin(phi), - 0.5 * en.e)) - half_pi;

        if (geometry::math::abs(elp_phi - phi) < del_tol)
        {
            break;
        }
        phi = elp_phi;
    }

    /* convergence failed */
    if (!i)
    {
        BOOST_THROW_EXCEPTION( projection_exception(error_non_conv_inv_meri_dist) );
    }
}

} // namespace detail

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_GAUSS_HPP

/* pj_gauss.hpp
ONGHhDpreovbNM2/4J6dG+f/TDBfLxYoPfoLwfz9+suKh7df/w7I4QpOY+BVvNZ415dLmraaEDtKrVt070/1+yY+CecOCWXH/HfCP96tHSln9zgPrejYlQD9nN/QSOuzGt+fQeZAnIV1gGVwsgbizDlqVmOtoYH+AT6ivO0LROY01++NO/v6l/m+CdIAqbNOY/eR6Im3tCf7l0dTvTxE4Xi0Dcajf3D7OWaEaz/7RKSfC4SzVThThb9E4cnp+DpgEl959rmSCOHpX8DT52XgfxbCE71Byk4krWGKFF7F8R3rEXum8smg386PlJfmzchoe4urB942hvCAN1b1m2DxaHtbd0L8YMGb6FN5jB5J+ft/uw2z/rCPixHf/htE43we2lN2EaOIfraJo6sg/ZR2P7YzyoZ8V1p4+3/YOw/wKqszjp/73YCgqGGIiAaiIlJUDGGIiJoNgZDEJCBi6+WS3Ay8JCGDYR3UgUhd2CpqHdSBe9Sqte6996p171rrwlW3/Z3znXvuez9uIFi7nqc8D0/uGd8Z7/m/47xnzU300IWobYf19c9/w9/tXdpUlNmrG2NetRG06zBlslWiqc7dZ5adoBm30ZpBtvuhtO+lj2hLZjexkXKvsRekK6+jR+MNmrQ6bgtNVxvXLui6pah3gke6oKsLUZeUbysHrOvr2DGwjtePcs37JllifSvonwjMw7bKsrJZyEJ5x2i2/S9l89ZZgbvLha6XOnKbLNtmka+HzEObtyWPnIMPsPp4ROBNip2Fv39oVqq/P5uwpNX2hOV5m9sD+2F3FOl86/Qc+Uz6TsTJNo4V63jSlguuRY4Q5eqygnbaSJE+krRg+q4ifZu+ad5LSaQLf7Vch8gh3bxdrnxaSbm7A3R1c9/AHkviTB5Z1zjKsvntPNQPtwrb2bxxZveCO3suy9pDgqbmbKvFpu63zD8pkJ90k39vgbHgOwCS5vsGxr6+rzy/lX5uUZAl54bp93QU2fZ+Z+c6sswSqw9k/smizATPtAX2lJem1uvyyTzTyONwrVLvPp0u+2rDZv3L8oNOq8xyaSk2ziFu3m//BvbnVgXa5mgt2lYT4Hv7xgXYCvglRVk9+qYva5Zt+9+D9LX2aTD/gRbbGVYvm72Sot8H2X5/s5XdW72dC6fQYUTAHo4NTKVD1NZzs5A3tQF5U2fHYUc7DjHC6e2N6qrKSGc7l9e0LnJbKAJx1t5oEP1qzEqeu2jKSp1rz8vy/0tePdjSMm7zjuqyLQ3lshUN4r3d5mQf9W/XltZA3xfYulssvdts3e1Z4p2/wDedWYH3mO03i2y+ietrr9kC41ot41zbl4i2LxFt/3mgHYfadhxi236YbcfhNl+V3JNp7RbCyEejx5X9rd9i1r/N3GyQanC/s1W5u1d1hNIGg2+HEvSWCp2f021cWCyIPhxp+9Bp+3CU7cPRgXwtAZovs/mOtfl8+ogzaAGcrcjS/wN3D9oyjrd5R6ajl6VFL0GXTOgyytqyJwo6DNoAJltF+04OtG9lFv8D7TvFtu9XNu/wlPbNHT82Mrc5dUwJi3uNT5X2YLfxZ98MD9B7lW3L6Vmp8g16uP/SF31moC/B+yRuDJz5OZv8Ip0+BnyngfQbA7bGbwPphwVsjfMD+n9OSnuDZ3WDZ4NdH50vvDUwp75Y1E+6oIdf/6UB/d9D/Je65nInj+Sd+54uR+7Xct9elWX+u/bJNl3t6nTpgbHy67yGfGI8XdlyPK91+jdYVrBMv+7rs5z/YgN5e6gbsgTtfZ+Q48VFvuyMLozVVY3OUWsTcb0ScaPV2iEa79DmphS8F7aXsMdJ33u9zK2TFy+ujZlbnQtbmrlgszNWvDg=
*/
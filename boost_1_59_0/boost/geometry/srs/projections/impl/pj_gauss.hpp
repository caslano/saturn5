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
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
*/
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
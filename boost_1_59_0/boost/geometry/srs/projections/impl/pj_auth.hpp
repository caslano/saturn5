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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_AUTH_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_AUTH_HPP

#include <cassert>
#include <cmath>

#include <boost/geometry/core/assert.hpp>

namespace boost { namespace geometry { namespace projections {

namespace detail {

template <typename T>
struct apa
{
    static const std::size_t size = 3;

    T const& operator[](size_t i) const { return data[i]; }
    T & operator[](size_t i) { return data[i]; }

private:
    T data[3];
};

/* determine latitude from authalic latitude */
template <typename T>
inline detail::apa<T> pj_authset(T const& es)
{
    static const T P00 = .33333333333333333333;
    static const T P01 = .17222222222222222222;
    static const T P02 = .10257936507936507936;
    static const T P10 = .06388888888888888888;
    static const T P11 = .06640211640211640211;
    static const T P20 = .01641501294219154443;

    T t = 0;
    detail::apa<T> apa;

    {
        apa[0] = es * P00;
        t = es * es;
        apa[0] += t * P01;
        apa[1] = t * P10;
        t *= es;
        apa[0] += t * P02;
        apa[1] += t * P11;
        apa[2] = t * P20;
    }

    return apa;
}

template <typename T>
inline T pj_authlat(T const& beta, detail::apa<T> const& apa)
{
    T const t = beta + beta;

    return(beta + apa[0] * sin(t) + apa[1] * sin(t + t) + apa[2] * sin(t + t + t));
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_AUTH_HPP

/* pj_auth.hpp
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
*/
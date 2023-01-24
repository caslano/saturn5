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
gDY6StPlSJdS6yqls5hMiid6uSJ4QohAZ+0ZZlRJkIQTnMwUWMdzz4czFufykZSq0/35ZpqsYbZkcT8XxoAcGD2pftocVDyBNPITKkPIWtR+S4NytogF1sP5qSz1+jPP4652iywTSBplbHEUOnEd5vcICn/sS/AmOyouIF7l8Mt4lKw5mGDYqcyxjDppSwY7eYJFlYt59iWBsirvUgRwBCokpWfUvH+Iv0sWRXim+7WG6haX/agjMWFZ8ZXXajPdPlDt57n+foOyuGzc3Jwq6iVa0ifOSym2Pq/NeSVEIsaL+ZhmSk3cLESib0UiNraZgL9MV2GlYjn6TWOpt2ptdZnDwK9od6lKHKP5xuXYymmN3QC8123V4sW1uDzuvjbhvsapleBU9EPBszAFeTUyYs8S7Ncxoq5cU+fuIOxMzjvctJ3wNzgvjvHbus/bJ9nHYFZTZM8vC+5j1+Fmt6beKc+p1en36n668YTAGATnL/VvkerMDICsHSlgxrq722w6GUlXj4sqHCmivh0z8g1I8F5VXMr2hcI8qEU8K5RjVhvAnh7flKdcG8hXalkHTwFkckcmslFrmSPjM7nOfCzPX+oC8j7BiO3Qic1vmK1U1PqjFH2lHc+Z1PeLbegStYWhKL383hmfqYUaLUeX7lknqHmHZiV5TWA9HAYuuvBhsu+XziyUoJLCfGlWX2So3juvd2SCpA9Xt42jaysd
*/
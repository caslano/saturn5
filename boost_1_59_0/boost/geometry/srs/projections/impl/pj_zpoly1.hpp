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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ZPOLY1_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ZPOLY1_HPP


#include <boost/geometry/srs/projections/impl/projects.hpp>


namespace boost { namespace geometry { namespace projections { namespace detail {

    /* evaluate complex polynomial */

    /* note: coefficients are always from C_1 to C_n
    **    i.e. C_0 == (0., 0)
    **    n should always be >= 1 though no checks are made
    */
    template <typename T>
    inline pj_complex<T>
    pj_zpoly1(pj_complex<T> z, const pj_complex<T> *C, int n)
    {
        pj_complex<T> a;
        T t;

        a = *(C += n);
        while (n-- > 0)
        {
            a.r = (--C)->r + z.r * (t = a.r) - z.i * a.i;
            a.i = C->i + z.r * a.i + z.i * t;
        }
        a.r = z.r * (t = a.r) - z.i * a.i;
        a.i = z.r * a.i + z.i * t;
        return a;
    }

    /* evaluate complex polynomial and derivative */
    template <typename T>
    inline pj_complex<T>
    pj_zpolyd1(pj_complex<T> z, const pj_complex<T> *C, int n, pj_complex<T> *der)
    {
        T t;
        bool first = true;

        pj_complex<T> a = *(C += n);
        pj_complex<T> b = a;
        while (n-- > 0)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                b.r = a.r + z.r * (t = b.r) - z.i * b.i;
                b.i = a.i + z.r * b.i + z.i * t;
            }
            a.r = (--C)->r + z.r * (t = a.r) - z.i * a.i;
            a.i = C->i + z.r * a.i + z.i * t;
        }
        b.r = a.r + z.r * (t = b.r) - z.i * b.i;
        b.i = a.i + z.r * b.i + z.i * t;
        a.r = z.r * (t = a.r) - z.i * a.i;
        a.i = z.r * a.i + z.i * t;
        *der = b;
        return a;
    }

}}}} // namespace boost::geometry::projections::detail

#endif

/* pj_zpoly1.hpp
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
*/
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
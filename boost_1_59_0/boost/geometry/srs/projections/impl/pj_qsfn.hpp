// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PJ_QSFN_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PJ_QSFN_HPP


namespace boost { namespace geometry { namespace projections
{
    
namespace detail {

/* determine small q */
template <typename T>
inline T pj_qsfn(T const& sinphi, T const& e, T const& one_es)
{
    static const T EPSILON = 1.0e-7;

    if (e >= EPSILON)
    {
        T con = e * sinphi;
        return (one_es * (sinphi / (1. - con * con) -
           (.5 / e) * log ((1. - con) / (1. + con))));
    } else
        return (sinphi + sinphi);
}


static const int MAX_C = 9;

template <typename T>
struct AUTHALIC
{
    T C[MAX_C], CP[MAX_C], CQ[MAX_C];
};

/**
 * @brief determine authalic latitude
 * @param[in] phi geographic latitude
 * @param[in] a initialized structure pointer
 * @return authalic latitude
 */
template <typename T>
inline T proj_qsfn(T const& phi, AUTHALIC<T> const& a)
{
    T s, s2, sum;
    int i = MAX_C;

    s = sin(phi);
    s2 = s * s;
    sum = a.CQ[MAX_C - 1];
    while (--i) sum = a.CQ[i] + s2 * sum;
    return(s * sum);
}

} // namespace detail

}}} // namespace boost::geometry::projections

#endif

/* pj_qsfn.hpp
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
*/
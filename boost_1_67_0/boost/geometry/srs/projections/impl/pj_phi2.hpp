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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PHI2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PHI2_HPP

#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/pj_strerrno.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry { namespace projections {
namespace detail {

template <typename T>
inline T pj_phi2(T const& ts, T const& e)
{
    static const T TOL = 1.0e-10;
    static const int N_ITER = 15;

    T eccnth, Phi, con, dphi;
    int i;

    eccnth = .5 * e;
    Phi = geometry::math::half_pi<T>() - 2. * atan (ts);
    i = N_ITER;
    do {
        con = e * sin (Phi);
        dphi = geometry::math::half_pi<T>() - 2. * atan (ts * math::pow((T(1) - con) /
           (T(1) + con), eccnth)) - Phi;
        Phi += dphi;
    } while ( geometry::math::abs(dphi) > TOL && --i);
    if (i <= 0)
        BOOST_THROW_EXCEPTION( projection_exception(error_non_con_inv_phi2) );
    return Phi;
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif

/* pj_phi2.hpp
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
*/
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
hz/vkPoRzQ8n8s6nLFGLyPHQLIJKoAAUq/CgvyjPWi2Ul1zmdU0s+dwCxirJVB7N4fuKMj9Dc7vKV3gcC0jWpKxWgGaFpLa8Ny9Ac7xEM8hQLkp6kkmwWIbycali1gZlSv6ChlG77NrixcPS2ZNGo76FKWKG6EfTMpu9FvBkloDCGuC5Y1YEWdSBEYm+kXkwo0ABzeZxvLSwLMGtu2S4fNhdVSXQhbJfBHlo33PpCFablQqLM+43JJxj8m1kjk0QmuyKUPGL8Rk+GP/yiyG+5CtYz9Kga15bzLvaHORrWV/hUyygG2FKgXDh8mdO5YY7/uG771IobpfI5/iPf/zjDmY80B3IiIVvg4uogkMcot1qD8zmqDf4sjXuf/z++98H7jKgpZAABdbsRqs1IJ+LZi+f2lKKNdEENGUDziTFVazdv/tBNLxG+/S9/RgZN05MGEc8LRbbM0sPXwr81cIJsQIpDBig6MtL6JA8IIYiDwDcYCASrPDijKl2YYBptaSN9tt3mDyJ7oeb7MPtSrcIsidfDdw3aLvtnVmdXvccFuE7sUIr7n3Y7o5Ur8Mq66KI/cpBjLSzmL4iwQDI66t1PCoS0g3VC5dowzNHSZFL5JWLZIFUJpOx4wpELsrVwlvLS1eaFJlVlvK4zR1v
*/
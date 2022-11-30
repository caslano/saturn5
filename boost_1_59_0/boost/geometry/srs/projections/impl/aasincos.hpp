// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_AASINCOS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_AASINCOS_HPP


#include <cmath>

#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/pj_strerrno.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry { namespace projections
{

namespace detail
{

namespace aasincos
{
    template <typename T>
    inline T ONE_TOL() { return 1.00000000000001; }
    //template <typename T>
    //inline T TOL() { return 0.000000001; }
    template <typename T>
    inline T ATOL() { return 1e-50; }
}

template <typename T>
inline T aasin(T const& v)
{
    T av = 0;

    if ((av = geometry::math::abs(v)) >= 1.0)
    {
        if (av > aasincos::ONE_TOL<T>())
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_acos_asin_arg_too_large) );
        }
        return (v < 0.0 ? -geometry::math::half_pi<T>() : geometry::math::half_pi<T>());
    }

    return asin(v);
}

template <typename T>
inline T aacos(T const& v)
{
    T av = 0;

    if ((av = geometry::math::abs(v)) >= 1.0)
    {
        if (av > aasincos::ONE_TOL<T>())
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_acos_asin_arg_too_large) );
        }
        return (v < 0.0 ? geometry::math::pi<T>() : 0.0);
    }

    return acos(v);
}

template <typename T>
inline T asqrt(T const& v)
{
    return ((v <= 0) ? 0 : sqrt(v));
}

template <typename T>
inline T aatan2(T const& n, T const& d)
{
    return ((geometry::math::abs(n) < aasincos::ATOL<T>()
        && geometry::math::abs(d) < aasincos::ATOL<T>()) ? 0.0 : atan2(n, d));
}


} // namespace detail


}}} // namespace boost::geometry::projections


#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_AASINCOS_HPP

/* aasincos.hpp
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
*/
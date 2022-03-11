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
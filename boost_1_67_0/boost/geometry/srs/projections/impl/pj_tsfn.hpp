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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PJ_TSFN_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PJ_TSFN_HPP

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry { namespace projections {
namespace detail {

    /* determine small t */
    template <typename T>
    inline T pj_tsfn(T const& phi, T sinphi, T const& e)
    {
        sinphi *= e;
        return (tan (.5 * (geometry::math::half_pi<T>() - phi)) /
           math::pow((T(1) - sinphi) / (T(1) + sinphi), T(0.5) * e));
    }

} // namespace detail
}}} // namespace boost::geometry::projections
#endif

/* pj_tsfn.hpp
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
*/
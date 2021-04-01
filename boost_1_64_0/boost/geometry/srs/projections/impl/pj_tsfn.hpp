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
yKNeJyPuRalBGRni0XFbqPynRQxZzx1q6ve+LiFhvT06RZD3cYynsWvNw+nRO6vnRTkY0A7hZPsY8Hw3kcCb2EQm8+YWXFise1CPJfYW70IBNTW0dXgwT0rFD0GsEYEGQAEuWz2YpFjExgpZGq2fmlDjx9jZMPRyTprX9tF16irGQfbJ6DpnDGLUVlDt/qwV2rftexzfTnh/Z57g5PA2vKHuB/sK6Ts1z3TMFTSn8Vof/7JAdLm3fTg513L9aPf/v/9xwUYSIH208UynmBLwHvjAK7acn3QsUUV6alR6Wcw6GIck0VE2CWpDX/EUCrwseffVanvjUvgrS1zukM73sL+OzM29hvOom0XKPHxmi4cntdOn2tOeFnQoVja/v64LrenUeQA9ZHfFPU0Cjs4fxq7sl0MOHSMGT+T5jykkT3p1/3r0qamwMNTHnP0BcNDFSwogeX8jjNWoi/4Rp00f86MjjoyvUisp67cn41TRB4a3ROy4LDGKKy5lVCGlz9sER1f182aFBKMH46FN6uzz58Ska1HURVm/f1Z8Ph341R/fV3v0jACXEFSFIQ==
*/
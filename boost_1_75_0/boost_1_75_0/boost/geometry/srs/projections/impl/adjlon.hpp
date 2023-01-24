// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_ADJLON_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_ADJLON_HPP

#include <boost/math/constants/constants.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry { namespace projections
{

namespace detail
{

/* reduce argument to range +/- PI */
template <typename T>
inline T adjlon (T lon)
{
    if (geometry::math::abs(lon) <= boost::math::constants::pi<T>())
    {
        return lon;
    }

    /* adjust to 0..2pi rad */
    lon += boost::math::constants::pi<T>();
    /* remove integral # of 'revolutions'*/
    lon -= boost::math::constants::two_pi<T>() *
                std::floor(lon / boost::math::constants::two_pi<T>());
    /* adjust back to -pi..pi rad */
    lon -= boost::math::constants::pi<T>();

    return lon;
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_ADJLON_HPP

/* adjlon.hpp
CWPrS7d13XLZOtntt7zR86aft+9yo7ySRVW+yN/XDoJPmOVPyX4U+zovWr8bnPMNyXfZHjCluJb2H9YBD21Y3CWlyYVLYcm8fzMCFn9JiSwdWIRhhTl+1Uj5JuurdwamYHW+QP1WzrZ103y3147tXDYHtd0JEwmwAYGnYBcRZGtfrmzMd/YH63kBZA95LV0x1zDslvvv+iqJPQFr66U+WEiSevaX4VK2sl1aq49Ow+dz68cGx/Y3gJPKmvKKipUW59tmyk+fClmbiQn5QzPs9Q2OX78y+ZM6BVpRds0dakeIFJJvUOr6jKB31bFgcXFxKQ7/LyB/3JFBZ2djJa7L/iYzXcRe++Tcq9Jx45kDsVcaF6GxQzdn2LC6jiX3BqAqNRXF0RH1Qed8qmopoqyFAe/qXJ1t4FNcaO+6S6j9DaryPMq3IXG3gTzaCKYTNXvm8bd0elZvWTlWGk1jOgad7BurgEn82k5LuvO/iusrS6aMW107qswKZ7QNtI2N9Qe/cIiSr0qefNv/rJFGGHgX7FoksBlCyDsM4et2yn7f06ivbgYGzoniuA+t5dCHOye5ra3X0mJE6S+F2Vv2ZPj4dxB1ifsbdbk2nD10J6+/dN62SKgaG2u/fPDR0xPub/F5CqT/U6LQqa0WJCkjZEVjQ0ZBqzgjrqWXFdFN9adi4pq7qs5MqT6jBefboKvOwCr7suOHbr+RTjIK8I1K
*/
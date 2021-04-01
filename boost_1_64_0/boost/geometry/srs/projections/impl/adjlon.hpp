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
yBIK0c5usB9FSMH1mGIXy5BaO7TQzAxX/LWuAk+kPlmjpqzM7XiST8ElgvHLjZyuLXV3mEUzdnC7L6dijiD8/pRinfA92tPZlotaveNpE8sIWc5W+e0PAZEUNVDgxxWYTw+y66hUEo8Q63AbKpll5CTC/zMue2o/wYT7+jtzelEsHr18z1U6FuQ3X4hoEWhapSv0N6TAP6OloitHtpQyWgQzCVrucnitE4GlU/2HDqBT/Ii9N1IpTSObs3M+i0ldSLl4bAPiXicJgqVMn0c57TBEPvyYUVYschcFB81P97lTQmxiPiLHozQkLZMWnfaNet0XRPMbGNVz67mfG1JqCJfJ1Fr3yLO/kTgipYGzJQJuf8FW0/0mg75JyeYwGiDnzCbpgkqN0PP0G5D66MdA5Sh1OpFsthyQ5qvsPte58WiiMjXtUJ/YHGowKHof/1E6/kjBOT4S+zajmVnYmqg6MMEM5tIboBy5TeNJM+sruUPhToSbf4lTFl3tc2MmrogzKihH4v9wndYndRTlzFreiehZrlv+LisRTG+0PqbALH1saPmunVjsCWS+LA==
*/
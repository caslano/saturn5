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
83zaGXU2gch34iDLpz3M4ayNQIP9eCHrsLJHxbNR5mqxb2ZlrhHPRplj0hdmvXNxrQcOImaz6yQuS3sZwI5H8KjHKTzfGnHHQ3WqwsY97CGxmZ/yjHcSluA+uiYqxiPMc549IcYjBduicn+n2ZjRHn1gOQc/wfd9S4mJi91e6IGgH36yjr/vK6WjfiHzUnjjkv9PoZ5GE89k61X5NCaxpu038CCms5sr1bkfmhkfxsxaGv4WSy6HNVzX9TmcCWKJ7yYz0i6d9Y2Tlhel98/6nPJGdgYpM2sr51unGC41AS9lbXKzlQQS3V8PwtgWcvwvrYOJYk6+pMrht1jjWENkJILZ7PeWC6EPcWqa17rneOIMYjavv/H8ZcYLOfN5UQdh5WEMG/MwwphYvnfAGRbQCVRZKLA1z8FmMb7h5SfUpdtyax0693Q6jy27bCA1lGJbdlrvy2b8ysjRlngdonL6gGs2r/ebZQxeWocb6lybITssJwMMmF/lDo29J1Tn3S+Co+d9qhPuPgzQjNzy6/HgJIerijXNjRIHnoW8w2hOcbim0b6k+en8f+E/dWlHlB7DjgyLwsQ4vorJ55Nb6txxB40h1wzr0P9nWP+/tW7umPvOOfP+S6idyKshKIb4KDafP5rtRx5j7Ece24zL2I88Tq0lH6/Kvtezvi9l6TsENDYBhiHR47OA4eyszMfIJrdcKnGIwWIuLO+hXSlgh+wEp20VsINe2jVuOS+sTcDSTkrMYetU/tMTWDtcALwMGmZpbV7P8mqfZNjnyc24DPs8RdnnqUGxH/kXhvp7ugb2DsV3DQ/uHXKrnQVVsZ8jitd2z/vqTnxsA/U1YPG8kZ4hCZ43VZ7rxPNm6X/1QD+D6V1vzT3/rPPuM+MHUbd+jornjeCt9pdX1sj7YsX7mc3ySz1lDAC6zZ9VgR3kaz0Bc3etgHVYiwC1Fl3VXLW+EaM+ysF+NvHGPlrlYB/1yI6xlbbG6l61SS/rN881/OJ5zbgMv3i+8osXBMbd3b8jqt/vw6ddKEBeDUE++iLwNN8pfrCR7/1iVf9LjLI4w6Oydarsy1TZlwfExksqbgpa11KvVDTXKJq7R/i4IE6p9PjO5jYPnE1ybO3e6C0zkUdoU+OaJC6RFH+pio8bDO5ly8YRVkaxJVyrxOHb1g7VtcaF0YtHbEyR8iWSkyIwmsnw836Jm0yz8u2q/JgLxnpQ5fy+mvndfUL0Gd1+S0Fnvj/+WtUWr2PnToOxyv1DqrwL/waUPYaL5428UfF5U7NR3ifv6S2q/FuN8tpvypa3/NtV+Wv1WBniXdjBS+VYaUL1WPnOwDyBZCmTn/B+aMILoj717uag9yKwcUvniAU9KRneO0t/2V/MvJzrlP7vV+X5OQBIfPL7JrEU5xkD9Ez132DkQOn2EtdFuP8g8JDBk5PyISXLh6v0+XvGZFubuRIfUTQfZX4m6jDr/jjwgJMPmPkwn1B8PsnlprqDaU8o2k9rGZbIcecPMaCNXIijgDX6xNljVvU4++OAa9U5gfARzetqoZN+b5m929iuYWpIwGaKaMRYud7A63fiNH6rgS/hz0563lkz8CJSy+PEOzTeeEfypZC3l+dksPfwXwHckFXE33CYtjla4F4F3H5rwi5VoXsNcAfc/IzKOHlllXecX49yRy2xP2GxeCP2cDXD81jmg0F7jTV37OKYFS528Wbwu1bvT0WzMn3eBtx1rhwTNvTEOW3a1nZ4B3DHmYwMTe9TnzDepy6A5iTy8e/Pnm+0sEfdYFHM/xRo8AUgIQrFZd+Fcje773vT1zwoZ+EWy5OzQGdNt1os5q/PdqvE9uuN2H5jQGy/KSC2HzNi+zr3o1U=
*/
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
VWcEp1dyBYrW4iRTmuNZpmtL4ORHR4jwdCzsopkC+9CRKXtUOTOfpZbnzceEnvy39wUtOCFzHPcr+tRzXSDjsJJ+18xbvvjeMi7/OhoZL8ZBGAb30Qu2X/glRTeaELvZzjCeC/f9nOWQLhf91zhHPbvp0UGz3xuOztpmp5VTMBrCJ4wOM2xH59WhcWnfwr1JegbBh18dGiZoIOhUxVQ7dBkTGxqNLcygcpCcN3Ja0AbY9UzBM2PH8fl7twsifhyIMQqApscGNOfaXkyKJOneuet6Sd7hWgEt8RR/zhsCEZU9G0Qx6CHelMn4H1KOPpuIkWm4fz7gYNUVO2tinxI8jXjPHdB9SCniyhti6fg3sCjTABYCsQ+AL2ceqOTINNzJPX5cijPV4E7RHNFaEXqoDKX2YE34ICu3Dx59wuuWZqqjkq1IxoXDfzTUcWqiO1A0UcareQimyCUdXeX2BhjuAnda33JluPOmHEx1mERF27hHK5pgiGMuY0Zwn0VSZUWGx13MjUCOQh9uH7KnU3poEXIGhkk5MV6dIiZKYfNFMGURWOo40APOKM4cCalx/9GzbEgP+UzUR+cEY7by2RNdEKrj4LMe29vyU8XBE30buUO6WLGiFf6LOmruX0Gnk7d1ldi4EZebeozmOCJj
*/
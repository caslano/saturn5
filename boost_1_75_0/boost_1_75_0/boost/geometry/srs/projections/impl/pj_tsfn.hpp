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
2L/xaevQn/ifdTDiYW9RsPM/t9FCv51+drKl2Up+Hvn+Y2Tkb2zGZUy45Yu4Xg9xNI9Dj6qWAa+UoO5Kq0KZ7cqpfTXnQCkd9sy+lJmvBgXxnjFQhYjv/Yin01N46LKUMSr2Wv/08wQkOG1SqsJ0ey1i4xAwRrmUheZu9kOLrPqNU4SoxvXt0+CEtdwRgvzymc1v9XNTdpPBQilZjcgSr0bi1IPJPTvtnYGstsE9hyjBtnTz09zkFLsAe6/GGtxXpKb2xc6Yw5QSSTntgY6Yk1YSNSuCph0UjDlsqvnpOweCB54US1ohomLBQZLhOwUJCfhHjrcQIday6TiKWF5rvUylE4bbgpgSSntvz8FowRgivl5ID4TZlB8/N7x0Bovv9/UFR12BJkEg/TYZvm1mY5uRYyAVB7ruBd6VFUC7Irl4plBp8rv90sAVR8zElJiVcL+h1Jywgs4w7qH6Ga56Vn5Xb7/Rmv7ryZ2Qkf50U3RQozgfqLHlJei6Re7lgWvkm6w5WmwPWRjTC9QDJ+i600Au6ygYu79tAyqXFbwAbmhAHvOFPJt8MrOzIHD8bujJxJqOWq/0HlT08eYVKyqefWf6F+qjn6nJz4/9pSVUlUUT7xN4IwoLj38y3R91TnGXoM4jU5I5L3f+kql2MZO+5cpTwaY7QvJtF3i8o+rx2nJx7v4mmdhA9y+0uV7wfkPZbu/MG7xM66kG4A58
*/
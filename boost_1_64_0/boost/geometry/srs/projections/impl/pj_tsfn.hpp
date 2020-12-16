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
Q989gk9B8//t1Pv2BOxTyv+GecLdyLI70JMX/hpZOQx+Bduvwa8N26EnvsW+PxhZoH3/zEWHL2OMitDhjOkuW4P9P/Pdi4xhAbz2U3iuAbwyp77qp546+FB4fCFnjz1sIeTV8nruiDgKfZlLfauh8UnMcy9CtuaB+fcZ1xeU2vw05gQLadvXyCH084f4MbNZezjyK/IuhOfxvx6Yy7wTrGx6H7bjKvzs74Nf7Mh4X16KGgFtd4Mvb/PUudhCRWBlKWN5FnO5Cx9iPCto44HobrD3Mb7Kli1D5r7Robehp+v5divWG15kTO5FF38ZVlOwW/vCoysod+ufoKdZa+iPLzCOrL62mZNZldgfg5jzIQenvgwt+S4KfVeMRW69xljNZY4ahTex3UoZj/1mo3fRB3ffjUyknsWT8PN/jE/5DWQ9euUng/GNY7e1oXeqnwOby5Hf+Mpq0MsRcHzA99SNbql5C5/ZZbSlENkJLYtqkQc/R1bfib6EXsOX4yNGxu3bG51PHXdjW+3zPOUgb09+SOFzxcZZgw8AHn2zk9vPwMmmyMCca7Hprof+A6H7EWH1juar6ZSzJzrxeNYihjJOyObL90M+r0JHI3uqwPVJ8Nw2bchG8HvSA/DTg8ge7P6LrwTzryEf90bejcbmxs+69zfwwr3wLDK6+ivw8TYyG/ypk9B77cz1z4WH+qLnRjLXWIZtAa3+1hv7DHt4LbbQHqTfOw5efAe+Yt53NXpsBvTKmI6/fgQyq455Ov1+8m5ssb3pRyeyD795SRYy7gto3w/+xM76EPy8Ohw/P7w5Bhu8alv8eD3QqzXMkaajV7BNdmZeVjQEfcb47zUGuTEKfyZ9/AW6fMcoOEbO1N+GTjkJvhtOP6+CV5DvN71BO66A/+H1bbcFl9A4Hzl+/DXod+0X5ZtPHmU8keWZzdgxZ8PD6O2JjN3Pm7E1a9ELvfBDw+8nEqfOZ64FfR6bjN45Cj1D21/WvP4bfkPHPaDxkHOxWU9EBqIr5tdjy2DDXnQWazP4F85A9n+7GHmIXFm5Bv6GN2eHkXXg9aWDWHdDN414gnYczc8G5u47MhfCZj2YvgxajQ97BnIfXhiJTLv+E+aNR4BRbPJR2Dofbo4vMc6axQx05cXYdSPB4z3Iib24b5T53Mhr4KcZfPdH2n4x9A+BrxZsTepbhX+vfho05dtdivA1QIsJZ8CDfHdDBXiF9s9fzhiCpy3hv52xPYejRxYuwpfEWs+mjdjy4GzTHZk3XMp8rI6/yKNtwe1e2Hoj4fk16OVT/kL8I8gp6F3G/Oal7T31C+bas9Cjq1Yxb/gr9Lga+4D2nbMSmQd2BuNbGXAdryQi21uP9ecT589gnN5B/u+K3cIc9+GR9O8ydOWtyBXW+a7+Enn8ADric3zb0PfrY1nD2QacX4ncwm46cWdsxqnQFax8rm1daJGH/FrQis3wDXQYx3z3eHgQPbNTJjIQn0HsH+ydZ3yV1RnA3yQsFTVMIQgiKrWgkIQh4iITwkhiEpai15t9JckN9yZh1K2o1dZRt3XvOqq17oG7rbPuOqt1b1TcA/s/5z333OeevDekX/qJ309icp7nrOc8+4yXnPnqD/DhmNereeTT8AEPege/5VP85H9BT8rr4PmX0T8TvsCHHsPaMebSoezfvIO9RT53vwW/eSE8/xPrvxH/D9qdSe7yXn5/6nX85FvJCUTYm92ePOPltD2AvNV7rAOx/Z7o1Zvx7XZDN0VmYI+fhA7kFWfuhf9KP9tk4jNE2Bfpk+ktexKfCt1y1r3IAeMeBP+OR4+HstH9+OO7gf8E9P3kdmT18Syv9Cr2CFnrez+Ct9aTuzqd73gdTR4=
*/
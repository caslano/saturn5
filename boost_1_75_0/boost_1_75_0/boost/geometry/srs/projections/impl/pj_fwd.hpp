// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_FWD_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_FWD_HPP

#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/adjlon.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

#include <boost/math/constants/constants.hpp>

/* general forward projection */

namespace boost { namespace geometry { namespace projections {

namespace detail {

/* forward projection entry */
template <typename Prj, typename LL, typename XY, typename P>
inline void pj_fwd(Prj const& prj, P const& par, LL const& ll, XY& xy)
{
    typedef typename P::type calc_t;
    static const calc_t EPS = 1.0e-12;

    using namespace detail;

    calc_t lp_lon = geometry::get_as_radian<0>(ll);
    calc_t lp_lat = geometry::get_as_radian<1>(ll);
    calc_t const t = geometry::math::abs(lp_lat) - geometry::math::half_pi<calc_t>();

    /* check for forward and latitude or longitude overange */
    if (t > EPS || geometry::math::abs(lp_lon) > 10.)
    {
        BOOST_THROW_EXCEPTION( projection_exception(error_lat_or_lon_exceed_limit) );
    }

    if (geometry::math::abs(t) <= EPS)
    {
        lp_lat = lp_lat < 0. ? -geometry::math::half_pi<calc_t>() : geometry::math::half_pi<calc_t>();
    }
    else if (par.geoc)
    {
        lp_lat = atan(par.rone_es * tan(lp_lat));
    }

    lp_lon -= par.lam0;    /* compute del lp.lam */
    if (! par.over)
    {
        lp_lon = adjlon(lp_lon); /* post_forward del longitude */
    }

    calc_t x = 0;
    calc_t y = 0;

    prj.fwd(par, lp_lon, lp_lat, x, y);

    geometry::set<0>(xy, par.fr_meter * (par.a * x + par.x0));
    geometry::set<1>(xy, par.fr_meter * (par.a * y + par.y0));
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_FWD_HPP

/* pj_fwd.hpp
USYpQ1DDWUtPEHag3j5QxUu3CROByPg7nx/cmNqyP7K9dIT7+Mm8VlJII5RayU39K58nnrhgu3dGNYYHbIIp2vGfaDY5+/DIU7lfZj6YuD7/jc+jrjw5iu9Vf8PyffI/5dQKJLlrVdb5HRQoDwhahpDEuXcVf0rVmoIWXPgKkwURvgDCECh/rdeNI/y/6v1POs/+X3v8PP9cnv4fjX4RDA/NIU9gjvZBSGhY/H3aRkNtmEXIJOfrqNzJl90Borza+s+vPZ4nJYqadMBHKy1/Sv8hxsDoOlGH3TMkZAu6rbTlEHVcRKH4kwiKQ6vAIJOn0s6gK6yoKjG+v3wHJcheMK7ldqI9QB9NTtJORSVAeT/ncb09XdT9bLXVHTpx8rIzkF5DLe66pmKqaRdMcffO6I+Z+pG0KLHkP9Qjz1SmDz1KhJ6Hrsrlu2STXNat0i/TYpwzLsX6/ftf93/sP4z8FDkQyau4PFXukAUHlCC6bMmlcT3iezBw/e0nRZcJFdOspKqb9oeVT1lYtvekCtpYMpsv1qkrHxxPLK3wsXxGkAH9+RiSW+2C+QR+qnSxqQdve/0tXr8k08SeC+vQNyQuy5UodnI5YYro/NJ+rPb9Ta+O+/m7jOLxrt19Cx1nMCYi9njddcFP2bt0LGh6p+ZTZctgl6s5SPCktWHLFRLNcpD3ZkhFwpzniVgDvKr2tGAEX3/P/5JIBSh23rO8
*/
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
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
*/
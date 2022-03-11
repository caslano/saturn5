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
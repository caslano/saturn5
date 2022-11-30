// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2019.
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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PJ_INV_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PJ_INV_HPP



#include <boost/geometry/srs/projections/impl/adjlon.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/util/math.hpp>

/* general inverse projection */

namespace boost { namespace geometry { namespace projections
{

namespace detail
{

 /* inverse projection entry */
template <typename PRJ, typename LL, typename XY, typename PAR>
inline void pj_inv(PRJ const& prj, PAR const& par, XY const& xy, LL& ll)
{
    typedef typename PAR::type calc_t;
    static const calc_t EPS = 1.0e-12;

    /* can't do as much preliminary checking as with forward */
    /* descale and de-offset */
    calc_t xy_x = (geometry::get<0>(xy) * par.to_meter - par.x0) * par.ra;
    calc_t xy_y = (geometry::get<1>(xy) * par.to_meter - par.y0) * par.ra;
    calc_t lon = 0, lat = 0;

    prj.inv(par, xy_x, xy_y, lon, lat); /* inverse project */
    
    lon += par.lam0; /* reduce from del lp.lam */
    if (!par.over)
        lon = adjlon(lon); /* adjust longitude to CM */
    if (par.geoc && geometry::math::abs(geometry::math::abs(lat)-geometry::math::half_pi<calc_t>()) > EPS)
        lat = atan(par.one_es * tan(lat));

    geometry::set_from_radian<0>(ll, lon);
    geometry::set_from_radian<1>(ll, lat);
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif

/* pj_inv.hpp
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
*/
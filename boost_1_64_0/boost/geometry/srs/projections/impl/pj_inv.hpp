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
Xt+54r+9ofHYHx4+RPDwnB8Rj+YuEbsPQKXbB2DX0XoF1tEK7N7ZQ6VPVq7j6+to3FGJNPFdrTNuZBnmvO2Q1LOqRxCWd1YvJazz/cLm07/vEPvPjyJeno/asWcyPNHz6XO06adxU4GOwpRxP8qk2f2ONtxLh0cnw5k6nJsMD9LhMclwtg6PTYZH6PC4ZDhHh8e7MFi1+x1tOE+HJ7gw+LT7HW24Utn9jjY8y4RHu/AcE8514UYTHuPCrSY81oUXq+R+x2MIL1XWpWdJ4/ZF9SRN7qvtafbR1srwyXJfbU+zj3auDK+W+2oJX0y6DF9NepMI30B5Mny73FdL+H65r7anv482R+R/Tu6r7envo80V4Xfkvtqe/j7asSL8hd1XOxt87wCPLBM8okKRaeXc0VRRll9TWlacWOENQD1dFol6yk7LOz9O2Zo/lgteOTxgN68gLNeNfynWlI+0afw1aSdY3jvRL8/ZX+GewfvAPXWyzbtSrLWYvSJ278iviJd3rIXdeotb93b3LF42OHXd+zTRxqcDZ6tPt/WeYeu1Zbn3IV60+fW+BPMWjM1/1hDxNoWtd0f7n7y6Hveu7nGWLh+YMnqpc2wZ59oydP9O6G/3KVk5tEqE058lm1JazrXU5SwxR8zgirCVjecH+nQB4R10L4J3V9r2rLFjvY+bP3Y265e2mvRZE7cu5GK0drV2m8jFeJWLO8cuNvZae21bR8RfAOOoO36Mzlb9t8OaaOvJoO2y61178qtYZtYrv0VuHY04vWvCRDo7krjqGZXyjrQMHVdVPL2ipria2NLEmnIvHT99Rhm7YYjyv8/UceUV1cXl1e6O8Ww/rsaUW1FVQ7EmPs/UX1E4zdazVIfL8lk9rFSjxHr0pdCBLYQkmrvE/X6LCN3PArl3yJxZTa7xZphwrgv3NOExKrF3rJcJj1XD7b6gy1N18+QZpXZfnf7VxT5SN1KLODqtn3JfyM1j8abaJf6X6dMoCxvSYOlKV6ewIelTX3bAXDXEfymvqaGzzf/eP3cU0veGiu9CP7ANDr+UUG/2pi331rs3duJEt7VTW6W7dYr9niIyr4vP/b0X/5vnxLTd/ntoFeyrrYu0H3aGbDNOYlybGMt/4gzZKQaby7u3x3ndcQzGtItdwiIybyOGWu8tcWPt9iZqOl6/Dh3bHR1J41+7xiOhQT3/QDij+/3YaDxCN+PTGdMvQbONqu9fQreB8s499Elnuz8PyrW8f6P0dW1Ap5WnkVlCu3BPwKK0EiOYGpRbN69Hbt2SRm6V27bfKuXWP9GOxHlFf9gWdLZ0JPerZzAnZJ+IO694e6o/J17XtDDi3ydjf1Oe2Afo9L20h+60+v4uX166+vvL+m24l65f3Dd4T6peiac0wLUAnUmZ5jwy39wXoJMmRD2njyKxZr0VqI63NuPx1o42W07XGWzZbr+K8DWFrK9pH71fxercB5K2hz8fjoBYZ3IE45M+mvOTNi/39bv9PoZ+8g7+h8j3MP8f4b+0px614RwdDNyP95DNL23fJ3z7lPy2LmurPiXzkfK0HDd7l9GzAfv8QVk33zwXsNdPtO8ua3tT2uQvDOF/oF0v2vpWBfK+PMT/L+8LfEXY2LpuWedrtpxnxX6pN4YI2oj2PineF8mx/126fk9/iL0LJ2DPXmN/2/m/u4fnHcIjhew254FZz2b+LnhMn90xke5u0Xcln3XjzMnUjahDx/1NnB/x+W6/zmidn55rz/2/Z3wJWJNVk4vNltTJxVVGKaRGaZ4I3B1a3wG8o/Gov++9akAizqyMq8H2zMsHpvySGlNmCTuNBfaqA/ebf2THcK0dw1y5/7+bbdTffxLw13wawPg=
*/
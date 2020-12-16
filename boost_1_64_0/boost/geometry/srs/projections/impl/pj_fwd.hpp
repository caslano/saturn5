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
tv8Z3G8+yTz9gv7jmucpHkcoLclV0oJcs7ynVR+TLo9nCE/RJfz0dJ+T9ubyn6Ha7QsU598dJN+gwqdJv5n3gQmXaWPanb0XVT+lab+saDteh0f7FaBN+u3Tlr3R17APZLhe57+haGhfI38E+LHFA+F/IniovdV2tCejD39R46Th9W2Kw7zeYd35K45ZzPe7FCf4XLb3pPyO94rcgfuo73Oam5RdSUSFc5VdyFUKfqkKX5HGDoLSBcr08Zgg/FIF/0TBr1DwzxT8JgX/PADX95cptsz1u3eBPU9GmXp7pYzvuHJfnVkWpHmLyjNLwW9T8GwFjyj4LmUoc7JhUmcq+8i5jITRBkbO3Sq4HexRJnMD2SuBc2wZE1EvcjlN0gvPQ9sPFTB+AvD9PGakOdsoLgOcNHO7UpAV4RB+UDZlZdjm5UxF5gYHhpylfrEsiLN/CM5eCieabz5lv1Tm7iSVe2xbQzbffv+MaaKFwTFmvCoTxQf6rYoy7DNDbJqENwd3ehDkbd8yHCvUPR7gZb+yYN+v85pI8EbfHt/dQWhpbqysa6H7PPWNbIOP8bQ701xbt7CG72JkIGx2bV1t05yaaoLtB3cWJpUhZWd6nwq7uySLhAdydGovYdQwC3IPRuIlmw+ZB0xTV90yp7KuumlO5RGGx6nAx0FlSL2xpnlhI3OjYpmn1P2c+U2HtzQ01hv388yV4wnihSsiUVlN72t5jjfEEeH5EYQmd1pC8YTWdLifM7ksyBGWBOOxLNjnb1NjdDXrxMFlAIf5+bHcLg4pc/jTyvguaBn6x/PTOth0hiGdIzlf+m/pzGQ6lQ43eJ6XNdCPWpXosuAEylGj4GMV/HBoV/6ZQKUX7Bdrub85sCxYniNUeaL52kaMarostc59TflOrCcYnuHX8/qpiT59926B6ps20Feu7chYdqfzmRv2S7R2k3Mj7AsW8Vh4D5zNL4Y6TESCa5WDAe/rDs/5M1T1dQyFj+UPZXkcyOMoNX4sgboimCof2YsBfAGXSc7zCd4B8Glsw4zpO0HeEwp5PUCfrJNB3l2Eq+U3LkR+xxMe+hRdo3ybxSNBG+9lQhfsX4Au/bZ0+7guy1xdilwJTutKXTbaWwO605hukj6SU4DfBOEJLSg71tFyzvtm5QtnZRms/cCmapXkLX0DrdEGyuokwKNzIlnHax5PwbLAPELjfbPMX/OIrauUO6bnfbTmWaP07Wzl12uaDwfbO9wrMXj38r4g/Xe2YsArpSO4/6m9ONFN1zZ0P3WW1AvSUTZj0HaOUWVZLzBJJ3tjG1TfEbYvdK5qWxQf4O98oUHwNDS+DzTwbv8l+Y7GRQDfS+Bwf7YM2gCFywuRb0OTPqWrl6v+fYKay1zJ/VsBnK1eFTK2XC11AvttSm6GZ41zbZmyZ3M8Eq7il3XwesVvrtKDH5al2Ufx76nTYURnn11XYoT47ripLHW/8uYy8R3jh+XevJHDW/nBcwTHQ9AXxq1l7izBHKz5YTovNGE5R/hxGewpDYtP6lvU2LkmxM7ydsIRPjNHBOS+ew7aUcHYBjh3Q/1F+cxf6+w9QRzp5xHnXmhbx6q7Kff7Oss8LyrAMLVLZadn0h8MNibow+hhtbagPD5Q9kzU/wZt2B7V44n06YiX6T0GendziL/WTVyO++Gc3i8zxQXKvBnG0a9F3J4N9bWUr/twHH0ccImOzLGkfwbcJ4J0ZVysCJkPbZF6A1xVb08Dzv1p9sOfCeLI+IE4z3G90JzEjTHKN2WEwhZf1qN+ncg8SD70dfKSlJfHVfDLlqvK+wfBlfMD4tXtk2vZvKrmUfQF6vp1Cs8i+B5OZ7hOhv7P9UD56jz38N4EPaQ=
*/
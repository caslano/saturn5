// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4 (projects.h)

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PROJECTS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PROJECTS_HPP


#include <cstring>
#include <string>
#include <vector>

#include <boost/config.hpp>
#include <boost/geometry/srs/projections/constants.hpp>
#include <boost/geometry/srs/projections/dpar.hpp>
#include <boost/geometry/srs/projections/spar.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_pod.hpp>


namespace boost { namespace geometry { namespace projections
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/* datum_type values */
enum datum_type
{
    datum_unknown   = 0,
    datum_3param    = 1,
    datum_7param    = 2,
    datum_gridshift = 3,
    datum_wgs84     = 4  /* WGS84 (or anything considered equivelent) */
};

// Originally defined in proj_internal.h
//enum pj_io_units {
//    pj_io_units_whatever  = 0,  /* Doesn't matter (or depends on pipeline neighbours) */
//    pj_io_units_classic   = 1,  /* Scaled meters (right), projected system */
//    pj_io_units_projected = 2,  /* Meters, projected system */
//    pj_io_units_cartesian = 3,  /* Meters, 3D cartesian system */
//    pj_io_units_angular   = 4   /* Radians */
//};

// Originally defined in proj_internal.h
/* Maximum latitudinal overshoot accepted */
//static const double pj_epsilon_lat = 1e-12;

template <typename T>
struct pj_consts
{
    // E L L I P S O I D     P A R A M E T E R S

    T a;                            /* semimajor axis (radius if eccentricity==0) */
    T ra;                           /* 1/a */

    T e;                            /* first  eccentricity */
    T es;                           /* first  eccentricity squared */
    T one_es;                       /* 1 - e^2 */
    T rone_es;                      /* 1/one_es */

    T es_orig, a_orig;              /* es and a before any +proj related adjustment */

    // C A R T O G R A P H I C       O F F S E T S

    T lam0, phi0;                   /* central longitude, latitude */
    T x0, y0/*, z0, t0*/;           /* false easting and northing (and height and time) */

    // S C A L I N G

    T k0;                           /* general scaling factor */
    T to_meter, fr_meter;           /* cartesian scaling */
    T vto_meter, vfr_meter;         /* Vertical scaling. Internal unit [m] */

    // D A T U M S   A N D   H E I G H T   S Y S T E M S    

    T from_greenwich;               /* prime meridian offset (in radians) */
    T long_wrap_center;             /* 0.0 for -180 to 180, actually in radians*/

    srs::detail::towgs84<T> datum_params; /* Parameters for 3PARAM and 7PARAM */
    srs::detail::nadgrids nadgrids;       /* Names of horozontal grid files. */
    detail::datum_type datum_type;        /* PJD_UNKNOWN/3PARAM/7PARAM/GRIDSHIFT/WGS84 */

    bool is_long_wrap_set;

    // C O O R D I N A T E   H A N D L I N G

    bool over;                       /* over-range flag */
    bool geoc;                       /* geocentric latitude flag */
    bool is_latlong;                 /* proj=latlong ... not really a projection at all */
    bool is_geocent;                 /* proj=geocent ... not really a projection at all */
    //bool need_ellps;                 /* 0 for operations that are purely cartesian */

    //enum pj_io_units left;          /* Flags for input/output coordinate types */
    //enum pj_io_units right;

    // Initialize all variables
    pj_consts()
        : a(0), ra(0)
        , e(0), es(0), one_es(0), rone_es(0)
        , es_orig(0), a_orig(0)
        , lam0(0), phi0(0)
        , x0(0), y0(0)/*, z0(0), t0(0)*/
        , k0(0) , to_meter(0), fr_meter(0), vto_meter(0), vfr_meter(0)
        , from_greenwich(0), long_wrap_center(0)
        , datum_type(datum_unknown)
        , is_long_wrap_set(false)
        , over(false), geoc(false), is_latlong(false), is_geocent(false)
        //, need_ellps(true)
        //, left(PJ_IO_UNITS_ANGULAR), right(PJ_IO_UNITS_CLASSIC)
    {}
};

// PROJ4 complex. Might be replaced with std::complex
template <typename T>
struct pj_complex { T r, i; };

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

/*!
    \brief parameters, projection parameters
    \details This structure initializes all projections
    \ingroup projection
*/
template <typename T>
struct parameters : public detail::pj_consts<T>
{
    typedef T type;

    struct proj_id
    {
        proj_id()
            : id(srs::dpar::proj_unknown)
        {}

        proj_id(srs::dpar::value_proj i)
            : id(i)
        {}

        proj_id(std::string const& s)
            : id(srs::dpar::proj_unknown)
            , name(s)
        {}

        bool is_unknown() const
        {
            return id == srs::dpar::proj_unknown && name.empty();
        }

        // Either one of these is set:
        srs::dpar::value_proj id; // id of projection
        std::string name; // name of projection
    };

    proj_id id;
};

}}} // namespace boost::geometry::projections
#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PROJECTS_HPP

/* projects.hpp
wmvDsPnQesY/PQJm7PpGzkS9CR+iS9aB3wBt/rECH/tjaDoE3TgGv+kZcI4jBm0iRvWIV7+CLy8ht7EFPgT69xRs9ZtnMd9LiJnJ7d0R4dtTZ2Rp/zaOPjmUtbqF3PxXnxKHDWVOh7LX9gjxN7q8GNvxHOUV77Ov/Th4L9GXOsdAWeYN7H8PQ0+8jF3APlWe62F4OKP4ILnw7zM4m4atx/fcMpLFGRvk5GjqdaJPhuHvoftL/4Pe+ho/AptzfCt2LIs812fQK5tzlvfgqxIvTv4cusCL7cjCEy/g98GTD9fC++Xk5zKR4y7s9r/gix3wK/Ffx5Gn+qgvtmU+sUA7ftcP8CV0Hwff/Qbe3XAkdvUUbMMX0OgBdC1+QSb+QdVJKt+IjWcv6jfI04Tn8NfB2fER5oB/9Mtr+M/0OWs2beQhj6z/e89g3z6h/0z2/edhs/llFbS4/EX2HiejB7HfFfAtU/LWnM5ajEIWme885DgCD+zDuG/4O/byCvIi32CnyaP/eAqxwDTmxe+nYsf/2p4JrTnT/Qi+9QmMKw853BFdxhxrLsPn/ZAY97f42Pg/b2eTawvDcx9g7/FJFzPvy9Zhr2L4zJ9gF1jr44k3nl+Cz8Lc9kF+yuCzWTPx/frgw+0Nf7AHOw0b9gE2Rp0JO+4m+roCfxF+bUO/73QCOuUVcInL6pGpZcQ/+zLW9cdkkT9hDS5hbY6nHmMoUeeP5uE/4099UkJO9C5ks8Dz+uSyx7MW3xk99XEdeyzfQgPWdOrj6EfW5KptsB9t8Ck8sATZu/xZ8rKTiZP3hHewH9NHsh6HIXcD0cn4eg/Rx3X4j5/ujg8EP2z1USb0h/bE/GPx70+9DD5dRb6M9fk3Yxrel9wV/sruR7E/vR9rid77PI7upL1jS+Ex4sImbOVfkbGVc6CPoptKtSyCn36H31OEXtmOvCJ+zZxz4fsb8K13I099cYb3LXbvbPzaSnRr196s1TzyI/Dm7cx9X2xa7UesfxV5Iex9f2Ts5us8BkCe4d/k1dHlCx7D92b+RcQEq+9G/oeSo6vB790ZPxn9NHId/iSxYJRY6Ib98de+Yt8Fufz+W2zvX+EfbMPh2xMTEdscUkrc8x6+2O7EUJxjeJl9xxsK8T1bySG9m8UPbPZLrAn8dex6ZAE9UYWd6NyPua1njtngIB+L4ZEZI+GbHOZIbrG8HtuivtuFzb5HxfzwQVkh+5f44yvJHz6HfzcZvyFyF3O4E35BN3x1ADHsZfiu2ONSlcccg493G/Megr5FnzxFHHsytnC3dnIE1ezLZqHbmUsVMhY+EvnZER8X/ur8Bl3B+v4F3rmA9Xz2OHgFP+XTa/j/O9jYbGJk9tB2RdddcRp9wnfxrdGddexbYatPRxe9iA7ZuQ049nrmPorXyWmck6V14o38fxFz23kRPm8dOvYPxGIHovPwFx5kTI//gD+7M/6GuovRhf3sw14O8dxRd+D3oScufoU1mw9vVSK/rN9P/bDt0OKBq8g1wkRDxmNDXmLPBL47+kXs/Ffo52PRM+/gd+xEDpH/vwbPVmLLM3LYU0bvb0N8sk7xw3fo0h3Qmc+h449HtvBbOwYga9iUk4i/f3sBsd9YdB3+4+RT0avk3u/+En05Et6mjw/I0dQjTxdNJOeCnrq7A5vwFLlo7N+pY7DBC+Ah5PqpNeR+iF+zzof+g6DZSuRpJn4Y8H/eqM6fYROIs7o+w5btAr0y8O0PRpc9Ry48IwMbAe3OQ7fskEEeEt8XH/aR8eS+d2U+t2GLiT8PYa9w0r2e90/keO8Z5GlOxqbdyppAp1HwwK57kAeh3rIL8S9ORmbuw5/bDR8UGTtlFfIPv9c=
*/
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
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
*/
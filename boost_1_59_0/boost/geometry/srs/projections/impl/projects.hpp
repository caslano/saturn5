// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4 (projects.h)

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
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
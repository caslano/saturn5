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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_DATUMS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_DATUMS_HPP

#include <boost/geometry/srs/projections/par_data.hpp>
#include <boost/geometry/srs/projections/dpar.hpp>

#include <string>

namespace boost { namespace geometry { namespace projections {

namespace detail {

// Originally defined in projects.h
template <typename T>
struct pj_datums_type
{
    std::string id;         /* datum keyword */
    //std::string defn_n;     /* e.g. "to_wgs84" */
    //std::string defn_v;     /* e.g. "0,0,0" */
    //std::string ellipse_id; /* ie from ellipse table */
    //std::string comments;   /* EPSG code, etc */
    srs::detail::nadgrids nadgrids;
    srs::detail::towgs84<T> towgs84;
    srs::dpar::value_ellps ellps;
};

// Originally defined in projects.h
struct pj_prime_meridians_type
{
    std::string id;   /* prime meridian keyword */
    //std::string defn; /* offset from greenwich in DMS format. */
    double deg;
};

inline double dms2d(double d, double m, double s, bool east)
{
    return (east ? 1 : -1) * (d + m / 60.0 + s / 3600.0);
}

/*
 * The ellipse code must match one from pj_ellps.c.  The datum id should
 * be kept to 12 characters or less if possible.  Use the official OGC
 * datum name for the comments if available.
 */

template <typename T>
inline std::pair<const pj_datums_type<T>*, int> pj_get_datums()
{
    static const pj_datums_type<T> pj_datums[] =
    {
        {"WGS84",           //"towgs84",   "0,0,0",
                            //"WGS84",     "",
                            srs::detail::nadgrids(),
                            srs::detail::towgs84<T>(0,0,0),
                            srs::dpar::ellps_wgs84},

        {"GGRS87",          //"towgs84",   "-199.87,74.79,246.62",
                            //"GRS80",     "Greek_Geodetic_Reference_System_1987",
                            srs::detail::nadgrids(),
                            srs::detail::towgs84<T>(-199.87,74.79,246.62),
                            srs::dpar::ellps_grs80},

        {"NAD83",           //"towgs84",   "0,0,0",
                            //"GRS80",     "North_American_Datum_1983",
                            srs::detail::nadgrids(),
                            srs::detail::towgs84<T>(0,0,0),
                            srs::dpar::ellps_grs80},

        {"NAD27",           //"nadgrids",  "@conus,@alaska,@ntv2_0.gsb,@ntv1_can.dat",
                            //"clrk66",    "North_American_Datum_1927",
                            srs::detail::nadgrids("@conus","@alaska","@ntv2_0.gsb","@ntv1_can.dat"),
                            srs::detail::towgs84<T>(),
                            srs::dpar::ellps_clrk66},

        {"potsdam",         //"towgs84",   "598.1,73.7,418.2,0.202,0.045,-2.455,6.7",
                            //"bessel",    "Potsdam Rauenberg 1950 DHDN",
                            srs::detail::nadgrids(),
                            srs::detail::towgs84<T>(598.1,73.7,418.2,0.202,0.045,-2.455,6.7),
                            srs::dpar::ellps_bessel},

        {"carthage",        //"towgs84",   "-263.0,6.0,431.0",
                            //"clrk80ign", "Carthage 1934 Tunisia",
                            srs::detail::nadgrids(),
                            srs::detail::towgs84<T>(-263.0,6.0,431.0),
                            srs::dpar::ellps_clrk80ign},

        {"hermannskogel",   //"towgs84",   "577.326,90.129,463.919,5.137,1.474,5.297,2.4232",
                            //"bessel",    "Hermannskogel",
                            srs::detail::nadgrids(),
                            srs::detail::towgs84<T>(577.326,90.129,463.919,5.137,1.474,5.297,2.4232),
                            srs::dpar::ellps_bessel},

        {"ire65",           //"towgs84",   "482.530,-130.596,564.557,-1.042,-0.214,-0.631,8.15",
                            //"mod_airy",  "Ireland 1965",
                            srs::detail::nadgrids(),
                            srs::detail::towgs84<T>(482.530,-130.596,564.557,-1.042,-0.214,-0.631,8.15),
                            srs::dpar::ellps_mod_airy},

        {"nzgd49",          //"towgs84",   "59.47,-5.04,187.44,0.47,-0.1,1.024,-4.5993",
                            //"intl",      "New Zealand Geodetic Datum 1949",
                            srs::detail::nadgrids(),
                            srs::detail::towgs84<T>(59.47,-5.04,187.44,0.47,-0.1,1.024,-4.5993),
                            srs::dpar::ellps_intl},

        {"OSGB36",          //"towgs84",   "446.448,-125.157,542.060,0.1502,0.2470,0.8421,-20.4894",
                            //"airy",      "Airy 1830",
                            srs::detail::nadgrids(),
                            srs::detail::towgs84<T>(446.448,-125.157,542.060,0.1502,0.2470,0.8421,-20.4894),
                            srs::dpar::ellps_airy}
    };

    return std::make_pair(pj_datums, (int)(sizeof(pj_datums) / sizeof(pj_datums[0])));
}

static const pj_prime_meridians_type pj_prime_meridians[] =
{
    /* id          definition */
    /* --          ---------- */
    { "greenwich", /*"0dE",*/             0 },
    { "lisbon",    /*"9d07'54.862\"W",*/  dms2d(  9, 7,54.862,false) },
    { "paris",     /*"2d20'14.025\"E",*/  dms2d(  2,20,14.025,true) },
    { "bogota",    /*"74d04'51.3\"W",*/   dms2d( 74, 4,51.3,  false) },
    { "madrid",    /*"3d41'16.58\"W",*/   dms2d(  3,41,16.58, false) },
    { "rome",      /*"12d27'8.4\"E",*/    dms2d( 12,27, 8.4,  true) },
    { "bern",      /*"7d26'22.5\"E",*/    dms2d(  7,26,22.5,  true) },
    { "jakarta",   /*"106d48'27.79\"E",*/ dms2d(106,48,27.79, true) },
    { "ferro",     /*"17d40'W",*/         dms2d( 17,40, 0,    false) },
    { "brussels",  /*"4d22'4.71\"E",*/    dms2d(  4,22,4.71,  true) },
    { "stockholm", /*"18d3'29.8\"E",*/    dms2d( 18, 3,29.8,  true) },
    { "athens",    /*"23d42'58.815\"E",*/ dms2d( 23,42,58.815,true) },
    { "oslo",      /*"10d43'22.5\"E",*/   dms2d( 10,43,22.5,  true) }
};

} // namespace detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_DATUMS_HPP

/* pj_datums.hpp
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
*/
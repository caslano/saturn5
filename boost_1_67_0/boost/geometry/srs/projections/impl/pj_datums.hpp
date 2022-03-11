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
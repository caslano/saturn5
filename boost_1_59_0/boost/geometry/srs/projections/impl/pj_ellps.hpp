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

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_ELLPS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_ELLPS_HPP

#include <string>

namespace boost { namespace geometry { namespace projections {

namespace detail {

// Originally defined in projects.h
template <typename T>
struct pj_ellps_type
{
    std::string id;    /* ellipse keyword name */
    //std::string major; /* a's value */
    //std::string ell;   /* elliptical parameter value */
    //bool is_rf;        /* rf or b? */
    T a;
    T b;
    //std::string name;  /* comments */
};

inline double b_from_a_rf(double a, double rf)
{
    return a * (1.0 - 1.0 / rf);
}

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF(ID, A, RF, NAME) \
    {ID, /*#A, #RF, true,*/ A, b_from_a_rf(A, RF), /*NAME*/}

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_B(ID, A, B, NAME) \
    {ID, /*#A, #B, false,*/ A, B, /*NAME*/}

template <typename T>
inline std::pair<const pj_ellps_type<T>*, int> pj_get_ellps()
{
    static const pj_ellps_type<T> pj_ellps[] =
    {
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("MERIT",     6378137.0,   298.257,           "MERIT 1983"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("SGS85",     6378136.0,   298.257,           "Soviet Geodetic System 85"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("GRS80",     6378137.0,   298.257222101,     "GRS 1980(IUGG, 1980)"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("IAU76",     6378140.0,   298.257,           "IAU 1976"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_B ("airy",      6377563.396, 6356256.910,       "Airy 1830"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("APL4.9",    6378137.0,   298.25,            "Appl. Physics. 1965"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("NWL9D",     6378145.0,   298.25,            "Naval Weapons Lab., 1965"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_B ("mod_airy",  6377340.189, 6356034.446,       "Modified Airy"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("andrae",    6377104.43,  300.0,             "Andrae 1876 (Den., Iclnd.)"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("aust_SA",   6378160.0,   298.25,            "Australian Natl & S. Amer. 1969"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("GRS67",     6378160.0,   298.2471674270,    "GRS 67(IUGG 1967)"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("bessel",    6377397.155, 299.1528128,       "Bessel 1841"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("bess_nam",  6377483.865, 299.1528128,       "Bessel 1841 (Namibia)"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_B ("clrk66",    6378206.4,   6356583.8,         "Clarke 1866"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("clrk80",    6378249.145, 293.4663,          "Clarke 1880 mod."),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("clrk80ign", 6378249.2,   293.4660212936269, "Clarke 1880 (IGN)."),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("CPM",       6375738.7,   334.29,            "Comm. des Poids et Mesures 1799"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("delmbr",    6376428.0,   311.5,             "Delambre 1810 (Belgium)"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("engelis",   6378136.05,  298.2566,          "Engelis 1985"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("evrst30",   6377276.345, 300.8017,          "Everest 1830"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("evrst48",   6377304.063, 300.8017,          "Everest 1948"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("evrst56",   6377301.243, 300.8017,          "Everest 1956"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("evrst69",   6377295.664, 300.8017,          "Everest 1969"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("evrstSS",   6377298.556, 300.8017,          "Everest (Sabah & Sarawak)"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("fschr60",   6378166.0,   298.3,             "Fischer (Mercury Datum) 1960"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("fschr60m",  6378155.0,   298.3,             "Modified Fischer 1960"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("fschr68",   6378150.0,   298.3,             "Fischer 1968"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("helmert",   6378200.0,   298.3,             "Helmert 1906"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("hough",     6378270.0,   297.0,             "Hough"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("intl",      6378388.0,   297.0,             "International 1909 (Hayford)"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("krass",     6378245.0,   298.3,             "Krassovsky, 1942"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("kaula",     6378163.0,   298.24,            "Kaula 1961"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("lerch",     6378139.0,   298.257,           "Lerch 1979"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("mprts",     6397300.0,   191.0,             "Maupertius 1738"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_B ("new_intl",  6378157.5,   6356772.2,         "New International 1967"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_B ("plessis",   6376523.0,   6355863.0,         "Plessis 1817 (France)"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_B ("SEasia",    6378155.0,   6356773.3205,      "Southeast Asia"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_B ("walbeck",   6376896.0,   6355834.8467,      "Walbeck"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("WGS60",     6378165.0,   298.3,             "WGS 60"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("WGS66",     6378145.0,   298.25,            "WGS 66"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_RF("WGS72",     6378135.0,   298.26,            "WGS 72"),
        // This has to be consistent with default spheroid and values in pj_datum_transform
        // TODO: Define in one place
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_B ("WGS84",     6378137.0,   6356752.3142451793, "WGS 84"),
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_PJ_ELLPS_B ("sphere",    6370997.0,   6370997.0,         "Normal Sphere (r=6370997)")
    };

    return std::make_pair(pj_ellps, (int)(sizeof(pj_ellps) / sizeof(pj_ellps[0])));
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_ELLPS_HPP

/* pj_ellps.hpp
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
*/
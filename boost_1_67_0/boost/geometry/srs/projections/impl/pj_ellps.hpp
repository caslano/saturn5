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
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_WKT_DETAIL_PREFIX_HPP
#define BOOST_GEOMETRY_IO_WKT_DETAIL_PREFIX_HPP

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace wkt
{

struct prefix_null
{
    static inline const char* apply() { return ""; }
};

struct prefix_point
{
    static inline const char* apply() { return "POINT"; }
};

struct prefix_polygon
{
    static inline const char* apply() { return "POLYGON"; }
};

struct prefix_linestring
{
    static inline const char* apply() { return "LINESTRING"; }
};

struct prefix_multipoint
{
    static inline const char* apply() { return "MULTIPOINT"; }
};

struct prefix_multilinestring
{
    static inline const char* apply() { return "MULTILINESTRING"; }
};

struct prefix_multipolygon
{
    static inline const char* apply() { return "MULTIPOLYGON"; }
};

}} // namespace wkt::impl
#endif


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_WKT_DETAIL_PREFIX_HPP

/* prefix.hpp
WWNvb5dVWbPerFdYhztS2GwQCGckvLsKOxxTy3+m/PFx0xevKkwEjNubmtTVVPrMdyfBgnuCwbMtLeH4Ysy4z8bCtzw5ghfpsGAq2ETagh2dX9z2+icVtphKa4pEntyQ+VM3tMdsyh8E84Ql5IOiMedewNwJoAPxsfQDIBgG0nU2gbdggfBmPtJA9tz2XcYfuLT5CBjxgE2DYO7v12pW6NkgfW3sWn7NMsPfnAazaCS3IMSMPzF3HrDAZaEvKgwhK2zmjuUEv0Eh0DgPR7b0p5VYGmDljGuux3xh20gL8KTwldiCDbR6KgjG5iCxDPDLdx0fWS2m7iwFCHpEKpPQc4AR6AGAxi6oucJCZyw8AqaRGxZap6TgpVMTyztmrgPCsNX2gPUGq2zEfelX2E3v6s359RW7aV9etvtXt+z8mLX7t0jsXa/fgamXwMxj4nHuCR+Ye0zO5rYUY83zn/vUVmpAkLXZyJNiwvxwNuPekxnumIPOcTDOHZu43owHvjIQsBYfBLzz3Ht/fwUIXB4fseZOY4e1NlubDWwZhE6F1XdY331A099i9d39rb391gt2cnbF2AGh7DaboOs58hmz0RO1NRrNlsIf8yckUQUS1SwBjb8Na8kd+a4tkhTqrR1FgbiznRiVJFGfA9D5
*/
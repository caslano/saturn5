// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_DOMAINS_GIS_IO_WKT_DETAIL_WKT_MULTI_HPP
#define BOOST_GEOMETRY_DOMAINS_GIS_IO_WKT_DETAIL_WKT_MULTI_HPP

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/domains/gis/io/wkt/write.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace wkt
{

struct prefix_null
{
    static inline const char* apply() { return ""; }
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

#endif // BOOST_GEOMETRY_DOMAINS_GIS_IO_WKT_DETAIL_WKT_MULTI_HPP

/* wkt_multi.hpp
rvXH1B/RXzzHrMByv3u+u4njosS29SoQ9jJWVQCap6Yd6+2oTcNMuB5wwLQW62SnMTMshK4DsVtd9fbkoa+Ft2Kz4pIG69vzWQxeehsbf4V8IYtV2XwQQEj0mosLvJahfbftU1+CjpWjFd+ZYK94mzkxY0uZKQ1glaRKqPQ1b291RvwfWPX7mYygJt1hr4m0pzUu9onmcNoyVuqu+qTm0m66s+c73MRA2herfONERKvB0iediMhWrn6zdKfOJj3PA4N3V6554lWsWUI9TtS0Y1FiTlq5tOdTsNZIeXBI8+SE3LbJvrLvq5d3izhg29Y5AotH00v8RuKtwBnK7jFUVncO3gdfK5fEaHQvYeUUx2ziS/BiPKxaTRQVTRkKWDM+xuEh9KHbpqrJ04tdkDA3kZDLpsjs2+wxX/qwOuHXW09weS/19GKdn5NE0HS6rF16pMhuuWOStjdeFyXNI4cumXg0josd2Ow9wb3Uo1gFNsHUNYWaZD6hkzC7Vt+lRhcHOhvpz1zbYSaCrPfNwCA+jUZBj84nbfK5ERTr/PE6iMSIP/D2/NiIYC5BPA==
*/
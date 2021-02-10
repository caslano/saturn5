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
oMeOnvtg/1YgZ6JU1qNE+Rcw8nA+d2FZoHg+W8CkuGEAHeIemp6Yw2eCBr9slNRVJD10FAlGbDUXMj2QiX12neVcCjko6aUH1ueBFRMyYSF6giUrnfSv1RxPYC37ZYBD1UYAMWk1GdAPz0qMmEoBHQAk2W0xAacSBhkRklIn5mmHKRWETuiH3IZVDmbGA9fzI/xNgNvUc1uD59pObW+rhhqFNsudzVzHfkKfMo6VR/OkSCy3yaPu1bKJ7A6uogEhPVjsc2HJCSxH4IRLA2wODBkWypMtYj6NJhuIOfj7+hZrbO/Xt/e3wf/XX9TrCMEDgGjEEM3Gfqu5Dy0bsD/U9XDmHLZEJwSHKC1QSGI5qvEgZn0PGOXo656IHCz0lX9Jx7LDsWCr6KaHvgjC+eZ0NdFxaEvwmf7m9FWyEaGVZ4f2mAgIYnFfIIW4EXygY4PPSreSu0DpiV2N3GbUViprR3oJAnkOjEy9XrQvB91O+6o7PH9HC7bKODhemFDLdR7ArcPmlIY7bvdOCQ7NULlzBRqk4U7hzyXC0Zy6ADCx3QXuY7R5cvC8sIGgD4T+YQZ5cH7eB2yNTPtEEhsfs9igez/ggbRgfw4SAwfh/IBZU2C4jg0VjcLWYc3Mw6B8ANMwFjTmnDbqBV1GAY2C
*/
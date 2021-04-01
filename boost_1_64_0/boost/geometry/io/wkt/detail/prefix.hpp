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
0EtbRJq0qN/Q+TdxhxlP5neyVWhM1gNTL39kJ5dtwS7Qi3Jkl5ffkY2o+MtZfjAyDfMCPEaIzzzvZJgO8k6OknDBSftX1YmiYGfyyf4xjl/GrcuPROqKBmkMIp13mUWuGL+meMPmuEBT/f499Uzitf7GQP21z1tMcEUi7Jv/81q0T9MLdcbDjGYEQJTYd7NUB+nRkB+l4XIwcRmFLognxY4MpP+5VD3j+axBspCJbQOxslCDN6jIkEFFxQqq9g99nRXkeemwhxM3hgrgERo0L7/ujb3ouhqQb9aXIycm2jEteHayTFBtZJS+giGaB1SdEMfyUxtuivNZ0lGimX/l+h2zki0t+ikCJCpy+gdvZ8QWMRk6IQIwUcjpzj+beShkIrcxu144mmv8EPClcjzI7AxvutFSzC4lVxE/Oc+1HAtmmlDwDja4RnvY26cO3qT6gqLkjckxz5XNxXOKOsHlN/k7tMd/ihpqkjdUPgX8YtHk0+fGS3Eb3szY64naxkl0uRNVkskwt0dYqhyqLZms2426E4BgVPm45mhL/e7az/Og1GpUZTeXCGZuyA==
*/
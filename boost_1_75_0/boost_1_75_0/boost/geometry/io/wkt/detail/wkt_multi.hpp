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
zw2x0uxm1M9mV6tVr1VNcwQ/UOR0WsQMcJZ2FDvy3cIaOWbbrDnEhd6FyIlHQ8W/zTL8MH51URZrxeJfFMkDKPPYBsr7nik8sQIULlBKAvK4K7xJTxj84miKnxc/iVEb+fMsP79IkCuGh2hYC3BcDWd7LhAex/4z79L8rKv9/HHe6ARU/yFhM3ZaSNeO+Sb3/sX0rJ1dWQA7f6VUSt43dUUHuMBSxaQZ5FPkt7JnXYRz4gOwxJHfHvrQYpqcteZd6YwsiVTFjtVpjQNT3zcmcBoe3pYKGwY03r0NTeVLhXdsYy0PLgtQv9FiE9RdOuc0HZ2p7zibWnKV6ezjbvQ9l/QhF9TndnBAzZqeQ8IpRFFit8+W7sfvnY1TDMM/2AhQtWn5Zh2n5Aayxf3FqLigyKPglTD10mHOL8LUbPWnwV8SQKP5AZhZhcEUnC2SXazBtogA/qaBZIyiekhs5KKa4s1i9Idl3zrKVyTCC2+GMqIbmZezpyV+PNCLNG7UYHllAqzk9nWLWnIu0EdGAxrNawAtDSh4TZpz60lndBV6jrXnjBIz4kZ/ic/sOzD7N6NRqYgl11MlHjgG0gImz8gzXglhOx3lPmfQidAHMtTZkNREU5McqBrMJH4k4lFukGeSwqn0ot2w/BjJFsXfShImM3TaF4y+fN/Eff/X8lai2UTrW7cMmenVQXrm++8VLLYblPR53cquukvEqb/x
*/
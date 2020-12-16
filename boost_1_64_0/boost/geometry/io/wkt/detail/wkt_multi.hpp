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
P/+N+F6PrJc7rnlWjGueE0PvXHfHNY/rCDkeOkJi6wJx1x3SPdt0H/yhb+2gyx4OdvV2eafPT8JnxXWEfBN0hMiwZxSIjpD9/H+B/P+dBHXGifqVd+OwSs5RkGXjRpEdKPoPhsPOcAQ8BY6CZ8LRsASeDlfCsbAGjoc74AS4F06Er8Iz4SF4FkwmrSkwB06Fg+E5cCg8F06F58Hp8AKt/0LeD8MlMfRf9CRcOuwFW8HesBvMhQNhH3gG7AsLYT84H/aX+DdjDkr8eyT+VLhe4m9BuEyYCfvA1nAQPAGOgG3geNhW6icHlsIT4UJ4ElwBO8DLYEd4JewEr4Gd4TbYBd4Nu8J74Elaz4K8b4XNY+hZKCecySWwGawQuXL9XpM2L3IhWCxyhYTzwSLYBs6SeiuGg+ECOAwuhMPhHDgWzoVTYRkskXBlEk7yK+8eSS9GfpdKfpfBZLgcRs531YjcszHOd+3lPEwX+HM4GO6HU+BLcC58GS6Hr8CV8FfwSvgavA7+AW6BB+Gj8HX4NPwzTCKN92EO/Cs8Cb4Le8IPYX/4CRwIv4BT4T/hudBjnpuFXjgb+mAZDMHLYBh+F6bA62EzeBtsDnfAbLgLtoX3wnbwAdgVPg+7wd/C7vAzuErOqWfAFNgStoKtYWvYA3aGvWAvOBD2g6fCAngaLId5cCkcAS+Go+BKOBquhWPgdrgK1sKz4AtwBnwDngc/hTOhz0d/hb1hCewP58LRsAxOhIvgFFgBZ8DL4U64GprX/21D3u/AE+ScaLY6z2n9rpVzot+DveH10h+fl374fTgT3iD9bgu8HN4i/e0BGX8egpnwx3AAfBhOhI/AIrgHlsFH4SL4BLwcPglvhk/B++HT8BH4DHwUPgefhjfCV+FN8HX4A2her5thCD6v9dPIexWwK4Z+mpWip2UVbA/XwJPhFbAX3GDr5wclnrPq93N1TtvkOhiE34EnwPWwPdwCc+AmqL6NCEfC6+Ek8Z8Mb4D5Yv8QMtWQdwWUSe4jmTKGmr8/ib6Kv0q+P4D94d9kHDkCz4Y+D+0RJsB7oB9+AgPwn/AEmCznYdvCrnAI7A6Hwhw4CnaA46APzoK9YTnMhatgX3gl7Ae/B8PwIbGb5dnvl7VeWWs3y/Og7fuR0wh3IpwBR8Lz4AQ4E86CRXAJnA2vg8XwVjgPPg7nw5/CBXAfrIJvwuXwHbhC8nExPAwvgWY7vRTmwmvgRHgtLIAbYTG8ES6GP4BXwJvhNXAb3ALvgLVwh5R3J9wDd8Fn4F3wRXgP/CV8GL4FH4HvwidggpfrDbvCfbAHfAH2gQfgEPhbeCFs72UchDlwLuwAK2BHuAJ2gpfBLnAD7Ao3wilwCzwf3gZnwp3wAlgLi+BeOAv+Gs6Gv4fF8B04B34AB8EjsAoOMc+RwmFwBZwD18AKuBbeBL8Fn4ffgS/Bq+Gf4Qb4KbwGfgFroD+BeocheD3MgpthF3gL7A9vhaPhNngWXG/eJ+A92OfBe+EieB+sgPfDi+CD8Ar4EHwQ7oFPwUfhs/Ax+Dv4BPwjfBK+BZ+C/4DPQHMA+SlMgc/BFvB52BHuh91hKvnpDVvAwTAbjoTt4ViYAyfBrnAuPBmugD3gt2FPWAN7we/CU+ANcADcBQfD3fBU+DAcAh+Hw+ABmAdfhyPgu3Ak/BCOhkfg6dAQfTwBOBG2gJNgDpwOe8MZcDg8F06E58FpsBAugbPhZbAYroElcB18zuz/8Hm4BV7npZ/CTXA7vBjeCS+BP4aXwsfgQfgkfB3+FO6DL8MX4G9gAvFnBRm/YF8YgGNhIrwQJsHZMARLYRgugynwEjgW3gzHwR/BlXAfrIa/g6vgW3At/Ag=
*/
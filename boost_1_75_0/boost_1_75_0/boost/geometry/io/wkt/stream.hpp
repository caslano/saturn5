// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_WKT_STREAM_HPP
#define BOOST_GEOMETRY_IO_WKT_STREAM_HPP

#include <boost/geometry/io/wkt/write.hpp>

// This short file contains only one manipulator, streaming as WKT
// Don't include this in any standard-included header file.

// Don't use namespace boost::geometry, to enable the library to stream custom
// geometries which are living outside the namespace boost::geometry

// This is currently not documented on purpose: the Doxygen 2 QBK generator
// should be updated w.r.t. << which in the end ruins the DocBook XML
template<typename Char, typename Traits, typename Geometry>
inline std::basic_ostream<Char, Traits>& operator<<
    (
        std::basic_ostream<Char, Traits> &os,
        Geometry const& geom
    )
{
    os << boost::geometry::wkt(geom);
    return os;
}

#endif // BOOST_GEOMETRY_IO_WKT_STREAM_HPP

/* stream.hpp
TQJaNFbQMmb6EAyCI8h/NbsclkDRSf6vsxn/d23rfza2aputBCNnSMh+oNDhjIec4Y4XkCaZ0+Hg0PVLz9rg4TT9pZJMEjZs0e+f0f242SlvpN8oGACSmXrk02Eez+wHNIA0iZi910uyhO9KqAOznSUWHLNPmgX8P5QmnEm6tCyIt+xdXEkGGM82otU4rGflNm1JHYUdgQFXwffSiF3gSteTa507gmBajcUJM/wHdzG2j5d61Hv9L68an+XEATMFCzJayLp5LVQKSKvmSQMZ00owTsFrbSwjHCNMVmw9FHbU6lKcWQqhpHKXxZWj5sg8xFW5RWOy1DybOk4qQQKQEBNzAYt9BirZFltePYGJoGzsFAh0Wyq7gkWcR3wnKdzsMd79xqaqQiEnjHHBfb7LHrD/V7zym9M4NMjDD2GWQ04H4JFYuMYyiIFWhvzM6QVVImfe0R89TYq9iIFnmwZIHZrfxKzMWgjLKlEIV5cbVO2wF/06LB2ZwjI6AJ4lZumhcjGLeVGVLhcpY9UeRPO8DNrZmCwGBr3YFW4xgkqGh9jHIMrl/QEJUaToddEEmK3+YTztjiqdqyhQSaV0niiEcdF5R3Zhr9CjwnHAY0iQ82JcVQYdEkEFhcMPy/qAPtyDB0PIFkZgkjp8CyXoZf2repw+83A8Kw4ryn/+VqvQruJUoJ6jnWNJYlRgLr56cC/q/hjOCExFZz1Dxf+o
*/
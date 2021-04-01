// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_HPP
#define BOOST_GEOMETRY_IO_HPP

#include <boost/geometry/io/wkt/read.hpp>
#include <boost/geometry/io/wkt/write.hpp>

namespace boost { namespace geometry
{

struct format_wkt {};
struct format_wkb {}; // TODO
struct format_dsv {}; // TODO

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{
template <typename Tag, typename Geometry>
struct read
{
};

template <typename Geometry>
struct read<format_wkt, Geometry>
{
    static inline void apply(Geometry& geometry, std::string const& wkt)
    {
        read_wkt<typename tag<Geometry>::type, Geometry>::apply(wkt, geometry);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

template <typename Format, typename Geometry>
inline void read(Geometry& geometry, std::string const& wkt)
{
    geometry::concepts::check<Geometry>();
    dispatch::read<Format, Geometry>::apply(geometry, wkt);
}

// TODO: wriite

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_HPP

/* io.hpp
b8O+YRkKdKyduCKmnKziV+TamMHgoFP55TVrgrNWeYzZ6atKcWdThk3Y4uUtXZ8aAMhLbSBsHh7dkB8gwoUotWT9Lk3eL8aoLt/dTUyG4mzSDw9OzqRfCJyjeq71L4vMqvO4Nbu8kNqmft8xZ8yhreaR7Z7QLt9xSWqSAGNS+WHAU6d0H4y5+44WmzzT3BVvgKqAeysZZU2GXAx6WOJheNM97zRLILJuzFLVVehjMQuccU6ygVZNV+nhf8d3SYHnH9DdJL/SYb5VL44VnB6vyO0RKsgzYImj8zwTkYtyM6Guxzyh+DV+X8MYereegNJaPG9y7gZ+9siE6lja8+zNBMPtiLg5itBC+eK7WAsFGsCNsJsqaIRAFZwM4L5ead+4uvgyuYFVaxQrjObwEhel8UeUlw3KjHgKp39dg80OQP1iy+aLR9v3IRgkPMwsm1zee54WrHNXF+XUHDMzOcjTPWcmaPqdcNH0JE8SQto87z5/0wiXiaOxHwucNM6hEEA2UQ4H37OIsrYu9DzVoAPfm6m+91+hul+ZRn+Ozno9FoxqhoAmb35tXQiAig==
*/
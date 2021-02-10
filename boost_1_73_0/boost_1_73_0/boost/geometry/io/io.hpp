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
UZ0LkGQsBUQJwLFFhurP1QdomQR0UW1XBLtIB8xByiwO7k3n/OVg+KYzFjMEvpMNdNiRhYHnBiHWcGifds6sf4w1MWr9i9y0N9abeiWVeYaIweXYHrzEKYPh+7acJTjRlh+7H8XIV/5z6vjBtCaqv6poNkauEzwjj8HwcG1dzI5BWeJQS18s57uj9qCwkwCy3z+BH/IpB8ZnT2NKcToeitTEDuGQD9AAPdBQO2oSBi4mmtYKdKeudvRR4NdNAksEEfj7J4parVMITD4+4MCRFV+NfKZ0WRN1aVV3YiESOKsgqXL0WZS/galtpITS8EYQIyerqd0bcC7YxE4Cdku/Y4eC37SwDfsDpqRRwId2uSmi5PMC2TBFIrXxrTUc9Qb9n7iw0GDQoQOFH45ax08/6qeNZRLzja2tI9+rCycnSHCX1zW5CASM2IRQYQUgkSNkjzyVGy1ok452/0QEvCdmhBR6gCj39gDEj+xHXLpgoej81mBAq5SEX9/Hp/vqExDy7PDwMXv22Ktm3Z7EDvMOQoiFTfkghkiZUBujWD2tBwr6cRVhq7DJKE5IZ5PYcSlQ2ZLqph0PDdfwGPIqeFOrFnQIhZgMEDVcAj4FhJpEAX5qEpEUHbXq4H9aylbUGuViVBSwoyX3/2gkgdcU
*/
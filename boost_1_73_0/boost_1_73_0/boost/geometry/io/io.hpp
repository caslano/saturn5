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
xCeo/yzEzoTJynciCOltVz/Stnk+jntUuhvpu+n23gXJnBS9FXlRsvoUWUNTxUSEvb+26cS9VJ17ibgVnPlC2B7MhY7agrf6WbrCH8Rycbb4Pbc5fjUoep6dII110PKcTWVxkePhfUJ8IC4UOcoYuLHHtPbXkz5Ed64WP41EMUxT7Pnoqtrz0P560w0C13hc0ildyH02cB0poukm/5HB4Z859IVrTv8va1PP6Bz/Z8Zp/uHaVRxKOyLa/RnOVwc=
*/
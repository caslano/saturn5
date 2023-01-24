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
JMSEDU5RmF+TG2RjSOeiGzlHZToBhBW3R359L9NYb9aAes0Lsv0s86GNWxjy+DGUsHv2AJyiNtyPozdGV0EBbm9l5awgc5+QAFBdhH1/oPTTbi1SdW9+Q0/pap/D2aBAw+lHZTav/HMESz6QNPv2qtSyGoL3EbWbaz6EU3lcvA5lCksPrQrFF8UX9RblFrXtGNzf3K4ACj0xlKAuf92oxdzygahU7d1e0ieVhQ/sPJfBrcksVUcT94b6gaZe53xX479pQ+riXj7w6LsfLGo6nyq3Ml6iFxRhv+5oHGbBvttnfBRJ9t7IEiDJJkRtJavafA3rQwTdLo/NrC4GE5R12P11mPkwrgfewjZSwYTDHrqW5snCG/xHHsunkTSytsnIZxi2KfGc8iVC3e/shZ22FDqcElUGN2Gw98jlDJq1QxrGDPbRHQaeLE2gIZKURFrdEySpg/l+MzRWPd2laywU2bBd3z6JRlI8Buu+hrugIifSlYsMTYGtmoQSc7vkY0grFBmYpzDm/QHn4Eku8i9UJ1QrOjZk/xGSyCbrJRc6J3YNyh/c9oTU6Tq0Gqwa1MyPIFRX1DOUM1RKFKES+BhzaiDKJYYblhvqItopiinq3UcsWbJ6/HrqevR64nq82b9W8dvV6tpID6R3V2OcZApwZl84zT3X/ubEZPHfsk5VRvlb1ygPaIno66gskExdVgnVmrvqzESj53ucag5r
*/
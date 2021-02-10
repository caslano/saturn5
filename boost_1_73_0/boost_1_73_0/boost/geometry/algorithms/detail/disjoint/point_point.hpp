// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_POINT_HPP

#include <cstddef>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>

// For backward compatibility
#include <boost/geometry/strategies/disjoint.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


/*!
    \brief Internal utility function to detect of points are disjoint
    \note To avoid circular references
 */
template <typename Point1, typename Point2, typename Strategy>
inline bool disjoint_point_point(Point1 const& point1, Point2 const& point2,
                                 Strategy const& )
{
    return ! Strategy::apply(point1, point2);
}


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Point1, typename Point2, std::size_t DimensionCount>
struct disjoint<Point1, Point2, DimensionCount, point_tag, point_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Point1 const& point1, Point2 const& point2,
                             Strategy const& )
    {
        return ! Strategy::apply(point1, point2);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_POINT_HPP

/* point_point.hpp
qxN7xa1UdcUY47EVjQDHqtD/ulX/cT6ogA3/9LA1b+lfNfuCg9KM2hYltAAx4JtND5Qqmo0Kb/pwyy+17izzPMBWcGeh28q5b5dxatEOA8ccM4uqwnsOETO8k/bg0HEPDoNvEhRgMMCI48M2WezTLqZ6FPQJIFfSe62SS5Me6XWiPrqe9hPODGqGlAzjm3oE7WrgFkP/f+6BYzWh6R1Q2jvXEKEpLpNk55PE+d2wscD2fiJM5iqBfQ5E10WgRENlGKWW2kSH8C786i6CzBSwlbtEO0TAX33XJ9Xw2G632lDGxS5ya1UXpPnWe0IKwEaQ42c6RbK1T9d5sNmYIU9g0W7XtakyWeroi5RVY7nSjNKCUINg2FGtBqwcq/QYFZadhDX/Jai0jAWnnwDrXmAYublvUvWWGRcQyzXNwOC/24n4Z9FhoHgmXjPuZcV7b+1LZcWp55hU0Z96nklGAxJMnLFsHKgTj5nk3QE0H6FboYXz3FwENWe3THTi7zKxWGir8LKZ5r7e0Ww5V7MFzmZz3c2W9SFcRBCWdxqs99arqyu9RCS2xMRKxHlkvRwouk38P7QQkcWODdexMaBIhLkY8OOj96esiaC42zlxxDpLix3ESbjEhUwVuwtxogf0w2vZEp6pGiU3PUr1Sj7u
*/
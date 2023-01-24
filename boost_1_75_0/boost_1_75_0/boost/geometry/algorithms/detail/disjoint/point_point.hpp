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
NeK+cDz/Yf8Njcn6hP7mKVwpnjNrAAG5E/i9Qq4z9x4Oo0gILjOh+LUtGTkCEfcNehnhzumBiDufXn5ML9voJSNIjZb0kqSX2+CCZ2N/9zXQDN3XrYQLfpywNdILXsSewzbZ7DA0nj/MZbPjh53r/1aKF7GNLELlNrwIJy350Owr/RVY/0dg/x/hfWUesU4MiuG0Pl09irdi8gAei3xkKuqjv/Ijtv00Dhp3HBHyT7f+RhL5OMYnUAGew/r6Atvkw0dMDDKoPA/lyhHmP8C9Zyypgruicc+MVu4/8Cfrzm0XgF9tuS6Y7cJtJCLlyueU/i41M0M+Io0lNbDTg3gmsKyT5RjqY63n/sa2bqZHQmgYfCB9Kta6Gcs3IBXLV/sbW17Uemj88DecVt/5G+tdNf/Fi/qn60MxPkkK8SKYkybm1J56/04dyB6zz8NQeRrKq78xc1yaOhCW4/JMt1vcKhlPUQ1Cu1QIonoBaZJ0i6fsJQ+MftT2LgdB48aj/F0OPup8l1tdwOsAoS2AsdP+8vsh//xByA+8lB94KT/wUtlXr+vKahf5v44KeWkBVI5BOQfFZ5eX6mypqtoLLa1OSl7qA9N4HMHY433aGl7bwA+86B697AI+SsJSklTJucrTejOO6oVamVqmxOQYKdRjWqvR6q7wDMfehDug5aN1VLdHlWG6jynTDQZezs+v/iksq4InbfvwJmjc9iTf
*/
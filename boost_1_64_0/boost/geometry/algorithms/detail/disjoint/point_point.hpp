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
xaDd/nL/6FJRYyyh103+stPAhS3lU2K43ksxqhGP0beaxjW+HNOqvFOD77JK6iKHpZg6WlEIu23OWaD7/Ey4mnHpVOG7S9DwnNl8VZYhugPcZu5zfd4IK95WsBVCrMA2n+nyDAEyIsPshKU7DLUP992vo+8UEwsx4cYFDFIGPxTk86OzCFrc31SGqhBtA16fJ0/vLnBgXSxI0SQUzhpiv68Y1R3oGDdZoKEcQ3lvD73Z9zq3gfEsQryc9pbO9v2LT2vd1weSUj7yBCYr0KUsXRE86boT0CL66UIDLw7wx/n0bn881MiWJhFXk6YW/SLydnvZ/JoCpcu7b97W3LDAUlWwkJmJLDqNUc7F4MdowrNHcW20X0HP1Xj9hHX3k6smRP7oLh3slnRLrUp0GGrSmaOX7eOfiFqPW9J+5m1HMAiasjQwJNbDhVtJzlp2D8osCoUIhCJ3f4o9E9e56P7Y7HsJ4P2Np6nD15dA7793iEyvGYjOn8O06EjuX2jk61uoHnIv2UeTKEjlhjcfED6YHwufhlKMZYI7YDeHUYoJeEAELykCIQdrO41zYg==
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace equals
{

/*!
    \brief Internal utility function to detect of points are disjoint
    \note To avoid circular references
 */
template <typename Point1, typename Point2, typename Strategy>
inline bool equals_point_point(Point1 const& point1, Point2 const& point2,
                               Strategy const& )
{
    return Strategy::apply(point1, point2);
}

}} // namespace detail::equals
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_POINT_POINT_HPP

/* point_point.hpp
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
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020, Oracle and/or its affiliates.

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
#include <type_traits>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>

#include <boost/geometry/strategies/detail.hpp>

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
template
<
    typename Point1, typename Point2, typename Strategy,
    std::enable_if_t<strategies::detail::is_umbrella_strategy<Strategy>::value, int> = 0
>
inline bool disjoint_point_point(Point1 const& point1, Point2 const& point2,
                                 Strategy const& strategy)
{
    typedef decltype(strategy.relate(point1, point2)) strategy_type;
    // ! within(point1, point2)
    return ! strategy_type::apply(point1, point2);
}

template
<
    typename Point1, typename Point2, typename Strategy,
    std::enable_if_t<! strategies::detail::is_umbrella_strategy<Strategy>::value, int> = 0
>
inline bool disjoint_point_point(Point1 const& point1, Point2 const& point2,
                                 Strategy const& )
{
    // ! within(point1, point2)
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
                             Strategy const& strategy)
    {
        typedef decltype(strategy.relate(point1, point2)) strategy_type;
        // ! within(point1, point2)
        return ! strategy_type::apply(point1, point2);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_POINT_HPP

/* point_point.hpp
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
*/
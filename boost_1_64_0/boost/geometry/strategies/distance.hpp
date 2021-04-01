// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DISTANCE_HPP
#define BOOST_GEOMETRY_STRATEGIES_DISTANCE_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace distance { namespace services
{


template <typename Strategy> struct tag {};

template <typename Strategy, typename P1, typename P2>
struct return_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_STRATEGY, (types<Strategy, P1, P2>)
        );
};


template <typename Strategy> struct comparable_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_STRATEGY, (types<Strategy>)
        );
};

template <typename Strategy> struct get_comparable
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_STRATEGY, (types<Strategy>)
        );
};

template <typename Strategy, typename P1, typename P2>
struct result_from_distance {};




// Default strategy


/*!
    \brief Traits class binding a default strategy for distance
        to one (or possibly two) coordinate system(s)
    \ingroup distance
    \tparam GeometryTag1 tag (point/segment/box) for which this strategy is the default
    \tparam GeometryTag2 tag (point/segment/box) for which this strategy is the default
    \tparam Point1 first point-type
    \tparam Point2 second point-type
    \tparam CsTag1 tag of coordinate system of first point type
    \tparam CsTag2 tag of coordinate system of second point type
*/
template
<
    typename GeometryTag1,
    typename GeometryTag2,
    typename Point1,
    typename Point2 = Point1,
    typename CsTag1 = typename cs_tag<Point1>::type,
    typename CsTag2 = typename cs_tag<Point2>::type,
    typename UnderlyingStrategy = void
>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPE_COMBINATION
            , (types<Point1, Point2, CsTag1, CsTag2>)
        );
};


}}} // namespace strategy::distance::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DISTANCE_HPP

/* distance.hpp
B/xHlym5VnzXW2WkApa9sjMDvA3jkOtH6C6DAf5x0qM+TpFroL7+82e6T5LVGGZmZ4sS1C+1PdQm5Fk1Vq5Y9p/umSquQ9lHyXG0iUwu99txLmKFEmwsnVV5nbH3fXh/xm4gMlgFqksNREjntvzo5FnbhgS87bysu+zDDcMi6DzzFFDxqNx1l4jdntTnpWOw4tzoHSfsRXWwY5IVJp7pX12bVpgItl8yDoIZpdGqeYz5zX2Ughdsy7njgNyATNdoRLjqkre3mXCgyOejAcsEx3qmOHGTcozAHfpB1A8Zg5WiBxPLIm4uRwFmZuPD+LaTs2RZe16L/jqxr9OD3DCZV5UUYNEMawLwxT/Aet56CMhBDZtkWWVY3i4noiQ5zUfE5+6dL+CLk8YOlEhIu4JrMZFSu5aVrB+31s+XPd05Zct3aZ2bhLyUFVmXWyCZj80XxN7eCBIizQXHv8zgn2DFLyguGCSZEyWoGyinM02h8T++Nw5NKfkSyffH+Z3MJ9jzC3+lYlgFDzfFGmo+ceB7pyBz5iSWDnZb7hNy9FhlL5H9yP1gwqmMQIJwaQ==
*/
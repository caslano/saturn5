// Boost.Geometry

// Copyright (c) 2016-2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP


#include <boost/geometry/strategies/tags.hpp>


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace intersection
{

namespace services
{

/*!
\brief Traits class binding a segments intersection strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system of point-type
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::intersection

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP

/* intersection.hpp
jlGI11bZsvgNfob7KeoPQ+7SLP013vGMpbOV8Qh7FYlXq9yJ6r/TkyIpvvZEpCoKHWWDzz0glII/mAakUuPQ3hCtxEDMLdpB82vuZuuNjnz488qlGZZs71U13FiPuLlKanmqM4hp8MrKfkQL5uEcpZ7xKcuhQjxGbkNzPXJk31ubqXy++5Fc6qOpdPhN1GJVmqnU4KhQkBr2eiJmhUuOtXKQZzLiGO9ShEvx191Jsxfs0PdWzJGfNKqckZlYak750dvTc1AMD6csElzvyFM2eMenEVn08cdgVkZZI7w4/09nRkylNtGCEZs/K8qYZKbPfiiuHRDEeTGIn7UWp2eCZ3fb7Zn0ZycyPynSTmBf2ms029PhGJswFYC4BQ80HOnf3ojXob7SHzCrKLSuwGxS17CkL7UuAnSkxIQ1+81gWaDR3WHkglfJyghhnwc1obJup2AB5+V20Ha2moWgY7pG+aHrO0DpSjkXWj8DZQuB+1s9iq7c7ha+Na53N3j3aObr652gui4jOKhOGWjDML1MtsJxeHLr5emORYOjkEShb6nMUGKQpP8lyvBC8v6ua1KZag/6W1Oea6ZIw36ljdg19pRRkej37AUgQ56qmZvLU74lqs2skf49p1IfywFeRf5qq1kUVbQ9cXZT+oMpbR+egX//pzsMU1EegcISbhKR4CNSjqak9oS6Qh5pzoXC6BGRlKvwWGKFqbh3c3zl
*/
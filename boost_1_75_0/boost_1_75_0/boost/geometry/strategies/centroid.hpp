// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CENTROID_HPP
#define BOOST_GEOMETRY_STRATEGIES_CENTROID_HPP


#include <cstddef>

#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace centroid
{

struct not_applicable_strategy
{
};


namespace services
{

/*!
    \brief Traits class binding a centroid calculation strategy to a coordinate system
    \ingroup centroid
    \tparam CsTag tag of coordinate system, for specialization
    \tparam GeometryTag tag of geometry, for specialization
    \tparam Dimension dimension of geometry, for specialization
    \tparam Point point-type
    \tparam Geometry
*/
template
<
    typename CsTag,
    typename GeometryTag,
    std::size_t Dimension,
    typename Point,
    typename Geometry
>
struct default_strategy
{
    typedef not_applicable_strategy type;
};


} // namespace services


}} // namespace strategy::centroid


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CENTROID_HPP

/* centroid.hpp
vQQ9R1MvrE2U5pXmR53GhHaUbD6HZ596oYGqakIlx/lNOIME7BpZ0hO1TcBBHIyL665cSc9nTs4jlm24/EMCeGx9q4QHeiX9y79mg8omgjwnv7qoK6/fV3aAKWZIJac5djr4bqQcWUVD96DkomSqtlDqDC+6r5hDTYbiLgE8bH4nmMFTelWieWqytoDrYezkkjAQ0bcLiypuxiPe2LQMH7osEb7PWSMeK88WG0dlR+W0DqoLlM6/co7Urr/+ji7cSDb4Bzva9+RL0qfDr38CyMs7O+xYSb3fWpx6MnKSblVWRNhMXO4r7XrmlUysqODbYAeyLh1sum7VOK4ISRPwyaZuCEYaqmClE9e7zHRkjx90iP5sQjPZJ+TW0MpIVbbdlZ6GHDHXworPw79ALMb48fNsSzL6qY5MDt593SWZB0wi3uQdf85K8cz6kjXG6ieQmphF2upqsxU5UmN4cPiKnYo3fh/Xw5pWGIZB9Zen5qDPwyRbddNpeiGqRKSeSLKkeMKjdcjEdX9ltlQ7G/30+IaqCPX414AXlo8dok0qIWl6dcHzrNjdn6qHGrSCDQf6p1CXaZ8frCWgXOLmRdrd7sGo2ZuZ99FhmTBa+FufpmRoeb3+Ez+QRPQvPykEC+69EVQ7ogtsQXJclgqAWERmkIxk3kzm3h1YV+bxyrBwk8Zl7y56qyBacUi6XGmI+mxG4qm82RxppeU+5UEF
*/
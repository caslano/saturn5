// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/azimuth.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace azimuth
{

template
<
    typename CalculationType = void
>
class cartesian
{};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<cartesian_tag, CalculationType>
{
    typedef strategy::azimuth::cartesian<CalculationType> type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}} // namespace strategy::azimuth


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP

/* azimuth.hpp
vG3utyDAC+jKHvt+RZWIy6uovmnP3QnprR1TQFOPSKG8cWb3PavdeNYMD6SqAIou09mVfOcFqWzT9DCjEIeU2z89CPGg9csq2ECHJfBaGfMzPtW0J/D9b+dBfLEJcUhqjjNjlSnncWEyJTPGF+fC5MaDMkQmYr4IZKMIVrysv5q5uFW/HQ2AhtQHOjyk9ZP8UiOZN3uF8riLs/nS1DoAwtQxjDW9zGAS2mNWV+G/K/vb4bmhEL3STtZQje6D3RYkNVrojW3STbVG4AcOoyXyCiBMtPdo1jUEEjaQcxGHmh8/V5+SxrsseUoFN8L2OQGr8u2PtP70tpexr+ADiiWQJwIxZTLTziNKcZMJqG56X6gnnaCxI6T/P1KHTDlyblM2sWTS7+mct9zwsBSvCWDSypjN/YdVwUY6moLReEFOg67jD3fDxsML3O7viB29h0iAs/OBE38BAjzBLoAV1NTkiIOfwznjjeOgUYyBf/BYfj8J5V1T7llcTkGK1iPTNp0yF2Zs+KDcffwW82wzMgGfTYvj2R7XSXAsy/mv5BDgMsW7gglJL/7IYegixA==
*/
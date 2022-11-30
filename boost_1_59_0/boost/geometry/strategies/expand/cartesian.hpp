// Boost.Geometry

// Copyright (c) 2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_EXPAND_CARTESIAN_HPP
#define BOOST_GEOMETRY_STRATEGIES_EXPAND_CARTESIAN_HPP


#include <type_traits>

#include <boost/geometry/strategy/cartesian/expand_box.hpp>
#include <boost/geometry/strategy/cartesian/expand_point.hpp>
#include <boost/geometry/strategy/cartesian/expand_segment.hpp>

#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/expand/services.hpp>


namespace boost { namespace geometry
{


namespace strategies { namespace expand
{


template <typename CalculationType = void>
struct cartesian
    : strategies::detail::cartesian_base
{
    template <typename Box, typename Geometry>
    static auto expand(Box const&, Geometry const&,
                       typename util::enable_if_point_t<Geometry> * = nullptr)
    {
        return strategy::expand::cartesian_point();
    }

    template <typename Box, typename Geometry>
    static auto expand(Box const&, Geometry const&,
                       typename util::enable_if_box_t<Geometry> * = nullptr)
    {
        return strategy::expand::cartesian_box();
    }

    template <typename Box, typename Geometry>
    static auto expand(Box const&, Geometry const&,
                       typename util::enable_if_segment_t<Geometry> * = nullptr)
    {
        return strategy::expand::cartesian_segment();
    }
};


namespace services
{

template <typename Box, typename Geometry>
struct default_strategy<Box, Geometry, cartesian_tag>
{
    using type = strategies::expand::cartesian<>;
};


template <>
struct strategy_converter<strategy::expand::cartesian_point>
{
    static auto get(strategy::expand::cartesian_point const& )
    {
        return strategies::expand::cartesian<>();
    }
};

template <>
struct strategy_converter<strategy::expand::cartesian_box>
{
    static auto get(strategy::expand::cartesian_box const& )
    {
        return strategies::expand::cartesian<>();
    }
};

template <>
struct strategy_converter<strategy::expand::cartesian_segment>
{
    static auto get(strategy::expand::cartesian_segment const&)
    {
        return strategies::expand::cartesian<>();
    }
};


} // namespace services

}} // namespace strategies::envelope

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_EXPAND_CARTESIAN_HPP

/* cartesian.hpp
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
*/
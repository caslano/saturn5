// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_CARTESIAN_HPP
#define BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_CARTESIAN_HPP


#include <boost/geometry/strategies/agnostic/simplify_douglas_peucker.hpp>
#include <boost/geometry/strategies/cartesian/distance_projected_point.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>

#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/distance/comparable.hpp>
#include <boost/geometry/strategies/distance/detail.hpp>
#include <boost/geometry/strategies/simplify/services.hpp>

#include <boost/geometry/strategy/cartesian/area.hpp>

#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace simplify
{

template <typename CalculationType = void>
struct cartesian
    : public strategies::detail::cartesian_base
{
    // TODO: Replace this if calculate_point_order() is used in simplify
    template <typename Geometry>
    static auto area(Geometry const&)
    {
        return strategy::area::cartesian<CalculationType>();
    }

    // For perimeter()
    template <typename Geometry1, typename Geometry2>
    static auto distance(Geometry1 const&, Geometry2 const&,
                         distance::detail::enable_if_pp_t<Geometry1, Geometry2> * = nullptr)
    {
        return strategy::distance::pythagoras<CalculationType>();
    }

    // For douglas_peucker
    template <typename Geometry1, typename Geometry2>
    static auto distance(Geometry1 const&, Geometry2 const&,
                         distance::detail::enable_if_ps_t<Geometry1, Geometry2> * = nullptr)
    {
        return strategy::distance::projected_point
            <
                CalculationType,
                strategy::distance::pythagoras<CalculationType>
            >();
    }

    // For equals()
    template <typename Geometry1, typename Geometry2>
    static auto relate(Geometry1 const&, Geometry2 const&,
                       std::enable_if_t
                            <
                                util::is_pointlike<Geometry1>::value
                             && util::is_pointlike<Geometry2>::value
                            > * = nullptr)
    {
        return strategy::within::cartesian_point_point();
    }
};


namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, cartesian_tag>
{
    using type = strategies::simplify::cartesian<>;
};


template <typename P, typename CT, typename S>
struct strategy_converter
    <
        strategy::simplify::douglas_peucker
            <
                P,
                strategy::distance::projected_point<CT, S>
            >
    >
{
    template <typename Strategy>
    static auto get(Strategy const& )
    {
        typedef strategies::simplify::cartesian<CT> strategy_type;
        return std::conditional_t
            <
                std::is_same
                    <
                        S,
                        typename strategy::distance::services::comparable_type<S>::type
                    >::value,
                strategies::distance::detail::comparable<strategy_type>,
                strategy_type
            >();
    }
};


} // namespace services

}} // namespace strategies::simplify

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_CARTESIAN_HPP

/* cartesian.hpp
+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
*/
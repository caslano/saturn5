// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_SPHERICAL_HPP
#define BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_SPHERICAL_HPP


#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/distance/comparable.hpp>
#include <boost/geometry/strategies/distance/detail.hpp>
#include <boost/geometry/strategies/simplify/services.hpp>

#include <boost/geometry/strategies/agnostic/simplify_douglas_peucker.hpp>
#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>

#include <boost/geometry/strategy/spherical/area.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace simplify
{

template
<
    typename RadiusTypeOrSphere = double,
    typename CalculationType = void
>
class spherical
    : public strategies::detail::spherical_base<RadiusTypeOrSphere>
{
    using base_t = strategies::detail::spherical_base<RadiusTypeOrSphere>;

public:
    spherical() = default;

    template <typename RadiusOrSphere>
    explicit spherical(RadiusOrSphere const& radius_or_sphere)
        : base_t(radius_or_sphere)
    {}

    // TODO: Replace this if calculate_point_order() is used in simplify
    template <typename Geometry>
    auto area(Geometry const&) const
    {
        return strategy::area::spherical
            <
                typename base_t::radius_type, CalculationType
            >(base_t::radius());
    }

    // For perimeter()
    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  distance::detail::enable_if_pp_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::haversine
                <
                    typename base_t::radius_type, CalculationType
                >(base_t::radius());
    }

    // For douglas_peucker
    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  distance::detail::enable_if_ps_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::cross_track
            <
                CalculationType,
                strategy::distance::haversine<typename base_t::radius_type, CalculationType>
            >(base_t::radius());
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
        return strategy::within::spherical_point_point();
    }
};


namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, spherical_equatorial_tag>
{
    using type = strategies::simplify::spherical<>;
};

template <typename P, typename CT, typename S>
struct strategy_converter
    <
        strategy::simplify::douglas_peucker
            <
                P,
                strategy::distance::cross_track<CT, S>
            >
    >
{
    template <typename Strategy>
    static auto get(Strategy const& )
    {
        return strategies::simplify::spherical<typename S::radius_type, CT>();
    }
};

template <typename P, typename CT, typename S>
struct strategy_converter
    <
        strategy::simplify::douglas_peucker
            <
                P,
                strategy::distance::comparable::cross_track<CT, S>
            >
    >
{
    template <typename Strategy>
    static auto get(Strategy const& )
    {
        return strategies::distance::detail::comparable
            <
                strategies::simplify::spherical<typename S::radius_type, CT>
            >();
    }
};


} // namespace services

}} // namespace strategies::simplify

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_SPHERICAL_HPP

/* spherical.hpp
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
*/
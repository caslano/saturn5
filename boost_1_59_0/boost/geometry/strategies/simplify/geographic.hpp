// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_GEOGRAPHIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_GEOGRAPHIC_HPP


#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/distance/detail.hpp>
#include <boost/geometry/strategies/simplify/services.hpp>

#include <boost/geometry/strategies/agnostic/simplify_douglas_peucker.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>

#include <boost/geometry/strategy/geographic/area.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace simplify
{

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
    : public strategies::detail::geographic_base<Spheroid>
{
    using base_t = strategies::detail::geographic_base<Spheroid>;

public:
    geographic() = default;

    explicit geographic(Spheroid const& spheroid)
        : base_t(spheroid)
    {}

    // TODO: Replace this if calculate_point_order() is used in simplify
    template <typename Geometry>
    auto area(Geometry const&) const
    {
        return strategy::area::geographic
            <
                FormulaPolicy,
                strategy::default_order<FormulaPolicy>::value,
                Spheroid,
                CalculationType
            >(base_t::m_spheroid);
    }

    // For perimeter()
    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  distance::detail::enable_if_pp_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic
                <
                    FormulaPolicy, Spheroid, CalculationType
                >(base_t::m_spheroid);
    }

    // For douglas_peucker
    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  distance::detail::enable_if_ps_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic_cross_track
            <
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
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
struct default_strategy<Geometry, geographic_tag>
{
    using type = strategies::simplify::geographic<>;
};


template <typename P, typename FP, typename S, typename CT>
struct strategy_converter
    <
        strategy::simplify::douglas_peucker
            <
                P,
                strategy::distance::geographic_cross_track<FP, S, CT>
            >
    >
{
    template <typename Strategy>
    static auto get(Strategy const& )
    {
        return strategies::simplify::geographic<FP, S, CT>();
    }
};


} // namespace services

}} // namespace strategies::simplify

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SIMPLIFY_GEOGRAPHIC_HPP

/* geographic.hpp
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
*/
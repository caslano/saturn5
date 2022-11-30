// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_EXPAND_SPHERICAL_HPP
#define BOOST_GEOMETRY_STRATEGIES_EXPAND_SPHERICAL_HPP


#include <type_traits>

#include <boost/geometry/strategy/spherical/expand_box.hpp>
#include <boost/geometry/strategy/spherical/expand_point.hpp>
#include <boost/geometry/strategy/spherical/expand_segment.hpp>

#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/expand/services.hpp>


namespace boost { namespace geometry
{


namespace strategies { namespace expand
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename RadiusTypeOrSphere, typename CalculationType>
struct spherical
    : strategies::detail::spherical_base<RadiusTypeOrSphere>
{
    spherical() = default;

    template <typename RadiusOrSphere>
    explicit spherical(RadiusOrSphere const& radius_or_sphere)
        : strategies::detail::spherical_base<RadiusTypeOrSphere>(radius_or_sphere)
    {}

    template <typename Box, typename Geometry>
    static auto expand(Box const&, Geometry const&,
                       typename util::enable_if_point_t<Geometry> * = nullptr)
    {
        return strategy::expand::spherical_point();
    }

    template <typename Box, typename Geometry>
    static auto expand(Box const&, Geometry const&,
                       typename util::enable_if_box_t<Geometry> * = nullptr)
    {
        return strategy::expand::spherical_box();
    }

    template <typename Box, typename Geometry>
    static auto expand(Box const&, Geometry const&,
                       typename util::enable_if_segment_t<Geometry> * = nullptr)
    {
        return strategy::expand::spherical_segment<CalculationType>();
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template <typename CalculationType = void>
class spherical
    : public strategies::expand::detail::spherical<void, CalculationType>
{};


namespace services
{

template <typename Box, typename Geometry>
struct default_strategy<Box, Geometry, spherical_tag>
{
    using type = strategies::expand::spherical<>;
};

template <typename Box, typename Geometry>
struct default_strategy<Box, Geometry, spherical_equatorial_tag>
{
    using type = strategies::expand::spherical<>;
};

template <typename Box, typename Geometry>
struct default_strategy<Box, Geometry, spherical_polar_tag>
{
    using type = strategies::expand::spherical<>;
};


template <>
struct strategy_converter<strategy::expand::spherical_point>
{
    static auto get(strategy::expand::spherical_point const& )
    {
        return strategies::expand::spherical<>();
    }
};

template <>
struct strategy_converter<strategy::expand::spherical_box>
{
    static auto get(strategy::expand::spherical_box const& )
    {
        return strategies::expand::spherical<>();
    }
};

template <typename CT>
struct strategy_converter<strategy::expand::spherical_segment<CT> >
{
    static auto get(strategy::expand::spherical_segment<CT> const&)
    {
        return strategies::expand::spherical<CT>();
    }
};


} // namespace services

}} // namespace strategies::envelope

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_EXPAND_SPHERICAL_HPP

/* spherical.hpp
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
*/
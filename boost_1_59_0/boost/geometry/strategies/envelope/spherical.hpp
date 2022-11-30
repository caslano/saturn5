// Boost.Geometry

// Copyright (c) 2020-2022, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_ENVELOPE_SPHERICAL_HPP
#define BOOST_GEOMETRY_STRATEGIES_ENVELOPE_SPHERICAL_HPP


#include <type_traits>

#include <boost/geometry/strategy/spherical/envelope_box.hpp>
#include <boost/geometry/strategy/spherical/envelope_boxes.hpp>
#include <boost/geometry/strategy/spherical/envelope_multipoint.hpp>
#include <boost/geometry/strategy/spherical/envelope_point.hpp>
#include <boost/geometry/strategy/spherical/envelope_range.hpp>
#include <boost/geometry/strategy/spherical/envelope_segment.hpp>

#include <boost/geometry/strategies/envelope/services.hpp>
#include <boost/geometry/strategies/expand/spherical.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace envelope
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename RadiusTypeOrSphere, typename CalculationType>
struct spherical
    : strategies::expand::detail::spherical<RadiusTypeOrSphere, CalculationType>
{
    spherical() = default;

    template <typename RadiusOrSphere>
    explicit spherical(RadiusOrSphere const& radius_or_sphere)
        : strategies::expand::detail::spherical<RadiusTypeOrSphere, CalculationType>(radius_or_sphere)
    {}

    template <typename Geometry, typename Box>
    static auto envelope(Geometry const&, Box const&,
                         util::enable_if_point_t<Geometry> * = nullptr)
    {
        return strategy::envelope::spherical_point();
    }

    template <typename Geometry, typename Box>
    static auto envelope(Geometry const&, Box const&,
                         util::enable_if_multi_point_t<Geometry> * = nullptr)
    {
        return strategy::envelope::spherical_multipoint();
    }

    template <typename Geometry, typename Box>
    static auto envelope(Geometry const&, Box const&,
                         util::enable_if_box_t<Geometry> * = nullptr)
    {
        return strategy::envelope::spherical_box();
    }

    template <typename Geometry, typename Box>
    static auto envelope(Geometry const&, Box const&,
                         util::enable_if_segment_t<Geometry> * = nullptr)
    {
        return strategy::envelope::spherical_segment<CalculationType>();
    }

    template <typename Geometry, typename Box>
    static auto envelope(Geometry const&, Box const&,
                         util::enable_if_linestring_t<Geometry> * = nullptr)
    {
        return strategy::envelope::spherical_linestring<CalculationType>();
    }

    template <typename Geometry, typename Box>
    static auto envelope(Geometry const&, Box const&,
                         std::enable_if_t
                            <
                                util::is_ring<Geometry>::value
                             || util::is_polygon<Geometry>::value
                            > * = nullptr)
    {
        return strategy::envelope::spherical_ring<CalculationType>();
    }

    template <typename Geometry, typename Box>
    static auto envelope(Geometry const&, Box const&,
                         std::enable_if_t
                            <
                                util::is_multi_linestring<Geometry>::value
                             || util::is_multi_polygon<Geometry>::value
                             || util::is_geometry_collection<Geometry>::value
                            > * = nullptr)
    {
        return strategy::envelope::spherical_boxes();
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template <typename CalculationType = void>
class spherical
    : public strategies::envelope::detail::spherical<void, CalculationType>
{};


namespace services
{

template <typename Geometry, typename Box>
struct default_strategy<Geometry, Box, spherical_tag>
{
    using type = strategies::envelope::spherical<>;
};

template <typename Geometry, typename Box>
struct default_strategy<Geometry, Box, spherical_equatorial_tag>
{
    using type = strategies::envelope::spherical<>;
};

template <typename Geometry, typename Box>
struct default_strategy<Geometry, Box, spherical_polar_tag>
{
    using type = strategies::envelope::spherical<>;
};


template <>
struct strategy_converter<strategy::envelope::spherical_point>
{
    static auto get(strategy::envelope::spherical_point const& )
    {
        return strategies::envelope::spherical<>();
    }
};

template <>
struct strategy_converter<strategy::envelope::spherical_multipoint>
{
    static auto get(strategy::envelope::spherical_multipoint const&)
    {
        return strategies::envelope::spherical<>();
    }
};

template <>
struct strategy_converter<strategy::envelope::spherical_box>
{
    static auto get(strategy::envelope::spherical_box const& )
    {
        return strategies::envelope::spherical<>();
    }
};

template <typename CT>
struct strategy_converter<strategy::envelope::spherical_segment<CT> >
{
    static auto get(strategy::envelope::spherical_segment<CT> const&)
    {
        return strategies::envelope::spherical<CT>();
    }
};

template <typename CT>
struct strategy_converter<strategy::envelope::spherical<CT> >
{
    static auto get(strategy::envelope::spherical<CT> const&)
    {
        return strategies::envelope::spherical<CT>();
    }
};


} // namespace services

}} // namespace strategies::envelope

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_ENVELOPE_SPHERICAL_HPP

/* spherical.hpp
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
*/
// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_AREA_SPHERICAL_HPP
#define BOOST_GEOMETRY_STRATEGIES_AREA_SPHERICAL_HPP


#include <boost/geometry/strategy/spherical/area.hpp>
#include <boost/geometry/strategy/spherical/area_box.hpp>

#include <boost/geometry/strategies/area/services.hpp>
#include <boost/geometry/strategies/detail.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace area
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
    spherical()
        : base_t()
    {}

    template <typename RadiusOrSphere>
    explicit spherical(RadiusOrSphere const& radius_or_sphere)
        : base_t(radius_or_sphere)
    {}

    template <typename Geometry>
    auto area(Geometry const&,
              std::enable_if_t<! util::is_box<Geometry>::value> * = nullptr) const
    {
        return strategy::area::spherical
            <
                typename base_t::radius_type, CalculationType
            >(base_t::m_radius);
    }

    template <typename Geometry>
    auto area(Geometry const&,
              std::enable_if_t<util::is_box<Geometry>::value> * = nullptr) const
    {
        return strategy::area::spherical_box
            <
                typename base_t::radius_type, CalculationType
            >(base_t::m_radius);
    }
};


namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, spherical_tag>
{
    using type = strategies::area::spherical<>;
};

template <typename Geometry>
struct default_strategy<Geometry, spherical_equatorial_tag>
{
    using type = strategies::area::spherical<>;
};

template <typename Geometry>
struct default_strategy<Geometry, spherical_polar_tag>
{
    using type = strategies::area::spherical<>;
};


template <typename R, typename CT>
struct strategy_converter<strategy::area::spherical<R, CT> >
{
    static auto get(strategy::area::spherical<R, CT> const& strategy)
    {
        return strategies::area::spherical<R, CT>(strategy.model());
    }
};


} // namespace services

}} // namespace strategies::area

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AREA_SPHERICAL_HPP

/* spherical.hpp
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
*/
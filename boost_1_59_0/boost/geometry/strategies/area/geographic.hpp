// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_AREA_GEOGRAPHIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_AREA_GEOGRAPHIC_HPP


#include <boost/geometry/strategy/geographic/area.hpp>
#include <boost/geometry/strategy/geographic/area_box.hpp>

#include <boost/geometry/strategies/area/services.hpp>
#include <boost/geometry/strategies/detail.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace area
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

    template <typename Geometry>
    auto area(Geometry const&,
              std::enable_if_t<! util::is_box<Geometry>::value> * = nullptr) const
    {
        return strategy::area::geographic
            <
                FormulaPolicy,
                strategy::default_order<FormulaPolicy>::value,
                Spheroid, CalculationType
            >(base_t::m_spheroid);
    }

    template <typename Geometry>
    auto area(Geometry const&,
              std::enable_if_t<util::is_box<Geometry>::value> * = nullptr) const
    {
        return strategy::area::geographic_box
            <
                Spheroid, CalculationType
            >(base_t::m_spheroid);
    }
};


namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, geographic_tag>
{
    using type = strategies::area::geographic<>;
};


template <typename FP, std::size_t SO, typename S, typename CT>
struct strategy_converter<strategy::area::geographic<FP, SO, S, CT> >
{
    struct altered_strategy
        : strategies::area::geographic<FP, S, CT>
    {
        explicit altered_strategy(S const& spheroid)
            : strategies::area::geographic<FP, S, CT>(spheroid)
        {}

        using strategies::area::geographic<FP, S, CT>::area;

        template <typename Geometry>
        auto area(Geometry const&,
                  std::enable_if_t<! util::is_box<Geometry>::value> * = nullptr) const
        {
            return strategy::area::geographic<FP, SO, S, CT>(this->m_spheroid);
        }
    };

    static auto get(strategy::area::geographic<FP, SO, S, CT> const& strategy)
    {
        return altered_strategy(strategy.model());
    }
};

} // namespace services

}} // namespace strategies::area

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AREA_GEOGRAPHIC_HPP

/* geographic.hpp
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
*/
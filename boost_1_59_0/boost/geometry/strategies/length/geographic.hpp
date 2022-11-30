// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_LENGTH_GEOGRAPHIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_LENGTH_GEOGRAPHIC_HPP


#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/distance/detail.hpp>
#include <boost/geometry/strategies/length/services.hpp>

#include <boost/geometry/strategies/geographic/distance.hpp>
// TODO - for backwards compatibility, remove?
#include <boost/geometry/strategies/geographic/distance_andoyer.hpp>
#include <boost/geometry/strategies/geographic/distance_thomas.hpp>
#include <boost/geometry/strategies/geographic/distance_vincenty.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace length
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

    template <typename Geometry1, typename Geometry2>
    auto distance(Geometry1 const&, Geometry2 const&,
                  distance::detail::enable_if_pp_t<Geometry1, Geometry2> * = nullptr) const
    {
        return strategy::distance::geographic
                <
                    FormulaPolicy, Spheroid, CalculationType
                >(base_t::m_spheroid);
    }
};


namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, geographic_tag>
{
    using type = strategies::length::geographic<>;
};


template <typename FP, typename S, typename CT>
struct strategy_converter<strategy::distance::geographic<FP, S, CT> >
{
    static auto get(strategy::distance::geographic<FP, S, CT> const& s)
    {
        return strategies::length::geographic<FP, S, CT>(s.model());
    }
};
// TODO - for backwards compatibility, remove?
template <typename S, typename CT>
struct strategy_converter<strategy::distance::andoyer<S, CT> >
{
    static auto get(strategy::distance::andoyer<S, CT> const& s)
    {
        return strategies::length::geographic<strategy::andoyer, S, CT>(s.model());
    }
};
// TODO - for backwards compatibility, remove?
template <typename S, typename CT>
struct strategy_converter<strategy::distance::thomas<S, CT> >
{
    static auto get(strategy::distance::thomas<S, CT> const& s)
    {
        return strategies::length::geographic<strategy::thomas, S, CT>(s.model());
    }
};
// TODO - for backwards compatibility, remove?
template <typename S, typename CT>
struct strategy_converter<strategy::distance::vincenty<S, CT> >
{
    static auto get(strategy::distance::vincenty<S, CT> const& s)
    {
        return strategies::length::geographic<strategy::vincenty, S, CT>(s.model());
    }
};


} // namespace services

}} // namespace strategies::length

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_LENGTH_GEOGRAPHIC_HPP

/* geographic.hpp
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
*/
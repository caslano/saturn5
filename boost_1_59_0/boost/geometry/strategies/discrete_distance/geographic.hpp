// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_DISCRETE_DISTANCE_GEOGRAPHIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_DISCRETE_DISTANCE_GEOGRAPHIC_HPP


#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/discrete_distance/services.hpp>
#include <boost/geometry/strategies/distance/comparable.hpp>
#include <boost/geometry/strategies/distance/detail.hpp>

#include <boost/geometry/strategies/geographic/distance.hpp>
// TODO - for backwards compatibility, remove?
#include <boost/geometry/strategies/geographic/distance_andoyer.hpp>
#include <boost/geometry/strategies/geographic/distance_thomas.hpp>
#include <boost/geometry/strategies/geographic/distance_vincenty.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace discrete_distance
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

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, geographic_tag, geographic_tag>
{
    using type = strategies::discrete_distance::geographic<>;
};


template <typename FP, typename S, typename CT>
struct strategy_converter<strategy::distance::geographic<FP, S, CT> >
{
    static auto get(strategy::distance::geographic<FP, S, CT> const& s)
    {
        return strategies::discrete_distance::geographic<FP, S, CT>(s.model());
    }
};
// TODO - for backwards compatibility, remove?
template <typename S, typename CT>
struct strategy_converter<strategy::distance::andoyer<S, CT> >
{
    static auto get(strategy::distance::andoyer<S, CT> const& s)
    {
        return strategies::discrete_distance::geographic<strategy::andoyer, S, CT>(s.model());
    }
};
// TODO - for backwards compatibility, remove?
template <typename S, typename CT>
struct strategy_converter<strategy::distance::thomas<S, CT> >
{
    static auto get(strategy::distance::thomas<S, CT> const& s)
    {
        return strategies::discrete_distance::geographic<strategy::thomas, S, CT>(s.model());
    }
};
// TODO - for backwards compatibility, remove?
template <typename S, typename CT>
struct strategy_converter<strategy::distance::vincenty<S, CT> >
{
    static auto get(strategy::distance::vincenty<S, CT> const& s)
    {
        return strategies::discrete_distance::geographic<strategy::vincenty, S, CT>(s.model());
    }
};


} // namespace services

}} // namespace strategies::discrete_distance

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DISCRETE_DISTANCE_GEOGRAPHIC_HPP

/* geographic.hpp
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
*/
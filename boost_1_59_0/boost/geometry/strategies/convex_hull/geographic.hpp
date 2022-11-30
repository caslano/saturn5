// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CONVEX_HULL_GEOGRAPHIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONVEX_HULL_GEOGRAPHIC_HPP


#include <boost/geometry/strategies/convex_hull/services.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/geographic/side.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace convex_hull
{

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic : public strategies::detail::geographic_base<Spheroid>
{
    using base_t = strategies::detail::geographic_base<Spheroid>;

public:
    geographic() = default;

    explicit geographic(Spheroid const& spheroid)
        : base_t(spheroid)
    {}

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

    auto side() const
    {
        return strategy::side::geographic
            <
                FormulaPolicy,
                Spheroid,
                CalculationType
            >(base_t::m_spheroid);
    }
};

namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, geographic_tag>
{
    using type = strategies::convex_hull::geographic<>;
};

} // namespace services

}} // namespace strategies::convex_hull

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CONVEX_HULL_GEOGRAPHIC_HPP

/* geographic.hpp
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
*/
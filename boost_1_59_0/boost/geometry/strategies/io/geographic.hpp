// Boost.Geometry

// Copyright (c) 2019-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_IO_GEOGRAPHIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_IO_GEOGRAPHIC_HPP


#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/io/services.hpp>

#include <boost/geometry/strategies/geographic/point_order.hpp>
#include <boost/geometry/strategies/geographic/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace io
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

    auto point_order() const
    {
        return strategy::point_order::geographic
                <
                    FormulaPolicy, Spheroid, CalculationType
                >(base_t::m_spheroid);
    }

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

    template <typename Geometry1, typename Geometry2>
    auto relate(Geometry1 const&, Geometry2 const&,
                std::enable_if_t
                    <
                        util::is_pointlike<Geometry1>::value
                        && ( util::is_linear<Geometry2>::value
                        || util::is_polygonal<Geometry2>::value )
                    > * = nullptr) const
    {
        return strategy::within::geographic_winding
            <
                void, void,
                FormulaPolicy, Spheroid, CalculationType
            >(base_t::m_spheroid);
    }
};

namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, geographic_tag>
{
    typedef geographic<> type;
};

} // namespace services

}} // namespace strategies::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_IO_GEOGRAPHIC_HPP

/* geographic.hpp
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
*/
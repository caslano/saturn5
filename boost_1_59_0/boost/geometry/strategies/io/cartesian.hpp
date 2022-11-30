// Boost.Geometry

// Copyright (c) 2019-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_IO_CARTESIAN_HPP
#define BOOST_GEOMETRY_STRATEGIES_IO_CARTESIAN_HPP


#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/io/services.hpp>

#include <boost/geometry/strategies/cartesian/point_order.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace io
{

template <typename CalculationType = void>
class cartesian
    : public strategies::detail::cartesian_base
{
public:
    static auto point_order()
    {
        return strategy::point_order::cartesian<CalculationType>();
    }

    template <typename Geometry1, typename Geometry2>
    static auto relate(Geometry1 const&, Geometry2 const&,
                       std::enable_if_t
                            <
                                util::is_pointlike<Geometry1>::value
                             && util::is_pointlike<Geometry2>::value
                            > * = nullptr)
    {
        return strategy::within::cartesian_point_point();
    }

    template <typename Geometry1, typename Geometry2>
    static auto relate(Geometry1 const&, Geometry2 const&,
                       std::enable_if_t
                            <
                                util::is_pointlike<Geometry1>::value
                             && ( util::is_linear<Geometry2>::value
                               || util::is_polygonal<Geometry2>::value )
                            > * = nullptr)
    {
        return strategy::within::cartesian_winding<void, void, CalculationType>();
    }
};

namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, cartesian_tag>
{
    typedef cartesian<> type;
};

} // namespace services

}} // namespace strategies::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_IO_CARTESIAN_HPP

/* cartesian.hpp
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
*/
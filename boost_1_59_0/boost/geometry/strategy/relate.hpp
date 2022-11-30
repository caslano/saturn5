// Boost.Geometry

// Copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_RELATE_HPP
#define BOOST_GEOMETRY_STRATEGY_RELATE_HPP


#include <type_traits>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/topological_dimension.hpp>

#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/intersection.hpp>
#include <boost/geometry/strategies/within.hpp>


namespace boost { namespace geometry
{

namespace strategy
{

namespace point_in_geometry
{

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template
<
    typename Point,
    typename Geometry,
    typename Tag1 = typename tag<Point>::type,
    typename Tag2 = typename tag<Geometry>::type
>
struct default_strategy
    : strategy::within::services::default_strategy
        <
            Point,
            Geometry
        >
{
    typedef typename default_strategy::type within_strategy_type;

    typedef typename strategy::covered_by::services::default_strategy
        <
            Point,
            Geometry
        >::type covered_by_strategy_type;

    static const bool same_strategies = std::is_same<within_strategy_type, covered_by_strategy_type>::value;
    BOOST_GEOMETRY_STATIC_ASSERT(same_strategies,
        "Default within and covered_by strategies not compatible.",
        within_strategy_type, covered_by_strategy_type);
};

template<typename Point, typename Geometry>
struct default_strategy<Point, Geometry, point_tag, point_tag>
    : strategy::within::services::default_strategy<Point, Geometry>
{};

template<typename Point, typename Geometry>
struct default_strategy<Point, Geometry, point_tag, multi_point_tag>
    : strategy::within::services::default_strategy<Point, Geometry>
{};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


} // namespace point_in_geometry
    
namespace relate
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Geometry>
struct default_intersection_strategy
    : strategy::intersection::services::default_strategy
        <
            typename cs_tag<Geometry>::type
        >
{};

template <typename PointLike, typename Geometry>
struct default_point_in_geometry_strategy
    : point_in_geometry::services::default_strategy
        <
            typename point_type<PointLike>::type,
            Geometry
        >
{};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template
<
    typename Geometry1,
    typename Geometry2,
    int TopDim1 = geometry::topological_dimension<Geometry1>::value,
    int TopDim2 = geometry::topological_dimension<Geometry2>::value
>
struct default_strategy
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for these types.",
        Geometry1, Geometry2);
};

template <typename PointLike1, typename PointLike2>
struct default_strategy<PointLike1, PointLike2, 0, 0>
    : detail::default_point_in_geometry_strategy<PointLike1, PointLike2>
{};

template <typename PointLike, typename Geometry, int TopDim2>
struct default_strategy<PointLike, Geometry, 0, TopDim2>
    : detail::default_point_in_geometry_strategy<PointLike, Geometry>
{};

template <typename Geometry, typename PointLike, int TopDim1>
struct default_strategy<Geometry, PointLike, TopDim1, 0>
    : detail::default_point_in_geometry_strategy<PointLike, Geometry>
{};

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, 1, 1>
    : detail::default_intersection_strategy<Geometry1>
{};

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, 1, 2>
    : detail::default_intersection_strategy<Geometry1>
{};

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, 2, 1>
    : detail::default_intersection_strategy<Geometry1>
{};

template <typename Geometry1, typename Geometry2>
struct default_strategy<Geometry1, Geometry2, 2, 2>
    : detail::default_intersection_strategy<Geometry1>
{};

} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

} // namespace relate

} // namespace strategy


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_RELATE_HPP

/* relate.hpp
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
*/
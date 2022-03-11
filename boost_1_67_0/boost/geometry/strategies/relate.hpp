// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_RELATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_RELATE_HPP


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
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

    static const bool same_strategies = boost::is_same<within_strategy_type, covered_by_strategy_type>::value;
    BOOST_MPL_ASSERT_MSG((same_strategies),
                         DEFAULT_WITHIN_AND_COVERED_BY_STRATEGIES_NOT_COMPATIBLE,
                         (within_strategy_type, covered_by_strategy_type));
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
    BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THESE_TYPES
        , (types<Geometry1, Geometry2>)
    );
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


#endif // BOOST_GEOMETRY_STRATEGIES_RELATE_HPP

/* relate.hpp
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
*/
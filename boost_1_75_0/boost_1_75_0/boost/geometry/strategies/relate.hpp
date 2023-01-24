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
Zg/pnM/vUmAb+L8v4IUnKXGqLXM5yS/SoHnVXtJU1D/WO+b6MDvGjpvaclfbkjCm7yztluRKnOWsWKbclKbOMQymjj0UApNksuHRNnXvub+Pb2uuyNm0WtYENI7dobOWkbZ+rmosSknZbRX9XXKaYh+LXlC1rVraUMLTXFdU0uThUUv/M9jDRqXSyqLQSlLH0sJVkmZprTf3lHCycM45cUhpH7enCMbZaae9tWXMWHK2nljfucSRFd5K9+71t2rMZjTJInnNniB1jOZY5vRSrzhSu3OaYRCamvHC6y4/cb5HkaWlViuD3YEiQs8NYyaNzMahRIDpWX2YdK2jWSqruC6bI23SB4/ZsIX44NQU8iV9OE8C6Vmmqevhuk+nB/AhFmy0Lryuzfl7DodEmMBwc20Wlb+Leb/faKqNsMCa1ltQruPrrzJ9nrPfG9tFjnOkrsIVbW16HJYkWeVHxA1lXGed6StJcjgM1Ia2iaUVpzWK+ad911/vfe8pYrPkGOsZi8JObMjB0Qe8++Lrkgszhdeimywad7m/GyYUZzkD1j8OcT453qB0O4A1hEp4ne8KRLZvM71nHX8OM8QcxO/rFSd5+lOMcZ19Fdhr6/Qe3d+4RfNYTK92PMNety0m5xrhZly9hmynF9Ff6/HiCnGvnvb8tUftsyqT8rE4f2VlKUIrTInK++kbvWd4zCct13FN1YsSJYW26+ONhxXd
*/
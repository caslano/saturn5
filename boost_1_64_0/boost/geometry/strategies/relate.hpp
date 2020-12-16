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
P9ef7+/ry9Gg9OVz+Xy+75e//NWvfv3rQIfkPeAnJM23ync2X80z7C14VzPOEvAO7gME/KUYG4p/JcaFYkFws6TTknRem2M6D5DlvyHLfxPl7fpP4JviQ4+/5qcBsUv4ugI8xR/6CTwyn0Am0VT86v7SfF8BTPOP8gOB4Ov/P3TQ29aiRb/U0bU8TvG7/j7MHuUogZHyzGfiMOjI0HHxxFul3tbHvexC5WKrsYe60mfXokV/Nf1SjcWhX3rHcP3PA9CHT/3LQFc7Y88jHvCEADLIsvyG+w8Eb7jrgAmDnr6ziB8wEGy7G8OCNfyed7ew8ocMvt9zG+RvR8xhTT8YuhE2wkbYCBvh3x7o6Gdu79bKN5/36B9PfPTnH9v73qe9/685sbZ7fV14e5Jc+YYuxuKGiIatPOTBQ/y6jaFyRK9qUnCyGAh8eqx8sFHmKzqPwIfDzmAjbISNsBE2wr8q5O6YC+54UsZ7Kb5LLrjLgkw/24h35YJdKl/Ed88Fd7+m4wQe5oMwt0Pj6fJ3ywV3o/TggXywKzcZ1O5Kv70CJ4SkcVLHTGs1sY2fTW+wLxh89rbGbZ+Kat00eNUx46X74qSCO7Ef/mw/HPlhLggN/ME9yEffqN/JRL/ZuIiBq2jf0OOn4RhHEd8uF9xO4d1MX+7qcQyI9z1KHn4m02k5UX16Q/H1H4jNMVX5Kq3gql/3uuV1PmJd3o5VuTSemiee8Rg8LObNvTH2vEdWY6xg9wDsq4Ck5ukNSUf1t5It3V6Xb5uPdPvcNOh2K79X8boHvP4GnKq8x+dE3lUcydpt+m5gtxexK9N+Hm7IOXLDmY9aJgeP5IM9Vt+qvJcj76n9Zt4g8j6geNqZC3ae9MQ7csEOX/5dc8FdT+rx0bEe5/vkgzvmHoA6ToAXV4YGD+aDu+fuhTI/tfUAt0nrUbsM2v0z1T83ybvuP9UfMeq4Ar+87lPmdW9mbI/dsxPeBvfng7uk5Rz8qvp2AvYKQFR7tf6w9ds12Za9qs/uxLz61zbmLa0LdOzoTrc85FPydCO1Flp6XozxDt0X7toJXm15zV6/3PUHa+zd9FoL2RD12LEujz66JtPpsdL16L5mfD2/lO7y9aeQwYfaOt5dS+w14mQPa5U5Lr2Mk41n85nOv6HWIDWHXgqZmYEO6LHuaxnrRvY6y+XT63WWPZVO63VJtlmN3c/UeqtkaodedyGr13Ssx5b5yOjrhcy+tmV8b8qu6LXv1Zj1Yo+Y8L1dbK+9qv07dT74S9u1Wesz9KrQPXfjfkrPFUXvmqTj2mMMV+O215UTxLqctv0SnXKvXHCvG2pO7ZD87LL7XbfHHT+kXZvTtQsQ63yuf6+emzz3tT2fEWv8jH2BI0eroAM57WEe+uI0nh6/1Djq8j3Yi3bM7VyNDhP92ct86HVN6qbroB+yY5u+u75y7Pabxke7Fd4q9htIZ9STqRe72NMKT+lFLecZ/fJsJ/bvf9z9gE1HlcvUm8oeOcL2SM6zv9ybSdO/NmTtJ/cquKbjj3uRLaTl2Kpyep+q65FrzE3ImjkmaXq+McMa6MZaZ8ImdtOoP2sMtax12ctcc8fejjPo6HrSa3e2fQe+1TiodLdx0/KRLcMcuzLP7czY6/UiJ7YOstvp0rHt0LS9m4yXvXbrdKo9ei+R6m89FzU824ZBfhc50OOm9jzK7r5Tmp5/ze1lLTbh11RayXkP/Y5Y47HtoPcV2iZ0fRWgn5rfOu3aCoMP6A8GybYSnjKhz14bIEg6q4i9a7bjQ3T5ge/Q2Sfbvqa9Ck/n++XZZ7tBn+mYy13TsdZn9vxx5xnb1l3mp7OmOfPd1ou92MjAc/fGvAYdYx8L1iA=
*/
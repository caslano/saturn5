// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DISJOINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DISJOINT_HPP


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/topological_dimension.hpp>

#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/relate.hpp>


namespace boost { namespace geometry { namespace strategy { namespace disjoint
{

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename geometry::tag<Geometry1>::type,
    typename Tag2 = typename geometry::tag<Geometry2>::type,
    int TopDim1 = geometry::topological_dimension<Geometry1>::value,
    int TopDim2 = geometry::topological_dimension<Geometry2>::value,
    typename CsTag1 = typename cs_tag<Geometry1>::type,
    typename CsTag2 = typename cs_tag<Geometry2>::type
>
struct default_strategy
    : relate::services::default_strategy
        <
            Geometry1, Geometry2
        >
{};

template <typename Point, typename Box>
struct default_strategy<Point, Box, point_tag, box_tag, 0, 2>
    : strategy::covered_by::services::default_strategy<Point, Box>
{};

template <typename Box, typename Point>
struct default_strategy<Box, Point, box_tag, point_tag, 2, 0>
    : strategy::covered_by::services::default_strategy<Point, Box>
{};

template <typename MultiPoint, typename Box>
struct default_strategy<MultiPoint, Box, multi_point_tag, box_tag, 0, 2>
    : strategy::covered_by::services::default_strategy
        <
            typename point_type<MultiPoint>::type,
            Box
        >
{};

template <typename Box, typename MultiPoint>
struct default_strategy<Box, MultiPoint, box_tag, multi_point_tag, 2, 0>
    : strategy::covered_by::services::default_strategy
        <
            typename point_type<MultiPoint>::type,
            Box
        >
{};

} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}}}} // namespace boost::geometry::strategy::disjoint


#endif // BOOST_GEOMETRY_STRATEGIES_DISJOINT_HPP

/* disjoint.hpp
oGBNG30JJjNRolU5VvwsvfMgEBaNAeLNySa6Xo0bjMDN1FlNi2D8rQDFCmfYpDCSZbOYU0CLqVmwlehhws1qJs2K6p6COF2dJHJ2S1NSZtzhzW8gdOga5umor6IQj1ijNo7PY1jG7M1/nyKvn5F0mOD4IVWXjvUuxCxq63RXk/HWUywQN/P9x+D4rj/SyJJr7Es0P2nd2xrRFZtu2owB8c0NP0WilBz8HYSsobMftVqa808xhEoGGlZuIQQsuBZSA1oS8pec8mB80copEmQ8CtPDf4hNHgGHKn4eFlSKPmzJPCHs7bF/wONqic/mGtFIINLkZnLObBjjory25MTGtIbCQDCWdktSXT4FDQDZzt6cykB/RDztngozF1JMF3yPo+m9iA66+ruOdDuV+gHDkeZpIo9JzSOoszgEQh2zE1t1kKousQpX+AwNGNorofIoc0NO72gYr4V8qN8ZCsReP9tl7tPXFUUr29+u/Z52p8DOG2UsmNLgIhfxLs/Lg1mp1S0kMUfKql4qQ7J2Y5JmORV96dn8eGNsPHyR/7GxesBfhCIE1DlyoyWVxQ==
*/
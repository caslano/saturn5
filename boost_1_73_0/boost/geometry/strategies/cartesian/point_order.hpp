// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/point_order.hpp>
#include <boost/geometry/strategies/cartesian/area.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

template <typename CalculationType = void>
struct cartesian
    : strategy::area::cartesian<CalculationType>
{
    typedef area_tag version_tag;
};

namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef cartesian<> type;
};

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP

/* point_order.hpp
o/DhPnd6TfrOu10K3vkik3OBxff1ewmYngMS5eXifV/hWLpib67WPuoMsY9at8FyPPaUig/vJ3Ua9lHSB30S3CWj8y+G6ZltaQzr4HNKK6XHf5FdO2NYp6c9l+yh16NeoIiNoeUD9bI2Yl8U25u9kfu+40r1uV3DZ9b4zIRxcWQNtuS3vCu+wwaX9oewqb5UbMJaAcPrV2sUZr7Pwvf+yGagNmKbluB5iwGRPfOWJZXKJL49
*/
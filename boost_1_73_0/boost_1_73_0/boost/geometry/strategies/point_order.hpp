// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

struct area_tag {};
struct azimuth_tag {};

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP

/* point_order.hpp
D9y0ft6RGxYeee6EqH7zCRTAaoQNe+m8T94f5/3VHr7e0l107vfnfJ98
*/
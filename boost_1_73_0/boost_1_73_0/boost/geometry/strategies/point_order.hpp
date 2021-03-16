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
iKvnONg6sMzu6hrYC2puTdVccAQS5lJtBSTNYwcJwSJpLkDJgCZnMj7c7OBk92tEc7hcldXuBFGzBVeAHanwuwE71EaTtA5qFQPhwW5BEp6mRMog9FMOLeb6G6G4VacGJJYopMuH1i2xUDQTk3OwrBLxyy6jSCZLbY5gv2qFKkK+kAoHZZFWk6C030K64mYEoMJxWM1OWHuFx1XtJm4+BU/sTj8RGbd4WvctFpOj+lwpFx9fgmtEUxScgCrf73Y=
*/
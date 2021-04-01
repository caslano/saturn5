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
KG7uWwVfomlqcWvAOx9YrNVzoi+Le8iC8gJBdvsVztiMx20J8S3UldgvjdsdGYI4j2UXCzc+ye115uM9Iu7UcL7dv9Ee7PbPBG/z+XUSkGEAeo5FV+CFSB1rjMNDScxQQezC0gMcBfcnFzC3whOjSVgQGQLirHE3fZeZEYH4sqDgYG/Lk6D6ki0M7fvCWYdZ5GqsL6QT0sytSph+zIdPXIBQ81xYIT35TddXRQcCPwapN/JbXVPxP0utDFFMPiwcWT/4AZ0rBYPQ10YdXyGkQCwxv+1PbIDaOFQB2ZgVOPjqg8zF5F1yvqK94WUTE3LHImaK6FSawSIb4qvYKSba3rAoJABMufpOxNrDppDDvmcJpF7b8e0JPFzxjtS72SI8LCpPb2aSSrR76SSnSEfGDHxVQrdS/CgnIbGiegN9+kxYtmo5wg876aM9wg3rjhxVip7RfXX2mby5bt6cezwQRuxeDcruTGjKXxMQ1egHSTKG47OyuVNejDyG8/2MtZzCP1Bl8G9DEWNSt6fuq1sDXPU4TNw5+GtLL76DbaXa/DPAhdXRIsZ+hCdEkA==
*/
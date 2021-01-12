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
42R6xm+Q79cb5O35Vllfdc2iq4P8p0t+fce3RmnMA+iQ1unKXtOBP6nbpd2vt0fvlwsBd7iHRb6I3kn3aeSpaNfyrogHFr+V3iNtvwI45UlwfsAz+d9PvBPFXShlPxj1Z2sF/1EfJp0c5AGNwrh+IPGWcpHt1EetTqOV6Q69Wubi4zXe/bXm2Otc070FtFF9sbhN/Cfb5meIDnWR75zPUZ/rZEyvA4zfiV+I3r1Jp+hg0Ty5
*/
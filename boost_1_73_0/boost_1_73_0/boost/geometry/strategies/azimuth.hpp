// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2017 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace azimuth { namespace services
{

/*!
\brief Traits class binding a default azimuth strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<CSTag>)
        );
};

}}} // namespace strategy::azimuth::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP

/* azimuth.hpp
pUfviFwPWsH/yKe/fhCA+ITli/CQ8OJwGCZ0P4j1J0RC66VCE+us037loG+S5gsy3mci0S0gk7bG+hJMVHsTxPvvPAwS9pjy6WB2V9aBi032fZUZsSSBlk22W0mZYmqf32AQIGEna8fSGHYxpiESeOwHtmnKacR5WUoWczKCraiPqG3AJcD2ah+AVt0aKTsfFAaPRbzQnUCXj+4ESAKcOqlY2E4N/7tNMCCoIuMQ6FkrhhLksVMk+PNuHBTdOCy68TfhhukbmG+bzcAg09MwJZs9NYlFLQBw1wh7cPU6Hmfxp8CgNjUgPTtmewcHpvEEkJFIcvYn2dJc1yAlqHNlcR3EnOQJhEAka9J+LvWj+Go33jSTZp/1J4PMNo9NHGUdk63nwTxG7aGWdGTfAgvWJ4wdG1CXGbg6l2TZuHnCNSNIZcck/oQ7L+MlSfrHtI8xJMdlUl5MRKXm9W7JVS4KsOYsGexsGe5Lkvly6MePmZXXX9d5/aXqDEP6KQWm1lcrFagsRIojsZRKzssZ4gxS07dqN1DzoItD7jpgClMOVkotu+Fbx0m0M0Utm5lb+Y5D4rWSe4VLB8jriWuaJrHvj0RFEFVhigoeomK7Q5ZcF0VAMcSaROSWkKCdcKIOXTkb2OBZ4Ec8nwpzKkPu
*/
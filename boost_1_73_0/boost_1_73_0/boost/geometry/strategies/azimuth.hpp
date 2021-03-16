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
knwCQjTgNF1UDlG8GH26aCYzThcZmvmxhgTwPizgd1C9iQiaY6to1qHw8Hf97LCKZvtF6ftjUy7KPobEtmvBzSaujrh64lYSdydx9xL3IHFbidtB3D7iDhD3OXGHifuOuJPE4byZ4FI0xT1I3MPEeWZAJfJH/hg+lepqa2NYObhz4g0vrWGLbyhGb+TmDHdJ+NWZ3sj3bR8tu0S6KUV5vprF53hdWy1db3hXspKuV+WBkq5dXZ1dvpq2j259zy8=
*/
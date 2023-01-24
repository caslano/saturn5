// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/azimuth.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace azimuth
{

template
<
    typename CalculationType = void
>
class cartesian
{};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<cartesian_tag, CalculationType>
{
    typedef strategy::azimuth::cartesian<CalculationType> type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}} // namespace strategy::azimuth


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP

/* azimuth.hpp
gRR37lKaOtt99SgOOo1SZNvvgDgmqhFbf0naVmugmpJhd5xoyJzUncUhz6Eq4pU9KU48FtiIqsdkrhnPdiESnCZdUVl1tDWKk0zjHEyZRMeejNQEOcg6SD2dFhgxS2DSZHtoix8+dM3+xXNb0dF65svxqyKch2MmMA1UA2uzLSRgk/t9B3lO5AZaBY+eT2YkUi5xL8UVhi0br0ZW/B3NXGda9HQHeRWVyOjlOMDJi/LtrAXawOhQhheYFlgmez8LnYZ+CoD7ox/KiiEbwPGBZ1GHeh9oc6XlNN2CXzB8IzW0/sD1E2lyYmazppinQNiaGU4GI5qyI9KB6VmFSn8xQPEldbO8EfWOzPxdYPgoIclq1Jn8UtkvAgj+AeiegBNLqoNkJ7N/WY8rgNDKwRMTxlb2uua68GA46QybHdeiZdruz9srj5v7nZtrnKhZZQiqT0SnOgR5D5QLUlxfPQQces35JYkwPeg9Sr28ffH3U5bOBSmpMry8tgoEboRX8VH+ae+QsT5SmCIvJHjkfQkyzc2aER0VRdC7zmBUxOdAKadayIyl1apkFxa/yJu3prXukrtirxA2EjUSHeU7zcSqMQBfp31ySp+zxJm4Nu61PKnz5sn4vCwy7OZTWYQ6+OZ2IZReJ0Y52/Qu96mF2VyIuey1qLsM9LPg7Gy8qP3Qe6J5TApxCdFrT4UB+sG0Agm9Aa5v6oWvL3xUzJnb
*/
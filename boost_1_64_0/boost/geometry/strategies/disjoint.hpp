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
vRVe53yvlFVEkgs0nWjN3ggT/eoczPcoSZnv7bwc871G7+F/0FIyM2Z9sBAlc44eWrXIOi8EhFdCrHtx6oELh+EdXm4BE83/5t0wonov3yVRoe68GiZuz3nJrcwrGl9ZfJFFA8WkHDZqcL+n2TQa7VF7onU8+lSxdjTTXXqj2BobrMoQV9dwujS08Se/+wWrncQcNwMH+EknVgnBFUrsFJPYN/+SIrGQJ+lqzt0VZo9XWk+57Mq6riVOlnGpDI8l99yGPEut+szOdIUdv0LFr3BrATGrxorchucS59+FSTu7YX2S8DuOsFZSWMsRtnZxCZ349gpzzFTJINmW9u+ukPt+g2Pl3daOS87BptZAshBOF15vRkbtxNSubT7pMBti74nv7sxt9Gk6VmiqPJN9eaPzv3Ws6yi/QYv7nLwgSdxnjS0FowXYpeU69KT3Id6xNAx17dS2jl2i0M6FB24t/NDGewYRcAgKFRbj47Bl/I+DP+7XHI+Thxm5N2SoOKXi8cHJIojjEEH6I5yEDHqoVkuTWU1kqJmMJlXS1XYyGy0RjSYV9OfKY5jWMmfgkeqkxqb0LXKTb11pUa8dmKwpXovP7C6hKA4FwWvtEwxe9h5E3uYiBSNGNOokd+4hYacX8dE/j1OXGxmXhlGizLhF60EG/0NdlGOU5VeZt/pTEZ4OcS+j1UR5a/LkSu3B/JNRUxiblLpY2J4aoaIWxQpSh/KhOzMFGEcfX+wMruDetUM6phyas61FrS4ehQrprOnFeuyO/jMelwvYA/IS/0uEkj6FKU0p/zkPH3by7pytXbLR3TsbWUtrSX6ys5EROCfZz8Euaa3U2kTMpLK83VPLFbLk3nfBJzm1nNC/JVbCPug/m6snXatCZtLVKk2x0iO/pVAt4rwfxmO5F3LR757sli7s3HKAG+99GZTEL4rca4IcJgnvSzP0QGsUgDepFERgTE7XOM735EFoRQu9qButWMhVlPVLaNznJoTjK5guD/dYNl7r3/2hT6QQVD7Ql7yh3Lz4Iirx6rcY1q9/O9Y63N/LTXrIXDQ6E1L2NpW7fORaN1JJwPORa86FnoZQf1LSwk9KQWY4Wj2GCVx3vi4uNgzlzJghsQ/VoMb6qpG2ojgUnS2yM8GMd3Pm52IQvp4O1vm0dNCXx0i/xYtiroU9lGMJPHiE3EhyS2kgb+wyXG55vV2m7V6ZUVFC7DOU2dMSKDxHflXNByyd1P0noVh9KEdyEZ32uPUkla1qr3a69CQmxIu/OZKAIeWjSnrWXAMpne9Nw1HjPSTjhVQbouNkvClMOYUIr1SvCKI5eeBBiO848qU6br8sJS3nZWPJ9HylcBN2DXPd41dT2CwBNQOhztwKHZEk3h2NMg4V240nMs2ZQrOOaMrXfPNQyjk696VInEjAQ3oFJhky7/J+F8HRIDhbCB5nCI5ngl59252SHSjycQGJtkRtK0rYwI6gZkr1OqiODi0+NEuYSRXizwVUp0nnED1+FIolLQskCw9corPQcrxs4lXQN6xvsvPUdrFPVfcQMcpXKtriktUb5WhkECywY/gVBI00UMOmU1S7yudP7bLz1DK3Wa41bQrjzGyhCd8UEP0bnUQ10vBYlqhKKoi+c7yqmli+1MP7J+jG9+5I1FWp7BTImu+1L2PNt+9/ZWL7H2ocuyC7LrR3jfW6MGQ0hA0Iuzc+NxAjW+2evTmj/f3FRK3q1ZKIQ635Qx7DJegBdY/iXE2PHVBxnlJ1e1dJJFGB+ipHSmA1inOnjqWUujzfm+UQmrmXiagUeiu+pEdLRjdZHUkkZXkmOhMBi4XPAFZzMj05GSkfVCgG7EQOeT99KLA5dfmcgWgAMDI=
*/
// Boost.Geometry Index
//
// R-tree strategies
//
// Copyright (c) 2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_INDEX_HPP
#define BOOST_GEOMETRY_STRATEGIES_INDEX_HPP


#include <boost/geometry/core/cs.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>


namespace boost { namespace geometry { namespace strategy { namespace index
{

namespace services
{

template
<
    typename Geometry,
    typename CSTag = typename geometry::cs_tag<Geometry>::type
>
struct default_strategy
{
    /*BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THESE_TYPES
        , (types<Geometry>)
    );*/

    typedef geometry::default_strategy type;
};


// TEMP
// Utility to get index strategy from other strategy
// In the final version this utility will probably replaced with some other mechanism
// The issue is cross-dependencies between strategies
template <typename Strategy>
struct from_strategy
{
    /*BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THESE_TYPES
        , (types<Strategy>)
    );*/

    typedef geometry::default_strategy type;

    static inline type get(Strategy const&)
    {
        return type();
    }
};


} // namespace services


}}}} // namespace boost::geometry::strategy::index

#endif // BOOST_GEOMETRY_STRATEGIES_INDEX_HPP

/* index.hpp
wGM98Q2AmR0J24oYTa3/KE9lgbsT0qwbc5a/F0f6gtY3s123/rQIb4j7fgHy8xwuRPiLoj68oDnQ6NZEo7sJjcznNNJM9y5Jz+YtbXl/G/Ece6j/6t+FeU3MB2Te2M6INg6/IrKr65O615NdTszzQh8r8rz6I56Xrp+4HwNET/WRzOMpRvTcq34MZH5WtQe/x6e6Nxr+ztD86sfA0kqvKrq3Vd5pPj4Br2mZg72A8Trdp/QU
*/
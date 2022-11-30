// Boost.Geometry Index
//
// boxes union/intersection area/volume
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_INTERSECTION_CONTENT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_INTERSECTION_CONTENT_HPP

#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/overlay/intersection_box_box.hpp>

#include <boost/geometry/index/detail/algorithms/content.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/disjoint.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

// Util to distinguish between default and non-default index strategy
template <typename Box, typename Strategy>
inline bool disjoint_box_box(Box const& box1, Box const& box2, Strategy const& s)
{
    return geometry::detail::disjoint::disjoint_box_box(box1, box2, s);
}

template <typename Box>
inline bool disjoint_box_box(Box const& box1, Box const& box2, default_strategy const& )
{
    typedef typename strategy::disjoint::services::default_strategy<Box, Box>::type strategy_type;
    return geometry::detail::disjoint::disjoint_box_box(box1, box2, strategy_type());
}

/**
 * \brief Compute the area, volume, ... of the intersection of b1 and b2
 */
template <typename Box, typename Strategy>
inline typename default_content_result<Box>::type intersection_content(Box const& box1, Box const& box2, Strategy const& strategy)
{
    bool const intersects = ! index::detail::disjoint_box_box(box1, box2, strategy);

    // NOTE: the code below may be inconsistent with the disjoint_box_box()
    // however intersection_box_box checks if the boxes intersect on the fly so it should be ok
    // but this also means that disjoint_box_box() is probably not needed

    if ( intersects )
    {
        Box box_intersection;
        bool const ok = geometry::detail::intersection::intersection_box_box
                            <
                                0, geometry::dimension<Box>::value
                            >::apply(box1, box2, 0, box_intersection, 0);
        if ( ok )
        {
            return index::detail::content(box_intersection);
        }
    }
    return 0;
}

template <typename Box>
inline typename default_content_result<Box>::type intersection_content(Box const& box1, Box const& box2)
{
    return intersection_content(box1, box2, default_strategy());
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_INTERSECTION_CONTENT_HPP

/* intersection_content.hpp
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
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_TYPE_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_TYPE_HPP

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/policies/robustness/rescale_policy_tags.hpp>

#include <boost/config.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace geometry { namespace detail
{

// Temporary meta-function to access segment-ratio for a policy
template <typename Point, typename Policy>
struct segment_ratio_type
{
    // Type in segment ratio is either the coordinate type, or for
    // deprecated robust point types it is a long_long type
    typedef typename boost::mpl::if_c
    <
        boost::is_same
        <
            typename rescale_policy_type<Policy>::type,
            no_rescale_policy_tag
        >::value,
        typename geometry::coordinate_type<Point>::type,
        boost::long_long_type
    >::type coordinate_type;

    // Define segment ratio based on the coordinate type
    typedef geometry::segment_ratio<coordinate_type> type;
};


}}} // namespace boost::geometry::deatil


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_TYPE_HPP

/* segment_ratio_type.hpp
iQ5X21h6fM6/7ujVYGKJwCBhguc7+efSstdt7WdAyuxMzNuQmj+m7JVDldKH/5iPZ07qEpOED3NvyHiVQ7eSTi6bT79owkdtkTg3DPkxl/vOXdkLx3PXfy4jbOmE4kc/xqw+uk9+7M3LqMzHyBfE2mSZLCmb8J3aAoG32H3KX1FI84MgDR+WZfZeJL+IM40tJ2PYOFfT5AqHAXund7d3CBvWKBMWsD9JZ1cnNlrdCK3Ks3jSdwBnKcLRiR4UKinv46zj6Yc7TLbQh8WJU8yasl1ieltMJtinPIfFnfs66Lurc8AKRacxTsMMs7GrEcE30zzxPPHjSR1rErRLF7OCU4J2hRuazndJNE2C8232TZgZdpb9bie9L7dvpnCe7ROvcbw6Ryq9llgtupaPWqoHfZxY2pywhUTAyF+zqpmc2PU89szb7PtJJhoyLtSBHY9/UkONmQfbHZFTTQj4axE88vA6V+IM04kxv9AtqozyfNbQjDz3xTgbd4pFu3xoIddrIQWb0H7cFWTuNyuKlmnY17DFdX5kz0nE/IGVjb7QuxIY9pWQcFdFNzarluS8FkfHkbDJCHmqD1c3QtaRwH6ARSsabMTZtKc/cYlOf4uPZfI2nIFQ1WfU1Mu4i/dFoQ1pP9Vly+kv42/+kBA1F/xENjZHvRW9GMJbiR9muG+joAGQieXcIZvMo8nqWNbaOfLw8SSapyaWzEH0jdVI
*/
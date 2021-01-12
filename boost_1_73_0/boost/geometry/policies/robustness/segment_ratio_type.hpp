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
x8GHHX493Hyf/Ez4Nof/EW7jdzfty+N/tI6PF3xR2Afd/fet8E8K+6K7/349/OMOp33Y8WkD/GOWx+1jlo5NGv7ewHP+0T01wfw5k8f3s8z8Av5zgrqtSozvL4z1q/Ph9zl85nXi+97wex3+ZLj9vjf8ew6/G27Hz6/UiO+vT7aftsML6ndVzL+0Pl4f6oXvcvhRG8T+PPjDtnzi+Qn6KSHAv1oTHOXbHw5vFvZrd/407Ws1
*/
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
sIaPOfrwkFCpXHL+TnSmDuE7MS0cVqgoZeWcdWmMwnHqpdc2eQ/0hFgF9VSX+8cH4tDqgoEiwSnFgQReqLpdHM7O5LVpPjcTwmefRGg3lSUHZQh4zVwx3d4O+LRjkp+5M9UgQsTjxM0sD+42d/7YETSGSCF1v71DvyaNe1UKGtMsDgj4eflYPBP7TfEHEyHu3eHZ0avuYNA/a3R7/bed02a7yv/4gH5+ruVAzko0is5BlZHbSwn+Xa///ROiRMZB9bqSFJ9XMp3A1ZzKpGgts2tYyFPsw+enZ/2f9o6RxY5bOlVOxKj3unvcOzlxR+7rzs/i+aGmoh8rU6w+1OaoPKw807PT+TSh+kDOUjx1EOO+R7eyKWANdJS/5/A1KNjro8D0Rt1K1oQ1IynnjQbzN5etomTNhsuV6otNBA/YaBqoN1pvF/tkjVHMk3Y5H3IwTlf989NTR+w7ooFR181MGH9Ckcl97a2IB0GRiwzkZlftYjzr0FfAFj4GqOiwJw729/fXkeaatjqVfzAx6p9mIvMhnxz+wB9jmBKbnA+7R2f946E7Wm8wuuFam/FaGAXtUgguH5Q3sAA6G7rsEiq8oNqOAYmRzK0ZqzK1tUU56fJRxdyiYq9WQdrQQzX1jfYaOmscRRdJHChNnTN5
*/
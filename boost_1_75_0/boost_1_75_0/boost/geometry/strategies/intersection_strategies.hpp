// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016, 2017.
// Modifications copyright (c) 2016-2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_INTERSECTION_HPP


#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/policies/relate/intersection_points.hpp>
#include <boost/geometry/policies/relate/direction.hpp>
#include <boost/geometry/policies/relate/tupled.hpp>

#include <boost/geometry/strategies/intersection.hpp>
#include <boost/geometry/strategies/intersection_result.hpp>
#include <boost/geometry/strategies/side.hpp>

#include <boost/geometry/strategies/cartesian/intersection.hpp>
#include <boost/geometry/strategies/cartesian/side_by_triangle.hpp>
#include <boost/geometry/strategies/spherical/intersection.hpp>
#include <boost/geometry/strategies/spherical/ssf.hpp>

#include <boost/geometry/policies/robustness/segment_ratio_type.hpp>


namespace boost { namespace geometry
{


/*!
\brief "compound strategy", containing a segment-intersection-strategy
       and a side-strategy
 */
template
<
    typename Tag,
    typename Geometry1,
    typename Geometry2,
    typename IntersectionPoint,
    typename RobustPolicy,
    typename CalculationType = void
>
struct intersection_strategies
{
private :
    // for development BOOST_STATIC_ASSERT((! boost::is_same<RobustPolicy, void>::type::value));

    typedef typename geometry::point_type<Geometry1>::type point1_type;
    typedef typename geometry::point_type<Geometry2>::type point2_type;
    typedef typename model::referring_segment<point1_type const> segment1_type;
    typedef typename model::referring_segment<point2_type const> segment2_type;

    typedef segment_intersection_points
    <
        IntersectionPoint,
        typename detail::segment_ratio_type
        <
            IntersectionPoint, RobustPolicy
        >::type
    > ip_type;

public:
    typedef policies::relate::segments_tupled
        <
            policies::relate::segments_intersection_points
                <
                    ip_type
                > ,
            policies::relate::segments_direction
        > intersection_policy_type;

    typedef typename strategy::intersection::services::default_strategy
            <
                Tag,
                CalculationType
            >::type segment_intersection_strategy_type;

    typedef typename strategy::side::services::default_strategy
        <
            Tag,
            CalculationType
        >::type side_strategy_type;

    typedef RobustPolicy rescale_policy_type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_INTERSECTION_HPP

/* intersection_strategies.hpp
UJzfzB1R74Vbg9uxK3g4F83dosYs/xs76/dHbTYLTPDlNfmzH3bta10YrreRo66x+ZOgGbPK77v5hAf7MhoJ5kqtGMox0M8xediVKFFm/2JihZbO3X3NW9JpoTvz5xGO35+mdGHcvkY96HtbrkMI+X7tP+IS4X1DglRjqyCOja8lrMOb0dnGJXCr4bbP0ZaUD7NMawJ/e+SdkAqccqUP5xkK3Vi8HJci1Cdk7yICjef3wieNt/UAa/TPBQnF4SauwDJJYa980LMILTjAA1b5/b6a3QlZG3XdPHtxDn8GbHXrtRT49pBAcLFgw+oWpx/vBwTwG0sYkO+iD4K34T+Qyjq6O47OuYOvpvXW+HYmz+aZVkwURCAZjhZJrS0fgmIs0j6te78SPJyWjbVHY8x1RWb9+fxHzJQk3aHZdzDBrQDsS65L2oyL++0Dgf/Yx9Q7S4f6ZyaLJj0Xbzm1n2wGOU7DvNZZ9RMCcKF91sqplPg0zWyhKcag1IpQ4/wsswFnXXaxJ3wTOfx2Ct6KcKq1ryJrNGCX4o+k6Ig3/h5FrZviqBHrKBXrcj4C0PPiB/PPFEVV8985w0q9uI5fuKXLZQxVBA1bDiZKb/huDWAUL2Djvj8eMQqNiwXmbwkGs79vDPoeFQ+HDw8B4qZfCZK11V4F7lVCEtpuEm4SsI1IVt6kaT75Lvplnglu8oxBjUgO2Fof2kgAOdGGw5Cx
*/
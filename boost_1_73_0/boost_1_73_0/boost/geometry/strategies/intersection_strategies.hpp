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
1GOLlmKoSYo1wux/Um+mictqtSqoBrAgA5c08eqXo+T65PTolyNhjGBl8I97NmDqVcRsd05uwfEBC4lPj3lC08D1anpgWJyp0WXn/ehbfc6YAdy5dO6FthFSDS0Hl5QNvvB+na7VV7FtCc3LZ3KZ433yAi/IdwQvXn2PFzhNsWqBNA11wQMMwYevvseLnxKuuGKS2eAfvMFQkABomGFkOAE1LPXuXWCHEMPxFs4QPCz4AbwCWQ4otRh5Oxq9aoN2jQhk6sIiMmLBla0EBI9cZs/BGxLHA/FzTYOq9JljzBmwf5IZwy0NJK5T18QHI2q+4WoXgOgc9dC7oW4txmTeZm7ciaufvv6YAe9CKgDT8qNQx6ygRrwoTC/uAsPnHyXM1c2847khvQ/1EQiHSeL4kQs2oNY7iKUQ4034qC/4Z/4kvA/lEw5iCiz46Ep5Jm9LQBDCYHJ+rtAGpChfyCf0gbEE+i7+xQFj8O+j0Fj6GATt4IFbBXcmmBpB7qPjUAVjIlnwwJDJQELlUHceLlY188nzV1XBQ0dAP/30zcdTNITAg1xhBk41tgV6D+PcOSULMCdQk+c6D8IiVE8nmUsMGoJpHawenQmkDSI06qPe8Md+B3xP+6L3kfyZL6yth5PXpBKYS6tympCWdh0L
*/
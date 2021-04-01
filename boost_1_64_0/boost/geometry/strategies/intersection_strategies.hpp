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
rp9Nl+Jl+r8SCFxEPhUcAImsNZahEvKXoG8Mzara5jjvmlHA7K7o9CrW/u9NeVgQzGwGN0170Rw354D7KDdAiLxHlYd79Ot9k+B1W3Osv/Lp0ozCCR7eRHcIlqB6kjnPoYdlpvCgGhe0jjhN76JkI6KutDgPhrMgUMNlBL9PGPR15dK32LXHndS8wKrLmOsaVLXfLdV6ye+ROG6SHNtap0Dr+vTrTNOz2Wf6oXj/z73mBS7IqmQuK7lc8zGa1Pd2DkQ6PhSZ2DMQsxkwJGrBf0SXq/M3qroCk5cOuv34V7RK2dU5PMJRmpzHPsQbxyjzpe/WozgnJUZOJ78HCfQ0raflMQB9x7FLNdRRUIGReBPD5M8MGG4nbwYydZGrcO2CzpSbUO5eD4IhTdXuYg7J4HbTSsSs9Ui4NkgLQY0giAETXNmuC3pKvr9QB8leSvwrsJSmBlvOZgN7xvHufO1yLyciBLyxuiC0IyY2EDka8+ybUg9t6efu06Er2DWgpyimT0rtf1TxnepUcwYGhiBDaALWgpdcncv8DWQQ+SnAFeKuSnXQLvUIBR4AKg==
*/
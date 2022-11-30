// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015, 2017, 2019.
// Modifications copyright (c) 2015-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_IS_EQUAL_OR_SPIKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_IS_EQUAL_OR_SPIKE_HPP

#include <boost/geometry/algorithms/detail/direction_code.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Checks if a point ("last_point") causes a spike w.r.t.
// the specified two other points (segment_a, segment_b)
//
//  x-------x------x
//  a       lp     b
//
// Above, lp generates a spike w.r.t. segment(a,b)
// So specify last point first, then (a,b)
// The segment's orientation does matter: if lp is to the right of b
// no spike is reported
template
<
    typename Point1, typename Point2, typename Point3,
    typename SideStrategy
>
inline bool point_is_spike_or_equal(Point1 const& last_point, // prev | back
                                    Point2 const& segment_a,  // next | back - 2
                                    Point3 const& segment_b,  // curr | back - 1 | spike's vertex
                                    SideStrategy const& strategy)
{
    typedef typename SideStrategy::cs_tag cs_tag;

    int const side = strategy.apply(segment_a, segment_b, last_point);
    if (side == 0)
    {
        // Last point is collinear w.r.t previous segment.
        return direction_code<cs_tag>(segment_a, segment_b, last_point) < 1;
    }
    return false;
}

template
<
    typename Point1,
    typename Point2,
    typename Point3,
    typename SideStrategy,
    typename RobustPolicy
>
inline bool point_is_spike_or_equal(Point1 const& last_point,
            Point2 const& segment_a,
            Point3 const& segment_b,
            SideStrategy const& strategy,
            RobustPolicy const& robust_policy)
{
    if (point_is_spike_or_equal(last_point, segment_a, segment_b, strategy))
    {
        return true;
    }

    if (BOOST_GEOMETRY_CONDITION(! RobustPolicy::enabled))
    {
        return false;
    }

    // Try using specified robust policy
    typedef typename geometry::robust_point_type
    <
        Point1,
        RobustPolicy
    >::type robust_point_type;

    robust_point_type last_point_rob, segment_a_rob, segment_b_rob;
    geometry::recalculate(last_point_rob, last_point, robust_policy);
    geometry::recalculate(segment_a_rob, segment_a, robust_policy);
    geometry::recalculate(segment_b_rob, segment_b, robust_policy);

    return point_is_spike_or_equal
        (
            last_point_rob,
            segment_a_rob,
            segment_b_rob,
            strategy
        );
}

template
<
    typename Point1,
    typename Point2,
    typename Point3,
    typename SideStrategy,
    typename RobustPolicy
>
inline bool point_is_collinear(Point1 const& last_point,
            Point2 const& segment_a,
            Point3 const& segment_b,
            SideStrategy const& strategy,
            RobustPolicy const& robust_policy)
{
    int const side = strategy.apply(segment_a, segment_b, last_point);
    if (side == 0)
    {
        return true;
    }

    // This part (or whole method, because it is then trivial)
    // will be removed after rescaling
    if (BOOST_GEOMETRY_CONDITION(! RobustPolicy::enabled))
    {
        return false;
    }

    // Redo, using specified robust policy
    typedef typename geometry::robust_point_type
    <
        Point1,
        RobustPolicy
    >::type robust_point_type;

    robust_point_type last_point_rob, segment_a_rob, segment_b_rob;
    geometry::recalculate(last_point_rob, last_point, robust_policy);
    geometry::recalculate(segment_a_rob, segment_a, robust_policy);
    geometry::recalculate(segment_b_rob, segment_b, robust_policy);

    int const side_rob = strategy.apply(segment_a_rob, segment_b_rob, last_point_rob);
    return side_rob == 0;
}


//! Version with intuitive order (A, B, C). The original order was
//! unclear (C, A, B). It was used in a different way in has_spikes.
//! On longer term the C,A,B version can be deprecated
template
<
    typename Point1,
    typename Point2,
    typename Point3,
    typename SideStrategy
>
inline bool is_spike_or_equal(Point1 const& a,
            Point2 const& b,
            Point3 const& c,
            SideStrategy const& strategy)
{
    return point_is_spike_or_equal(c, a, b, strategy);
}


} // namespace detail
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_IS_EQUAL_OR_SPIKE_HPP

/* point_is_spike_or_equal.hpp
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
*/
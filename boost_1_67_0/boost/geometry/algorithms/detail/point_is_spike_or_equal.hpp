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
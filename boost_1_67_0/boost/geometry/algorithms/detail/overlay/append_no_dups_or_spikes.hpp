// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2017, 2018.
// Modifications copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPS_OR_SPIKES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPS_OR_SPIKES_HPP

#include <boost/range.hpp>
#include <boost/static_assert.hpp>

#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/detail/point_is_spike_or_equal.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>

#include <boost/geometry/core/closure.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

// TODO: move this / rename this
template <typename Point1, typename Point2, typename EqualsStrategy, typename RobustPolicy>
inline bool points_equal_or_close(Point1 const& point1,
        Point2 const& point2,
        EqualsStrategy const& strategy,
        RobustPolicy const& robust_policy)
{
    if (detail::equals::equals_point_point(point1, point2, strategy))
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

    robust_point_type point1_rob, point2_rob;
    geometry::recalculate(point1_rob, point1, robust_policy);
    geometry::recalculate(point2_rob, point2, robust_policy);

    // Only if this is the case the same strategy can be used.
    BOOST_STATIC_ASSERT((boost::is_same
                            <
                                typename geometry::cs_tag<Point1>::type,
                                typename geometry::cs_tag<robust_point_type>::type
                            >::value));

    return detail::equals::equals_point_point(point1_rob, point2_rob, strategy);
}


template <typename Range, typename Point, typename SideStrategy, typename RobustPolicy>
inline void append_no_dups_or_spikes(Range& range, Point const& point,
        SideStrategy const& strategy,
        RobustPolicy const& robust_policy)
{
#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
    std::cout << "  add: ("
        << geometry::get<0>(point) << ", " << geometry::get<1>(point) << ")"
        << std::endl;
#endif
    // The code below this condition checks all spikes/dups
    // for geometries >= 3 points.
    // So we have to check the first potential duplicate differently
    if ( boost::size(range) == 1
      && points_equal_or_close(*(boost::begin(range)), point,
                               strategy.get_equals_point_point_strategy(),
                               robust_policy) )
    {
        return;
    }

    traits::push_back<Range>::apply(range, point);

    // If a point is equal, or forming a spike, remove the pen-ultimate point
    // because this one caused the spike.
    // If so, the now-new-pen-ultimate point can again cause a spike
    // (possibly at a corner). So keep doing this.
    // Besides spikes it will also avoid adding duplicates.
    while(boost::size(range) >= 3
            && point_is_spike_or_equal(point,
                *(boost::end(range) - 3),
                *(boost::end(range) - 2),
                strategy,
                robust_policy))
    {
        // Use the Concept/traits, so resize and append again
        traits::resize<Range>::apply(range, boost::size(range) - 2);
        traits::push_back<Range>::apply(range, point);
    }
}

template <typename Range, typename Point, typename SideStrategy, typename RobustPolicy>
inline void append_no_collinear(Range& range, Point const& point,
        SideStrategy const& strategy,
        RobustPolicy const& robust_policy)
{
    // Stricter version, not allowing any point in a linear row
    // (spike, continuation or same point)

    // The code below this condition checks all spikes/dups
    // for geometries >= 3 points.
    // So we have to check the first potential duplicate differently
    if ( boost::size(range) == 1
      && points_equal_or_close(*(boost::begin(range)), point,
                               strategy.get_equals_point_point_strategy(),
                               robust_policy) )
    {
        return;
    }

    traits::push_back<Range>::apply(range, point);

    // If a point is equal, or forming a spike, remove the pen-ultimate point
    // because this one caused the spike.
    // If so, the now-new-pen-ultimate point can again cause a spike
    // (possibly at a corner). So keep doing this.
    // Besides spikes it will also avoid adding duplicates.
    while(boost::size(range) >= 3
            && point_is_collinear(point,
                *(boost::end(range) - 3),
                *(boost::end(range) - 2),
                strategy,
                robust_policy))
    {
        // Use the Concept/traits, so resize and append again
        traits::resize<Range>::apply(range, boost::size(range) - 2);
        traits::push_back<Range>::apply(range, point);
    }
}

template <typename Range, typename SideStrategy, typename RobustPolicy>
inline void clean_closing_dups_and_spikes(Range& range,
                SideStrategy const& strategy,
                RobustPolicy const& robust_policy)
{
    std::size_t const minsize
        = core_detail::closure::minimum_ring_size
            <
                geometry::closure<Range>::value
            >::value;

    if (boost::size(range) <= minsize)
    {
        return;
    }

    typedef typename boost::range_iterator<Range>::type iterator_type;
    static bool const closed = geometry::closure<Range>::value == geometry::closed;

// TODO: the following algorithm could be rewritten to first look for spikes
// and then erase some number of points from the beginning of the Range

    bool found = false;
    do
    {
        found = false;
        iterator_type first = boost::begin(range);
        iterator_type second = first + 1;
        iterator_type ultimate = boost::end(range) - 1;
        if (BOOST_GEOMETRY_CONDITION(closed))
        {
            ultimate--;
        }

        // Check if closing point is a spike (this is so if the second point is
        // considered as collinear w.r.t. the last segment)
        if (point_is_collinear(*second, *ultimate, *first, strategy, robust_policy))
        {
            range::erase(range, first);
            if (BOOST_GEOMETRY_CONDITION(closed))
            {
                // Remove closing last point
                range::resize(range, boost::size(range) - 1);
                // Add new closing point
                range::push_back(range, range::front(range));
            }
            found = true;
        }
    } while(found && boost::size(range) > minsize);
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPS_OR_SPIKES_HPP

/* append_no_dups_or_spikes.hpp
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
*/
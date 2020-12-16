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
MGSXdrB580ub15v4mZZ8/ip5ARs5Zyn/J575cLs4rkYgtpZPWpcPfaVt1fiZr9V5xAXtXjLmk9jG+WKi18mQjEvIHfqNEDcuZVvNtYfGuO4cnz+CvDrKT9iDDenYloXGg+7kFxe3Y48WG9eETOqQldn25vYphNed2Im2bNHgb+jfSbGKtfb+dG7LA8agu3wgRp6XmW1cogZeVzvV4yezd8XlTkW/saZTz/i30Oce1lmn6NMt7Fpz6xBz6A//7ntc8j95w+3mqnMf30N384nLM6p7r7YmIe6tYG7e3I9Mn5YL/cIOVjXv5Ah55PMT1NmnnrC3qSMbaAxjxHyp2fPx4u6+X1tTHB3wx577HrszSfwVYj/kG7dk4se68iu+VxA5nk5q0w5zO9148Ukfcphn3J9xH1k9xOacqyc3Zzu7fs7Gbiaz18LfyeWHzcc+/HhV4xJaQD7aPrY6uev7+tvYk3BtlO3Nb67cLUYL1Qypg7GXfFVrx+ZUDIw5X9NSXLfFnNXuqD50MUadge40edk8pAuv1zb3x/Itt7C9zej4d8ZIjFfzWbr3HpvEvrZnD7tj/4PsBr/b7xh/fr35wtac4peS2Zmh+r7pHr79JLvOHn8u39mk/t3yUa7duNbxjkzqC3fYRzWNXLqLC6Ny0HPxxvdj2Ipx1jfMSd99CrqMpmMPqo9/xbbN1v962hpeazynJmLP8b6f1BW+YH+7sT/iqTg2/ZbVfEEV/luNouxxtdGP1HLNqyTtvh/ZPHP66/aGs5+1i7MRjcVdZE+tgjvmmn/GdvJTbKw49+3nzJdSaim1zclw3SWj2jTZlblOfrefnollOw2Wx7QRv30rb6jh2AkxjfjnHN0b613vmEevruZH3NtspHkgrp522PvYoI1tyJP/qn+AfpemO33lNfLHx9iN2C4h39EXs/TVT+3+EgexH0c/93cY1C2P61t9z2+2hn4fDPn+Kn04rF/91FrEVGfya9teeYH5UaWt+uok+bRYalMhdWX6tIBvnTyKDk9ky8h5upjlx0ohtWb2mw3roa75Uhn2Z0sEH6JdYtyzQ9lo/uLttWx5IbEHOx8qpbbVVC7BvtYay+c9YO5YT4l9REymvhmqI26LlotbK9+9iR03hunVeJ4bSOZiiofHOf8I/0Ju6Q5rRzn+md/s+icxtra99oz3JVif22FN1nzONVQ9SG125DLyfkmuu5FtWMdmhPWDbamp/U3N/4HG5Cc2M28LbTGHm8axh/zEs5Xp2KPq38vNU20et5huP2n8FonnP2TP/T70F/Z5A5tP1yYVd4385plRau6D9Lu1uRmvHccDe0HIPy87XoFNPENe/dTVfhT3iI9KLdS3hvJFcWRcLTl6SXOMf/hirRyjHP36mu+vR7foZ3Xy38oe7xplDrIl89cbnwQ2qpB8oxSdIo/15noXuje2lb1Zc8VTg8Ub11tnECNe9zyZyxVLi4lvFG88vpZfNr/63CQGMkeWKqKUZ3PklcHEN9Xud/JDaqhBVn0Wv7SQf04pbP+TeZ3+XTaCTymz3FyxzpddLXH5N2LGBmRnTvWKFZ/Tpw4z+Jxa7PX74rLabNQX7Nhb4VhEvCRf6y9OKcqvzCS7G34Qw5Ldp+xpNvbuMzZ/wadsghz5ttZsVUE28Rr2ez85jOOzdouFcvI5BwJxozhPbtfYJJ1Chj2y6+e91owi5XwZzZ3U4ng2av7j9pbg80L0nG95N1o95zn53kT23fGmWcXb4TVm8f2d69lCceqe6mxJjJjpWvlVaevBGeSvU9i+ImIMY7O4rnjpLbGd+LxWOfL+hS0SLzd8VwxWU5zGfu4ey0fd7Ln95Mbue6SKHDaDWGuhPOg=
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_SEGMENT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_SEGMENT_HPP

#include <algorithm>
#include <iterator>

#include <boost/core/addressof.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/condition.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{



// compute segment-segment distance
template<typename Segment1, typename Segment2, typename Strategy>
class segment_to_segment
{
private:
    typedef typename strategy::distance::services::comparable_type
        <
            Strategy
        >::type comparable_strategy;

    typedef typename strategy::distance::services::return_type
        <
            comparable_strategy,
            typename point_type<Segment1>::type,
            typename point_type<Segment2>::type
        >::type comparable_return_type;

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Segment1>::type,
            typename point_type<Segment2>::type
        >::type return_type;

    static inline return_type
    apply(Segment1 const& segment1, Segment2 const& segment2,
          Strategy const& strategy)
    {
        if (geometry::intersects(segment1, segment2, strategy.get_relate_segment_segment_strategy()))
        {
            return 0;
        }

        typename point_type<Segment1>::type p[2];
        detail::assign_point_from_index<0>(segment1, p[0]);
        detail::assign_point_from_index<1>(segment1, p[1]);

        typename point_type<Segment2>::type q[2];
        detail::assign_point_from_index<0>(segment2, q[0]);
        detail::assign_point_from_index<1>(segment2, q[1]);

        comparable_strategy cstrategy =
            strategy::distance::services::get_comparable
                <
                    Strategy
                >::apply(strategy);

        comparable_return_type d[4];
        d[0] = cstrategy.apply(q[0], p[0], p[1]);
        d[1] = cstrategy.apply(q[1], p[0], p[1]);
        d[2] = cstrategy.apply(p[0], q[0], q[1]);
        d[3] = cstrategy.apply(p[1], q[0], q[1]);

        std::size_t imin = std::distance(boost::addressof(d[0]),
                                         std::min_element(d, d + 4));

        if (BOOST_GEOMETRY_CONDITION(is_comparable<Strategy>::value))
        {
            return d[imin];
        }

        switch (imin)
        {
        case 0:
            return strategy.apply(q[0], p[0], p[1]);
        case 1:
            return strategy.apply(q[1], p[0], p[1]);
        case 2:
            return strategy.apply(p[0], q[0], q[1]);
        default:
            return strategy.apply(p[1], q[0], q[1]);
        }
    }
};




}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{



// segment-segment
template <typename Segment1, typename Segment2, typename Strategy>
struct distance
    <
        Segment1, Segment2, Strategy, segment_tag, segment_tag,
        strategy_tag_distance_point_segment, false
    >
    : detail::distance::segment_to_segment<Segment1, Segment2, Strategy>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_SEGMENT_HPP

/* segment_to_segment.hpp
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
*/
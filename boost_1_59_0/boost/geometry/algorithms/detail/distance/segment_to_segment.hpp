// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_SEGMENT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_SEGMENT_HPP

#include <algorithm>
#include <iterator>

#include <boost/core/addressof.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/distance/strategy_utils.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/util/condition.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{



// compute segment-segment distance
template<typename Segment1, typename Segment2, typename Strategies>
class segment_to_segment
{
    typedef distance::strategy_t<Segment1, Segment2, Strategies> strategy_type;

public:
    typedef distance::return_t<Segment1, Segment2, Strategies> return_type;

    static inline return_type apply(Segment1 const& segment1, Segment2 const& segment2,
                                    Strategies const& strategies)
    {
        if (geometry::intersects(segment1, segment2, strategies))
        {
            return 0;
        }

        typename point_type<Segment1>::type p[2];
        detail::assign_point_from_index<0>(segment1, p[0]);
        detail::assign_point_from_index<1>(segment1, p[1]);

        typename point_type<Segment2>::type q[2];
        detail::assign_point_from_index<0>(segment2, q[0]);
        detail::assign_point_from_index<1>(segment2, q[1]);

        strategy_type const strategy = strategies.distance(segment1, segment2);

        auto const cstrategy = strategy::distance::services::get_comparable
                                <
                                    strategy_type
                                >::apply(strategy);

        distance::creturn_t<Segment1, Segment2, Strategies> d[4];
        d[0] = cstrategy.apply(q[0], p[0], p[1]);
        d[1] = cstrategy.apply(q[1], p[0], p[1]);
        d[2] = cstrategy.apply(p[0], q[0], q[1]);
        d[3] = cstrategy.apply(p[1], q[0], q[1]);

        std::size_t imin = std::distance(boost::addressof(d[0]),
                                         std::min_element(d, d + 4));

        if (BOOST_GEOMETRY_CONDITION(is_comparable<strategy_type>::value))
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
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
irrnkJOnfzYoXRbm4Xlif3SuEjp2qS+d9qlDgQ7yDLOjYbOH9qS2KPVDdPwfief7Nojo+DAlUuJry0meXTaUvNzWQs6+JfoNtT9KQUPzJOqTyhNV7hqVV4zcPx2WlG/1HkLtRTqTgE5UGT8qbzxyf2dYUqSfZyrIM7ekIH/bHcjfUIn8edOQP2kq0rgtST3ZlyTno6CfOqCfOirpmfB6gfIzCKUR3JtSVi4hJZPZmKRCBLuwZ1wqymzLRJkNQZSZF0CZSV5ErXa6HYd1f8SF8OgrQCc8CSL7IGToPqzpSU9u6Wb2gsXsz4yzfbsZqmH9A+YDiQb+BAMGKMFml54NG3GhkCWukmbLPmWiulTboi50rHbWuGLuRb7N3uX+jRlTvTm+Fm++2+8KO7NUnzdMY041rMS1HDVfichOIYrDqNGh+TRNQy5M0fI1SGVofodLc/bt6yEZ+jrxJYx0G+EI8uZ9G3mTQn3OJFTBs8PIGaZZEFkB4QEIibOp1ys03e6uhXtkIICenWn0cOo62VhPHkn2oPRU9+v4HfEBqVa+Cyv7sV/5Sl4rbUCNSlG/57m64f2Ebdy7kPhMZmPrnEGY2lYvEKQjGJ9CUVxLy9QPXoxvCF9TxkAkF0IcgsjMH+sp1m/BkARRem5uit2xDbuESRjnCrNxA/LCxOkd1IdFO1Cg52jXQ+RfILw4RK+r9pjJbL491zgn3cnO8f7J
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>
#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/algorithms/num_points.hpp>
#include <boost/geometry/algorithms/num_segments.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/distance/range_to_geometry_rtree.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename Linear1, typename Linear2, typename Strategy>
struct linear_to_linear
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Linear1>::type,
            typename point_type<Linear2>::type
        >::type return_type;

    static inline return_type apply(Linear1 const& linear1,
                                    Linear2 const& linear2,
                                    Strategy const& strategy,
                                    bool = false)
    {
        if (geometry::num_points(linear1) == 1)
        {
            return dispatch::distance
                <
                    typename point_type<Linear1>::type,
                    Linear2,
                    Strategy
                >::apply(*points_begin(linear1), linear2, strategy);
        }

        if (geometry::num_points(linear2) == 1)
        {
            return dispatch::distance
                <
                    typename point_type<Linear2>::type,
                    Linear1,
                    Strategy
                >::apply(*points_begin(linear2), linear1, strategy);
        }

        if (geometry::num_segments(linear2) < geometry::num_segments(linear1))
        {
            return point_or_segment_range_to_geometry_rtree
                <
                    geometry::segment_iterator<Linear2 const>,
                    Linear1,
                    Strategy
                >::apply(geometry::segments_begin(linear2),
                         geometry::segments_end(linear2),
                         linear1,
                         strategy);

        }

        return point_or_segment_range_to_geometry_rtree
            <
                geometry::segment_iterator<Linear1 const>,
                Linear2,
                Strategy
            >::apply(geometry::segments_begin(linear1),
                     geometry::segments_end(linear1),
                     linear2,
                     strategy);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Linear1, typename Linear2, typename Strategy>
struct distance
    <
        Linear1, Linear2, Strategy,
        linear_tag, linear_tag, 
        strategy_tag_distance_point_segment, false
    > : detail::distance::linear_to_linear
        <
            Linear1, Linear2, Strategy
        >
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP

/* linear_to_linear.hpp
Q7kcyH3Qis36xvtc90XKcRoSyR+wclxk5bhmlCNFx6/beO+tHmRPFs+QzZ4b2MDxOmi1N4p+wGlPgMgPINz9AcP1W3GPjutXDXeQKP3kg8RXVtrMXwmI0qvAye4gOzaDluPBD0zl2AeJlz6w4PA9/YGhyCeEx5Hsz6XZHzD/F3WaNyCS/GEQjf2Q5X93Iv+uD2n+R31otLYl/zNY/l9j+R/gOzUfmr6j1xMavLzrPjT1vx2Q+PcPWXkf+ZCW94CRoxLB3P/GJ8OEMFfA+wfOz4dm2lcgMeIjRlv4iNJO/ShB+2WbmfZ8UXxVGCPcrK3iH5noT4fErzj9Bkb/boP+NUveL5C8B+yD5f0hM+0DkPgfTvswo/2yQftOC+1rJO8Hbpp34bypn6VB4tbzjH7GeUp/zPkE/bcs4+Vd0uFSbdhuGzDv9TrtuyFyD4Sd51l/ez7R31adp/3td8ZXpli+4kmm/W2rgBcOXEfH9O+c7PWdv9DvDPge+ht/L/Vv1veu8vcGqbfCv5nqbQokfvE3Vm81f6P1NutviRLZ7eYSpUhQb7cNWm/bddp7IfIvEE7+jeUrfZFeb8//jdbbfxpfWWCpt0ms3o6wehus/T82tz8kbv2Yt//HrP0/TnxhhmUmmCJCOV7ClwaZb+p12ndD5B4IOz9m5chNlGPVx6z9ja+cxOavzLfTcnyEjfkmvW/7f2waIych8XdehrOs
*/
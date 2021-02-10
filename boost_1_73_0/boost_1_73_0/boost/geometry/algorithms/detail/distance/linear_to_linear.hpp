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
Cj1YCJwBRJYPvjZI5FkslMTS/HgJ7Vjp5aX7k+prEd8DZUi9OyL9UZ3cUm5zg/zWH58MLsbkt+5w2D0fX5LBR9I9v0Rhv/bPD2H/bVgsJOwxCBmHxUNiu4FjM0uv+f0+u7Xa32xv4kQWI3XcQpMzEQWteR0npuSFxaa2x6xG72J4ah72R90Pp0fmyXj8qUlevlwy3RtefhoPzO7F+KSZlQ/iLSooCk8HwVcTyllp0FJapGP3NBLzXfl/1YRlzxgX+RnEpkkfuMnt2f2P+Tll7Jzu//RzfkKE1ONTFmofrNQTQgcCkYqi+syzpnn+N8J2gepdrbb7WoaVQ7kgP5CEACHF4xi9ZSqebdx8RCJsVEH1ILQ9Ma2wyWWuHy7yEzBmsdtopnRSm0ZOzro9c3TSBQ807gxy50CowV/48ptJlqsRDImvK1NhmhNr+H8I6est6aEuc5dObNGQvzPLGRnq8qcRebBfgCoymVMwvXlnbEQN/miiEc+SbW0uW3mmo6ntaQMNfQGWAvaPzMGvzUo3xbJnPmSXKSTOTvVaWeqnVSQF6idM8g5r7EGocUGFPSH3vm0RBW1T+OacPTaUtRYXmNpyHgA6g3D7CzMFgXnTada+glgwmNidGvw6PPpwcdwdjY6G44YkIO/ekp9/
*/
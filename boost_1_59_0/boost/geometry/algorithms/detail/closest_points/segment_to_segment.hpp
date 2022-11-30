// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_SEGMENT_TO_SEGMENT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_SEGMENT_TO_SEGMENT_HPP

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
namespace detail { namespace closest_points
{



// compute segment-segment closest-points
class segment_to_segment
{
public:
    
    template <typename Segment1, typename Segment2, typename OutputSegment, typename Strategies>
    static inline void apply(Segment1 const& segment1, Segment2 const& segment2,
                             OutputSegment& shortest_seg,
                             Strategies const& strategies)
    {
        using intersection_return_type = segment_intersection_points
            <
                typename point_type<Segment1>::type
            >;

        using intersection_policy = policies::relate::segments_intersection_points
            <
                intersection_return_type
            >;

        detail::segment_as_subrange<Segment1> sub_range1(segment1);
        detail::segment_as_subrange<Segment2> sub_range2(segment2);
        auto is = strategies.relate().apply(sub_range1, sub_range2,
                                            intersection_policy());
        if (is.count > 0)
        {
            set_segment_from_points::apply(is.intersections[0], 
                                           is.intersections[0], 
                                           shortest_seg);
            return;
        }
        
        typename point_type<Segment1>::type p[2];
        detail::assign_point_from_index<0>(segment1, p[0]);
        detail::assign_point_from_index<1>(segment1, p[1]);

        typename point_type<Segment2>::type q[2];
        detail::assign_point_from_index<0>(segment2, q[0]);
        detail::assign_point_from_index<1>(segment2, q[1]);

        auto cp0 = strategies.closest_points(q[0], segment1).apply(q[0], p[0], p[1]);
        auto cp1 = strategies.closest_points(q[1], segment1).apply(q[1], p[0], p[1]);
        auto cp2 = strategies.closest_points(p[0], segment2).apply(p[0], q[0], q[1]);
        auto cp3 = strategies.closest_points(p[1], segment2).apply(p[1], q[0], q[1]);

        closest_points::creturn_t<Segment1, Segment2, Strategies> d[4];
        
        auto const cds = strategies::distance::detail::make_comparable(strategies)
            .distance(detail::dummy_point(), detail::dummy_point());
        
        d[0] = cds.apply(cp0, q[0]);
        d[1] = cds.apply(cp1, q[1]);
        d[2] = cds.apply(p[0], cp2);
        d[3] = cds.apply(p[1], cp3);

        std::size_t imin = std::distance(boost::addressof(d[0]), std::min_element(d, d + 4));    
        
        switch (imin)
        {
        case 0:
            set_segment_from_points::apply(cp0, q[0], shortest_seg);
            return;
        case 1:
            set_segment_from_points::apply(cp1, q[1], shortest_seg);
            return;
        case 2:
            set_segment_from_points::apply(p[0], cp2, shortest_seg);
            return;
        default:
            set_segment_from_points::apply(p[1], cp3, shortest_seg);
            return;
        }
    }
};


}} // namespace detail::closest_points
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// segment-segment
template <typename Segment1, typename Segment2>
struct closest_points
    <
        Segment1, Segment2, segment_tag, segment_tag, false
    > : detail::closest_points::segment_to_segment
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_SEGMENT_TO_SEGMENT_HPP

/* segment_to_segment.hpp
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
*/
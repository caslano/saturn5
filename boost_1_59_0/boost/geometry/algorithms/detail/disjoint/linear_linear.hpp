// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_LINEAR_HPP

#include <cstddef>
#include <deque>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/do_reverse.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_as_subrange.hpp>

#include <boost/geometry/policies/disjoint_interrupt_policy.hpp>
#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{

template <typename Segment1, typename Segment2>
struct disjoint_segment
{
    template <typename Strategy>
    static inline bool apply(Segment1 const& segment1, Segment2 const& segment2,
                             Strategy const& strategy)
    {
        typedef typename point_type<Segment1>::type point_type;

        typedef segment_intersection_points<point_type> intersection_return_type;

        typedef policies::relate::segments_intersection_points
            <
                intersection_return_type
            > intersection_policy;

        detail::segment_as_subrange<Segment1> sub_range1(segment1);
        detail::segment_as_subrange<Segment2> sub_range2(segment2);
        intersection_return_type is = strategy.relate().apply(sub_range1, sub_range2,
                                                              intersection_policy());

        return is.count == 0;
    }
};


struct assign_disjoint_policy
{
    // We want to include all points:
    static bool const include_no_turn = true;
    static bool const include_degenerate = true;
    static bool const include_opposite = true;
    static bool const include_start_turn = false;
};


template <typename Geometry1, typename Geometry2>
struct disjoint_linear
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        typedef typename geometry::point_type<Geometry1>::type point_type;
        typedef geometry::segment_ratio
            <
                typename coordinate_type<point_type>::type
            > ratio_type;
        typedef overlay::turn_info
            <
                point_type,
                ratio_type,
                typename detail::get_turns::turn_operation_type
                        <
                            Geometry1, Geometry2, ratio_type
                        >::type
            > turn_info_type;

        std::deque<turn_info_type> turns;

        // Specify two policies:
        // 1) Stop at any intersection
        // 2) In assignment, include also degenerate points (which are normally skipped)
        disjoint_interrupt_policy interrupt_policy;
        dispatch::get_turns
            <
                typename geometry::tag<Geometry1>::type,
                typename geometry::tag<Geometry2>::type,
                Geometry1,
                Geometry2,
                overlay::do_reverse<geometry::point_order<Geometry1>::value>::value, // should be false
                overlay::do_reverse<geometry::point_order<Geometry2>::value>::value, // should be false
                detail::get_turns::get_turn_info_type
                    <
                        Geometry1, Geometry2, assign_disjoint_policy
                    >
            >::apply(0, geometry1, 1, geometry2,
                     strategy, detail::no_rescale_policy(), turns, interrupt_policy);

        return !interrupt_policy.has_intersections;
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Linear1, typename Linear2>
struct disjoint<Linear1, Linear2, 2, linear_tag, linear_tag, false>
    : detail::disjoint::disjoint_linear<Linear1, Linear2>
{};


template <typename Segment1, typename Segment2>
struct disjoint<Segment1, Segment2, 2, segment_tag, segment_tag, false>
    : detail::disjoint::disjoint_segment<Segment1, Segment2>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_LINEAR_HPP

/* linear_linear.hpp
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
*/
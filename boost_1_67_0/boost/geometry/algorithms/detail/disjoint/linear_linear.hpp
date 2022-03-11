// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2017.
// Modifications copyright (c) 2013-2017, Oracle and/or its affiliates.

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

#include <boost/range.hpp>
#include <boost/geometry/util/range.hpp>

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
        intersection_return_type is = strategy.apply(sub_range1, sub_range2,
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
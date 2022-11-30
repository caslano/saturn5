// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_INTERSECTION_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_INTERSECTION_POINTS_HPP


#include <cstddef>
#include <type_traits>

#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/policies/robustness/rescale_policy_tags.hpp>

#include <boost/geometry/geometries/segment.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace get_intersection_points
{


template
<
    typename Point1,
    typename Point2,
    typename TurnInfo
>
struct get_turn_without_info
{
    template
    <
        typename UniqueSubRange1,
        typename UniqueSubRange2,
        typename Strategy,
        typename RobustPolicy,
        typename OutputIterator
    >
    static inline OutputIterator apply(UniqueSubRange1 const& range_p,
                UniqueSubRange2 const& range_q,
                TurnInfo const& ,
                Strategy const& strategy,
                RobustPolicy const& ,
                OutputIterator out)
    {
        // Make sure this is only called with no rescaling
        BOOST_STATIC_ASSERT((std::is_same
           <
               no_rescale_policy_tag,
               typename rescale_policy_type<RobustPolicy>::type
           >::value));

        typedef typename TurnInfo::point_type turn_point_type;

        typedef policies::relate::segments_intersection_points
            <
                segment_intersection_points<turn_point_type>
            > policy_type;

        typename policy_type::return_type const result
            = strategy.relate().apply(range_p, range_q, policy_type());

        for (std::size_t i = 0; i < result.count; i++)
        {
            TurnInfo tp;
            geometry::convert(result.intersections[i], tp.point);
            *out++ = tp;
        }

        return out;
    }
};

}} // namespace detail::get_intersection_points
#endif // DOXYGEN_NO_DETAIL




template
<
    typename Geometry1,
    typename Geometry2,
    typename RobustPolicy,
    typename Turns,
    typename Strategy
>
inline void get_intersection_points(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            RobustPolicy const& robust_policy,
            Turns& turns,
            Strategy const& strategy)
{
    concepts::check_concepts_and_equal_dimensions<Geometry1 const, Geometry2 const>();

    typedef detail::get_intersection_points::get_turn_without_info
                        <
                            typename point_type<Geometry1>::type,
                            typename point_type<Geometry2>::type,
                            typename boost::range_value<Turns>::type
                        > TurnPolicy;

    detail::get_turns::no_interrupt_policy interrupt_policy;

    std::conditional_t
        <
            reverse_dispatch<Geometry1, Geometry2>::type::value,
            dispatch::get_turns_reversed
            <
                typename tag<Geometry1>::type,
                typename tag<Geometry2>::type,
                Geometry1, Geometry2,
                false, false,
                TurnPolicy
            >,
            dispatch::get_turns
            <
                typename tag<Geometry1>::type,
                typename tag<Geometry2>::type,
                Geometry1, Geometry2,
                false, false,
                TurnPolicy
            >
        >::apply(0, geometry1,
                 1, geometry2,
                 strategy,
                 robust_policy,
                 turns, interrupt_policy);
}




}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_INTERSECTION_POINTS_HPP

/* get_intersection_points.hpp
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
*/
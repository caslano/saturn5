// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_INTERSECTION_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_INTERSECTION_POINTS_HPP


#include <cstddef>

#include <boost/mpl/if.hpp>
#include <boost/range.hpp>

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
        BOOST_STATIC_ASSERT((boost::is_same
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
            = strategy.apply(range_p, range_q, policy_type());

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

    boost::mpl::if_c
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
        >::type::apply(
            0, geometry1,
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
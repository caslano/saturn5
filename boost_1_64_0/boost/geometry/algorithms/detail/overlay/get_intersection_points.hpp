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
Qx4jfnbLKQr+H9AzQ+hj0/UqxvzChvQSUozMITO2UmaCAMm9PbbKG+P0mMxOTxfLyV/KQlFLhUqkKCtDDaV0fERKVY2VKyXemJWysXSxoKIbYuPG1S5D6mOA7On66Kb2Cn4kpjemPFz/pHKHVLD8tPWJhhv0RYcygR8tKqFtud70Li2IkJouAs8gf5daNi7Igg3zLLvXJsUjqyB2g91rKf8leW9wqaUhEpbSgzbIU8UcJNsIcrHb7d7GAlRMQYINAgRPb2/WelYoVPyAbH+hfupaqYw+cq2oplKXUP4CMZ7c68/j0EuHPUUETOM7aS3W+/3W4gNxY6/iCLDHurqD1au0o8M4jFWZKD0/EYnGRXn5RqAnRClufFLxDfp4Y5QcCezfHRpvnNCODBMjAa5A3SqbTPKvXDivv/5fGVzLyy/lIFnbUoIQyZSYRZTDw41prmOriwTLXq4gqkvihX8Kd/GLbOQW4YpDXZLAcZalQq76XVqFtyx4yg57USXjds5AKSanYuCuZ1SRx7kMf0yyYa2U5bgL9GjvojBJObzIIAi5VOSpqGTPW2QLhPNFvryCR7HiScLdyshLV4tqyT8uZmdxFeaTpwL7D8c8H5GJPKxntagwk5kKz4+CrQCGN/Yfrlv+1idQH5PXB/cS1q8TEhRZVn8Kcf7d/Y9AmuOK6pWF99oo54vLgrsOWPfuadG+Wy8r5aCIeCQc9/vS4F7AB2ffrZ6RnxXrTucnnnnMKa3HzxCdn14BfkK4d/w+fgLyTJK8pOx3YPnBc6ixdeYMBMOXmjsMrjH3Jrjtcy+2e04Ycxtqf1jN3XhZy0WhitdXaKaG9sfUfKmLedTFsE0s7d3iEAWnul17DPYehRDW3Zq5Vy0PUtyGkClvhSglyjWg36ZiRQkXBg18yL5fuVaviUcXMPsVM1YjjxxzSY5X+PS8czxFhK4fH1d8vZgBzyUoVqz3vOf3/6J8N5bXtx9Pvi/rdEuxfPvL5Psioc5quM69tl4PClX7E2FBvuaf7ODe4bPMaNhtMKAVom0bfsOWoa6fGWL9P8Bz5OBH9KV2R2Jq0MTvg+J6ipaxwtw2T5GoXHGka6lgyoVF++bvHkNCLOAm6PCbhFUX4CJD3g0ffvL2M0YusBWt6fLglx8+/v4u5dhBdJbOUq2lfVRJ3hMLDEmVRXfl5OQcqy49YVLLSrVW5m36AoRayKzt6ZVTbnBb0uYy+2lYH89jKE81JJWoPSOSNnjN3p4Rkxr6K/NLM7pYDQL0pBvcjfInRyzoBF2N5M6BWVHFUl4qFwmWrpVbntkQXsbZN6WzegL6sKpUyJaySaURm7ccMLuRlxGL1ZpUg/WRhdJ7PbxzhMRVqZ35Qe2EL2jJQ9q5Umpn4Wq9n0hfLTXrgWJugUxqgI5RqoWe0p+3KLyDXSS66pgKEYo/QePYqjAj+y7aaspvbIBn3v8pCUlDK3wXALdehRimNxYimB4TGmHpo68z0wPHp7fvLElf27e67njjam3WLRg2ME1SpVoaInt6/19Sv/32LpUbSiFTt1GUA5x/bS8aqC9zJ6N1ZmxFHqJDf29gYHvWOtNLsmUUq3e2aOXLpR/NW3b6MRWzA709d20ekb35I8SVu5nI6RJ206wX7ypRk9nx9U8LaKNlnyGsxlD47UV3S6Px2ha5YnjVQLmsmQkVFKn/SVV7+v7/e+FjRGE9Eshobho3am9YVb9uDg3A+qCaICrHqyaG1h4r8kQ6/exk5GkJ30bCVZSbujGpUk+TVkgCVs8yPZVvlRw8WWe8o4esKa5Lp602CnT07paDUIn2RHH97LoA7bScxt1E5FGnITcHctIexOnY3gWS8HMEtDTgO1Q=
*/
// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016.
// Modifications copyright (c) 2016 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_INTERSECTION_POINTS_HPP
#define BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_INTERSECTION_POINTS_HPP


#include <algorithm>
#include <string>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/strategies/side_info.hpp>

namespace boost { namespace geometry
{

namespace policies { namespace relate
{


/*!
\brief Policy calculating the intersection points themselves
 */
template
<
    typename ReturnType
>
struct segments_intersection_points
{
    typedef ReturnType return_type;

    template
    <
        typename Segment1,
        typename Segment2,
        typename SegmentIntersectionInfo
    >
    static inline return_type segments_crosses(side_info const&,
                    SegmentIntersectionInfo const& sinfo,
                    Segment1 const& s1, Segment2 const& s2)
    {
        return_type result;
        result.count = 1;
        sinfo.calculate(result.intersections[0], s1, s2);

        // Temporary - this should go later
        result.fractions[0].assign(sinfo);

        return result;
    }

    template <typename Segment1, typename Segment2, typename Ratio>
    static inline return_type segments_collinear(
        Segment1 const& a, Segment2 const& b, bool /*opposite*/,
        int a1_wrt_b, int a2_wrt_b, int b1_wrt_a, int b2_wrt_a,
        Ratio const& ra_from_wrt_b, Ratio const& ra_to_wrt_b,
        Ratio const& rb_from_wrt_a, Ratio const& rb_to_wrt_a)
    {
        return_type result;
        unsigned int index = 0, count_a = 0, count_b = 0;
        Ratio on_a[2];

        // The conditions "index < 2" are necessary for non-robust handling,
        // if index would be 2 this indicate an (currently uncatched) error

        // IMPORTANT: the order of conditions is different as in direction.hpp
        if (a1_wrt_b >= 1 && a1_wrt_b <= 3 // ra_from_wrt_b.on_segment()
            && index < 2)
        {
            //     a1--------->a2
            // b1----->b2
            //
            // ra1 (relative to b) is between 0/1:
            // -> First point of A is intersection point
            detail::assign_point_from_index<0>(a, result.intersections[index]);
            result.fractions[index].assign(Ratio::zero(), ra_from_wrt_b);
            on_a[index] = Ratio::zero();
            index++;
            count_a++;
        }
        if (b1_wrt_a == 2 //rb_from_wrt_a.in_segment()
            && index < 2)
        {
            // We take the first intersection point of B
            // a1--------->a2
            //         b1----->b2
            // But only if it is not located on A
            // a1--------->a2
            // b1----->b2      rb_from_wrt_a == 0/1 -> a already taken

            detail::assign_point_from_index<0>(b, result.intersections[index]);
            result.fractions[index].assign(rb_from_wrt_a, Ratio::zero());
            on_a[index] = rb_from_wrt_a;
            index++;
            count_b++;
        }

        if (a2_wrt_b >= 1 && a2_wrt_b <= 3 //ra_to_wrt_b.on_segment()
            && index < 2)
        {
            // Similarly, second IP (here a2)
            // a1--------->a2
            //         b1----->b2
            detail::assign_point_from_index<1>(a, result.intersections[index]);
            result.fractions[index].assign(Ratio::one(), ra_to_wrt_b);
            on_a[index] = Ratio::one();
            index++;
            count_a++;
        }
        if (b2_wrt_a == 2 // rb_to_wrt_a.in_segment()
            && index < 2)
        {
            detail::assign_point_from_index<1>(b, result.intersections[index]);
            result.fractions[index].assign(rb_to_wrt_a, Ratio::one());
            on_a[index] = rb_to_wrt_a;
            index++;
            count_b++;
        }

        // TEMPORARY
        // If both are from b, and b is reversed w.r.t. a, we swap IP's
        // to align them w.r.t. a
        // get_turn_info still relies on some order (in some collinear cases)
        if (index == 2 && on_a[1] < on_a[0])
        {
            std::swap(result.fractions[0], result.fractions[1]);
            std::swap(result.intersections[0], result.intersections[1]);
        }

        result.count = index;

        return result;
    }

    static inline return_type disjoint()
    {
        return return_type();
    }
    static inline return_type error(std::string const&)
    {
        return return_type();
    }

    // Both degenerate
    template <typename Segment>
    static inline return_type degenerate(Segment const& segment, bool)
    {
        return_type result;
        result.count = 1;
        set<0>(result.intersections[0], get<0, 0>(segment));
        set<1>(result.intersections[0], get<0, 1>(segment));
        return result;
    }

    // One degenerate
    template <typename Segment, typename Ratio>
    static inline return_type one_degenerate(Segment const& degenerate_segment,
            Ratio const& ratio, bool a_degenerate)
    {
        return_type result;
        result.count = 1;
        set<0>(result.intersections[0], get<0, 0>(degenerate_segment));
        set<1>(result.intersections[0], get<0, 1>(degenerate_segment));
        if (a_degenerate)
        {
            // IP lies on ratio w.r.t. segment b
            result.fractions[0].assign(Ratio::zero(), ratio);
        }
        else
        {
            result.fractions[0].assign(ratio, Ratio::zero());
        }
        return result;
    }
};


}} // namespace policies::relate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_INTERSECTION_POINTS_HPP

/* intersection_points.hpp
SxGHJ/CnAicsrGyjMjL+BDkVMTd5CUev02wy7NNA73CY38o7nNa4QuKEe7sQJisaanSU+8LVZSLqKJxiWmHLKu+XRplEvKUXsLrgknc5tUhhVphJH1bk2+RF8ZdqZ4l3z3e9UbD8fZ55J4mucq7S0T2fAgqZPiPnFo9RLmQ/K0MQXkJmFkli0OdY1IZaJ/aV2gnmR1s6OtJsrWB2f+0Y+VrqhOC8Ln0X2krsI//4qGOMvHT9giMGiLf/2aEkF+GUUT61OS3TgdhPaHwSq112UeFIVNyfmjJ15Y8KR+JQ7pyqAYdEYsOkgFF13YV2LB63aRebr5rIsj3UZ4nYKM1YyH0Ew5K8v1zjV0t+jNCVmcr6gvtmbLyZRH+h930aKM7Krsaoz+7C61mwKimqtsxZXz93vW8WbBF+yTUu76j9C2F3EdYGkMUBvBSnBYoVhy1etHiRIIXi7hR3d3cv7sUlOMWhuLu7u7tbIBBIsr6n3W8PM3Ocw5x+7/++N5Orm0vHTgJkOus/yLeq9MML8yNDFnLxg2tymS8PK7+HMkgamsAsu0dp+dYOKXmCtyxF9rM3Lhy5GrcuLK2t3fjXscMKvcPrO3XeiYPiSnItb4ooBOc+AZPDG4/lpkot91UbyAUXJgXQosgz5pS3rnYusaTO5oJFAe+hmDbU7rmqLkXUYDsM6XYrzwMTbKGZ9fp2BwNFg/iPMaCHngWFrz9I
*/
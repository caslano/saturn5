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
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
*/
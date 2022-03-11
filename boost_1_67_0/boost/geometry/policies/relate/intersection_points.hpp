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
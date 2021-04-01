// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_TUPLED_HPP
#define BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_TUPLED_HPP


#include <string>

#include <boost/tuple/tuple.hpp>
#include <boost/geometry/strategies/side_info.hpp>

namespace boost { namespace geometry
{

namespace policies { namespace relate
{


// "tupled" to return intersection results together.
// Now with two, with some meta-programming and derivations it can also be three (or more)
template <typename Policy1, typename Policy2>
struct segments_tupled
{
    typedef boost::tuple
        <
            typename Policy1::return_type,
            typename Policy2::return_type
        > return_type;

    template <typename Segment1, typename Segment2, typename SegmentIntersectionInfo>
    static inline return_type segments_crosses(side_info const& sides,
                    SegmentIntersectionInfo const& sinfo,
                    Segment1 const& s1, Segment2 const& s2)
    {
        return boost::make_tuple
            (
                Policy1::segments_crosses(sides, sinfo, s1, s2),
                Policy2::segments_crosses(sides, sinfo, s1, s2)
            );
    }

    template <typename Segment1, typename Segment2, typename Ratio>
    static inline return_type segments_collinear(
                    Segment1 const& segment1, Segment2 const& segment2,
                    bool opposite,
                    int pa1, int pa2, int pb1, int pb2,
                    Ratio const& ra1, Ratio const& ra2,
                    Ratio const& rb1, Ratio const& rb2)
    {
        return boost::make_tuple
            (
                Policy1::segments_collinear(segment1, segment2,
                                            opposite,
                                            pa1, pa2, pb1, pb2,
                                            ra1, ra2, rb1, rb2),
                Policy2::segments_collinear(segment1, segment2,
                                            opposite,
                                            pa1, pa2, pb1, pb2,
                                            ra1, ra2, rb1, rb2)
            );
    }

    template <typename Segment>
    static inline return_type degenerate(Segment const& segment,
                bool a_degenerate)
    {
        return boost::make_tuple
            (
                Policy1::degenerate(segment, a_degenerate),
                Policy2::degenerate(segment, a_degenerate)
            );
    }

    template <typename Segment, typename Ratio>
    static inline return_type one_degenerate(Segment const& segment,
            Ratio const& ratio,
            bool a_degenerate)
    {
        return boost::make_tuple
            (
                Policy1::one_degenerate(segment, ratio, a_degenerate),
                Policy2::one_degenerate(segment, ratio, a_degenerate)
            );
    }

    static inline return_type disjoint()
    {
        return boost::make_tuple
            (
                Policy1::disjoint(),
                Policy2::disjoint()
            );
    }

    static inline return_type error(std::string const& msg)
    {
        return boost::make_tuple
            (
                Policy1::error(msg),
                Policy2::error(msg)
            );
    }

};

}} // namespace policies::relate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_TUPLED_HPP

/* tupled.hpp
us5GV8wOzLBbVm5aAY6ENQLBXNtvP6ML9KDICIO90c1pnj6kEVwKkiZ9JUgkOfXSvlJ5xGq8CZH5BfJBul+Tc1druZiKSCGBAPb/rwYXoLcauVJhRz1C0vV1iZKFU1T67Jv5Jx7CH2Ewrktycso6k5ZT6miwQbLv6U50oXszb8V/0NzWp7l7mYEGJJpFj81ZJHLhWaahp18sZpeCBCGCYcn3Kfo0JeNKhBbLQ4RBbYZnOlKApo8lUc/7pXSUnLUhPIFDGuLQ7XFh4iyWbBLYU2iUqITmKTMyZlhGxtJkfvxUDAbScPUmc4yA5QLC8vCrtUncI+j7ecyGPfyKFFI8MErKXlgitw6GhTn/Eb7satBtmSqlAyr0ocmtlE9TZNUdy4wEZ/q4wl8ZLqN6KHbNAS4hxPDXOzMnK9puMXgvCMcxltf0x7SbDlwbD83M3fJM5i9sOqwwyHms7uwCOuZPut8bmvI5lzfrD5TMtiHOJ+rHSsxfX2WACw6jwRuyxKDNfX+X0VRWr1xub6uXnOB1Oz4ekCj1hjrtS/lrsdopitkNiU2l1WlbC8PGAg==
*/
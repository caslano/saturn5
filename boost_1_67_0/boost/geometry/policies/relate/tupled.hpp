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
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
*/
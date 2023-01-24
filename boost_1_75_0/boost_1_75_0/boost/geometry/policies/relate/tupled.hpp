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
2oLtY4K0ujuQ9C/LHHWFB7Ddpim71tmmW5mJtg/FGE7Anku31rzeRLEUQNy8Lu1jqS3TH7BpGFSf6kJX1OD7xLQdTIK9/xskdYRgIn9HQGYUksO/rkFqx+/7itFg/zFXpJc3o6j/hRUlnnRQ8Ls231fooqXO5yfVHso06bue+XKyLU1EzTWOezB3T2MPv4/DEtrqIRkZWC4YykM28i3xDcFMDqKPeeDpPraSAwXRn0/vPQd+GhDe0Pjp96RY3ewzv07je26jmH/WSBx00WZskqlETh4r1shQt2dpYKwcs4U+QI4eswR/auPh08dn/s5YS80J6op90BxFt2uzIhzjTcA26PUxJCQ1wml8+nZ8qWPJ1hV9PQB2JPC+Od5swCvmt7z9smkDbo+/KqUGBW764xrc2xGth602G8K285Qrv04rrjYSY+h8AcefykPQoahQ+spdizzYp2L2/WYjFgy/N+3OSWyHAqXZxfiDfmVroWzV2fL0vugG5XzqsX9C9+4n0WV46DOTO7r4UhTMck8Jf73rWhAXZlolk+wOtXWIqziJfJTNuZ0qYh7Vjb3XXVukaoqoMs7qvf5Ybjq+IpMaWqw7FtyQsZ2LZICr9HfQayd+nxHsQK4oDXMkYtLiuzvccNMiU64dW8HVmJRZNXZH9EmkecVxq9ebeMcQPmjqfd9aPbPssjP95yaW+TUscKryJ3+yLq919rmI9QBq
*/
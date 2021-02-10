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
ehEIaqa7eHjGvXLYDFfSMHTsFBMPViOy0tbuLL6lexVOxe6/7Ro/kzg21+3P9gEElhufAhuz+3+gr4fJorHMdVL7+vpMgzfFHVuw+njN1kJOMe8DE52F7P5gfgfk7Eig/s2AWGTNDlMVr1qCty0bJ7oQSkWKsUhWIQGNbah6KhY0dfNSDliRKM/srk9tCqkiLLA/dInBPpZoh+jIwmyW7j2aHSsHanRkzkEkFaprKjMZINDvVHkCXTyXUlH4da6Cc+nyyV01gHhnbuuxFofrxqlEiWjk0ndgg4w2572XN68umrkjJzgWH8nXi/B4alPi8bQczZZXrm11yUJXYz9LV3Po5Baxa7tIeavaK+9W4adUeWqO5SJoOpAdqGuBkGp22GMvjVXrip98DrGg37Nma5XiJrW4KWgHVngL1gIDmpUbmUyL7fFrDjdcu39aIF6moZeo8IovM8pudaYtLwOXVErDhxTAscNTdF52C2Jb3OEvPDYQga9wC+TP2GZPn4uAyBQ3IsNZgmU/sTol37FaZqIEyhF3ucBHfXIq/vmm18MNw7Nf8yJUkaOrF9eiIqsTVktUTWhXVBiPYGlxxzyvcxUSdaI2lCuPw4DHv01x3wx3zWywtqhl2L0QjSaejQcb2ms1ODXfyurkRkkY
*/
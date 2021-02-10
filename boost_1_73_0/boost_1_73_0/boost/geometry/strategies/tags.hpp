// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_TAGS_HPP
#define BOOST_GEOMETRY_STRATEGIES_TAGS_HPP


namespace boost { namespace geometry
{

namespace strategy
{
    /*!
        \brief Indicate compiler/library user that strategy is not implemented.
        \details Strategies are defined for point types or for point type
        combinations. If there is no implementation for that specific point type, or point type
        combination, the calculation cannot be done. To indicate this, this not_implemented
        class is used as a typedef stub.

    */
    struct not_implemented {};
}


struct strategy_tag_distance_point_point {};
struct strategy_tag_distance_point_segment {};
struct strategy_tag_distance_point_box {};
struct strategy_tag_distance_box_box {};
struct strategy_tag_distance_segment_box {};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_TAGS_HPP

/* tags.hpp
kOfsHKchzzhrIdle5Tqss+yU0EPwFm5JQD5kYckRhgVkauqdVY+lx1l6jvdXVx/wDpcXlxcxhkIrqjD3pFdkH2NcyzbypRRPT31Hn2OQh6j6e6pFqRycKfxWWAKvK5WTdiQhHCS53KoV/1EaviQUqiKkN7fLyfRbjG2p8jKQ7EwDV5qmkijFhmApJ7V54aiF9TAFw5lcKueZsPHK6D5rEzzZtQscQV5UzkBshKrEioWER+l97T4mSd7Yit0n0uQuyV/L75d+/aeSJZtYix1M7eENGkcxQmaMtZGqCDM3hIN1s6qUK+ODG5bSMjEWjqoqcDFOkXuxTZjv2xOHNNTsWPkwOaNdkNqWZv1PIvcxsBSN1SzEfeAkabjNMRo+UrZNbit/ldj3tG3w0a05+JUwms2gM5hjMu9gJZxyMe4ni/HN3QL3g9lsMF0scfMVg+kykH2fTIe89YrFLOiptuRY3EKt60qR3Gu+3UiiqKt0XjWS0Am7lznyTd0vO38/8GpNG34ZQ3RjlETaZtZEUmnlz7jehg9vGyXhduhJ4cX5pyh8a3LDFAdAXlL+6wgijo6etD0gWAxuoM2W+aMuaX5pkPSOft3ANf4GUEsDBAoAAAAIAC1nSlLWUVtljgkAAAQeAAAXAAkAY3VybC1t
*/
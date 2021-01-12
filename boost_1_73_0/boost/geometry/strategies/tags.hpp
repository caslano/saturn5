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
3Baak9tG8U/0Tuhwd6F8/6S6P0p318eQjf3PSf61knSqT5H8JqM+M+gRsB5El3wjd1Cbm6nNL1F9Wwi+mdr8FPvyJJ95nRX8APdJe3c/M1MGdurVy/RLmd1S5pbgJfu5P9PkJ8QLml/0j635FLbcywVmDvLkhUdWWKebUU8T6pkS3eQ7Id0GH/aTY0cXZyXPnQFbkVwWzNIEthWwlfASN3ng/qUDx4I93wWAdYJXs7hQgmPp
*/
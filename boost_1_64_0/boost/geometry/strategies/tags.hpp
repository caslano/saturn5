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
zbhK7/DeGu0TI7GImiHhhFnnI0v8TrYY/KvcVQ9tA9H9s6mAD0BeeJzLoJg/lo51GayJQ6xrU3HSCzVYkhfD3+P1ANOQ2Pz6MM16IGb5Th0PWz6hFwyHYsLiRfi86ZuiSU4Vxr/4MPuRLQ7t96GSydyFs/QQSW9LKIV26LVWHXtF5GmoL4r2upPPpkU1n7sMCogIdfjqqXj7gTV2/u/z/nkoP9d4Tw2xx6hY5q+UxB4pGMNefUTDtGiPNgvZUHsgbCKjKhSZMr1YcoiG02iPLozJ4nKRayl4qGN/5CSuWlOFc9Lef1rFLopeN5za9UoJ5wCF5YTP2b4ElyvLya6DbQy2VFtC6BfsC6kXcwOCMT5CSbCEt2xDJoOwH/azso+l7twtvPv7peqb/HvimVz7/nvlHUTBu6T99VWeELfEuNvYYu/hPNrNszG3qkrYA/aR0sjBvE67T++1IlPyj5z8tZDZecfvNamJ5io+EyIWiKcIvkCApIZDFJNHrmAjJ5m6QpoTR9hQJs67TCm5ZRWLzb9cMWvMuJ0S6FQdqTTgszqhdYhg1ZgVC2jTzw==
*/
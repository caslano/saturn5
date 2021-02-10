// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DEBUG_TURN_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DEBUG_TURN_INFO_HPP

#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/visit_info.hpp>


namespace boost { namespace geometry
{

inline char method_char(detail::overlay::method_type const& method)
{
    using namespace detail::overlay;
    switch(method)
    {
        case method_none : return '-';
        case method_disjoint : return 'd';
        case method_crosses : return 'i';
        case method_touch : return 't';
        case method_touch_interior : return 'm';
        case method_collinear : return 'c';
        case method_equal : return 'e';
        case method_error : return '!';
        default : return '?';
    }
}

inline char operation_char(detail::overlay::operation_type const& operation)
{
    using namespace detail::overlay;
    switch(operation)
    {
        case operation_none : return '-';
        case operation_union : return 'u';
        case operation_intersection : return 'i';
        case operation_blocked : return 'x';
        case operation_continue : return 'c';
        case operation_opposite : return 'o';
        default : return '?';
    }
}

inline char visited_char(detail::overlay::visit_info const& v)
{
    if (v.rejected()) return 'R';
    if (v.started()) return 's';
    if (v.visited()) return 'v';
    if (v.none()) return '-';
    if (v.finished()) return 'f';
    return '?';
}



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_DEBUG_TURN_INFO_HPP

/* debug_turn_info.hpp
PHkDQGz+zDNhh1OUDMUbj+UwykaxhdOnZmTFsTi9vxC7Wzs1K0bYyMLXeLQchpT4Q7obZ0EiUVHjzJbFp3JTUDKaxL8G1CwbiTWT+VYcwmjjJZLTLVBnMM1m8C/f6QlfLOoHhtrDgZFXZMWQ7G4mOA1DTK0J3dQJa+kNxrWjCb7hjNIb75cAijWlo6UoAc2xuSpihEY51mdxhNLbW9LhHAXIT8cPsEVWo1JiHrHxj12oKV05NlFOr85Ouq2j4TGgP5v4/ueoUTn2tooaVbGppEsvCij19+/7PnmuP65x6mUm5UN67h4fDwei9nul+KKHWL6Kd9bYGMA/xn7jJSUqGzs8q8lfyRxD7dznQOnL62PlssOvcz+5UXH3OQGCvi22atBEGfHBbu2WMoRlQbBnf2ULAlWyTL8M/Ko2A6z9R2BgGF/CzJW7SPI34bEyMEuCmCyH6SiMU7/eEBc+rhmlK1kFSWVXXw5Jc25LeE/BHT1dZYzB6u5FULp69cSxyjolPUOkFfYSSJVK0VaeARd7GnJpKjxclBZiVQGN/qgsx9jZLWtOVcQMxkLmA2aWax7saiPrko98RHdpyOjPQHvGGyMNzchBSTYDS1BXib+kQHJbc7A+R1XHxwc6eDB3/Kc6srMPlp5567O/vGGD
*/
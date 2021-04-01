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
PP8iLlu8asBcpdo3XEwxnw5WdD8kbFzbspU4huqd+OzIDsRrJE+XycWz0Kseu/O9DSiH8IFvzig02F+pfhyZ1giyHoPd5VH1138H2vEMJHlqP/XZuX35/x7DdI10IWSsxVGtjho+ED/vzt8QMibmSWnlW2oER/nxNODJklLmY56ukyG+efSZShN6Q9YS/3K17RP1HzM4vKmb2TInv4+14FOBCtryT1RkQsjmZZ7aMA/dMab12FlJ5UoiEsEJHwPRiQQjjsKqPFrmJmtDL9nLP8C5YrGZXBRYBwBAlhCYzeWDWevK6tsl5cHnBHObfiyuQE4SLcdvODTUnCeroGFgeKilhTGfkWa3w3qIyx5vextvTwl8OaSL1bl2nuGnnQvspcIVuwbXXXNJe7sOPd5lH54yKojHVkdqo4hvjOFvC5eQ99pN0xnImeP5wayY9Tg533aD6JCEBttELuwHRhOjcvsqrgbSkix9MCTe+xcCM5Xvh78AiZE7KRHupi/qF+Zm/N4f35/qtnCwDom2r89tP9SaHW6XtAL6aXQQg1hOI4n+V3K6x1CNB4GjoQ==
*/
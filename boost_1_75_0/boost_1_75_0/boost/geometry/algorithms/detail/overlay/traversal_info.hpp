// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_INFO_HPP


#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/enrichment_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/visit_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template <typename Point, typename SegmentRatio>
struct traversal_turn_operation : public turn_operation<Point, SegmentRatio>
{
    enrichment_info<Point> enriched;
    visit_info visited;
};

template <typename Point, typename SegmentRatio>
struct traversal_turn_info
    : public turn_info
                <
                    Point,
                    SegmentRatio,
                    traversal_turn_operation<Point, SegmentRatio>
                >
{};



}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TRAVERSAL_INFO_HPP

/* traversal_info.hpp
UvxvnpMlOZGJ7FT7z22/TDdG5FvzXrO1tMi+jZP7Tf6jRmoJ6qEzqJ5q2D4CSPiDxuA1rcj4JInYDN2rQUx+eJtzbqTsLlO+BL0GPfrEcM0WZDmG/N2D5FDuRxjnG51xIx36AXZaw9Zy/CWSdCi6QAjoUhffDlcXnx7riyR1FG+QP65mgtT2DWyHXyYO39JGxZyWN3N/PTSh5E1nlu1uJTJ3IHGLJr918eJH2QApfgQBKETlQ03b0z+cdaec3oPFf9PlTWXTnJfvkrVHbgCYgdnV/8bZBmdXP9q7CRmt/mjCwkK2qSaA4Afnc0yF28/giAUyYhHlpYlCcjJvmtOkgl28smkzsl0K2b0FMpBZhpKPeegIlMeFz7Bpxmvrxa8O3rHG3g0qNmR3f4cZ8mAI1Lt0A/tFg2CUnN375EWrR3fEfzmmM79bJQiTJjmmEOzie+kcU5b2M9N+17Phzo8PeYr+XD/7Zg/oUnC4ULPPHTwQcuNA25Tsx67y+QfXSXho9nW80LG5ht6NU4hM8PybixIA5GstkrENl1jh6C8qldEtUyGbsRfvLezzCHo8lell/pseRrxgiBCJ9APPS5h6sBoqW5/9hQQKfQXZMs+2+EqsPD0fZL+DFTVAX1++8U1HKNmPT5HP47LSjXtD1v8Nwwb8bbJrjHGvltJldkqk28JhsfXXdMjbjz/zup1xv8PjsRNpjzIRAjzRYHc/
*/
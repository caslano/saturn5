// Boost.Geometry Index
//
// R-tree nodes weak visitor and nodes base type
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_VISITOR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_VISITOR_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// empty visitor
template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag, bool IsVisitableConst>
struct weak_visitor {};

// node

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct weak_node {};

// nodes variants forward declarations

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct weak_internal_node;

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct weak_leaf;

// nodes conversion

template <typename Derived, typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
inline Derived & get(weak_node<Value, Parameters, Box, Allocators, Tag> & n)
{
    return static_cast<Derived&>(n);
}

// apply visitor

template <typename Visitor, typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
inline void apply_visitor(Visitor & v,
                          weak_node<Value, Parameters, Box, Allocators, Tag> & n,
                          bool is_internal_node)
{
    BOOST_GEOMETRY_INDEX_ASSERT(&n, "null ptr");
    if ( is_internal_node )
    {
        typedef weak_internal_node<Value, Parameters, Box, Allocators, Tag> internal_node;
        v(get<internal_node>(n));
    }
    else
    {
        typedef weak_leaf<Value, Parameters, Box, Allocators, Tag> leaf;
        v(get<leaf>(n));
    }
}

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_DYNAMIC_VISITOR_HPP

/* weak_visitor.hpp
MmJvvI+Dly9f4BmeD58PFQ61NVRhHskuyZ8rvMnbkfelvrwcBHqnQBG6GmyoFqUJCK6Ia+0J3K9MRjZQDh2QU8i8WfIfYxFLQmEqwvjk6+lk+klhXZqsFJIr1yCUrqlylPqC4Ckjc9Fx1NpHuILhTJ6bEJmwicbZAWsTIvlVEA6R11Vw0BfaVHrJQjqijLEOr5Ika3zF2Se5y0KSbZc/KOPqz0pOOYmVvoKrI6JDE0hBIhVWLjeFtGwID9bNsjKhVDfZsJTNE+cRqKqEi3GGQpc2Yb6xR0kYas7YRGmCs0Gk1qVb/RPIPgpL0XjLQuwDB+WObVZo+CL5Nrhd+VZi42lr8L1bc5NvDmc5GeyM5pjMd7DUwQSF75PF8cm3Bb6PZrPRdHGKk48YTU+F7PNkeshbb1jMgy5rT4HFPcyqrgzlG83/9yS93q6xWdXkhB3ZvTRQbOpBucPjXTVpS8XhZD768OWoKxk9rhh8eCL7FvDsQBZZ8GFoxPohTGdV6UIUNwrHXiocSP+vcfs0dlPgHIyNGIs4n8JAlqLP9jLetYis1B59wajeXRewm+9X7tzY+sGQWoewdj6/J2rpXIWOJ2WEPaf8ocAt28OxnbQcFqtXtP+ag9i5UQjNil5h7yan/R/Dn2+5LMhCuYsn
*/
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
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
*/
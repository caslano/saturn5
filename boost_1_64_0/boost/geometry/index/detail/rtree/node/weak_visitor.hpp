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
o3GR82z4KZL2ljQm6HZXZUowZzygOPJ8t6+mQTfFMI/2VhlodTzXpceyIVthS8/9s2+Sp6b9K0ay2XUmm1OUnk20X3RCbvhTreL2dfoW5ffELjBuKNQ+vCRlLPORoXO5Pi8LbxvLmT9RQvumsoZKdOJ+b3brUXay8jpwyQmXWgRFecjFFJTyqtHMMRVfbnFCwB6UIKLRNlC4zfSquR2wspP7q4WPMBYYyJxEEBOrVYZ8vG9ZhiJATdwtFxl4F3T+xz6cocLWej2CTgZMcFHjLWdNNRSMZkQ7p/yleGNQ3cJ3A4EZkjSjcNp1KHkQ/xX/zkjNymPm6BwAzQ4bdjd04M4WZF7r43qYvj7yGHKoTFYtqiZzTCL7eXNu2mnWsu0lLGRwuKdmYgVWCVzH9v0oTg2ZVY+fOK/bEXIt6Z6fUsvCgxem3rVa+w0X9A9bIBAuBiTKrUHS1hKcsf/d6YxfZcrjlwp2SdufDcFHEAgbP3npQYsCVuGVtPs5gCTtihl64+rdXUvFwwng29FxWCg9qRpnHORFBLtu3AOMNKslT3KH9aPgAz19nAy0dQ==
*/
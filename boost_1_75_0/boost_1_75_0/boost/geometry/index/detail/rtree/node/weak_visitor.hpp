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
vcV+I+FoY6LCdtLU9K11Lg/akvBdq+b7GJ55wPpyO3bK1d11somAVa7zKsll08U3vTZENAlXaY3pD9CNpGg5eAkJcC6HvD9uOm471ZBufqOBZXWedH2uC8g3v7b44fIvKXdbuy1iW9s9OjfUYnLQ9xtYcj3wJ0vupUubnYfbEMpUUeUXjT/hhnVWx5j9JSU5/YYbHwTtLrBa3M6ikus7y336SNx/UWzpvbh5cdldgvyhbQnpAoJFG7rGv+UwBvZ+5/4g4c0WKsMut5Adn9sqNkiSUVsLEYfk1sR3KJtPNkz57NoI1+/8IGFFqf1ZKXEuW/iayNiUdsKNJ3WGteEaMygFCC/OLOS0MphPNnCQw9JmwFRq2agPpzorWgPtd4DbKCMw9c2Nv3DKL547036vc43YflSYjIhMYCcbtFly7IIFZkxF2O4XWRWrOIv+sHD1A8kKPyfaozyQfS99b+rFX9URcfeniCw5d6XUphzp9qONsonJvmuxO/KZT9W7bHa9gpAgapFQ8i/sRswoMcm3xlRmdPvqfR9Z5/bV90ODnvBaSPiU9zG/1JJe/8an5CcDC6zibXX7C+cR3Jis5N6fm5hvpv84ch/FECu5kN9u4ml31RKNTK8hL//lPxxuqnj9yV7Xh628UrAvCyuypPRuIfn7X28uYyCn+PebQISdJ8nsd+9v7AXoMdFV/a3amYIKzQmZUoT42CV187x2
*/
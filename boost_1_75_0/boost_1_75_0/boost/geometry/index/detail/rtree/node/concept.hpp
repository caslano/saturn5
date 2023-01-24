// Boost.Geometry Index
//
// R-tree node concept
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_CONCEPT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_CONCEPT_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct node
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_TAG_TYPE,
        (node));
};

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct internal_node
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_TAG_TYPE,
        (internal_node));
};

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct leaf
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_TAG_TYPE,
        (leaf));
};

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag, bool IsVisitableConst>
struct visitor
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_TAG_TYPE,
        (visitor));
};

template <typename Allocator, typename Value, typename Parameters, typename Box, typename Tag>
class allocators
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_TAG_TYPE,
        (allocators));
};

template <typename Allocators, typename Node>
struct create_node
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_NODE_TYPE,
        (create_node));
};

template <typename Allocators, typename Node>
struct destroy_node
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_NODE_TYPE,
        (destroy_node));
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_CONCEPT_HPP

/* concept.hpp
but7uNOf4NEPHsdFSWLRnWhFXbkXcD0R2WBcTXmjuRscNIO2LoQltsV3GkfezeYMgPzd+eTLB6kodfpTfXTacDUc9XsUdTBqqb9XLFcncSn448a3cDXR/XOsQuH8Of38mbQjn3f3dvkQYZFs32vFJkJTLRwRMM7+HkCyED1/XC9/lEJhROBrWiENS4mU0lhIeCX6wb75F96N1ESNxvzfjcHXAihZBqh8Tcv5VbMhxXMvp9xfvN95rzBoEKyTkM/eGCYngJG1wK7q9w0zPhSDsWAO61s1JXTlrUIL2VfHWZrZLKkfnmF8ovRcOGfl6O/TYwywBKHT3F9VeGnST4KVeWi9yU1tpE9ITrvtN/wxQ45yMRK9AS2rThseL91DL4KpTt9nS4riMP/9MfF76kXzZY6+aqYy3/V/sO0VwX8HWC50Dj1V7ufJxbCRKpy4S1WNGlCRC0lSA+AL3ieAhzUNXTLRbWtXNB2Zlm4Mdd5tZH0OOVKsN/wkrUqh72IOJ1+k7E7po5tvd02Im2t01cJxkKtAFZc9ESFewt4nl77HdUIDNQ4294SnoYBdJ1/KwCsEptqhwBMDMuk7Ts/ARpJUZwaFKsBBhaQ7vL/rPKztbfXdD+dgcHp7XoU2SAMRa9IlO8r2yzoOSD2Drj4uff8z+WKcwPm+MF7+ERvun7q37yCbTWUlWB307bEzWeviznkXlHARB4o9SrNNL1yL
*/
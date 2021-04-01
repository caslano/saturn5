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
/Gom9vtVrQ4Y/iX+wLmGxjG51NtrqeYjS3qg5W714ZD0pqW/URvxpU8aqRm6l/141GWwkxY5nBnMznfOV0b/NuR8IP4WeLAIQ6822MwLPIKa38AuFAGjWB3CtH5h2DrqHZlnLyDfv4YrdKPHCg2Ga0XFAPD8CCtiOW/NGf/j9zcihIOC6txS2xByIY1gZR4pjd/CzE37Z7HC73gecKogTExwDugPaY6kDX6yCGauNCzzSTyiwYWNeOuIzvhK/mP+ASMgzjSZouNhl9CZyd10JxH7WDcG8YWaJxbRLuDtEJUMmk9XNRNrjSAbh1jZpBnv5fN+3JjSpQ1v4wTCsfKD4mzZ9c7Mg8OcYWj4poP+1cJarXtS0D2wIaLpxw8rZoLirL9yxnzSnXCfpfniUNzgC5gQCy4cVv4CD9mYCn1t1Uo1X2pauAau5TAoCvVYepocMcuMQl7sp7PqIz4Fkq3/2bUGQDO6I6ISvZE31MhGqs3HBTB4n3VDgujWfjGGXZrh/l48PgQdQa0u3G7YIwOAJOi1yuwoZ5eWvsAHEnAb5Sa4KCwfXVnsBMUgVg==
*/
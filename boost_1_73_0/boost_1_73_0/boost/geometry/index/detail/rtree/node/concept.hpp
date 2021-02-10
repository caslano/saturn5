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
aJY6CqGkvUchjEO0AcJTGUsbmBRlLTHO21OduaZDcrJILsKM6Dow9hJVYnAuW/TL7iffG55+9BANva534zp08X1F8KE3oX0fu2fdd9jaOVwfHs5mu48orsf9SUkxmx0e7rYqEtJy1B/1fPQc6EzLJ54J4MJPRIpL7xtHHjKFf9b3CI7F601G3f54V3z7bU105fX8dxfYREoWRF4tVW/Ah6+7H3tXo9ZLSogZW3gpI7iEzADd+5dXl1QswXCMgBAeLpHupSfgAticI7lpLbot+10MM7BafcovT+3sHF2JN2/Ed8j5fSQ+8+NmregVisv/LjarmFpg9j51bBx6eWZ1yNG60aXkUab53gbYe51aCitL3RlCMkRAokhS42goROhXiKDFYdhTur5joddQyNVPjjwH6YJJrND5Uce4JcA0N7H1+Oa76DhwKZDHVt/GPAJk6K9vdYAQZimvlev2JaoRWur7/UjHdyCkVsrxazCzm30Rqcy7e/Q3OXlyK0pOiFckgRkbZzcQkzBodJiQCeTC5Nw1oAFCkwx+xcjSFEpOzVIVepUIuBKX6iFEU25u+ng6CanGof12alPm36vtF1aqqJENRVm76u5qWxMq0Bty/8lSOFEhRVGRrJilmC/KQhVWRdM+iZe4i4HxKns2
*/
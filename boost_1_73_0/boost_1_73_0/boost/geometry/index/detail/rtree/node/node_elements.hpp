// Boost.Geometry Index
//
// R-tree node elements access
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_ELEMENTS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_ELEMENTS_HPP

#include <boost/container/vector.hpp>
#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>
#include <boost/geometry/index/detail/varray.hpp>
#include <boost/geometry/index/detail/rtree/node/pairs.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// element's indexable type

template <typename Element, typename Translator>
struct element_indexable_type
{
    typedef typename indexable_type<Translator>::type type;
};

template <typename First, typename Pointer, typename Translator>
struct element_indexable_type<
    rtree::ptr_pair<First, Pointer>,
    Translator
>
{
    typedef First type;
};

// is leaf element

template <typename Element>
struct is_leaf_element
{
    static const bool value = true;
};

template <typename First, typename Pointer>
struct is_leaf_element< rtree::ptr_pair<First, Pointer> >
{
    static const bool value = false;
};

// element's indexable getter

template <typename Element, typename Translator>
typename result_type<Translator>::type
element_indexable(Element const& el, Translator const& tr)
{
    return tr(el);
}

template <typename First, typename Pointer, typename Translator>
First const&
element_indexable(rtree::ptr_pair<First, Pointer> const& el, Translator const& /*tr*/)
{
    return el.first;
}

// nodes elements

template <typename Node>
struct elements_type
{
    typedef typename Node::elements_type type;
};

template <typename Node>
inline typename elements_type<Node>::type &
elements(Node & n)
{
    return n.elements;
}

template <typename Node>
inline typename elements_type<Node>::type const&
elements(Node const& n)
{
    return n.elements;
}

// elements derived type

template <typename Elements, typename NewValue>
struct container_from_elements_type
{
    typedef boost::container::vector<NewValue> type;
};

template <typename OldValue, size_t N, typename NewValue>
struct container_from_elements_type<detail::varray<OldValue, N>, NewValue>
{
    typedef detail::varray<NewValue, N> type;
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_NODE_ELEMENTS_HPP

/* node_elements.hpp
+cbdL+9Unvj0iuaX419Z/vqlDWyW0+tFEtkRfo3Uh1RaqnOQJmyLo421VardnVSUS3Yq+wPX5prKwkrGWTmkTA1m2ebuSbmYKmRKcOeadRYdNa9u0ThIAxSc2w0oHVf+PmnKTa6j2WA1pzenaq2CnEuUfGB9B5Isf/BXJr2z7k2R04Tvm6desdPp/wFQSwMECgAAAAgALWdKUgj/kQ7oBQAAlw8AABkACQBjdXJsLW1hc3Rlci9saWIvbXVsdGlpZi5oVVQFAAG2SCRgrVdhT9tIEP3OrxiVD5dwadL2w+l6RacLIZSokKDEqIdUabWxN3iv9q7lXRNy6o+/N2uHEEqA6poWbMc7897OzpsZ9vXCJGpBp8P+8XAqBpfTM3F+eRaNRifidG8fr7RRO972Dn7eZ48O6NmPCD8CH1yDxUVp/1Gxf3y1EN+o/gerL7g+B9Kjjck30abnTb5RK5iIBuWQ74V4DugLc+NfPbb8IvgW38CMLQe2WJX6OvXUGrTp7fv3v9Nrevfm3dsOHUujVUYzr8xcldcdOkzCN3+l8va269SfHVKeZNZtXEWpduTswi9lqQj3mY6VcSoh6ShRLi71HA/akE8VLXSmaDC5uBqNP3Zomeo4ZScrW5FLbZUllMobRaWKlb6pfRSy
*/
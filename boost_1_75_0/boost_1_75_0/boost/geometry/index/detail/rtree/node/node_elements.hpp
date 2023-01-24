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
m8rygufnEpXsJkVq1aw+p5zUhiLfWedOgTJKl6CLlopZukEFOPXVjVXi2MhKKy+ICjQ20lr4eJ6+23WeXJIekKI0xcFaKHihxVdRmsBCVJY2IQPsyhzfe9x9UJteZn18UWq2SlLuWSk5OP/rjRC5LnolxhjqHMoe2l5ZZ1GZ87drSPFz1wFNEQrHAVHBe6XsSKXmUJZp83LmW7HmZEwHh4/3OOeeOm7rS+ny+oEbv2BDGjckg00vYzWyMFAi8zswDSkw5Zts3QalxYXRHz2hCcug6qi95WB4VmWz/Hq76FodSwM/+JGHtOTd1Nv0jPvBqykEajUN5OkEXuPZFAFJHMl4athZx3VkG+jyuylToPNHVNv0ZFvnh+kPjN/EH0yYjNbHvkEu13x0ziJ7tBsen7b4Dnzs/5NglC2dFJmH54JddXzrtddm51b39vziMRkRM/8pSFDjL8Org5r9X4L+DO4iPOKHHz15v3ZVRAMlulpZTutz7neuTp4Fv2Kh2gJdUQcvwhDPK1WkAJcXHKgc6BwADia7C7aQCoU8QpEh/m7whv6GSrc3CnlwAiwg21b81HoDY0POlLCWrAV7AQ0XJcy+UzvVINggZDnYqdsguPlNko0lJIYr3DtXFtGulcvZS7UB7xYN9gu5D74PwfwC8f4hhhX/feTZS/E+AbW+XyiN66Zo8yCcrCn+Y3mXje3EsTLDFGCw9uBycS7f
*/
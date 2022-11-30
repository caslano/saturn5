// Boost.Geometry Index
//
// R-tree deep copying visitor implementation
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COPY_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COPY_HPP

#include <boost/geometry/index/detail/rtree/node/subtree_destroyer.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename MembersHolder>
class copy
    : public MembersHolder::visitor
{
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef rtree::subtree_destroyer<MembersHolder> subtree_destroyer;
    typedef typename allocators_type::node_pointer node_pointer;

public:
    explicit inline copy(allocators_type & allocators)
        : result(0)
        , m_allocators(allocators)
    {}

    inline void operator()(internal_node & n)
    {
        node_pointer raw_new_node = rtree::create_node<allocators_type, internal_node>::apply(m_allocators);      // MAY THROW, STRONG (N: alloc)
        subtree_destroyer new_node(raw_new_node, m_allocators);

        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type & elements = rtree::elements(n);

        elements_type & elements_dst = rtree::elements(rtree::get<internal_node>(*new_node));

        for (typename elements_type::iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            rtree::apply_visitor(*this, *it->second);                                                   // MAY THROW (V, E: alloc, copy, N: alloc) 

            // for exception safety
            subtree_destroyer auto_result(result, m_allocators);

            elements_dst.push_back( rtree::make_ptr_pair(it->first, result) );                          // MAY THROW, STRONG (E: alloc, copy)

            auto_result.release();
        }

        result = new_node.get();
        new_node.release();
    }

    inline void operator()(leaf & l)
    {
        node_pointer raw_new_node = rtree::create_node<allocators_type, leaf>::apply(m_allocators);                // MAY THROW, STRONG (N: alloc)
        subtree_destroyer new_node(raw_new_node, m_allocators);

        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type & elements = rtree::elements(l);

        elements_type & elements_dst = rtree::elements(rtree::get<leaf>(*new_node));

        for (typename elements_type::iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            elements_dst.push_back(*it);                                                                // MAY THROW, STRONG (V: alloc, copy)
        }

        result = new_node.get();
        new_node.release();
    }

    node_pointer result;

private:
    allocators_type & m_allocators;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COPY_HPP

/* copy.hpp
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
*/
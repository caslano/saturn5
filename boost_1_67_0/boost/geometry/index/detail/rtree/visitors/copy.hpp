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
// Boost.Geometry Index
//
// R-tree subtree scoped destroyer
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SUBTREE_DESTROYED_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SUBTREE_DESTROYED_HPP

#include <boost/geometry/index/detail/rtree/visitors/destroy.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

template <typename MembersHolder>
class subtree_destroyer
{
    typedef typename MembersHolder::node node;

    typedef typename MembersHolder::allocators_type allocators_type;
    typedef typename MembersHolder::node_pointer pointer;

    subtree_destroyer(subtree_destroyer const&);
    subtree_destroyer & operator=(subtree_destroyer const&);

public:
    subtree_destroyer(pointer ptr, allocators_type & allocators)
        : m_ptr(ptr)
        , m_allocators(allocators)
    {}

    ~subtree_destroyer()
    {
        reset();
    }

    void reset(pointer ptr = 0)
    {
        if ( m_ptr && m_ptr != ptr )
        {
            detail::rtree::visitors::destroy<MembersHolder>::apply(m_ptr, m_allocators);
        }
        m_ptr = ptr;
    }

    void release()
    {
        m_ptr = 0;
    }

    pointer get() const
    {
        return m_ptr;
    }

    node & operator*() const
    {
        return *m_ptr;
    }

    pointer operator->() const
    {
        return m_ptr;
    }

private:
    pointer m_ptr;
    allocators_type & m_allocators;
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SUBTREE_DESTROYED_HPP

/* subtree_destroyer.hpp
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
*/
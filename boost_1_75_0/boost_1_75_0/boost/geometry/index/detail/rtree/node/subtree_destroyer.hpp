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
7eEUvkPqIwfxml4Ygrmq1oUPS7Qm2OnTWLn6mKyoyY2wufGrdTPlfYvcH41vdtBMC8/tgONi269iu1jFBAsNQ9wzwcbVPjuI7HB8Hv+uu0eyzq2M/XYlOG3PDRnhpe/mQzVxZym2sFAa9j5r6DJTyOPLtriNiRemAKovp7SoahPy6P4lKM9GaDVspnm73315OG9Yf+ltHX5fc6wZqrje9eGPuG4+HF7uu7EyZvk+5RbxdKlVqUPa6eQi0/r1x21sB6X+L2yTxVe6rZ5QC6ObzexrPP/xuR+YnOuK7RrLWCorst4VgYgfkII/HvidPctcxWH63NVxQOWS2jdiEti5/umd8usl1KYqgWjvXD5TbXW+zJ7Yf1XpyiYrX0i/1LpvKyOQNTm2Uz/p6MEnpB/VFn5+8fvDTuiiaWIzpvxFYWBmkGr7a0rKo72dULLL4cN9N9HZ2iu+KOHtP3bdj8G8DKdrdG9JToGS/BbGhFp1i7W856yLH7wShfxrUfBJfxeicRBtyDTEwa1FUbV0NTNKP1ZK4mmDWlGmAgMtKPylUbbbVvLsokZ+MYLECSlneQ0/s3gTgQsM7+6Yz/eZC/B38pjwIBFw0NH9hw6fV/6dWE9QFBPmbgh2qakU535RlA6+YOiFuzbGxAIkJbwL7UGFwH/nXakpYQjjbnLt69o3tWnsZnEhgvU0y4z2nxZYxTrC2M0Ff2qTmBrIOvGf
*/
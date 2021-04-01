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
tJb28v2ViLbV3bukD6qGAEaolZkfzsbB+xY5FssVdjpoWTUUfh0fGRVzNojVHaoxHC4Mhqx+XtzufKFgpjKdv1WnTEXLJGZ6qaZzoHfYGmioGqX2llk5BozMCN2S5PcQtoaZM0v2hNOPmYjuIKDu9vu7hAUiRjsw2EJJv8rUEPhxwqFgYHzpEstGJTOsZamuGEJcAve185S9q4ybD4YFkz+1ob5M4khO95Xk+7T3Fg9xFexygg1KzzPSyHGkIrAWkw/i3zDgVdf/E9pmN3cyCcjMzNUvZe4WbKv3znlKk1YFBBWWhqCz5Gf+5RVJ7YeKaxRJOT5I1giyDbRhXE5nm4F03kAEx1eebm3HuVChbrYxTz+FKTRZEvhJK9Lalatdby6LSVDf6RXqEaaC5tFL+Ve68Cxie0CMM+pK0jygTp4oed8ExfnE5ZruAjxBrerYT+uKup1DbbrqwjQnagSzAFP5RksSGBXOTMxHS4Zq1fxoSqW41dsgeRdJNtcAiwAQtj5xwXBMC03jEkrEww6kvaWBSoaZtE5lyAygo+yToT3W6qZa4SIXm4yXIA==
*/
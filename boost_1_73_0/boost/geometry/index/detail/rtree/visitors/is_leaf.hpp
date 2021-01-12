// Boost.Geometry Index
//
// R-tree leaf node checking visitor implementation
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_IS_LEAF_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_IS_LEAF_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename MembersHolder>
struct is_leaf
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    is_leaf()
        : result(false)
    {}

    inline void operator()(internal_node const&)
    {
        // result = false;
    }

    inline void operator()(leaf const&)
    {
        result = true;
    }

    bool result;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_IS_LEAF_HPP

/* is_leaf.hpp
J2beT32aQ+cCmC+zWqaFf6D+hMUyC90/gsbnKVgDZnGbfJtRv1zEOsjs8pUhtGaFwpowW/PiFTqzJ8KCmf2yM78VjUGYN7NJMWPa054q2Knl6RF03hXq0juuKZ0Z+sPqMBuue3ovjQlYoGb4nU4L8fntoTYqZ4PFlFl62iKd+02z6TBfV7ml2jrYQz+f8gDLcNlRodxx2GpXbj/V7hnXctAeMP+SO6ZYbgFslAe7Dov0YOHf
*/
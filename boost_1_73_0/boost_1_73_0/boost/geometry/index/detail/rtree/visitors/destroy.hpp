// Boost.Geometry Index
//
// R-tree destroying visitor implementation
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DELETE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DELETE_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename MembersHolder>
class destroy
    : public MembersHolder::visitor
{
public:
    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef typename MembersHolder::allocators_type allocators_type;
    typedef typename MembersHolder::node_pointer node_pointer;

    inline destroy(node_pointer node, allocators_type & allocators)
        : m_current_node(node)
        , m_allocators(allocators)
    {}

    inline void operator()(internal_node & n)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(&n == &rtree::get<internal_node>(*m_current_node), "invalid pointers");

        node_pointer node_to_destroy = m_current_node;

        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type & elements = rtree::elements(n);

        for (typename elements_type::iterator it = elements.begin();
             it != elements.end(); ++it)
        {
            m_current_node = it->second;
            rtree::apply_visitor(*this, *m_current_node);
            it->second = 0;
        }

        rtree::destroy_node<allocators_type, internal_node>::apply(m_allocators, node_to_destroy);
    }

    inline void operator()(leaf & l)
    {
        boost::ignore_unused(l);
        BOOST_GEOMETRY_INDEX_ASSERT(&l == &rtree::get<leaf>(*m_current_node), "invalid pointers");

        rtree::destroy_node<allocators_type, leaf>::apply(m_allocators, m_current_node);
    }

    static inline void apply(node_pointer node, allocators_type & allocators)
    {
        destroy v(node, allocators);
        rtree::apply_visitor(v, *node);
    }

private:
    node_pointer m_current_node;
    allocators_type & m_allocators;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_DELETE_HPP

/* destroy.hpp
Ci7OWj2eH26CiPvmdFMqJ7hQt3DrfUWv8mB5h0cqfLBJrjubZLdCu0rCpv7dpW7hln90pZv5qJN2XPPKAeR/BYmnbm7CPpdJ2xdI3elR21Mqbnx9D37vbV3c9s5JLww6NxwA2F63eDFtWw99UDnjdWskv2ssuX2O9uBt4WP6dWK8d69Dam3Du+RA4a1Q2NQZ1XzKNRcT/cbtPm387gX/KZo5uOAvpczKOq0gfKIzP+vqYUn/kkFuXPDrVXtBz87LhNLBEQtf1tY3KHxos0jNHCEhY0Ff4B1dbFzuU0lA186mpE95PDaacvM13f8XRiNbd1PKi+e8dn6nrPNN7+b6anbz5ur85MwdX2x4012K3GOn1oj1v6Po/KuJd5enfMkE4K9cVqLQvViVdGz74vnh83/3eVln7g0P0xqe0tALOM9yS+cNdPzG521kVn9H06oVSP4/UEsDBAoAAAAIAC1nSlJt5JC4AAQAADgKAAAWAAkAY3VybC1tYXN0ZXIvbGliL253b3MuY1VUBQABtkgkYK1VbW/bNhD+7l9xcL/ImWolWQusW1LMVZzWmCsHtbMsQACBFk8WF4kUSMqO1/S/70g7MZI48V4qw5ZM3j3Pc3e8U7T3/a4W7MHOK/XflC66e48zrf7EzG63TtNb
*/
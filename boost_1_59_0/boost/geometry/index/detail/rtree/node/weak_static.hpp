// Boost.Geometry Index
//
// R-tree nodes based on static conversion, storing static-size containers
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2021.
// Modifications copyright (c) 2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_STATIC_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_STATIC_HPP

#include <boost/geometry/index/detail/rtree/node/weak_dynamic.hpp>
#include <boost/geometry/index/detail/varray.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct weak_internal_node<Value, Parameters, Box, Allocators, node_weak_static_tag>
    : public weak_node<Value, Parameters, Box, Allocators, node_weak_static_tag>
{
    typedef detail::varray<
        rtree::ptr_pair<Box, typename Allocators::node_pointer>,
        Parameters::max_elements + 1
    > elements_type;

    template <typename Alloc>
    inline weak_internal_node(Alloc const&) {}

    elements_type elements;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct weak_leaf<Value, Parameters, Box, Allocators, node_weak_static_tag>
    : public weak_node<Value, Parameters, Box, Allocators, node_weak_static_tag>
{
    typedef detail::varray<
        Value,
        Parameters::max_elements + 1
    > elements_type;

    template <typename Alloc>
    inline weak_leaf(Alloc const&) {}

    elements_type elements;
};

// nodes traits

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct node<Value, Parameters, Box, Allocators, node_weak_static_tag>
{
    typedef weak_node<Value, Parameters, Box, Allocators, node_weak_static_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct internal_node<Value, Parameters, Box, Allocators, node_weak_static_tag>
{
    typedef weak_internal_node<Value, Parameters, Box, Allocators, node_weak_static_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct leaf<Value, Parameters, Box, Allocators, node_weak_static_tag>
{
    typedef weak_leaf<Value, Parameters, Box, Allocators, node_weak_static_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators, bool IsVisitableConst>
struct visitor<Value, Parameters, Box, Allocators, node_weak_static_tag, IsVisitableConst>
{
    typedef weak_visitor<Value, Parameters, Box, Allocators, node_weak_static_tag, IsVisitableConst> type;
};

// allocators

template <typename Allocator, typename Value, typename Parameters, typename Box>
class allocators<Allocator, Value, Parameters, Box, node_weak_static_tag>
    : public detail::rtree::internal_node_alloc<Allocator, Value, Parameters, Box, node_weak_static_tag>::type
    , public detail::rtree::leaf_alloc<Allocator, Value, Parameters, Box, node_weak_static_tag>::type
{
    typedef detail::rtree::internal_node_alloc
        <
            Allocator, Value, Parameters, Box, node_weak_static_tag
        > internal_node_alloc;

    typedef detail::rtree::leaf_alloc
        <
            Allocator, Value, Parameters, Box, node_weak_static_tag
        > leaf_alloc;

    typedef detail::rtree::node_alloc
        <
            Allocator, Value, Parameters, Box, node_weak_static_tag
        > node_alloc;

public:
    typedef typename internal_node_alloc::type internal_node_allocator_type;
    typedef typename leaf_alloc::type leaf_allocator_type;
    typedef typename node_alloc::traits::pointer node_pointer;

private:
    typedef typename boost::container::allocator_traits
        <
            leaf_allocator_type
        >::template rebind_alloc<Value> value_allocator_type;
    typedef boost::container::allocator_traits<value_allocator_type> value_allocator_traits;

public:
    typedef Allocator allocator_type;

    typedef Value value_type;
    typedef typename value_allocator_traits::reference reference;
    typedef typename value_allocator_traits::const_reference const_reference;
    typedef typename value_allocator_traits::size_type size_type;
    typedef typename value_allocator_traits::difference_type difference_type;
    typedef typename value_allocator_traits::pointer pointer;
    typedef typename value_allocator_traits::const_pointer const_pointer;

    inline allocators()
        : internal_node_allocator_type()
        , leaf_allocator_type()
    {}

    template <typename Alloc>
    inline explicit allocators(Alloc const& alloc)
        : internal_node_allocator_type(alloc)
        , leaf_allocator_type(alloc)
    {}

    inline allocators(BOOST_FWD_REF(allocators) a)
        : internal_node_allocator_type(boost::move(a.internal_node_allocator()))
        , leaf_allocator_type(boost::move(a.leaf_allocator()))
    {}

    inline allocators & operator=(BOOST_FWD_REF(allocators) a)
    {
        internal_node_allocator() = ::boost::move(a.internal_node_allocator());
        leaf_allocator() = ::boost::move(a.leaf_allocator());
        return *this;
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    inline allocators & operator=(allocators const& a)
    {
        internal_node_allocator() = a.internal_node_allocator();
        leaf_allocator() = a.leaf_allocator();
        return *this;
    }
#endif

    void swap(allocators & a)
    {
        boost::swap(internal_node_allocator(), a.internal_node_allocator());
        boost::swap(leaf_allocator(), a.leaf_allocator());
    }

    bool operator==(allocators const& a) const { return leaf_allocator() == a.leaf_allocator(); }
    template <typename Alloc>
    bool operator==(Alloc const& a) const { return leaf_allocator() == leaf_allocator_type(a); }

    Allocator allocator() const { return Allocator(leaf_allocator()); }

    internal_node_allocator_type & internal_node_allocator() { return *this; }
    internal_node_allocator_type const& internal_node_allocator() const { return *this; }
    leaf_allocator_type & leaf_allocator() { return *this; }
    leaf_allocator_type const& leaf_allocator() const{ return *this; }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_STATIC_HPP

/* weak_static.hpp
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
*/
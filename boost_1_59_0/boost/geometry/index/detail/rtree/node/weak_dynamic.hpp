// Boost.Geometry Index
//
// R-tree nodes based on static conversion, storing dynamic-size containers
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_DYNAMIC_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_DYNAMIC_HPP

#include <boost/container/allocator_traits.hpp>
#include <boost/container/vector.hpp>
#include <boost/core/pointer_traits.hpp>

#include <boost/geometry/index/detail/rtree/options.hpp>
#include <boost/geometry/index/detail/rtree/node/concept.hpp>
#include <boost/geometry/index/detail/rtree/node/pairs.hpp>
#include <boost/geometry/index/detail/rtree/node/weak_visitor.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// TODO: This should be defined in options.hpp
// For now it's defined here to satisfy Boost header policy
struct node_weak_dynamic_tag {};
struct node_weak_static_tag {};

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct weak_internal_node
    : public weak_node<Value, Parameters, Box, Allocators, Tag>
{
    typedef rtree::ptr_pair<Box, typename Allocators::node_pointer> element_type;
    typedef typename boost::container::allocator_traits
        <
            typename Allocators::internal_node_allocator_type
        >::template rebind_alloc<element_type> allocator_type;

    typedef boost::container::vector<element_type, allocator_type> elements_type;

    template <typename Al>
    inline weak_internal_node(Al const& al)
        : elements(allocator_type(al))
    {}

    elements_type elements;
};

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct weak_leaf
    : public weak_node<Value, Parameters, Box, Allocators, Tag>
{
    typedef typename boost::container::allocator_traits
        <
            typename Allocators::leaf_allocator_type
        >::template rebind_alloc<Value> allocator_type;

    typedef boost::container::vector<Value, allocator_type> elements_type;

    template <typename Al>
    inline weak_leaf(Al const& al)
        : elements(allocator_type(al))
    {}

    elements_type elements;
};

// nodes traits

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct node<Value, Parameters, Box, Allocators, node_weak_dynamic_tag>
{
    typedef weak_node<Value, Parameters, Box, Allocators, node_weak_dynamic_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct internal_node<Value, Parameters, Box, Allocators, node_weak_dynamic_tag>
{
    typedef weak_internal_node<Value, Parameters, Box, Allocators, node_weak_dynamic_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct leaf<Value, Parameters, Box, Allocators, node_weak_dynamic_tag>
{
    typedef weak_leaf<Value, Parameters, Box, Allocators, node_weak_dynamic_tag> type;
};

// visitor traits

template <typename Value, typename Parameters, typename Box, typename Allocators, bool IsVisitableConst>
struct visitor<Value, Parameters, Box, Allocators, node_weak_dynamic_tag, IsVisitableConst>
{
    typedef weak_visitor<Value, Parameters, Box, Allocators, node_weak_dynamic_tag, IsVisitableConst> type;
};

// allocators

template <typename Allocator, typename Value, typename Parameters, typename Box, typename Tag>
struct internal_node_alloc
{
    typedef typename internal_node
        <
            Value, Parameters, Box,
            allocators<Allocator, Value, Parameters, Box, Tag>,
            Tag
        >::type node_type;

    typedef typename boost::container::allocator_traits
        <
            Allocator
        >::template rebind_alloc<node_type> type;
};

template <typename Allocator, typename Value, typename Parameters, typename Box, typename Tag>
struct leaf_alloc
{
    typedef typename leaf
        <
            Value, Parameters, Box,
            allocators<Allocator, Value, Parameters, Box, Tag>,
            Tag
        >::type node_type;

    typedef typename ::boost::container::allocator_traits
        <
            Allocator
        >::template rebind_alloc<node_type> type;
};

template <typename Allocator, typename Value, typename Parameters, typename Box, typename Tag>
struct node_alloc
{
    typedef typename weak_node
        <
            Value, Parameters, Box,
            allocators<Allocator, Value, Parameters, Box, Tag>,
            Tag
        >::type node_type;

    typedef typename ::boost::container::allocator_traits
        <
            Allocator
        >::template rebind_alloc<node_type> type;
};

template <typename Allocator, typename Value, typename Parameters, typename Box>
class allocators<Allocator, Value, Parameters, Box, node_weak_dynamic_tag>
    : public internal_node_alloc<Allocator, Value, Parameters, Box, node_weak_dynamic_tag>::type
    , public leaf_alloc<Allocator, Value, Parameters, Box, node_weak_dynamic_tag>::type
{
    typedef detail::rtree::internal_node_alloc
        <
            Allocator, Value, Parameters, Box, node_weak_dynamic_tag
        > internal_node_alloc;

    typedef detail::rtree::leaf_alloc
        <
            Allocator, Value, Parameters, Box, node_weak_dynamic_tag
        > leaf_alloc;

    typedef detail::rtree::node_alloc
        <
            Allocator, Value, Parameters, Box, node_weak_dynamic_tag
        > node_alloc;

public:
    typedef typename internal_node_alloc::type internal_node_allocator_type;
    typedef typename leaf_alloc::type leaf_allocator_type;
    typedef typename node_alloc::traits::pointer node_pointer;

private:
    typedef typename boost::container::allocator_traits
        <
            leaf_allocator_type // leaf_allocator_type for consistency with weak_leaf
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
    leaf_allocator_type const& leaf_allocator() const { return *this; }
};

// create_node_impl

template <typename BaseNodePtr, typename Node>
struct create_weak_node
{
    template <typename AllocNode>
    static inline BaseNodePtr apply(AllocNode & alloc_node)
    {
        typedef boost::container::allocator_traits<AllocNode> Al;
        typedef typename Al::pointer P;

        P p = Al::allocate(alloc_node, 1);

        if ( 0 == p )
            throw_runtime_error("boost::geometry::index::rtree node creation failed");

        scoped_deallocator<AllocNode> deallocator(p, alloc_node);

        Al::construct(alloc_node, boost::to_address(p), alloc_node);

        deallocator.release();
        return p;
    }
};

// destroy_node_impl

template <typename Node>
struct destroy_weak_node
{
    template <typename AllocNode, typename BaseNodePtr>
    static inline void apply(AllocNode & alloc_node, BaseNodePtr n)
    {
        typedef boost::container::allocator_traits<AllocNode> Al;
        typedef typename Al::pointer P;

        P p(&static_cast<Node&>(rtree::get<Node>(*n)));
        Al::destroy(alloc_node, boost::addressof(*p));
        Al::deallocate(alloc_node, p, 1);
    }
};

// create_node

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct create_node<
    Allocators,
    weak_internal_node<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        return create_weak_node<
            typename Allocators::node_pointer,
            weak_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.internal_node_allocator());
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct create_node<
    Allocators,
    weak_leaf<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        return create_weak_node<
            typename Allocators::node_pointer,
            weak_leaf<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.leaf_allocator());
    }
};

// destroy_node

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct destroy_node<
    Allocators,
    weak_internal_node<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline void apply(Allocators & allocators, typename Allocators::node_pointer n)
    {
        destroy_weak_node<
            weak_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.internal_node_allocator(), n);
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct destroy_node<
    Allocators,
    weak_leaf<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline void apply(Allocators & allocators, typename Allocators::node_pointer n)
    {
        destroy_weak_node<
            weak_leaf<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.leaf_allocator(), n);
    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_DYNAMIC_HPP

/* weak_dynamic.hpp
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
*/
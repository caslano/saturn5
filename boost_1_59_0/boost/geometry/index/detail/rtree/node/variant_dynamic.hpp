// Boost.Geometry Index
//
// R-tree nodes based on Boost.Variant, storing dynamic-size containers
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_DYNAMIC_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_DYNAMIC_HPP

#include <boost/container/allocator_traits.hpp>
#include <boost/container/vector.hpp>
#include <boost/core/pointer_traits.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant.hpp>

#include <boost/geometry/index/detail/rtree/options.hpp>
#include <boost/geometry/index/detail/rtree/node/concept.hpp>
#include <boost/geometry/index/detail/rtree/node/pairs.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// nodes default types

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct variant_internal_node
{
    typedef rtree::ptr_pair<Box, typename Allocators::node_pointer> element_type;
    typedef typename boost::container::allocator_traits
        <
            typename Allocators::node_allocator_type
        >::template rebind_alloc<element_type> allocator_type;

    typedef boost::container::vector<element_type, allocator_type> elements_type;

    template <typename Al>
    inline variant_internal_node(Al const& al)
        : elements(allocator_type(al))
    {}

    elements_type elements;
};

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct variant_leaf
{
    typedef typename boost::container::allocator_traits
        <
            typename Allocators::node_allocator_type
        >::template rebind_alloc<Value> allocator_type;

    typedef boost::container::vector<Value, allocator_type> elements_type;

    template <typename Al>
    inline variant_leaf(Al const& al)
        : elements(allocator_type(al))
    {}

    elements_type elements;
};

// nodes traits

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct node<Value, Parameters, Box, Allocators, node_variant_dynamic_tag>
{
    typedef boost::variant<
        variant_leaf<Value, Parameters, Box, Allocators, node_variant_dynamic_tag>,
        variant_internal_node<Value, Parameters, Box, Allocators, node_variant_dynamic_tag>
    > type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct internal_node<Value, Parameters, Box, Allocators, node_variant_dynamic_tag>
{
    typedef variant_internal_node<Value, Parameters, Box, Allocators, node_variant_dynamic_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct leaf<Value, Parameters, Box, Allocators, node_variant_dynamic_tag>
{
    typedef variant_leaf<Value, Parameters, Box, Allocators, node_variant_dynamic_tag> type;
};

// visitor traits

template <typename Value, typename Parameters, typename Box, typename Allocators, bool IsVisitableConst>
struct visitor<Value, Parameters, Box, Allocators, node_variant_dynamic_tag, IsVisitableConst>
{
    typedef static_visitor<> type;
};

// allocators

template <typename Allocator, typename Value, typename Parameters, typename Box, typename Tag>
struct node_alloc
{
    typedef typename node
        <
            Value, Parameters, Box,
            allocators<Allocator, Value, Parameters, Box, Tag>,
            Tag
        >::type node_type;

    typedef typename boost::container::allocator_traits
        <
            Allocator
        >::template rebind_alloc<node_type> type;

    typedef boost::container::allocator_traits<type> traits;
};


template <typename Allocator, typename Value, typename Parameters, typename Box>
class allocators<Allocator, Value, Parameters, Box, node_variant_dynamic_tag>
    : public detail::rtree::node_alloc
        <
            Allocator, Value, Parameters, Box, node_variant_dynamic_tag
        >::type
{
    typedef detail::rtree::node_alloc
        <
            Allocator, Value, Parameters, Box, node_variant_dynamic_tag
        > node_alloc;

public:
    typedef typename node_alloc::type node_allocator_type;
    typedef typename node_alloc::traits::pointer node_pointer;

private:
    typedef typename boost::container::allocator_traits
        <
            node_allocator_type // node_allocator_type for consistency with variant_leaf
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
        : node_allocator_type()
    {}

    template <typename Alloc>
    inline explicit allocators(Alloc const& alloc)
        : node_allocator_type(alloc)
    {}

    inline allocators(BOOST_FWD_REF(allocators) a)
        : node_allocator_type(boost::move(a.node_allocator()))
    {}

    inline allocators & operator=(BOOST_FWD_REF(allocators) a)
    {
        node_allocator() = boost::move(a.node_allocator());
        return *this;
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    inline allocators & operator=(allocators const& a)
    {
        node_allocator() = a.node_allocator();
        return *this;
    }
#endif

    void swap(allocators & a)
    {
        boost::swap(node_allocator(), a.node_allocator());
    }

    bool operator==(allocators const& a) const { return node_allocator() == a.node_allocator(); }
    template <typename Alloc>
    bool operator==(Alloc const& a) const { return node_allocator() == node_allocator_type(a); }

    Allocator allocator() const { return Allocator(node_allocator()); }

    node_allocator_type & node_allocator() { return *this; }
    node_allocator_type const& node_allocator() const { return *this; }
};

// create_node_variant

template <typename VariantPtr, typename Node>
struct create_variant_node
{
    template <typename AllocNode>
    static inline VariantPtr apply(AllocNode & alloc_node)
    {
        typedef boost::container::allocator_traits<AllocNode> Al;
        typedef typename Al::pointer P;

        P p = Al::allocate(alloc_node, 1);

        if ( 0 == p )
            throw_runtime_error("boost::geometry::index::rtree node creation failed");

        scoped_deallocator<AllocNode> deallocator(p, alloc_node);

        Al::construct(alloc_node, boost::to_address(p), Node(alloc_node)); // implicit cast to Variant

        deallocator.release();
        return p;
    }
};

// destroy_node_variant

template <typename Node>
struct destroy_variant_node
{
    template <typename AllocNode, typename VariantPtr>
    static inline void apply(AllocNode & alloc_node, VariantPtr n)
    {
        typedef boost::container::allocator_traits<AllocNode> Al;

        Al::destroy(alloc_node, boost::addressof(*n));
        Al::deallocate(alloc_node, n, 1);
    }
};

// create_node

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct create_node<
    Allocators,
    variant_internal_node<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        return create_variant_node<
            typename Allocators::node_pointer,
            variant_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.node_allocator());
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct create_node<
    Allocators,
    variant_leaf<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline typename Allocators::node_pointer
    apply(Allocators & allocators)
    {
        return create_variant_node<
            typename Allocators::node_pointer,
            variant_leaf<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.node_allocator());
    }
};

// destroy_node

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct destroy_node<
    Allocators,
    variant_internal_node<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline void apply(Allocators & allocators, typename Allocators::node_pointer n)
    {
        destroy_variant_node<
            variant_internal_node<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.node_allocator(), n);
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct destroy_node<
    Allocators,
    variant_leaf<Value, Parameters, Box, Allocators, Tag>
>
{
    static inline void apply(Allocators & allocators, typename Allocators::node_pointer n)
    {
        destroy_variant_node<
            variant_leaf<Value, Parameters, Box, Allocators, Tag>
        >::apply(allocators.node_allocator(), n);
    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_DYNAMIC_HPP

/* variant_dynamic.hpp
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
*/
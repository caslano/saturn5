// Boost.Geometry Index
//
// R-tree nodes based on Boost.Variant, storing dynamic-size containers
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_DYNAMIC_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_DYNAMIC_HPP

#include <boost/core/pointer_traits.hpp>

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
// Boost.Geometry Index
//
// R-tree nodes based on static conversion, storing dynamic-size containers
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_DYNAMIC_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_DYNAMIC_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

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
    typedef typename internal_nod
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
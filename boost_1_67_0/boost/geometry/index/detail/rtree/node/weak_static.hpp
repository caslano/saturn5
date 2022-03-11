// Boost.Geometry Index
//
// R-tree nodes based on static conversion, storing static-size containers
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_STATIC_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_WEAK_STATIC_HPP

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
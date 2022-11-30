// Boost.Geometry Index
//
// R-tree nodes based on Boost.Variant, storing static-size containers
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_STATIC_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_STATIC_HPP

#include <boost/geometry/index/detail/rtree/node/variant_dynamic.hpp>
#include <boost/geometry/index/detail/varray.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// nodes default types

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct variant_internal_node<Value, Parameters, Box, Allocators, node_variant_static_tag>
{
    typedef detail::varray<
        rtree::ptr_pair<Box, typename Allocators::node_pointer>,
        Parameters::max_elements + 1
    > elements_type;

    template <typename Alloc>
    inline variant_internal_node(Alloc const&) {}

    elements_type elements;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct variant_leaf<Value, Parameters, Box, Allocators, node_variant_static_tag>
{
    typedef detail::varray<
        Value,
        Parameters::max_elements + 1
    > elements_type;

    template <typename Alloc>
    inline variant_leaf(Alloc const&) {}

    elements_type elements;
};

// nodes traits

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct node<Value, Parameters, Box, Allocators, node_variant_static_tag>
{
    typedef boost::variant<
        variant_leaf<Value, Parameters, Box, Allocators, node_variant_static_tag>,
        variant_internal_node<Value, Parameters, Box, Allocators, node_variant_static_tag>
    > type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct internal_node<Value, Parameters, Box, Allocators, node_variant_static_tag>
{
    typedef variant_internal_node<Value, Parameters, Box, Allocators, node_variant_static_tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Allocators>
struct leaf<Value, Parameters, Box, Allocators, node_variant_static_tag>
{
    typedef variant_leaf<Value, Parameters, Box, Allocators, node_variant_static_tag> type;
};

// visitor traits

template <typename Value, typename Parameters, typename Box, typename Allocators, bool IsVisitableConst>
struct visitor<Value, Parameters, Box, Allocators, node_variant_static_tag, IsVisitableConst>
{
    typedef static_visitor<> type;
};

// allocators

template <typename Allocator, typename Value, typename Parameters, typename Box>
class allocators<Allocator, Value, Parameters, Box, node_variant_static_tag>
    : public detail::rtree::node_alloc
        <
            Allocator, Value, Parameters, Box, node_variant_static_tag
        >::type
{
    typedef detail::rtree::node_alloc
        <
            Allocator, Value, Parameters, Box, node_variant_static_tag
        > node_alloc;

public:
    typedef typename node_alloc::type node_allocator_type;
    typedef typename node_alloc::traits::pointer node_pointer;

private:
    typedef typename boost::container::allocator_traits
        <
            node_allocator_type
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

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_STATIC_HPP

/* variant_static.hpp
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
*/
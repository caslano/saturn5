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
vCvnHPW1Y5WgYO1Nlgc45/O0PLrP8PK5wfr/13a0O5eTLFF6blxpWu34L9cqvP9uVWPdFjcfRfAngtwLjRBgLj+GJXJinhLpve1OdfBWnAgp+Ty6p2wCIlgLff2YpnaZfaoIN11v1zTEO+0f5A/SNLEx0ZHkHpyOJ87J+XBijSalCwal6TraGbQO6ubsH1VjX3nkKkHGXFNt9IAyRMCTurNQqcfypaWNVh2tX3XQ/kfGzfjy5YvcsEK5dT3ZWn4OkM3c9e6oUUEdDxH5+1Ld43FuO8Z9ptdX5O8tPnce9flGr6/1+4rnywz8z3j/Kf5fswNGscqxaNhCShcNgX8LN9WG7dqkbPX9H1BLAwQKAAAACAAtZ0pSW2GbcfwCAADoBgAAFwAJAGN1cmwtbWFzdGVyL2xpYi9uZXRyYy5oVVQFAAG2SCRgrVVdb9MwFH3vrzhsD2yVaTqe+BalG6wCdagtQhNDkZvcLEapHdnOukn78dybtAymfbyQqrVr33PO9bF9s2sKm1OB46PR4dEsHX+bfUmnR4vZOD3u7fKEsXTnXNL/f08PfTz6pO035YfbFvHVu1+Uxbuj0/Qa3YdRZ9w+JpLgBnKd7uNxyDX2Wki6UXkj/TR9TOhMcpOfRJBnqXR5hGGCHLv6ypvz
*/
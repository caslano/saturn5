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
vwsowyF1/4bfjdR9PCZGf8/ABPT3DZhU/d2DOA8TVy6UM+z0/D38mIFLHyF/3wWsigbwR9gU/gRbw5/h6ZDupmIw8MAz4IPwXOiFF8J4eDNMhM/CenA7TIcvwTrwVVgXvg6T4bswBe6BteCHsDb8CLaC+2Fr+IXGaz/qbwtjYBNYEzaFtWFDmAYbwXSYARvDU2BT2Bx2hB1gHuwEC2FnOAl2hVNgN1gCe8ArYE84A/aG18A+cC7sBxfC/nARzILL4AC4HA6Gt8IhcA08E94OR8B34Di4F14IP4XnwwPwAvg1HA2PwTHwR5gN/V6ubRgHR8IkeDasC0fALvAq2BvOgqfDK+EZcAYcAcfDUTAfXgBz4KUwF+ZrPDfCyXAFLIYrYSG8DRbB22EB/AOcCNfDq+FDcA7cBKfCx2AJ3KLxvgsXwA/hfPgZvA7uh3PhQTgPfg3L4TE4Hf4DXg7jfLwPgG3hcpgJV8DOcC3sBe+AfeBSOBAug4PhjXAEXAJHwpVwDLwFnq/xlsJ18Ep4N5wJb4MV8PdwHlwNb4D3w6fgA3A7fBAelm/B9Xw62BhjX2d+2EEH84oatFs4F9aB82C62uU6xWRp+O4aPg6O0fB3ImfzLtgM/gG2gOthS3g3bKfuHdS9I7wHdlP7YTgWs1TTSdN0YuFZms52ymPzZRiAO2E8fAXWhrtgCnwVpqq9rtoPw0LMRo1/gMYfDy/W+K8jHz64AMbChTAe3ggT4A2wk7p3UfeucBHsBRfDLMfd6C2pJLrelqrelqneVqjeVqrelsN26t5B3TvCm2E3tR+GmZhcTcev6fhgC01nt+rtDeiDb8Jg/kqPk7/Vmr9bNX+3af5u1/ytge3UvYO6d4S/h93UfhgOxWzVdFI0nRjYV9PZqvl7FgbgczAObtP6fR4mO3bTTvZqfP1d2skm5GrCh2EK3AzrwydhI/g4bAu3wEx17wWfgI4+9QwqGO+iz/tVLxtgHHxAy2mZc56Q8TjhGvL7iIarq9dVOuwEm8Ms2BaeA9vBItgeToUd4BWwI5wDT4XXwk7wOtgZ3gC7wCWwK7wPdoPPwO5wB+yh+esFv4ODoNceN2AGHADbwoGwPRwEu8O+cATsB8+D/eE0eDq8EraAv4Ot4FoNZ9ojgh4YcNFftupvFPTD82GwnyrVcB1c+ql/ar3+AJvAH2Fr+FNIvW3U8D6XdMdpuhdBL8zRdLMwWzVcMw0XgF013JnaPw6DKXAkTFN7Q8du8n9I46ntkn+vpu+DNaAf1oIx5jrRc3dgA8z+iOvkbcsJ/w70wndhTfgerAf3wFPg+9C0R41vukt7fNtvVbSC78Is+Bk8C/4NngP3wzFwD5yq/lerf4X6z4MfwjXqv17971f/B+BH8EX1f13931T/t+Hn8CP4d/gpPAgPw0PQvn86DDPgt7Az/A6eAX+AQ6EnwH0f/An7RdCPPRfGQade9PwY2NylXuK0fuNhBkyAjdR+GK7FZGv4xzV8Mlyh4fd4nPHnA1gH7oVN4UewI/wEZqq9h9qHw32wCH4Kp8L9sAJ+DhepfYnal8Mv4Dr4JXwQfgU3w4PwMGxi6dkrsKHm0wPraD7fU7mxmFKVm+LSf+ZpefJhMiyA7eFELUchHAcnw3xYDC+DUzT+Coyc3wFGavw1YbnGv9DriNwAA/A3MB4uhsnwRpgBl8Bm8LewPVwKu8BlsDe8CQ6Ay+EwuAKeBW+GwXzkHicfV2o+Zmg+rtJ8zNJ8zNZ8XK35mKP5uEbzUaH5mKv5mKf5uFbzMR8G+6Wtmo/OLv3SYfRWE34DO8IjUOuTzFXeD7WJqE/meyqHqaZcVjXlcqspV1FNubXVlNt6HLlhIXI=
*/
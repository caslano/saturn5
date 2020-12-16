// Boost.Geometry Index
//
// R-tree nodes based on Boost.Variant, storing static-size containers
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_STATIC_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_STATIC_HPP

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
06E15FRpG6XhaWkd6LNx7WNSYHOnffjbs9P1Hk+idYr3PPYo/sn6yFdLZaKNDWus7/1Zklaua31PlDOTG+m7w/VyTd3hn+MNsOdrAk88ulrbfOfqu0W+sJL20Fn7Q60j51MNsy/EtZLGC4Ee6OUb/5mOu9HDleirh9S7ecYX8Q6xu477k0T+w0A28ZzvGc6e+hOtbG9r9rRtzjkfzXiykWR5/PHWKL/HszxQlzIQLnLMQd93evr5vvSfJToodNVBMe+/ik2b/3Cxtnnt1xJu1HPYuZ/045+RKt9DiEnV9Z1vn+B54yGzbtqM8+J+zH0eTrJV5+G4M4ZVfW4p6x485hsLma+/ckP4txJnLwq3v7DY2MPewyeOcDK+XL+PmQO7ko+kpRH3Mqa6nPU00e4/GF81bFszD+wl9ss8bvcWek+oYVqZOWt3sRd6qrwjVfn14t/TvAPNFHsXK0Xvb/aKfQ21OsZ1DUXuMp3Xan85QORHeRp7apv5tWU/3xxP0afLo2Azz58pso09GSZe+7j4sPdSJp2+IhtwTac386THuJdcN9xpV76KtzjmLyYm3heTUJAwKKEgJskXy5m35/N/q5hZvp4xFU/7AkygfL6o747/KfFf4txbGT2ss07Bze398WjCfCky8wiDPSRMTdyivVP+QmSuIwz2kDDxuEW8PzbPMw6JzDWO3YRJsiLe85ozNb8R/9mkgT0kjVTc7PepfYdx3zY8+O41Qd6nNuf9aIuENvruNUbevdom+P3DLXodr6zG9036HtT1eh0b5d3i2cF9GPS6Og1TE9NKv11JuslcV0zanEWEbt/6MdUqJ4j793x6nbWQuE6RdT5JpLcGU9uet9eokxhIq/73nMFvvwdPdDxqJDhzwH/Gc59CGbND8jytIK+8IPRLuejvFcyZnDMk/Afxn3v2x2reNc425tls09/Z9mESVzfpI8LS0Otaw5HDfGtlfLBdfblG3jWY59UZbnHkjJevUbS/0HiaWCna35SKfV/8sVhf1DnauSHpF1rL4u30tlthcwyRG4PcRpFbHf9QbGLYPIPwZp6xC7t5zxj2PF/PSV8u/Ux8x9g6le/HXN6T2ME/lXjXqj2oz04yBl6M/4/if1a86bP03Y3zpiuHDqzyHvCdW+VbuKpp6jPoNJXbIXH+JbaVNYezDdJj7bTG4P65uOfGqx71HlP7e20Tt0v+/mbqv4/YT4vs10wbun6N8+72QutM3ELD1GLVxmsel7yGvVt9S/J0r9pFPzpGDZRrOSC6HhxfpY/UvujFVbb/5WY9VZV+UfvSWRLPbLNuyq3e8kJ0eFDydXtsA+s8tOgVHcr3khLP0Hi3+UMarBD/HXF31BhepUymjqO8n0uGCRLeZ9aa1RJ7n/iusW3D3j+bNqnPrH+WtpHvaWaRrriZtiZlXSr1rQmW5+WTaZXjznGNqXPsWn+8h8sw4Xg0Fd63mPayV8K61709jm4bYe/jrePoda/GMEbGJCYGfAlFCYNiujJq9vYlM5TOSgzYo2hiID7Gy38ua7C0f+oi9T3WvGfPFPskNDa2yjiqeVKZ3r7B3hejjpstRKYi6pjXWvyvlvFtfraz6X6MlOmn445vp6oOKkYFdTBZdIBJKEAFHVDBQKOC6OXecYtT7jQt9wti3y3lnhK97Cq3zvcgZY92bTwtMp9VLbvq5lnxz5eyL6Tcs0cFy76iemUfHSy7J6T+qxQ+atnztewZWvZcsff22GUvwrwevfwqG++v43Mpv9btGJF5PWr5LxD/SU7dU/bZo4PlP7Va5Z8/Rss//3dhdZ9J8ftXo+6/X+mUP/js8ajY13mk7rX8/TxRdaDy5f45vuht4CuR2RU=
*/
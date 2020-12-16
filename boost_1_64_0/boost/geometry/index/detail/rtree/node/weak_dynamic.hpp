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
p99krXkHFbJxOfnN5/gYK/q++oSLvq++8c8I/35Ax7Xe4peodr4+EnvghPvIncwe/F3Xmj34w/Yv6FroRNhF9XAq5nl7z6NKPRTmTZ3A4TmTOe1lAvk35deyqywp231INno9gmlkt1tfSkIrepk4r+W6r0QynCZhfebb+ulib4R/nLTzYLsfWI199WqF6yOsnD8UO4JzdR+AUmi/J12r5dRDcMwrjHhdd0r/a+Z8ne9wvi1KMeu1HenQe5QfJb6kyvfiYi+0WEUiOiiV3KDIkHWJ2RJvY1YJxFrN0GFP6mR9EbqydeifOzixRkJCrRgv4/CQmJjEuNYue+xF3e+vEAbulLHRfb8/rYczRKaXWc8TJ/YpUff/qyX+TUyb7W3btc4aaRkKJ1EGud9/ntw30Nxb1snmf7LEXX7c/D8qMn1N/q/QMNHyf01E/u93yX/6ZM3/vO//rfzfcZe0Mff8a343iMz0qPn9413h+f3orqr53W7yu+rfym+WxJ133PyOUJlo+R0Tkd8Kl/zOKA7mt8e/ld8P7zxxfr+48/j5/SaiPTQOyW878hOne3g30bX9NptiRpOn7BDTDBfufXTNv+u5TqbNHpI0kk64PsTux07VfmzVFMejngqkYXpRnqS7TT9G51KlvzXfsKSKXCqpeoJ7iRD2hPtiV65td9u7R/NWPNUR7q5jSScdSzJN3lioPlHy5zqOIGfGkTWUs8NUHUdiUhLauo8jZtwYevevO24cwZ5OI9zqRz+eyxu3bfJIvRWb/jHz0YV/veHwKNq3z3Y/59H1Z3/48wPDDt63clX8/S1v47x7kT+9ScHRqy++rL3vissSZn9e8Dr7Mon7W8s+2TGwoOj2ud9cNf7hZvcGuA/FJHmOHo1fvf60JfP7vlRRltbt42ZyZhLu995+9+Br/b6fBub3uG/qxz3yeFYv7j/seS529Zy5S89852he0UUt9zKmeW33+ff87o1PX8zMnPvi6BlFN/7hAO2jnu1+56Zbn33tpcuPzUp5rE772O/YDPTcGNv9qpRbnnvu8ozzdt0x6U97217UnXzWtd03n37WkR96d3/95s8/ejHfk/8X3hFatvu6N2v3us438sczW9V+6pVWH+2g/lNs9wOLm/yu47apP8w9vO7xeesaP8BcPdV2b/hmfkLxpSOu/SDu+tIWbbPvZH4i+SzdNeX6bw+13vH6TYMadPik5zN8+STyd98ycdQj/i/ff+quVj/fumIhh8J/5rHdMzPvHvPZa/9MH/X2rAajft+Am8bzxf3+cVeNPRCz5O4561P37vzDsm18eyTxeO8qatZiztFeGccykuv+afy7tBfJ/6GB5zSY3mbJ4qfT+y6J2/vTFzynq2O7Zzw7e/EPzcc+tWDG8E3XP/HQTnoQKdcZZ+dnfDL2SIe40gZ7r+l27Bn05pV8PhyzpXW/Jf/odlvs/ePG3Poy47XE/9irm9/85ylnzvpz1rS/vtD1+SXy3TTu5Rk3fDv33FsvvK7dBb9P6hq3jzYt6T7628uXd1j82MSP6v244ds2TbsyVsTa7j82frm9Z2adprdcWLIr5vr+L/DOVNx9zyRPGH95xztuvf/hC35qtpO52h6JJy1xwrC/nntgSruWt9wwe+Z93/INjri/Nuv1HT9/+9sjM3/TuN7mxRfZ349I++n7XZvWY47OXrDhzAvTD9T4zTXcD0t5L31i1rqkN9PuGT5v/yXFx8bezv2iuP85MfXJnK5dn+8faN/r8kZDWLR11JKLUP6uSkIOvaBmma+14fdQyh0X8jsh5HfNkN81Qn4nhvyupb+H2foL+f3PlMrfX4b8rh0icyDE/Ufz2/lGrJTfm+yspzo=
*/
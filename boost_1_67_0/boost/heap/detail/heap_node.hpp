// boost heap: heap node helper classes
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_DETAIL_HEAP_NODE_HPP
#define BOOST_HEAP_DETAIL_HEAP_NODE_HPP

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/type_traits/conditional.hpp>

#ifdef BOOST_HEAP_SANITYCHECKS
#define BOOST_HEAP_ASSERT BOOST_ASSERT
#else
#define BOOST_HEAP_ASSERT(expression)
#endif


namespace boost  {
namespace heap   {
namespace detail {

namespace bi = boost::intrusive;

template <bool auto_unlink = false>
struct heap_node_base:
    bi::list_base_hook<typename boost::conditional<auto_unlink,
                                          bi::link_mode<bi::auto_unlink>,
                                          bi::link_mode<bi::safe_link>
                                         >::type
                      >
{};

typedef bi::list<heap_node_base<false> > heap_node_list;

struct nop_disposer
{
    template <typename T>
    void operator()(T * n)
    {
        BOOST_HEAP_ASSERT(false);
    }
};

template <typename Node, typename HeapBase>
bool is_heap(const Node * n, typename HeapBase::value_compare const & cmp)
{
    for (typename Node::const_child_iterator it = n->children.begin(); it != n->children.end(); ++it) {
        Node const & this_node = static_cast<Node const &>(*it);
        const Node * child = static_cast<const Node*>(&this_node);

        if (cmp(HeapBase::get_value(n->value), HeapBase::get_value(child->value)) ||
            !is_heap<Node, HeapBase>(child, cmp))
            return false;
    }
    return true;
}

template <typename Node>
std::size_t count_nodes(const Node * n);

template <typename Node, typename List>
std::size_t count_list_nodes(List const & node_list)
{
    std::size_t ret = 0;

    for (typename List::const_iterator it = node_list.begin(); it != node_list.end(); ++it) {
        const Node * child = static_cast<const Node*>(&*it);
        ret += count_nodes<Node>(child);
    }
    return ret;
}

template <typename Node>
std::size_t count_nodes(const Node * n)
{
    return 1 + count_list_nodes<Node, typename Node::child_list>(n->children);
}


/* node cloner
 *
 * Requires `Clone Constructor':
 * template <typename Alloc>
 * Node::Node(Node const &, Alloc &)
 *
 * template <typename Alloc>
 * Node::Node(Node const &, Alloc &, Node * parent)
 *
 * */
template <typename Node,
          typename NodeBase,
          typename Alloc>
struct node_cloner
{
#ifndef BOOST_NO_CXX11_ALLOCATOR
    typedef std::allocator_traits<Alloc> allocator_traits;
#endif

    node_cloner(Alloc & allocator):
        allocator(allocator)
    {}

    Node * operator() (NodeBase const & node)
    {
#ifdef BOOST_NO_CXX11_ALLOCATOR
        Node * ret = allocator.allocate(1);
        new (ret) Node(static_cast<Node const &>(node), allocator);
#else
        Node * ret = allocator_traits::allocate(allocator, 1);
        allocator_traits::construct(allocator, ret, static_cast<Node const &>(node), allocator);
#endif
        return ret;
    }

    Node * operator() (NodeBase const & node, Node * parent)
    {
#ifdef BOOST_NO_CXX11_ALLOCATOR
        Node * ret = allocator.allocate(1);
        new (ret) Node(static_cast<Node const &>(node), allocator, parent);
#else
        Node * ret = allocator_traits::allocate(allocator, 1);
        allocator_traits::construct(allocator, ret, static_cast<Node const &>(node), allocator, parent);
#endif
        return ret;
    }

private:
    Alloc & allocator;
};

/* node disposer
 *
 * Requirements:
 * Node::clear_subtree(Alloc &) clears the subtree via allocator
 *
 * */
template <typename Node,
          typename NodeBase,
          typename Alloc>
struct node_disposer
{
#ifdef BOOST_NO_CXX11_ALLOCATOR
    typedef typename Alloc::pointer node_pointer;
#else
    typedef std::allocator_traits<Alloc> allocator_traits;
    typedef typename allocator_traits::pointer node_pointer;
#endif

    node_disposer(Alloc & alloc):
        alloc_(alloc)
    {}

    void operator()(NodeBase * base)
    {
        node_pointer n = static_cast<node_pointer>(base);
        n->clear_subtree(alloc_);
#ifdef BOOST_NO_CXX11_ALLOCATOR
        alloc_.destroy(n);
        alloc_.deallocate(n, 1);
#else
        allocator_traits::destroy(alloc_, n);
        allocator_traits::deallocate(alloc_, n, 1);
#endif
    }

    Alloc & alloc_;
};


template <typename ValueType,
          bool constant_time_child_size = true
         >
struct heap_node:
    heap_node_base<!constant_time_child_size>
{
    typedef heap_node_base<!constant_time_child_size> node_base;

public:
    typedef ValueType value_type;

    typedef bi::list<node_base,
                     bi::constant_time_size<constant_time_child_size> > child_list;

    typedef typename child_list::iterator child_iterator;
    typedef typename child_list::const_iterator const_child_iterator;
    typedef typename child_list::size_type size_type;

    heap_node(ValueType const & v):
        value(v)
    {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <class... Args>
    heap_node(Args&&... args):
        value(std::forward<Args>(args)...)
    {}
#endif

/* protected:                      */
    heap_node(heap_node const & rhs):
        value(rhs.value)
    {
        /* we don't copy the child list, but clone it later */
    }

public:

    template <typename Alloc>
    heap_node (heap_node const & rhs, Alloc & allocator):
        value(rhs.value)
    {
        children.clone_from(rhs.children, node_cloner<heap_node, node_base, Alloc>(allocator), nop_disposer());
    }

    size_type child_count(void) const
    {
        BOOST_STATIC_ASSERT(constant_time_child_size);
        return children.size();
    }

    void add_child(heap_node * n)
    {
        children.push_back(*n);
    }

    template <typename Alloc>
    void clear_subtree(Alloc & alloc)
    {
        children.clear_and_dispose(node_disposer<heap_node, node_base, Alloc>(alloc));
    }

    void swap_children(heap_node * rhs)
    {
        children.swap(rhs->children);
    }

    ValueType value;
    child_list children;
};

template <typename value_type>
struct parent_pointing_heap_node:
    heap_node<value_type>
{
    typedef heap_node<value_type> super_t;

    parent_pointing_heap_node(value_type const & v):
        super_t(v), parent(NULL)
    {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <class... Args>
    parent_pointing_heap_node(Args&&... args):
        super_t(std::forward<Args>(args)...), parent(NULL)
    {}
#endif

    template <typename Alloc>
    struct node_cloner
    {
        node_cloner(Alloc & allocator, parent_pointing_heap_node * parent):
            allocator(allocator), parent_(parent)
        {}

        parent_pointing_heap_node * operator() (typename super_t::node_base const & node)
        {
            parent_pointing_heap_node * ret = allocator.allocate(1);
            new (ret) parent_pointing_heap_node(static_cast<parent_pointing_heap_node const &>(node), allocator, parent_);
            return ret;
        }

    private:
        Alloc & allocator;
        parent_pointing_heap_node * parent_;
    };

    template <typename Alloc>
    parent_pointing_heap_node (parent_pointing_heap_node const & rhs, Alloc & allocator, parent_pointing_heap_node * parent):
        super_t(static_cast<super_t const &>(rhs)), parent(parent)
    {
        super_t::children.clone_from(rhs.children, node_cloner<Alloc>(allocator, this), nop_disposer());
    }

    void update_children(void)
    {
        typedef heap_node_list::iterator node_list_iterator;
        for (node_list_iterator it = super_t::children.begin(); it != super_t::children.end(); ++it) {
            parent_pointing_heap_node * child = static_cast<parent_pointing_heap_node*>(&*it);
            child->parent = this;
        }
    }

    void remove_from_parent(void)
    {
        BOOST_HEAP_ASSERT(parent);
        parent->children.erase(heap_node_list::s_iterator_to(*this));
        parent = NULL;
    }

    void add_child(parent_pointing_heap_node * n)
    {
        BOOST_HEAP_ASSERT(n->parent == NULL);
        n->parent = this;
        super_t::add_child(n);
    }

    parent_pointing_heap_node * get_parent(void)
    {
        return parent;
    }

    const parent_pointing_heap_node * get_parent(void) const
    {
        return parent;
    }

    parent_pointing_heap_node * parent;
};


template <typename value_type>
struct marked_heap_node:
    parent_pointing_heap_node<value_type>
{
    typedef parent_pointing_heap_node<value_type> super_t;

    marked_heap_node(value_type const & v):
        super_t(v), mark(false)
    {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <class... Args>
    marked_heap_node(Args&&... args):
        super_t(std::forward<Args>(args)...), mark(false)
    {}
#endif

    marked_heap_node * get_parent(void)
    {
        return static_cast<marked_heap_node*>(super_t::parent);
    }

    const marked_heap_node * get_parent(void) const
    {
        return static_cast<marked_heap_node*>(super_t::parent);
    }

    bool mark;
};


template <typename Node>
struct cmp_by_degree
{
    template <typename NodeBase>
    bool operator()(NodeBase const & left,
                    NodeBase const & right)
    {
        return static_cast<const Node*>(&left)->child_count() < static_cast<const Node*>(&right)->child_count();
    }
};

template <typename List, typename Node, typename Cmp>
Node * find_max_child(List const & list, Cmp const & cmp)
{
    BOOST_HEAP_ASSERT(!list.empty());

    const Node * ret = static_cast<const Node *> (&list.front());
    for (typename List::const_iterator it = list.begin(); it != list.end(); ++it) {
        const Node * current = static_cast<const Node *> (&*it);

        if (cmp(ret->value, current->value))
            ret = current;
    }

    return const_cast<Node*>(ret);
}

} /* namespace detail */
} /* namespace heap */
} /* namespace boost */

#undef BOOST_HEAP_ASSERT
#endif /* BOOST_HEAP_DETAIL_HEAP_NODE_HPP */

/* heap_node.hpp
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
*/
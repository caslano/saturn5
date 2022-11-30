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
#include <boost/core/allocator_access.hpp>
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

template<class Node>
void destroy_node(Node& node)
{
    node.~Node();
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
    node_cloner(Alloc & allocator):
        allocator(allocator)
    {}

    Node * operator() (NodeBase const & node)
    {
        Node * ret = allocator.allocate(1);
        new (ret) Node(static_cast<Node const &>(node), allocator);
        return ret;
    }

    Node * operator() (NodeBase const & node, Node * parent)
    {
        Node * ret = allocator.allocate(1);
        new (ret) Node(static_cast<Node const &>(node), allocator, parent);
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
    typedef typename boost::allocator_pointer<Alloc>::type node_pointer;

    node_disposer(Alloc & alloc):
        alloc_(alloc)
    {}

    void operator()(NodeBase * base)
    {
        node_pointer n = static_cast<node_pointer>(base);
        n->clear_subtree(alloc_);
        boost::heap::detail::destroy_node(*n);
        alloc_.deallocate(n, 1);
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
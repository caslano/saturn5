// boost heap: skew heap
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_SKEW_HEAP_HPP
#define BOOST_HEAP_SKEW_HEAP_HPP

#include <algorithm>
#include <utility>
#include <vector>

#include <boost/assert.hpp>
#include <boost/array.hpp>

#include <boost/heap/detail/heap_comparison.hpp>
#include <boost/heap/detail/heap_node.hpp>
#include <boost/heap/detail/stable_heap.hpp>
#include <boost/heap/detail/tree_iterator.hpp>
#include <boost/type_traits/integral_constant.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_DOXYGEN_INVOKED
#ifdef BOOST_HEAP_SANITYCHECKS
#define BOOST_HEAP_ASSERT BOOST_ASSERT
#else
#define BOOST_HEAP_ASSERT(expression)
#endif
#endif

namespace boost  {
namespace heap   {
namespace detail {

template <typename node_pointer, bool store_parent_pointer>
struct parent_holder
{
    parent_holder(void):
        parent_(NULL)
    {}

    void set_parent(node_pointer parent)
    {
        BOOST_HEAP_ASSERT(static_cast<node_pointer>(this) != parent);
        parent_ = parent;
    }

    node_pointer get_parent(void) const
    {
        return parent_;
    }

    node_pointer parent_;
};

template <typename node_pointer>
struct parent_holder<node_pointer, false>
{
    void set_parent(node_pointer parent)
    {}

    node_pointer get_parent(void) const
    {
        return NULL;
    }
};


template <typename value_type, bool store_parent_pointer>
struct skew_heap_node:
    parent_holder<skew_heap_node<value_type, store_parent_pointer>*, store_parent_pointer>
{
    typedef parent_holder<skew_heap_node<value_type, store_parent_pointer>*, store_parent_pointer> super_t;

    typedef boost::array<skew_heap_node*, 2> child_list_type;
    typedef typename child_list_type::iterator child_iterator;
    typedef typename child_list_type::const_iterator const_child_iterator;

    skew_heap_node(value_type const & v):
        value(v)
    {
        children.assign(0);
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    skew_heap_node(value_type && v):
        value(v)
    {
        children.assign(0);
    }
#endif

    template <typename Alloc>
    skew_heap_node (skew_heap_node const & rhs, Alloc & allocator, skew_heap_node * parent):
        value(rhs.value)
    {
        super_t::set_parent(parent);
        node_cloner<skew_heap_node, skew_heap_node, Alloc> cloner(allocator);
        clone_child(0, rhs, cloner);
        clone_child(1, rhs, cloner);
    }

    template <typename Cloner>
    void clone_child(int index, skew_heap_node const & rhs, Cloner & cloner)
    {
        if (rhs.children[index])
            children[index] = cloner(*rhs.children[index], this);
        else
            children[index] = NULL;
    }

    template <typename Alloc>
    void clear_subtree(Alloc & alloc)
    {
        node_disposer<skew_heap_node, skew_heap_node, Alloc> disposer(alloc);
        dispose_child(children[0], disposer);
        dispose_child(children[1], disposer);
    }

    template <typename Disposer>
    void dispose_child(skew_heap_node * node, Disposer & disposer)
    {
        if (node)
            disposer(node);
    }

    std::size_t count_children(void) const
    {
        size_t ret = 1;
        if (children[0])
            ret += children[0]->count_children();
        if (children[1])
            ret += children[1]->count_children();

        return ret;
    }

    template <typename HeapBase>
    bool is_heap(typename HeapBase::value_compare const & cmp) const
    {
        for (const_child_iterator it = children.begin(); it != children.end(); ++it) {
            const skew_heap_node * child = *it;

            if (child == NULL)
                continue;

            if (store_parent_pointer)
                BOOST_HEAP_ASSERT(child->get_parent() == this);

            if (cmp(HeapBase::get_value(value), HeapBase::get_value(child->value)) ||
                !child->is_heap<HeapBase>(cmp))
                return false;
        }
        return true;
    }

    value_type value;
    boost::array<skew_heap_node*, 2> children;
};


typedef parameter::parameters<boost::parameter::optional<tag::allocator>,
                              boost::parameter::optional<tag::compare>,
                              boost::parameter::optional<tag::stable>,
                              boost::parameter::optional<tag::store_parent_pointer>,
                              boost::parameter::optional<tag::stability_counter_type>,
                              boost::parameter::optional<tag::constant_time_size>,
                              boost::parameter::optional<tag::mutable_>
                             > skew_heap_signature;

template <typename T, typename BoundArgs>
struct make_skew_heap_base
{
    static const bool constant_time_size = parameter::binding<BoundArgs,
                                                              tag::constant_time_size,
                                                              boost::true_type
                                                             >::type::value;

    typedef typename make_heap_base<T, BoundArgs, constant_time_size>::type base_type;
    typedef typename make_heap_base<T, BoundArgs, constant_time_size>::allocator_argument allocator_argument;
    typedef typename make_heap_base<T, BoundArgs, constant_time_size>::compare_argument compare_argument;

    static const bool is_mutable = extract_mutable<BoundArgs>::value;
    static const bool store_parent_pointer = parameter::binding<BoundArgs,
                                                              tag::store_parent_pointer,
                                                              boost::false_type>::type::value || is_mutable;

    typedef skew_heap_node<typename base_type::internal_type, store_parent_pointer> node_type;

    typedef typename boost::allocator_rebind<allocator_argument, node_type>::type allocator_type;

    struct type:
        base_type,
        allocator_type
    {
        type(compare_argument const & arg):
            base_type(arg)
        {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        type(type && rhs):
            base_type(std::move(static_cast<base_type&>(rhs))),
            allocator_type(std::move(static_cast<allocator_type&>(rhs)))
        {}

        type(type const & rhs):
            base_type(rhs),
            allocator_type(rhs)
        {}

        type & operator=(type && rhs)
        {
            base_type::operator=(std::move(static_cast<base_type&>(rhs)));
            allocator_type::operator=(std::move(static_cast<allocator_type&>(rhs)));
            return *this;
        }

        type & operator=(type const & rhs)
        {
            base_type::operator=(static_cast<base_type const &>(rhs));
            allocator_type::operator=(static_cast<allocator_type const &>(rhs));
            return *this;
        }
#endif
    };
};

} /* namespace detail */

/**
 * \class skew_heap
 * \brief skew heap
 *
 *
 * The template parameter T is the type to be managed by the container.
 * The user can specify additional options and if no options are provided default options are used.
 *
 * The container supports the following options:
 * - \c boost::heap::compare<>, defaults to \c compare<std::less<T> >
 * - \c boost::heap::stable<>, defaults to \c stable<false>
 * - \c boost::heap::stability_counter_type<>, defaults to \c stability_counter_type<boost::uintmax_t>
 * - \c boost::heap::allocator<>, defaults to \c allocator<std::allocator<T> >
 * - \c boost::heap::constant_time_size<>, defaults to \c constant_time_size<true>
 * - \c boost::heap::store_parent_pointer<>, defaults to \c store_parent_pointer<true>. Maintaining a parent pointer adds some
 *   maintenance and size overhead, but iterating a heap is more efficient.
 * - \c boost::heap::mutable<>, defaults to \c mutable<false>.
 *
 */
#ifdef BOOST_DOXYGEN_INVOKED
template<class T, class ...Options>
#else
template <typename T,
          class A0 = boost::parameter::void_,
          class A1 = boost::parameter::void_,
          class A2 = boost::parameter::void_,
          class A3 = boost::parameter::void_,
          class A4 = boost::parameter::void_,
          class A5 = boost::parameter::void_,
          class A6 = boost::parameter::void_
         >
#endif
class skew_heap:
    private detail::make_skew_heap_base<T,
                                          typename detail::skew_heap_signature::bind<A0, A1, A2, A3, A4, A5, A6>::type
                                         >::type
{
    typedef typename detail::skew_heap_signature::bind<A0, A1, A2, A3, A4, A5, A6>::type bound_args;
    typedef detail::make_skew_heap_base<T, bound_args> base_maker;
    typedef typename base_maker::type super_t;

    typedef typename super_t::internal_type internal_type;
    typedef typename super_t::size_holder_type size_holder;
    typedef typename base_maker::allocator_argument allocator_argument;

    static const bool store_parent_pointer = base_maker::store_parent_pointer;
    template <typename Heap1, typename Heap2>
    friend struct heap_merge_emulate;

    struct implementation_defined:
        detail::extract_allocator_types<typename base_maker::allocator_argument>
    {
        typedef T value_type;

        typedef typename base_maker::compare_argument value_compare;
        typedef typename base_maker::allocator_type allocator_type;

        typedef typename base_maker::node_type node;
        typedef typename boost::allocator_pointer<allocator_type>::type node_pointer;
        typedef typename boost::allocator_const_pointer<allocator_type>::type const_node_pointer;

        typedef detail::value_extractor<value_type, internal_type, super_t> value_extractor;

        typedef boost::array<node_pointer, 2> child_list_type;
        typedef typename child_list_type::iterator child_list_iterator;

        typedef typename boost::conditional<false,
                                        detail::recursive_tree_iterator<node,
                                                                        child_list_iterator,
                                                                        const value_type,
                                                                        value_extractor,
                                                                        detail::list_iterator_converter<node,
                                                                                                        child_list_type
                                                                                                       >
                                                                       >,
                                        detail::tree_iterator<node,
                                                              const value_type,
                                                              allocator_type,
                                                              value_extractor,
                                                              detail::dereferencer<node>,
                                                              true,
                                                              false,
                                                              value_compare
                                                    >
                                        >::type iterator;

        typedef iterator const_iterator;

        typedef detail::tree_iterator<node,
                                      const value_type,
                                      allocator_type,
                                      value_extractor,
                                      detail::dereferencer<node>,
                                      true,
                                      true,
                                      value_compare
                                     > ordered_iterator;

        typedef typename detail::extract_allocator_types<typename base_maker::allocator_argument>::reference reference;
        typedef detail::node_handle<node_pointer, super_t, reference> handle_type;
    };

    typedef typename implementation_defined::value_extractor value_extractor;
    typedef typename implementation_defined::node node;
    typedef typename implementation_defined::node_pointer node_pointer;

public:
    typedef T value_type;

    typedef typename implementation_defined::size_type size_type;
    typedef typename implementation_defined::difference_type difference_type;
    typedef typename implementation_defined::value_compare value_compare;
    typedef typename implementation_defined::allocator_type allocator_type;
    typedef typename implementation_defined::reference reference;
    typedef typename implementation_defined::const_reference const_reference;
    typedef typename implementation_defined::pointer pointer;
    typedef typename implementation_defined::const_pointer const_pointer;

    /// \copydoc boost::heap::priority_queue::iterator
    typedef typename implementation_defined::iterator iterator;
    typedef typename implementation_defined::const_iterator const_iterator;
    typedef typename implementation_defined::ordered_iterator ordered_iterator;

    static const bool constant_time_size = super_t::constant_time_size;
    static const bool has_ordered_iterators = true;
    static const bool is_mergable = true;
    static const bool is_stable = detail::extract_stable<bound_args>::value;
    static const bool has_reserve = false;
    static const bool is_mutable = detail::extract_mutable<bound_args>::value;

    typedef typename boost::conditional<is_mutable, typename implementation_defined::handle_type, void*>::type handle_type;

    /// \copydoc boost::heap::priority_queue::priority_queue(value_compare const &)
    explicit skew_heap(value_compare const & cmp = value_compare()):
        super_t(cmp), root(NULL)
    {}

    /// \copydoc boost::heap::priority_queue::priority_queue(priority_queue const &)
    skew_heap(skew_heap const & rhs):
        super_t(rhs), root(0)
    {
        if (rhs.empty())
            return;

        clone_tree(rhs);
        size_holder::set_size(rhs.get_size());
    }

    /// \copydoc boost::heap::priority_queue::operator=(priority_queue const & rhs)
    skew_heap & operator=(skew_heap const & rhs)
    {
        clear();
        size_holder::set_size(rhs.get_size());
        static_cast<super_t&>(*this) = rhs;

        clone_tree(rhs);
        return *this;
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    /// \copydoc boost::heap::priority_queue::priority_queue(priority_queue &&)
    skew_heap(skew_heap && rhs):
        super_t(std::move(rhs)), root(rhs.root)
    {
        rhs.root = NULL;
    }

    /// \copydoc boost::heap::priority_queue::operator=(priority_queue &&)
    skew_heap & operator=(skew_heap && rhs)
    {
        super_t::operator=(std::move(rhs));
        root = rhs.root;
        rhs.root = NULL;
        return *this;
    }
#endif

    ~skew_heap(void)
    {
        clear();
    }

    /**
     * \b Effects: Adds a new element to the priority queue.
     *
     * \b Complexity: Logarithmic (amortized).
     *
     * */
    typename boost::conditional<is_mutable, handle_type, void>::type push(value_type const & v)
    {
        typedef typename boost::conditional<is_mutable, push_handle, push_void>::type push_helper;
        return push_helper::push(this, v);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    /**
     * \b Effects: Adds a new element to the priority queue. The element is directly constructed in-place.
     *
     * \b Complexity: Logarithmic (amortized).
     *
     * */
    template <typename... Args>
    typename boost::conditional<is_mutable, handle_type, void>::type emplace(Args&&... args)
    {
        typedef typename boost::conditional<is_mutable, push_handle, push_void>::type push_helper;
        return push_helper::emplace(this, std::forward<Args>(args)...);
    }
#endif

    /// \copydoc boost::heap::priority_queue::empty
    bool empty(void) const
    {
        return root == NULL;
    }

    /// \copydoc boost::heap::binomial_heap::size
    size_type size(void) const
    {
        if (constant_time_size)
            return size_holder::get_size();

        if (root == NULL)
            return 0;
        else
            return root->count_children();
    }

    /// \copydoc boost::heap::priority_queue::max_size
    size_type max_size(void) const
    {
        const allocator_type& alloc = *this;
        return boost::allocator_max_size(alloc);
    }

    /// \copydoc boost::heap::priority_queue::clear
    void clear(void)
    {
        if (empty())
            return;

        root->template clear_subtree<allocator_type>(*this);
        root->~node();
        allocator_type& alloc = *this;
        alloc.deallocate(root, 1);
        root = NULL;
        size_holder::set_size(0);
    }

    /// \copydoc boost::heap::priority_queue::get_allocator
    allocator_type get_allocator(void) const
    {
        return *this;
    }

    /// \copydoc boost::heap::priority_queue::swap
    void swap(skew_heap & rhs)
    {
        super_t::swap(rhs);
        std::swap(root, rhs.root);
    }

    /// \copydoc boost::heap::priority_queue::top
    const_reference top(void) const
    {
        BOOST_ASSERT(!empty());

        return super_t::get_value(root->value);
    }

    /**
     * \b Effects: Removes the top element from the priority queue.
     *
     * \b Complexity: Logarithmic (amortized).
     *
     * */
    void pop(void)
    {
        BOOST_ASSERT(!empty());

        node_pointer top = root;

        root = merge_children(root);
        size_holder::decrement();

        if (root)
            BOOST_HEAP_ASSERT(root->get_parent() == NULL);
        else
            BOOST_HEAP_ASSERT(size_holder::get_size() == 0);

        top->~node();
        allocator_type& alloc = *this;
        alloc.deallocate(top, 1);
        sanity_check();
    }

    /// \copydoc boost::heap::priority_queue::begin
    iterator begin(void) const
    {
        return iterator(root, super_t::value_comp());
    }

    /// \copydoc boost::heap::priority_queue::end
    iterator end(void) const
    {
        return iterator();
    }

    /// \copydoc boost::heap::fibonacci_heap::ordered_begin
    ordered_iterator ordered_begin(void) const
    {
        return ordered_iterator(root, super_t::value_comp());
    }

    /// \copydoc boost::heap::fibonacci_heap::ordered_begin
    ordered_iterator ordered_end(void) const
    {
        return ordered_iterator(0, super_t::value_comp());
    }

    /**
     * \b Effects: Merge all elements from rhs into this
     *
     * \b Complexity: Logarithmic (amortized).
     *
     * */
    void merge(skew_heap & rhs)
    {
        if (rhs.empty())
            return;

        merge_node(rhs.root);

        size_holder::add(rhs.get_size());
        rhs.set_size(0);
        rhs.root = NULL;
        sanity_check();

        super_t::set_stability_count((std::max)(super_t::get_stability_count(),
                                     rhs.get_stability_count()));
        rhs.set_stability_count(0);
    }

    /// \copydoc boost::heap::priority_queue::value_comp
    value_compare const & value_comp(void) const
    {
        return super_t::value_comp();
    }

    /// \copydoc boost::heap::priority_queue::operator<(HeapType const & rhs) const
    template <typename HeapType>
    bool operator<(HeapType const & rhs) const
    {
        return detail::heap_compare(*this, rhs);
    }

    /// \copydoc boost::heap::priority_queue::operator>(HeapType const & rhs) const
    template <typename HeapType>
    bool operator>(HeapType const & rhs) const
    {
        return detail::heap_compare(rhs, *this);
    }

    /// \copydoc boost::heap::priority_queue::operator>=(HeapType const & rhs) const
    template <typename HeapType>
    bool operator>=(HeapType const & rhs) const
    {
        return !operator<(rhs);
    }

    /// \copydoc boost::heap::priority_queue::operator<=(HeapType const & rhs) const
    template <typename HeapType>
    bool operator<=(HeapType const & rhs) const
    {
        return !operator>(rhs);
    }

    /// \copydoc boost::heap::priority_queue::operator==(HeapType const & rhs) const
    template <typename HeapType>
    bool operator==(HeapType const & rhs) const
    {
        return detail::heap_equality(*this, rhs);
    }

    /// \copydoc boost::heap::priority_queue::operator!=(HeapType const & rhs) const
    template <typename HeapType>
    bool operator!=(HeapType const & rhs) const
    {
        return !(*this == rhs);
    }


    /// \copydoc boost::heap::d_ary_heap::s_handle_from_iterator
    static handle_type s_handle_from_iterator(iterator const & it)
    {
        node * ptr = const_cast<node *>(it.get_node());
        return handle_type(ptr);
    }

    /**
     * \b Effects: Removes the element handled by \c handle from the priority_queue.
     *
     * \b Complexity: Logarithmic (amortized).
     * */
    void erase (handle_type object)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        node_pointer this_node = object.node_;

        unlink_node(this_node);
        size_holder::decrement();

        sanity_check();
        this_node->~node();
        allocator_type& alloc = *this;
        alloc.deallocate(this_node, 1);
    }

    /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic (amortized).
     *
     * */
    void update (handle_type handle, const_reference v)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        if (super_t::operator()(super_t::get_value(handle.node_->value), v))
            increase(handle, v);
        else
            decrease(handle, v);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic (amortized).
     *
     * \b Note: If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void update (handle_type handle)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        node_pointer this_node = handle.node_;

        if (this_node->get_parent()) {
            if (super_t::operator()(super_t::get_value(this_node->get_parent()->value),
                                    super_t::get_value(this_node->value)))
                increase(handle);
            else
                decrease(handle);
        }
        else
            decrease(handle);
    }

    /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic (amortized).
     *
     * \b Note: The new value is expected to be greater than the current one
     * */
    void increase (handle_type handle, const_reference v)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        handle.node_->value = super_t::make_node(v);
        increase(handle);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic (amortized).
     *
     * \b Note: If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void increase (handle_type handle)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        node_pointer this_node = handle.node_;

        if (this_node == root)
            return;

        node_pointer parent = this_node->get_parent();

        if (this_node == parent->children[0])
            parent->children[0] = NULL;
        else
            parent->children[1] = NULL;

        this_node->set_parent(NULL);
        merge_node(this_node);
    }

    /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic (amortized).
     *
     * \b Note: The new value is expected to be less than the current one
     * */
    void decrease (handle_type handle, const_reference v)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        handle.node_->value = super_t::make_node(v);
        decrease(handle);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic (amortized).
     *
     * \b Note: The new value is expected to be less than the current one. If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void decrease (handle_type handle)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        node_pointer this_node = handle.node_;

        unlink_node(this_node);
        this_node->children.assign(0);
        this_node->set_parent(NULL);
        merge_node(this_node);
    }

private:
#if !defined(BOOST_DOXYGEN_INVOKED)
    struct push_void
    {
        static void push(skew_heap * self, const_reference v)
        {
            self->push_internal(v);
        }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
        template <class... Args>
        static void emplace(skew_heap * self, Args&&... args)
        {
            self->emplace_internal(std::forward<Args>(args)...);
        }
#endif
    };

    struct push_handle
    {
        static handle_type push(skew_heap * self, const_reference v)
        {
            return handle_type(self->push_internal(v));
        }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
        template <class... Args>
        static handle_type emplace(skew_heap * self, Args&&... args)
        {
            return handle_type(self->emplace_internal(std::forward<Args>(args)...));
        }
#endif
    };

    node_pointer push_internal(const_reference v)
    {
        size_holder::increment();

        allocator_type& alloc = *this;
        node_pointer n = alloc.allocate(1);
        new(n) node(super_t::make_node(v));
        merge_node(n);
        return n;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <class... Args>
    node_pointer emplace_internal(Args&&... args)
    {
        size_holder::increment();

        allocator_type& alloc = *this;
        node_pointer n = alloc.allocate(1);
        new(n) node(super_t::make_node(std::forward<Args>(args)...));
        merge_node(n);
        return n;
    }
#endif

    void unlink_node(node_pointer node)
    {
        node_pointer parent = node->get_parent();
        node_pointer merged_children = merge_children(node);

        if (parent) {
            if (node == parent->children[0])
                parent->children[0] = merged_children;
            else
                parent->children[1] = merged_children;
        }
        else
            root = merged_children;
    }

    void clone_tree(skew_heap const & rhs)
    {
        BOOST_HEAP_ASSERT(root == NULL);
        if (rhs.empty())
            return;

        allocator_type& alloc = *this;
        root = alloc.allocate(1);
        new(root) node(*rhs.root, alloc, NULL);
    }

    void merge_node(node_pointer other)
    {
        BOOST_HEAP_ASSERT(other);
        if (root != NULL)
            root = merge_nodes(root, other, NULL);
        else
            root = other;
    }

    node_pointer merge_nodes(node_pointer node1, node_pointer node2, node_pointer new_parent)
    {
        if (node1 == NULL) {
            if (node2)
                node2->set_parent(new_parent);
            return node2;
        }
        if (node2 == NULL) {
            node1->set_parent(new_parent);
            return node1;
        }

        node_pointer merged = merge_nodes_recursive(node1, node2, new_parent);
        return merged;
    }

    node_pointer merge_children(node_pointer node)
    {
        node_pointer parent = node->get_parent();
        node_pointer merged_children = merge_nodes(node->children[0], node->children[1], parent);

        return merged_children;
    }

    node_pointer merge_nodes_recursive(node_pointer node1, node_pointer node2, node_pointer new_parent)
    {
        if (super_t::operator()(node1->value, node2->value))
            std::swap(node1, node2);

        node * parent = node1;
        node * child = node2;

        if (parent->children[1]) {
            node * merged = merge_nodes(parent->children[1], child, parent);
            parent->children[1] = merged;
            merged->set_parent(parent);
        } else {
            parent->children[1] = child;
            child->set_parent(parent);
        }


        std::swap(parent->children[0], parent->children[1]);
        parent->set_parent(new_parent);
        return parent;
    }

    void sanity_check(void)
    {
#ifdef BOOST_HEAP_SANITYCHECKS
        if (root)
            BOOST_HEAP_ASSERT( root->template is_heap<super_t>(super_t::value_comp()) );

        if (constant_time_size) {
            size_type stored_size = size_holder::get_size();

            size_type counted_size;
            if (root == NULL)
                counted_size = 0;
            else
                counted_size = root->count_children();

            BOOST_HEAP_ASSERT(counted_size == stored_size);
        }
#endif
    }

    node_pointer root;
#endif
};

} /* namespace heap */
} /* namespace boost */

#undef BOOST_HEAP_ASSERT
#endif /* BOOST_HEAP_SKEW_HEAP_HPP */

/* skew_heap.hpp
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
*/
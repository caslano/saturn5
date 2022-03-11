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

#ifdef BOOST_NO_CXX11_ALLOCATOR
    typedef typename allocator_argument::template rebind<node_type>::other allocator_type;
#else
    typedef typename std::allocator_traits<allocator_argument>::template rebind_alloc<node_type> allocator_type;
#endif

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
#ifdef BOOST_NO_CXX11_ALLOCATOR
        typedef typename allocator_type::pointer node_pointer;
        typedef typename allocator_type::const_pointer const_node_pointer;
#else
        typedef std::allocator_traits<allocator_type> allocator_traits;
        typedef typename allocator_traits::pointer node_pointer;
        typedef typename allocator_traits::const_pointer const_node_pointer;
#endif

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
#ifndef BOOST_NO_CXX11_ALLOCATOR
    typedef typename implementation_defined::allocator_traits allocator_traits;
#endif
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
#ifdef BOOST_NO_CXX11_ALLOCATOR
        return allocator_type::max_size();
#else
        const allocator_type& alloc = *this;
        return allocator_traits::max_size(alloc);
#endif
    }

    /// \copydoc boost::heap::priority_queue::clear
    void clear(void)
    {
        if (empty())
            return;

        root->template clear_subtree<allocator_type>(*this);
#ifdef BOOST_NO_CXX11_ALLOCATOR
        root->~node();
        allocator_type::deallocate(root, 1);
#else
        allocator_type& alloc = *this;
        allocator_traits::destroy(alloc, root);
        allocator_traits::deallocate(alloc, root, 1);
#endif
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
#ifdef BOOST_NO_CXX11_ALLOCATOR
        top->~node();
        allocator_type::deallocate(top, 1);
#else
        allocator_type& alloc = *this;
        allocator_traits::destroy(alloc, top);
        allocator_traits::deallocate(alloc, top, 1);
#endif
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
#ifdef BOOST_NO_CXX11_ALLOCATOR
        this_node->~node();
        allocator_type::deallocate(this_node, 1);
#else
        allocator_type& alloc = *this;
        allocator_traits::destroy(alloc, this_node);
        allocator_traits::deallocate(alloc, this_node, 1);
#endif
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

#ifdef BOOST_NO_CXX11_ALLOCATOR
        node_pointer n = allocator_type::allocate(1);
        new(n) node(super_t::make_node(v));
#else
        allocator_type& alloc = *this;
        node_pointer n = allocator_traits::allocate(alloc, 1);
        allocator_traits::construct(alloc, n, super_t::make_node(v));
#endif
        merge_node(n);
        return n;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <class... Args>
    node_pointer emplace_internal(Args&&... args)
    {
        size_holder::increment();

#ifdef BOOST_NO_CXX11_ALLOCATOR
        node_pointer n = allocator_type::allocate(1);
        new(n) node(super_t::make_node(std::forward<Args>(args)...));
#else
        allocator_type& alloc = *this;
        node_pointer n = allocator_traits::allocate(alloc, 1);
        allocator_traits::construct(alloc, n, super_t::make_node(std::forward<Args>(args)...));
#endif
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
#ifdef BOOST_NO_CXX11_ALLOCATOR
        root = allocator_type::allocate(1);
        new(root) node(*rhs.root, alloc, NULL);
#else
        root = allocator_traits::allocate(alloc, 1);
        allocator_traits::construct(alloc, root, *rhs.root, alloc, nullptr);
#endif
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
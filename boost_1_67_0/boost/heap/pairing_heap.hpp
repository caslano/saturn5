// boost heap: pairing heap
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_PAIRING_HEAP_HPP
#define BOOST_HEAP_PAIRING_HEAP_HPP

#include <algorithm>
#include <utility>
#include <vector>

#include <boost/assert.hpp>

#include <boost/heap/detail/heap_comparison.hpp>
#include <boost/heap/detail/heap_node.hpp>
#include <boost/heap/policies.hpp>
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

typedef parameter::parameters<boost::parameter::optional<tag::allocator>,
                              boost::parameter::optional<tag::compare>,
                              boost::parameter::optional<tag::stable>,
                              boost::parameter::optional<tag::constant_time_size>,
                              boost::parameter::optional<tag::stability_counter_type>
                             > pairing_heap_signature;

template <typename T, typename Parspec>
struct make_pairing_heap_base
{
    static const bool constant_time_size = parameter::binding<Parspec,
                                                              tag::constant_time_size,
                                                              boost::true_type
                                                             >::type::value;
    typedef typename detail::make_heap_base<T, Parspec, constant_time_size>::type base_type;
    typedef typename detail::make_heap_base<T, Parspec, constant_time_size>::allocator_argument allocator_argument;
    typedef typename detail::make_heap_base<T, Parspec, constant_time_size>::compare_argument compare_argument;

    typedef heap_node<typename base_type::internal_type, false> node_type;

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
        type(type const & rhs):
            base_type(rhs), allocator_type(rhs)
        {}

        type(type && rhs):
            base_type(std::move(static_cast<base_type&>(rhs))),
            allocator_type(std::move(static_cast<allocator_type&>(rhs)))
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
            allocator_type::operator=(static_cast<const allocator_type&>(rhs));
            return *this;
        }
#endif
    };
};

}

/**
 * \class pairing_heap
 * \brief pairing heap
 *
 * Pairing heaps are self-adjusting binary heaps. Although design and implementation are rather simple,
 * the complexity analysis is yet unsolved. For details, consult:
 *
 * Pettie, Seth (2005), "Towards a final analysis of pairing heaps",
 * Proc. 46th Annual IEEE Symposium on Foundations of Computer Science, pp. 174-183
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
 *
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
          class A4 = boost::parameter::void_
         >
#endif
class pairing_heap:
    private detail::make_pairing_heap_base<T,
                                           typename detail::pairing_heap_signature::bind<A0, A1, A2, A3, A4>::type
                                          >::type
{
    typedef typename detail::pairing_heap_signature::bind<A0, A1, A2, A3, A4>::type bound_args;
    typedef detail::make_pairing_heap_base<T, bound_args> base_maker;
    typedef typename base_maker::type super_t;

    typedef typename super_t::internal_type internal_type;
    typedef typename super_t::size_holder_type size_holder;
    typedef typename base_maker::allocator_argument allocator_argument;

private:
    template <typename Heap1, typename Heap2>
    friend struct heap_merge_emulate;

#ifndef BOOST_DOXYGEN_INVOKED
    struct implementation_defined:
        detail::extract_allocator_types<typename base_maker::allocator_argument>
    {
        typedef T value_type;
        typedef typename detail::extract_allocator_types<typename base_maker::allocator_argument>::size_type size_type;
        typedef typename detail::extract_allocator_types<typename base_maker::allocator_argument>::reference reference;

        typedef typename base_maker::compare_argument value_compare;
        typedef typename base_maker::allocator_type allocator_type;

#ifdef BOOST_NO_CXX11_ALLOCATOR
        typedef typename allocator_type::pointer node_pointer;
        typedef typename allocator_type::const_pointer const_node_pointer;
#else
        typedef std::allocator_traits<allocator_type> allocator_traits;
        typedef typename allocator_traits::pointer node_pointer;
        typedef typename allocator_traits::const_pointer const_node_pointer;
#endif

        typedef detail::heap_node_list node_list_type;
        typedef typename node_list_type::iterator node_list_iterator;
        typedef typename node_list_type::const_iterator node_list_const_iterator;

        typedef typename base_maker::node_type node;

        typedef detail::value_extractor<value_type, internal_type, super_t> value_extractor;
        typedef typename super_t::internal_compare internal_compare;
        typedef detail::node_handle<node_pointer, super_t, reference> handle_type;

        typedef detail::tree_iterator<node,
                                      const value_type,
                                      allocator_type,
                                      value_extractor,
                                      detail::pointer_to_reference<node>,
                                      false,
                                      false,
                                      value_compare
                                     > iterator;

        typedef iterator const_iterator;

        typedef detail::tree_iterator<node,
                                      const value_type,
                                      allocator_type,
                                      value_extractor,
                                      detail::pointer_to_reference<node>,
                                      false,
                                      true,
                                      value_compare
                                     > ordered_iterator;
    };

    typedef typename implementation_defined::node node;
    typedef typename implementation_defined::node_pointer node_pointer;
    typedef typename implementation_defined::node_list_type node_list_type;
    typedef typename implementation_defined::node_list_iterator node_list_iterator;
    typedef typename implementation_defined::node_list_const_iterator node_list_const_iterator;
    typedef typename implementation_defined::internal_compare internal_compare;

    typedef boost::intrusive::list<detail::heap_node_base<true>,
                                   boost::intrusive::constant_time_size<false>
                                  > node_child_list;
#endif

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

    typedef typename implementation_defined::handle_type handle_type;

    static const bool constant_time_size = super_t::constant_time_size;
    static const bool has_ordered_iterators = true;
    static const bool is_mergable = true;
    static const bool is_stable = detail::extract_stable<bound_args>::value;
    static const bool has_reserve = false;

    /// \copydoc boost::heap::priority_queue::priority_queue(value_compare const &)
    explicit pairing_heap(value_compare const & cmp = value_compare()):
        super_t(cmp), root(NULL)
    {}

    /// \copydoc boost::heap::priority_queue::priority_queue(priority_queue const &)
    pairing_heap(pairing_heap const & rhs):
        super_t(rhs), root(NULL)
    {
        if (rhs.empty())
            return;

        clone_tree(rhs);
        size_holder::set_size(rhs.get_size());
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    /// \copydoc boost::heap::priority_queue::priority_queue(priority_queue &&)
    pairing_heap(pairing_heap && rhs):
        super_t(std::move(rhs)), root(rhs.root)
    {
        rhs.root = NULL;
    }

    /// \copydoc boost::heap::priority_queue::operator=(priority_queue &&)
    pairing_heap & operator=(pairing_heap && rhs)
    {
        super_t::operator=(std::move(rhs));
        root = rhs.root;
        rhs.root = NULL;
        return *this;
    }
#endif

    /// \copydoc boost::heap::priority_queue::operator=(priority_queue const & rhs)
    pairing_heap & operator=(pairing_heap const & rhs)
    {
        clear();
        size_holder::set_size(rhs.get_size());
        static_cast<super_t&>(*this) = rhs;

        clone_tree(rhs);
        return *this;
    }

    ~pairing_heap(void)
    {
        while (!empty())
            pop();
    }

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
            return detail::count_nodes(root);
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
    void swap(pairing_heap & rhs)
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
     * \b Effects: Adds a new element to the priority queue. Returns handle to element
     *
     * \cond
     * \b Complexity: \f$2^2log(log(N))\f$ (amortized).
     * \endcond
     *
     * \b Complexity: 2**2*log(log(N)) (amortized).
     *
     * */
    handle_type push(value_type const & v)
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
        return handle_type(n);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    /**
     * \b Effects: Adds a new element to the priority queue. The element is directly constructed in-place. Returns handle to element.
     *
     * \cond
     * \b Complexity: \f$2^2log(log(N))\f$ (amortized).
     * \endcond
     *
     * \b Complexity: 2**2*log(log(N)) (amortized).
     *
     * */
    template <class... Args>
    handle_type emplace(Args&&... args)
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
        return handle_type(n);
    }
#endif

    /**
     * \b Effects: Removes the top element from the priority queue.
     *
     * \b Complexity: Logarithmic (amortized).
     *
     * */
    void pop(void)
    {
        BOOST_ASSERT(!empty());

        erase(handle_type(root));
    }

    /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \cond
     * \b Complexity: \f$2^2log(log(N))\f$ (amortized).
     * \endcond
     *
     * \b Complexity: 2**2*log(log(N)) (amortized).
     *
     * */
    void update (handle_type handle, const_reference v)
    {
        handle.node_->value = super_t::make_node(v);
        update(handle);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \cond
     * \b Complexity: \f$2^2log(log(N))\f$ (amortized).
     * \endcond
     *
     * \b Complexity: 2**2*log(log(N)) (amortized).
     *
     * \b Note: If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void update (handle_type handle)
    {
        node_pointer n = handle.node_;

        n->unlink();
        if (!n->children.empty())
            n = merge_nodes(n, merge_node_list(n->children));

        if (n != root)
            merge_node(n);
    }

     /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \cond
     * \b Complexity: \f$2^2log(log(N))\f$ (amortized).
     * \endcond
     *
     * \b Complexity: 2**2*log(log(N)) (amortized).
     *
     * \b Note: The new value is expected to be greater than the current one
     * */
    void increase (handle_type handle, const_reference v)
    {
        update(handle, v);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \cond
     * \b Complexity: \f$2^2log(log(N))\f$ (amortized).
     * \endcond
     *
     * \b Complexity: 2**2*log(log(N)) (amortized).
     *
     * \b Note: If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void increase (handle_type handle)
    {
        update(handle);
    }

    /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \cond
     * \b Complexity: \f$2^2log(log(N))\f$ (amortized).
     * \endcond
     *
     * \b Complexity: 2**2*log(log(N)) (amortized).
     *
     * \b Note: The new value is expected to be less than the current one
     * */
    void decrease (handle_type handle, const_reference v)
    {
        update(handle, v);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \cond
     * \b Complexity: \f$2^2log(log(N))\f$ (amortized).
     * \endcond
     *
     * \b Complexity: 2**2*log(log(N)) (amortized).
     *
     * \b Note: The new value is expected to be less than the current one. If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void decrease (handle_type handle)
    {
        update(handle);
    }

    /**
     * \b Effects: Removes the element handled by \c handle from the priority_queue.
     *
     * \cond
     * \b Complexity: \f$2^2log(log(N))\f$ (amortized).
     * \endcond
     *
     * \b Complexity: 2**2*log(log(N)) (amortized).
     * */
    void erase(handle_type handle)
    {
        node_pointer n = handle.node_;
        if (n != root) {
            n->unlink();
            if (!n->children.empty())
                merge_node(merge_node_list(n->children));
        } else {
            if (!n->children.empty())
                root = merge_node_list(n->children);
            else
                root = NULL;
        }

        size_holder::decrement();
#ifdef BOOST_NO_CXX11_ALLOCATOR
        n->~node();
        allocator_type::deallocate(n, 1);
#else
        allocator_type& alloc = *this;
        allocator_traits::destroy(alloc, n);
        allocator_traits::deallocate(alloc, n, 1);
#endif
    }

    /// \copydoc boost::heap::priority_queue::begin
    iterator begin(void) const
    {
        return iterator(root, super_t::value_comp());
    }

    /// \copydoc boost::heap::priority_queue::end
    iterator end(void) const
    {
        return iterator(super_t::value_comp());
    }

    /// \copydoc boost::heap::fibonacci_heap::ordered_begin
    ordered_iterator ordered_begin(void) const
    {
        return ordered_iterator(root, super_t::value_comp());
    }

    /// \copydoc boost::heap::fibonacci_heap::ordered_begin
    ordered_iterator ordered_end(void) const
    {
        return ordered_iterator(NULL, super_t::value_comp());
    }


    /// \copydoc boost::heap::d_ary_heap_mutable::s_handle_from_iterator
    static handle_type s_handle_from_iterator(iterator const & it)
    {
        node * ptr = const_cast<node *>(it.get_node());
        return handle_type(ptr);
    }

    /**
     * \b Effects: Merge all elements from rhs into this
     *
     * \cond
     * \b Complexity: \f$2^2log(log(N))\f$ (amortized).
     * \endcond
     *
     * \b Complexity: 2**2*log(log(N)) (amortized).
     *
     * */
    void merge(pairing_heap & rhs)
    {
        if (rhs.empty())
            return;

        merge_node(rhs.root);

        size_holder::add(rhs.get_size());
        rhs.set_size(0);
        rhs.root = NULL;

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

private:
#if !defined(BOOST_DOXYGEN_INVOKED)
    void clone_tree(pairing_heap const & rhs)
    {
        BOOST_HEAP_ASSERT(root == NULL);
        if (rhs.empty())
            return;

        root = allocator_type::allocate(1);

        new(root) node(static_cast<node const &>(*rhs.root), static_cast<allocator_type&>(*this));
    }

    void merge_node(node_pointer other)
    {
        BOOST_HEAP_ASSERT(other);
        if (root != NULL)
            root = merge_nodes(root, other);
        else
            root = other;
    }

    node_pointer merge_node_list(node_child_list & children)
    {
        BOOST_HEAP_ASSERT(!children.empty());
        node_pointer merged = merge_first_pair(children);
        if (children.empty())
            return merged;

        node_child_list node_list;
        node_list.push_back(*merged);

        do {
            node_pointer next_merged = merge_first_pair(children);
            node_list.push_back(*next_merged);
        } while (!children.empty());

        return merge_node_list(node_list);
    }

    node_pointer merge_first_pair(node_child_list & children)
    {
        BOOST_HEAP_ASSERT(!children.empty());
        node_pointer first_child = static_cast<node_pointer>(&children.front());
        children.pop_front();
        if (children.empty())
            return first_child;

        node_pointer second_child = static_cast<node_pointer>(&children.front());
        children.pop_front();

        return merge_nodes(first_child, second_child);
    }

    node_pointer merge_nodes(node_pointer node1, node_pointer node2)
    {
        if (super_t::operator()(node1->value, node2->value))
            std::swap(node1, node2);

        node2->unlink();
        node1->children.push_front(*node2);
        return node1;
    }

    node_pointer root;
#endif
};


} /* namespace heap */
} /* namespace boost */

#undef BOOST_HEAP_ASSERT
#endif /* BOOST_HEAP_PAIRING_HEAP_HPP */

/* pairing_heap.hpp
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
*/
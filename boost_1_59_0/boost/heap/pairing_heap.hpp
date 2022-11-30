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

    typedef typename boost::allocator_rebind<allocator_argument, node_type>::type allocator_type;

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

        typedef typename boost::allocator_pointer<allocator_type>::type node_pointer;
        typedef typename boost::allocator_const_pointer<allocator_type>::type const_node_pointer;

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

        allocator_type& alloc = *this;
        node_pointer n = alloc.allocate(1);
        new(n) node(super_t::make_node(v));
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

        allocator_type& alloc = *this;
        node_pointer n = alloc.allocate(1);
        new(n) node(super_t::make_node(std::forward<Args>(args)...));
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
        n->~node();
        allocator_type& alloc = *this;
        alloc.deallocate(n, 1);
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
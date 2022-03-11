// boost heap: binomial heap
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_BINOMIAL_HEAP_HPP
#define BOOST_HEAP_BINOMIAL_HEAP_HPP

#include <algorithm>
#include <utility>
#include <vector>

#include <boost/assert.hpp>

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

typedef parameter::parameters<boost::parameter::optional<tag::allocator>,
                              boost::parameter::optional<tag::compare>,
                              boost::parameter::optional<tag::stable>,
                              boost::parameter::optional<tag::constant_time_size>,
                              boost::parameter::optional<tag::stability_counter_type>
                             > binomial_heap_signature;

template <typename T, typename Parspec>
struct make_binomial_heap_base
{
    static const bool constant_time_size = parameter::binding<Parspec,
                                                              tag::constant_time_size,
                                                              boost::true_type
                                                             >::type::value;
    typedef typename detail::make_heap_base<T, Parspec, constant_time_size>::type base_type;
    typedef typename detail::make_heap_base<T, Parspec, constant_time_size>::allocator_argument allocator_argument;
    typedef typename detail::make_heap_base<T, Parspec, constant_time_size>::compare_argument compare_argument;

    typedef parent_pointing_heap_node<typename base_type::internal_type> node_type;

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
            allocator_type::operator=(static_cast<allocator_type const &>(rhs));
            return *this;
        }
#endif
    };
};

}

/**
 * \class binomial_heap
 * \brief binomial heap
 *
 * The template parameter T is the type to be managed by the container.
 * The user can specify additional options and if no options are provided default options are used.
 *
 * The container supports the following options:
 * - \c boost::heap::stable<>, defaults to \c stable<false>
 * - \c boost::heap::compare<>, defaults to \c compare<std::less<T> >
 * - \c boost::heap::allocator<>, defaults to \c allocator<std::allocator<T> >
 * - \c boost::heap::constant_time_size<>, defaults to \c constant_time_size<true>
 * - \c boost::heap::stability_counter_type<>, defaults to \c stability_counter_type<boost::uintmax_t>
 *
 */
#ifdef BOOST_DOXYGEN_INVOKED
template<class T, class ...Options>
#else
template <typename T,
          class A0 = boost::parameter::void_,
          class A1 = boost::parameter::void_,
          class A2 = boost::parameter::void_,
          class A3 = boost::parameter::void_
         >
#endif
class binomial_heap:
    private detail::make_binomial_heap_base<T,
                                            typename detail::binomial_heap_signature::bind<A0, A1, A2, A3>::type
                                           >::type
{
    typedef typename detail::binomial_heap_signature::bind<A0, A1, A2, A3>::type bound_args;
    typedef detail::make_binomial_heap_base<T, bound_args> base_maker;
    typedef typename base_maker::type super_t;

    typedef typename super_t::internal_type internal_type;
    typedef typename super_t::size_holder_type size_holder;
    typedef typename super_t::stability_counter_type stability_counter_type;
    typedef typename base_maker::allocator_argument allocator_argument;

    template <typename Heap1, typename Heap2>
    friend struct heap_merge_emulate;

public:
    static const bool constant_time_size = super_t::constant_time_size;
    static const bool has_ordered_iterators = true;
    static const bool is_mergable = true;
    static const bool is_stable = detail::extract_stable<bound_args>::value;
    static const bool has_reserve = false;

private:
#ifndef BOOST_DOXYGEN_INVOKED
    struct implementation_defined:
        detail::extract_allocator_types<typename base_maker::allocator_argument>
    {
        typedef T value_type;
        typedef typename detail::extract_allocator_types<typename base_maker::allocator_argument>::size_type size_type;
        typedef typename detail::extract_allocator_types<typename base_maker::allocator_argument>::reference reference;

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

        typedef detail::node_handle<node_pointer, super_t, reference> handle_type;

        typedef typename base_maker::node_type node_type;

        typedef boost::intrusive::list<detail::heap_node_base<false>,
                                       boost::intrusive::constant_time_size<true>
                                       > node_list_type;

        typedef typename node_list_type::iterator node_list_iterator;
        typedef typename node_list_type::const_iterator node_list_const_iterator;
        typedef detail::value_extractor<value_type, internal_type, super_t> value_extractor;

        typedef detail::recursive_tree_iterator<node_type,
                                        node_list_const_iterator,
                                        const value_type,
                                        value_extractor,
                                        detail::list_iterator_converter<node_type, node_list_type>
                                        > iterator;
        typedef iterator const_iterator;

        typedef detail::tree_iterator<node_type,
                                     const value_type,
                                     allocator_type,
                                     value_extractor,
                                     detail::list_iterator_converter<node_type, node_list_type>,
                                     true,
                                     true,
                                     value_compare
                                    > ordered_iterator;
    };
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

private:
    typedef typename implementation_defined::node_type node_type;
    typedef typename implementation_defined::node_list_type node_list_type;
    typedef typename implementation_defined::node_pointer node_pointer;
    typedef typename implementation_defined::const_node_pointer const_node_pointer;
    typedef typename implementation_defined::node_list_iterator node_list_iterator;
    typedef typename implementation_defined::node_list_const_iterator node_list_const_iterator;

    typedef typename super_t::internal_compare internal_compare;

public:
    /// \copydoc boost::heap::priority_queue::priority_queue(value_compare const &)
    explicit binomial_heap(value_compare const & cmp = value_compare()):
        super_t(cmp), top_element(0)
    {}

    /// \copydoc boost::heap::priority_queue::priority_queue(priority_queue const &)
    binomial_heap(binomial_heap const & rhs):
        super_t(rhs), top_element(0)
    {
        if (rhs.empty())
            return;

        clone_forest(rhs);
        size_holder::set_size(rhs.get_size());
    }

    /// \copydoc boost::heap::priority_queue::operator=(priority_queue const &)
    binomial_heap & operator=(binomial_heap const & rhs)
    {
        clear();
        size_holder::set_size(rhs.get_size());
        static_cast<super_t&>(*this) = rhs;

        if (rhs.empty())
            top_element = NULL;
        else
            clone_forest(rhs);
        return *this;
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    /// \copydoc boost::heap::priority_queue::priority_queue(priority_queue &&)
    binomial_heap(binomial_heap && rhs):
        super_t(std::move(rhs)), top_element(rhs.top_element)
    {
        trees.splice(trees.begin(), rhs.trees);
        rhs.top_element = NULL;
    }

    /// \copydoc boost::heap::priority_queue::operator=(priority_queue &&)
    binomial_heap & operator=(binomial_heap && rhs)
    {
        clear();
        super_t::operator=(std::move(rhs));
        trees.splice(trees.begin(), rhs.trees);
        top_element = rhs.top_element;
        rhs.top_element = NULL;
        return *this;
    }
#endif

    ~binomial_heap(void)
    {
        clear();
    }

    /// \copydoc boost::heap::priority_queue::empty
    bool empty(void) const
    {
        return top_element == NULL;
    }

    /**
     * \b Effects: Returns the number of elements contained in the priority queue.
     *
     * \b Complexity: Constant, if configured with constant_time_size<true>, otherwise linear.
     *
     * */
    size_type size(void) const
    {
        if (constant_time_size)
            return size_holder::get_size();

        if (empty())
            return 0;
        else
            return detail::count_list_nodes<node_type, node_list_type>(trees);
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
        typedef detail::node_disposer<node_type, typename node_list_type::value_type, allocator_type> disposer;
        trees.clear_and_dispose(disposer(*this));

        size_holder::set_size(0);
        top_element = NULL;
    }

    /// \copydoc boost::heap::priority_queue::get_allocator
    allocator_type get_allocator(void) const
    {
        return *this;
    }

    /// \copydoc boost::heap::priority_queue::swap
    void swap(binomial_heap & rhs)
    {
        super_t::swap(rhs);
        std::swap(top_element, rhs.top_element);
        trees.swap(rhs.trees);
    }

    /// \copydoc boost::heap::priority_queue::top
    const_reference top(void) const
    {
        BOOST_ASSERT(!empty());

        return super_t::get_value(top_element->value);
    }

    /**
     * \b Effects: Adds a new element to the priority queue. Returns handle to element
     *
     * \b Complexity: Logarithmic.
     *
     * */
    handle_type push(value_type const & v)
    {
#ifdef BOOST_NO_CXX11_ALLOCATOR
        node_pointer n = allocator_type::allocate(1);
        new(n) node_type(super_t::make_node(v));
#else
        allocator_type& alloc = *this;
        node_pointer n = allocator_traits::allocate(alloc, 1);
        allocator_traits::construct(alloc, n, super_t::make_node(v));
#endif
        insert_node(trees.begin(), n);

        if (!top_element || super_t::operator()(top_element->value, n->value))
            top_element = n;

        size_holder::increment();
        sanity_check();
        return handle_type(n);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    /**
     * \b Effects: Adds a new element to the priority queue. The element is directly constructed in-place. Returns handle to element.
     *
     * \b Complexity: Logarithmic.
     *
     * */
    template <class... Args>
    handle_type emplace(Args&&... args)
    {
#ifdef BOOST_NO_CXX11_ALLOCATOR
        node_pointer n = allocator_type::allocate(1);
        new(n) node_type(super_t::make_node(std::forward<Args>(args)...));
#else
        allocator_type& alloc = *this;
        node_pointer n = allocator_traits::allocate(alloc, 1);
        allocator_traits::construct(alloc, n, super_t::make_node(std::forward<Args>(args)...));
#endif
        insert_node(trees.begin(), n);

        if (!top_element || super_t::operator()(top_element->value, n->value))
            top_element = n;

        size_holder::increment();
        sanity_check();
        return handle_type(n);
    }
#endif

    /**
     * \b Effects: Removes the top element from the priority queue.
     *
     * \b Complexity: Logarithmic.
     *
     * */
    void pop(void)
    {
        BOOST_ASSERT(!empty());

        node_pointer element = top_element;

        trees.erase(node_list_type::s_iterator_to(*element));
        size_holder::decrement();

        if (element->child_count()) {
            size_type sz = (1 << element->child_count()) - 1;

            binomial_heap children(value_comp(), element->children, sz);
            if (trees.empty()) {
                stability_counter_type stability_count = super_t::get_stability_count();
                size_t size = constant_time_size ? size_holder::get_size()
                                                 : 0;
                swap(children);
                super_t::set_stability_count(stability_count);

                if (constant_time_size)
                    size_holder::set_size( size );
            } else
                merge_and_clear_nodes(children);

        }

        if (trees.empty())
            top_element = NULL;
        else
            update_top_element();

#ifdef BOOST_NO_CXX11_ALLOCATOR
        element->~node_type();
        allocator_type::deallocate(element, 1);
#else
        allocator_type& alloc = *this;
        allocator_traits::destroy(alloc, element);
        allocator_traits::deallocate(alloc, element, 1);
#endif
        sanity_check();
    }

    /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic.
     *
     * */
    void update (handle_type handle, const_reference v)
    {
        if (super_t::operator()(super_t::get_value(handle.node_->value), v))
            increase(handle, v);
        else
            decrease(handle, v);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void update (handle_type handle)
    {
        node_pointer this_node = handle.node_;

        if (this_node->parent) {
            if (super_t::operator()(super_t::get_value(this_node->parent->value), super_t::get_value(this_node->value)))
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
     * \b Complexity: Logarithmic.
     *
     * \b Note: The new value is expected to be greater than the current one
     * */
    void increase (handle_type handle, const_reference v)
    {
        handle.node_->value = super_t::make_node(v);
        increase(handle);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void increase (handle_type handle)
    {
        node_pointer n = handle.node_;
        siftup(n, *this);

        update_top_element();
        sanity_check();
    }

    /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: The new value is expected to be less than the current one
     * */
    void decrease (handle_type handle, const_reference v)
    {
        handle.node_->value = super_t::make_node(v);
        decrease(handle);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: The new value is expected to be less than the current one. If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void decrease (handle_type handle)
    {
        node_pointer n = handle.node_;

        siftdown(n);

        update_top_element();
    }

    /**
     * \b Effects: Merge with priority queue rhs.
     *
     * \b Complexity: Logarithmic.
     *
     * */
    void merge(binomial_heap & rhs)
    {
        if (rhs.empty())
            return;

        if (empty()) {
            swap(rhs);
            return;
        }

        size_type new_size = size_holder::get_size() + rhs.get_size();
        merge_and_clear_nodes(rhs);

        size_holder::set_size(new_size);
        rhs.set_size(0);
        rhs.top_element = NULL;

        super_t::set_stability_count((std::max)(super_t::get_stability_count(),
                                     rhs.get_stability_count()));
        rhs.set_stability_count(0);
    }

public:
    /// \copydoc boost::heap::priority_queue::begin
    iterator begin(void) const
    {
        return iterator(trees.begin());
    }

    /// \copydoc boost::heap::priority_queue::end
    iterator end(void) const
    {
        return iterator(trees.end());
    }

    /// \copydoc boost::heap::fibonacci_heap::ordered_begin
    ordered_iterator ordered_begin(void) const
    {
        return ordered_iterator(trees.begin(), trees.end(), top_element, super_t::value_comp());
    }

    /// \copydoc boost::heap::fibonacci_heap::ordered_end
    ordered_iterator ordered_end(void) const
    {
        return ordered_iterator(NULL, super_t::value_comp());
    }

    /**
     * \b Effects: Removes the element handled by \c handle from the priority_queue.
     *
     * \b Complexity: Logarithmic.
     * */
    void erase(handle_type handle)
    {
        node_pointer n = handle.node_;
        siftup(n, force_inf());
        top_element = n;
        pop();
    }

    /// \copydoc boost::heap::d_ary_heap_mutable::s_handle_from_iterator
    static handle_type s_handle_from_iterator(iterator const & it)
    {
        node_type * ptr = const_cast<node_type *>(it.get_node());
        return handle_type(ptr);
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
    void merge_and_clear_nodes(binomial_heap & rhs)
    {
        BOOST_HEAP_ASSERT (!empty());
        BOOST_HEAP_ASSERT (!rhs.empty());

        node_list_iterator this_iterator = trees.begin();
        node_pointer carry_node = NULL;

        while (!rhs.trees.empty()) {
            node_pointer rhs_node = static_cast<node_pointer>(&rhs.trees.front());
            size_type rhs_degree = rhs_node->child_count();

            if (super_t::operator()(top_element->value, rhs_node->value))
                top_element = rhs_node;

        try_again:
            node_pointer this_node = static_cast<node_pointer>(&*this_iterator);
            size_type this_degree = this_node->child_count();
            sorted_by_degree();
            rhs.sorted_by_degree();

            if (this_degree == rhs_degree) {
                if (carry_node) {
                    if (carry_node->child_count() < this_degree) {
                        trees.insert(this_iterator, *carry_node);
                        carry_node = NULL;
                    } else {
                        rhs.trees.pop_front();
                        carry_node = merge_trees(carry_node, rhs_node);
                    }
                    ++this_iterator;
                } else {
                    this_iterator = trees.erase(this_iterator);
                    rhs.trees.pop_front();
                    carry_node = merge_trees(this_node, rhs_node);
                }

                if (this_iterator == trees.end())
                    break;
                else
                    continue;
            }

            if (this_degree < rhs_degree) {
                if (carry_node) {
                    if (carry_node->child_count() < this_degree) {
                        trees.insert(this_iterator, *carry_node);
                        carry_node = NULL;
                        ++this_iterator;
                    } else if (carry_node->child_count() == rhs_degree) {
                        rhs.trees.pop_front();
                        carry_node = merge_trees(carry_node, rhs_node);
                        continue;
                    } else {
                        this_iterator = trees.erase(this_iterator);
                        carry_node = merge_trees(this_node, carry_node);
                    }
                    goto try_again;
                } else {
                    ++this_iterator;
                    if (this_iterator == trees.end())
                        break;
                    goto try_again;
                }

                if (this_iterator == trees.end())
                    break;
                else
                    continue;
            }

            if (this_degree > rhs_degree) {
                rhs.trees.pop_front();
                if (carry_node) {
                    if (carry_node->child_count() < rhs_degree) {
                        trees.insert(this_iterator, *carry_node);
                        trees.insert(this_iterator, *rhs_node);
                        carry_node = NULL;
                    } else
                        carry_node = merge_trees(rhs_node, carry_node);
                } else
                    trees.insert(this_iterator, *rhs_node);
            }
        }

        if (!rhs.trees.empty()) {
            if (carry_node) {
                node_list_iterator rhs_it = rhs.trees.begin();
                while (static_cast<node_pointer>(&*rhs_it)->child_count() < carry_node->child_count())
                    ++rhs_it;
                rhs.insert_node(rhs_it, carry_node);
                rhs.increment();
                sorted_by_degree();
                rhs.sorted_by_degree();
                if (trees.empty()) {
                    trees.splice(trees.end(), rhs.trees, rhs.trees.begin(), rhs.trees.end());
                    update_top_element();
                } else
                    merge_and_clear_nodes(rhs);
            } else
                trees.splice(trees.end(), rhs.trees, rhs.trees.begin(), rhs.trees.end());
            return;
        }

        if (carry_node)
            insert_node(this_iterator, carry_node);
    }

    void clone_forest(binomial_heap const & rhs)
    {
        BOOST_HEAP_ASSERT(trees.empty());
        typedef typename node_type::template node_cloner<allocator_type> node_cloner;
        trees.clone_from(rhs.trees, node_cloner(*this, NULL), detail::nop_disposer());

        update_top_element();
    }

    struct force_inf
    {
        template <typename X>
        bool operator()(X const &, X const &) const
        {
            return false;
        }
    };

    template <typename Compare>
    void siftup(node_pointer n, Compare const & cmp)
    {
        while (n->parent) {
            node_pointer parent = n->parent;
            node_pointer grand_parent = parent->parent;
            if (cmp(n->value, parent->value))
                return;

            n->remove_from_parent();

            n->swap_children(parent);
            n->update_children();
            parent->update_children();

            if (grand_parent) {
                parent->remove_from_parent();
                grand_parent->add_child(n);
            } else {
                node_list_iterator it = trees.erase(node_list_type::s_iterator_to(*parent));
                trees.insert(it, *n);
            }
            n->add_child(parent);
        }
    }

    void siftdown(node_pointer n)
    {
        while (n->child_count()) {
            node_pointer max_child = detail::find_max_child<node_list_type, node_type, internal_compare>(n->children, super_t::get_internal_cmp());

            if (super_t::operator()(max_child->value, n->value))
                return;

            max_child->remove_from_parent();

            n->swap_children(max_child);
            n->update_children();
            max_child->update_children();

            node_pointer parent = n->parent;
            if (parent) {
                n->remove_from_parent();
                max_child->add_child(n);
                parent->add_child(max_child);
            } else {
                node_list_iterator position = trees.erase(node_list_type::s_iterator_to(*n));
                max_child->add_child(n);
                trees.insert(position, *max_child);
            }
        }
    }

    void insert_node(node_list_iterator it, node_pointer n)
    {
        if (it != trees.end())
            BOOST_HEAP_ASSERT(static_cast<node_pointer>(&*it)->child_count() >= n->child_count());

        while(true) {
            BOOST_HEAP_ASSERT(!n->is_linked());
            if (it == trees.end())
                break;

            node_pointer this_node = static_cast<node_pointer>(&*it);
            size_type this_degree = this_node->child_count();
            size_type n_degree = n->child_count();
            if (this_degree == n_degree) {
                BOOST_HEAP_ASSERT(it->is_linked());
                it = trees.erase(it);

                n = merge_trees(n, this_node);
            } else
                break;
        }
        trees.insert(it, *n);
    }

    // private constructor, just used in pop()
    explicit binomial_heap(value_compare const & cmp, node_list_type & child_list, size_type size):
        super_t(cmp)
    {
        size_holder::set_size(size);
        if (size)
            top_element = static_cast<node_pointer>(&*child_list.begin()); // not correct, but we will reset it later
        else
            top_element = NULL;

        for (node_list_iterator it = child_list.begin(); it != child_list.end(); ++it) {
            node_pointer n = static_cast<node_pointer>(&*it);
            n->parent = NULL;
        }

        trees.splice(trees.end(), child_list, child_list.begin(), child_list.end());

        trees.sort(detail::cmp_by_degree<node_type>());
    }

    node_pointer merge_trees (node_pointer node1, node_pointer node2)
    {
        BOOST_HEAP_ASSERT(node1->child_count() == node2->child_count());

        if (super_t::operator()(node1->value, node2->value))
            std::swap(node1, node2);

        if (node2->parent)
            node2->remove_from_parent();

        node1->add_child(node2);
        return node1;
    }

    void update_top_element(void)
    {
        top_element = detail::find_max_child<node_list_type, node_type, internal_compare>(trees, super_t::get_internal_cmp());
    }

    void sorted_by_degree(void) const
    {
#ifdef BOOST_HEAP_SANITYCHECKS
        int degree = -1;

        for (node_list_const_iterator it = trees.begin(); it != trees.end(); ++it) {
            const_node_pointer n = static_cast<const_node_pointer>(&*it);
            BOOST_HEAP_ASSERT(int(n->child_count()) > degree);
            degree = n->child_count();

            BOOST_HEAP_ASSERT((detail::is_heap<node_type, super_t>(n, *this)));

            size_type child_nodes = detail::count_nodes<node_type>(n);
            BOOST_HEAP_ASSERT(child_nodes == size_type(1 << static_cast<const_node_pointer>(&*it)->child_count()));
        }
#endif
    }

    void sanity_check(void)
    {
#ifdef BOOST_HEAP_SANITYCHECKS
        sorted_by_degree();

        if (!empty()) {
            node_pointer found_top = detail::find_max_child<node_list_type, node_type, internal_compare>(trees, super_t::get_internal_cmp());
            BOOST_HEAP_ASSERT(top_element == found_top);
        }

        if (constant_time_size) {
            size_t counted = detail::count_list_nodes<node_type, node_list_type>(trees);
            size_t stored = size_holder::get_size();
            BOOST_HEAP_ASSERT(counted == stored);
        }
#endif
    }

    node_pointer top_element;
    node_list_type trees;
#endif // BOOST_DOXYGEN_INVOKED
};


} /* namespace heap */
} /* namespace boost */

#undef BOOST_HEAP_ASSERT

#endif /* BOOST_HEAP_D_ARY_HEAP_HPP */

/* binomial_heap.hpp
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
*/
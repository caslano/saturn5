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

        typedef typename boost::allocator_pointer<allocator_type>::type node_pointer;
        typedef typename boost::allocator_const_pointer<allocator_type>::type const_node_pointer;

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
        const allocator_type& alloc = *this;
        return boost::allocator_max_size(alloc);
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
        allocator_type& alloc = *this;
        node_pointer n = alloc.allocate(1);
        new(n) node_type(super_t::make_node(v));
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
        allocator_type& alloc = *this;
        node_pointer n = alloc.allocate(1);
        new(n) node_type(super_t::make_node(std::forward<Args>(args)...));
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

        element->~node_type();
        allocator_type& alloc = *this;
        alloc.deallocate(element, 1);
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
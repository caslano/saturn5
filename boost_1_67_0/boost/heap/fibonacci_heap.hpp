// boost heap: fibonacci heap
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_FIBONACCI_HEAP_HPP
#define BOOST_HEAP_FIBONACCI_HEAP_HPP

#include <algorithm>
#include <utility>
#include <vector>

#include <boost/array.hpp>
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
                             > fibonacci_heap_signature;

template <typename T, typename Parspec>
struct make_fibonacci_heap_base
{
    static const bool constant_time_size = parameter::binding<Parspec,
                                                              tag::constant_time_size,
                                                              boost::true_type
                                                             >::type::value;

    typedef typename detail::make_heap_base<T, Parspec, constant_time_size>::type base_type;
    typedef typename detail::make_heap_base<T, Parspec, constant_time_size>::allocator_argument allocator_argument;
    typedef typename detail::make_heap_base<T, Parspec, constant_time_size>::compare_argument compare_argument;
    typedef marked_heap_node<typename base_type::internal_type> node_type;

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

        type(type const & rhs):
            base_type(static_cast<base_type const &>(rhs)),
            allocator_type(static_cast<allocator_type const &>(rhs))
        {}

        type & operator=(type const & rhs)
        {
            base_type::operator=(static_cast<base_type const &>(rhs));
            allocator_type::operator=(static_cast<allocator_type const &>(rhs));
            return *this;
        }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
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
#endif
    };
};

}



/**
 * \class fibonacci_heap
 * \brief fibonacci heap
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
          class A3 = boost::parameter::void_,
          class A4 = boost::parameter::void_
         >
#endif
class fibonacci_heap:
    private detail::make_fibonacci_heap_base<T,
                                             typename detail::fibonacci_heap_signature::bind<A0, A1, A2, A3, A4>::type
                                            >::type
{
    typedef typename detail::fibonacci_heap_signature::bind<A0, A1, A2, A3, A4>::type bound_args;
    typedef detail::make_fibonacci_heap_base<T, bound_args> base_maker;
    typedef typename base_maker::type super_t;

    typedef typename super_t::size_holder_type size_holder;
    typedef typename super_t::internal_type internal_type;
    typedef typename base_maker::allocator_argument allocator_argument;

    template <typename Heap1, typename Heap2>
    friend struct heap_merge_emulate;

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

        typedef detail::recursive_tree_iterator<node,
                                                node_list_const_iterator,
                                                const value_type,
                                                value_extractor,
                                                detail::list_iterator_converter<node, node_list_type>
                                               > iterator;
        typedef iterator const_iterator;

        typedef detail::tree_iterator<node,
                                      const value_type,
                                      allocator_type,
                                      value_extractor,
                                      detail::list_iterator_converter<node, node_list_type>,
                                      true,
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

    static const bool constant_time_size = base_maker::constant_time_size;
    static const bool has_ordered_iterators = true;
    static const bool is_mergable = true;
    static const bool is_stable = detail::extract_stable<bound_args>::value;
    static const bool has_reserve = false;

    /// \copydoc boost::heap::priority_queue::priority_queue(value_compare const &)
    explicit fibonacci_heap(value_compare const & cmp = value_compare()):
        super_t(cmp), top_element(0)
    {}

    /// \copydoc boost::heap::priority_queue::priority_queue(priority_queue const &)
    fibonacci_heap(fibonacci_heap const & rhs):
        super_t(rhs), top_element(0)
    {
        if (rhs.empty())
            return;

        clone_forest(rhs);
        size_holder::set_size(rhs.size());
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    /// \copydoc boost::heap::priority_queue::priority_queue(priority_queue &&)
    fibonacci_heap(fibonacci_heap && rhs):
        super_t(std::move(rhs)), top_element(rhs.top_element)
    {
        roots.splice(roots.begin(), rhs.roots);
        rhs.top_element = NULL;
    }

    /// \copydoc boost::heap::priority_queue::operator=(priority_queue &&)
    fibonacci_heap & operator=(fibonacci_heap && rhs)
    {
        clear();

        super_t::operator=(std::move(rhs));
        roots.splice(roots.begin(), rhs.roots);
        top_element = rhs.top_element;
        rhs.top_element = NULL;
        return *this;
    }
#endif

    /// \copydoc boost::heap::priority_queue::operator=(priority_queue const &)
    fibonacci_heap & operator=(fibonacci_heap const & rhs)
    {
        clear();
        size_holder::set_size(rhs.size());
        static_cast<super_t&>(*this) = rhs;

        if (rhs.empty())
            top_element = NULL;
        else
            clone_forest(rhs);
        return *this;
    }

    ~fibonacci_heap(void)
    {
        clear();
    }

    /// \copydoc boost::heap::priority_queue::empty
    bool empty(void) const
    {
        if (constant_time_size)
            return size() == 0;
        else
            return roots.empty();
    }

    /// \copydoc boost::heap::priority_queue::size
    size_type size(void) const
    {
        if (constant_time_size)
            return size_holder::get_size();

        if (empty())
            return 0;
        else
            return detail::count_list_nodes<node, node_list_type>(roots);
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
        typedef detail::node_disposer<node, typename node_list_type::value_type, allocator_type> disposer;
        roots.clear_and_dispose(disposer(*this));

        size_holder::set_size(0);
        top_element = NULL;
    }

    /// \copydoc boost::heap::priority_queue::get_allocator
    allocator_type get_allocator(void) const
    {
        return *this;
    }

    /// \copydoc boost::heap::priority_queue::swap
    void swap(fibonacci_heap & rhs)
    {
        super_t::swap(rhs);
        std::swap(top_element, rhs.top_element);
        roots.swap(rhs.roots);
    }


    /// \copydoc boost::heap::priority_queue::top
    value_type const & top(void) const
    {
        BOOST_ASSERT(!empty());

        return super_t::get_value(top_element->value);
    }

    /**
     * \b Effects: Adds a new element to the priority queue. Returns handle to element
     *
     * \b Complexity: Constant.
     *
     * \b Note: Does not invalidate iterators.
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
        roots.push_front(*n);

        if (!top_element || super_t::operator()(top_element->value, n->value))
            top_element = n;
        return handle_type(n);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    /**
     * \b Effects: Adds a new element to the priority queue. The element is directly constructed in-place. Returns handle to element.
     *
     * \b Complexity: Constant.
     *
     * \b Note: Does not invalidate iterators.
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
        roots.push_front(*n);

        if (!top_element || super_t::operator()(top_element->value, n->value))
            top_element = n;
        return handle_type(n);
    }
#endif

    /**
     * \b Effects: Removes the top element from the priority queue.
     *
     * \b Complexity: Logarithmic (amortized). Linear (worst case).
     *
     * */
    void pop(void)
    {
        BOOST_ASSERT(!empty());

        node_pointer element = top_element;
        roots.erase(node_list_type::s_iterator_to(*element));

        finish_erase_or_pop(element);
    }

    /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic if current value < v, Constant otherwise.
     *
     * */
    void update (handle_type handle, const_reference v)
    {
        if (super_t::operator()(super_t::get_value(handle.node_->value), v))
            increase(handle, v);
        else
            decrease(handle, v);
    }

    /** \copydoc boost::heap::fibonacci_heap::update(handle_type, const_reference)
     *
     * \b Rationale: The lazy update function is a modification of the traditional update, that just invalidates
     *               the iterator to the object referred to by the handle.
     * */
    void update_lazy(handle_type handle, const_reference v)
    {
        handle.node_->value = super_t::make_node(v);
        update_lazy(handle);
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
        update_lazy(handle);
        consolidate();
    }

    /** \copydoc boost::heap::fibonacci_heap::update (handle_type handle)
     *
     * \b Rationale: The lazy update function is a modification of the traditional update, that just invalidates
     *               the iterator to the object referred to by the handle.
     * */
    void update_lazy (handle_type handle)
    {
        node_pointer n = handle.node_;
        node_pointer parent = n->get_parent();

        if (parent) {
            n->parent = NULL;
            roots.splice(roots.begin(), parent->children, node_list_type::s_iterator_to(*n));
        }
        add_children_to_root(n);

        if (super_t::operator()(top_element->value, n->value))
            top_element = n;
    }


     /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Constant.
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
     * \b Complexity: Constant.
     *
     * \b Note: If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void increase (handle_type handle)
    {
        node_pointer n = handle.node_;

        if (n->parent) {
            if (super_t::operator()(n->get_parent()->value, n->value)) {
                node_pointer parent = n->get_parent();
                cut(n);
                cascading_cut(parent);
            }
        }

        if (super_t::operator()(top_element->value, n->value)) {
            top_element = n;
            return;
        }
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
        update(handle);
    }

    /**
     * \b Effects: Removes the element handled by \c handle from the priority_queue.
     *
     * \b Complexity: Logarithmic.
     * */
    void erase(handle_type const & handle)
    {
        node_pointer element = handle.node_;
        node_pointer parent = element->get_parent();

        if (parent)
            parent->children.erase(node_list_type::s_iterator_to(*element));
        else
            roots.erase(node_list_type::s_iterator_to(*element));

        finish_erase_or_pop(element);
    }

    /// \copydoc boost::heap::priority_queue::begin
    iterator begin(void) const
    {
        return iterator(roots.begin());
    }

    /// \copydoc boost::heap::priority_queue::end
    iterator end(void) const
    {
        return iterator(roots.end());
    }


    /**
     * \b Effects: Returns an ordered iterator to the first element contained in the priority queue.
     *
     * \b Note: Ordered iterators traverse the priority queue in heap order.
     * */
    ordered_iterator ordered_begin(void) const
    {
        return ordered_iterator(roots.begin(), roots.end(), top_element, super_t::value_comp());
    }

    /**
     * \b Effects: Returns an ordered iterator to the end of the priority queue.
     *
     * \b Note: Ordered iterators traverse the priority queue in heap order.
     * */
    ordered_iterator ordered_end(void) const
    {
        return ordered_iterator(NULL, super_t::value_comp());
    }

    /**
     * \b Effects: Merge with priority queue rhs.
     *
     * \b Complexity: Constant.
     *
     * */
    void merge(fibonacci_heap & rhs)
    {
        size_holder::add(rhs.get_size());

        if (!top_element ||
            (rhs.top_element && super_t::operator()(top_element->value, rhs.top_element->value)))
            top_element = rhs.top_element;

        roots.splice(roots.end(), rhs.roots);

        rhs.top_element = NULL;
        rhs.set_size(0);

        super_t::set_stability_count((std::max)(super_t::get_stability_count(),
                                     rhs.get_stability_count()));
        rhs.set_stability_count(0);
    }

    /// \copydoc boost::heap::d_ary_heap_mutable::s_handle_from_iterator
    static handle_type s_handle_from_iterator(iterator const & it)
    {
        node * ptr = const_cast<node *>(it.get_node());
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
    void clone_forest(fibonacci_heap const & rhs)
    {
        BOOST_HEAP_ASSERT(roots.empty());
        typedef typename node::template node_cloner<allocator_type> node_cloner;
        roots.clone_from(rhs.roots, node_cloner(*this, NULL), detail::nop_disposer());

        top_element = detail::find_max_child<node_list_type, node, internal_compare>(roots, super_t::get_internal_cmp());
    }

    void cut(node_pointer n)
    {
        node_pointer parent = n->get_parent();
        roots.splice(roots.begin(), parent->children, node_list_type::s_iterator_to(*n));
        n->parent = 0;
        n->mark = false;
    }

    void cascading_cut(node_pointer n)
    {
        node_pointer parent = n->get_parent();

        if (parent) {
            if (!parent->mark)
                parent->mark = true;
            else {
                cut(n);
                cascading_cut(parent);
            }
        }
    }

    void add_children_to_root(node_pointer n)
    {
        for (node_list_iterator it = n->children.begin(); it != n->children.end(); ++it) {
            node_pointer child = static_cast<node_pointer>(&*it);
            child->parent = 0;
        }

        roots.splice(roots.end(), n->children);
    }

    void consolidate(void)
    {
        if (roots.empty())
            return;

        static const size_type max_log2 = sizeof(size_type) * 8;
        boost::array<node_pointer, max_log2> aux;
        aux.assign(NULL);

        node_list_iterator it = roots.begin();
        top_element = static_cast<node_pointer>(&*it);

        do {
            node_pointer n = static_cast<node_pointer>(&*it);
            ++it;
            size_type node_rank = n->child_count();

            if (aux[node_rank] == NULL)
                aux[node_rank] = n;
            else {
                do {
                    node_pointer other = aux[node_rank];
                    if (super_t::operator()(n->value, other->value))
                        std::swap(n, other);

                    if (other->parent)
                        n->children.splice(n->children.end(), other->parent->children, node_list_type::s_iterator_to(*other));
                    else
                        n->children.splice(n->children.end(), roots, node_list_type::s_iterator_to(*other));

                    other->parent = n;

                    aux[node_rank] = NULL;
                    node_rank = n->child_count();
                } while (aux[node_rank] != NULL);
                aux[node_rank] = n;
            }

            if (!super_t::operator()(n->value, top_element->value))
                top_element = n;
        }
        while (it != roots.end());
    }

    void finish_erase_or_pop(node_pointer erased_node)
    {
        add_children_to_root(erased_node);

#ifdef BOOST_NO_CXX11_ALLOCATOR
        erased_node->~node();
        allocator_type::deallocate(erased_node, 1);
#else
        allocator_type& alloc = *this;
        allocator_traits::destroy(alloc, erased_node);
        allocator_traits::deallocate(alloc, erased_node, 1);
#endif

        size_holder::decrement();
        if (!empty())
            consolidate();
        else
            top_element = NULL;
    }

    mutable node_pointer top_element;
    node_list_type roots;
#endif
};

} /* namespace heap */
} /* namespace boost */

#undef BOOST_HEAP_ASSERT

#endif /* BOOST_HEAP_FIBONACCI_HEAP_HPP */

/* fibonacci_heap.hpp
s9A8LzE2/l3SdRh5IU7GDyBGktjMZDpRbc9EZuKxsDv4dmhgvXG80CpHjzr3rl19xV12mXpTLCqv1oFaQsIP6WFuD0DrQAkM6k+65QsvbROxjXpV/zcngOx1/vh3rEYm4YJNIPwpV9vWqW5uPZEqjVMEHEg/n9svjoMLkfz0or4bpyOYYhcYGdBG6K8pIJGcwoEaOAoLQ1ZsoO7rqP/d0E7/OfuiNz11kaOzBPQh1gzDT82tPtIZaPXTmOD7J9JAJJ4AovPiUdd4MSOR7D8wgjAZ8pzv34vbnaUz9nhHwJHC1A/CphVtDj08fQcxbifCS4RHQjGGkFLM1l5aTwYVysozhiouNm+0mAdRlXtGmqkI1Y7MCEiggHLBHRlY1cSNkIKnWYhAiqZF3mhZcEw+smwBQDgyw8zeXKxw6kWEY7uDXn9eDwGRDgGTD4OCr5m1ZKVNxSpvZSGvXDWxfHWJ7BE56QepXaCkei0DZx9tC4fTGO/uCSAjJeQPNBVBf9oyZvHpJW4tY5TBZ5dR3kHSX7n28tv5eAlkQvDrk7ZljKiIp6BgOopjZzdtAYItsx+UthFRiAeR9iVro7G8EBI+K0WIYDbrYJtgR9Xymo4SndzKw3BaQ289g4UNAsROUB981NAe5cWPqF4HtpDKaYs3vD81iGoNXxEe6XcE01mlGaGUoA9JRwx5/bNCsjOipqUMSvopvY/kDbNI2m40t1KawU2G9+cDDa0gpBYTO/Pb87v+WYvixUpvrzjJmE0egjx7KJu9Tp5DlMuISiR7C2nb6L4HlffLs01pVI0BO4k6YBEnGV7R7huaVxHsZplMCRgmxXQme8vvHLPewhlwEYs9hsPWEiQo2+FXVauloiy4qM1gSbzNGk4ZefXZi1FcRn3f2SfLRfAJRua7A8A6B1b/w+XH6F+fY9/PGaEuKzwGwuiO00K4zdnZyIyQioQL3mt2w8j0TZR0eBhh9A+dAYTWE6L4wJ6gmYjBzVBgu1vHuTfv5cm8o2vbVQBcAgbXFbmOnGmoLWeX7d8AW5OmGaWQDws8xRuzAZf7p9C+4E+MyuiLcc6uZrqvLM+KRa/0PC/DFnzAIa8Lq6aq+Vta5+0faI69WCs82pgdySanaUURnLnyGENgQPMaeMRIDoTDb1kqXMYo4oCBf9SdHOFBSRhMvAsNFMRQxmZLLYbmc0HtyE5413daG3z3DEjcfjQd+oZwUkqj4QKrOxgfKnbIC04NKVrPOOrEg1ibgyv336ZwttgfIWobSuhzsA6A+nViz7QGIiaK/N2TVh/BmMthOXz4zuPMkMeiUiLxWywgbaX2GFH3QVVbD1lVZmeKckjd3Kum7huqDgPlplCx6k8c4V+cqpNygNgrnWKkaK7bRVFIVcaoHL+pfeqNXmAMFm4ejBpf7DRpQ8iCjhAH2Aage0unAuwkJVAl9v1ejL2ZSIFflIgz5pkcRFdvF9uQctsKiTLhfq7UqNGperJjdVhApOotp4+/hwclhXgBlMnQkZAzbWHMNqY+MUcM1f+MtzfPHtORMixrW7NBPSJXpeS1YNaSn3HtwagMByMw5qc7qgMQsxiUU+lxfMqS/3oJSYHG0g1Eb5KXB3AAES/PN5ZCn4zhsi+8Bw3GbHlZ8iGEcaon2B5CRRmBCS93A0BsxyIiSgTFkDSc5Tmjpd3ZlE0LJ7mVjyZOR0EAJVRJNZZPzpNSRSizn8xOICk+gUHn3uSv52NWt9/sBzeaHoXMMJeWBAGADklDigdsB9AlXwtSigfj2xpKjykl6DqmGZMA7yLnJzXWrBeV0ZT5szwi9fLfa53O+CGEJgR+0GVatHD/FFDgrftROR9sBZzwwQZa7BfUYqrhNEL0yQXm2eKAXhb0HnmVh5wc+VCgFtgJ2B+Vy2qyRbFhB5Udas0tVulpCi8AVU/blnyoleyyQjioHP6RvlhKTCwtm9Ep+wAF6ChhnE1ZktlTlxgfjBlZJ1J4Jv92nlOdKcEU2BwcjxQWlULK3OfrzA6r2TUJnOZjnSfiQIh8QBAFxdGKu63P6787Yptzs+n7azovUsyHmMdeUoLMJCclNkNVsmp4OOQra1uz5950pZZZpCUbAHmdBZMRxuTl7T623iRL5HO4iiZPG+SNG9XX6w9Pf/g+r2/uzjNm7sZ2YuOgeNcXRiyoyHqpSwSc3AYGQUu/wkIxma7BIAT6Ad7x7cIBMNzxdjtalGFnM2SMTn/XeH/AXCjWUgk7AABaGasQ+eV4w7wUe1HzGkKjPlIYpesy/e4N0FcQjYtH1m3ZTqxmbCUpyOggZ7Iep/K7eTdXVbuyx1yzjzEZA066yDVj3pj4wqcVeqoar82NWnW3P/2IIHFSNb7YwtY+4AwOS4k/vQmo4q9N8Z879cyS3U+c1/IUBL8VP9OLFGqUP0zQpDLwdq54Sy/ZQpCB4tqhWjACAqDSQSsfHzj3WUP6lvYP0X8jIThFOyNCGCAe9LWyTtAZBW8wuisz5jj7EF9T4NQCfUCdimj+cPQwDYf+0FC56WY7NUIpJYE9LorsDDSZNINIGINE2jxtkQqyVT2cIfstWWmiT4A9MVxdzx5GAwGzSFOwRPIFiOzNNG4pZuWWDmv+78i30z7Py1XFN22A5d5zjJ8B+Ndq4VkrbLKErBnrKD2C4kSm+HMwSCEZOrcGksuO+kJgi9qBMqaSYD7A4gUSBoBAQDC+pmAMoKIZ/BB+ysBjnHG6iX1lghCTrnOM5lsH67FUuBW3sF73vyXNAfs5CdR+IMNEB/CQCGUo3ZCoFEsceX7QhkERBDCJdJg1SBB2n1u5Yd8X107teEJ0OA7OryC8EwJgkkNGRxWU598IzPQiBBsOYBgioNJBSdrP0FD4y0+WdMGIM1ZLNO8Dbu5D9Es4hWvKJcoexRRb5Umxyhxz0jRu0THip2LDMH5XZfGNjcnYAYOCR/3oHAg/XDLR/WMirTKPlgVrfQpjdKzjtfGUw9FkjE9qo/LlqdTm+qzKvEFndq8SBXhu3OMTmYByLM1dMhGDRdkSdhKlYWYOX314tZgGpWuNd3JMD/AvAxKrhduYpuuuPR4jf7Pf3w+uaOMmbYRnsmlt43oYlW5Iq4yO9Pg0z60IQmXph44dGG2jPCU7rjUBDSwMQkZQERmea1hXOFN7M0xxUyieiIekWATa5dwuB0EwAUUbJm2a4QKF8BeRGklZ8K2tepdruzSk0FvvdSJrnZDl4TdESIdWh+D9Yw5glHqb01jammqsbQsAZAnt+ZsC798UcP5vCkTTroJaegVTl0P0ip9AQJ1sI07hj5qshzzPwqiO1WAO4dlBPE5ez80G1uhvCZoyvkrT0cS3BcaaV64WISyVBKYU5QnRJLzi6cElDKfNbEmbqO6LHjmW0M1Z4zojIV3aelVXvS0ZCYY+EuqLiAHofhOACjuYBWpACBa16UCpCc2ho/JAzk4AfrmltKWncs8BHriv6H1tezzJGbBPNIioxrW7LkfVpR0Hl1Hspt/LceZp2op/ceb0kG5RKUnsoZzZg4GWbwUv/+QX11XkwZoR2p+uZHufWP2akL+8cnfhzP65JIa8IIGDY3DTgbd6zW0/oKkQiEzB1CG8v+S8HgVrPql7j32HSj3KzyhcxfcOlr59Tk9aIH8Cf2eZVcOgii7kQnHuWWl4Zlzp0LESctp38WQ6RGUsgUYKygNNy+MK7QfC/CQA41NlP2gu2KxXnQEjCIkDgsSgxL35D2XwJdymafDzefk9koYxWdbH3Q8TXitQzkPg9s+a83t98nWD2Wr0YmBANHnfEKcb79tMvu4FYtn5xhNn11dDDO9HT9WfyvQkt1WwQ/s3dQg0sEKwggggAgSGToD1lzpnGj7bSHCQ6wvOMETqhAbQgmeAJRzJlQZLEbb+a0IFvJs7SfVRhfC70T/ZbqDAgNgTMX+4L9xfB4BkWoW2/YFE8a26kJcQuAI97bskieLhDsUtLhYhyvJC7c9/71HXvQiBhvzq5QoQECGU1u1SyVUqNKEgZ0ZEMjwuNVbqvs1RJ+IM9caLfMWyjc0B/BWVLDak0Y/BDU1LgtFOQoCPVyfEAduLgK30LcoRf/d5SfSiEtI1rZpVVBiBpui0uGdln+wpZmjJ7CUra2k5qaxzBHEbY9O4rGM3O9utajthq2YjqZQvEQJpnIuuqaPBoRURUw/Q7ogZQidJxmst1DSpqtLLhpovs+RM8ApXyoReAgKYShwD0c0NWSNhHfn78eC9lQC5uUecrhMHSg/TKKFqe1Oj1ULkH+g3ZH3WCKhHypBtnxynmQt4dx0wuQTTtA35IzEVGuNr4Y4Fl1eavgBZToyAIgyDQJoBAI3B6bup9WHUjiskEK7Yg8F0PT2d4tUB/lANK5lBZJ1hSK9OikS6NK8HKDTd4l4PJnIHFBjSgjdQSl3YJ//LlckgrhHfTmm7VEr6l3fZ3W2ibOq5UCvIFlzHsfsTio7qz/UbR73fOPL+30XJjWlXHq9tomjjfeV5pCKz363i4jH8QEIQnco5o935irWfnnYyv8ctrbgngwtkTenrhgXESa3HenFvgSICCp+23n+TtYjeePQG++3b4U6g/78uKzN3ViB8oz+D7l7FJJVWs7AEADxU7Yc5+Z+pCh2AjxS38JCb4XWsa2HylH+RvKnBPAiVng+pw/CfzyEbpKN7nRaCf2RhlsyJVEg1aaxUlSRyyCBo4WKWKg3p7TBWpyIlmgdq286dDJRJ0sH+Nh7AwKnOBSJDTmtWFVhND6oFZ8K1kjali6+E1XpzUEu7ZiG8HRO9k3ifcnUVCnYHm0Rad1LGI5xzmyYqS8vvDZTL1SW7Qg+r4c9CxckloyYc3ETVei593npuiZNb0zGRW1tK1MAMcv7aHxM8DZ7/SlbZbyv3f5xXL1Ptal92rC6rkHa49lbuhgCkOjQAFIQg4cgAhAALz0r2WkK5yG7g3cJTjVh5Z0EtBtckUS1F+77vn+QQqhc6dUnoJ9OXjvVyiPMWMTg1rDhsFmBAsmIDs6fF43f1dHUg+LRifNJwhb17gpc5wybJb2EPBK7o6nVQ9Em4CcYolW/0hQgD8kEPLJSIyc6plsS/jpR8/PwWVU9pweEifdc0U7Ix9eEIseS+f74BfBWnJAMLNIwJMYhJTQTp4sOVAaqgxdUPRf201scZFIv5bIjKECHeyXycdoLP0EpItw5QFIIjFMsyC0/+teuAvckHwUkpCyqux3lu9IhusilFSKQJFm+kcAsPYiDvBWhN8UeMyAAulekwVF+7SsMZb7Pw0o4uKPUg/Ovtm378CuvLje5iKr7gzXPIVHTpq43+IKk2a2sVguzerTZjyD8Y08Kj/Fwwo7TwI5eDjXICV+6Yy+F9PvR+22B11DttZ70Q6pRPVC2lyAy0pK9OOM7jTbIqXJ28Rx1dEIy0AgGmltD+Vyp9j7lva4TJx6iIlNioefkSTjqvnIqFIR2KEsNBzQloxEHQCggcQ2M+M1+USD2Bvfrg0VkIMx2MJnwEnZuuVxzE6qqkA17sgNmcSS6yNR8KtWYDBjxwNcf7wrNj+2/RfnSwipMWvcWvnF1xBeTiWMFuQEbZljXtm16rKAIW8iHzLm+EdNh6PLDu023NmF5/6uhcu+XhORb7Z4uB3lWZNsxTXERXO1LWQRRYurxGLZwPAAAsTiATSl6fyOZnapJUMORNJFek5sIqMnwPIv+iyHV8R+hJeM64Y9CPnvjUu+07ZX00tVW3fc3TCgO4kUv8MOKsM6icFD5AYJEtTivAXuIUa+A97Y3Gil1c3he/g+PhztmBco/bzqlD0f2HSLjVl5Xs+kv3H244RnFuIueKqxCv2YtH1o6KkFeIDtM3pRQIiHstOPnD+izNPX0foZ7+PldpaI24HyM1cbpgHS8gAiesoagK9w/3xDmAI5WKQ4evTRhF1LbaZ5s288HZ44eu+vJhUWfHUxAtt/ftH9Ij9MllkJ4IU8as/pkV7CEWEW3Y3ecpGjk5LISr8iAEO82M28FPB01tunF4oM74zDaOL9C5kPadKjcr/O+Nvsps8+QSOkgrwqL+sDUM6ilPCpwYXqCkk2Va7u3SJZOGhHBBDvX1Ai1x0uQM57DEReVYdaCpwYWyJXsn2v5Aoq5ceXnyAosf74BUKqRxisk8EpnUl2yjoIadxGJYO7VH+udz+/xaI15UL34WgmzWu1i9maPC1pp5QZVMI24JPH1rE7J4NEp85UBSfKnFwFfTKokbtfs9N5aMQYnUtxq15K7BtrhizsuQk1GD4wBH1XMtytNsr7e3gWPUrPhPR/pTT2OpC9sYL6RQojEpPM9eIDCNLp+0oWPJBEeiiuXZkn9XJzdhy1fC4aEakai7OneU9tZ+TuhQV6wXtd4wr9HtIcHmO5R2ZXy9ptHwYBtfcTyeoLV4hKQGFGPALKKkJ6zXFK3dAa6FGuriM/m8M0JzlYDkGYP/DGHI++AxD5/hB7smqOz7DEVicErJGtDMcx96BJJ14wWnGWbOz/SOEdCUOqSCDAcGmlx9l9nfWWOIuwujo3afOFxl/Y808qhyjUFzZc9FMg2d27G+y1buP8KzA3gGNeEc+u+noeNvBUTK0g7y7yFbFw2QfIaAiC2JOx+YdDTOT7nGLfBIZg8O7KvsUkjE6xTjw67Hx1NZpGn7QgkzADxqLjko9//FRwsUu8fJkbClRo1OelZRAA16cN4g77UqvUiRmCFl8VFAndFnfGxc+gvx/UO+qAJc4OeoalLlFDhhdvauGZSyWZ01bPD9/NP0oi3OhWqWscVtV1AIum0Ah2djS46w427dTSXbE/gKob7fH6V1V5uHH4wnJdAPCI6V60TPrm8IsSDkBRCypdigKZYiKuax33DZpd2r3KlRQr1gxSh+onWdI3ckOvPvA3ZEv0OEg6aH84K3tSPLaBieSPyQSDIK/CtywM8lVzRJ0IK0kKyjXw4cCzVK/sLnrI//Ioq/cYkzvzdmPX+e6sISzgdSgHdWc8B9Y1I4uWICzk0gZtJ1xofS+9o1gCNi7UVQksBPX75BDE2g/KAtF5gWu+MDAWzL4mKDLNw+9yGTt27IYdtq4AXnH2HkOzHG1RApG62dAh6jd9kEyV2zK5m6i40HxhDo5EeXo8QqWBd/z6aRf5CD2fG5533eHfAcDeLVnCFLPTjysXi53KHEnXc16LD2WLpBdBpRE3dSdMna62g3lSUb2WgdkP+ixoBJ6fmEqJgBV3kwWOty+nl6qlf5aji1pTe6UR245ccKGsHH7NC1jY++tBVPTkKpy5XR9HIJ5881PRB8WnoYnfCeHO/qKzR0a8SbvZcrg47KbJ8Lg+78Tv3QHlKZ/8XN/gKv0EVTlFuuBLrxweltOiXUIDwCs0AQGKmuCJBq/sTNWISDgnEqwXl+mUQcx7EHIpDf7YxO4c+LSKatLQuHTmSw+0WJtKRBObdpPdofeDcMNJYAxUljuf1pufm/Aui0qpqTxs1q2Qp1a2xaFZoHc0Q/AK13ReuA4wvqUTt7pox1LR8W9sN5LLa7ovwNN4MxbgxH5vyqKfFsORm7DSDhMz2o85Jx2IPxvqBE+PAYJQ4geAR/ZPk+LSs3fHpnFM9cS+5xvNny0ar10/Kd18xfy7rn7z9eYq4QSHEDOtAjS7Olra7+3Ogb6kZAlj7CiMidhxhTU3RM4gpiBzh/7MEaVnvGqg78k9rqyzUXZAzdX0ycro3qntKQp03EWc8PhoU5YxaGQ0E46VphwRZzc66zSAql257W26w9d/3D9D21F7s6drir+Aryxt2eupPC1VBn5PfmmRGfGXPYdmRVv6wXKIG3Jt8fyI0gpwcueem8PZMZhOmE8z0SptxffzXYPiCXJ3NJ9Mh6BW94M6KGPuaRQuGtSSYgq+q4pdvEzAqMMAAsIeh1Sj7JxWCd7U6vj0GIBf/t9wDg3VIKNaI0gDEsQKcK7KkShSgOCnB9/CMbS8UoG5hIOVNUym5qoDWTcnIQx5LvymPmWVw/Tiiexc85kkjad/QYoQkCPh291umAmnueWRPvlEPOjhwRaFY3xMjOvcuLOzViWCMZ8zQNyzq8He9vfy9UWPh61pkCt1i7bj6hWwqhfMEjcqlggtyeFT8aPi9NaPEcUVEY1jvh7gpqNxvL3cQIZdPb+ZE94rakQy5s9NDr4mb6DCbevm/kNo3AQErElVigxgsExU8wfqqvcyyZMTp+TkvLB+3A+QkLMy6+XO/9QKIDtXinLo/4bMmkLAtsZMBkDk0PQGNC/gpkV6t/5Ju7HTL4pAu1Vb+9JTggEErhng/FRf/H/pPpacws97BM6tAQi3beA6MJMc6F1orWsCqp3bxJsZGbPXCtaoy+Va8Ykso270AW9jllHFn2r+ITzYzRnC/RbUYoXg1PHk15T1CEUZyGFkRX9PGLVZTRGucmVYb5QiXW97+/resbfFaDTKfQlFeYdRayD8T4v60bwH8nBXSXYIwKxvMRIitndFBq+KsmU4wBrLJb2F6OvhcNUCM5wvhPn9O0pUjKVGJ98bqjnxNSBDGa0JKflLWONGHDtQz2APZoWmAnekcxpukBwYGcwmVEHf/88eN7xqzu6CRNTPBQ+vu9REQn2UyRNdu/uD2XsFXEpEJLEkzsfJO8IbNXpFV8aS8oidtclpG86Ys5EmG+e2PEvGMQR16ATKuIMNiatIDkaN7ZyK4oM9dBzYkCBrXwCKp3Qi/VzkC320jm96ZMYRjRiv43rL/mzX+wPxh7gbfAH0MKovrOlQlGHyiFStk/uR50oPDISP4zYYCW3/5w3jqGecmo74p8yk54649SbfNaC7sEAzXAudFoEk/qEtfVx3QGz559miva39JFcutBCrOKaduHxllRpQW9yrJE5KrhEqw70d32uGLnXNK+l5c4lJ/gqgoEb8ky6F42rosB4Zr51stFgmcoV4oMzlmLgRWYMZZ5RYcY9oVpVQ7STxLDYwS434F3B8yFESl1/QEk/L6aEGNA1Bk3qnnZM7JzLmtbBr3EFZh1Djp8MAG+ArSN6ZEYYzJZ2ePYjlT05QaA3HCZ1Z9hg0hZtwAsUwh2UKb0CvEoq9qAWWufnKB+7ttqt2HP/auuj9a5RKXXn40PxTl9tdFbXNISfhTMFxSI9rt9KslFmxCO4K/TYLUkJVrWLicF4MILEGmHGQscaZMjj5Kx2c2ZmmZixYY=
*/
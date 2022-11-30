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

    typedef typename boost::allocator_rebind<allocator_argument, node_type>::type allocator_type;

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

        typedef typename boost::allocator_pointer<allocator_type>::type node_pointer;
        typedef typename boost::allocator_const_pointer<allocator_type>::type const_node_pointer;

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
        const allocator_type& alloc = *this;
        return boost::allocator_max_size(alloc);
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

        allocator_type& alloc = *this;
        node_pointer n = alloc.allocate(1);
        new(n) node(super_t::make_node(v));
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

        allocator_type& alloc = *this;
        node_pointer n = alloc.allocate(1);
        new(n) node(super_t::make_node(std::forward<Args>(args)...));
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

        erased_node->~node();
        allocator_type& alloc = *this;
        alloc.deallocate(erased_node, 1);

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
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
*/
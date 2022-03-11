// // boost heap: d-ary heap as container adaptor
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_D_ARY_HEAP_HPP
#define BOOST_HEAP_D_ARY_HEAP_HPP

#include <algorithm>
#include <utility>
#include <vector>

#include <boost/assert.hpp>

#include <boost/mem_fn.hpp>
#include <boost/heap/detail/heap_comparison.hpp>
#include <boost/heap/detail/ordered_adaptor_iterator.hpp>
#include <boost/heap/detail/stable_heap.hpp>
#include <boost/heap/detail/mutable_heap.hpp>

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

struct nop_index_updater
{
    template <typename T>
    static void run(T &, std::size_t)
    {}
};

typedef parameter::parameters<boost::parameter::required<tag::arity>,
                              boost::parameter::optional<tag::allocator>,
                              boost::parameter::optional<tag::compare>,
                              boost::parameter::optional<tag::stable>,
                              boost::parameter::optional<tag::stability_counter_type>,
                              boost::parameter::optional<tag::constant_time_size>
                             > d_ary_heap_signature;


/* base class for d-ary heap */
template <typename T,
          class BoundArgs,
          class IndexUpdater>
class d_ary_heap:
    private make_heap_base<T, BoundArgs, false>::type
{
    typedef make_heap_base<T, BoundArgs, false> heap_base_maker;

    typedef typename heap_base_maker::type super_t;
    typedef typename super_t::internal_type internal_type;

#ifdef BOOST_NO_CXX11_ALLOCATOR
    typedef typename heap_base_maker::allocator_argument::template rebind<internal_type>::other internal_type_allocator;
#else
    typedef typename std::allocator_traits<typename heap_base_maker::allocator_argument>::template rebind_alloc<internal_type> internal_type_allocator;
#endif
    typedef std::vector<internal_type, internal_type_allocator> container_type;
    typedef typename container_type::const_iterator container_iterator;

    typedef IndexUpdater index_updater;

    container_type q_;

    static const unsigned int D = parameter::binding<BoundArgs, tag::arity>::type::value;

    template <typename Heap1, typename Heap2>
    friend struct heap_merge_emulate;

    struct implementation_defined:
        extract_allocator_types<typename heap_base_maker::allocator_argument>
    {
        typedef T value_type;
        typedef typename detail::extract_allocator_types<typename heap_base_maker::allocator_argument>::size_type size_type;

        typedef typename heap_base_maker::compare_argument value_compare;
        typedef typename heap_base_maker::allocator_argument allocator_type;

        struct ordered_iterator_dispatcher
        {
            static size_type max_index(const d_ary_heap * heap)
            {
                return heap->q_.size() - 1;
            }

            static bool is_leaf(const d_ary_heap * heap, size_type index)
            {
                return !heap->not_leaf(index);
            }

            static std::pair<size_type, size_type> get_child_nodes(const d_ary_heap * heap, size_type index)
            {
                BOOST_HEAP_ASSERT(!is_leaf(heap, index));
                return std::make_pair(d_ary_heap::first_child_index(index),
                                    heap->last_child_index(index));
            }

            static internal_type const & get_internal_value(const d_ary_heap * heap, size_type index)
            {
                return heap->q_[index];
            }

            static value_type const & get_value(internal_type const & arg)
            {
                return super_t::get_value(arg);
            }
        };

        typedef detail::ordered_adaptor_iterator<const value_type,
                                                 internal_type,
                                                 d_ary_heap,
                                                 allocator_type,
                                                 typename super_t::internal_compare,
                                                 ordered_iterator_dispatcher
                                                > ordered_iterator;

        typedef detail::stable_heap_iterator<const value_type, container_iterator, super_t> iterator;
        typedef iterator const_iterator;
        typedef void * handle_type;

    };

    typedef typename implementation_defined::ordered_iterator_dispatcher ordered_iterator_dispatcher;

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
    typedef typename implementation_defined::iterator iterator;
    typedef typename implementation_defined::const_iterator const_iterator;
    typedef typename implementation_defined::ordered_iterator ordered_iterator;
    typedef typename implementation_defined::handle_type handle_type;

    static const bool is_stable = extract_stable<BoundArgs>::value;

    explicit d_ary_heap(value_compare const & cmp = value_compare()):
        super_t(cmp)
    {}

    d_ary_heap(d_ary_heap const & rhs):
        super_t(rhs), q_(rhs.q_)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    d_ary_heap(d_ary_heap && rhs):
        super_t(std::move(rhs)), q_(std::move(rhs.q_))
    {}

    d_ary_heap & operator=(d_ary_heap && rhs)
    {
        super_t::operator=(std::move(rhs));
        q_ = std::move(rhs.q_);
        return *this;
    }
#endif

    d_ary_heap & operator=(d_ary_heap const & rhs)
    {
        static_cast<super_t&>(*this) = static_cast<super_t const &>(rhs);
        q_ = rhs.q_;
        return *this;
    }

    bool empty(void) const
    {
        return q_.empty();
    }

    size_type size(void) const
    {
        return q_.size();
    }

    size_type max_size(void) const
    {
        return q_.max_size();
    }

    void clear(void)
    {
        q_.clear();
    }

    allocator_type get_allocator(void) const
    {
        return q_.get_allocator();
    }

    value_type const & top(void) const
    {
        BOOST_ASSERT(!empty());
        return super_t::get_value(q_.front());
    }

    void push(value_type const & v)
    {
        q_.push_back(super_t::make_node(v));
        reset_index(size() - 1, size() - 1);
        siftup(q_.size() - 1);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <class... Args>
    void emplace(Args&&... args)
    {
        q_.emplace_back(super_t::make_node(std::forward<Args>(args)...));
        reset_index(size() - 1, size() - 1);
        siftup(q_.size() - 1);
    }
#endif
    void pop(void)
    {
        BOOST_ASSERT(!empty());
        std::swap(q_.front(), q_.back());
        q_.pop_back();

        if (q_.empty())
            return;

        reset_index(0, 0);
        siftdown(0);
    }

    void swap(d_ary_heap & rhs)
    {
        super_t::swap(rhs);
        q_.swap(rhs.q_);
    }

    iterator begin(void) const
    {
        return iterator(q_.begin());
    }

    iterator end(void) const
    {
        return iterator(q_.end());
    }

    ordered_iterator ordered_begin(void) const
    {
        return ordered_iterator(0, this, super_t::get_internal_cmp());
    }

    ordered_iterator ordered_end(void) const
    {
        return ordered_iterator(size(), this, super_t::get_internal_cmp());
    }

    void reserve (size_type element_count)
    {
        q_.reserve(element_count);
    }

    value_compare const & value_comp(void) const
    {
        return super_t::value_comp();
    }

private:
    void reset_index(size_type index, size_type new_index)
    {
        BOOST_HEAP_ASSERT(index < q_.size());
        index_updater::run(q_[index], new_index);
    }

    void siftdown(size_type index)
    {
        while (not_leaf(index)) {
            size_type max_child_index = top_child_index(index);
            if (!super_t::operator()(q_[max_child_index], q_[index])) {
                reset_index(index, max_child_index);
                reset_index(max_child_index, index);
                std::swap(q_[max_child_index], q_[index]);
                index = max_child_index;
            }
            else
                return;
        }
    }

    /* returns new index */
    void siftup(size_type index)
    {
        while (index != 0) {
            size_type parent = parent_index(index);

            if (super_t::operator()(q_[parent], q_[index])) {
                reset_index(index, parent);
                reset_index(parent, index);
                std::swap(q_[parent], q_[index]);
                index = parent;
            }
            else
                return;
        }
    }

    bool not_leaf(size_type index) const
    {
        const size_t first_child = first_child_index(index);
        return first_child < q_.size();
    }

    size_type top_child_index(size_type index) const
    {
        // invariant: index is not a leaf, so the iterator range is not empty

        const size_t first_index = first_child_index(index);
        typedef typename container_type::const_iterator container_iterator;

        const container_iterator first_child = q_.begin() + first_index;
        const container_iterator end = q_.end();

        const size_type max_elements = std::distance(first_child, end);

        const container_iterator last_child = (max_elements > D) ? first_child + D
                                                                 : end;

        const container_iterator min_element = std::max_element(first_child, last_child, static_cast<super_t const &>(*this));

        return min_element - q_.begin();
    }

    static size_type parent_index(size_type index)
    {
        return (index - 1) / D;
    }

    static size_type first_child_index(size_type index)
    {
        return index * D + 1;
    }

    size_type last_child_index(size_type index) const
    {
        const size_t first_index = first_child_index(index);
        const size_type last_index = (std::min)(first_index + D - 1, size() - 1);

        return last_index;
    }

    template<typename U,
             typename V,
             typename W,
             typename X>
    struct rebind {
        typedef d_ary_heap<U, typename d_ary_heap_signature::bind<boost::heap::stable<heap_base_maker::is_stable>,
                                                                  boost::heap::stability_counter_type<typename heap_base_maker::stability_counter_type>,
                                                                  boost::heap::arity<D>,
                                                                  boost::heap::compare<V>,
                                                                  boost::heap::allocator<W>
                                                                    >::type,
                           X
                          > other;
    };

    template <class U> friend class priority_queue_mutable_wrapper;

    void update(size_type index)
    {
        if (index == 0) {
            siftdown(index);
            return;
        }
        size_type parent = parent_index(index);

        if (super_t::operator()(q_[parent], q_[index]))
            siftup(index);
        else
            siftdown(index);
    }

    void erase(size_type index)
    {
        while (index != 0)
        {
            size_type parent = parent_index(index);

            reset_index(index, parent);
            reset_index(parent, index);
            std::swap(q_[parent], q_[index]);
            index = parent;
        }
        pop();
    }

    void increase(size_type index)
    {
        siftup(index);
    }

    void decrease(size_type index)
    {
        siftdown(index);
    }
};


template <typename T, typename BoundArgs>
struct select_dary_heap
{
    static const bool is_mutable = extract_mutable<BoundArgs>::value;

    typedef typename boost::conditional< is_mutable,
                                priority_queue_mutable_wrapper<d_ary_heap<T, BoundArgs, nop_index_updater > >,
                                d_ary_heap<T, BoundArgs, nop_index_updater >
                              >::type type;
};

} /* namespace detail */



/**
 * \class d_ary_heap
 * \brief d-ary heap class
 *
 * This class implements an immutable priority queue. Internally, the d-ary heap is represented
 * as dynamically sized array (std::vector), that directly stores the values.
 *
 * The template parameter T is the type to be managed by the container.
 * The user can specify additional options and if no options are provided default options are used.
 *
 * The container supports the following options:
 * - \c boost::heap::arity<>, required
 * - \c boost::heap::compare<>, defaults to \c compare<std::less<T> >
 * - \c boost::heap::stable<>, defaults to \c stable<false>
 * - \c boost::heap::stability_counter_type<>, defaults to \c stability_counter_type<boost::uintmax_t>
 * - \c boost::heap::allocator<>, defaults to \c allocator<std::allocator<T> >
 * - \c boost::heap::mutable_<>, defaults to \c mutable_<false>
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
          class A5 = boost::parameter::void_
         >
#endif
class d_ary_heap:
    public detail::select_dary_heap<T, typename detail::d_ary_heap_signature::bind<A0, A1, A2, A3, A4, A5>::type>::type
{
    typedef typename detail::d_ary_heap_signature::bind<A0, A1, A2, A3, A4, A5>::type bound_args;
    typedef typename detail::select_dary_heap<T, bound_args>::type super_t;

    template <typename Heap1, typename Heap2>
    friend struct heap_merge_emulate;

#ifndef BOOST_DOXYGEN_INVOKED
    static const bool is_mutable = detail::extract_mutable<bound_args>::value;

#define BOOST_HEAP_TYPEDEF_FROM_SUPER_T(NAME)   \
    typedef typename super_t::NAME NAME;

    struct implementation_defined
    {
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(size_type)
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(difference_type)
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(value_compare)
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(allocator_type)
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(reference)
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(const_reference)
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(pointer)
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(const_pointer)
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(iterator)
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(const_iterator)
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(ordered_iterator)
        BOOST_HEAP_TYPEDEF_FROM_SUPER_T(handle_type)
    };
#undef BOOST_HEAP_TYPEDEF_FROM_SUPER_T

#endif
public:
    static const bool constant_time_size = true;
    static const bool has_ordered_iterators = true;
    static const bool is_mergable = false;
    static const bool has_reserve = true;
    static const bool is_stable = super_t::is_stable;

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

    /// \copydoc boost::heap::priority_queue::priority_queue(value_compare const &)
    explicit d_ary_heap(value_compare const & cmp = value_compare()):
        super_t(cmp)
    {}

    /// \copydoc boost::heap::priority_queue::priority_queue(priority_queue const &)
    d_ary_heap(d_ary_heap const & rhs):
        super_t(rhs)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    /// \copydoc boost::heap::priority_queue::priority_queue(priority_queue &&)
    d_ary_heap(d_ary_heap && rhs):
        super_t(std::move(rhs))
    {}

    /// \copydoc boost::heap::priority_queue::operator=(priority_queue &&)
    d_ary_heap & operator=(d_ary_heap && rhs)
    {
        super_t::operator=(std::move(rhs));
        return *this;
    }
#endif

    /// \copydoc boost::heap::priority_queue::operator=(priority_queue const &)
    d_ary_heap & operator=(d_ary_heap const & rhs)
    {
        super_t::operator=(rhs);
        return *this;
    }

    /// \copydoc boost::heap::priority_queue::empty
    bool empty(void) const
    {
        return super_t::empty();
    }

    /// \copydoc boost::heap::priority_queue::size
    size_type size(void) const
    {
        return super_t::size();
    }

    /// \copydoc boost::heap::priority_queue::max_size
    size_type max_size(void) const
    {
        return super_t::max_size();
    }

    /// \copydoc boost::heap::priority_queue::clear
    void clear(void)
    {
        super_t::clear();
    }

    /// \copydoc boost::heap::priority_queue::get_allocator
    allocator_type get_allocator(void) const
    {
        return super_t::get_allocator();
    }

    /// \copydoc boost::heap::priority_queue::top
    value_type const & top(void) const
    {
        return super_t::top();
    }

    /// \copydoc boost::heap::priority_queue::push
    typename boost::conditional<is_mutable, handle_type, void>::type push(value_type const & v)
    {
        return super_t::push(v);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    /// \copydoc boost::heap::priority_queue::emplace
    template <class... Args>
    typename boost::conditional<is_mutable, handle_type, void>::type emplace(Args&&... args)
    {
        return super_t::emplace(std::forward<Args>(args)...);
    }
#endif

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

    /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Requirement: data structure must be configured as mutable
     * */
    void update(handle_type handle, const_reference v)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        super_t::update(handle, v);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     *
     * \b Requirement: data structure must be configured as mutable
     * */
    void update(handle_type handle)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        super_t::update(handle);
    }

     /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: The new value is expected to be greater than the current one
     *
     * \b Requirement: data structure must be configured as mutable
     * */
    void increase(handle_type handle, const_reference v)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        super_t::increase(handle, v);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: The new value is expected to be greater than the current one. If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     *
     * \b Requirement: data structure must be configured as mutable
     * */
    void increase(handle_type handle)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        super_t::increase(handle);
    }

     /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: The new value is expected to be less than the current one
     *
     * \b Requirement: data structure must be configured as mutable
     * */
    void decrease(handle_type handle, const_reference v)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        super_t::decrease(handle, v);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: The new value is expected to be less than the current one. If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     *
     * \b Requirement: data structure must be configured as mutable
     * */
    void decrease(handle_type handle)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        super_t::decrease(handle);
    }

    /**
     * \b Effects: Removes the element handled by \c handle from the priority_queue.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Requirement: data structure must be configured as mutable
     * */
    void erase(handle_type handle)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        super_t::erase(handle);
    }

    /**
     * \b Effects: Casts an iterator to a node handle.
     *
     * \b Complexity: Constant.
     *
     * \b Requirement: data structure must be configured as mutable
     * */
    static handle_type s_handle_from_iterator(iterator const & it)
    {
        BOOST_STATIC_ASSERT(is_mutable);
        return super_t::s_handle_from_iterator(it);
    }

    /// \copydoc boost::heap::priority_queue::pop
    void pop(void)
    {
        super_t::pop();
    }

    /// \copydoc boost::heap::priority_queue::swap
    void swap(d_ary_heap & rhs)
    {
        super_t::swap(rhs);
    }

    /// \copydoc boost::heap::priority_queue::begin
    const_iterator begin(void) const
    {
        return super_t::begin();
    }

    /// \copydoc boost::heap::priority_queue::begin
    iterator begin(void)
    {
        return super_t::begin();
    }

    /// \copydoc boost::heap::priority_queue::end
    iterator end(void)
    {
        return super_t::end();
    }

    /// \copydoc boost::heap::priority_queue::end
    const_iterator end(void) const
    {
        return super_t::end();
    }

    /// \copydoc boost::heap::fibonacci_heap::ordered_begin
    ordered_iterator ordered_begin(void) const
    {
        return super_t::ordered_begin();
    }

    /// \copydoc boost::heap::fibonacci_heap::ordered_end
    ordered_iterator ordered_end(void) const
    {
        return super_t::ordered_end();
    }

    /// \copydoc boost::heap::priority_queue::reserve
    void reserve (size_type element_count)
    {
        super_t::reserve(element_count);
    }

    /// \copydoc boost::heap::priority_queue::value_comp
    value_compare const & value_comp(void) const
    {
        return super_t::value_comp();
    }
};

} /* namespace heap */
} /* namespace boost */

#undef BOOST_HEAP_ASSERT

#endif /* BOOST_HEAP_D_ARY_HEAP_HPP */

/* d_ary_heap.hpp
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
*/
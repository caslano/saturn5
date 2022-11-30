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

    typedef typename boost::allocator_rebind<typename heap_base_maker::allocator_argument, internal_type>::type internal_type_allocator;
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
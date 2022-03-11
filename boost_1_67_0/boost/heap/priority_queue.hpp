// boost heap: wrapper for stl heap
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_PRIORITY_QUEUE_HPP
#define BOOST_HEAP_PRIORITY_QUEUE_HPP

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

#include <boost/assert.hpp>

#include <boost/heap/detail/heap_comparison.hpp>
#include <boost/heap/detail/stable_heap.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif


namespace boost  {
namespace heap   {
namespace detail {

typedef parameter::parameters<boost::parameter::optional<tag::allocator>,
                              boost::parameter::optional<tag::compare>,
                              boost::parameter::optional<tag::stable>,
                              boost::parameter::optional<tag::stability_counter_type>
                             > priority_queue_signature;
}

/**
 * \class priority_queue
 * \brief priority queue, based on stl heap functions
 *
 * The priority_queue class is a wrapper for the stl heap functions.<br>
 * The template parameter T is the type to be managed by the container.
 * The user can specify additional options and if no options are provided default options are used.
 *
 * The container supports the following options:
 * - \c boost::heap::compare<>, defaults to \c compare<std::less<T> >
 * - \c boost::heap::stable<>, defaults to \c stable<false>
 * - \c boost::heap::stability_counter_type<>, defaults to \c stability_counter_type<boost::uintmax_t>
 * - \c boost::heap::allocator<>, defaults to \c allocator<std::allocator<T> >
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
class priority_queue:
    private detail::make_heap_base<T, typename detail::priority_queue_signature::bind<A0, A1, A2, A3>::type, false>::type
{
    typedef detail::make_heap_base<T, typename detail::priority_queue_signature::bind<A0, A1, A2, A3>::type, false> heap_base_maker;

    typedef typename heap_base_maker::type super_t;
    typedef typename super_t::internal_type internal_type;
#ifdef BOOST_NO_CXX11_ALLOCATOR
    typedef typename heap_base_maker::allocator_argument::template rebind<internal_type>::other internal_type_allocator;
#else
    typedef typename std::allocator_traits<typename heap_base_maker::allocator_argument>::template rebind_alloc<internal_type> internal_type_allocator;
#endif
    typedef std::vector<internal_type, internal_type_allocator> container_type;

    template <typename Heap1, typename Heap2>
    friend struct detail::heap_merge_emulate;

    container_type q_;

#ifndef BOOST_DOXYGEN_INVOKED
    struct implementation_defined:
        detail::extract_allocator_types<typename heap_base_maker::allocator_argument>
    {
        typedef typename heap_base_maker::compare_argument value_compare;
        typedef detail::stable_heap_iterator<T, typename container_type::const_iterator, super_t> iterator;
        typedef iterator const_iterator;
        typedef typename container_type::allocator_type allocator_type;
#ifndef BOOST_NO_CXX11_ALLOCATOR
        typedef typename std::allocator_traits<allocator_type> allocator_traits;
#endif
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
    /**
     * \b Note: The iterator does not traverse the priority queue in order of the priorities.
     * */
    typedef typename implementation_defined::iterator iterator;
    typedef typename implementation_defined::const_iterator const_iterator;

    static const bool constant_time_size = true;
    static const bool has_ordered_iterators = false;
    static const bool is_mergable = false;
    static const bool is_stable = heap_base_maker::is_stable;
    static const bool has_reserve = true;

    /**
     * \b Effects: constructs an empty priority queue.
     *
     * \b Complexity: Constant.
     *
     * */
    explicit priority_queue(value_compare const & cmp = value_compare()):
        super_t(cmp)
    {}

    /**
     * \b Effects: copy-constructs priority queue from rhs.
     *
     * \b Complexity: Linear.
     *
     * */
    priority_queue (priority_queue const & rhs):
        super_t(rhs), q_(rhs.q_)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    /**
     * \b Effects: C++11-style move constructor.
     *
     * \b Complexity: Constant.
     *
     * \b Note: Only available, if BOOST_NO_CXX11_RVALUE_REFERENCES is not defined
     * */
    priority_queue(priority_queue && rhs) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible<super_t>::value):
        super_t(std::move(rhs)), q_(std::move(rhs.q_))
    {}

    /**
     * \b Effects: C++11-style move assignment.
     *
     * \b Complexity: Constant.
     *
     * \b Note: Only available, if BOOST_NO_CXX11_RVALUE_REFERENCES is not defined
     * */
    priority_queue & operator=(priority_queue && rhs) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_assignable<super_t>::value)
    {
        super_t::operator=(std::move(rhs));
        q_ = std::move(rhs.q_);
        return *this;
    }
#endif

    /**
     * \b Effects: Assigns priority queue from rhs.
     *
     * \b Complexity: Linear.
     *
     * */
    priority_queue & operator=(priority_queue const & rhs)
    {
        static_cast<super_t&>(*this) = static_cast<super_t const &>(rhs);
        q_ = rhs.q_;
        return *this;
    }

    /**
     * \b Effects: Returns true, if the priority queue contains no elements.
     *
     * \b Complexity: Constant.
     *
     * */
    bool empty(void) const BOOST_NOEXCEPT
    {
        return q_.empty();
    }

    /**
     * \b Effects: Returns the number of elements contained in the priority queue.
     *
     * \b Complexity: Constant.
     *
     * */
    size_type size(void) const BOOST_NOEXCEPT
    {
        return q_.size();
    }

    /**
     * \b Effects: Returns the maximum number of elements the priority queue can contain.
     *
     * \b Complexity: Constant.
     *
     * */
    size_type max_size(void) const BOOST_NOEXCEPT
    {
        return q_.max_size();
    }

    /**
     * \b Effects: Removes all elements from the priority queue.
     *
     * \b Complexity: Linear.
     *
     * */
    void clear(void) BOOST_NOEXCEPT
    {
        q_.clear();
    }

    /**
     * \b Effects: Returns allocator.
     *
     * \b Complexity: Constant.
     *
     * */
    allocator_type get_allocator(void) const
    {
        return q_.get_allocator();
    }

    /**
     * \b Effects: Returns a const_reference to the maximum element.
     *
     * \b Complexity: Constant.
     *
     * */
    const_reference top(void) const
    {
        BOOST_ASSERT(!empty());
        return super_t::get_value(q_.front());
    }

    /**
     * \b Effects: Adds a new element to the priority queue.
     *
     * \b Complexity: Logarithmic (amortized). Linear (worst case).
     *
     * */
    void push(value_type const & v)
    {
        q_.push_back(super_t::make_node(v));
        std::push_heap(q_.begin(), q_.end(), static_cast<super_t const &>(*this));
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    /**
     * \b Effects: Adds a new element to the priority queue. The element is directly constructed in-place.
     *
     * \b Complexity: Logarithmic (amortized). Linear (worst case).
     *
     * */
    template <class... Args>
    void emplace(Args&&... args)
    {
        q_.emplace_back(super_t::make_node(std::forward<Args>(args)...));
        std::push_heap(q_.begin(), q_.end(), static_cast<super_t const &>(*this));
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
        std::pop_heap(q_.begin(), q_.end(), static_cast<super_t const &>(*this));
        q_.pop_back();
    }

    /**
     * \b Effects: Swaps two priority queues.
     *
     * \b Complexity: Constant.
     *
     * */
    void swap(priority_queue & rhs) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible<super_t>::value && boost::is_nothrow_move_assignable<super_t>::value)
    {
        super_t::swap(rhs);
        q_.swap(rhs.q_);
    }

    /**
     * \b Effects: Returns an iterator to the first element contained in the priority queue.
     *
     * \b Complexity: Constant.
     *
     * */
    iterator begin(void) const BOOST_NOEXCEPT
    {
        return iterator(q_.begin());
    }

    /**
     * \b Effects: Returns an iterator to the end of the priority queue.
     *
     * \b Complexity: Constant.
     *
     * */
    iterator end(void) const BOOST_NOEXCEPT
    {
        return iterator(q_.end());
    }

    /**
     * \b Effects: Reserves memory for element_count elements
     *
     * \b Complexity: Linear.
     *
     * \b Node: Invalidates iterators
     *
     * */
    void reserve(size_type element_count)
    {
        q_.reserve(element_count);
    }

    /**
     * \b Effect: Returns the value_compare object used by the priority queue
     *
     * */
    value_compare const & value_comp(void) const
    {
        return super_t::value_comp();
    }

    /**
     * \b Returns: Element-wise comparison of heap data structures
     *
     * \b Requirement: the \c value_compare object of both heaps must match.
     *
     * */
    template <typename HeapType>
    bool operator<(HeapType const & rhs) const
    {
        return detail::heap_compare(*this, rhs);
    }

    /**
     * \b Returns: Element-wise comparison of heap data structures
     *
     * \b Requirement: the \c value_compare object of both heaps must match.
     *
     * */
    template <typename HeapType>
    bool operator>(HeapType const & rhs) const
    {
        return detail::heap_compare(rhs, *this);
    }

    /**
     * \b Returns: Element-wise comparison of heap data structures
     *
     * \b Requirement: the \c value_compare object of both heaps must match.
     *
     * */
    template <typename HeapType>
    bool operator>=(HeapType const & rhs) const
    {
        return !operator<(rhs);
    }

    /**
     * \b Returns: Element-wise comparison of heap data structures
     *
     * \b Requirement: the \c value_compare object of both heaps must match.
     *
     * */
    template <typename HeapType>
    bool operator<=(HeapType const & rhs) const
    {
        return !operator>(rhs);
    }

    /** \brief Equivalent comparison
     * \b Returns: True, if both heap data structures are equivalent.
     *
     * \b Requirement: the \c value_compare object of both heaps must match.
     *
     * */
    template <typename HeapType>
    bool operator==(HeapType const & rhs) const
    {
        return detail::heap_equality(*this, rhs);
    }

    /** \brief Equivalent comparison
     * \b Returns: True, if both heap data structures are not equivalent.
     *
     * \b Requirement: the \c value_compare object of both heaps must match.
     *
     * */
    template <typename HeapType>
    bool operator!=(HeapType const & rhs) const
    {
        return !(*this == rhs);
    }
};

} /* namespace heap */
} /* namespace boost */

#endif /* BOOST_HEAP_PRIORITY_QUEUE_HPP */

/* priority_queue.hpp
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
*/
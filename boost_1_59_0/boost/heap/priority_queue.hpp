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
    typedef typename boost::allocator_rebind<typename heap_base_maker::allocator_argument, internal_type>::type internal_type_allocator;
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
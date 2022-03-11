// Helper classes and functions for the circular buffer.

// Copyright (c) 2003-2008 Jan Gaspar

// Copyright 2014,2018 Glen Joseph Fernandes
// (glenjofe@gmail.com)

// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_CIRCULAR_BUFFER_DETAILS_HPP)
#define BOOST_CIRCULAR_BUFFER_DETAILS_HPP

#if defined(_MSC_VER)
    #pragma once
#endif

#include <boost/throw_exception.hpp>
#include <boost/circular_buffer/allocators.hpp>
#include <boost/core/pointer_traits.hpp>
#include <boost/move/move.hpp>
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <iterator>

// Silence MS /W4 warnings like C4913:
// "user defined binary operator ',' exists but no overload could convert all operands, default built-in binary operator ',' used"
// This might happen when previously including some boost headers that overload the coma operator.
#if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable:4913)
#endif

namespace boost {

namespace cb_details {

template <class Traits> struct nonconst_traits;

template<class ForwardIterator, class Diff, class T, class Alloc>
void uninitialized_fill_n_with_alloc(
    ForwardIterator first, Diff n, const T& item, Alloc& alloc);

template<class InputIterator, class ForwardIterator, class Alloc>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator dest, Alloc& a);

template<class InputIterator, class ForwardIterator, class Alloc>
ForwardIterator uninitialized_move_if_noexcept(InputIterator first, InputIterator last, ForwardIterator dest, Alloc& a);

/*!
    \struct const_traits
    \brief Defines the data types for a const iterator.
*/
template <class Traits>
struct const_traits {
    // Basic types
    typedef typename Traits::value_type value_type;
    typedef typename Traits::const_pointer pointer;
    typedef const value_type& reference;
    typedef typename Traits::size_type size_type;
    typedef typename Traits::difference_type difference_type;

    // Non-const traits
    typedef nonconst_traits<Traits> nonconst_self;
};

/*!
    \struct nonconst_traits
    \brief Defines the data types for a non-const iterator.
*/
template <class Traits>
struct nonconst_traits {
    // Basic types
    typedef typename Traits::value_type value_type;
    typedef typename Traits::pointer pointer;
    typedef value_type& reference;
    typedef typename Traits::size_type size_type;
    typedef typename Traits::difference_type difference_type;

    // Non-const traits
    typedef nonconst_traits<Traits> nonconst_self;
};

/*!
    \struct iterator_wrapper
    \brief Helper iterator dereference wrapper.
*/
template <class Iterator>
struct iterator_wrapper {
    mutable Iterator m_it;
    explicit iterator_wrapper(Iterator it) : m_it(it) {}
    Iterator operator () () const { return m_it++; }
private:
    iterator_wrapper<Iterator>& operator = (const iterator_wrapper<Iterator>&); // do not generate
};

/*!
    \struct item_wrapper
    \brief Helper item dereference wrapper.
*/
template <class Pointer, class Value>
struct item_wrapper {
    Value m_item;
    explicit item_wrapper(Value item) : m_item(item) {}
    Pointer operator () () const { return &m_item; }
private:
    item_wrapper<Pointer, Value>& operator = (const item_wrapper<Pointer, Value>&); // do not generate
};

/*!
    \struct assign_n
    \brief Helper functor for assigning n items.
*/
template <class Value, class Alloc>
struct assign_n {
    typedef typename allocator_traits<Alloc>::size_type size_type;
    size_type m_n;
    Value m_item;
    Alloc& m_alloc;
    assign_n(size_type n, Value item, Alloc& alloc) : m_n(n), m_item(item), m_alloc(alloc) {}
    template <class Pointer>
    void operator () (Pointer p) const {
        uninitialized_fill_n_with_alloc(p, m_n, m_item, m_alloc);
    }
private:
    assign_n<Value, Alloc>& operator = (const assign_n<Value, Alloc>&); // do not generate
};

/*!
    \struct assign_range
    \brief Helper functor for assigning range of items.
*/
template <class Iterator, class Alloc>
struct assign_range {
    Iterator m_first;
    Iterator m_last;
    Alloc&   m_alloc;

    assign_range(const Iterator& first, const Iterator& last, Alloc& alloc)
        : m_first(first), m_last(last), m_alloc(alloc) {}

    template <class Pointer>
    void operator () (Pointer p) const {
        boost::cb_details::uninitialized_copy(m_first, m_last, p, m_alloc);
    }
};

template <class Iterator, class Alloc>
inline assign_range<Iterator, Alloc> make_assign_range(const Iterator& first, const Iterator& last, Alloc& a) {
    return assign_range<Iterator, Alloc>(first, last, a);
}

/*!
    \class capacity_control
    \brief Capacity controller of the space optimized circular buffer.
*/
template <class Size>
class capacity_control {

    //! The capacity of the space-optimized circular buffer.
    Size m_capacity;

    //! The lowest guaranteed or minimum capacity of the adapted space-optimized circular buffer.
    Size m_min_capacity;

public:

    //! Constructor.
    capacity_control(Size buffer_capacity, Size min_buffer_capacity = 0)
    : m_capacity(buffer_capacity), m_min_capacity(min_buffer_capacity)
    { // Check for capacity lower than min_capacity.
        BOOST_CB_ASSERT(buffer_capacity >= min_buffer_capacity);
    }

    // Default copy constructor.

    // Default assign operator.

    //! Get the capacity of the space optimized circular buffer.
    Size capacity() const { return m_capacity; }

    //! Get the minimal capacity of the space optimized circular buffer.
    Size min_capacity() const { return m_min_capacity; }

    //! Size operator - returns the capacity of the space optimized circular buffer.
    operator Size() const { return m_capacity; }
};

/*!
    \struct iterator
    \brief Random access iterator for the circular buffer.
    \param Buff The type of the underlying circular buffer.
    \param Traits Basic iterator types.
    \note This iterator is not circular. It was designed
          for iterating from begin() to end() of the circular buffer.
*/
template <class Buff, class Traits>
struct iterator
#if BOOST_CB_ENABLE_DEBUG
    : public debug_iterator_base
#endif // #if BOOST_CB_ENABLE_DEBUG
{
// Helper types

    //! Non-const iterator.
    typedef iterator<Buff, typename Traits::nonconst_self> nonconst_self;

// Basic types
    typedef std::random_access_iterator_tag iterator_category;

    //! The type of the elements stored in the circular buffer.
    typedef typename Traits::value_type value_type;

    //! Pointer to the element.
    typedef typename Traits::pointer pointer;

    //! Reference to the element.
    typedef typename Traits::reference reference;

    //! Size type.
    typedef typename Traits::size_type size_type;

    //! Difference type.
    typedef typename Traits::difference_type difference_type;

// Member variables

    //! The circular buffer where the iterator points to.
    const Buff* m_buff;

    //! An internal iterator.
    pointer m_it;

// Construction & assignment

    // Default copy constructor.

    //! Default constructor.
    iterator() : m_buff(0), m_it(0) {}

#if BOOST_CB_ENABLE_DEBUG

    //! Copy constructor (used for converting from a non-const to a const iterator).
    iterator(const nonconst_self& it) : debug_iterator_base(it), m_buff(it.m_buff), m_it(it.m_it) {}

    //! Internal constructor.
    /*!
        \note This constructor is not intended to be used directly by the user.
    */
    iterator(const Buff* cb, const pointer p) : debug_iterator_base(cb), m_buff(cb), m_it(p) {}

#else

    iterator(const nonconst_self& it) : m_buff(it.m_buff), m_it(it.m_it) {}

    iterator(const Buff* cb, const pointer p) : m_buff(cb), m_it(p) {}

#endif // #if BOOST_CB_ENABLE_DEBUG

    //! Assign operator.
    iterator& operator = (const iterator& it) {
        if (this == &it)
            return *this;
#if BOOST_CB_ENABLE_DEBUG
        debug_iterator_base::operator =(it);
#endif // #if BOOST_CB_ENABLE_DEBUG
        m_buff = it.m_buff;
        m_it = it.m_it;
        return *this;
    }

// Random access iterator methods

    //! Dereferencing operator.
    reference operator * () const {
        BOOST_CB_ASSERT(is_valid(m_buff)); // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(m_it != 0);        // check for iterator pointing to end()
        return *m_it;
    }

    //! Dereferencing operator.
    pointer operator -> () const { return &(operator*()); }

    //! Difference operator.
    template <class Traits0>
    difference_type operator - (const iterator<Buff, Traits0>& it) const {
        BOOST_CB_ASSERT(is_valid(m_buff));    // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(it.is_valid(m_buff)); // check for uninitialized or invalidated iterator
        return linearize_pointer(*this) - linearize_pointer(it);
    }

    //! Increment operator (prefix).
    iterator& operator ++ () {
        BOOST_CB_ASSERT(is_valid(m_buff)); // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(m_it != 0);        // check for iterator pointing to end()
        m_buff->increment(m_it);
        if (m_it == m_buff->m_last)
            m_it = 0;
        return *this;
    }

    //! Increment operator (postfix).
    iterator operator ++ (int) {
        iterator<Buff, Traits> tmp = *this;
        ++*this;
        return tmp;
    }

    //! Decrement operator (prefix).
    iterator& operator -- () {
        BOOST_CB_ASSERT(is_valid(m_buff));        // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(m_it != m_buff->m_first); // check for iterator pointing to begin()
        if (m_it == 0)
            m_it = m_buff->m_last;
        m_buff->decrement(m_it);
        return *this;
    }

    //! Decrement operator (postfix).
    iterator operator -- (int) {
        iterator<Buff, Traits> tmp = *this;
        --*this;
        return tmp;
    }

    //! Iterator addition.
    iterator& operator += (difference_type n) {
        BOOST_CB_ASSERT(is_valid(m_buff)); // check for uninitialized or invalidated iterator
        if (n > 0) {
            BOOST_CB_ASSERT(m_buff->end() - *this >= n); // check for too large n
            m_it = m_buff->add(m_it, n);
            if (m_it == m_buff->m_last)
                m_it = 0;
        } else if (n < 0) {
            *this -= -n;
        }
        return *this;
    }

    //! Iterator addition.
    iterator operator + (difference_type n) const { return iterator<Buff, Traits>(*this) += n; }

    //! Iterator subtraction.
    iterator& operator -= (difference_type n) {
        BOOST_CB_ASSERT(is_valid(m_buff)); // check for uninitialized or invalidated iterator
        if (n > 0) {
            BOOST_CB_ASSERT(*this - m_buff->begin() >= n); // check for too large n
            m_it = m_buff->sub(m_it == 0 ? m_buff->m_last : m_it, n);
        } else if (n < 0) {
            *this += -n;
        }
        return *this;
    }

    //! Iterator subtraction.
    iterator operator - (difference_type n) const { return iterator<Buff, Traits>(*this) -= n; }

    //! Element access operator.
    reference operator [] (difference_type n) const { return *(*this + n); }

// Equality & comparison

    //! Equality.
    template <class Traits0>
    bool operator == (const iterator<Buff, Traits0>& it) const {
        BOOST_CB_ASSERT(is_valid(m_buff));    // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(it.is_valid(m_buff)); // check for uninitialized or invalidated iterator
        return m_it == it.m_it;
    }

    //! Inequality.
    template <class Traits0>
    bool operator != (const iterator<Buff, Traits0>& it) const {
        BOOST_CB_ASSERT(is_valid(m_buff));    // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(it.is_valid(m_buff)); // check for uninitialized or invalidated iterator
        return m_it != it.m_it;
    }

    //! Less.
    template <class Traits0>
    bool operator < (const iterator<Buff, Traits0>& it) const {
        BOOST_CB_ASSERT(is_valid(m_buff));    // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(it.is_valid(m_buff)); // check for uninitialized or invalidated iterator
        return linearize_pointer(*this) < linearize_pointer(it);
    }

    //! Greater.
    template <class Traits0>
    bool operator > (const iterator<Buff, Traits0>& it) const { return it < *this; }

    //! Less or equal.
    template <class Traits0>
    bool operator <= (const iterator<Buff, Traits0>& it) const { return !(it < *this); }

    //! Greater or equal.
    template <class Traits0>
    bool operator >= (const iterator<Buff, Traits0>& it) const { return !(*this < it); }

// Helpers

    //! Get a pointer which would point to the same element as the iterator in case the circular buffer is linearized.
    template <class Traits0>
    typename Traits0::pointer linearize_pointer(const iterator<Buff, Traits0>& it) const {
        return it.m_it == 0 ? m_buff->m_buff + m_buff->size() :
            (it.m_it < m_buff->m_first ? it.m_it + (m_buff->m_end - m_buff->m_first)
                : m_buff->m_buff + (it.m_it - m_buff->m_first));
    }
};

//! Iterator addition.
template <class Buff, class Traits>
inline iterator<Buff, Traits>
operator + (typename Traits::difference_type n, const iterator<Buff, Traits>& it) {
    return it + n;
}

/*!
    \fn ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator dest)
    \brief Equivalent of <code>std::uninitialized_copy</code> but with explicit specification of value type.
*/
template<class InputIterator, class ForwardIterator, class Alloc>
inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator dest, Alloc& a) {
    ForwardIterator next = dest;
    BOOST_TRY {
        for (; first != last; ++first, ++dest)
            allocator_traits<Alloc>::construct(a, boost::to_address(dest), *first);
    } BOOST_CATCH(...) {
        for (; next != dest; ++next)
            allocator_traits<Alloc>::destroy(a, boost::to_address(next));
        BOOST_RETHROW
    }
    BOOST_CATCH_END
    return dest;
}

template<class InputIterator, class ForwardIterator, class Alloc>
ForwardIterator uninitialized_move_if_noexcept_impl(InputIterator first, InputIterator last, ForwardIterator dest, Alloc& a,
    true_type) {
    for (; first != last; ++first, ++dest)
        allocator_traits<Alloc>::construct(a, boost::to_address(dest), boost::move(*first));
    return dest;
}

template<class InputIterator, class ForwardIterator, class Alloc>
ForwardIterator uninitialized_move_if_noexcept_impl(InputIterator first, InputIterator last, ForwardIterator dest, Alloc& a,
    false_type) {
    return uninitialized_copy(first, last, dest, a);
}

/*!
    \fn ForwardIterator uninitialized_move_if_noexcept(InputIterator first, InputIterator last, ForwardIterator dest)
    \brief Equivalent of <code>std::uninitialized_copy</code> but with explicit specification of value type and moves elements if they have noexcept move constructors.
*/
template<class InputIterator, class ForwardIterator, class Alloc>
ForwardIterator uninitialized_move_if_noexcept(InputIterator first, InputIterator last, ForwardIterator dest, Alloc& a) {
    typedef typename boost::is_nothrow_move_constructible<typename allocator_traits<Alloc>::value_type>::type tag_t;
    return uninitialized_move_if_noexcept_impl(first, last, dest, a, tag_t());
}

/*!
    \fn void uninitialized_fill_n_with_alloc(ForwardIterator first, Diff n, const T& item, Alloc& alloc)
    \brief Equivalent of <code>std::uninitialized_fill_n</code> with allocator.
*/
template<class ForwardIterator, class Diff, class T, class Alloc>
inline void uninitialized_fill_n_with_alloc(ForwardIterator first, Diff n, const T& item, Alloc& alloc) {
    ForwardIterator next = first;
    BOOST_TRY {
        for (; n > 0; ++first, --n)
            allocator_traits<Alloc>::construct(alloc, boost::to_address(first), item);
    } BOOST_CATCH(...) {
        for (; next != first; ++next)
            allocator_traits<Alloc>::destroy(alloc, boost::to_address(next));
        BOOST_RETHROW
    }
    BOOST_CATCH_END
}

} // namespace cb_details

} // namespace boost

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif

#endif // #if !defined(BOOST_CIRCULAR_BUFFER_DETAILS_HPP)

/* details.hpp
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
*/
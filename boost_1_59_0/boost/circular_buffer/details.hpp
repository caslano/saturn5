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
#include <boost/core/allocator_access.hpp>
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

template <class Alloc> struct nonconst_traits;

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
template <class Alloc>
struct const_traits {
    // Basic types
    typedef typename Alloc::value_type value_type;
    typedef typename boost::allocator_const_pointer<Alloc>::type pointer;
    typedef const value_type& reference;
    typedef typename boost::allocator_size_type<Alloc>::type size_type;
    typedef typename boost::allocator_difference_type<Alloc>::type difference_type;

    // Non-const traits
    typedef nonconst_traits<Alloc> nonconst_self;
};

/*!
    \struct nonconst_traits
    \brief Defines the data types for a non-const iterator.
*/
template <class Alloc>
struct nonconst_traits {
    // Basic types
    typedef typename Alloc::value_type value_type;
    typedef typename boost::allocator_pointer<Alloc>::type pointer;
    typedef value_type& reference;
    typedef typename boost::allocator_size_type<Alloc>::type size_type;
    typedef typename boost::allocator_difference_type<Alloc>::type difference_type;

    // Non-const traits
    typedef nonconst_traits<Alloc> nonconst_self;
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
    typedef typename boost::allocator_size_type<Alloc>::type size_type;
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
            boost::allocator_construct(a, boost::to_address(dest), *first);
    } BOOST_CATCH(...) {
        for (; next != dest; ++next)
            boost::allocator_destroy(a, boost::to_address(next));
        BOOST_RETHROW
    }
    BOOST_CATCH_END
    return dest;
}

template<class InputIterator, class ForwardIterator, class Alloc>
ForwardIterator uninitialized_move_if_noexcept_impl(InputIterator first, InputIterator last, ForwardIterator dest, Alloc& a,
    true_type) {
    for (; first != last; ++first, ++dest)
        boost::allocator_construct(a, boost::to_address(dest), boost::move(*first));
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
    typedef typename boost::is_nothrow_move_constructible<typename Alloc::value_type>::type tag_t;
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
            boost::allocator_construct(alloc, boost::to_address(first), item);
    } BOOST_CATCH(...) {
        for (; next != first; ++next)
            boost::allocator_destroy(alloc, boost::to_address(next));
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
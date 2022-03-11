// Implementation of the circular buffer adaptor.

// Copyright (c) 2003-2008 Jan Gaspar
// Copyright (c) 2013  Paul A. Bristow // Doxygen comments changed for new version of documentation.
// Copyright (c) 2013  Antony Polukhin // Move semantics implementation.

// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_CIRCULAR_BUFFER_SPACE_OPTIMIZED_HPP)
#define BOOST_CIRCULAR_BUFFER_SPACE_OPTIMIZED_HPP

#if defined(_MSC_VER)
    #pragma once
#endif

#include <boost/type_traits/is_same.hpp>
#include <boost/config/workaround.hpp>

namespace boost {

/*!
    \class circular_buffer_space_optimized
    \brief Space optimized circular buffer container adaptor. 
           <code>T</code> must be a copyable class or must have an noexcept move constructor
           and move assignment operator.
*/
template <class T, class Alloc>
class circular_buffer_space_optimized :
/*! \cond */
#if BOOST_CB_ENABLE_DEBUG
public
#endif
/*! \endcond */
circular_buffer<T, Alloc> {
public:
// Typedefs

    typedef typename circular_buffer<T, Alloc>::value_type value_type;
    typedef typename circular_buffer<T, Alloc>::pointer pointer;
    typedef typename circular_buffer<T, Alloc>::const_pointer const_pointer;
    typedef typename circular_buffer<T, Alloc>::reference reference;
    typedef typename circular_buffer<T, Alloc>::const_reference const_reference;
    typedef typename circular_buffer<T, Alloc>::size_type size_type;
    typedef typename circular_buffer<T, Alloc>::difference_type difference_type;
    typedef typename circular_buffer<T, Alloc>::allocator_type allocator_type;
    typedef typename circular_buffer<T, Alloc>::const_iterator const_iterator;
    typedef typename circular_buffer<T, Alloc>::iterator iterator;
    typedef typename circular_buffer<T, Alloc>::const_reverse_iterator const_reverse_iterator;
    typedef typename circular_buffer<T, Alloc>::reverse_iterator reverse_iterator;
    typedef typename circular_buffer<T, Alloc>::array_range array_range;
    typedef typename circular_buffer<T, Alloc>::const_array_range const_array_range;
    typedef typename circular_buffer<T, Alloc>::param_value_type param_value_type;
    typedef typename circular_buffer<T, Alloc>::rvalue_type rvalue_type;
    //typedef typename circular_buffer<T, Alloc>::return_value_type return_value_type;

/* <pre> is not passed through to html or pdf. So <br> is used in code section below.  Ugly :-(
Ideally want a link to capacity_control, but this would require include details
and this would expose all the functions in details.
There must be a better way of doing this.
*/

    /*! Capacity controller of the space optimized circular buffer.

    \see capacity_control in details.hpp.
<p>
<code>
class capacity_control<br>
{<br>
   size_type m_capacity;  // Available capacity.<br>
   size_type m_min_capacity; // Minimum capacity.<br>
public:<br>
   capacity_control(size_type capacity, size_type min_capacity = 0)<br>
   : m_capacity(capacity), m_min_capacity(min_capacity)<br>
     {};<br>
   size_type %capacity() const { return m_capacity; }<br>
   size_type min_capacity() const { return m_min_capacity; }<br>
   operator size_type() const { return m_capacity; }<br>
};<br>
</code>
</p>


  <p>Always
    <code>capacity >= min_capacity</code>.
  </p>
  <p>
    The <code>capacity()</code> represents the capacity
    of the <code>circular_buffer_space_optimized</code> and
    the <code>min_capacity()</code> determines the minimal allocated size of its internal buffer.
 </p>
 <p>The converting constructor of the <code>capacity_control</code> allows implicit conversion from
  <code>size_type</code>-like types which ensures compatibility of creating an instance of the
  <code>circular_buffer_space_optimized</code> with other STL containers.

  On the other hand the operator <code>%size_type()</code>
  provides implicit conversion to the <code>size_type</code> which allows to treat the
  capacity of the <code>circular_buffer_space_optimized</code> the same way as in the
  <code>circular_buffer</a></code>.
</p>
    */
    typedef cb_details::capacity_control<size_type> capacity_type;

// Inherited

    using circular_buffer<T, Alloc>::get_allocator;
    using circular_buffer<T, Alloc>::begin;
    using circular_buffer<T, Alloc>::end;
    using circular_buffer<T, Alloc>::rbegin;
    using circular_buffer<T, Alloc>::rend;
    using circular_buffer<T, Alloc>::at;
    using circular_buffer<T, Alloc>::front;
    using circular_buffer<T, Alloc>::back;
    using circular_buffer<T, Alloc>::array_one;
    using circular_buffer<T, Alloc>::array_two;
    using circular_buffer<T, Alloc>::linearize;
    using circular_buffer<T, Alloc>::is_linearized;
    using circular_buffer<T, Alloc>::rotate;
    using circular_buffer<T, Alloc>::size;
    using circular_buffer<T, Alloc>::max_size;
    using circular_buffer<T, Alloc>::empty;

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    reference operator [] (size_type n) { return circular_buffer<T, Alloc>::operator[](n); }
    const_reference operator [] (size_type n) const { return circular_buffer<T, Alloc>::operator[](n); }
#else
    using circular_buffer<T, Alloc>::operator[];
#endif

private:
// Member variables

    //! The capacity controller of the space optimized circular buffer.
    capacity_type m_capacity_ctrl;

public:
// Overridden

    //! Is the <code>circular_buffer_space_optimized</code> full?
    /*!
        \return <code>true</code> if the number of elements stored in the <code>circular_buffer_space_optimized</code>
                equals the capacity of the <code>circular_buffer_space_optimized</code>; <code>false</code> otherwise.
        \throws Nothing.
        \par Exception Safety
             No-throw.
        \par Iterator Invalidation
             Does not invalidate any iterators.
        \par Complexity
             Constant (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>empty()</code>
    */
    bool full() const BOOST_NOEXCEPT { return m_capacity_ctrl == size(); }

    /*! \brief Get the maximum number of elements which can be inserted into the
               <code>circular_buffer_space_optimized</code> without overwriting any of already stored elements.
        \return <code>capacity().%capacity() - size()</code>
        \throws Nothing.
        \par Exception Safety
             No-throw.
        \par Iterator Invalidation
             Does not invalidate any iterators.
        \par Complexity
             Constant (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>capacity()</code>, <code>size()</code>, <code>max_size()</code>
    */
    size_type reserve() const BOOST_NOEXCEPT { return m_capacity_ctrl - size(); }

    //! Get the capacity of the <code>circular_buffer_space_optimized</code>.
    /*!
        \return The capacity controller representing the maximum number of elements which can be stored in the
                <code>circular_buffer_space_optimized</code> and the minimal allocated size of the internal buffer.
        \throws Nothing.
        \par Exception Safety
             No-throw.
        \par Iterator Invalidation
             Does not invalidate any iterators.
        \par Complexity
             Constant (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>reserve()</code>, <code>size()</code>, <code>max_size()</code>,
            <code>set_capacity(const capacity_type&)</code>
    */
    const capacity_type& capacity() const BOOST_NOEXCEPT { return m_capacity_ctrl; }

#if defined(BOOST_CB_TEST)

    // Return the current capacity of the adapted circular buffer.
    /*
       \note This method is not intended to be used directly by the user.
             It is defined only for testing purposes.
    */
    size_type internal_capacity() const BOOST_NOEXCEPT { return circular_buffer<T, Alloc>::capacity(); }

#endif // #if defined(BOOST_CB_TEST)

    /*! \brief Change the capacity (and the minimal guaranteed amount of allocated memory) of the
               <code>circular_buffer_space_optimized</code>.
        \post <code>capacity() == capacity_ctrl \&\& size() \<= capacity_ctrl.capacity()</code><br><br>
              If the current number of elements stored in the <code>circular_buffer_space_optimized</code> is greater
              than the desired new capacity then number of <code>[size() - capacity_ctrl.capacity()]</code> <b>last</b>
              elements will be removed and the new size will be equal to <code>capacity_ctrl.capacity()</code>.<br><br>
              If the current number of elements stored in the <code>circular_buffer_space_optimized</code> is lower
              than the new capacity then the amount of allocated memory in the internal buffer may be accommodated as
              necessary but it will never drop below <code>capacity_ctrl.min_capacity()</code>.
        \param capacity_ctrl The new capacity controller.
        \throws "An allocation error" if memory is exhausted, (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
        \par Exception Safety
             Strong.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in <code>min[size(), capacity_ctrl.%capacity()]</code>).
        \note To explicitly clear the extra allocated memory use the <b>shrink-to-fit</b> technique:<br><br>
              <code>%boost::%circular_buffer_space_optimized\<int\> cb(1000);<br>
              ...<br>
              %boost::%circular_buffer_space_optimized\<int\>(cb).swap(cb);</code><br><br>
              For more information about the shrink-to-fit technique in STL see
              <a href="http://www.gotw.ca/gotw/054.htm">http://www.gotw.ca/gotw/054.htm</a>.
        \sa <code>rset_capacity(const capacity_type&)</code>,
            <code>\link resize() resize(size_type, const_reference)\endlink</code>
    */
    void set_capacity(const capacity_type& capacity_ctrl) {
        m_capacity_ctrl = capacity_ctrl;
        if (capacity_ctrl < size()) {
            iterator e = end();
            circular_buffer<T, Alloc>::erase(e - (size() - capacity_ctrl), e);
        }
        adjust_min_capacity();
    }

    //! Change the size of the <code>circular_buffer_space_optimized</code>.
    /*!
        \post <code>size() == new_size \&\& capacity().%capacity() >= new_size</code><br><br>
              If the new size is greater than the current size, copies of <code>item</code> will be inserted at the
              <b>back</b> of the of the <code>circular_buffer_space_optimized</code> in order to achieve the desired
              size. In the case the resulting size exceeds the current capacity the capacity will be set to
              <code>new_size</code>.<br><br>
              If the current number of elements stored in the <code>circular_buffer_space_optimized</code> is greater
              than the desired new size then number of <code>[size() - new_size]</code> <b>last</b> elements will be
              removed. (The capacity will remain unchanged.)<br><br>
              The amount of allocated memory in the internal buffer may be accommodated as necessary.
        \param new_size The new size.
        \param item The element the <code>circular_buffer_space_optimized</code> will be filled with in order to gain
                    the requested size. (See the <i>Effect</i>.)
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the new size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link rresize() rresize(size_type, const_reference)\endlink</code>,
            <code>set_capacity(const capacity_type&)</code>
    */
    void resize(size_type new_size, param_value_type item = value_type()) {
        if (new_size > size()) {
            if (new_size > m_capacity_ctrl)
                m_capacity_ctrl = capacity_type(new_size, m_capacity_ctrl.min_capacity());
            insert(end(), new_size - size(), item);
        } else {
            iterator e = end();
            erase(e - (size() - new_size), e);
        }
    }

    /*! \brief Change the capacity (and the minimal guaranteed amount of allocated memory) of the
               <code>circular_buffer_space_optimized</code>.
        \post <code>capacity() == capacity_ctrl \&\& size() \<= capacity_ctrl</code><br><br>
              If the current number of elements stored in the <code>circular_buffer_space_optimized</code> is greater
              than the desired new capacity then number of <code>[size() - capacity_ctrl.capacity()]</code>
              <b>first</b> elements will be removed and the new size will be equal to
              <code>capacity_ctrl.capacity()</code>.<br><br>
              If the current number of elements stored in the <code>circular_buffer_space_optimized</code> is lower
              than the new capacity then the amount of allocated memory in the internal buffer may be accommodated as
              necessary but it will never drop below <code>capacity_ctrl.min_capacity()</code>.
        \param capacity_ctrl The new capacity controller.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
        \par Exception Safety
             Strong.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in <code>min[size(), capacity_ctrl.%capacity()]</code>).
        \sa <code>set_capacity(const capacity_type&)</code>,
            <code>\link rresize() rresize(size_type, const_reference)\endlink</code>
    */
    void rset_capacity(const capacity_type& capacity_ctrl) {
        m_capacity_ctrl = capacity_ctrl;
        if (capacity_ctrl < size()) {
            iterator b = begin();
            circular_buffer<T, Alloc>::rerase(b, b + (size() - capacity_ctrl));
        }
        adjust_min_capacity();
    }

    //! Change the size of the <code>circular_buffer_space_optimized</code>.
    /*!
        \post <code>size() == new_size \&\& capacity().%capacity() >= new_size</code><br><br>
              If the new size is greater than the current size, copies of <code>item</code> will be inserted at the
              <b>front</b> of the of the <code>circular_buffer_space_optimized</code> in order to achieve the desired
              size. In the case the resulting size exceeds the current capacity the capacity will be set to
              <code>new_size</code>.<br><br>
              If the current number of elements stored in the <code>circular_buffer_space_optimized</code> is greater
              than the desired new size then number of <code>[size() - new_size]</code> <b>first</b> elements will be
              removed. (The capacity will remain unchanged.)<br><br>
              The amount of allocated memory in the internal buffer may be accommodated as necessary.
        \param new_size The new size.
        \param item The element the <code>circular_buffer_space_optimized</code> will be filled with in order to gain
                    the requested size. (See the <i>Effect</i>.)
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the new size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link resize() resize(size_type, const_reference)\endlink</code>,
            <code>rset_capacity(const capacity_type&)</code>
    */
    void rresize(size_type new_size, param_value_type item = value_type()) {
        if (new_size > size()) {
            if (new_size > m_capacity_ctrl)
                m_capacity_ctrl = capacity_type(new_size, m_capacity_ctrl.min_capacity());
            rinsert(begin(), new_size - size(), item);
        } else {
            rerase(begin(), end() - new_size);
        }
    }

    //! Create an empty space optimized circular buffer with zero capacity.
    /*!
        \post <code>capacity().%capacity() == 0 \&\& capacity().min_capacity() == 0 \&\& size() == 0</code>
        \param alloc The allocator.
        \throws Nothing.
        \par Complexity
             Constant.
        \warning Since Boost version 1.36 the behaviour of this constructor has changed. Now it creates a space
                 optimized circular buffer with zero capacity.
    */
    explicit circular_buffer_space_optimized(const allocator_type& alloc = allocator_type()) BOOST_NOEXCEPT
    : circular_buffer<T, Alloc>(0, alloc)
    , m_capacity_ctrl(0) {}

    //! Create an empty space optimized circular buffer with the specified capacity.
    /*!
        \post <code>capacity() == capacity_ctrl \&\& size() == 0</code><br><br>
              The amount of allocated memory in the internal buffer is <code>capacity_ctrl.min_capacity()</code>.
        \param capacity_ctrl The capacity controller representing the maximum number of elements which can be stored in
                             the <code>circular_buffer_space_optimized</code> and the minimal allocated size of the
                             internal buffer.
        \param alloc The allocator.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
        \par Complexity
             Constant.
    */
    explicit circular_buffer_space_optimized(capacity_type capacity_ctrl,
        const allocator_type& alloc = allocator_type())
    : circular_buffer<T, Alloc>(capacity_ctrl.min_capacity(), alloc)
    , m_capacity_ctrl(capacity_ctrl) {}

    /*! \brief Create a full space optimized circular buffer with the specified capacity filled with
               <code>capacity_ctrl.%capacity()</code> copies of <code>item</code>.
        \post <code>capacity() == capacity_ctrl \&\& full() \&\& (*this)[0] == item \&\& (*this)[1] == item \&\& ...
              \&\& (*this) [capacity_ctrl.%capacity() - 1] == item </code><br><br>
              The amount of allocated memory in the internal buffer is <code>capacity_ctrl.capacity()</code>.
        \param capacity_ctrl The capacity controller representing the maximum number of elements which can be stored in
                             the <code>circular_buffer_space_optimized</code> and the minimal allocated size of the
                             internal buffer.
        \param item The element the created <code>circular_buffer_space_optimized</code> will be filled with.
        \param alloc The allocator.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
        \throws Whatever <code>T::T(const T&)</code> throws.
        \par Complexity
             Linear (in the <code>capacity_ctrl.%capacity()</code>).
    */
    circular_buffer_space_optimized(capacity_type capacity_ctrl, param_value_type item,
        const allocator_type& alloc = allocator_type())
    : circular_buffer<T, Alloc>(capacity_ctrl.capacity(), item, alloc)
    , m_capacity_ctrl(capacity_ctrl) {}

    /*! \brief Create a space optimized circular buffer with the specified capacity filled with <code>n</code> copies
               of <code>item</code>.
        \pre <code>capacity_ctrl.%capacity() >= n</code>
        \post <code>capacity() == capacity_ctrl \&\& size() == n \&\& (*this)[0] == item \&\& (*this)[1] == item
              \&\& ... \&\& (*this)[n - 1] == item</code><br><br>
              The amount of allocated memory in the internal buffer is
              <code>max[n, capacity_ctrl.min_capacity()]</code>.
        \param capacity_ctrl The capacity controller representing the maximum number of elements which can be stored in
                             the <code>circular_buffer_space_optimized</code> and the minimal allocated size of the
                             internal buffer.
        \param n The number of elements the created <code>circular_buffer_space_optimized</code> will be filled with.
        \param item The element the created <code>circular_buffer_space_optimized</code> will be filled with.
        \param alloc The allocator.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
        \par Complexity
             Linear (in the <code>n</code>).
    */
    circular_buffer_space_optimized(capacity_type capacity_ctrl, size_type n, param_value_type item,
        const allocator_type& alloc = allocator_type())
    : circular_buffer<T, Alloc>(init_capacity(capacity_ctrl, n), n, item, alloc)
    , m_capacity_ctrl(capacity_ctrl) {}

    //! The copy constructor.
    /*!
        Creates a copy of the specified <code>circular_buffer_space_optimized</code>.
        \post <code>*this == cb</code><br><br>
              The amount of allocated memory in the internal buffer is <code>cb.size()</code>.
        \param cb The <code>circular_buffer_space_optimized</code> to be copied.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
        \par Complexity
             Linear (in the size of <code>cb</code>).
    */
    circular_buffer_space_optimized(const circular_buffer_space_optimized<T, Alloc>& cb)
    : circular_buffer<T, Alloc>(cb.begin(), cb.end(), cb.get_allocator())
    , m_capacity_ctrl(cb.m_capacity_ctrl) {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    //! The move constructor.
    /*! \brief Move constructs a <code>circular_buffer_space_optimized</code> from <code>cb</code>, 
                leaving <code>cb</code> empty.
        \pre C++ compiler with rvalue references support.
        \post <code>cb.empty()</code>
        \param cb <code>circular_buffer</code> to 'steal' value from.
        \throws Nothing.
        \par Constant.
    */
    circular_buffer_space_optimized(circular_buffer_space_optimized<T, Alloc>&& cb) BOOST_NOEXCEPT
    : circular_buffer<T, Alloc>()
    , m_capacity_ctrl(0) {
        cb.swap(*this);
    }
#endif // BOOST_NO_CXX11_RVALUE_REFERENCES

    //! Create a full space optimized circular buffer filled with a copy of the range.
    /*!
        \pre Valid range <code>[first, last)</code>.<br>
             <code>first</code> and <code>last</code> have to meet the requirements of
             <a href="https://www.boost.org/sgi/stl/InputIterator.html">InputIterator</a>.
        \post <code>capacity().%capacity() == std::distance(first, last) \&\& capacity().min_capacity() == 0 \&\&
              full() \&\& (*this)[0]== *first \&\& (*this)[1] == *(first + 1) \&\& ... \&\&
              (*this)[std::distance(first, last) - 1] == *(last - 1)</code><br><br>
              The amount of allocated memory in the internal buffer is <code>std::distance(first, last)</code>.
        \param first The beginning of the range to be copied.
        \param last The end of the range to be copied.
        \param alloc The allocator.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept 
                and <code>InputIterator</code> is a move iterator.
        \par Complexity
             Linear (in the <code>std::distance(first, last)</code>).
    */
    template <class InputIterator>
    circular_buffer_space_optimized(InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type())
    : circular_buffer<T, Alloc>(first, last, alloc)
    , m_capacity_ctrl(circular_buffer<T, Alloc>::capacity()) {}

    /*! \brief Create a space optimized circular buffer with the specified capacity (and the minimal guaranteed amount
               of allocated memory) filled with a copy of the range.
        \pre Valid range <code>[first, last)</code>.<br>
             <code>first</code> and <code>last</code> have to meet the requirements of
             <a href="https://www.boost.org/sgi/stl/InputIterator.html">InputIterator</a>.
        \post <code>capacity() == capacity_ctrl \&\& size() \<= std::distance(first, last) \&\& (*this)[0]==
              *(last - capacity_ctrl.%capacity()) \&\& (*this)[1] == *(last - capacity_ctrl.%capacity() + 1) \&\& ...
              \&\& (*this)[capacity_ctrl.%capacity() - 1] == *(last - 1)</code><br><br>
              If the number of items to be copied from the range <code>[first, last)</code> is greater than the
              specified <code>capacity_ctrl.%capacity()</code> then only elements from the range
              <code>[last - capacity_ctrl.%capacity(), last)</code> will be copied.<br><br>
              The amount of allocated memory in the internal buffer is <code>max[capacity_ctrl.min_capacity(),
              min[capacity_ctrl.%capacity(), std::distance(first, last)]]</code>.
        \param capacity_ctrl The capacity controller representing the maximum number of elements which can be stored in
                             the <code>circular_buffer_space_optimized</code> and the minimal allocated size of the
                             internal buffer.
        \param first The beginning of the range to be copied.
        \param last The end of the range to be copied.
        \param alloc The allocator.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
        \par Complexity
             Linear (in <code>std::distance(first, last)</code>; in
             <code>min[capacity_ctrl.%capacity(), std::distance(first, last)]</code> if the <code>InputIterator</code>
             is a <a href="https://www.boost.org/sgi/stl/RandomAccessIterator.html">RandomAccessIterator</a>).
    */
    template <class InputIterator>
    circular_buffer_space_optimized(capacity_type capacity_ctrl, InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type())
    : circular_buffer<T, Alloc>(
        init_capacity(capacity_ctrl, first, last, is_integral<InputIterator>()),
        first, last, alloc)
    , m_capacity_ctrl(capacity_ctrl) {
        reduce_capacity(
            is_same< BOOST_DEDUCED_TYPENAME std::iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag >());
    }

#if defined(BOOST_CB_NEVER_DEFINED)
// This section will never be compiled - the default destructor will be generated instead.
// Declared only for documentation purpose.

    //! The destructor.
    /*!
        Destroys the <code>circular_buffer_space_optimized</code>.
        \throws Nothing.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (including
             iterators equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>clear()</code>
    */
    ~circular_buffer_space_optimized();

    //! no-comment
    void erase_begin(size_type n);

    //! no-comment
    void erase_end(size_type n);

#endif // #if defined(BOOST_CB_NEVER_DEFINED)

    //! The assign operator.
    /*!
        Makes this <code>circular_buffer_space_optimized</code> to become a copy of the specified
        <code>circular_buffer_space_optimized</code>.
        \post <code>*this == cb</code><br><br>
              The amount of allocated memory in the internal buffer is <code>cb.size()</code>.
        \param cb The <code>circular_buffer_space_optimized</code> to be copied.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
        \throws Whatever <code>T::T(const T&)</code> throws.
        \par Exception Safety
             Strong.
        \par Iterator Invalidation
             Invalidates all iterators pointing to this <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of <code>cb</code>).
        \sa <code>\link assign(size_type, param_value_type) assign(size_type, const_reference)\endlink</code>,
            <code>\link assign(capacity_type, size_type, param_value_type)
            assign(capacity_type, size_type, const_reference)\endlink</code>,
            <code>assign(InputIterator, InputIterator)</code>,
            <code>assign(capacity_type, InputIterator, InputIterator)</code>
    */
    circular_buffer_space_optimized<T, Alloc>& operator = (const circular_buffer_space_optimized<T, Alloc>& cb) {
        if (this == &cb)
            return *this;
        circular_buffer<T, Alloc>::assign(cb.begin(), cb.end());
        m_capacity_ctrl = cb.m_capacity_ctrl;
        return *this;
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    /*! \brief Move assigns content of <code>cb</code> to <code>*this</code>, leaving <code>cb</code> empty.
        \pre C++ compiler with rvalue references support.
        \post <code>cb.empty()</code>
        \param cb <code>circular_buffer</code> to 'steal' value from.
        \throws Nothing.
        \par Complexity
             Constant.
    */
    circular_buffer_space_optimized<T, Alloc>& operator = (circular_buffer_space_optimized<T, Alloc>&& cb) BOOST_NOEXCEPT {
        cb.swap(*this); // now `this` holds `cb`
        circular_buffer<T, Alloc>(get_allocator()) // temporary that holds initial `cb` allocator
            .swap(cb); // makes `cb` empty
        return *this;
    }
#endif // BOOST_NO_CXX11_RVALUE_REFERENCES


    //! Assign <code>n</code> items into the space optimized circular buffer.
    /*!
        The content of the <code>circular_buffer_space_optimized</code> will be removed and replaced with
        <code>n</code> copies of the <code>item</code>.
        \post <code>capacity().%capacity() == n \&\& capacity().min_capacity() == 0 \&\& size() == n \&\& (*this)[0] ==
              item \&\& (*this)[1] == item \&\& ... \&\& (*this) [n - 1] == item</code><br><br>
              The amount of allocated memory in the internal buffer is <code>n</code>.
        \param n The number of elements the <code>circular_buffer_space_optimized</code> will be filled with.
        \param item The element the <code>circular_buffer_space_optimized</code> will be filled with.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the <code>n</code>).
        \sa <code>\link operator=(const circular_buffer_space_optimized&) operator=\endlink</code>,
            <code>\link assign(capacity_type, size_type, param_value_type)
            assign(capacity_type, size_type, const_reference)\endlink</code>,
            <code>assign(InputIterator, InputIterator)</code>,
            <code>assign(capacity_type, InputIterator, InputIterator)</code>
    */
    void assign(size_type n, param_value_type item) {
        circular_buffer<T, Alloc>::assign(n, item);
        m_capacity_ctrl = capacity_type(n);
    }

    //! Assign <code>n</code> items into the space optimized circular buffer specifying the capacity.
    /*!
        The capacity of the <code>circular_buffer_space_optimized</code> will be set to the specified value and the
        content of the <code>circular_buffer_space_optimized</code> will be removed and replaced with <code>n</code>
        copies of the <code>item</code>.
        \pre <code>capacity_ctrl.%capacity() >= n</code>
        \post <code>capacity() == capacity_ctrl \&\& size() == n \&\& (*this)[0] == item \&\& (*this)[1] == item
              \&\& ... \&\& (*this) [n - 1] == item </code><br><br>
              The amount of allocated memory will be <code>max[n, capacity_ctrl.min_capacity()]</code>.
        \param capacity_ctrl The new capacity controller.
        \param n The number of elements the <code>circular_buffer_space_optimized</code> will be filled with.
        \param item The element the <code>circular_buffer_space_optimized</code> will be filled with.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the <code>n</code>).
        \sa <code>\link operator=(const circular_buffer_space_optimized&) operator=\endlink</code>,
            <code>\link assign(size_type, param_value_type) assign(size_type, const_reference)\endlink</code>,
            <code>assign(InputIterator, InputIterator)</code>,
            <code>assign(capacity_type, InputIterator, InputIterator)</code>
    */
    void assign(capacity_type capacity_ctrl, size_type n, param_value_type item) {
       BOOST_CB_ASSERT(capacity_ctrl.capacity() >= n); // check for new capacity lower than n
       circular_buffer<T, Alloc>::assign((std::max)(capacity_ctrl.min_capacity(), n), n, item);
       m_capacity_ctrl = capacity_ctrl;
    }

    //! Assign a copy of the range into the space optimized circular buffer.
    /*!
        The content of the <code>circular_buffer_space_optimized</code> will be removed and replaced with copies of
        elements from the specified range.
        \pre Valid range <code>[first, last)</code>.<br>
             <code>first</code> and <code>last</code> have to meet the requirements of
             <a href="https://www.boost.org/sgi/stl/InputIterator.html">InputIterator</a>.
        \post <code>capacity().%capacity() == std::distance(first, last) \&\& capacity().min_capacity() == 0 \&\&
              size() == std::distance(first, last) \&\& (*this)[0]== *first \&\& (*this)[1] == *(first + 1) \&\& ...
              \&\& (*this)[std::distance(first, last) - 1] == *(last - 1)</code><br><br>
              The amount of allocated memory in the internal buffer is <code>std::distance(first, last)</code>.
        \param first The beginning of the range to be copied.
        \param last The end of the range to be copied.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept and 
                <code>InputIterator</code> is a move iterator.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the <code>std::distance(first, last)</code>).
        \sa <code>\link operator=(const circular_buffer_space_optimized&) operator=\endlink</code>,
            <code>\link assign(size_type, param_value_type) assign(size_type, const_reference)\endlink</code>,
            <code>\link assign(capacity_type, size_type, param_value_type)
            assign(capacity_type, size_type, const_reference)\endlink</code>,
            <code>assign(capacity_type, InputIterator, InputIterator)</code>
    */
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last) {
        circular_buffer<T, Alloc>::assign(first, last);
        m_capacity_ctrl = capacity_type(circular_buffer<T, Alloc>::capacity());
    }

    //! Assign a copy of the range into the space optimized circular buffer specifying the capacity.
    /*!
        The capacity of the <code>circular_buffer_space_optimized</code> will be set to the specified value and the
        content of the <code>circular_buffer_space_optimized</code> will be removed and replaced with copies of
        elements from the specified range.
        \pre Valid range <code>[first, last)</code>.<br>
             <code>first</code> and <code>last</code> have to meet the requirements of
             <a href="https://www.boost.org/sgi/stl/InputIterator.html">InputIterator</a>.
        \post <code>capacity() == capacity_ctrl \&\& size() \<= std::distance(first, last) \&\&
             (*this)[0]== *(last - capacity) \&\& (*this)[1] == *(last - capacity + 1) \&\& ... \&\&
             (*this)[capacity - 1] == *(last - 1)</code><br><br>
             If the number of items to be copied from the range <code>[first, last)</code> is greater than the
             specified <code>capacity</code> then only elements from the range <code>[last - capacity, last)</code>
             will be copied.<br><br> The amount of allocated memory in the internal buffer is
             <code>max[std::distance(first, last), capacity_ctrl.min_capacity()]</code>.
        \param capacity_ctrl The new capacity controller.
        \param first The beginning of the range to be copied.
        \param last The end of the range to be copied.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept and 
                <code>InputIterator</code> is a move iterator.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in <code>std::distance(first, last)</code>; in
             <code>min[capacity_ctrl.%capacity(), std::distance(first, last)]</code> if the <code>InputIterator</code>
             is a <a href="https://www.boost.org/sgi/stl/RandomAccessIterator.html">RandomAccessIterator</a>).
        \sa <code>\link operator=(const circular_buffer_space_optimized&) operator=\endlink</code>,
            <code>\link assign(size_type, param_value_type) assign(size_type, const_reference)\endlink</code>,
            <code>\link assign(capacity_type, size_type, param_value_type)
            assign(capacity_type, size_type, const_reference)\endlink</code>,
            <code>assign(InputIterator, InputIterator)</code>
    */
    template <class InputIterator>
    void assign(capacity_type capacity_ctrl, InputIterator first, InputIterator last) {
       m_capacity_ctrl = capacity_ctrl;
       circular_buffer<T, Alloc>::assign(capacity_ctrl, first, last);
    }

    //! Swap the contents of two space-optimized circular-buffers.
    /*!
        \post <code>this</code> contains elements of <code>cb</code> and vice versa; the capacity and the amount of
              allocated memory in the internal buffer of <code>this</code> equal to the capacity and the amount of
              allocated memory of <code>cb</code> and vice versa.
        \param cb The <code>circular_buffer_space_optimized</code> whose content will be swapped.
        \throws Nothing.
        \par Exception Safety
             No-throw.
        \par Iterator Invalidation
             Invalidates all iterators of both <code>circular_buffer_space_optimized</code> containers. (On the other
             hand the iterators still point to the same elements but within another container. If you want to rely on
             this feature you have to turn the __debug_support off,
             otherwise an assertion will report an error if such invalidated iterator is used.)
        \par Complexity
             Constant (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>swap(circular_buffer<T, Alloc>&, circular_buffer<T, Alloc>&)</code>, 
            <code>swap(circular_buffer_space_optimized<T, Alloc>&, circular_buffer_space_optimized<T, Alloc>&)</code>


    */
    // Note link does not work right.  Asked on Doxygen forum for advice 23 May 2103.

    void swap(circular_buffer_space_optimized<T, Alloc>& cb) BOOST_NOEXCEPT {
        std::swap(m_capacity_ctrl, cb.m_capacity_ctrl);
        circular_buffer<T, Alloc>::swap(cb);
    }

    //! Insert a new element at the end of the space optimized circular buffer.
    /*!
        \post if <code>capacity().%capacity() > 0</code> then <code>back() == item</code><br>
              If the <code>circular_buffer_space_optimized</code> is full, the first element will be removed. If the
              capacity is <code>0</code>, nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param item The element to be inserted.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link push_front() push_front(const_reference)\endlink</code>, <code>pop_back()</code>,
            <code>pop_front()</code>
    */
    void push_back(param_value_type item) {
        check_low_capacity();
        circular_buffer<T, Alloc>::push_back(item);
    }

    //! Insert a new element at the end of the space optimized circular buffer.
    /*!
        \post if <code>capacity().%capacity() > 0</code> then <code>back() == item</code><br>
              If the <code>circular_buffer_space_optimized</code> is full, the first element will be removed. If the
              capacity is <code>0</code>, nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param item The element to be inserted.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link push_front() push_front(const_reference)\endlink</code>, <code>pop_back()</code>,
            <code>pop_front()</code>
    */
    void push_back(rvalue_type item) {
        check_low_capacity();
        circular_buffer<T, Alloc>::push_back(boost::move(item));
    }

    //! Insert a new element at the end of the space optimized circular buffer.
    /*!
        \post if <code>capacity().%capacity() > 0</code> then <code>back() == item</code><br>
              If the <code>circular_buffer_space_optimized</code> is full, the first element will be removed. If the
              capacity is <code>0</code>, nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T()</code> throws. 
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link push_front() push_front(const_reference)\endlink</code>, <code>pop_back()</code>,
            <code>pop_front()</code>
    */
    void push_back() {
        check_low_capacity();
        circular_buffer<T, Alloc>::push_back();
    }

    //! Insert a new element at the beginning of the space optimized circular buffer.
    /*!
        \post if <code>capacity().%capacity() > 0</code> then <code>front() == item</code><br>
              If the <code>circular_buffer_space_optimized</code> is full, the last element will be removed. If the
              capacity is <code>0</code>, nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param item The element to be inserted.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link push_back() push_back(const_reference)\endlink</code>, <code>pop_back()</code>,
            <code>pop_front()</code>
    */
    void push_front(param_value_type item) {
        check_low_capacity();
        circular_buffer<T, Alloc>::push_front(item);
    }

    //! Insert a new element at the beginning of the space optimized circular buffer.
    /*!
        \post if <code>capacity().%capacity() > 0</code> then <code>front() == item</code><br>
              If the <code>circular_buffer_space_optimized</code> is full, the last element will be removed. If the
              capacity is <code>0</code>, nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param item The element to be inserted.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link push_back() push_back(const_reference)\endlink</code>, <code>pop_back()</code>,
            <code>pop_front()</code>
    */
    void push_front(rvalue_type item) {
        check_low_capacity();
        circular_buffer<T, Alloc>::push_front(boost::move(item));
    }

    //! Insert a new element at the beginning of the space optimized circular buffer.
    /*!
        \post if <code>capacity().%capacity() > 0</code> then <code>front() == item</code><br>
              If the <code>circular_buffer_space_optimized</code> is full, the last element will be removed. If the
              capacity is <code>0</code>, nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T()</code> throws.
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link push_back() push_back(const_reference)\endlink</code>, <code>pop_back()</code>,
            <code>pop_front()</code>
    */
    void push_front() {
        check_low_capacity();
        circular_buffer<T, Alloc>::push_front();
    }

    //! Remove the last element from the space optimized circular buffer.
    /*!
        \pre <code>!empty()</code>
        \post The last element is removed from the <code>circular_buffer_space_optimized</code>.<br><br>
              The amount of allocated memory in the internal buffer may be predictively decreased.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>pop_front()</code>, <code>\link push_back() push_back(const_reference)\endlink</code>,
            <code>\link push_front() push_front(const_reference)\endlink</code>
    */
    void pop_back() {
        circular_buffer<T, Alloc>::pop_back();
        check_high_capacity();
    }

    //! Remove the first element from the space optimized circular buffer.
    /*!
        \pre <code>!empty()</code>
        \post The first element is removed from the <code>circular_buffer_space_optimized</code>.<br><br>
              The amount of allocated memory in the internal buffer may be predictively decreased.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>pop_back()</code>, <code>\link push_back() push_back(const_reference)\endlink</code>,
            <code>\link push_front() push_front(const_reference)\endlink</code>
    */
    void pop_front() {
        circular_buffer<T, Alloc>::pop_front();
        check_high_capacity();
    }

    //! Insert an element at the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> or its
             end.
        \post The <code>item</code> will be inserted at the position <code>pos</code>.<br>
              If the <code>circular_buffer_space_optimized</code> is full, the first element will be overwritten. If
              the <code>circular_buffer_space_optimized</code> is full and the <code>pos</code> points to
              <code>begin()</code>, then the <code>item</code> will not be inserted. If the capacity is <code>0</code>,
              nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param pos An iterator specifying the position where the <code>item</code> will be inserted.
        \param item The element to be inserted.
        \return Iterator to the inserted element or <code>begin()</code> if the <code>item</code> is not inserted. (See
                the <i>Effect</i>.)
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
                Whatever <code>T::operator = (const T&)</code> throws.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link insert(iterator, size_type, param_value_type)
            insert(iterator, size_type, value_type)\endlink</code>,
            <code>insert(iterator, InputIterator, InputIterator)</code>,
            <code>\link rinsert(iterator, param_value_type) rinsert(iterator, value_type)\endlink</code>,
            <code>\link rinsert(iterator, size_type, param_value_type)
            rinsert(iterator, size_type, value_type)\endlink</code>,
            <code>rinsert(iterator, InputIterator, InputIterator)</code>
    */
    iterator insert(iterator pos, param_value_type item) {
        size_type index = pos - begin();
        check_low_capacity();
        return circular_buffer<T, Alloc>::insert(begin() + index, item);
    }

    //! Insert an element at the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> or its
             end.
        \post The <code>item</code> will be inserted at the position <code>pos</code>.<br>
              If the <code>circular_buffer_space_optimized</code> is full, the first element will be overwritten. If
              the <code>circular_buffer_space_optimized</code> is full and the <code>pos</code> points to
              <code>begin()</code>, then the <code>item</code> will not be inserted. If the capacity is <code>0</code>,
              nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param pos An iterator specifying the position where the <code>item</code> will be inserted.
        \param item The element to be inserted.
        \return Iterator to the inserted element or <code>begin()</code> if the <code>item</code> is not inserted. (See
                the <i>Effect</i>.)
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link insert(iterator, size_type, param_value_type)
            insert(iterator, size_type, value_type)\endlink</code>,
            <code>insert(iterator, InputIterator, InputIterator)</code>,
            <code>\link rinsert(iterator, param_value_type) rinsert(iterator, value_type)\endlink</code>,
            <code>\link rinsert(iterator, size_type, param_value_type)
            rinsert(iterator, size_type, value_type)\endlink</code>,
            <code>rinsert(iterator, InputIterator, InputIterator)</code>
    */
    iterator insert(iterator pos, rvalue_type item) {
        size_type index = pos - begin();
        check_low_capacity();
        return circular_buffer<T, Alloc>::insert(begin() + index, boost::move(item));
    }

    //! Insert an element at the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> or its
             end.
        \post The <code>item</code> will be inserted at the position <code>pos</code>.<br>
              If the <code>circular_buffer_space_optimized</code> is full, the first element will be overwritten. If
              the <code>circular_buffer_space_optimized</code> is full and the <code>pos</code> points to
              <code>begin()</code>, then the <code>item</code> will not be inserted. If the capacity is <code>0</code>,
              nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param pos An iterator specifying the position where the <code>item</code> will be inserted.
        \return Iterator to the inserted element or <code>begin()</code> if the <code>item</code> is not inserted. (See
                the <i>Effect</i>.)
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T()</code> throws.
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link insert(iterator, size_type, param_value_type)
            insert(iterator, size_type, value_type)\endlink</code>,
            <code>insert(iterator, InputIterator, InputIterator)</code>,
            <code>\link rinsert(iterator, param_value_type) rinsert(iterator, value_type)\endlink</code>,
            <code>\link rinsert(iterator, size_type, param_value_type)
            rinsert(iterator, size_type, value_type)\endlink</code>,
            <code>rinsert(iterator, InputIterator, InputIterator)</code>
    */
    iterator insert(iterator pos) {
        size_type index = pos - begin();
        check_low_capacity();
        return circular_buffer<T, Alloc>::insert(begin() + index);
    }

    //! Insert <code>n</code> copies of the <code>item</code> at the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> or its
             end.
        \post The number of <code>min[n, (pos - begin()) + reserve()]</code> elements will be inserted at the position
              <code>pos</code>.<br>The number of <code>min[pos - begin(), max[0, n - reserve()]]</code> elements will
              be overwritten at the beginning of the <code>circular_buffer_space_optimized</code>.<br>(See
              <i>Example</i> for the explanation.)<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param pos An iterator specifying the position where the <code>item</code>s will be inserted.
        \param n The number of <code>item</code>s the to be inserted.
        \param item The element whose copies will be inserted.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
                Whatever <code>T::operator = (const T&)</code> throws.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in <code>min[capacity().%capacity(), size() + n]</code>).
        \par Example
             Consider a <code>circular_buffer_space_optimized</code> with the capacity of 6 and the size of 4. Its
             internal buffer may look like the one below.<br><br>
             <code>|1|2|3|4| | |</code><br>
             <code>p ___^</code><br><br>After inserting 5 elements at the position <code>p</code>:<br><br>
             <code>insert(p, (size_t)5, 0);</code><br><br>actually only 4 elements get inserted and elements
             <code>1</code> and <code>2</code> are overwritten. This is due to the fact the insert operation preserves
             the capacity. After insertion the internal buffer looks like this:<br><br><code>|0|0|0|0|3|4|</code><br>
             <br>For comparison if the capacity would not be preserved the internal buffer would then result in
             <code>|1|2|0|0|0|0|0|3|4|</code>.
        \sa <code>\link insert(iterator, param_value_type) insert(iterator, value_type)\endlink</code>,
            <code>insert(iterator, InputIterator, InputIterator)</code>,
            <code>\link rinsert(iterator, param_value_type) rinsert(iterator, value_type)\endlink</code>,
            <code>\link rinsert(iterator, size_type, param_value_type)
            rinsert(iterator, size_type, value_type)\endlink</code>,
            <code>rinsert(iterator, InputIterator, InputIterator)</code>
    */
    void insert(iterator pos, size_type n, param_value_type item) {
        size_type index = pos - begin();
        check_low_capacity(n);
        circular_buffer<T, Alloc>::insert(begin() + index, n, item);
    }

    //! Insert the range <code>[first, last)</code> at the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> or its
             end.<br>Valid range <code>[first, last)</code> where <code>first</code> and <code>last</code> meet the
             requirements of an <a href="https://www.boost.org/sgi/stl/InputIterator.html">InputIterator</a>.
        \post Elements from the range
              <code>[first + max[0, distance(first, last) - (pos - begin()) - reserve()], last)</code> will be
              inserted at the position <code>pos</code>.<br>The number of <code>min[pos - begin(), max[0,
              distance(first, last) - reserve()]]</code> elements will be overwritten at the beginning of the
              <code>circular_buffer_space_optimized</code>.<br>(See <i>Example</i> for the explanation.)<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param pos An iterator specifying the position where the range will be inserted.
        \param first The beginning of the range to be inserted.
        \param last The end of the range to be inserted.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in <code>[size() + std::distance(first, last)]</code>; in
             <code>min[capacity().%capacity(), size() + std::distance(first, last)]</code> if the
             <code>InputIterator</code> is a
             <a href="https://www.boost.org/sgi/stl/RandomAccessIterator.html">RandomAccessIterator</a>).
        \par Example
             Consider a <code>circular_buffer_space_optimized</code> with the capacity of 6 and the size of 4. Its
             internal buffer may look like the one below.<br><br>
             <code>|1|2|3|4| | |</code><br>
             <code>p ___^</code><br><br>After inserting a range of elements at the position <code>p</code>:<br><br>
             <code>int array[] = { 5, 6, 7, 8, 9 };</code><br><code>insert(p, array, array + 5);</code><br><br>
             actually only elements <code>6</code>, <code>7</code>, <code>8</code> and <code>9</code> from the
             specified range get inserted and elements <code>1</code> and <code>2</code> are overwritten. This is due
             to the fact the insert operation preserves the capacity. After insertion the internal buffer looks like
             this:<br><br><code>|6|7|8|9|3|4|</code><br><br>For comparison if the capacity would not be preserved the
             internal buffer would then result in <code>|1|2|5|6|7|8|9|3|4|</code>.
        \sa <code>\link insert(iterator, param_value_type) insert(iterator, value_type)\endlink</code>,
            <code>\link insert(iterator, size_type, param_value_type)
            insert(iterator, size_type, value_type)\endlink</code>, <code>\link rinsert(iterator, param_value_type)
            rinsert(iterator, value_type)\endlink</code>, <code>\link rinsert(iterator, size_type, param_value_type)
            rinsert(iterator, size_type, value_type)\endlink</code>,
            <code>rinsert(iterator, InputIterator, InputIterator)</code>
    */
    template <class InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last) {
        insert(pos, first, last, is_integral<InputIterator>());
    }

    //! Insert an element before the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> or its
             end.
        \post The <code>item</code> will be inserted before the position <code>pos</code>.<br>
              If the <code>circular_buffer_space_optimized</code> is full, the last element will be overwritten. If the
              <code>circular_buffer_space_optimized</code> is full and the <code>pos</code> points to
              <code>end()</code>, then the <code>item</code> will not be inserted. If the capacity is <code>0</code>,
              nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param pos An iterator specifying the position before which the <code>item</code> will be inserted.
        \param item The element to be inserted.
        \return Iterator to the inserted element or <code>end()</code> if the <code>item</code> is not inserted. (See
                the <i>Effect</i>.)
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
                Whatever <code>T::operator = (const T&)</code> throws.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link rinsert(iterator, size_type, param_value_type)
            rinsert(iterator, size_type, value_type)\endlink</code>,
            <code>rinsert(iterator, InputIterator, InputIterator)</code>,
            <code>\link insert(iterator, param_value_type) insert(iterator, value_type)\endlink</code>,
            <code>\link insert(iterator, size_type, param_value_type)
            insert(iterator, size_type, value_type)\endlink</code>,
            <code>insert(iterator, InputIterator, InputIterator)</code>
    */
    iterator rinsert(iterator pos, param_value_type item) {
        size_type index = pos - begin();
        check_low_capacity();
        return circular_buffer<T, Alloc>::rinsert(begin() + index, item);
    }

    //! Insert an element before the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> or its
             end.
        \post The <code>item</code> will be inserted before the position <code>pos</code>.<br>
              If the <code>circular_buffer_space_optimized</code> is full, the last element will be overwritten. If the
              <code>circular_buffer_space_optimized</code> is full and the <code>pos</code> points to
              <code>end()</code>, then the <code>item</code> will not be inserted. If the capacity is <code>0</code>,
              nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param pos An iterator specifying the position before which the <code>item</code> will be inserted.
        \param item The element to be inserted.
        \return Iterator to the inserted element or <code>end()</code> if the <code>item</code> is not inserted. (See
                the <i>Effect</i>.)
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link rinsert(iterator, size_type, param_value_type)
            rinsert(iterator, size_type, value_type)\endlink</code>,
            <code>rinsert(iterator, InputIterator, InputIterator)</code>,
            <code>\link insert(iterator, param_value_type) insert(iterator, value_type)\endlink</code>,
            <code>\link insert(iterator, size_type, param_value_type)
            insert(iterator, size_type, value_type)\endlink</code>,
            <code>insert(iterator, InputIterator, InputIterator)</code>
    */
    iterator rinsert(iterator pos, rvalue_type item) {
        size_type index = pos - begin();
        check_low_capacity();
        return circular_buffer<T, Alloc>::rinsert(begin() + index, boost::move(item));
    }

    //! Insert an element before the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> or its
             end.
        \post The <code>item</code> will be inserted before the position <code>pos</code>.<br>
              If the <code>circular_buffer_space_optimized</code> is full, the last element will be overwritten. If the
              <code>circular_buffer_space_optimized</code> is full and the <code>pos</code> points to
              <code>end()</code>, then the <code>item</code> will not be inserted. If the capacity is <code>0</code>,
              nothing will be inserted.<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param pos An iterator specifying the position before which the <code>item</code> will be inserted.
        \return Iterator to the inserted element or <code>end()</code> if the <code>item</code> is not inserted. (See
                the <i>Effect</i>.)
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T()</code> throws.
                Whatever <code>T::T(const T&)</code> throws or nothing if <code>T::T(T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>\link rinsert(iterator, size_type, param_value_type)
            rinsert(iterator, size_type, value_type)\endlink</code>,
            <code>rinsert(iterator, InputIterator, InputIterator)</code>,
            <code>\link insert(iterator, param_value_type) insert(iterator, value_type)\endlink</code>,
            <code>\link insert(iterator, size_type, param_value_type)
            insert(iterator, size_type, value_type)\endlink</code>,
            <code>insert(iterator, InputIterator, InputIterator)</code>
    */
    iterator rinsert(iterator pos) {
        size_type index = pos - begin();
        check_low_capacity();
        return circular_buffer<T, Alloc>::rinsert(begin() + index);
    }

    //! Insert <code>n</code> copies of the <code>item</code> before the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> or its
             end.
        \post The number of <code>min[n, (end() - pos) + reserve()]</code> elements will be inserted before the
              position <code>pos</code>.<br>The number of <code>min[end() - pos, max[0, n - reserve()]]</code> elements
              will be overwritten at the end of the <code>circular_buffer_space_optimized</code>.<br>(See
              <i>Example</i> for the explanation.)<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param pos An iterator specifying the position where the <code>item</code>s will be inserted.
        \param n The number of <code>item</code>s the to be inserted.
        \param item The element whose copies will be inserted.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
                Whatever <code>T::operator = (const T&)</code> throws.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in <code>min[capacity().%capacity(), size() + n]</code>).
        \par Example
             Consider a <code>circular_buffer_space_optimized</code> with the capacity of 6 and the size of 4. Its
             internal buffer may look like the one below.<br><br>
             <code>|1|2|3|4| | |</code><br>
             <code>p ___^</code><br><br>After inserting 5 elements before the position <code>p</code>:<br><br>
             <code>rinsert(p, (size_t)5, 0);</code><br><br>actually only 4 elements get inserted and elements
             <code>3</code> and <code>4</code> are overwritten. This is due to the fact the rinsert operation preserves
             the capacity. After insertion the internal buffer looks like this:<br><br><code>|1|2|0|0|0|0|</code><br>
             <br>For comparison if the capacity would not be preserved the internal buffer would then result in
             <code>|1|2|0|0|0|0|0|3|4|</code>.
        \sa <code>\link rinsert(iterator, param_value_type) rinsert(iterator, value_type)\endlink</code>,
            <code>rinsert(iterator, InputIterator, InputIterator)</code>,
            <code>\link insert(iterator, param_value_type) insert(iterator, value_type)\endlink</code>,
            <code>\link insert(iterator, size_type, param_value_type)
            insert(iterator, size_type, value_type)\endlink</code>,
            <code>insert(iterator, InputIterator, InputIterator)</code>
    */
    void rinsert(iterator pos, size_type n, param_value_type item) {
        size_type index = pos - begin();
        check_low_capacity(n);
        circular_buffer<T, Alloc>::rinsert(begin() + index, n, item);
    }

        //! Insert the range <code>[first, last)</code> before the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> or its
             end.<br>
             Valid range <code>[first, last)</code> where <code>first</code> and <code>last</code> meet the
             requirements of an <a href="https://www.boost.org/sgi/stl/InputIterator.html">InputIterator</a>.
        \post Elements from the range
              <code>[first, last - max[0, distance(first, last) - (end() - pos) - reserve()])</code> will be inserted
              before the position <code>pos</code>.<br>The number of <code>min[end() - pos, max[0,
              distance(first, last) - reserve()]]</code> elements will be overwritten at the end of the
              <code>circular_buffer</code>.<br>(See <i>Example</i> for the explanation.)<br><br>
              The amount of allocated memory in the internal buffer may be predictively increased.
        \param pos An iterator specifying the position where the range will be inserted.
        \param first The beginning of the range to be inserted.
        \param last The end of the range to be inserted.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::T(const T&)</code> throws.
                Whatever <code>T::operator = (const T&)</code> throws.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in <code>[size() + std::distance(first, last)]</code>; in
             <code>min[capacity().%capacity(), size() + std::distance(first, last)]</code> if the
             <code>InputIterator</code> is a
             <a href="https://www.boost.org/sgi/stl/RandomAccessIterator.html">RandomAccessIterator</a>).
        \par Example
             Consider a <code>circular_buffer_space_optimized</code> with the capacity of 6 and the size of 4. Its
             internal buffer may look like the one below.<br><br>
             <code>|1|2|3|4| | |</code><br>
             <code>p ___^</code><br><br>After inserting a range of elements before the position <code>p</code>:<br><br>
             <code>int array[] = { 5, 6, 7, 8, 9 };</code><br><code>insert(p, array, array + 5);</code><br><br>
             actually only elements <code>5</code>, <code>6</code>, <code>7</code> and <code>8</code> from the
             specified range get inserted and elements <code>3</code> and <code>4</code> are overwritten. This is due
             to the fact the rinsert operation preserves the capacity. After insertion the internal buffer looks like
             this:<br><br><code>|1|2|5|6|7|8|</code><br><br>For comparison if the capacity would not be preserved the
             internal buffer would then result in <code>|1|2|5|6|7|8|9|3|4|</code>.
        \sa <code>\link rinsert(iterator, param_value_type) rinsert(iterator, value_type)\endlink</code>,
            <code>\link rinsert(iterator, size_type, param_value_type)
            rinsert(iterator, size_type, value_type)\endlink</code>, <code>\link insert(iterator, param_value_type)
            insert(iterator, value_type)\endlink</code>, <code>\link insert(iterator, size_type, param_value_type)
            insert(iterator, size_type, value_type)\endlink</code>,
            <code>insert(iterator, InputIterator, InputIterator)</code>
    */
    template <class InputIterator>
    void rinsert(iterator pos, InputIterator first, InputIterator last) {
        rinsert(pos, first, last, is_integral<InputIterator>());
    }

    //! Remove an element at the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> (but not
             an <code>end()</code>).
        \post The element at the position <code>pos</code> is removed.<br><br>
              The amount of allocated memory in the internal buffer may be predictively decreased.
        \param pos An iterator pointing at the element to be removed.
        \return Iterator to the first element remaining beyond the removed element or <code>end()</code> if no such
                element exists.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::operator = (const T&)</code> throws or 
                nothing if <code>T::operator = (T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>erase(iterator, iterator)</code>, <code>rerase(iterator)</code>,
            <code>rerase(iterator, iterator)</code>, <code>clear()</code>
    */
    iterator erase(iterator pos) {
        iterator it = circular_buffer<T, Alloc>::erase(pos);
        size_type index = it - begin();
        check_high_capacity();
        return begin() + index;
    }

    //! Erase the range <code>[first, last)</code>.
    /*!
        \pre Valid range <code>[first, last)</code>.
        \post The elements from the range <code>[first, last)</code> are removed. (If <code>first == last</code>
              nothing is removed.)<br><br>
              The amount of allocated memory in the internal buffer may be predictively decreased.
        \param first The beginning of the range to be removed.
        \param last The end of the range to be removed.
        \return Iterator to the first element remaining beyond the removed elements or <code>end()</code> if no such
                element exists.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::operator = (const T&)</code> throws or 
                nothing if <code>T::operator = (T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>erase(iterator)</code>, <code>rerase(iterator)</code>, <code>rerase(iterator, iterator)</code>,
            <code>clear()</code>
    */
    iterator erase(iterator first, iterator last) {
        iterator it = circular_buffer<T, Alloc>::erase(first, last);
        size_type index = it - begin();
        check_high_capacity();
        return begin() + index;
    }

    //! Remove an element at the specified position.
    /*!
        \pre <code>pos</code> is a valid iterator pointing to the <code>circular_buffer_space_optimized</code> (but not
             an <code>end()</code>).<br><br>
              The amount of allocated memory in the internal buffer may be predictively decreased.
        \post The element at the position <code>pos</code> is removed.
        \param pos An iterator pointing at the element to be removed.
        \return Iterator to the first element remaining in front of the removed element or <code>begin()</code> if no
                such element exists.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::operator = (const T&)</code> throws or 
                nothing if <code>T::operator = (T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \note Basically there is no difference between <code>erase(iterator)</code> and this method. It is implemented
              only for consistency with the base <code>circular_buffer</code>.
        \sa <code>erase(iterator)</code>, <code>erase(iterator, iterator)</code>,
            <code>rerase(iterator, iterator)</code>, <code>clear()</code>
    */
    iterator rerase(iterator pos) {
        iterator it = circular_buffer<T, Alloc>::rerase(pos);
        size_type index = it - begin();
        check_high_capacity();
        return begin() + index;
    }

    //! Erase the range <code>[first, last)</code>.
    /*!
        \pre Valid range <code>[first, last)</code>.
        \post The elements from the range <code>[first, last)</code> are removed. (If <code>first == last</code>
              nothing is removed.)<br><br>
              The amount of allocated memory in the internal buffer may be predictively decreased.
        \param first The beginning of the range to be removed.
        \param last The end of the range to be removed.
        \return Iterator to the first element remaining in front of the removed elements or <code>begin()</code> if no
                such element exists.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
                Whatever <code>T::operator = (const T&)</code> throws or 
                nothing if <code>T::operator = (T&&)</code> is noexcept.
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \note Basically there is no difference between <code>erase(iterator, iterator)</code> and this method. It is
              implemented only for consistency with the base
              <code><circular_buffer</code>.
        \sa <code>erase(iterator)</code>, <code>erase(iterator, iterator)</code>, <code>rerase(iterator)</code>,
            <code>clear()</code>
    */
    iterator rerase(iterator first, iterator last) {
        iterator it = circular_buffer<T, Alloc>::rerase(first, last);
        size_type index = it - begin();
        check_high_capacity();
        return begin() + index;
    }

    //! Remove all stored elements from the space optimized circular buffer.
    /*!
        \post <code>size() == 0</code><br><br>
              The amount of allocated memory in the internal buffer may be predictively decreased.
        \throws "An allocation error" if memory is exhausted (<code>std::bad_alloc</code> if the standard allocator is
                used).
        \par Exception Safety
             Basic.
        \par Iterator Invalidation
             Invalidates all iterators pointing to the <code>circular_buffer_space_optimized</code> (except iterators
             equal to <code>end()</code>).
        \par Complexity
             Linear (in the size of the <code>circular_buffer_space_optimized</code>).
        \sa <code>~circular_buffer_space_optimized()</code>, <code>erase(iterator)</code>,
            <code>erase(iterator, iterator)</code>, <code>rerase(iterator)</code>,
            <code>rerase(iterator, iterator)</code>
    */
    void clear() { erase(begin(), end()); }

private:
// Helper methods

    /*! INTERNAL ONLY */
    void adjust_min_capacity() {
        if (m_capacity_ctrl.min_capacity() > circular_buffer<T, Alloc>::capacity())
            circular_buffer<T, Alloc>::set_capacity(m_capacity_ctrl.min_capacity());
        else
            check_high_capacity();
    }

    /*! INTERNAL ONLY */
    size_type ensure_reserve(size_type new_capacity, size_type buffer_size) const {
        if (buffer_size + new_capacity / 5 >= new_capacity)
            new_capacity *= 2; // ensure at least 20% reserve
        if (new_capacity > m_capacity_ctrl)
            return m_capacity_ctrl;
        return new_capacity;
    }

    /*! INTERNAL ONLY */
    void check_low_capacity(size_type n = 1) {
        size_type new_size = size() + n;
        size_type new_capacity = circular_buffer<T, Alloc>::capacity();
        if (new_size > new_capacity) {
            if (new_capacity == 0)
                new_capacity = 1;
            for (; new_size > new_capacity; new_capacity *= 2) {}
            circular_buffer<T, Alloc>::set_capacity(
                ensure_reserve(new_capacity, new_size));
        }
#if BOOST_CB_ENABLE_DEBUG
        this->invalidate_iterators_except(end());
#endif
    }

    /*! INTERNAL ONLY */
    void check_high_capacity() {
        size_type new_capacity = circular_buffer<T, Alloc>::capacity();
        while (new_capacity / 3 >= size()) { // (new_capacity / 3) -> avoid oscillations
            new_capacity /= 2;
            if (new_capacity <= m_capacity_ctrl.min_capacity()) {
                new_capacity = m_capacity_ctrl.min_capacity();
                break;
            }
        }
        circular_buffer<T, Alloc>::set_capacity(
            ensure_reserve(new_capacity, size()));
#if BOOST_CB_ENABLE_DEBUG
        this->invalidate_iterators_except(end());
#endif
    }

    /*! INTERNAL ONLY */
    void reduce_capacity(const true_type&) {
        circular_buffer<T, Alloc>::set_capacity((std::max)(m_capacity_ctrl.min_capacity(), size()));
    }

    /*! INTERNAL ONLY */
    void reduce_capacity(const false_type&) {}

    /*! INTERNAL ONLY */
    static size_type init_capacity(const capacity_type& capacity_ctrl, size_type n) {
        BOOST_CB_ASSERT(capacity_ctrl.capacity() >= n); // check for capacity lower than n
        return (std::max)(capacity_ctrl.min_capacity(), n);
    }

    /*! INTERNAL ONLY */
    template <class IntegralType>
    static size_type init_capacity(const capacity_type& capacity_ctrl, IntegralType n, IntegralType,
        const true_type&) {
        return init_capacity(capacity_ctrl, static_cast<size_type>(n));
    }

    /*! INTERNAL ONLY */
    template <class Iterator>
    static size_type init_capacity(const capacity_type& capacity_ctrl, Iterator first, Iterator last,
        const false_type&) {
        BOOST_CB_IS_CONVERTIBLE(Iterator, value_type); // check for invalid iterator type
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x581))
        return init_capacity(capacity_ctrl, first, last, std::iterator_traits<Iterator>::iterator_category());
#else
        return init_capacity(
            capacity_ctrl, first, last, BOOST_DEDUCED_TYPENAME std::iterator_traits<Iterator>::iterator_category());
#endif
    }

    /*! INTERNAL ONLY */
    template <class InputIterator>
    static size_type init_capacity(const capacity_type& capacity_ctrl, InputIterator, InputIterator,
        const std::input_iterator_tag&) {
        return capacity_ctrl.capacity();
    }

    /*! INTERNAL ONLY */
    template <class ForwardIterator>
    static size_type init_capacity(const capacity_type& capacity_ctrl, ForwardIterator first, ForwardIterator last,
        const std::forward_iterator_tag&) {
        BOOST_CB_ASSERT(std::distance(first, last) >= 0); // check for wrong range
        return (std::max)(capacity_ctrl.min_capacity(),
            (std::min)(capacity_ctrl.capacity(), static_cast<size_type>(std::distance(first, last))));
    }

    /*! INTERNAL ONLY */
    template <class IntegralType>
    void insert(const iterator& pos, IntegralType n, IntegralType item, const true_type&) {
        insert(pos, static_cast<size_type>(n), static_cast<value_type>(item));
    }

    /*! INTERNAL ONLY */
    template <class Iterator>
    void insert(const iterator& pos, Iterator first, Iterator last, const false_type&) {
        size_type index = pos - begin();
        check_low_capacity(std::distance(first, last));
        circular_buffer<T, Alloc>::insert(begin() + index, first, last);
    }

    /*! INTERNAL ONLY */
    template <class IntegralType>
    void rinsert(const iterator& pos, IntegralType n, IntegralType item, const true_type&) {
        rinsert(pos, static_cast<size_type>(n), static_cast<value_type>(item));
    }

    /*! INTERNAL ONLY */
    template <class Iterator>
    void rinsert(const iterator& pos, Iterator first, Iterator last, const false_type&) {
        size_type index = pos - begin();
        check_low_capacity(std::distance(first, last));
        circular_buffer<T, Alloc>::rinsert(begin() + index, first, last);
    }
};

// Non-member functions

//! Test two space optimized circular buffers for equality.
template <class T, class Alloc>
inline bool operator == (const circular_buffer_space_optimized<T, Alloc>& lhs,
    const circular_buffer_space_optimized<T, Alloc>& rhs) {
    return lhs.size() == rhs.size() &&
        std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

//! Lexicographical comparison.
template <class T, class Alloc>
inline bool operator < (const circular_buffer_space_optimized<T, Alloc>& lhs,
    const circular_buffer_space_optimized<T, Alloc>& rhs) {
    return std::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) || BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))

//! Test two space optimized circular buffers for non-equality.
template <class T, class Alloc>
inline bool operator != (const circular_buffer_space_optimized<T, Alloc>& lhs,
    const circular_buffer_space_optimized<T, Alloc>& rhs) {
    return !(lhs == rhs);
}

//! Lexicographical comparison.
template <class T, class Alloc>
inline bool operator > (const circular_buffer_space_optimized<T, Alloc>& lhs,
    const circular_buffer_space_optimized<T, Alloc>& rhs) {
    return rhs < lhs;
}

//! Lexicographical comparison.
template <class T, class Alloc>
inline bool operator <= (const circular_buffer_space_optimized<T, Alloc>& lhs,
    const circular_buffer_space_optimized<T, Alloc>& rhs) {
    return !(rhs < lhs);
}

//! Lexicographical comparison.
template <class T, class Alloc>
inline bool operator >= (const circular_buffer_space_optimized<T, Alloc>& lhs,
    const circular_buffer_space_optimized<T, Alloc>& rhs) {
    return !(lhs < rhs);
}

//! Swap the contents of two space optimized circular buffers.
template <class T, class Alloc>
inline void swap(circular_buffer_space_optimized<T, Alloc>& lhs,
    circular_buffer_space_optimized<T, Alloc>& rhs) BOOST_NOEXCEPT {
    lhs.swap(rhs);
}

#endif // #if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) || BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))

} // namespace boost

#endif // #if !defined(BOOST_CIRCULAR_BUFFER_SPACE_OPTIMIZED_HPP)

/* space_optimized.hpp
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
*/
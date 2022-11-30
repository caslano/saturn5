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

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x581))
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
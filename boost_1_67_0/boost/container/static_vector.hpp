// Boost.Container static_vector
//
// Copyright (c) 2012-2013 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2011-2013 Andrew Hundt.
// Copyright (c) 2013-2014 Ion Gaztanaga
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTAINER_STATIC_VECTOR_HPP
#define BOOST_CONTAINER_STATIC_VECTOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/vector.hpp>

#include <cstddef>
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

namespace boost { namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

namespace dtl {

template<class T, std::size_t N, std::size_t InplaceAlignment, bool ThrowOnOverflow>
class static_storage_allocator
{
   typedef bool_<ThrowOnOverflow> throw_on_overflow_t;

   static BOOST_NORETURN BOOST_CONTAINER_FORCEINLINE void on_capacity_overflow(true_type)
   {
      (throw_bad_alloc)();
   }

   static BOOST_CONTAINER_FORCEINLINE void on_capacity_overflow(false_type)
   {
      BOOST_ASSERT_MSG(false, "ERROR: static vector capacity overflow");
   }
   
   public:
   typedef T value_type;

   BOOST_CONTAINER_FORCEINLINE static_storage_allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   BOOST_CONTAINER_FORCEINLINE static_storage_allocator(const static_storage_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   BOOST_CONTAINER_FORCEINLINE static_storage_allocator & operator=(const static_storage_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return *this;  }

   BOOST_CONTAINER_FORCEINLINE T* internal_storage() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return const_cast<T*>(static_cast<const T*>(static_cast<const void*>(storage.data)));  }

   BOOST_CONTAINER_FORCEINLINE T* internal_storage() BOOST_NOEXCEPT_OR_NOTHROW
   {  return static_cast<T*>(static_cast<void*>(storage.data));  }

   static const std::size_t internal_capacity = N;

   std::size_t max_size() const
   {  return N;   }

   static BOOST_CONTAINER_FORCEINLINE void on_capacity_overflow()
   {
      (on_capacity_overflow)(throw_on_overflow_t());
   }

   typedef boost::container::dtl::version_type<static_storage_allocator, 0>   version;

   BOOST_CONTAINER_FORCEINLINE friend bool operator==(const static_storage_allocator &, const static_storage_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return false;  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator!=(const static_storage_allocator &, const static_storage_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return true;  }

   private:
   BOOST_STATIC_ASSERT_MSG(!InplaceAlignment || (InplaceAlignment & (InplaceAlignment-1)) == 0, "Alignment option must be zero or power of two");
   static const std::size_t final_alignment = InplaceAlignment ? InplaceAlignment : dtl::alignment_of<T>::value;
   typename dtl::aligned_storage<sizeof(T)*N, final_alignment>::type storage;
};

template<class Options>
struct get_static_vector_opt
{
   typedef Options type;
};

template<>
struct get_static_vector_opt<void>
{
   typedef static_vector_null_opt type;
};

template <typename T, std::size_t Capacity, class Options>
struct get_static_vector_allocator
{
   typedef typename  get_static_vector_opt<Options>::type options_t;
   typedef dtl::static_storage_allocator
      < T
      , Capacity
      , options_t::inplace_alignment
      , options_t::throw_on_overflow
      > type;
};


}  //namespace dtl {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//!
//!@brief A variable-size array container with fixed capacity.
//!
//!static_vector is a sequence container like boost::container::vector with contiguous storage that can
//!change in size, along with the static allocation, low overhead, and fixed capacity of boost::array.
//!
//!A static_vector is a sequence that supports random access to elements, constant time insertion and
//!removal of elements at the end, and linear time insertion and removal of elements at the beginning or
//!in the middle. The number of elements in a static_vector may vary dynamically up to a fixed capacity
//!because elements are stored within the object itself similarly to an array. However, objects are
//!initialized as they are inserted into static_vector unlike C arrays or std::array which must construct
//!all elements on instantiation. The behavior of static_vector enables the use of statically allocated
//!elements in cases with complex object lifetime requirements that would otherwise not be trivially
//!possible.
//!
//!@par Error Handling
//! Insertion beyond the capacity result in throwing std::bad_alloc() if exceptions are enabled or
//! calling throw_bad_alloc() if not enabled.
//!
//! std::out_of_range is thrown if out of bounds access is performed in <code>at()</code> if exceptions are
//! enabled, throw_out_of_range() if not enabled.
//!
//!@tparam T    The type of element that will be stored.
//!@tparam Capacity The maximum number of elements static_vector can store, fixed at compile time.
//!@tparam Options A type produced from \c boost::container::static_vector_options.
template <typename T, std::size_t Capacity, class Options BOOST_CONTAINER_DOCONLY(= void) >
class static_vector
    : public vector<T, typename dtl::get_static_vector_allocator< T, Capacity, Options>::type>
{
   public:
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef typename dtl::get_static_vector_allocator< T, Capacity, Options>::type allocator_type;
   typedef vector<T, allocator_type > base_t;

   BOOST_COPYABLE_AND_MOVABLE(static_vector)

   template<class U, std::size_t OtherCapacity, class OtherOptions>
   friend class static_vector;

   public:
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

public:
    //! @brief The type of elements stored in the container.
    typedef typename base_t::value_type value_type;
    //! @brief The unsigned integral type used by the container.
    typedef typename base_t::size_type size_type;
    //! @brief The pointers difference type.
    typedef typename base_t::difference_type difference_type;
    //! @brief The pointer type.
    typedef typename base_t::pointer pointer;
    //! @brief The const pointer type.
    typedef typename base_t::const_pointer const_pointer;
    //! @brief The value reference type.
    typedef typename base_t::reference reference;
    //! @brief The value const reference type.
    typedef typename base_t::const_reference const_reference;
    //! @brief The iterator type.
    typedef typename base_t::iterator iterator;
    //! @brief The const iterator type.
    typedef typename base_t::const_iterator const_iterator;
    //! @brief The reverse iterator type.
    typedef typename base_t::reverse_iterator reverse_iterator;
    //! @brief The const reverse iterator.
    typedef typename base_t::const_reverse_iterator const_reverse_iterator;

    //! @brief The capacity/max size of the container
    static const size_type static_capacity = Capacity;

    //! @brief Constructs an empty static_vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    BOOST_CONTAINER_FORCEINLINE static_vector() BOOST_NOEXCEPT_OR_NOTHROW
        : base_t()
    {}

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Constructs a static_vector containing count value initialized values.
    //!
    //! @param count    The number of values which will be contained in the container.
    //!
    //! @par Throws
    //!   If T's value initialization throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    BOOST_CONTAINER_FORCEINLINE explicit static_vector(size_type count)
        : base_t(count)
    {}

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Constructs a static_vector containing count default initialized values.
    //!
    //! @param count    The number of values which will be contained in the container.
    //!
    //! @par Throws
    //!   If T's default initialization throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    //!
    //! @par Note
    //!   Non-standard extension
    BOOST_CONTAINER_FORCEINLINE static_vector(size_type count, default_init_t)
        : base_t(count, default_init_t())
    {}

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Constructs a static_vector containing count copies of value.
    //!
    //! @param count    The number of copies of a values that will be contained in the container.
    //! @param value    The value which will be used to copy construct values.
    //!
    //! @par Throws
    //!   If T's copy constructor throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    BOOST_CONTAINER_FORCEINLINE static_vector(size_type count, value_type const& value)
        : base_t(count, value)
    {}

    //! @pre
    //!  @li <tt>distance(first, last) <= capacity()</tt>
    //!  @li Iterator must meet the \c ForwardTraversalIterator concept.
    //!
    //! @brief Constructs a static_vector containing copy of a range <tt>[first, last)</tt>.
    //!
    //! @param first    The iterator to the first element in range.
    //! @param last     The iterator to the one after the last element in range.
    //!
    //! @par Throws
    //!   If T's constructor taking a dereferenced Iterator throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <typename Iterator>
    BOOST_CONTAINER_FORCEINLINE static_vector(Iterator first, Iterator last)
        : base_t(first, last)
    {}

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    //! @pre
    //!  @li <tt>distance(il.begin(), il.end()) <= capacity()</tt>
    //!
    //! @brief Constructs a static_vector containing copy of a range <tt>[il.begin(), il.end())</tt>.
    //!
    //! @param il       std::initializer_list with values to initialize vector.
    //!
    //! @par Throws
    //!   If T's constructor taking a dereferenced std::initializer_list throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    BOOST_CONTAINER_FORCEINLINE static_vector(std::initializer_list<value_type> il)
        : base_t(il)
    {}
#endif

    //! @brief Constructs a copy of other static_vector.
    //!
    //! @param other    The static_vector which content will be copied to this one.
    //!
    //! @par Throws
    //!   If T's copy constructor throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    BOOST_CONTAINER_FORCEINLINE static_vector(static_vector const& other)
        : base_t(other)
    {}

    BOOST_CONTAINER_FORCEINLINE static_vector(static_vector const& other, const allocator_type &)
       : base_t(other)
    {}

    BOOST_CONTAINER_FORCEINLINE static_vector(BOOST_RV_REF(static_vector) other,  const allocator_type &)
       BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<value_type>::value)
       : base_t(BOOST_MOVE_BASE(base_t, other))
    {}

    BOOST_CONTAINER_FORCEINLINE explicit static_vector(const allocator_type &)
       : base_t()
    {}

    //! @pre <tt>other.size() <= capacity()</tt>.
    //!
    //! @brief Constructs a copy of other static_vector.
    //!
    //! @param other    The static_vector which content will be copied to this one.
    //!
    //! @par Throws
    //!   If T's copy constructor throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <std::size_t C, class O>
    BOOST_CONTAINER_FORCEINLINE static_vector(static_vector<T, C, O> const& other)
        : base_t(other)
    {}

    //! @brief Move constructor. Moves Values stored in the other static_vector to this one.
    //!
    //! @param other    The static_vector which content will be moved to this one.
    //!
    //! @par Throws
    //!   @li If \c has_nothrow_move<T>::value is \c true and T's move constructor throws.
    //!   @li If \c has_nothrow_move<T>::value is \c false and T's copy constructor throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    BOOST_CONTAINER_FORCEINLINE static_vector(BOOST_RV_REF(static_vector) other)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<value_type>::value)
        : base_t(BOOST_MOVE_BASE(base_t, other))
    {}

    //! @pre <tt>other.size() <= capacity()</tt>
    //!
    //! @brief Move constructor. Moves Values stored in the other static_vector to this one.
    //!
    //! @param other    The static_vector which content will be moved to this one.
    //!
    //! @par Throws
    //!   @li If \c has_nothrow_move<T>::value is \c true and T's move constructor throws.
    //!   @li If \c has_nothrow_move<T>::value is \c false and T's copy constructor throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <std::size_t C, class O>
    BOOST_CONTAINER_FORCEINLINE static_vector(BOOST_RV_REF_BEG static_vector<T, C, O> BOOST_RV_REF_END other)
        : base_t(BOOST_MOVE_BASE(typename static_vector<T BOOST_MOVE_I C>::base_t, other))
    {}

    //! @brief Copy assigns Values stored in the other static_vector to this one.
    //!
    //! @param other    The static_vector which content will be copied to this one.
    //!
    //! @par Throws
    //!   If T's copy constructor or copy assignment throws.
    //!
    //! @par Complexity
    //! Linear O(N).
    BOOST_CONTAINER_FORCEINLINE static_vector & operator=(BOOST_COPY_ASSIGN_REF(static_vector) other)
    {
        return static_cast<static_vector&>(base_t::operator=(static_cast<base_t const&>(other)));
    }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
    //! @brief Copy assigns Values stored in std::initializer_list to *this.
    //!
    //! @param il    The std::initializer_list which content will be copied to this one.
    //!
    //! @par Throws
    //!   If T's copy constructor or copy assignment throws.
    //!
    //! @par Complexity
    //! Linear O(N).
    BOOST_CONTAINER_FORCEINLINE static_vector & operator=(std::initializer_list<value_type> il)
    { return static_cast<static_vector&>(base_t::operator=(il));  }
#endif

    //! @pre <tt>other.size() <= capacity()</tt>
    //!
    //! @brief Copy assigns Values stored in the other static_vector to this one.
    //!
    //! @param other    The static_vector which content will be copied to this one.
    //!
    //! @par Throws
    //!   If T's copy constructor or copy assignment throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <std::size_t C, class O>
    BOOST_CONTAINER_FORCEINLINE static_vector & operator=(static_vector<T, C, O> const& other)
    {
        return static_cast<static_vector&>(base_t::operator=
            (static_cast<typename static_vector<T, C, O>::base_t const&>(other)));
    }

    //! @brief Move assignment. Moves Values stored in the other static_vector to this one.
    //!
    //! @param other    The static_vector which content will be moved to this one.
    //!
    //! @par Throws
    //!   @li If \c has_nothrow_move<T>::value is \c true and T's move constructor or move assignment throws.
    //!   @li If \c has_nothrow_move<T>::value is \c false and T's copy constructor or copy assignment throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    BOOST_CONTAINER_FORCEINLINE static_vector & operator=(BOOST_RV_REF(static_vector) other)
       BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_assignable<value_type>::value)
    {
        return static_cast<static_vector&>(base_t::operator=(BOOST_MOVE_BASE(base_t, other)));
    }

    //! @pre <tt>other.size() <= capacity()</tt>
    //!
    //! @brief Move assignment. Moves Values stored in the other static_vector to this one.
    //!
    //! @param other    The static_vector which content will be moved to this one.
    //!
    //! @par Throws
    //!   @li If \c has_nothrow_move<T>::value is \c true and T's move constructor or move assignment throws.
    //!   @li If \c has_nothrow_move<T>::value is \c false and T's copy constructor or copy assignment throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <std::size_t C, class O>
    BOOST_CONTAINER_FORCEINLINE static_vector & operator=(BOOST_RV_REF_BEG static_vector<T, C, O> BOOST_RV_REF_END other)
    {
        return static_cast<static_vector&>(base_t::operator=
         (BOOST_MOVE_BASE(typename static_vector<T BOOST_MOVE_I C>::base_t, other)));
    }

#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED

    //! @brief Destructor. Destroys Values stored in this container.
    //!
    //! @par Throws
    //!   Nothing
    //!
    //! @par Complexity
    //!   Linear O(N).
    ~static_vector();

    //! @brief Swaps contents of the other static_vector and this one.
    //!
    //! @param other    The static_vector which content will be swapped with this one's content.
    //!
    //! @par Throws
    //!   @li If \c has_nothrow_move<T>::value is \c true and T's move constructor or move assignment throws,
    //!   @li If \c has_nothrow_move<T>::value is \c false and T's copy constructor or copy assignment throws,
    //!
    //! @par Complexity
    //!   Linear O(N).
    void swap(static_vector & other);

    //! @pre <tt>other.size() <= capacity() && size() <= other.capacity()</tt>
    //!
    //! @brief Swaps contents of the other static_vector and this one.
    //!
    //! @param other    The static_vector which content will be swapped with this one's content.
    //!
    //! @par Throws
    //!   @li If \c has_nothrow_move<T>::value is \c true and T's move constructor or move assignment throws,
    //!   @li If \c has_nothrow_move<T>::value is \c false and T's copy constructor or copy assignment throws,
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <std::size_t C, class O>
    void swap(static_vector<T, C, O> & other);

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Inserts or erases elements at the end such that
    //!   the size becomes count. New elements are value initialized.
    //!
    //! @param count    The number of elements which will be stored in the container.
    //!
    //! @par Throws
    //!   If T's value initialization throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    void resize(size_type count);

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Inserts or erases elements at the end such that
    //!   the size becomes count. New elements are default initialized.
    //!
    //! @param count    The number of elements which will be stored in the container.
    //!
    //! @par Throws
    //!   If T's default initialization throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    //!
    //! @par Note
    //!   Non-standard extension
    void resize(size_type count, default_init_t);

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Inserts or erases elements at the end such that
    //!   the size becomes count. New elements are copy constructed from value.
    //!
    //! @param count    The number of elements which will be stored in the container.
    //! @param value    The value used to copy construct the new element.
    //!
    //! @par Throws
    //!   If T's copy constructor throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    void resize(size_type count, value_type const& value);

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief This call has no effect because the Capacity of this container is constant.
    //!
    //! @param count    The number of elements which the container should be able to contain.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Linear O(N).
    void reserve(size_type count)  BOOST_NOEXCEPT_OR_NOTHROW;

    //! @pre <tt>size() < capacity()</tt>
    //!
    //! @brief Adds a copy of value at the end.
    //!
    //! @param value    The value used to copy construct the new element.
    //!
    //! @par Throws
    //!   If T's copy constructor throws.
    //!
    //! @par Complexity
    //!   Constant O(1).
    void push_back(value_type const& value);

    //! @pre <tt>size() < capacity()</tt>
    //!
    //! @brief Moves value to the end.
    //!
    //! @param value    The value to move construct the new element.
    //!
    //! @par Throws
    //!   If T's move constructor throws.
    //!
    //! @par Complexity
    //!   Constant O(1).
    void push_back(BOOST_RV_REF(value_type) value);

    //! @pre <tt>!empty()</tt>
    //!
    //! @brief Destroys last value and decreases the size.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    void pop_back();

    //! @pre
    //!  @li \c p must be a valid iterator of \c *this in range <tt>[begin(), end()]</tt>.
    //!  @li <tt>size() < capacity()</tt>
    //!
    //! @brief Inserts a copy of element at p.
    //!
    //! @param p     The position at which the new value will be inserted.
    //! @param value The value used to copy construct the new element.
    //!
    //! @par Throws
    //!   @li If T's copy constructor or copy assignment throws
    //!   @li If T's move constructor or move assignment throws.
    //!
    //! @par Complexity
    //!   Constant or linear.
    iterator insert(const_iterator p, value_type const& value);

    //! @pre
    //!  @li \c p must be a valid iterator of \c *this in range <tt>[begin(), end()]</tt>.
    //!  @li <tt>size() < capacity()</tt>
    //!
    //! @brief Inserts a move-constructed element at p.
    //!
    //! @param p     The position at which the new value will be inserted.
    //! @param value The value used to move construct the new element.
    //!
    //! @par Throws
    //!   If T's move constructor or move assignment throws.
    //!
    //! @par Complexity
    //!   Constant or linear.
    iterator insert(const_iterator p, BOOST_RV_REF(value_type) value);

    //! @pre
    //!  @li \c p must be a valid iterator of \c *this in range <tt>[begin(), end()]</tt>.
    //!  @li <tt>size() + count <= capacity()</tt>
    //!
    //! @brief Inserts a count copies of value at p.
    //!
    //! @param p     The position at which new elements will be inserted.
    //! @param count The number of new elements which will be inserted.
    //! @param value The value used to copy construct new elements.
    //!
    //! @par Throws
    //!   @li If T's copy constructor or copy assignment throws.
    //!   @li If T's move constructor or move assignment throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    iterator insert(const_iterator p, size_type count, value_type const& value);

    //! @pre
    //!  @li \c p must be a valid iterator of \c *this in range <tt>[begin(), end()]</tt>.
    //!  @li <tt>distance(first, last) <= capacity()</tt>
    //!  @li \c Iterator must meet the \c ForwardTraversalIterator concept.
    //!
    //! @brief Inserts a copy of a range <tt>[first, last)</tt> at p.
    //!
    //! @param p     The position at which new elements will be inserted.
    //! @param first The iterator to the first element of a range used to construct new elements.
    //! @param last  The iterator to the one after the last element of a range used to construct new elements.
    //!
    //! @par Throws
    //!   @li If T's constructor and assignment taking a dereferenced \c Iterator.
    //!   @li If T's move constructor or move assignment throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <typename Iterator>
    iterator insert(const_iterator p, Iterator first, Iterator last);

    //! @pre
    //!  @li \c p must be a valid iterator of \c *this in range <tt>[begin(), end()]</tt>.
    //!  @li <tt>distance(il.begin(), il.end()) <= capacity()</tt>
    //!
    //! @brief Inserts a copy of a range <tt>[il.begin(), il.end())</tt> at p.
    //!
    //! @param p     The position at which new elements will be inserted.
    //! @param il    The std::initializer_list which contains elements that will be inserted.
    //!
    //! @par Throws
    //!   @li If T's constructor and assignment taking a dereferenced std::initializer_list iterator.
    //!
    //! @par Complexity
    //!   Linear O(N).
    iterator insert(const_iterator p, std::initializer_list<value_type> il);

    //! @pre \c p must be a valid iterator of \c *this in range <tt>[begin(), end())</tt>
    //!
    //! @brief Erases T from p.
    //!
    //! @param p    The position of the element which will be erased from the container.
    //!
    //! @par Throws
    //!   If T's move assignment throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    iterator erase(const_iterator p);

    //! @pre
    //!  @li \c first and \c last must define a valid range
    //!  @li iterators must be in range <tt>[begin(), end()]</tt>
    //!
    //! @brief Erases Values from a range <tt>[first, last)</tt>.
    //!
    //! @param first    The position of the first element of a range which will be erased from the container.
    //! @param last     The position of the one after the last element of a range which will be erased from the container.
    //!
    //! @par Throws
    //!   If T's move assignment throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    iterator erase(const_iterator first, const_iterator last);

    //! @pre <tt>distance(first, last) <= capacity()</tt>
    //!
    //! @brief Assigns a range <tt>[first, last)</tt> of Values to this container.
    //!
    //! @param first       The iterator to the first element of a range used to construct new content of this container.
    //! @param last        The iterator to the one after the last element of a range used to construct new content of this container.
    //!
    //! @par Throws
    //!   If T's copy constructor or copy assignment throws,
    //!
    //! @par Complexity
    //!   Linear O(N).
    template <typename Iterator>
    void assign(Iterator first, Iterator last);

    //! @pre <tt>distance(il.begin(), il.end()) <= capacity()</tt>
    //!
    //! @brief Assigns a range <tt>[il.begin(), il.end())</tt> of Values to this container.
    //!
    //! @param il       std::initializer_list with values used to construct new content of this container.
    //!
    //! @par Throws
    //!   If T's copy constructor or copy assignment throws,
    //!
    //! @par Complexity
    //!   Linear O(N).
    void assign(std::initializer_list<value_type> il);

    //! @pre <tt>count <= capacity()</tt>
    //!
    //! @brief Assigns a count copies of value to this container.
    //!
    //! @param count       The new number of elements which will be container in the container.
    //! @param value       The value which will be used to copy construct the new content.
    //!
    //! @par Throws
    //!   If T's copy constructor or copy assignment throws.
    //!
    //! @par Complexity
    //!   Linear O(N).
    void assign(size_type count, value_type const& value);

    //! @pre <tt>size() < capacity()</tt>
    //!
    //! @brief Inserts a T constructed with
    //!   \c std::forward<Args>(args)... in the end of the container.
    //!
    //! @return A reference to the created object.
    //!
    //! @param args     The arguments of the constructor of the new element which will be created at the end of the container.
    //!
    //! @par Throws
    //!   If in-place constructor throws or T's move constructor throws.
    //!
    //! @par Complexity
    //!   Constant O(1).
    template<class ...Args>
    reference emplace_back(Args &&...args);

    //! @pre
    //!  @li \c p must be a valid iterator of \c *this in range <tt>[begin(), end()]</tt>
    //!  @li <tt>size() < capacity()</tt>
    //!
    //! @brief Inserts a T constructed with
    //!   \c std::forward<Args>(args)... before p
    //!
    //! @param p     The position at which new elements will be inserted.
    //! @param args  The arguments of the constructor of the new element.
    //!
    //! @par Throws
    //!   If in-place constructor throws or if T's move constructor or move assignment throws.
    //!
    //! @par Complexity
    //!   Constant or linear.
    template<class ...Args>
    iterator emplace(const_iterator p, Args &&...args);

    //! @brief Removes all elements from the container.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    void clear()  BOOST_NOEXCEPT_OR_NOTHROW;

    //! @pre <tt>i < size()</tt>
    //!
    //! @brief Returns reference to the i-th element.
    //!
    //! @param i    The element's index.
    //!
    //! @return reference to the i-th element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   \c std::out_of_range exception by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reference at(size_type i);

    //! @pre <tt>i < size()</tt>
    //!
    //! @brief Returns const reference to the i-th element.
    //!
    //! @param i    The element's index.
    //!
    //! @return const reference to the i-th element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   \c std::out_of_range exception by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reference at(size_type i) const;

    //! @pre <tt>i < size()</tt>
    //!
    //! @brief Returns reference to the i-th element.
    //!
    //! @param i    The element's index.
    //!
    //! @return reference to the i-th element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reference operator[](size_type i);

    //! @pre <tt>i < size()</tt>
    //!
    //! @brief Returns const reference to the i-th element.
    //!
    //! @param i    The element's index.
    //!
    //! @return const reference to the i-th element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reference operator[](size_type i) const;

    //! @pre <tt>i =< size()</tt>
    //!
    //! @brief Returns a iterator to the i-th element.
    //!
    //! @param i    The element's index.
    //!
    //! @return a iterator to the i-th element.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    iterator nth(size_type i);

    //! @pre <tt>i =< size()</tt>
    //!
    //! @brief Returns a const_iterator to the i-th element.
    //!
    //! @param i    The element's index.
    //!
    //! @return a const_iterator to the i-th element.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_iterator nth(size_type i) const;

    //! @pre <tt>begin() <= p <= end()</tt>
    //!
    //! @brief Returns the index of the element pointed by p.
    //!
    //! @param p    An iterator to the element.
    //!
    //! @return The index of the element pointed by p.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    size_type index_of(iterator p);

    //! @pre <tt>begin() <= p <= end()</tt>
    //!
    //! @brief Returns the index of the element pointed by p.
    //!
    //! @param p    A const_iterator to the element.
    //!
    //! @return a const_iterator to the i-th element.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    size_type index_of(const_iterator p) const;

    //! @pre \c !empty()
    //!
    //! @brief Returns reference to the first element.
    //!
    //! @return reference to the first element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reference front();

    //! @pre \c !empty()
    //!
    //! @brief Returns const reference to the first element.
    //!
    //! @return const reference to the first element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reference front() const;

    //! @pre \c !empty()
    //!
    //! @brief Returns reference to the last element.
    //!
    //! @return reference to the last element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reference back();

    //! @pre \c !empty()
    //!
    //! @brief Returns const reference to the first element.
    //!
    //! @return const reference to the last element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing by default.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reference back() const;

    //! @brief Pointer such that <tt>[data(), data() + size())</tt> is a valid range.
    //!   For a non-empty vector <tt>data() == &front()</tt>.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    T * data() BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Const pointer such that <tt>[data(), data() + size())</tt> is a valid range.
    //!   For a non-empty vector <tt>data() == &front()</tt>.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const T * data() const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns iterator to the first element.
    //!
    //! @return iterator to the first element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    iterator begin() BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns const iterator to the first element.
    //!
    //! @return const_iterator to the first element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_iterator begin() const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns const iterator to the first element.
    //!
    //! @return const_iterator to the first element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_iterator cbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns iterator to the one after the last element.
    //!
    //! @return iterator pointing to the one after the last element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    iterator end() BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns const iterator to the one after the last element.
    //!
    //! @return const_iterator pointing to the one after the last element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns const iterator to the one after the last element.
    //!
    //! @return const_iterator pointing to the one after the last element contained in the vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_iterator cend() const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns reverse iterator to the first element of the reversed container.
    //!
    //! @return reverse_iterator pointing to the beginning
    //! of the reversed static_vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reverse_iterator rbegin() BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns const reverse iterator to the first element of the reversed container.
    //!
    //! @return const_reverse_iterator pointing to the beginning
    //! of the reversed static_vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reverse_iterator rbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns const reverse iterator to the first element of the reversed container.
    //!
    //! @return const_reverse_iterator pointing to the beginning
    //! of the reversed static_vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reverse_iterator crbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns reverse iterator to the one after the last element of the reversed container.
    //!
    //! @return reverse_iterator pointing to the one after the last element
    //! of the reversed static_vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reverse_iterator rend() BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns const reverse iterator to the one after the last element of the reversed container.
    //!
    //! @return const_reverse_iterator pointing to the one after the last element
    //! of the reversed static_vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reverse_iterator rend() const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Returns const reverse iterator to the one after the last element of the reversed container.
    //!
    //! @return const_reverse_iterator pointing to the one after the last element
    //! of the reversed static_vector.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reverse_iterator crend() const BOOST_NOEXCEPT_OR_NOTHROW;

   #endif   //#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED

   //! @brief Returns container's capacity.
   //!
   //! @return container's capacity.
   //!
   //! @par Throws
   //!   Nothing.
   //!
   //! @par Complexity
   //!   Constant O(1).
   BOOST_CONTAINER_FORCEINLINE static size_type capacity() BOOST_NOEXCEPT_OR_NOTHROW
   { return static_capacity; }

   //! @brief Returns container's capacity.
   //!
   //! @return container's capacity.
   //!
   //! @par Throws
   //!   Nothing.
   //!
   //! @par Complexity
   //!   Constant O(1).
   BOOST_CONTAINER_FORCEINLINE static size_type max_size() BOOST_NOEXCEPT_OR_NOTHROW
   { return static_capacity; }

   #ifdef BOOST_CONTAINER_DOXYGEN_INVOKED

    //! @brief Returns the number of stored elements.
    //!
    //! @return Number of elements contained in the container.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    size_type size() const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @brief Queries if the container contains elements.
    //!
    //! @return true if the number of elements contained in the
    //!   container is equal to 0.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    bool empty() const BOOST_NOEXCEPT_OR_NOTHROW;
#else

   BOOST_CONTAINER_FORCEINLINE friend void swap(static_vector &x, static_vector &y)
   {
      x.swap(y);
   }

#endif // BOOST_CONTAINER_DOXYGEN_INVOKED

};

#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED

//! @brief Checks if contents of two static_vectors are equal.
//!
//! @ingroup static_vector_non_member
//!
//! @param x    The first static_vector.
//! @param y    The second static_vector.
//!
//! @return     \c true if containers have the same size and elements in both containers are equal.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2, class O1, class O2>
bool operator== (static_vector<V, C1, O1> const& x, static_vector<V, C2, O2> const& y);

//! @brief Checks if contents of two static_vectors are not equal.
//!
//! @ingroup static_vector_non_member
//!
//! @param x    The first static_vector.
//! @param y    The second static_vector.
//!
//! @return     \c true if containers have different size or elements in both containers are not equal.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2, class O1, class O2>
bool operator!= (static_vector<V, C1, O1> const& x, static_vector<V, C2, O2> const& y);

//! @brief Lexicographically compares static_vectors.
//!
//! @ingroup static_vector_non_member
//!
//! @param x    The first static_vector.
//! @param y    The second static_vector.
//!
//! @return     \c true if x compares lexicographically less than y.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2, class O1, class O2>
bool operator< (static_vector<V, C1, O1> const& x, static_vector<V, C2, O2> const& y);

//! @brief Lexicographically compares static_vectors.
//!
//! @ingroup static_vector_non_member
//!
//! @param x    The first static_vector.
//! @param y    The second static_vector.
//!
//! @return     \c true if y compares lexicographically less than x.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2, class O1, class O2>
bool operator> (static_vector<V, C1, O1> const& x, static_vector<V, C2, O2> const& y);

//! @brief Lexicographically compares static_vectors.
//!
//! @ingroup static_vector_non_member
//!
//! @param x    The first static_vector.
//! @param y    The second static_vector.
//!
//! @return     \c true if y don't compare lexicographically less than x.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2, class O1, class O2>
bool operator<= (static_vector<V, C1, O1> const& x, static_vector<V, C2, O2> const& y);

//! @brief Lexicographically compares static_vectors.
//!
//! @ingroup static_vector_non_member
//!
//! @param x    The first static_vector.
//! @param y    The second static_vector.
//!
//! @return     \c true if x don't compare lexicographically less than y.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2, class O1, class O2>
bool operator>= (static_vector<V, C1, O1> const& x, static_vector<V, C2, O2> const& y);

//! @brief Swaps contents of two static_vectors.
//!
//! This function calls static_vector::swap().
//!
//! @ingroup static_vector_non_member
//!
//! @param x    The first static_vector.
//! @param y    The second static_vector.
//!
//! @par Complexity
//!   Linear O(N).
template<typename V, std::size_t C1, std::size_t C2, class O1, class O2>
inline void swap(static_vector<V, C1, O1> & x, static_vector<V, C2, O2> & y);

#else

template<typename V, std::size_t C1, std::size_t C2, class O1, class O2>
inline void swap(static_vector<V, C1, O1> & x, static_vector<V, C2, O2> & y
      , typename dtl::enable_if_c< C1 != C2>::type * = 0)
{
   x.swap(y);
}

#endif // BOOST_CONTAINER_DOXYGEN_INVOKED

}} // namespace boost::container

#include <boost/container/detail/config_end.hpp>

#endif // BOOST_CONTAINER_STATIC_VECTOR_HPP

/* static_vector.hpp
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
*/
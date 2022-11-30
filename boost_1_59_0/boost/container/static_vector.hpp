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
//! Insertion beyond the capacity result in throwing bad_alloc() if exceptions are enabled or
//! calling throw_bad_alloc() if not enabled.
//!
//! out_of_range is thrown if out of bounds access is performed in <code>at()</code> if exceptions are
//! enabled, throw_out_of_range() if not enabled.
//!
//!@tparam T    The type of element that will be stored.
//!@tparam Capacity The maximum number of elements static_vector can store, fixed at compile time.
//!@tparam Options A type produced from \c boost::container::static_vector_options. If no option
//! is specified, by default throw_on_overflow<true> option is set.
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
    //!   @li If T's value initialization throws
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's default initialization throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's copy constructor throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's constructor taking a dereferenced Iterator throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's constructor taking a dereferenced std::initializer_list throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's copy constructor throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's copy constructor or copy assignment throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's copy constructor or copy assignment throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's value initialization throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's default initialization throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's copy constructor throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   If \c throw_on_overflow<true> option is set and the container runs out of capacity.
    //!
    //! @par Complexity
    //!   Constant O(1).
    void reserve(size_type count);

    //! @pre <tt>size() < capacity()</tt>
    //!
    //! @brief Adds a copy of value at the end.
    //!
    //! @param value    The value used to copy construct the new element.
    //!
    //! @par Throws
    //!   @li If T's copy constructor throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's move constructor throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
    //!
    //! @par Complexity
    //!   Constant O(1).
    void push_back(BOOST_RV_REF(value_type) value);

    //! @pre <tt>!empty()</tt>
    //!
    //! @brief Destroys last value and decreases the size.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    void pop_back() BOOST_NOEXCEPT_OR_NOTHROW;

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
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's move constructor or move assignment throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's copy constructor or copy assignment throws,
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's copy constructor or copy assignment throws,
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If T's copy constructor or copy assignment throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If in-place constructor throws or T's move constructor throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   @li If in-place constructor throws or if T's move constructor or move assignment throws.
    //!   @li If \c throw_on_overflow<true> option is set and the container runs out of capacity.
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
    //!   \c out_of_range exception by default.
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
    //!   \c out_of_range exception by default.
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
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reference operator[](size_type i) BOOST_NOEXCEPT_OR_NOTHROW;

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
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reference operator[](size_type i) const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @pre <tt>i =< size()</tt>
    //!
    //! @brief Returns a iterator to the i-th element.
    //!
    //! @param i    The element's index.
    //!
    //! @return a iterator to the i-th element.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    iterator nth(size_type i) BOOST_NOEXCEPT_OR_NOTHROW;

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
    const_iterator nth(size_type i) const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @pre <tt>begin() <= p <= end()</tt>
    //!
    //! @brief Returns the index of the element pointed by p.
    //!
    //! @param p    An iterator to the element.
    //!
    //! @return The index of the element pointed by p.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    size_type index_of(iterator p) BOOST_NOEXCEPT_OR_NOTHROW;

    //! @pre <tt>begin() <= p <= end()</tt>
    //!
    //! @brief Returns the index of the element pointed by p.
    //!
    //! @param p    A const_iterator to the element.
    //!
    //! @return a const_iterator to the i-th element.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    size_type index_of(const_iterator p) const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @pre \c !empty()
    //!
    //! @brief Returns reference to the first element.
    //!
    //! @return reference to the first element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reference front() BOOST_NOEXCEPT_OR_NOTHROW;

    //! @pre \c !empty()
    //!
    //! @brief Returns const reference to the first element.
    //!
    //! @return const reference to the first element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reference front() const BOOST_NOEXCEPT_OR_NOTHROW;

    //! @pre \c !empty()
    //!
    //! @brief Returns reference to the last element.
    //!
    //! @return reference to the last element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    reference back() BOOST_NOEXCEPT_OR_NOTHROW;

    //! @pre \c !empty()
    //!
    //! @brief Returns const reference to the first element.
    //!
    //! @return const reference to the last element
    //!   from the beginning of the container.
    //!
    //! @par Throws
    //!   Nothing.
    //!
    //! @par Complexity
    //!   Constant O(1).
    const_reference back() const BOOST_NOEXCEPT_OR_NOTHROW;

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
       BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT(x.swap(y)))
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
inline void swap(static_vector<V, C1, O1> & x, static_vector<V, C2, O2> & y)
    BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT(x.swap(y)));

#else

template<typename V, std::size_t C1, std::size_t C2, class O1, class O2>
inline void swap(static_vector<V, C1, O1> & x, static_vector<V, C2, O2> & y
      , typename dtl::enable_if_c< C1 != C2>::type * = 0)
    BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT(x.swap(y)))
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
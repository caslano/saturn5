//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_NEW_ALLOCATOR_HPP
#define BOOST_CONTAINER_NEW_ALLOCATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/throw_exception.hpp>
#include <cstddef>

//!\file

namespace boost {
namespace container {

/// @cond

template<bool Value>
struct new_allocator_bool
{  static const bool value = Value;  };

template<class T>
class new_allocator;

/// @endcond

//! Specialization of new_allocator for void types
template<>
class new_allocator<void>
{
   public:
   typedef void                                 value_type;
   typedef void *                               pointer;
   typedef const void*                          const_pointer;
   //!A integral constant of type bool with value true
   typedef BOOST_CONTAINER_IMPDEF(new_allocator_bool<true>) propagate_on_container_move_assignment;
   //!A integral constant of type bool with value true
   typedef BOOST_CONTAINER_IMPDEF(new_allocator_bool<true>) is_always_equal;
   // reference-to-void members are impossible

   //!Obtains an new_allocator that allocates
   //!objects of type T2
   template<class T2>
   struct rebind
   {
      typedef new_allocator< T2> other;
   };

   //!Default constructor
   //!Never throws
   new_allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Constructor from other new_allocator.
   //!Never throws
   new_allocator(const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Copy assignment operator from other new_allocator.
   //!Never throws
   new_allocator& operator=(const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {
       return *this;
   }

   //!Constructor from related new_allocator.
   //!Never throws
   template<class T2>
   new_allocator(const new_allocator<T2> &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Swaps two allocators, does nothing
   //!because this new_allocator is stateless
   friend void swap(new_allocator &, new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!An new_allocator always compares to true, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator==(const new_allocator &, const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return true;   }

   //!An new_allocator always compares to false, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator!=(const new_allocator &, const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return false;   }
};


//! This class is a reduced STL-compatible allocator that allocates memory using operator new
template<class T>
class new_allocator
{
   public:
   typedef T                                    value_type;
   typedef T *                                  pointer;
   typedef const T *                            const_pointer;
   typedef T &                                  reference;
   typedef const T &                            const_reference;
   typedef std::size_t                          size_type;
   typedef std::ptrdiff_t                       difference_type;
   //!A integral constant of type bool with value true
   typedef BOOST_CONTAINER_IMPDEF(new_allocator_bool<true>) propagate_on_container_move_assignment;
   //!A integral constant of type bool with value true
   typedef BOOST_CONTAINER_IMPDEF(new_allocator_bool<true>) is_always_equal;

   //!Obtains an new_allocator that allocates
   //!objects of type T2
   template<class T2>
   struct rebind
   {
      typedef new_allocator<T2> other;
   };

   //!Default constructor
   //!Never throws
   new_allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Constructor from other new_allocator.
   //!Never throws
   new_allocator(const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Copy assignment operator from other new_allocator.
   //!Never throws
   new_allocator& operator=(const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {
       return *this;
   }

   //!Constructor from related new_allocator.
   //!Never throws
   template<class T2>
   new_allocator(const new_allocator<T2> &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Allocates memory for an array of count elements.
   //!Throws std::bad_alloc if there is no enough memory
   pointer allocate(size_type count)
   {
      const std::size_t max_count = std::size_t(-1)/(2*sizeof(T));
      if(BOOST_UNLIKELY(count > max_count))
         throw_bad_alloc();
      return static_cast<T*>(::operator new(count*sizeof(T)));
   }

   //!Deallocates previously allocated memory.
   //!Never throws
   void deallocate(pointer ptr, size_type) BOOST_NOEXCEPT_OR_NOTHROW
     { ::operator delete((void*)ptr); }

   //!Returns the maximum number of elements that could be allocated.
   //!Never throws
   size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return std::size_t(-1)/(2*sizeof(T));   }

   //!Swaps two allocators, does nothing
   //!because this new_allocator is stateless
   friend void swap(new_allocator &, new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!An new_allocator always compares to true, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator==(const new_allocator &, const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return true;   }

   //!An new_allocator always compares to false, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator!=(const new_allocator &, const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return false;   }
};

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_NEW_ALLOCATOR_HPP

/* new_allocator.hpp
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
*/
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
   //!Throws bad_alloc if there is no enough memory
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
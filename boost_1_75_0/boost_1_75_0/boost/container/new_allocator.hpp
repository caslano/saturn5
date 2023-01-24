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
coZdF+rH2QHQ/R0QcrtQhvIdPwvl6Jqs23TCBArWp2wK18xljo4FdcDWPFiR6MxRzMfy7bF1/rbUNBnDOoeSWIeZ8vO0gu98DjLhb0PM8+a3H3HPZe/p74vWvqXTE2QSPeA1qlGbVKv0byrLf/uyCc/elbbehA4e9i/XKp9yKtcSpxGZLT7V0NkaXd9sF80zlK3RBhcbwZHcnK1u3QHbIM32DzxebMY7hde2SZ8y7Neafn8BVfb2pDIaosZcrn7K+HGi0dA19l2Cac0J/JHMvCYDp9PmGoay0RlzMm9Ij9w4BBaUk29yyxeQRjcrXBJcQ5fahM5zMorWgXQpXCNQPJPanZHjnF97eQFLT/y/1y4idth3ZjtmMCtXCPDId6XPziee9evSBgsHvDXrUFJA8HTJ9SPW51brwmmMEUMTDjfZiz3RuM52tLM/0sZvTOepXFHtUkn2CTeAzVU34EDzzlmfpieTDPd9noOwS86WjoApHg2DoZdtNdarcpIlfmabbSw1m5+O5xlFnkCF0PYbSDAVVt7frvpp1wsN+rrz6BbNONI66VqapaXtdfzFbKtjQZ5/FM402zHseb+YLZm26EIt4WtZFKEbJfmUs3+cmegYDkjrKkf/3Lo4jpS6dTXk160UTIJe3xEJHgPHkZ6e3T4S7DDjNIdYCba7KLx+Ryf3U86Z5o4lcwEF0fzk3efRe8XxX0OY224a0dop
*/
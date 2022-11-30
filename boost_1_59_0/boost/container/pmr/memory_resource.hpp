//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_MEMORY_RESOURCE_HPP
#define BOOST_CONTAINER_PMR_MEMORY_RESOURCE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/move/detail/type_traits.hpp>
#include <boost/container/detail/placement_new.hpp>
#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! The memory_resource class is an abstract interface to an
//! unbounded set of classes encapsulating memory resources.
class memory_resource
{
   public:
   // For exposition only
   static BOOST_CONSTEXPR_OR_CONST std::size_t max_align =
      boost::move_detail::alignment_of<boost::move_detail::max_align_t>::value;

   //! <b>Effects</b>: Destroys
   //! this memory_resource.
   virtual ~memory_resource(){}

   //! <b>Effects</b>: Equivalent to
   //! `return do_allocate(bytes, alignment);`
   void* allocate(std::size_t bytes, std::size_t alignment = max_align)
   {  
      //Obtain a pointer to enough storage and initialize the lifetime 
      //of an array object of the given size in the address
      return ::operator new(bytes, this->do_allocate(bytes, alignment), boost_container_new_t());
   }

   //! <b>Effects</b>: Equivalent to
   //! `return do_deallocate(bytes, alignment);`
   void  deallocate(void* p, std::size_t bytes, std::size_t alignment = max_align)
   {  return this->do_deallocate(p, bytes, alignment);  }

   //! <b>Effects</b>: Equivalent to
   //! `return return do_is_equal(other);`
   bool is_equal(const memory_resource& other) const BOOST_NOEXCEPT
   {  return this->do_is_equal(other);  }
   
   #if !defined(BOOST_EMBTC)

   //! <b>Returns</b>:
   //!   `&a == &b || a.is_equal(b)`.
   friend bool operator==(const memory_resource& a, const memory_resource& b) BOOST_NOEXCEPT
   {  return &a == &b || a.is_equal(b);   }

   //! <b>Returns</b>:
   //!   !(a == b).
   friend bool operator!=(const memory_resource& a, const memory_resource& b) BOOST_NOEXCEPT
   {  return !(a == b); }
   
   #else
   
   //! <b>Returns</b>:
   //!   `&a == &b || a.is_equal(b)`.
   friend bool operator==(const memory_resource& a, const memory_resource& b) BOOST_NOEXCEPT;

   //! <b>Returns</b>:
   //!   !(a == b).
   friend bool operator!=(const memory_resource& a, const memory_resource& b) BOOST_NOEXCEPT;
   
   #endif

   protected:
   //! <b>Requires</b>: Alignment shall be a power of two.
   //!
   //! <b>Returns</b>: A derived class shall implement this function to return a pointer
   //!   to allocated storage with a size of at least bytes. The returned storage is
   //!   aligned to the specified alignment, if such alignment is supported; otherwise
   //!   it is aligned to max_align.
   //!
   //! <b>Throws</b>: A derived class implementation shall throw an appropriate exception if
   //!   it is unable to allocate memory with the requested size and alignment.
   virtual void* do_allocate(std::size_t bytes, std::size_t alignment) = 0;

   //! <b>Requires</b>: p shall have been returned from a prior call to
   //!   `allocate(bytes, alignment)` on a memory resource equal to *this, and the storage
   //!   at p shall not yet have been deallocated.
   //!
   //! <b>Effects</b>: A derived class shall implement this function to dispose of allocated storage.
   //!
   //! <b>Throws</b>: Nothing.
   virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) = 0;

   //! <b>Returns</b>: A derived class shall implement this function to return true if memory
   //!   allocated from this can be deallocated from other and vice-versa; otherwise it shall
   //!   return false. <i>[Note: The most-derived type of other might not match the type of this.
   //!   For a derived class, D, a typical implementation of this function will compute
   //!   `dynamic_cast<const D*>(&other)` and go no further (i.e., return false)
   //!   if it returns nullptr. - end note]</i>.
   virtual bool do_is_equal(const memory_resource& other) const BOOST_NOEXCEPT = 0;
};

#if defined(BOOST_EMBTC)

//! <b>Returns</b>:
//!   `&a == &b || a.is_equal(b)`.
inline bool operator==(const memory_resource& a, const memory_resource& b) BOOST_NOEXCEPT
{  return &a == &b || a.is_equal(b);   }

//! <b>Returns</b>:
//!   !(a == b).
inline bool operator!=(const memory_resource& a, const memory_resource& b) BOOST_NOEXCEPT
{  return !(a == b); }

#endif
   
}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_MEMORY_RESOURCE_HPP

/* memory_resource.hpp
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
*/
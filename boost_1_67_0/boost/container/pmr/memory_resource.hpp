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
#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! The memory_resource class is an abstract interface to an
//! unbounded set of classes encapsulating memory resources.
class BOOST_CONTAINER_DECL memory_resource
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
   {  return this->do_allocate(bytes, alignment);  }

   //! <b>Effects</b>: Equivalent to
   //! `return do_deallocate(bytes, alignment);`
   void  deallocate(void* p, std::size_t bytes, std::size_t alignment = max_align)
   {  return this->do_deallocate(p, bytes, alignment);  }

   //! <b>Effects</b>: Equivalent to
   //! `return return do_is_equal(other);`
   bool is_equal(const memory_resource& other) const BOOST_NOEXCEPT
   {  return this->do_is_equal(other);  }

   //! <b>Returns</b>:
   //!   `&a == &b || a.is_equal(b)`.
   friend bool operator==(const memory_resource& a, const memory_resource& b) BOOST_NOEXCEPT
   {  return &a == &b || a.is_equal(b);   }

   //! <b>Returns</b>:
   //!   !(a == b).
   friend bool operator!=(const memory_resource& a, const memory_resource& b) BOOST_NOEXCEPT
   {  return !(a == b); }

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

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_MEMORY_RESOURCE_HPP

/* memory_resource.hpp
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
*/
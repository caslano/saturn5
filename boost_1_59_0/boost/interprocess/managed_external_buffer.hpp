//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_EXTERNAL_BUFFER_HPP
#define BOOST_INTERPROCESS_MANAGED_EXTERNAL_BUFFER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/assert.hpp>
//These includes needed to fulfill default template parameters of
//predeclarations in interprocess_fwd.hpp
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/sync/mutex_family.hpp>
#include <boost/interprocess/indexes/iset_index.hpp>

//!\file
//!Describes a named user memory allocation user class.

namespace boost {
namespace interprocess {

//!A basic user memory named object creation class. Inherits all
//!basic functionality from
//!basic_managed_memory_impl<CharType, AllocationAlgorithm, IndexType>*/
template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
class basic_managed_external_buffer
   : public ipcdetail::basic_managed_memory_impl <CharType, AllocationAlgorithm, IndexType>
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType>    base_t;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_managed_external_buffer)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef typename base_t::size_type              size_type;

   //!Default constructor. Does nothing.
   //!Useful in combination with move semantics
   basic_managed_external_buffer() BOOST_NOEXCEPT
   {}

   //!Creates and places the segment manager. This can throw
   //!The external memory supplied by the user shall be aligned to the maximum value between 
   //!`alignof(std::max_align_t)` and the strictest alignment of any over-aligned type to be built
   //!inside that memory.
   basic_managed_external_buffer
      (create_only_t, void *addr, size_type size)
   {
      //Check if alignment is correct
      BOOST_ASSERT((0 == (((std::size_t)addr) & (AllocationAlgorithm::Alignment - size_type(1u)))));
      if(!base_t::create_impl(addr, size)){
         throw interprocess_exception("Could not initialize buffer in basic_managed_external_buffer constructor");
      }
   }

   //!Creates and places the segment manager. This can throw
   //!The external memory supplied by the user shall be aligned to the maximum value between 
   //!`alignof(std::max_align_t)` and the strictest alignment of any over-aligned type to be built
   //!inside that memory.
   basic_managed_external_buffer
      (open_only_t, void *addr, size_type size)
   {
      //Check if alignment is correct
      BOOST_ASSERT((0 == (((std::size_t)addr) & (AllocationAlgorithm::Alignment - size_type(1u)))));
      if(!base_t::open_impl(addr, size)){
         throw interprocess_exception("Could not initialize buffer in basic_managed_external_buffer constructor");
      }
   }

   //!Moves the ownership of "moved"'s managed memory to *this. Does not throw
   basic_managed_external_buffer(BOOST_RV_REF(basic_managed_external_buffer) moved) BOOST_NOEXCEPT
   {
      this->swap(moved);
   }

   //!Moves the ownership of "moved"'s managed memory to *this. Does not throw
   basic_managed_external_buffer &operator=(BOOST_RV_REF(basic_managed_external_buffer) moved) BOOST_NOEXCEPT
   {
      basic_managed_external_buffer tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   void grow(size_type extra_bytes)
   {  base_t::grow(extra_bytes);   }

   //!Swaps the ownership of the managed heap memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_external_buffer &other) BOOST_NOEXCEPT
   {  base_t::swap(other); }
};

#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Typedef for a default basic_managed_external_buffer
//!of narrow characters
typedef basic_managed_external_buffer
   <char
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
managed_external_buffer;

//!Typedef for a default basic_managed_external_buffer
//!of wide characters
typedef basic_managed_external_buffer
   <wchar_t
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
wmanaged_external_buffer;

#endif   //#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_EXTERNAL_BUFFER_HPP


/* managed_external_buffer.hpp
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
*/
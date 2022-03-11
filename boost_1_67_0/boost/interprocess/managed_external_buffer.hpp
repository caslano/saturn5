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
   basic_managed_external_buffer()
   {}

   //!Creates and places the segment manager. This can throw
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
   basic_managed_external_buffer(BOOST_RV_REF(basic_managed_external_buffer) moved)
   {
      this->swap(moved);
   }

   //!Moves the ownership of "moved"'s managed memory to *this. Does not throw
   basic_managed_external_buffer &operator=(BOOST_RV_REF(basic_managed_external_buffer) moved)
   {
      basic_managed_external_buffer tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   void grow(size_type extra_bytes)
   {  base_t::grow(extra_bytes);   }

   //!Swaps the ownership of the managed heap memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_external_buffer &other)
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
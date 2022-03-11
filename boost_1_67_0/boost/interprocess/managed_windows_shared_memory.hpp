//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_WINDOWS_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_MANAGED_WINDOWS_SHARED_MEMORY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/move/utility_core.hpp>
//These includes needed to fulfill default template parameters of
//predeclarations in interprocess_fwd.hpp
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/sync/mutex_family.hpp>
#include <boost/interprocess/indexes/iset_index.hpp>

namespace boost {
namespace interprocess {

namespace ipcdetail {

template<class AllocationAlgorithm>
struct wshmem_open_or_create
{
   typedef  ipcdetail::managed_open_or_create_impl
      < windows_shared_memory, AllocationAlgorithm::Alignment, false, false> type;
};

}  //namespace ipcdetail {

//!A basic managed windows shared memory creation class. Initializes the
//!shared memory segment. Inherits all basic functionality from
//!basic_managed_memory_impl<CharType, AllocationAlgorithm, IndexType>
//!Unlike basic_managed_shared_memory, it has
//!no kernel persistence and the shared memory is destroyed
//!when all processes destroy all their windows_shared_memory
//!objects and mapped regions for the same shared memory
//!or the processes end/crash.
//!
//!Warning: basic_managed_windows_shared_memory and
//!basic_managed_shared_memory can't communicate between them.
template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
class basic_managed_windows_shared_memory
   : public ipcdetail::basic_managed_memory_impl
      < CharType, AllocationAlgorithm, IndexType
      , ipcdetail::wshmem_open_or_create<AllocationAlgorithm>::type::ManagedOpenOrCreateUserOffset>
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType,
      ipcdetail::wshmem_open_or_create<AllocationAlgorithm>::type::ManagedOpenOrCreateUserOffset>   base_t;
   typedef ipcdetail::create_open_func<base_t>        create_open_func_t;

   basic_managed_windows_shared_memory *get_this_pointer()
   {  return this;   }

   private:
   typedef typename base_t::char_ptr_holder_t   char_ptr_holder_t;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_managed_windows_shared_memory)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public: //functions
   typedef typename base_t::size_type              size_type;

   //!Default constructor. Does nothing.
   //!Useful in combination with move semantics
   basic_managed_windows_shared_memory()
   {}

   //!Creates shared memory and creates and places the segment manager.
   //!This can throw.
   basic_managed_windows_shared_memory
      (create_only_t, const char *name,
     size_type size, const void *addr = 0, const permissions &perm = permissions())
      : m_wshm(create_only, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoCreate), perm)
   {}

   //!Creates shared memory and creates and places the segment manager if
   //!segment was not created. If segment was created it connects to the
   //!segment.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_or_create_t,
      const char *name, size_type size,
      const void *addr = 0,
      const permissions &perm = permissions())
      : m_wshm(open_or_create, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpenOrCreate), perm)
   {}

   //!Connects to a created shared memory and its segment manager.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_only_t, const char* name, const void *addr = 0)
      : m_wshm(open_only, name, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager
   //!in copy_on_write mode.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_copy_on_write_t, const char* name, const void *addr = 0)
      : m_wshm(open_only, name, copy_on_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager
   //!in read-only mode.
   //!This can throw.
   basic_managed_windows_shared_memory
      (open_read_only_t, const char* name, const void *addr = 0)
      : base_t()
      , m_wshm(open_only, name, read_only, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoOpen))
   {}

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_windows_shared_memory
      (BOOST_RV_REF(basic_managed_windows_shared_memory) moved)
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_windows_shared_memory &operator=(BOOST_RV_REF(basic_managed_windows_shared_memory) moved)
   {
      basic_managed_windows_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. All mapped regions are still valid after
   //!destruction. When all mapped regions and basic_managed_windows_shared_memory
   //!objects referring the shared memory are destroyed, the
   //!operating system will destroy the shared memory.
   ~basic_managed_windows_shared_memory()
   {}

   //!Swaps the ownership of the managed mapped memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_windows_shared_memory &other)
   {
      base_t::swap(other);
      m_wshm.swap(other.m_wshm);
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Tries to find a previous named allocation address. Returns a memory
   //!buffer and the object count. If not found returned pointer is 0.
   //!Never throws.
   template <class T>
   std::pair<T*, size_type> find  (char_ptr_holder_t name)
   {
      if(m_wshm.get_mapped_region().get_mode() == read_only){
         return base_t::template find_no_lock<T>(name);
      }
      else{
         return base_t::template find<T>(name);
      }
   }

   private:
   typename ipcdetail::wshmem_open_or_create<AllocationAlgorithm>::type m_wshm;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Typedef for a default basic_managed_windows_shared_memory
//!of narrow characters
typedef basic_managed_windows_shared_memory
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_windows_shared_memory;

//!Typedef for a default basic_managed_windows_shared_memory
//!of wide characters
typedef basic_managed_windows_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_windows_shared_memory;

#endif   //#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED


}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_WINDOWS_SHARED_MEMORY_HPP

/* managed_windows_shared_memory.hpp
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
*/
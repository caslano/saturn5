//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_XSI_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_MANAGED_XSI_SHARED_MEMORY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#if !defined(BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS)
#error "This header can't be used in operating systems without XSI (System V) shared memory support"
#endif

#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/detail/xsi_shared_memory_file_wrapper.hpp>
#include <boost/interprocess/creation_tags.hpp>
//These includes needed to fulfill default template parameters of
//predeclarations in interprocess_fwd.hpp
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/sync/mutex_family.hpp>
#include <boost/interprocess/indexes/iset_index.hpp>

namespace boost {

namespace interprocess {

namespace ipcdetail {

template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
struct xsishmem_open_or_create
{
   static const std::size_t segment_manager_alignment = boost::move_detail::alignment_of
         < segment_manager
               < CharType
               , AllocationAlgorithm
               , IndexType>
         >::value;
   static const std::size_t final_segment_manager_alignment
      = segment_manager_alignment > AllocationAlgorithm::Alignment
      ? segment_manager_alignment : AllocationAlgorithm::Alignment;

   typedef  ipcdetail::managed_open_or_create_impl
      < xsi_shared_memory_file_wrapper
      , final_segment_manager_alignment
      , false
      , true> type;
};


}  //namespace ipcdetail {

//!A basic X/Open System Interface (XSI) shared memory named object creation class. Initializes the
//!shared memory segment. Inherits all basic functionality from
//!basic_managed_memory_impl<CharType, AllocationAlgorithm, IndexType>
template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
class basic_managed_xsi_shared_memory
   : public ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType
      ,ipcdetail::xsishmem_open_or_create<CharType, AllocationAlgorithm, IndexType>
         ::type::ManagedOpenOrCreateUserOffset>
   , private ipcdetail::xsishmem_open_or_create
      <CharType, AllocationAlgorithm, IndexType>::type
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   public:
   typedef xsi_shared_memory_file_wrapper device_type;

   public:
   typedef typename ipcdetail::xsishmem_open_or_create
      <CharType, AllocationAlgorithm, IndexType>::type base2_t;
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType,
      base2_t::ManagedOpenOrCreateUserOffset>          base_t;

   typedef ipcdetail::create_open_func<base_t>        create_open_func_t;

   basic_managed_xsi_shared_memory *get_this_pointer()
   {  return this;   }

   private:
   typedef typename base_t::char_ptr_holder_t   char_ptr_holder_t;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_managed_xsi_shared_memory)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public: //functions
   typedef typename base_t::size_type              size_type;

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~basic_managed_xsi_shared_memory()
   {}

   //!Default constructor. Does nothing.
   //!Useful in combination with move semantics
   basic_managed_xsi_shared_memory() BOOST_NOEXCEPT
   {}

   //!Creates shared memory and creates and places the segment manager.
   //!This can throw.
   basic_managed_xsi_shared_memory(create_only_t, const xsi_key &key,
                             std::size_t size, const void *addr = 0, const permissions& perm = permissions())
      : base_t()
      , base2_t(create_only, key, size, read_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoCreate), perm)
   {}

   //!Creates shared memory and creates and places the segment manager if
   //!segment was not created. If segment was created it connects to the
   //!segment.
   //!This can throw.
   basic_managed_xsi_shared_memory (open_or_create_t,
                              const xsi_key &key, std::size_t size,
                              const void *addr = 0, const permissions& perm = permissions())
      : base_t()
      , base2_t(open_or_create, key, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpenOrCreate), perm)
   {}

   //!Connects to a created shared memory and its segment manager.
   //!in read-only mode.
   //!This can throw.
   basic_managed_xsi_shared_memory (open_read_only_t, const xsi_key &key,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, key, read_only, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager.
   //!This can throw.
   basic_managed_xsi_shared_memory (open_only_t, const xsi_key &key,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, key, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_xsi_shared_memory(BOOST_RV_REF(basic_managed_xsi_shared_memory) moved) BOOST_NOEXCEPT
   {
      basic_managed_xsi_shared_memory tmp;
      this->swap(moved);
      tmp.swap(moved);
   }

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_xsi_shared_memory &operator=(BOOST_RV_REF(basic_managed_xsi_shared_memory) moved) BOOST_NOEXCEPT
   {
      basic_managed_xsi_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps the ownership of the managed shared memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_xsi_shared_memory &other) BOOST_NOEXCEPT
   {
      base_t::swap(other);
      base2_t::swap(other);
   }

   //!Erases a XSI shared memory object identified by shmid
   //!from the system.
   //!Returns false on error. Never throws
   static bool remove(int shmid)
   {  return device_type::remove(shmid); }

   int get_shmid() const BOOST_NOEXCEPT
   {  return base2_t::get_device().get_shmid(); }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Tries to find a previous named allocation address. Returns a memory
   //!buffer and the object count. If not found returned pointer is 0.
   //!Never throws.
   template <class T>
   std::pair<T*, std::size_t> find  (char_ptr_holder_t name)
   {
      if(base2_t::get_mapped_region().get_mode() == read_only){
         return base_t::template find_no_lock<T>(name);
      }
      else{
         return base_t::template find<T>(name);
      }
   }

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Typedef for a default basic_managed_xsi_shared_memory
//!of narrow characters
typedef basic_managed_xsi_shared_memory
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_xsi_shared_memory;

//!Typedef for a default basic_managed_xsi_shared_memory
//!of wide characters
typedef basic_managed_xsi_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_xsi_shared_memory;

#endif   //#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_XSI_SHARED_MEMORY_HPP


/* managed_xsi_shared_memory.hpp
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
*/
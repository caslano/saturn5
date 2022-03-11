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

template<class AllocationAlgorithm>
struct xsishmem_open_or_create
{
   typedef  ipcdetail::managed_open_or_create_impl                 //!FileBased, StoreDevice
      < xsi_shared_memory_file_wrapper, AllocationAlgorithm::Alignment, false, true> type;
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
      ,ipcdetail::xsishmem_open_or_create<AllocationAlgorithm>::type::ManagedOpenOrCreateUserOffset>
   , private ipcdetail::xsishmem_open_or_create<AllocationAlgorithm>::type
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   public:
   typedef xsi_shared_memory_file_wrapper device_type;

   public:
   typedef typename ipcdetail::xsishmem_open_or_create<AllocationAlgorithm>::type base2_t;
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType,
      base2_t::ManagedOpenOrCreateUserOffset>   base_t;

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
   basic_managed_xsi_shared_memory()
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
   basic_managed_xsi_shared_memory(BOOST_RV_REF(basic_managed_xsi_shared_memory) moved)
   {
      basic_managed_xsi_shared_memory tmp;
      this->swap(moved);
      tmp.swap(moved);
   }

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_xsi_shared_memory &operator=(BOOST_RV_REF(basic_managed_xsi_shared_memory) moved)
   {
      basic_managed_xsi_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps the ownership of the managed shared memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_xsi_shared_memory &other)
   {
      base_t::swap(other);
      base2_t::swap(other);
   }

   //!Erases a XSI shared memory object identified by shmid
   //!from the system.
   //!Returns false on error. Never throws
   static bool remove(int shmid)
   {  return device_type::remove(shmid); }

   int get_shmid() const
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
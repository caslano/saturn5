//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_MANAGED_SHARED_MEMORY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/permissions.hpp>
//These includes needed to fulfill default template parameters of
//predeclarations in interprocess_fwd.hpp
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/sync/mutex_family.hpp>

namespace boost {
namespace interprocess {

namespace ipcdetail {

template<class AllocationAlgorithm>
struct shmem_open_or_create
{
   typedef  ipcdetail::managed_open_or_create_impl
      < shared_memory_object, AllocationAlgorithm::Alignment, true, false> type;
};

}  //namespace ipcdetail {

//!A basic shared memory named object creation class. Initializes the
//!shared memory segment. Inherits all basic functionality from
//!basic_managed_memory_impl<CharType, AllocationAlgorithm, IndexType>*/
template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
class basic_managed_shared_memory
   : public ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType
      ,ipcdetail::shmem_open_or_create<AllocationAlgorithm>::type::ManagedOpenOrCreateUserOffset>
   , private ipcdetail::shmem_open_or_create<AllocationAlgorithm>::type
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType,
      ipcdetail::shmem_open_or_create<AllocationAlgorithm>::type::ManagedOpenOrCreateUserOffset>   base_t;
   typedef typename ipcdetail::shmem_open_or_create<AllocationAlgorithm>::type                     base2_t;

   typedef ipcdetail::create_open_func<base_t>        create_open_func_t;

   basic_managed_shared_memory *get_this_pointer()
   {  return this;   }

   public:
   typedef shared_memory_object                    device_type;
   typedef typename base_t::size_type              size_type;

   private:
   typedef typename base_t::char_ptr_holder_t   char_ptr_holder_t;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_managed_shared_memory)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public: //functions

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~basic_managed_shared_memory()
   {}

   //!Default constructor. Does nothing.
   //!Useful in combination with move semantics
   basic_managed_shared_memory()
   {}

   //!Creates shared memory and creates and places the segment manager.
   //!This can throw.
   basic_managed_shared_memory(create_only_t, const char *name,
                             size_type size, const void *addr = 0, const permissions& perm = permissions())
      : base_t()
      , base2_t(create_only, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoCreate), perm)
   {}

   //!Creates shared memory and creates and places the segment manager if
   //!segment was not created. If segment was created it connects to the
   //!segment.
   //!This can throw.
   basic_managed_shared_memory (open_or_create_t,
                              const char *name, size_type size,
                              const void *addr = 0, const permissions& perm = permissions())
      : base_t()
      , base2_t(open_or_create, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpenOrCreate), perm)
   {}

   //!Connects to a created shared memory and its segment manager.
   //!in copy_on_write mode.
   //!This can throw.
   basic_managed_shared_memory (open_copy_on_write_t, const char* name,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, name, copy_on_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager.
   //!in read-only mode.
   //!This can throw.
   basic_managed_shared_memory (open_read_only_t, const char* name,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, name, read_only, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager.
   //!This can throw.
   basic_managed_shared_memory (open_only_t, const char* name,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, name, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_shared_memory(BOOST_RV_REF(basic_managed_shared_memory) moved)
   {
      basic_managed_shared_memory tmp;
      this->swap(moved);
      tmp.swap(moved);
   }

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_shared_memory &operator=(BOOST_RV_REF(basic_managed_shared_memory) moved)
   {
      basic_managed_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps the ownership of the managed shared memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_shared_memory &other)
   {
      base_t::swap(other);
      base2_t::swap(other);
   }

   //!Tries to resize the managed shared memory object so that we have
   //!room for more objects.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   static bool grow(const char *shmname, size_type extra_bytes)
   {
      return base_t::template grow
         <basic_managed_shared_memory>(shmname, extra_bytes);
   }

   //!Tries to resize the managed shared memory to minimized the size of the file.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   static bool shrink_to_fit(const char *shmname)
   {
      return base_t::template shrink_to_fit
         <basic_managed_shared_memory>(shmname);
   }
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Tries to find a previous named allocation address. Returns a memory
   //!buffer and the object count. If not found returned pointer is 0.
   //!Never throws.
   template <class T>
   std::pair<T*, size_type> find  (char_ptr_holder_t name)
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

//!Typedef for a default basic_managed_shared_memory
//!of narrow characters
typedef basic_managed_shared_memory
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_shared_memory;

//!Typedef for a default basic_managed_shared_memory
//!of wide characters
typedef basic_managed_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_shared_memory;

//!Typedef for a default basic_managed_shared_memory
//!of narrow characters to be placed in a fixed address
typedef basic_managed_shared_memory
   <char
   ,rbtree_best_fit<mutex_family, void*>
   ,iset_index>
fixed_managed_shared_memory;

//!Typedef for a default basic_managed_shared_memory
//!of narrow characters to be placed in a fixed address
typedef basic_managed_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family, void*>
   ,iset_index>
wfixed_managed_shared_memory;


#endif   //#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_SHARED_MEMORY_HPP


/* managed_shared_memory.hpp
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
*/
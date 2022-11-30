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

template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
struct shmem_open_or_create
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

   typedef ipcdetail::managed_open_or_create_impl
      < shared_memory_object
      , final_segment_manager_alignment
      , true
      , false> type;
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
      < CharType, AllocationAlgorithm, IndexType
      , ipcdetail::shmem_open_or_create<CharType, AllocationAlgorithm, IndexType>::type::ManagedOpenOrCreateUserOffset>
   , private ipcdetail::shmem_open_or_create<CharType, AllocationAlgorithm, IndexType>::type
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef typename ipcdetail::shmem_open_or_create
      < CharType
      , AllocationAlgorithm
      , IndexType>::type                                 base2_t;
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType,
      base2_t::ManagedOpenOrCreateUserOffset>            base_t;

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

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates shared memory and creates and places the segment manager.
   //!This can throw.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   basic_managed_shared_memory(create_only_t, const wchar_t *name,
                             size_type size, const void *addr = 0, const permissions& perm = permissions())
      : base_t()
      , base2_t(create_only, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoCreate), perm)
   {}

   //!Creates shared memory and creates and places the segment manager if
   //!segment was not created. If segment was created it connects to the
   //!segment.
   //!This can throw.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   basic_managed_shared_memory (open_or_create_t,
                              const wchar_t *name, size_type size,
                              const void *addr = 0, const permissions& perm = permissions())
      : base_t()
      , base2_t(open_or_create, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpenOrCreate), perm)
   {}

   //!Connects to a created shared memory and its segment manager.
   //!in copy_on_write mode.
   //!This can throw.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   basic_managed_shared_memory (open_copy_on_write_t, const wchar_t* name,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, name, copy_on_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager.
   //!in read-only mode.
   //!This can throw.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   basic_managed_shared_memory (open_read_only_t, const wchar_t* name,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, name, read_only, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager.
   //!This can throw.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   basic_managed_shared_memory (open_only_t, const wchar_t* name,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, name, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

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

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Tries to resize the managed shared memory object so that we have
   //!room for more objects.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool grow(const wchar_t *shmname, size_type extra_bytes)
   {
      return base_t::template grow
         <basic_managed_shared_memory>(shmname, extra_bytes);
   }

   //!Tries to resize the managed shared memory to minimized the size of the file.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool shrink_to_fit(const wchar_t *shmname)
   {
      return base_t::template shrink_to_fit
         <basic_managed_shared_memory>(shmname);
   }

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

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
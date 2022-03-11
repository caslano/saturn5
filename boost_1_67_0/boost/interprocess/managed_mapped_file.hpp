//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_MAPPED_FILE_HPP
#define BOOST_INTERPROCESS_MANAGED_MAPPED_FILE_HPP

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
#include <boost/interprocess/detail/file_wrapper.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/permissions.hpp>
//These includes needed to fulfill default template parameters of
//predeclarations in interprocess_fwd.hpp
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/sync/mutex_family.hpp>
#include <boost/interprocess/indexes/iset_index.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

template<class AllocationAlgorithm>
struct mfile_open_or_create
{
   typedef  ipcdetail::managed_open_or_create_impl
      < file_wrapper, AllocationAlgorithm::Alignment, true, false> type;
};

}  //namespace ipcdetail {

//!A basic mapped file named object creation class. Initializes the
//!mapped file. Inherits all basic functionality from
//!basic_managed_memory_impl<CharType, AllocationAlgorithm, IndexType>
template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
class basic_managed_mapped_file
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   : public ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType
      ,ipcdetail::mfile_open_or_create<AllocationAlgorithm>::type::ManagedOpenOrCreateUserOffset>
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   public:
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType,
      ipcdetail::mfile_open_or_create<AllocationAlgorithm>::type::ManagedOpenOrCreateUserOffset>   base_t;
   typedef ipcdetail::file_wrapper device_type;

   private:

   typedef ipcdetail::create_open_func<base_t>        create_open_func_t;

   basic_managed_mapped_file *get_this_pointer()
   {  return this;   }

   private:
   typedef typename base_t::char_ptr_holder_t   char_ptr_holder_t;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_managed_mapped_file)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public: //functions

   //!Unsigned integral type enough to represent
   //!the size of a basic_managed_mapped_file.
   typedef typename BOOST_INTERPROCESS_IMPDEF(base_t::size_type) size_type;

   //!Creates mapped file and creates and places the segment manager.
   //!This can throw.
   basic_managed_mapped_file()
   {}

   //!Creates mapped file and creates and places the segment manager.
   //!This can throw.
   basic_managed_mapped_file(create_only_t, const char *name,
                             size_type size, const void *addr = 0, const permissions &perm = permissions())
      : m_mfile(create_only, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoCreate), perm)
   {}

   //!Creates mapped file and creates and places the segment manager if
   //!segment was not created. If segment was created it connects to the
   //!segment.
   //!This can throw.
   basic_managed_mapped_file (open_or_create_t,
                              const char *name, size_type size,
                              const void *addr = 0, const permissions &perm = permissions())
      : m_mfile(open_or_create, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpenOrCreate), perm)
   {}

   //!Connects to a created mapped file and its segment manager.
   //!This can throw.
   basic_managed_mapped_file (open_only_t, const char* name,
                              const void *addr = 0)
      : m_mfile(open_only, name, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created mapped file and its segment manager
   //!in copy_on_write mode.
   //!This can throw.
   basic_managed_mapped_file (open_copy_on_write_t, const char* name,
                              const void *addr = 0)
      : m_mfile(open_only, name, copy_on_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created mapped file and its segment manager
   //!in read-only mode.
   //!This can throw.
   basic_managed_mapped_file (open_read_only_t, const char* name,
                              const void *addr = 0)
      : m_mfile(open_only, name, read_only, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_mapped_file(BOOST_RV_REF(basic_managed_mapped_file) moved)
   {
      this->swap(moved);
   }

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_mapped_file &operator=(BOOST_RV_REF(basic_managed_mapped_file) moved)
   {
      basic_managed_mapped_file tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~basic_managed_mapped_file()
   {}

   //!Swaps the ownership of the managed mapped memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_mapped_file &other)
   {
      base_t::swap(other);
      m_mfile.swap(other.m_mfile);
   }

   //!Flushes cached data to file.
   //!Never throws
   bool flush()
   {  return m_mfile.flush();  }

   //!Tries to resize mapped file so that we have room for
   //!more objects.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   static bool grow(const char *filename, size_type extra_bytes)
   {
      return base_t::template grow
         <basic_managed_mapped_file>(filename, extra_bytes);
   }

   //!Tries to resize mapped file to minimized the size of the file.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   static bool shrink_to_fit(const char *filename)
   {
      return base_t::template shrink_to_fit
         <basic_managed_mapped_file>(filename);
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Tries to find a previous named allocation address. Returns a memory
   //!buffer and the object count. If not found returned pointer is 0.
   //!Never throws.
   template <class T>
   std::pair<T*, size_type> find  (char_ptr_holder_t name)
   {
      if(m_mfile.get_mapped_region().get_mode() == read_only){
         return base_t::template find_no_lock<T>(name);
      }
      else{
         return base_t::template find<T>(name);
      }
   }

   private:
   typename ipcdetail::mfile_open_or_create<AllocationAlgorithm>::type m_mfile;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Typedef for a default basic_managed_mapped_file
//!of narrow characters
typedef basic_managed_mapped_file
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_mapped_file;

//!Typedef for a default basic_managed_mapped_file
//!of wide characters
typedef basic_managed_mapped_file
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_mapped_file;

#endif   //#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_MAPPED_FILE_HPP

/* managed_mapped_file.hpp
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
*/
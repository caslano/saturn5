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

template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
struct mfile_open_or_create
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
      < file_wrapper
      , final_segment_manager_alignment
      , true
      , false> type;
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
      < CharType, AllocationAlgorithm, IndexType
      , ipcdetail::mfile_open_or_create
         <CharType, AllocationAlgorithm, IndexType>::type::ManagedOpenOrCreateUserOffset>
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   public:
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType,
      ipcdetail::mfile_open_or_create<CharType, AllocationAlgorithm, IndexType>
         ::type::ManagedOpenOrCreateUserOffset>   base_t;
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
   basic_managed_mapped_file() BOOST_NOEXCEPT
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

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates mapped file and creates and places the segment manager.
   //!This can throw.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   basic_managed_mapped_file(create_only_t, const wchar_t *name,
                             size_type size, const void *addr = 0, const permissions &perm = permissions())
      : m_mfile(create_only, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoCreate), perm)
   {}

   //!Creates mapped file and creates and places the segment manager if
   //!segment was not created. If segment was created it connects to the
   //!segment.
   //!This can throw.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   basic_managed_mapped_file (open_or_create_t,
                              const wchar_t *name, size_type size,
                              const void *addr = 0, const permissions &perm = permissions())
      : m_mfile(open_or_create, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpenOrCreate), perm)
   {}

   //!Connects to a created mapped file and its segment manager.
   //!This can throw.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   basic_managed_mapped_file (open_only_t, const wchar_t* name,
                              const void *addr = 0)
      : m_mfile(open_only, name, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created mapped file and its segment manager
   //!in copy_on_write mode.
   //!This can throw.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   basic_managed_mapped_file (open_copy_on_write_t, const wchar_t* name,
                              const void *addr = 0)
      : m_mfile(open_only, name, copy_on_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created mapped file and its segment manager
   //!in read-only mode.
   //!This can throw.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   basic_managed_mapped_file (open_read_only_t, const wchar_t* name,
                              const void *addr = 0)
      : m_mfile(open_only, name, read_only, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_mapped_file(BOOST_RV_REF(basic_managed_mapped_file) moved) BOOST_NOEXCEPT
   {
      this->swap(moved);
   }

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_mapped_file &operator=(BOOST_RV_REF(basic_managed_mapped_file) moved) BOOST_NOEXCEPT
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
   void swap(basic_managed_mapped_file &other) BOOST_NOEXCEPT
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

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Tries to resize mapped file so that we have room for
   //!more objects.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool grow(const wchar_t *filename, size_type extra_bytes)
   {
      return base_t::template grow
         <basic_managed_mapped_file>(filename, extra_bytes);
   }

   //!Tries to resize mapped file to minimized the size of the file.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool shrink_to_fit(const wchar_t *filename)
   {
      return base_t::template shrink_to_fit
         <basic_managed_mapped_file>(filename);
   }

   #endif

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
   typename ipcdetail::mfile_open_or_create
      <CharType, AllocationAlgorithm, IndexType>::type m_mfile;
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
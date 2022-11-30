//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_WINDOWS_SHARED_MEMORY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/simple_swap.hpp>
#include <boost/interprocess/detail/char_wchar_holder.hpp>

#if !defined(BOOST_INTERPROCESS_WINDOWS)
#error "This header can only be used in Windows operating systems"
#endif

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/win32_api.hpp>
#include <cstddef>
#include <boost/cstdint.hpp>


//!\file
//!Describes a class representing a native windows shared memory.

namespace boost {
namespace interprocess {

//!A class that wraps the native Windows shared memory
//!that is implemented as a file mapping of the paging file.
//!Unlike shared_memory_object, windows_shared_memory has
//!no kernel persistence and the shared memory is destroyed
//!when all processes destroy all their windows_shared_memory
//!objects and mapped regions for the same shared memory
//!or the processes end/crash.
//!
//!Warning: Windows native shared memory and interprocess portable
//!shared memory (boost::interprocess::shared_memory_object)
//!can't communicate between them.
class windows_shared_memory
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable and non-assignable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(windows_shared_memory)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Default constructor.
   //!Represents an empty windows_shared_memory.
   windows_shared_memory() BOOST_NOEXCEPT;

   //!Creates a new native shared memory with name "name" and at least size "size",
   //!with the access mode "mode".
   //!If the file previously exists, throws an error.
   windows_shared_memory(create_only_t, const char *name, mode_t mode, std::size_t size, const permissions& perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, name, mode, size, perm);  }

   //!Tries to create a shared memory object with name "name" and at least size "size", with the
   //!access mode "mode". If the file previously exists, it tries to open it with mode "mode".
   //!Otherwise throws an error.
   windows_shared_memory(open_or_create_t, const char *name, mode_t mode, std::size_t size, const permissions& perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoOpenOrCreate, name, mode, size, perm);  }

   //!Tries to open a shared memory object with name "name", with the access mode "mode".
   //!If the file does not previously exist, it throws an error.
   windows_shared_memory(open_only_t, const char *name, mode_t mode)
   {  this->priv_open_or_create(ipcdetail::DoOpen, name, mode, 0, permissions());  }

   //!Creates a new native shared memory with name "name" and at least size "size",
   //!with the access mode "mode".
   //!If the file previously exists, throws an error.
   windows_shared_memory(create_only_t, const wchar_t *name, mode_t mode, std::size_t size, const permissions& perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, name, mode, size, perm);  }

   //!Tries to create a shared memory object with name "name" and at least size "size", with the
   //!access mode "mode". If the file previously exists, it tries to open it with mode "mode".
   //!Otherwise throws an error.
   windows_shared_memory(open_or_create_t, const wchar_t *name, mode_t mode, std::size_t size, const permissions& perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoOpenOrCreate, name, mode, size, perm);  }

   //!Tries to open a shared memory object with name "name", with the access mode "mode".
   //!If the file does not previously exist, it throws an error.
   windows_shared_memory(open_only_t, const wchar_t *name, mode_t mode)
   {  this->priv_open_or_create(ipcdetail::DoOpen, name, mode, 0, permissions());  }

   //!Moves the ownership of "moved"'s shared memory object to *this.
   //!After the call, "moved" does not represent any shared memory object.
   //!Does not throw
   windows_shared_memory(BOOST_RV_REF(windows_shared_memory) moved) BOOST_NOEXCEPT
      : m_handle(0)
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s shared memory to *this.
   //!After the call, "moved" does not represent any shared memory.
   //!Does not throw
   windows_shared_memory &operator=(BOOST_RV_REF(windows_shared_memory) moved) BOOST_NOEXCEPT
   {
      windows_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps to shared_memory_objects. Does not throw
   void swap(windows_shared_memory &other) BOOST_NOEXCEPT;

   //!Destroys *this. All mapped regions are still valid after
   //!destruction. When all mapped regions and windows_shared_memory
   //!objects referring the shared memory are destroyed, the
   //!operating system will destroy the shared memory.
   ~windows_shared_memory();

   //!Returns the name of the shared memory.
   const char *get_name() const BOOST_NOEXCEPT;

   //!Returns access mode
   mode_t get_mode() const BOOST_NOEXCEPT;

   //!Returns the mapping handle. Never throws
   mapping_handle_t get_mapping_handle() const BOOST_NOEXCEPT;

   //!Returns the size of the windows shared memory. It will be a 4K rounded
   //!size of the "size" passed in the constructor.
   offset_t get_size() const BOOST_NOEXCEPT;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   //!Closes a previously opened file mapping. Never throws.
   void priv_close();

   //!Closes a previously opened file mapping. Never throws.
   template <class CharT>
   bool priv_open_or_create(ipcdetail::create_enum_t type, const CharT *filename, mode_t mode, std::size_t size, const permissions& perm = permissions());

   void *         m_handle;
   mode_t         m_mode;
   char_wchar_holder m_name;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline windows_shared_memory::windows_shared_memory() BOOST_NOEXCEPT
   :  m_handle(0)
{}

inline windows_shared_memory::~windows_shared_memory()
{  this->priv_close(); }

inline const char *windows_shared_memory::get_name() const BOOST_NOEXCEPT
{  return m_name.getn(); }

inline void windows_shared_memory::swap(windows_shared_memory &other) BOOST_NOEXCEPT
{
   (simple_swap)(m_handle,  other.m_handle);
   (simple_swap)(m_mode,    other.m_mode);
   m_name.swap(other.m_name);
}

inline mapping_handle_t windows_shared_memory::get_mapping_handle() const BOOST_NOEXCEPT
{  mapping_handle_t mhnd = { m_handle, true};   return mhnd;   }

inline mode_t windows_shared_memory::get_mode() const BOOST_NOEXCEPT
{  return m_mode; }

inline offset_t windows_shared_memory::get_size() const BOOST_NOEXCEPT
{
   offset_t size; //This shall never fail
   return (m_handle && winapi::get_file_mapping_size(m_handle, size)) ? size : 0;
}

template <class CharT>
inline bool windows_shared_memory::priv_open_or_create
   (ipcdetail::create_enum_t type, const CharT *filename, mode_t mode, std::size_t size, const permissions& perm)
{
   if (filename){
      m_name = filename;
   }
   else{
      m_name = "";
   }

   unsigned long protection = 0;
   unsigned long map_access = 0;

   switch(mode)
   {
      //"protection" is for "create_file_mapping"
      //"map_access" is for "open_file_mapping"
      //Add section query (strange that read or access does not grant it...)
      //to obtain the size of the mapping. copy_on_write is equal to section_query.
      case read_only:
         protection   |= winapi::page_readonly;
         map_access   |= winapi::file_map_read | winapi::section_query;
      break;
      case read_write:
         protection   |= winapi::page_readwrite;
         map_access   |= winapi::file_map_write | winapi::section_query;
      break;
      case copy_on_write:
         protection   |= winapi::page_writecopy;
         map_access   |= winapi::file_map_copy;
      break;
      default:
         {
            error_info err(mode_error);
            throw interprocess_exception(err);
         }
      break;
   }

   switch(type){
      case ipcdetail::DoOpen:
         m_handle = winapi::open_file_mapping(map_access, filename);
      break;
      case ipcdetail::DoCreate:
      case ipcdetail::DoOpenOrCreate:
      {
         m_handle = winapi::create_file_mapping
            ( winapi::invalid_handle_value, protection, size, filename
            , (winapi::interprocess_security_attributes*)perm.get_permissions());
      }
      break;
      default:
         {
            error_info err = other_error;
            throw interprocess_exception(err);
         }
   }

   if(!m_handle || (type == ipcdetail::DoCreate && winapi::get_last_error() == winapi::error_already_exists)){
      error_info err = system_error_code();
      this->priv_close();
      throw interprocess_exception(err);
   }

   m_mode = mode;
   return true;
}

inline void windows_shared_memory::priv_close()
{
   if(m_handle){
      winapi::close_handle(m_handle);
      m_handle = 0;
   }
}

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_SHARED_MEMORY_HPP

/* windows_shared_memory.hpp
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
*/
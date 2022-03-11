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
#include <string>

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
   windows_shared_memory();

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

   //!Moves the ownership of "moved"'s shared memory object to *this.
   //!After the call, "moved" does not represent any shared memory object.
   //!Does not throw
   windows_shared_memory(BOOST_RV_REF(windows_shared_memory) moved)
      : m_handle(0)
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s shared memory to *this.
   //!After the call, "moved" does not represent any shared memory.
   //!Does not throw
   windows_shared_memory &operator=(BOOST_RV_REF(windows_shared_memory) moved)
   {
      windows_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps to shared_memory_objects. Does not throw
   void swap(windows_shared_memory &other);

   //!Destroys *this. All mapped regions are still valid after
   //!destruction. When all mapped regions and windows_shared_memory
   //!objects referring the shared memory are destroyed, the
   //!operating system will destroy the shared memory.
   ~windows_shared_memory();

   //!Returns the name of the shared memory.
   const char *get_name() const;

   //!Returns access mode
   mode_t get_mode() const;

   //!Returns the mapping handle. Never throws
   mapping_handle_t get_mapping_handle() const;

   //!Returns the size of the windows shared memory. It will be a 4K rounded
   //!size of the "size" passed in the constructor.
   offset_t get_size() const;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   //!Closes a previously opened file mapping. Never throws.
   void priv_close();

   //!Closes a previously opened file mapping. Never throws.
   bool priv_open_or_create(ipcdetail::create_enum_t type, const char *filename, mode_t mode, std::size_t size, const permissions& perm = permissions());

   void *         m_handle;
   mode_t         m_mode;
   std::string    m_name;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline windows_shared_memory::windows_shared_memory()
   :  m_handle(0)
{}

inline windows_shared_memory::~windows_shared_memory()
{  this->priv_close(); }

inline const char *windows_shared_memory::get_name() const
{  return m_name.c_str(); }

inline void windows_shared_memory::swap(windows_shared_memory &other)
{
   (simple_swap)(m_handle,  other.m_handle);
   (simple_swap)(m_mode,    other.m_mode);
   m_name.swap(other.m_name);
}

inline mapping_handle_t windows_shared_memory::get_mapping_handle() const
{  mapping_handle_t mhnd = { m_handle, true};   return mhnd;   }

inline mode_t windows_shared_memory::get_mode() const
{  return m_mode; }

inline offset_t windows_shared_memory::get_size() const
{
   offset_t size; //This shall never fail
   return (m_handle && winapi::get_file_mapping_size(m_handle, size)) ? size : 0;
}

inline bool windows_shared_memory::priv_open_or_create
   (ipcdetail::create_enum_t type, const char *filename, mode_t mode, std::size_t size, const permissions& perm)
{
   m_name = filename ? filename : "";

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
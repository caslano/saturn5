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
1RLE7lZdgi7ftWod+QCseBXlgg2v+ify31Pemnq1nX7rLkj7t+6B2OnWfoidbp2E2NvWUxB723oWYrdblyH2tnUVYr9br0Pmmdaa19jt39oAKU9rG6QeWrsh9dC6H1Lu1iFbT/q2HG+dhtRP6zzE7rcuQvpF6wVIf2m9DKm31g1IPbTGZ+16a01B+m9rh3CS9Ge1/LR3awZ5AJ6AR+AcPArPwBG4ArNwAz4ZmtfSH2ADHIKd8DDsgcOSHhyFk/AQnIU5uAAH4Xl4AK7BgzDyun+iPf6JcDM2yr9l7mN2PW1ZhIzDLRcg9bVlDVJfW65B6muL+bjdn7bsgrT3lg5Ie2/phozjLQOQ9tsyBmmvLVOQ9tpySrhE+pD23LIEaactK5B637IKac8t65B+uyV6ztM/t9QgH4HN8BDsgEPCHH4L3IOchf0wA8fhQTgFD8M5OADPwmG4DEfgVfhkGPnEv16/f9hxh33jpLO6s9ws3bHc9N+53EyzLbJFosH9KX/SfN6u92QDpP8nOyD9ObkfUh/JMUh9JE9A+nNyxtbHk/O2Pp48A6m/5DKkHZKrkHZIbkDaLRn9gt1uyRpIuyV3Qdot2Qlp52QvpL2S/bY+lhyz9ZwPYr+TpyD2O3kaFrJNfSeXkDNQ2uMIdNoD5vAP4QrxWXgFDsLIBdoD2u0BpT2G4bJT/8ka4o9Kehf+9Xaw59vP0A7j5Wby6dQ/2+Z0+6xy08Om7RHaLo39X7Lro3EMYrcaT0DsWOMMpL4bFyF2onEJUo+NKxC71ngZYtcar0DqtTHyZbvfN1ZA2rWxFjIuGtsh46KxC9KujT2Q9V/jAKTdGycg69HGKaHhvJB2bVyw5XjjOcj4bFyBtHPjKqSdG9ch9rTxOqS9GyuW7f7VWAtZRza2QNahjXsg7du4H7KebRyC9L/Gccj4bJyx4+ONC5D2bzwHXdcRGpeRj8Ir8Mkw8hXsGayFg7AZHoAdMAcH4EE4CY/ABTgCz8MheBFmYfSr9AtJBx6CXfAwHIcZOP/Vf0//KBauk352hnH7KvrOq51+M/0a5Fl+u8L661SerHKu33YNbzffvHkk0g2/A3vh92AfvAwH4A9hBn4djsFvwwn4XXgCfh+ehD+AM/C1GOhT8IvI8/BNyKfhl5HPwGVYPFSa9s9vFz/B7IH4B6YP4geYMcj9ZzMlXK00p4TrlWZR2F9lVuz9jVkTLlaZyBfgUpWpFq5WmWZIwU27cNqYbuFKlemD3D81Gch9VTMJua9qZiH3v80i5D6suWAfb5nLdrqWWYf4JSZ6QY5LmFqIX2LaIX6J6YUsS0xW2FJlTgpNlVm0968yy8JUlbkqnDOm4ouSb2NqhUvGtED8GNP1RYmnHqDcThyH+HdmDnI/36zY+qS5BvFDTc2XJN2kaYf4PSYD8avNHGScmYuQ8WM27Pi4qf6yHGeZFsj4Nb2Q++Yma+srzYytrzTnIPfNzWXIfX5TvQyzlaYDcl/a9Amn2V84x/7CRfa34ytM9VckvsK0QO5vm26If2+ywn7yB7Ff5jzEXpk14STr+K/KcXFTC/EjTRfEfzTjtj5pTkP8R7MK8Z/Nhi3HTM3XpB6TphliD00XxM81/cIeY8aF/cbMQp6TMOfs/SrMGsT+mfiK9BvqU7hOfQqzxvQKJ42ZgPirZl64gl8CsY/mMsR/Ndcgfrap+LrU81ZTC7nfb9qEPVWmS7hO/xN2Ut+2fquZFNKRZ2y50ixArtaby3Y6xlyz9zem+huSj7hpgdhf0w2xu6YPYmdNBmJnzQTkeRZzEmJvzVmInTVr9n6Wqfmm5Kvc7ILMx2YPxM6aAeE0NkU4hz2BzCdmwdZvNUuQecM=
*/
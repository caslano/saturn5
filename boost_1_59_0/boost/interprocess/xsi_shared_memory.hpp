//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_XSI_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_XSI_SHARED_MEMORY_HPP

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

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/utilities.hpp>

#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/xsi_key.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/simple_swap.hpp>
// move
#include <boost/move/utility_core.hpp>
// other boost
#include <boost/cstdint.hpp>
// std
#include <cstddef>
// OS
#include <sys/shm.h>


//!\file
//!Describes a class representing a native xsi shared memory.

namespace boost {
namespace interprocess {

//!A class that wraps XSI (System V) shared memory.
//!Unlike shared_memory_object, xsi_shared_memory needs a valid
//!xsi_key to identify a shared memory object.
//!
//!Warning: XSI shared memory and interprocess portable
//!shared memory (boost::interprocess::shared_memory_object)
//!can't communicate between them.
class xsi_shared_memory
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable and non-assignable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(xsi_shared_memory)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Default constructor.
   //!Represents an empty xsi_shared_memory.
   xsi_shared_memory() BOOST_NOEXCEPT;

   //!Initializes *this with a shmid previously obtained (possibly from another process)
   //!This lower-level initializer allows shared memory mapping without having a key.
   xsi_shared_memory(open_only_t, int shmid)
      : m_shmid (shmid)
   {}

   //!Creates a new XSI shared memory from 'key', with size "size" and permissions "perm".
   //!If the shared memory previously exists, throws an error.
   xsi_shared_memory(create_only_t, const xsi_key &key, std::size_t size, const permissions& perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, key, perm, size);  }

   //!Opens an existing shared memory with identifier 'key' or creates a new XSI shared memory from
   //!identifier 'key', with size "size" and permissions "perm".
   xsi_shared_memory(open_or_create_t, const xsi_key &key, std::size_t size, const permissions& perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoOpenOrCreate, key, perm, size);  }

   //!Tries to open a XSI shared memory with identifier 'key'
   //!If the shared memory does not previously exist, it throws an error.
   xsi_shared_memory(open_only_t, const xsi_key &key)
   {  this->priv_open_or_create(ipcdetail::DoOpen, key, permissions(), 0);  }

   //!Moves the ownership of "moved"'s shared memory object to *this.
   //!After the call, "moved" does not represent any shared memory object.
   //!Does not throw
   xsi_shared_memory(BOOST_RV_REF(xsi_shared_memory) moved) BOOST_NOEXCEPT
      : m_shmid(-1)
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s shared memory to *this.
   //!After the call, "moved" does not represent any shared memory.
   //!Does not throw
   xsi_shared_memory &operator=(BOOST_RV_REF(xsi_shared_memory) moved) BOOST_NOEXCEPT
   {
      xsi_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps two xsi_shared_memorys. Does not throw
   void swap(xsi_shared_memory &other) BOOST_NOEXCEPT;

   //!Destroys *this. The shared memory won't be destroyed, just
   //!this connection to it. Use remove() to destroy the shared memory.
   ~xsi_shared_memory();

   //!Returns the shared memory ID that
   //!identifies the shared memory
   int get_shmid() const BOOST_NOEXCEPT;

   //!Returns the mapping handle.
   //!Never throws
   mapping_handle_t get_mapping_handle() const BOOST_NOEXCEPT;

   //!Erases the XSI shared memory object identified by shmid
   //!from the system.
   //!Returns false on error. Never throws
   static bool remove(int shmid);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   //!Closes a previously opened file mapping. Never throws.
   bool priv_open_or_create( ipcdetail::create_enum_t type
                           , const xsi_key &key
                           , const permissions& perm
                           , std::size_t size);
   int            m_shmid;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline xsi_shared_memory::xsi_shared_memory() BOOST_NOEXCEPT
   :  m_shmid(-1)
{}

inline xsi_shared_memory::~xsi_shared_memory()
{}

inline int xsi_shared_memory::get_shmid() const BOOST_NOEXCEPT
{  return m_shmid; }

inline void xsi_shared_memory::swap(xsi_shared_memory &other) BOOST_NOEXCEPT
{
   (simple_swap)(m_shmid, other.m_shmid);
}

inline mapping_handle_t xsi_shared_memory::get_mapping_handle() const BOOST_NOEXCEPT
{  mapping_handle_t mhnd = { m_shmid, true};   return mhnd;   }

inline bool xsi_shared_memory::priv_open_or_create
   (ipcdetail::create_enum_t type, const xsi_key &key, const permissions& permissions, std::size_t size)
{
   int perm = (int)permissions.get_permissions();
   perm &= 0x01FF;
   int shmflg = perm;

   switch(type){
      case ipcdetail::DoOpen:
         shmflg |= 0;
      break;
      case ipcdetail::DoCreate:
         shmflg |= IPC_CREAT | IPC_EXCL;
      break;
      case ipcdetail::DoOpenOrCreate:
         shmflg |= IPC_CREAT;
      break;
      default:
         {
            error_info err = other_error;
            throw interprocess_exception(err);
         }
   }

   int ret = ::shmget(key.get_key(), size, shmflg);
   int shmid = ret;
   if((type == ipcdetail::DoOpen) && (-1 != ret)){
      //Now get the size
      ::shmid_ds xsi_ds;
      ret = ::shmctl(ret, IPC_STAT, &xsi_ds);
      size = xsi_ds.shm_segsz;
   }
   if(-1 == ret){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }

   m_shmid = shmid;
   return true;
}

inline bool xsi_shared_memory::remove(int shmid)
{  return -1 != ::shmctl(shmid, IPC_RMID, 0); }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_XSI_SHARED_MEMORY_HPP

/* xsi_shared_memory.hpp
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
*/
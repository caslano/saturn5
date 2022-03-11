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
   xsi_shared_memory();

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
   xsi_shared_memory(BOOST_RV_REF(xsi_shared_memory) moved)
      : m_shmid(-1)
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s shared memory to *this.
   //!After the call, "moved" does not represent any shared memory.
   //!Does not throw
   xsi_shared_memory &operator=(BOOST_RV_REF(xsi_shared_memory) moved)
   {
      xsi_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps two xsi_shared_memorys. Does not throw
   void swap(xsi_shared_memory &other);

   //!Destroys *this. The shared memory won't be destroyed, just
   //!this connection to it. Use remove() to destroy the shared memory.
   ~xsi_shared_memory();

   //!Returns the shared memory ID that
   //!identifies the shared memory
   int get_shmid() const;

   //!Returns the mapping handle.
   //!Never throws
   mapping_handle_t get_mapping_handle() const;

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

inline xsi_shared_memory::xsi_shared_memory()
   :  m_shmid(-1)
{}

inline xsi_shared_memory::~xsi_shared_memory()
{}

inline int xsi_shared_memory::get_shmid() const
{  return m_shmid; }

inline void xsi_shared_memory::swap(xsi_shared_memory &other)
{
   (simple_swap)(m_shmid, other.m_shmid);
}

inline mapping_handle_t xsi_shared_memory::get_mapping_handle() const
{  mapping_handle_t mhnd = { m_shmid, true};   return mhnd;   }

inline bool xsi_shared_memory::priv_open_or_create
   (ipcdetail::create_enum_t type, const xsi_key &key, const permissions& permissions, std::size_t size)
{
   int perm = permissions.get_permissions();
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
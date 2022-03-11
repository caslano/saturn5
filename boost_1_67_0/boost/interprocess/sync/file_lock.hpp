//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_FILE_LOCK_HPP
#define BOOST_INTERPROCESS_FILE_LOCK_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/detail/common_algorithms.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#include <boost/move/utility_core.hpp>

//!\file
//!Describes a class that wraps file locking capabilities.

namespace boost {
namespace interprocess {


//!A file lock, is a mutual exclusion utility similar to a mutex using a
//!file. A file lock has sharable and exclusive locking capabilities and
//!can be used with scoped_lock and sharable_lock classes.
//!A file lock can't guarantee synchronization between threads of the same
//!process so just use file locks to synchronize threads from different processes.
class file_lock
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(file_lock)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructs an empty file mapping.
   //!Does not throw
   file_lock()
      :  m_file_hnd(file_handle_t(ipcdetail::invalid_file()))
   {}

   //!Opens a file lock. Throws interprocess_exception if the file does not
   //!exist or there are no operating system resources.
   file_lock(const char *name);

   //!Moves the ownership of "moved"'s file mapping object to *this.
   //!After the call, "moved" does not represent any file mapping object.
   //!Does not throw
   file_lock(BOOST_RV_REF(file_lock) moved)
      :  m_file_hnd(file_handle_t(ipcdetail::invalid_file()))
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s file mapping to *this.
   //!After the call, "moved" does not represent any file mapping.
   //!Does not throw
   file_lock &operator=(BOOST_RV_REF(file_lock) moved)
   {
      file_lock tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Closes a file lock. Does not throw.
   ~file_lock();

   //!Swaps two file_locks.
   //!Does not throw.
   void swap(file_lock &other)
   {
      file_handle_t tmp = m_file_hnd;
      m_file_hnd = other.m_file_hnd;
      other.m_file_hnd = tmp;
   }

   //Exclusive locking

   //!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
   //!   and if another thread has exclusive, or sharable ownership of
   //!   the mutex, it waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock();

   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   without waiting. If no other thread has exclusive, or sharable
   //!   ownership of the mutex this succeeds.
   //!Returns: If it can acquire exclusive ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock();

   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive, or sharable
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Precondition: The thread must have exclusive ownership of the mutex.
   //!Effects: The calling thread releases the exclusive ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock();

   //Sharable locking

   //!Effects: The calling thread tries to obtain sharable ownership of the mutex,
   //!   and if another thread has exclusive ownership of the mutex, waits until
   //!   it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   void lock_sharable();

   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   without waiting. If no other thread has exclusive ownership of the
   //!   mutex this succeeds.
   //!Returns: If it can acquire sharable ownership immediately returns true. If it
   //!   has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock_sharable();

   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive ownership of
   //!   the mutex or abs_time is reached.
   //!Returns: If acquires sharable ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   bool timed_lock_sharable(const boost::posix_time::ptime &abs_time);

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The calling thread releases the sharable ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_sharable();
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   file_handle_t m_file_hnd;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline file_lock::file_lock(const char *name)
{
   m_file_hnd = ipcdetail::open_existing_file(name, read_write);

   if(m_file_hnd == ipcdetail::invalid_file()){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline file_lock::~file_lock()
{
   if(m_file_hnd != ipcdetail::invalid_file()){
      ipcdetail::close_file(m_file_hnd);
      m_file_hnd = ipcdetail::invalid_file();
   }
}

inline void file_lock::lock()
{
   if(!ipcdetail::acquire_file_lock(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline bool file_lock::try_lock()
{
   bool result;
   if(!ipcdetail::try_acquire_file_lock(m_file_hnd, result)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
   return result;
}

inline bool file_lock::timed_lock(const boost::posix_time::ptime &abs_time)
{  return ipcdetail::try_based_timed_lock(*this, abs_time);   }

inline void file_lock::unlock()
{
   if(!ipcdetail::release_file_lock(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline void file_lock::lock_sharable()
{
   if(!ipcdetail::acquire_file_lock_sharable(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline bool file_lock::try_lock_sharable()
{
   bool result;
   if(!ipcdetail::try_acquire_file_lock_sharable(m_file_hnd, result)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
   return result;
}

inline bool file_lock::timed_lock_sharable(const boost::posix_time::ptime &abs_time)
{
   ipcdetail::lock_to_sharable<file_lock> lsh(*this);
   return ipcdetail::try_based_timed_lock(lsh, abs_time);
}

inline void file_lock::unlock_sharable()
{
   if(!ipcdetail::release_file_lock_sharable(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_FILE_LOCK_HPP

/* file_lock.hpp
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
*/
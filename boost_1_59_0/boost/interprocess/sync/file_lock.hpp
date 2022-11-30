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
   file_lock() BOOST_NOEXCEPT
      :  m_file_hnd(file_handle_t(ipcdetail::invalid_file()))
   {}

   //!Opens a file lock. Throws interprocess_exception if the file does not
   //!exist or there are no operating system resources.
   file_lock(const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //!Opens a file lock. Throws interprocess_exception if the file does not
   //!exist or there are no operating system resources.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   file_lock(const wchar_t *name);
   #endif

   //!Moves the ownership of "moved"'s file mapping object to *this.
   //!After the call, "moved" does not represent any file mapping object.
   //!Does not throw
   file_lock(BOOST_RV_REF(file_lock) moved) BOOST_NOEXCEPT
      :  m_file_hnd(file_handle_t(ipcdetail::invalid_file()))
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s file mapping to *this.
   //!After the call, "moved" does not represent any file mapping.
   //!Does not throw
   file_lock &operator=(BOOST_RV_REF(file_lock) moved) BOOST_NOEXCEPT
   {
      file_lock tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Closes a file lock. Does not throw.
   ~file_lock();

   //!Swaps two file_locks.
   //!Does not throw.
   void swap(file_lock &other) BOOST_NOEXCEPT
   {
      file_handle_t tmp = m_file_hnd;
      m_file_hnd = other.m_file_hnd;
      other.m_file_hnd = tmp;
   }

   //Exclusive locking

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain exclusive ownership of the mutex,
   //!   and if another thread has exclusive, or sharable ownership of
   //!   the mutex, it waits until it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   void lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   without waiting. If no other thread has exclusive, or sharable
   //!   ownership of the mutex this succeeds.
   //!Returns: If it can acquire exclusive ownership immediately returns true.
   //!   If it has to wait, returns false.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   bool try_lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to acquire exclusive ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive, or sharable
   //!   ownership of the mutex or abs_time is reached.
   //!Returns: If acquires exclusive ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time);

   //!Same as `timed_lock`, but this function is modeled after the
   //!standard library interface.
   template<class TimePoint> bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   //!Same as `timed_lock`, but this function is modeled after the
   //!standard library interface.
   template<class Duration>  bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(ipcdetail::duration_to_ustime(dur)); }

   //!Precondition: The thread must have exclusive ownership of the mutex.
   //!Effects: The calling thread releases the exclusive ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock();

   //Sharable locking

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain sharable ownership of the mutex,
   //!   and if another thread has exclusive ownership of the mutex, waits until
   //!   it can obtain the ownership.
   //!Throws: interprocess_exception on error.
   //!
   //!Note: A program may deadlock if the thread that owns a mutex object calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   void lock_sharable();

   //!Same as `lock_sharable` but with a std-compatible interface
   //! 
   void lock_shared()
   {  this->lock_sharable();  }

   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   without waiting. If no other thread has exclusive ownership of the
   //!   mutex this succeeds.
   //!Returns: If it can acquire sharable ownership immediately returns true. If it
   //!   has to wait, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock_sharable();

   //!Same as `try_lock_sharable` but with a std-compatible interface
   //! 
   bool try_lock_shared()
   {  return this->try_lock_sharable();  }

   //!Effects: The calling thread tries to acquire sharable ownership of the mutex
   //!   waiting if necessary until no other thread has exclusive ownership of
   //!   the mutex or abs_time is reached.
   //!Returns: If acquires sharable ownership, returns true. Otherwise returns false.
   //!Throws: interprocess_exception on error.
   template<class TimePoint>
   bool timed_lock_sharable(const TimePoint &abs_time);

   //!Same as `timed_lock_sharable`, but this function is modeled after the
   //!standard library interface.
   template<class TimePoint> bool try_lock_shared_until(const TimePoint &abs_time)
   {  return this->timed_lock_sharable(abs_time);  }

   //!Same as `timed_lock_sharable`, but this function is modeled after the
   //!standard library interface.
   template<class Duration>  bool try_lock_shared_for(const Duration &dur)
   {  return this->timed_lock_sharable(ipcdetail::duration_to_ustime(dur)); }

   //!Precondition: The thread must have sharable ownership of the mutex.
   //!Effects: The calling thread releases the sharable ownership of the mutex.
   //!Throws: An exception derived from interprocess_exception on error.
   void unlock_sharable();

   //!Same as `unlock_sharable` but with a std-compatible interface
   //! 
   void unlock_shared()
   {  this->unlock_sharable();  }

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

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline file_lock::file_lock(const wchar_t *name)
{
   m_file_hnd = ipcdetail::open_existing_file(name, read_write);

   if(m_file_hnd == ipcdetail::invalid_file()){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

#endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

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

template<class TimePoint>
inline bool file_lock::timed_lock(const TimePoint &abs_time)
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

template<class TimePoint>
inline bool file_lock::timed_lock_sharable(const TimePoint &abs_time)
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
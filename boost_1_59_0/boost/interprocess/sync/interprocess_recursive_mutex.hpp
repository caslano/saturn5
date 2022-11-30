//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
// Parts of the pthread code come from Boost Threads code:
//
//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2001-2003
// William E. Kempf
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  William E. Kempf makes no representations
// about the suitability of this software for any purpose.
// It is provided "as is" without express or implied warranty.
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_RECURSIVE_MUTEX_HPP

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/detail/common_algorithms.hpp>
#include <boost/assert.hpp>

#if   !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && \
       defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED) && \
       defined (BOOST_INTERPROCESS_POSIX_RECURSIVE_MUTEXES)
   #include <boost/interprocess/sync/posix/recursive_mutex.hpp>
   #define BOOST_INTERPROCESS_RECURSIVE_MUTEX_USE_POSIX
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   //Experimental...
   #include <boost/interprocess/sync/windows/recursive_mutex.hpp>
   #define BOOST_INTERPROCESS_RECURSIVE_MUTEX_USE_WINAPI
#else
   //spin_recursive_mutex is used
   #include <boost/interprocess/sync/spin/recursive_mutex.hpp>
   namespace boost {
   namespace interprocess {
   namespace ipcdetail{
   namespace robust_emulation_helpers {

   template<class T>
   class mutex_traits;

   }}}}
#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!\file
//!Describes interprocess_recursive_mutex and shared_recursive_try_mutex classes

namespace boost {
namespace interprocess {

//!Wraps a interprocess_mutex that can be placed in shared memory and can be
//!shared between processes. Allows several locking calls by the same
//!process. Allows timed lock tries
class interprocess_recursive_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   interprocess_recursive_mutex(const interprocess_recursive_mutex &);
   interprocess_recursive_mutex &operator=(const interprocess_recursive_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Constructor.
   //!Throws interprocess_exception on error.
   interprocess_recursive_mutex();

   //!Destructor. If any process uses the mutex after the destructor is called
   //!the result is undefined. Does not throw.
  ~interprocess_recursive_mutex();

   //!Effects: The calling thread tries to obtain ownership of the mutex, and
   //!   if another thread has ownership of the mutex, it waits until it can
   //!   obtain the ownership. If a thread takes ownership of the mutex the
   //!   mutex must be unlocked by the same mutex. The mutex must be unlocked
   //!   the same number of times it is locked.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program shall not deadlock if the thread that has ownership calls 
   //!   this function. 
   void lock();

   //!Tries to lock the interprocess_mutex, returns false when interprocess_mutex
   //!is already locked, returns true when success. The mutex must be unlocked
   //!the same number of times it is locked.
   //!Throws: interprocess_exception if a severe error is found
   //! 
   //!Note: A program shall not deadlock if the thread that has ownership calls 
   //!   this function. 
   bool try_lock();

   //!Tries to lock the interprocess_mutex, if interprocess_mutex can't be locked before
   //!abs_time time, returns false. The mutex must be unlocked
   //!   the same number of times it is locked.
   //!Throws: interprocess_exception if a severe error is found
   //! 
   //!Note: A program shall not deadlock if the thread that has ownership calls 
   //!   this function.
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

   //!Effects: The calling thread releases the exclusive ownership of the mutex.
   //!   If the mutex supports recursive locking, the mutex must be unlocked the
   //!   same number of times it is locked.
   //!Throws: interprocess_exception on error.
   void unlock();
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   #if defined(BOOST_INTERPROCESS_RECURSIVE_MUTEX_USE_POSIX)
      ipcdetail::posix_recursive_mutex mutex;
   #elif defined(BOOST_INTERPROCESS_RECURSIVE_MUTEX_USE_WINAPI)
      ipcdetail::winapi_recursive_mutex mutex;
   #else
      void take_ownership(){ mutex.take_ownership(); }
      friend class ipcdetail::robust_emulation_helpers::mutex_traits<interprocess_recursive_mutex>;
      ipcdetail::spin_recursive_mutex mutex;
   #endif
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace interprocess {
}  //namespace boost {

namespace boost {
namespace interprocess {

inline interprocess_recursive_mutex::interprocess_recursive_mutex(){}

inline interprocess_recursive_mutex::~interprocess_recursive_mutex(){}

inline void interprocess_recursive_mutex::lock()
{  ipcdetail::timeout_when_locking_aware_lock(mutex);  }

inline bool interprocess_recursive_mutex::try_lock()
{ return mutex.try_lock(); }

template<class TimePoint>
inline bool interprocess_recursive_mutex::timed_lock(const TimePoint &abs_time)
{ return mutex.timed_lock(abs_time); }

inline void interprocess_recursive_mutex::unlock()
{ mutex.unlock(); }

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_RECURSIVE_MUTEX_HPP

/* interprocess_recursive_mutex.hpp
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
*/
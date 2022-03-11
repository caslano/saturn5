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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/assert.hpp>

#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && \
   (defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED) && defined (BOOST_INTERPROCESS_POSIX_RECURSIVE_MUTEXES))
   #include <boost/interprocess/sync/posix/recursive_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_POSIX
//Experimental...
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/recursive_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#elif !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   #include <boost/interprocess/sync/spin/recursive_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_GENERIC_EMULATION
#endif

#if defined (BOOST_INTERPROCESS_USE_GENERIC_EMULATION)
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
   void lock();

   //!Tries to lock the interprocess_mutex, returns false when interprocess_mutex
   //!is already locked, returns true when success. The mutex must be unlocked
   //!the same number of times it is locked.
   //!Throws: interprocess_exception if a severe error is found
   bool try_lock();

   //!Tries to lock the interprocess_mutex, if interprocess_mutex can't be locked before
   //!abs_time time, returns false. The mutex must be unlocked
   //!   the same number of times it is locked.
   //!Throws: interprocess_exception if a severe error is found
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Effects: The calling thread releases the exclusive ownership of the mutex.
   //!   If the mutex supports recursive locking, the mutex must be unlocked the
   //!   same number of times it is locked.
   //!Throws: interprocess_exception on error.
   void unlock();
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   #if defined (BOOST_INTERPROCESS_USE_GENERIC_EMULATION)
      #undef BOOST_INTERPROCESS_USE_GENERIC_EMULATION
      void take_ownership(){ mutex.take_ownership(); }
      friend class ipcdetail::robust_emulation_helpers::mutex_traits<interprocess_recursive_mutex>;
      ipcdetail::spin_recursive_mutex mutex;
   #elif defined(BOOST_INTERPROCESS_USE_POSIX)
      #undef BOOST_INTERPROCESS_USE_POSIX
      ipcdetail::posix_recursive_mutex mutex;
   #elif defined(BOOST_INTERPROCESS_USE_WINDOWS)
      #undef BOOST_INTERPROCESS_USE_WINDOWS
      ipcdetail::windows_recursive_mutex mutex;
   #else
      #error "Unknown platform for interprocess_mutex"
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
{
   #ifdef BOOST_INTERPROCESS_ENABLE_TIMEOUT_WHEN_LOCKING
      boost::posix_time::ptime wait_time
         = microsec_clock::universal_time()
         + boost::posix_time::milliseconds(BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS);
      if (!mutex.timed_lock(wait_time)){
         throw interprocess_exception(timeout_when_locking_error, "Interprocess mutex timeout when locking. Possible deadlock: owner died without unlocking?");
      }
   #else
      mutex.lock();
   #endif
}

inline bool interprocess_recursive_mutex::try_lock()
{ return mutex.try_lock(); }

inline bool interprocess_recursive_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
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
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
// Parts of the pthread code come from Boost Threads code.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MUTEX_HPP
#define BOOST_INTERPROCESS_MUTEX_HPP

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/assert.hpp>
#include <boost/interprocess/sync/detail/common_algorithms.hpp>

#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_POSIX_PROCESS_SHARED)
   #include <boost/interprocess/sync/posix/mutex.hpp>
   #define BOOST_INTERPROCESS_MUTEX_USE_POSIX
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   //Experimental...
   #define BOOST_INTERPROCESS_MUTEX_USE_WINAPI
   #include <boost/interprocess/sync/windows/mutex.hpp>
#else
   //spin_mutex is used
   #include <boost/interprocess/sync/spin/mutex.hpp>
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
//!Describes a mutex class that can be placed in memory shared by
//!several processes.

namespace boost {
namespace interprocess {

class interprocess_condition;

//!Wraps a interprocess_mutex that can be placed in shared memory and can be
//!shared between processes. Allows timed lock tries
class interprocess_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   interprocess_mutex(const interprocess_mutex &);
   interprocess_mutex &operator=(const interprocess_mutex &);
   friend class interprocess_condition;

   public:
   #if defined(BOOST_INTERPROCESS_MUTEX_USE_POSIX)
      typedef ipcdetail::posix_mutex internal_mutex_type;
   #elif defined(BOOST_INTERPROCESS_MUTEX_USE_WINAPI)
      typedef ipcdetail::winapi_mutex internal_mutex_type;
   #else
      typedef ipcdetail::spin_mutex internal_mutex_type;
      private:
      friend class ipcdetail::robust_emulation_helpers::mutex_traits<interprocess_mutex>;
      void take_ownership(){ m_mutex.take_ownership(); }
      public:
   #endif

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Constructor.
   //!Throws interprocess_exception on error.
   interprocess_mutex();

   //!Destructor. If any process uses the mutex after the destructor is called
   //!the result is undefined. Does not throw.
   ~interprocess_mutex();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain ownership of the mutex, and
   //!   if another thread has ownership of the mutex, it waits until it can
   //!   obtain the ownership. If a thread takes ownership of the mutex the
   //!   mutex must be unlocked by the same mutex.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   void lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread tries to obtain ownership of the mutex, and
   //!   if another thread has ownership of the mutex returns immediately.
   //!Returns: If the thread acquires ownership of the mutex, returns true, if
   //!   the another thread has ownership of the mutex, returns false.
   //!Throws: interprocess_exception on error.
   //! 
   //!Note: A program may deadlock if the thread that has ownership calls 
   //!   this function. If the implementation can detect the deadlock,
   //!   an exception could be thrown.
   bool try_lock();

   //!Requires: The calling thread does not own the mutex.
   //!
   //!Effects: The calling thread will try to obtain exclusive ownership of the
   //!   mutex if it can do so in until the specified time is reached. If the
   //!   mutex supports recursive locking, the mutex must be unlocked the same
   //!   number of times it is locked.
   //!Returns: If the thread acquires ownership of the mutex, returns true, if
   //!   the timeout expires returns false.
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

   //!Effects: The calling thread releases the exclusive ownership of the mutex.
   //!Throws: interprocess_exception on error.
   void unlock();

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   internal_mutex_type &internal_mutex()
   {  return m_mutex;   }

   const internal_mutex_type &internal_mutex() const
   {  return m_mutex;   }

   private:
   internal_mutex_type m_mutex;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace interprocess {
}  //namespace boost {


namespace boost {
namespace interprocess {

inline interprocess_mutex::interprocess_mutex(){}

inline interprocess_mutex::~interprocess_mutex(){}

inline void interprocess_mutex::lock()
{  ipcdetail::timeout_when_locking_aware_lock(m_mutex);  }

inline bool interprocess_mutex::try_lock()
{ return m_mutex.try_lock(); }

template <class TimePoint>
inline bool interprocess_mutex::timed_lock(const TimePoint &abs_time)
{ return m_mutex.timed_lock(abs_time); }

inline void interprocess_mutex::unlock()
{ m_mutex.unlock(); }

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MUTEX_HPP

/* interprocess_mutex.hpp
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
*/
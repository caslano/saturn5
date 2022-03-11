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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/assert.hpp>

#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_POSIX_PROCESS_SHARED)
   #include <boost/interprocess/sync/posix/mutex.hpp>
   #define BOOST_INTERPROCESS_USE_POSIX
//Experimental...
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/mutex.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#elif !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   #include <boost/interprocess/sync/spin/mutex.hpp>
   #define BOOST_INTERPROCESS_USE_GENERIC_EMULATION

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
   #if defined(BOOST_INTERPROCESS_USE_GENERIC_EMULATION)
      #undef BOOST_INTERPROCESS_USE_GENERIC_EMULATION
      typedef ipcdetail::spin_mutex internal_mutex_type;
      private:
      friend class ipcdetail::robust_emulation_helpers::mutex_traits<interprocess_mutex>;
      void take_ownership(){ m_mutex.take_ownership(); }
      public:
   #elif defined(BOOST_INTERPROCESS_USE_POSIX)
      #undef BOOST_INTERPROCESS_USE_POSIX
      typedef ipcdetail::posix_mutex internal_mutex_type;
   #elif defined(BOOST_INTERPROCESS_USE_WINDOWS)
      #undef BOOST_INTERPROCESS_USE_WINDOWS
      typedef ipcdetail::windows_mutex internal_mutex_type;
   #else
      #error "Unknown platform for interprocess_mutex"
   #endif

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Constructor.
   //!Throws interprocess_exception on error.
   interprocess_mutex();

   //!Destructor. If any process uses the mutex after the destructor is called
   //!the result is undefined. Does not throw.
   ~interprocess_mutex();

   //!Effects: The calling thread tries to obtain ownership of the mutex, and
   //!   if another thread has ownership of the mutex, it waits until it can
   //!   obtain the ownership. If a thread takes ownership of the mutex the
   //!   mutex must be unlocked by the same mutex.
   //!Throws: interprocess_exception on error.
   void lock();

   //!Effects: The calling thread tries to obtain ownership of the mutex, and
   //!   if another thread has ownership of the mutex returns immediately.
   //!Returns: If the thread acquires ownership of the mutex, returns true, if
   //!   the another thread has ownership of the mutex, returns false.
   //!Throws: interprocess_exception on error.
   bool try_lock();

   //!Effects: The calling thread will try to obtain exclusive ownership of the
   //!   mutex if it can do so in until the specified time is reached. If the
   //!   mutex supports recursive locking, the mutex must be unlocked the same
   //!   number of times it is locked.
   //!Returns: If the thread acquires ownership of the mutex, returns true, if
   //!   the timeout expires returns false.
   //!Throws: interprocess_exception on error.
   bool timed_lock(const boost::posix_time::ptime &abs_time);

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
{
   #ifdef BOOST_INTERPROCESS_ENABLE_TIMEOUT_WHEN_LOCKING
      boost::posix_time::ptime wait_time
         = microsec_clock::universal_time()
         + boost::posix_time::milliseconds(BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS);
      if (!m_mutex.timed_lock(wait_time))
      {
         throw interprocess_exception(timeout_when_locking_error
                                     , "Interprocess mutex timeout when locking. Possible deadlock: "
                                       "owner died without unlocking?");
      }
   #else
      m_mutex.lock();
   #endif
}

inline bool interprocess_mutex::try_lock()
{ return m_mutex.try_lock(); }

inline bool interprocess_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
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
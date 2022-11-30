//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_SEMAPHORE_HPP

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

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#include <boost/interprocess/sync/detail/common_algorithms.hpp>

#if   !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && \
       defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED)    && \
       defined(BOOST_INTERPROCESS_POSIX_UNNAMED_SEMAPHORES)
   #include <boost/interprocess/sync/posix/semaphore.hpp>
   #define BOOST_INTERPROCESS_SEMAPHORE_USE_POSIX
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   //Experimental...
   #include <boost/interprocess/sync/windows/semaphore.hpp>
   #define BOOST_INTERPROCESS_SEMAPHORE_USE_WINAPI
#else
   //spin_semaphore is used
   #include <boost/interprocess/sync/spin/semaphore.hpp>
#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!\file
//!Describes a interprocess_semaphore class for inter-process synchronization

namespace boost {
namespace interprocess {

//!Wraps a interprocess_semaphore that can be placed in shared memory and can be
//!shared between processes. Allows timed lock tries
class interprocess_semaphore
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   interprocess_semaphore(const interprocess_semaphore &);
   interprocess_semaphore &operator=(const interprocess_semaphore &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Creates a interprocess_semaphore with the given initial count.
   //!interprocess_exception if there is an error.*/
   interprocess_semaphore(unsigned int initialCount);

   //!Destroys the interprocess_semaphore.
   //!Does not throw
   ~interprocess_semaphore();

   //!Increments the interprocess_semaphore count. If there are processes/threads blocked waiting
   //!for the interprocess_semaphore, then one of these processes will return successfully from
   //!its wait function. If there is an error an interprocess_exception exception is thrown.
   void post();

   //!Decrements the interprocess_semaphore. If the interprocess_semaphore value is not greater than zero,
   //!then the calling process/thread blocks until it can decrement the counter.
   //!If there is an error an interprocess_exception exception is thrown.
   void wait();

   //!Decrements the interprocess_semaphore if the interprocess_semaphore's value is greater than zero
   //!and returns true. If the value is not greater than zero returns false.
   //!If there is an error an interprocess_exception exception is thrown.
   bool try_wait();

   //!Decrements the interprocess_semaphore if the interprocess_semaphore's value is greater
   //!than zero and returns true. Otherwise, waits for the interprocess_semaphore
   //!to the posted or the timeout expires. If the timeout expires, the
   //!function returns false. If the interprocess_semaphore is posted the function
   //!returns true. If there is an error throws sem_exception
   template<class TimePoint>
   bool timed_wait(const TimePoint &abs_time);

   //!Returns the interprocess_semaphore count
//   int get_count() const;
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   #if defined(BOOST_INTERPROCESS_SEMAPHORE_USE_POSIX)
      typedef ipcdetail::posix_semaphore internal_sem_t;
   #elif defined(BOOST_INTERPROCESS_SEMAPHORE_USE_WINAPI)
      typedef ipcdetail::winapi_semaphore internal_sem_t;
   #else
      typedef ipcdetail::spin_semaphore internal_sem_t;
   #endif   //#if defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION)
   internal_sem_t m_sem;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace interprocess {
}  //namespace boost {

namespace boost {
namespace interprocess {

inline interprocess_semaphore::interprocess_semaphore(unsigned int initialCount)
   : m_sem(initialCount)
{}

inline interprocess_semaphore::~interprocess_semaphore(){}

inline void interprocess_semaphore::wait()
{
   ipcdetail::lock_to_wait<internal_sem_t> ltw(m_sem);
   timeout_when_locking_aware_lock(ltw);
}

inline bool interprocess_semaphore::try_wait()
{ return m_sem.try_wait(); }

template<class TimePoint>
inline bool interprocess_semaphore::timed_wait(const TimePoint &abs_time)
{ return m_sem.timed_wait(abs_time); }

inline void interprocess_semaphore::post()
{ m_sem.post(); }

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SEMAPHORE_HPP

/* interprocess_semaphore.hpp
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
*/
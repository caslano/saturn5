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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && \
   (defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED) && defined(BOOST_INTERPROCESS_POSIX_UNNAMED_SEMAPHORES))
   #include <boost/interprocess/sync/posix/semaphore.hpp>
   #define BOOST_INTERPROCESS_USE_POSIX
//Experimental...
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/semaphore.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#elif !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   #include <boost/interprocess/sync/spin/semaphore.hpp>
   #define BOOST_INTERPROCESS_USE_GENERIC_EMULATION
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
   bool timed_wait(const boost::posix_time::ptime &abs_time);

   //!Returns the interprocess_semaphore count
//   int get_count() const;
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   #if defined(BOOST_INTERPROCESS_USE_GENERIC_EMULATION)
      #undef BOOST_INTERPROCESS_USE_GENERIC_EMULATION
      ipcdetail::spin_semaphore m_sem;
   #elif defined(BOOST_INTERPROCESS_USE_WINDOWS)
      #undef BOOST_INTERPROCESS_USE_WINDOWS
      ipcdetail::windows_semaphore m_sem;
   #else
      #undef BOOST_INTERPROCESS_USE_POSIX
      ipcdetail::posix_semaphore m_sem;
   #endif   //#if defined(BOOST_INTERPROCESS_USE_GENERIC_EMULATION)
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
   #ifdef BOOST_INTERPROCESS_ENABLE_TIMEOUT_WHEN_LOCKING
      boost::posix_time::ptime wait_time
         = microsec_clock::universal_time()
         + boost::posix_time::milliseconds(BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS);
      if (!m_sem.timed_wait(wait_time))
      {
         throw interprocess_exception(timeout_when_waiting_error, "Interprocess semaphore timeout when waiting. Possible deadlock: owner died without posting?");
      }
   #else
      m_sem.wait();
   #endif
}
inline bool interprocess_semaphore::try_wait()
{ return m_sem.try_wait(); }

inline bool interprocess_semaphore::timed_wait(const boost::posix_time::ptime &abs_time)
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
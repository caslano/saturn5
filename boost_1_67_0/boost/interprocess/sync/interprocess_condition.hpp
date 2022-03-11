//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CONDITION_HPP
#define BOOST_INTERPROCESS_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/limits.hpp>
#include <boost/assert.hpp>

#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED)
   #include <boost/interprocess/sync/posix/condition.hpp>
   #define BOOST_INTERPROCESS_USE_POSIX
//Experimental...
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/condition.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#elif !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   #include <boost/interprocess/sync/spin/condition.hpp>
   #define BOOST_INTERPROCESS_USE_GENERIC_EMULATION
#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!\file
//!Describes process-shared variables interprocess_condition class

namespace boost {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace posix_time
{  class ptime;   }

#endif   //#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace interprocess {

class named_condition;

//!This class is a condition variable that can be placed in shared memory or
//!memory mapped files.
//!Destroys the object of type std::condition_variable_any
//!
//!Unlike std::condition_variable in C++11, it is NOT safe to invoke the destructor if all
//!threads have been only notified. It is required that they have exited their respective wait
//!functions.
class interprocess_condition
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   interprocess_condition(const interprocess_condition &);
   interprocess_condition &operator=(const interprocess_condition &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructs a interprocess_condition. On error throws interprocess_exception.
   interprocess_condition()
   {}

   //!Destroys *this
   //!liberating system resources.
   ~interprocess_condition()
   {}

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.
   void notify_one()
   {  m_condition.notify_one();  }

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all()
   {  m_condition.notify_all();  }

   //!Releases the lock on the interprocess_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      m_condition.wait(internal_lock);
   }

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      m_condition.wait(internal_lock, pred);
   }

   //!Releases the lock on the interprocess_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      return m_condition.timed_wait(internal_lock, abs_time);
   }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      return m_condition.timed_wait(internal_lock, abs_time, pred);
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   private:
   #if defined (BOOST_INTERPROCESS_USE_GENERIC_EMULATION)
      #undef BOOST_INTERPROCESS_USE_GENERIC_EMULATION
      ipcdetail::spin_condition m_condition;
   #elif defined(BOOST_INTERPROCESS_USE_POSIX)
      #undef BOOST_INTERPROCESS_USE_POSIX
      ipcdetail::posix_condition m_condition;
   #elif defined(BOOST_INTERPROCESS_USE_WINDOWS)
      #undef BOOST_INTERPROCESS_USE_WINDOWS
      ipcdetail::windows_condition m_condition;
   #else
      #error "Unknown platform for interprocess_mutex"
   #endif
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace interprocess
}  // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_CONDITION_HPP

/* interprocess_condition.hpp
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
*/
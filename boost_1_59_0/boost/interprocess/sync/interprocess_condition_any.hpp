//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CONDITION_ANY_HPP
#define BOOST_INTERPROCESS_CONDITION_ANY_HPP

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

#include <boost/interprocess/sync/cv_status.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/detail/condition_any_algorithm.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!\file
//!Describes process-shared variables interprocess_condition_any class

namespace boost {
namespace interprocess {

//!This class is a condition variable that can be placed in shared memory or
//!memory mapped files.
//!
//!The interprocess_condition_any class is a generalization of interprocess_condition.
//!Whereas interprocess_condition works only on Locks with mutex_type == interprocess_mutex
//!interprocess_condition_any can operate on any user-defined lock that meets the BasicLockable
//!requirements (lock()/unlock() member functions).
//!
//!Unlike std::condition_variable_any in C++11, it is NOT safe to invoke the destructor if all
//!threads have been only notified. It is required that they have exited their respective wait
//!functions.
class interprocess_condition_any
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   interprocess_condition_any(const interprocess_condition_any &);
   interprocess_condition_any &operator=(const interprocess_condition_any &);

   class members
   {
      public:
      typedef interprocess_condition   condvar_type;
      typedef interprocess_mutex       mutex_type;

      condvar_type &get_condvar() {  return m_cond;  }
      mutex_type   &get_mutex()   {  return m_mut; }

      private:
      condvar_type   m_cond;
      mutex_type     m_mut;
   };

   ipcdetail::condition_any_wrapper<members>   m_cond;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Constructs a interprocess_condition_any. On error throws interprocess_exception.
   interprocess_condition_any(){}

   //!Destroys *this
   //!liberating system resources.
   ~interprocess_condition_any(){}

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.
   void notify_one()
   {  m_cond.notify_one();  }

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all()
   {  m_cond.notify_all();  }

   //!Releases the lock on the interprocess_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock)
   {  m_cond.wait(lock);  }

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  m_cond.wait(lock, pred);  }

   //!Releases the lock on the interprocess_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L, class TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time)
   {  return m_cond.timed_wait(lock, abs_time);  }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, class TimePoint, typename Pr>
   bool timed_wait(L& lock, const TimePoint &abs_time, Pr pred)
   {  return m_cond.timed_wait(lock, abs_time, pred);  }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface.
   template <typename L, class TimePoint>
   cv_status wait_until(L& lock, const TimePoint &abs_time)
   {  return this->timed_wait(lock, abs_time) ? cv_status::no_timeout : cv_status::timeout; }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface.
   template <typename L, class TimePoint, typename Pr>
   bool wait_until(L& lock, const TimePoint &abs_time, Pr pred)
   {  return this->timed_wait(lock, abs_time, pred); }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface and uses relative timeouts.
   template <typename L, class Duration>
   cv_status wait_for(L& lock, const Duration &dur)
   {  return this->wait_until(lock, ipcdetail::duration_to_ustime(dur)); }

   //!Same as `timed_wait`, but this function is modeled after the
   //!standard library interface and uses relative timeouts
   template <typename L, class Duration, typename Pr>
   bool wait_for(L& lock, const Duration &dur, Pr pred)
   {  return this->wait_until(lock, ipcdetail::duration_to_ustime(dur), pred); }
};

}  //namespace interprocess
}  // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_CONDITION_ANY_HPP

/* interprocess_condition_any.hpp
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
*/
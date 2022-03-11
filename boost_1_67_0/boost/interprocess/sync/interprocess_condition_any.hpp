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

#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/detail/condition_any_algorithm.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!\file
//!Describes process-shared variables interprocess_condition_any class

namespace boost {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace posix_time
{  class ptime;   }

#endif   //#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

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
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return m_cond.timed_wait(lock, abs_time);  }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {  return m_cond.timed_wait(lock, abs_time, pred);  }
};

}  //namespace interprocess
}  // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_CONDITION_ANY_HPP

/* interprocess_condition_any.hpp
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
*/
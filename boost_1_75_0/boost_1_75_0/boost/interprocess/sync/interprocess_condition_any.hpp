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
I1olxLePfZ4euAZ9I3fI1xKV7fB+CGymF3G/TDKAfdPbR9doegGGPWx1RXB+IbhYD280fooBmvwO3aGgHhuZPaoOrO4QUO/VDvZ1KKOSJ/JeClq0Hp0R6KvMkf3+i98TgCHYnQPuUw9Yc1t09jKUtQyVxzhCC0sLi6ZgTJwnY+Bc6ftgH6H1NXG0dGno2KGlKhURgTa/jOtfqWLBu2QV/FSR2hwJdbcG1+ansmnqs/kIg6wrghqS9zTmkd7fZlVUg4dFhqUADjdaPwwJUi0dz0OqZvf9fHISVnDdaYjUZOfeRwm/nSuNOVXF0xw1oT1L2H2tMBklHItWTa9XlnRccekumidjib59keT7VLR5FWu/DtgCFrbgmstLNX/tw82rEVGk6q4TaT0gkVZRjTWDM+2xT6IKXevVCzH9a0eNX+urcEFZqSqME/CT6mo0fb5cAodsgXT4NGIWp9M0/z7tvtpMbHp3sr18ST12l15whqRfAZ8Nx59auDlFZh4XRmHNQSsNnI+uERw2wanUXyx2xWeUz+jp7qmvN7OU3RfmIgQUHVko3Qtd8vrNonWYsxlfJU484q79RMJUYxkrEyy4voXffXlkse1gq2fFaxMIT4nliprlGYuXHFU1LC0Q2cTUH5PCFkVdnv3rPmv+euAzifCoXguqewKtUQinVmTOGFJsYyoIxvX45E8fr1WwhdWv9p5hKAtOsH4tyWPP
*/
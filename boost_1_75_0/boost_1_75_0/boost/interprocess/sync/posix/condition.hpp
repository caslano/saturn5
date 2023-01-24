//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_CONDITION_HPP
#define BOOST_INTERPROCESS_POSIX_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <pthread.h>
#include <errno.h>
#include <boost/interprocess/sync/posix/pthread_helpers.hpp>
#include <boost/interprocess/sync/posix/ptime_to_timespec.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/posix/mutex.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class posix_condition
{
   //Non-copyable
   posix_condition(const posix_condition &);
   posix_condition &operator=(const posix_condition &);

   public:
   //!Constructs a posix_condition. On error throws interprocess_exception.
   posix_condition();

   //!Destroys *this
   //!liberating system resources.
   ~posix_condition();

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.
   void notify_one();

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all();

   //!Releases the lock on the posix_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock)
   {
      if (!lock)
         throw lock_exception();
      this->do_wait(*lock.mutex());
   }

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         this->do_wait(*lock.mutex());
   }

   //!Releases the lock on the posix_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      if (!lock)
         throw lock_exception();
      //Posix does not support infinity absolute time so handle it here
      if(abs_time == boost::posix_time::pos_infin){
         this->wait(lock);
         return true;
      }
      return this->do_timed_wait(abs_time, *lock.mutex());
   }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {
      if (!lock)
         throw lock_exception();
      //Posix does not support infinity absolute time so handle it here
      if(abs_time == boost::posix_time::pos_infin){
         this->wait(lock, pred);
         return true;
      }
      while (!pred()){
         if (!this->do_timed_wait(abs_time, *lock.mutex()))
            return pred();
      }
      return true;
   }


   void do_wait(posix_mutex &mut);

   bool do_timed_wait(const boost::posix_time::ptime &abs_time, posix_mutex &mut);

   private:
   pthread_cond_t   m_condition;
};

inline posix_condition::posix_condition()
{
   int res;
   pthread_condattr_t cond_attr;
   res = pthread_condattr_init(&cond_attr);
   if(res != 0){
      throw interprocess_exception("pthread_condattr_init failed");
   }
   res = pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED);
   if(res != 0){
      pthread_condattr_destroy(&cond_attr);
      throw interprocess_exception(res);
   }
   res = pthread_cond_init(&m_condition, &cond_attr);
   pthread_condattr_destroy(&cond_attr);
   if(res != 0){
      throw interprocess_exception(res);
   }
}

inline posix_condition::~posix_condition()
{
    int res = 0;
    res = pthread_cond_destroy(&m_condition);
    BOOST_ASSERT(res == 0); (void)res;
}

inline void posix_condition::notify_one()
{
    int res = 0;
    res = pthread_cond_signal(&m_condition);
    BOOST_ASSERT(res == 0); (void)res;
}

inline void posix_condition::notify_all()
{
    int res = 0;
    res = pthread_cond_broadcast(&m_condition);
    BOOST_ASSERT(res == 0); (void)res;
}

inline void posix_condition::do_wait(posix_mutex &mut)
{
   pthread_mutex_t* pmutex = &mut.m_mut;
   int res = 0;
   res = pthread_cond_wait(&m_condition, pmutex);
   BOOST_ASSERT(res == 0); (void)res;
}

inline bool posix_condition::do_timed_wait
   (const boost::posix_time::ptime &abs_time, posix_mutex &mut)
{
   timespec ts = ptime_to_timespec(abs_time);
   pthread_mutex_t* pmutex = &mut.m_mut;
   int res = 0;
   res = pthread_cond_timedwait(&m_condition, pmutex, &ts);
   BOOST_ASSERT(res == 0 || res == ETIMEDOUT);

   return res != ETIMEDOUT;
}

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_POSIX_CONDITION_HPP

/* condition.hpp
4Hrcd6c0plnGWWKDhp+DvHZF1+SMbl9qdImeB9czzc3wD9Otf96vvy3fUlqlaCakk7n26XJYMYgmON3ebEtJBcKItFk9otj51tXW1LS+DQac5IyYdhI+3AYGvgngCcBvXe2kd2ZLVtD0lhIfcfEeTiEt5whhcWeiV8lqyZ12h7N7WIroiCQ/pMQ75oAxy4g9cFfOBj8GyjMOm/bqe78T/4EZ4fsTx4m0jIV9fwral1odTmmKSXQh5p/GO60irvXCQAwwv50A5GfZLrUyUaEnC8vnm2U9/gGmKTz4TRGK1+qbVjPjd8+SMMM/W1o4nIMYQ2B0abQUzVgOxY1WImgQ97QIrE7ZLq0e9R7+jVKkJCIH4YA4QPjd492r33Pf095L3mPfG90lthzRt6ujNGEzqNkHxG5Vd/wDak3pDlXbsHySAcPkrwBtkUNDQvWQ30XTLO8Zm4hc9Z8f664OrKFTkgvPnqpnmPkr2BYGD0MZ8+BL8iZLYILqfYB36M1NmEZPdtaBt3PZRLfRd1BwNa7BHxnKC4Ht4Oe5TZ7nbVqepqnxdXbcJr+Vl26pN5HNSqtFbvaiWwPpttiihwV1RMBwf0zIWEXjgH5xQkpSNfqv+ZWmTzc/F7+T28S015jPEM5oJEJC1VxmLEZMcngDIsCqc/U73sPQlXn3E2+AtrCmjYEWDr4h5/AFcL/BRq3mqcTTa0tra+wZGz8wDN3B
*/
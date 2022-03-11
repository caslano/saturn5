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
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
*/
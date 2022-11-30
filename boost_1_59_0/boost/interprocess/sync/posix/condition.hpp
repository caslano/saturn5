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

#include <boost/interprocess/sync/cv_status.hpp>
#include <pthread.h>
#include <errno.h>
#include <boost/interprocess/sync/posix/pthread_helpers.hpp>
#include <boost/interprocess/sync/posix/timepoint_to_timespec.hpp>
#include <boost/interprocess/detail/timed_utils.hpp>
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
   template <typename L, typename TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time)
   {
      if (!lock)
         throw lock_exception();
      //Posix does not support infinity absolute time so handle it here
      if(ipcdetail::is_pos_infinity(abs_time)){
         this->wait(lock);
         return true;
      }
      return this->do_timed_wait(abs_time, *lock.mutex());
   }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename TimePoint, typename Pr>
   bool timed_wait(L& lock, const TimePoint &abs_time, Pr pred)
   {
      if (!lock)
         throw lock_exception();
      //Posix does not support infinity absolute time so handle it here
      if(ipcdetail::is_pos_infinity(abs_time)){
         this->wait(lock, pred);
         return true;
      }
      while (!pred()){
         if (!this->do_timed_wait(abs_time, *lock.mutex()))
            return pred();
      }
      return true;
   }

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

   template <typename L, class Duration>
   cv_status wait_for(L& lock, const Duration &dur)
   {  return this->wait_until(lock, duration_to_ustime(dur)) ? cv_status::no_timeout : cv_status::timeout; }

   template <typename L, class Duration, typename Pr>
   bool wait_for(L& lock, const Duration &dur, Pr pred)
   {  return this->wait_until(lock, duration_to_ustime(dur), pred); }

   void do_wait(posix_mutex &mut);

   template<class TimePoint>
   bool do_timed_wait(const TimePoint &abs_time, posix_mutex &mut);

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

template<class TimePoint>
inline bool posix_condition::do_timed_wait
   (const TimePoint &abs_time, posix_mutex &mut)
{
   timespec ts = timepoint_to_timespec(abs_time);
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
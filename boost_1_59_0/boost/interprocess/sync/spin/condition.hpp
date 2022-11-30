//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_SPIN_CONDITION_HPP
#define BOOST_INTERPROCESS_DETAIL_SPIN_CONDITION_HPP

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
#include <boost/interprocess/sync/spin/mutex.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/detail/timed_utils.hpp>
#include <boost/interprocess/sync/spin/wait.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/cstdint.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class spin_condition
{
   spin_condition(const spin_condition &);
   spin_condition &operator=(const spin_condition &);

   public:
   spin_condition()
   {
      //Note that this class is initialized to zero.
      //So zeroed memory can be interpreted as an initialized
      //condition variable
      m_command      = SLEEP;
      m_num_waiters  = 0;
   }

   ~spin_condition()
   {
      //Notify all waiting threads
      //to allow POSIX semantics on condition destruction
      this->notify_all();
   }

   void notify_one()
   {  this->notify(NOTIFY_ONE);  }

   void notify_all()
   {  this->notify(NOTIFY_ALL);  }

   template <typename L>
   void wait(L& lock)
   {
      if (!lock)
         throw lock_exception();
      this->do_timed_wait_impl<false>(0, *lock.mutex());
   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         this->do_timed_wait_impl<false>(0, *lock.mutex());
   }

   template <typename L, typename TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time)
   {
      if (!lock)
         throw lock_exception();
      //Handle infinity absolute time here to avoid complications in do_timed_wait
      if(is_pos_infinity(abs_time)){
         this->wait(lock);
         return true;
      }
      return this->do_timed_wait_impl<true>(abs_time, *lock.mutex());
   }

   template <typename L, typename TimePoint, typename Pr>
   bool timed_wait(L& lock, const TimePoint &abs_time, Pr pred)
   {
      if (!lock)
         throw lock_exception();
      //Handle infinity absolute time here to avoid complications in do_timed_wait
      if(is_pos_infinity(abs_time)){
         this->wait(lock, pred);
         return true;
      }
      while (!pred()){
         if (!this->do_timed_wait_impl<true>(abs_time, *lock.mutex()))
            return pred();
      }
      return true;
   }

   template <typename L, class TimePoint>
   cv_status wait_until(L& lock, const TimePoint &abs_time)
   {  return this->timed_wait(lock, abs_time) ? cv_status::no_timeout : cv_status::timeout; }

   template <typename L, class TimePoint, typename Pr>
   bool wait_until(L& lock, const TimePoint &abs_time, Pr pred)
   {  return this->timed_wait(lock, abs_time, pred); }

   template <typename L, class Duration>
   cv_status wait_for(L& lock, const Duration &dur)
   {  return this->wait_until(lock, duration_to_ustime(dur)); }

   template <typename L, class Duration, typename Pr>
   bool wait_for(L& lock, const Duration &dur, Pr pred)
   {  return this->wait_until(lock, duration_to_ustime(dur), pred); }

   private:

   template<bool TimeoutEnabled, class InterprocessMutex, class TimePoint>
   bool do_timed_wait_impl(const TimePoint &abs_time, InterprocessMutex &mut)
   {
      typedef boost::interprocess::scoped_lock<spin_mutex> InternalLock;
      //The enter mutex guarantees that while executing a notification,
      //no other thread can execute the do_timed_wait method.
      {
         //---------------------------------------------------------------
         InternalLock lock;
         get_lock(bool_<TimeoutEnabled>(), m_enter_mut, lock, abs_time);

         if(!lock)
            return false;
         //---------------------------------------------------------------
         //We increment the waiting thread count protected so that it will be
         //always constant when another thread enters the notification logic.
         //The increment marks this thread as "waiting on spin_condition"
         atomic_inc32(const_cast<boost::uint32_t*>(&m_num_waiters));

         //We unlock the external mutex atomically with the increment
         mut.unlock();
      }

      //By default, we suppose that no timeout has happened
      bool timed_out  = false, unlock_enter_mut= false;

      //Loop until a notification indicates that the thread should
      //exit or timeout occurs
      while(1){
         //The thread sleeps/spins until a spin_condition commands a notification
         //Notification occurred, we will lock the checking mutex so that
         spin_wait swait;
         while(atomic_read32(&m_command) == SLEEP){
            swait.yield();

            //Check for timeout
            if(TimeoutEnabled){
               TimePoint now = get_now<TimePoint>(bool_<TimeoutEnabled>());

               if(now >= abs_time){
                  //If we can lock the mutex it means that no notification
                  //is being executed in this spin_condition variable
                  timed_out = m_enter_mut.try_lock();

                  //If locking fails, indicates that another thread is executing
                  //notification, so we play the notification game
                  if(!timed_out){
                     //There is an ongoing notification, we will try again later
                     continue;
                  }
                  //No notification in execution, since enter mutex is locked.
                  //We will execute time-out logic, so we will decrement count,
                  //release the enter mutex and return false.
                  break;
               }
            }
         }

         //If a timeout occurred, the mutex will not execute checking logic
         if(TimeoutEnabled && timed_out){
            //Decrement wait count
            atomic_dec32(const_cast<boost::uint32_t*>(&m_num_waiters));
            unlock_enter_mut = true;
            break;
         }
         else{
            boost::uint32_t result = atomic_cas32
                           (const_cast<boost::uint32_t*>(&m_command), SLEEP, NOTIFY_ONE);
            if(result == SLEEP){
               //Other thread has been notified and since it was a NOTIFY one
               //command, this thread must sleep again
               continue;
            }
            else if(result == NOTIFY_ONE){
               //If it was a NOTIFY_ONE command, only this thread should
               //exit. This thread has atomically marked command as sleep before
               //so no other thread will exit.
               //Decrement wait count.
               unlock_enter_mut = true;
               atomic_dec32(const_cast<boost::uint32_t*>(&m_num_waiters));
               break;
            }
            else{
               //If it is a NOTIFY_ALL command, all threads should return
               //from do_timed_wait function. Decrement wait count.
               unlock_enter_mut = 1 == atomic_dec32(const_cast<boost::uint32_t*>(&m_num_waiters));
               //Check if this is the last thread of notify_all waiters
               //Only the last thread will release the mutex
               if(unlock_enter_mut){
                  atomic_cas32(const_cast<boost::uint32_t*>(&m_command), SLEEP, NOTIFY_ALL);
               }
               break;
            }
         }
      }

      //Unlock the enter mutex if it is a single notification, if this is
      //the last notified thread in a notify_all or a timeout has occurred
      if(unlock_enter_mut){
         m_enter_mut.unlock();
      }

      //Lock external again before returning from the method
      mut.lock();
      return !timed_out;
   }

   template <class TimePoint>
   static TimePoint get_now(bool_<true>)
   {  return microsec_clock<TimePoint>::universal_time();  }

   template <class TimePoint>
   static TimePoint get_now(bool_<false>)
   {  return TimePoint();  }

   template <class Mutex, class Lock, class TimePoint>
   static void  get_lock(bool_<true>, Mutex &m, Lock &lck, const TimePoint &abs_time)
   { 
      Lock dummy(m, abs_time);
      lck = boost::move(dummy);
   }

   template <class Mutex, class Lock, class TimePoint>
   static void get_lock(bool_<false>, Mutex &m, Lock &lck, const TimePoint &)
   { 
      Lock dummy(m);
      lck = boost::move(dummy);
   }

   void notify(boost::uint32_t command)
   {
      //This mutex guarantees that no other thread can enter to the
      //do_timed_wait method logic, so that thread count will be
      //constant until the function writes a NOTIFY_ALL command.
      //It also guarantees that no other notification can be signaled
      //on this spin_condition before this one ends
      m_enter_mut.lock();

      //Return if there are no waiters
      if(!atomic_read32(&m_num_waiters)) {
         m_enter_mut.unlock();
         return;
      }

      //Notify that all threads should execute wait logic
      spin_wait swait;
      while(SLEEP != atomic_cas32(const_cast<boost::uint32_t*>(&m_command), command, SLEEP)){
         swait.yield();
      }
      //The enter mutex will rest locked until the last waiting thread unlocks it
   }

   enum { SLEEP = 0, NOTIFY_ONE, NOTIFY_ALL };
   spin_mutex  m_enter_mut;
   volatile boost::uint32_t    m_command;
   volatile boost::uint32_t    m_num_waiters;
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_SPIN_CONDITION_HPP

/* condition.hpp
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
*/
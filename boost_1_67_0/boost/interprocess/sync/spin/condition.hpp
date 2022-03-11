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
#include <boost/interprocess/sync/spin/mutex.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
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
   spin_condition();
   ~spin_condition();

   void notify_one();
   void notify_all();

   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      if (!lock)
         throw lock_exception();
      //Handle infinity absolute time here to avoid complications in do_timed_wait
      if(abs_time == boost::posix_time::pos_infin){
         this->wait(lock);
         return true;
      }
      return this->do_timed_wait(abs_time, *lock.mutex());
   }

   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {
      if (!lock)
         throw lock_exception();
      //Handle infinity absolute time here to avoid complications in do_timed_wait
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

   template <typename L>
   void wait(L& lock)
   {
      if (!lock)
         throw lock_exception();
      do_wait(*lock.mutex());
   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         do_wait(*lock.mutex());
   }

   template<class InterprocessMutex>
   void do_wait(InterprocessMutex &mut);

   template<class InterprocessMutex>
   bool do_timed_wait(const boost::posix_time::ptime &abs_time, InterprocessMutex &mut);

   private:
   template<class InterprocessMutex>
   bool do_timed_wait(bool tout_enabled, const boost::posix_time::ptime &abs_time, InterprocessMutex &mut);

   enum { SLEEP = 0, NOTIFY_ONE, NOTIFY_ALL };
   spin_mutex  m_enter_mut;
   volatile boost::uint32_t    m_command;
   volatile boost::uint32_t    m_num_waiters;
   void notify(boost::uint32_t command);
};

inline spin_condition::spin_condition()
{
   //Note that this class is initialized to zero.
   //So zeroed memory can be interpreted as an initialized
   //condition variable
   m_command      = SLEEP;
   m_num_waiters  = 0;
}

inline spin_condition::~spin_condition()
{
   //Notify all waiting threads
   //to allow POSIX semantics on condition destruction
   this->notify_all();
}

inline void spin_condition::notify_one()
{
   this->notify(NOTIFY_ONE);
}

inline void spin_condition::notify_all()
{
   this->notify(NOTIFY_ALL);
}

inline void spin_condition::notify(boost::uint32_t command)
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

template<class InterprocessMutex>
inline void spin_condition::do_wait(InterprocessMutex &mut)
{
   this->do_timed_wait(false, boost::posix_time::ptime(), mut);
}

template<class InterprocessMutex>
inline bool spin_condition::do_timed_wait
   (const boost::posix_time::ptime &abs_time, InterprocessMutex &mut)
{
   return this->do_timed_wait(true, abs_time, mut);
}

template<class InterprocessMutex>
inline bool spin_condition::do_timed_wait(bool tout_enabled,
                                     const boost::posix_time::ptime &abs_time,
                                     InterprocessMutex &mut)
{
   boost::posix_time::ptime now = microsec_clock::universal_time();

   if(tout_enabled){
      if(now >= abs_time) return false;
   }

   typedef boost::interprocess::scoped_lock<spin_mutex> InternalLock;
   //The enter mutex guarantees that while executing a notification,
   //no other thread can execute the do_timed_wait method.
   {
      //---------------------------------------------------------------
      InternalLock lock;
      if(tout_enabled){
         InternalLock dummy(m_enter_mut, abs_time);
         lock = boost::move(dummy);
      }
      else{
         InternalLock dummy(m_enter_mut);
         lock = boost::move(dummy);
      }

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
         if(tout_enabled){
            now = microsec_clock::universal_time();

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
      if(tout_enabled && timed_out){
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

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_SPIN_CONDITION_HPP

/* condition.hpp
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
*/
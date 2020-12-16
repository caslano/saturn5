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
7It+fi1nX/vbYjTza61xPpjHQd8/XBArim3/SV32lE34zW9fu+T0i889fn/fS07duOz7hQvig8j5kG/JT57r1Z4x7Ewde7bfS6aD8QHS7zmu9xz/Weqbvt/pO+l+HS+NC7jjnUEwG+yl41Pp6u6rbsTqC56p7tHg6TpeOwC8TMev1un41MfB4eAmcBT4dR3nfUjHcR8BLwAfVfe3wfFgrfo/B04A68GJ4EvgheDL4EXgm+BU8A+aDjsvM8AgOAvMBmeD/dR9JngZOAi8FHTGL192x/OqWxjnPObRmx6mFx9w9ax90eklR6mX49HLNIybBqO0/dr+RJP9V2Et4zdP4vdE28YOaz3jh88+8d+xCdv/xAfXLuzoE223DUusJd210dmI5dW2Pn4ZshObXBudrVhFrWsvtrG24zZjW2tjOmwztqu27XZj9bWu7djh2o7Zj52sjd6GLPnJ/y87Mq8NWcGTHbMj28PY6XEk8xbaJLIUqb6lczy189f56/x1/jp/nb/OX+ev89f56/x1/t4Pv/du/r+s9LpTNP9/YSrjkjr/f1DHU4eEOB+RGtum6SWZc5EJF10E0GTfvKSkMldsHn1cAM66+eMS9nQr3bxXu8bt2iQGPHsxWz+X/VNN8zIazrWt3xQI7W3T1zM31ao9qmGfBeUyaD4/JXM1oXJKi9Xy0UgGIV8gbO7PzeWkJrTlq1dUGjkT7EjzJGwPUxlpvAHfXohp9piznOuqbnYxEHeslEtjgHsao7bXXbM8c7E+WxInHRdK+O7qDsUXYyzHuCjK0Vtue7TcunvsNL+IboW/3KTEpHqpeXZz+1g3vZUSNtFUbhpvoFWbaU231xa0WbrXa0Z7Wq699GbSXdVCutUjYrrXS9guxnRXdTDdUzXd+fH+dH+JdG9pKd03rF5UVrq4tGTlqohp39pC2rd0MO0XhtKeoDb27ppj6357P2l/2rEf0rQ3VTlJ97V9XF6PUH/yrITNNqWbeA39kOZ3j5wLmveMbmN+SVeIT8LQx7j37mSCv60U2n1xS/kXj1KshExloP1xC+3lWAfyYqd9hqa9rovOP2mgdE271RA57bIluJsBX/pDz5O4Bt0zzfw84Rody0Oo/q1N9Jf/FnRzzHnQjt7t401lP7AhctnndDDdjv1nV7P9Z25Dx+0/cxvav6aHuI1revp2i2AP2XCK7CEbol/bkt/Q/rUt0dhDHv8/2d/ja7Km44KKmoTyN1485+prZnfp03jm7z94azo69/dw13qoHWvEfTnEvi703q7fGHVe+zq1E7RxBpio9n9dwZlgUO0FMy1dH6Hn+4Czwb5qNzhY/f8MFjjvzqRFr9cFmazXO1+vd4FebyrYU9dnZNl64EC1axxkn9d480Pvlvp8qNN+Ky/E8azxlmq8ZZqPZWBQ3G48VRpPT0M8czWeeRrPhzWe+WAPcbvxbGkhnkKNZ5HGU6zxFGk8xRrP9ND7DNhP40lAxnvsvmzsB/YGc/Q+nK73oT94mrjddB1roZzO0vgGabrO1nQNAYPq1r0P9LlO/TLsfXCOxpOr8Zyn8YzS+3kumKL+qbqOJ13dmk59/prT2VvjT9f4szT+TE0nbtcOryG6vSHyW9HbExfduphTYUP3Xq1/+aCufWnrupdo1rtEu9YlmnUunZzI0a1neS/WsrwX61gi8yG3bQ1LLetVDiHJ62hbyFKkBnkWOY4MvjXWmoOsu7VzXUvnr/PX+ev8df46f52/zl/n7//v997N/9u26KeG/3+yh/+/Vub/XXueacjdDG5U73Xs//XaLhezy+Hv2sbfJ/oXGsfjicudt9c9Dnf0sjn0hkS0Da/Ac4py6Lk6zbmAf47b5nk=
*/
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_CONDITION_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_CONDITION_HPP

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
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/windows/semaphore.hpp>
#include <boost/interprocess/sync/windows/mutex.hpp>
#include <boost/interprocess/sync/detail/condition_algorithm_8a.hpp>


namespace boost {
namespace interprocess {
namespace ipcdetail {

class winapi_condition
{
   winapi_condition(const winapi_condition &);
   winapi_condition &operator=(const winapi_condition &);

   public:
   winapi_condition()
      : m_condition_data()
   {}

   ~winapi_condition()
   {
      //Notify all waiting threads
      //to allow POSIX semantics on condition destruction
      this->notify_all();
   }

   void notify_one()
   {  m_condition_data.notify_one();   }

   void notify_all()
   {  m_condition_data.notify_all();   }

   template <typename L>
   void wait(L& lock)
   {  m_condition_data.wait(lock);   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  m_condition_data.wait(lock, pred);   }


   template <typename L, typename TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time)
   {  return m_condition_data.timed_wait(lock, abs_time);   }

   template <typename L, typename TimePoint, typename Pr>
   bool timed_wait(L& lock, const TimePoint &abs_time, Pr pred)
   {  return m_condition_data.timed_wait(lock, abs_time, pred);   }

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

   struct condition_data
   {
      typedef unsigned int      integer_type;
      typedef winapi_semaphore  semaphore_type;
      typedef winapi_mutex      mutex_type;

      condition_data()
         : m_nwaiters_blocked(0)
         , m_nwaiters_gone(0)
         , m_nwaiters_to_unblock(0)
         , m_sem_block_queue(0)
         , m_sem_block_lock(1)
         , m_mtx_unblock_lock()
      {}

      integer_type    &get_nwaiters_blocked()
      {  return m_nwaiters_blocked;  }

      integer_type    &get_nwaiters_gone()
      {  return m_nwaiters_gone;  }

      integer_type    &get_nwaiters_to_unblock()
      {  return m_nwaiters_to_unblock;  }

      semaphore_type  &get_sem_block_queue()
      {  return m_sem_block_queue;  }

      semaphore_type  &get_sem_block_lock()
      {  return m_sem_block_lock;  }

      mutex_type      &get_mtx_unblock_lock()
      {  return m_mtx_unblock_lock;  }

      integer_type            m_nwaiters_blocked;
      integer_type            m_nwaiters_gone;
      integer_type            m_nwaiters_to_unblock;
      semaphore_type          m_sem_block_queue;
      semaphore_type          m_sem_block_lock;
      mutex_type              m_mtx_unblock_lock;
   };

   ipcdetail::condition_8a_wrapper<condition_data> m_condition_data;
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_CONDITION_HPP

/* condition.hpp
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
*/
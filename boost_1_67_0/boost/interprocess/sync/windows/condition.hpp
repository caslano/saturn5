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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/windows/semaphore.hpp>
#include <boost/interprocess/sync/windows/mutex.hpp>
#include <boost/interprocess/sync/detail/condition_algorithm_8a.hpp>


namespace boost {
namespace interprocess {
namespace ipcdetail {

class windows_condition
{
   windows_condition(const windows_condition &);
   windows_condition &operator=(const windows_condition &);

   public:
   windows_condition()
      : m_condition_data()
   {}

   ~windows_condition()
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
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return m_condition_data.timed_wait(lock, abs_time);   }

   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {  return m_condition_data.timed_wait(lock, abs_time, pred);   }

   template <typename L>
   void wait(L& lock)
   {  m_condition_data.wait(lock);   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  m_condition_data.wait(lock, pred);   }

   private:

   struct condition_data
   {
      typedef boost::int32_t     integer_type;
      typedef windows_semaphore  semaphore_type;
      typedef windows_mutex      mutex_type;

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

      boost::int32_t    m_nwaiters_blocked;
      boost::int32_t    m_nwaiters_gone;
      boost::int32_t    m_nwaiters_to_unblock;
      windows_semaphore m_sem_block_queue;
      windows_semaphore m_sem_block_lock;
      windows_mutex     m_mtx_unblock_lock;
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
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
//yum686fhG0kNDVvZiLuu3wacHFl4bm3ln2rLcstNtef141sB3VwkKNf3zzmnfTaZElNvzznJi0Ff6nkX47Hn/s5BuDyCKkj0h0x3KMD1u3hIwW0/ioMiIMYyBZdSrM1PrhNMbjy+Hm0HDwKd84xBYjfWTiO5hjrNi7J2702AdMqTFiHRZZI5FRdnkaZxJUgnpXxCCaQ/I+IUVeJkXd6A6kqM3W/LLVZ3xSylCIAiPD9LTEo2uCRo1xnNQZGaaxkK5+gSenjAUpMELMT0+8uihyFIsMnGJjxT488kYks/wytc4orGAVR8N3RT0fmYoQrny2jiWMCZ9uCRktpvFRZUQYxkCy6oz8zlyM9JFhYje/7okbPfYBU2qMWIdF4kh4f2ey3GMukqr/duMzSp+n6eWqvuGY9yk34WOLkD4i0R3LMT5s3RIyWkzjo8qIMIyBLNUz6ixP2UxaSlCvsFcwYyFSlC/oFeTVNUGjxjhO6owM01hIV7+AVaGqVzBPJ3ONmUq2BatXMPlaxcaKfXikjkguKyPyMsnjkMPSYGt+2eozWhsZClFgZJgsDh5dEzRqjOOkzsgwjYU89TPrLVPhjJryVbHbXgfZLj/S8+bEdp9CYbcfDOtWM3YDbT8s9Gnvvz91Oj+f/9I/f/m2
*/
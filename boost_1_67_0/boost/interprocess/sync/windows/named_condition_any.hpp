 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_ANY_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_ANY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/windows/named_sync.hpp>
#include <boost/interprocess/sync/windows/winapi_semaphore_wrapper.hpp>
#include <boost/interprocess/sync/detail/condition_algorithm_8a.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class windows_named_condition_any
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   windows_named_condition_any();
   windows_named_condition_any(const windows_named_condition_any &);
   windows_named_condition_any &operator=(const windows_named_condition_any &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   windows_named_condition_any
      (create_only_t, const char *name, const permissions &perm)
      : m_condition_data()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.open_or_create(DoCreate, name, perm, callbacks);
   }

   windows_named_condition_any
      (open_or_create_t, const char *name, const permissions &perm)
      : m_condition_data()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.open_or_create(DoOpenOrCreate, name, perm, callbacks);
   }

   windows_named_condition_any(open_only_t, const char *name)
      : m_condition_data()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.open_or_create(DoOpen, name, permissions(), callbacks);
   }

   ~windows_named_condition_any()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.close(callbacks);
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

   static bool remove(const char *name)
   {  return windows_named_sync::remove(name);  }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   void dont_close_on_destruction()
   {}

   friend class interprocess_tester;

   struct condition_data
   {
      typedef boost::int32_t           integer_type;
      typedef winapi_semaphore_wrapper semaphore_type;
      typedef winapi_mutex_wrapper     mutex_type;

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

      integer_type               m_nwaiters_blocked;
      integer_type               m_nwaiters_gone;
      integer_type               m_nwaiters_to_unblock;
      winapi_semaphore_wrapper   m_sem_block_queue;
      winapi_semaphore_wrapper   m_sem_block_lock;
      winapi_mutex_wrapper       m_mtx_unblock_lock;
   };

   class named_cond_callbacks : public windows_named_sync_interface
   {
      typedef __int64 sem_count_t;
      mutable sem_count_t sem_counts [2];

      public:
      named_cond_callbacks(condition_data &cond_data)
         : m_condition_data(cond_data)
      {}

      virtual std::size_t get_data_size() const
      {  return sizeof(sem_counts);   }

      virtual const void *buffer_with_final_data_to_file()
      {
         sem_counts[0] = m_condition_data.m_sem_block_queue.value();
         sem_counts[1] = m_condition_data.m_sem_block_lock.value();
         return &sem_counts;
      }

      virtual const void *buffer_with_init_data_to_file()
      {
         sem_counts[0] = 0;
         sem_counts[1] = 1;
         return &sem_counts;
      }

      virtual void *buffer_to_store_init_data_from_file()
      {  return &sem_counts; }

      virtual bool open(create_enum_t, const char *id_name)
      {
         m_condition_data.m_nwaiters_blocked = 0;
         m_condition_data.m_nwaiters_gone = 0;
         m_condition_data.m_nwaiters_to_unblock = 0;

         //Now open semaphores and mutex.
         //Use local variables + swap to guarantee consistent
         //initialization and cleanup in case any opening fails
         permissions perm;
         perm.set_unrestricted();
         std::string aux_str  = "Global\\bipc.cond.";
         aux_str += id_name;
         std::size_t pos = aux_str.size();

         //sem_block_queue
         aux_str += "_bq";
         winapi_semaphore_wrapper sem_block_queue;
         bool created;
         if(!sem_block_queue.open_or_create
            (aux_str.c_str(), sem_counts[0], winapi_semaphore_wrapper::MaxCount, perm, created))
            return false;
         aux_str.erase(pos);

         //sem_block_lock
         aux_str += "_bl";
         winapi_semaphore_wrapper sem_block_lock;
         if(!sem_block_lock.open_or_create
            (aux_str.c_str(), sem_counts[1], winapi_semaphore_wrapper::MaxCount, perm, created))
            return false;
         aux_str.erase(pos);

         //mtx_unblock_lock
         aux_str += "_ul";
         winapi_mutex_wrapper mtx_unblock_lock;
         if(!mtx_unblock_lock.open_or_create(aux_str.c_str(), perm))
            return false;

         //All ok, commit data
         m_condition_data.m_sem_block_queue.swap(sem_block_queue);
         m_condition_data.m_sem_block_lock.swap(sem_block_lock);
         m_condition_data.m_mtx_unblock_lock.swap(mtx_unblock_lock);
         return true;
      }

      virtual void close()
      {
         m_condition_data.m_sem_block_queue.close();
         m_condition_data.m_sem_block_lock.close();
         m_condition_data.m_mtx_unblock_lock.close();
         m_condition_data.m_nwaiters_blocked = 0;
         m_condition_data.m_nwaiters_gone = 0;
         m_condition_data.m_nwaiters_to_unblock = 0;
      }

      virtual ~named_cond_callbacks()
      {}

      private:
      condition_data &m_condition_data;
   };

   windows_named_sync   m_named_sync;
   ipcdetail::condition_8a_wrapper<condition_data> m_condition_data;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_ANY_HPP

/* named_condition_any.hpp
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
*/
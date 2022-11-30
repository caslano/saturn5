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

#include <boost/interprocess/sync/cv_status.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/sync/windows/named_sync.hpp>
#include <boost/interprocess/sync/windows/winapi_semaphore_wrapper.hpp>
#include <boost/interprocess/sync/detail/condition_algorithm_8a.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

template<class CharT>
struct named_cond_callbacks_str;

template<>
struct named_cond_callbacks_str<char>
{
   static const char* ipc_cond()
   {  return "Global\\bipc.cond.";  }

   static const char* bq()
   {  return "_bq";  }

   static const char* bl()
   {  return "_bl";  }

   static const char* ul()
   {  return "_ul";  }
};

template<>
struct named_cond_callbacks_str<wchar_t>
{
   static const wchar_t* ipc_cond()
   {  return L"Global\\bipc.cond.";  }

   static const wchar_t* bq()
   {  return L"_bq";  }

   static const wchar_t* bl()
   {  return L"_bl";  }

   static const wchar_t* ul()
   {  return L"_ul";  }
};

class winapi_named_condition_any
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   winapi_named_condition_any();
   winapi_named_condition_any(const winapi_named_condition_any &);
   winapi_named_condition_any &operator=(const winapi_named_condition_any &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   winapi_named_condition_any
      (create_only_t, const char *name, const permissions &perm = permissions())
      : m_condition_data()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.open_or_create(DoCreate, name, perm, callbacks);
   }

   winapi_named_condition_any
      (open_or_create_t, const char *name, const permissions &perm = permissions())
      : m_condition_data()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.open_or_create(DoOpenOrCreate, name, perm, callbacks);
   }

   winapi_named_condition_any(open_only_t, const char *name)
      : m_condition_data()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.open_or_create(DoOpen, name, permissions(), callbacks);
   }

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   winapi_named_condition_any
      (create_only_t, const wchar_t *name, const permissions &perm = permissions())
      : m_condition_data()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.open_or_create(DoCreate, name, perm, callbacks);
   }

   winapi_named_condition_any
      (open_or_create_t, const wchar_t *name, const permissions &perm = permissions())
      : m_condition_data()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.open_or_create(DoOpenOrCreate, name, perm, callbacks);
   }

   winapi_named_condition_any(open_only_t, const wchar_t *name)
      : m_condition_data()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.open_or_create(DoOpen, name, permissions(), callbacks);
   }

   #endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   ~winapi_named_condition_any()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.close(callbacks);
   }

   void notify_one()
   {  m_condition_data.notify_one();   }

   void notify_all()
   {  m_condition_data.notify_all();   }

   template <typename L, typename TimePoint>
   bool timed_wait(L& lock, const TimePoint &abs_time)
   {  return m_condition_data.timed_wait(lock, abs_time);   }

   template <typename L, typename TimePoint, typename Pr>
   bool timed_wait(L& lock, const TimePoint &abs_time, Pr pred)
   {  return m_condition_data.timed_wait(lock, abs_time, pred);   }

   template <typename L>
   void wait(L& lock)
   {  m_condition_data.wait(lock);   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  m_condition_data.wait(lock, pred);   }

   template <typename L, class TimePoint>
   cv_status wait_until(L& lock, const TimePoint &abs_time)
   {  return this->timed_wait(lock, abs_time) ? cv_status::no_timeout : cv_status::timeout; }

   template <typename L, class TimePoint, typename Pr>
   bool wait_until(L& lock, const TimePoint &abs_time, Pr pred)
   {  return this->timed_wait(lock, abs_time, pred); }

   template <typename L, class Duration>
   cv_status wait_for(L& lock, const Duration &dur)
   {  return this->wait_until(lock, ipcdetail::duration_to_ustime(dur)); }

   template <typename L, class Duration, typename Pr>
   bool wait_for(L& lock, const Duration &dur, Pr pred)
   {  return this->wait_until(lock, ipcdetail::duration_to_ustime(dur), pred); }

   static bool remove(const char *name)
   {  return windows_named_sync::remove(name);  }

   static bool remove(const wchar_t *name)
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

      virtual std::size_t get_data_size() const BOOST_OVERRIDE
      {  return sizeof(sem_counts);   }

      virtual const void *buffer_with_final_data_to_file() BOOST_OVERRIDE
      {
         sem_counts[0] = m_condition_data.m_sem_block_queue.value();
         sem_counts[1] = m_condition_data.m_sem_block_lock.value();
         return &sem_counts;
      }

      virtual const void *buffer_with_init_data_to_file() BOOST_OVERRIDE
      {
         sem_counts[0] = 0;
         sem_counts[1] = 1;
         return &sem_counts;
      }

      virtual void *buffer_to_store_init_data_from_file() BOOST_OVERRIDE
      {  return &sem_counts; }

      virtual bool open(create_enum_t op, const char *id_name) BOOST_OVERRIDE
      {  return this->open_impl(op, id_name);   }

      virtual bool open(create_enum_t op, const wchar_t *id_name) BOOST_OVERRIDE
      {  return this->open_impl(op, id_name);   }

      virtual void close() BOOST_OVERRIDE
      {
         m_condition_data.m_sem_block_queue.close();
         m_condition_data.m_sem_block_lock.close();
         m_condition_data.m_mtx_unblock_lock.close();
         m_condition_data.m_nwaiters_blocked = 0;
         m_condition_data.m_nwaiters_gone = 0;
         m_condition_data.m_nwaiters_to_unblock = 0;
      }

      virtual ~named_cond_callbacks() BOOST_OVERRIDE
      {}

      private:

      template<class CharT>
      bool open_impl(create_enum_t, const CharT *id_name)
      {
         typedef named_cond_callbacks_str<CharT> str_t;
         m_condition_data.m_nwaiters_blocked = 0;
         m_condition_data.m_nwaiters_gone = 0;
         m_condition_data.m_nwaiters_to_unblock = 0;

         //Now open semaphores and mutex.
         //Use local variables + swap to guarantee consistent
         //initialization and cleanup in case any opening fails
         permissions perm;
         perm.set_unrestricted();
         std::basic_string<CharT> aux_str  = str_t::ipc_cond();
         aux_str += id_name;
         std::size_t pos = aux_str.size();

         //sem_block_queue
         aux_str += str_t::bq();
         winapi_semaphore_wrapper sem_block_queue;
         bool created;
         if(!sem_block_queue.open_or_create
            (aux_str.c_str(), static_cast<long>(sem_counts[0]), winapi_semaphore_wrapper::MaxCount, perm, created))
            return false;
         aux_str.erase(pos);

         //sem_block_lock
         aux_str += str_t::bl();
         winapi_semaphore_wrapper sem_block_lock;
         if(!sem_block_lock.open_or_create
            (aux_str.c_str(), static_cast<long>(sem_counts[1]), winapi_semaphore_wrapper::MaxCount, perm, created))
            return false;
         aux_str.erase(pos);

         //mtx_unblock_lock
         aux_str += str_t::ul();
         winapi_mutex_wrapper mtx_unblock_lock;
         if(!mtx_unblock_lock.open_or_create(aux_str.c_str(), perm))
            return false;

         //All ok, commit data
         m_condition_data.m_sem_block_queue.swap(sem_block_queue);
         m_condition_data.m_sem_block_lock.swap(sem_block_lock);
         m_condition_data.m_mtx_unblock_lock.swap(mtx_unblock_lock);
         return true;
      }

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
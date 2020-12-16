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
VulNco74LCCTZP82+O2siG+eQySPTGbYi/pu7iM8c/FtNxV+PCGOD+YF39o4Y9fVYPmMjpDzdxjHIZ99fqpRSPyVIec/QPsQ1QbpTqRh6B/ThJ7N6cTlP5ItSf5uzgJNCouUln3XTVHfUNu+zf7IR3+o9g2945joPRa7T/2qNhAh9n572sBYpE9NfPDNsTYgETY4r3zcGWOjTp1X1hf+beBjFdLZBcvrpcxLIp+F299czue57UST1xBckR1LYTc5P0iwYxmmTaNNo6HrcGZBOBWDx75OEONAvlXAt63J139NFw4isa9up/5NXeRDF6r+SxT9q37OrYwdUMT43YPx8znyt3TquqqhbmQFAhvgHrhiWlUdHKyp7w2zLb96S1+XLjTz9LZxgVLGXrC1dD22QdHhj1Ke6NDGR8j5ycZq+J1oYxqZbxu7P+yy1HFl9cVokWsPK+4FLG+2tIPjY+uFIqfln/6llNXXGn/LZX8HYzCktsuYXj97li1rrpRxDDjKjVpwFcbkvU3yzkZkjLONPgr2QuZ1K6bLa8Lbhrk1ZMWrOh32cQbSDtmJx2O0/9E3xCHY/f+jHIN+6ZedIvJiXBV07q/p2N/VsR9x7B+j7Ktjt72fG1f4VRF+blFwhRy/0fuqj71xhciXPK7QuCV5XKFxiy9cYcwzxcddwBVa6x9lufXzDcordumH99jEu3TEw1760FGxDx0Vd0NHHV3QkRXPJMuNB2rBQC67RcUD0YaSufe9JXk8UNktXccDlWQntwbSsmx3+74z75017aMNJHz+rPTRxkp/bdQ8T3u3cQNeV9pw3Nz2Zp1TkJajjc12G+XdhVxUiHv6QWy8Avd19nVY4stInj1k/ocMLCMnNkaNq/329bgA9CI5v7FOH8iru3YQLyvndlLnbEDq7Gveg3I+i/u9jFfMfeLgd8kRNIAl9xlybkfn/G9dp06S8+ONobgXeBKFl6EdZ3Zi5MO9eocz0sK9Ng5nhKyYSh1ZZuL9A/NUg/8spHDvYqt/vyFPdP/sJGJnRPFVP8g4tvrE0e/UMXnRXhw7UOxgW9rBWXnudZaeRZnGrWIHnQ8bWG1J+9KF9xq4BoK3TvY1to+y7Ge0F8A7BXWeI/h7/X2T4XHdPF3ahHpoyztE31Pku57FpQ1ZCdoQmR3x1Y4spR3z0YZSnNgVlYaz7fvF4dnda1P0vi+vwN0vv6FNpZ1tQmu22m38yIrdtxo3Ec90TbOibfhFxmjD/vo2ML8yt3QksUZWVFaz7HyU7ZTVGOCW9Q/wlulkBeKvqSY5WZHf8aw3s3qObs60ee0x1cV2cfzw2Qf1OWztME1b8bholFtt3W3CVtvsWLHztk5zs1Yo870+WXSsjhrorjuEuiuTqBsWInpMGRJf55XdsA+ULXp0js+NBrnlTgdvJLHc1hDtx+uPt+wsj++SnhNeM+v0prppepshvzJ2k2/rD4rNFNBmnpNjdp1q35UWunWQAR00J6GDpoYZSbVfysI/ey6LmCHv9NdUR9s/99HPP7jHC+cx1Ofo++GD3e3ui3a3JG43Z4rk7LbFx1zR0o25ImVI4rmC78+xxrD+2rqAbfe4qrL/4rd3gaMN3/loA8q22qCuuVhe5JY3E+1dqMirn9L8r7lIHWHudNe5HuaLVu86m6JxPkcOiq+j1m7MZShbq6NfNfJWgbdNKy+nMB/92qbMYSdmJ57D2roxh0EW1xyGOh1zmN1Xnw91t30F6KNd33ZOXcm1u90ev3iOij93tXdj7oIcrvGL+jh3xba3qNjd3v5ob4dXe+WFZ3Lt7fAxX3XodaN/5+3QzYCc7unGmtt4LBxHX+GV3PpafxB+bqO+9FN8UmM=
*/
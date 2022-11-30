 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_SEMAPHORE_HPP

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
#include <boost/interprocess/sync/windows/named_sync.hpp>
#include <boost/interprocess/sync/windows/winapi_semaphore_wrapper.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {



class winapi_named_semaphore
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   winapi_named_semaphore();
   winapi_named_semaphore(const winapi_named_semaphore &);
   winapi_named_semaphore &operator=(const winapi_named_semaphore &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   winapi_named_semaphore(create_only_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   winapi_named_semaphore(open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   winapi_named_semaphore(open_only_t, const char *name);

   winapi_named_semaphore(create_only_t, const wchar_t *name, unsigned int initialCount, const permissions &perm = permissions());

   winapi_named_semaphore(open_or_create_t, const wchar_t *name, unsigned int initialCount, const permissions &perm = permissions());

   winapi_named_semaphore(open_only_t, const wchar_t *name);

   ~winapi_named_semaphore();

   void post();
   void wait();
   bool try_wait();
   template<class TimePoint> bool timed_wait(const TimePoint &abs_time);

   static bool remove(const char *name);
   static bool remove(const wchar_t *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class interprocess_tester;
   void dont_close_on_destruction();
   winapi_semaphore_wrapper m_sem_wrapper;
   windows_named_sync m_named_sync;

   class named_sem_callbacks : public windows_named_sync_interface
   {
      public:
      typedef __int64 sem_count_t;
      named_sem_callbacks(winapi_semaphore_wrapper &sem_wrapper, sem_count_t sem_cnt)
         : m_sem_wrapper(sem_wrapper), m_sem_count(sem_cnt)
      {}

      virtual std::size_t get_data_size() const BOOST_OVERRIDE
      {  return sizeof(sem_count_t);   }

      virtual const void *buffer_with_final_data_to_file() BOOST_OVERRIDE
      {  return &m_sem_count; }

      virtual const void *buffer_with_init_data_to_file() BOOST_OVERRIDE
      {  return &m_sem_count; }

      virtual void *buffer_to_store_init_data_from_file() BOOST_OVERRIDE
      {  return &m_sem_count; }

      virtual bool open(create_enum_t, const char *id_name) BOOST_OVERRIDE
      {
         std::string aux_str  = "Global\\bipc.sem.";
         aux_str += id_name;
         //
         permissions sem_perm;
         sem_perm.set_unrestricted();
         bool created;
         return m_sem_wrapper.open_or_create
            ( aux_str.c_str(), static_cast<long>(m_sem_count)
            , winapi_semaphore_wrapper::MaxCount, sem_perm, created);
      }

      virtual bool open(create_enum_t, const wchar_t *id_name) BOOST_OVERRIDE
      {
         std::wstring aux_str  = L"Global\\bipc.sem.";
         aux_str += id_name;
         //
         permissions sem_perm;
         sem_perm.set_unrestricted();
         bool created;
         return m_sem_wrapper.open_or_create
            ( aux_str.c_str(), static_cast<long>(m_sem_count)
            , winapi_semaphore_wrapper::MaxCount, sem_perm, created);
      }

      virtual void close() BOOST_OVERRIDE
      {
         m_sem_wrapper.close();
      }

      virtual ~named_sem_callbacks() BOOST_OVERRIDE
      {}

      private:
      winapi_semaphore_wrapper&     m_sem_wrapper;
      sem_count_t m_sem_count;
   };

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline winapi_named_semaphore::~winapi_named_semaphore()
{
   named_sem_callbacks callbacks(m_sem_wrapper, m_sem_wrapper.value());
   m_named_sync.close(callbacks);
}

inline void winapi_named_semaphore::dont_close_on_destruction()
{}

inline winapi_named_semaphore::winapi_named_semaphore
   (create_only_t, const char *name, unsigned int initial_count, const permissions &perm)
   : m_sem_wrapper()
{
   named_sem_callbacks callbacks(m_sem_wrapper, initial_count);
   m_named_sync.open_or_create(DoCreate, name, perm, callbacks);
}

inline winapi_named_semaphore::winapi_named_semaphore
   (open_or_create_t, const char *name, unsigned int initial_count, const permissions &perm)
   : m_sem_wrapper()
{
   named_sem_callbacks callbacks(m_sem_wrapper, initial_count);
   m_named_sync.open_or_create(DoOpenOrCreate, name, perm, callbacks);
}

inline winapi_named_semaphore::winapi_named_semaphore(open_only_t, const char *name)
   : m_sem_wrapper()
{
   named_sem_callbacks callbacks(m_sem_wrapper, 0);
   m_named_sync.open_or_create(DoOpen, name, permissions(), callbacks);
}

inline winapi_named_semaphore::winapi_named_semaphore
   (create_only_t, const wchar_t *name, unsigned int initial_count, const permissions &perm)
   : m_sem_wrapper()
{
   named_sem_callbacks callbacks(m_sem_wrapper, initial_count);
   m_named_sync.open_or_create(DoCreate, name, perm, callbacks);
}

inline winapi_named_semaphore::winapi_named_semaphore
   (open_or_create_t, const wchar_t *name, unsigned int initial_count, const permissions &perm)
   : m_sem_wrapper()
{
   named_sem_callbacks callbacks(m_sem_wrapper, initial_count);
   m_named_sync.open_or_create(DoOpenOrCreate, name, perm, callbacks);
}

inline winapi_named_semaphore::winapi_named_semaphore(open_only_t, const wchar_t *name)
   : m_sem_wrapper()
{
   named_sem_callbacks callbacks(m_sem_wrapper, 0);
   m_named_sync.open_or_create(DoOpen, name, permissions(), callbacks);
}

inline void winapi_named_semaphore::post()
{
   m_sem_wrapper.post();
}

inline void winapi_named_semaphore::wait()
{
   m_sem_wrapper.wait();
}

inline bool winapi_named_semaphore::try_wait()
{
   return m_sem_wrapper.try_wait();
}

template<class TimePoint>
inline bool winapi_named_semaphore::timed_wait(const TimePoint &abs_time)
{
   return m_sem_wrapper.timed_wait(abs_time);
}

inline bool winapi_named_semaphore::remove(const char *name)
{
   return windows_named_sync::remove(name);
}

inline bool winapi_named_semaphore::remove(const wchar_t *name)
{
   return windows_named_sync::remove(name);
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_SEMAPHORE_HPP

/* named_semaphore.hpp
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
*/
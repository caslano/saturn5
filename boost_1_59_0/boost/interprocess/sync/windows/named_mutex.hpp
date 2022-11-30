 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_MUTEX_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_MUTEX_HPP

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
#include <boost/interprocess/sync/windows/sync_utils.hpp>
#include <boost/interprocess/sync/windows/named_sync.hpp>
#include <boost/interprocess/sync/windows/winapi_mutex_wrapper.hpp>
#include <boost/interprocess/errors.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <limits>

namespace boost {
namespace interprocess {
namespace ipcdetail {



class winapi_named_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   winapi_named_mutex();
   winapi_named_mutex(const winapi_named_mutex &);
   winapi_named_mutex &operator=(const winapi_named_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   winapi_named_mutex(create_only_t, const char *name, const permissions &perm = permissions());

   winapi_named_mutex(open_or_create_t, const char *name, const permissions &perm = permissions());

   winapi_named_mutex(open_only_t, const char *name);

   winapi_named_mutex(create_only_t, const wchar_t *name, const permissions &perm = permissions());

   winapi_named_mutex(open_or_create_t, const wchar_t *name, const permissions &perm = permissions());

   winapi_named_mutex(open_only_t, const wchar_t *name);

   ~winapi_named_mutex();

   void unlock();
   void lock();
   bool try_lock();
   template<class TimePoint> bool timed_lock(const TimePoint &abs_time);

   template<class TimePoint> bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   template<class Duration>  bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(duration_to_ustime(dur)); }

   static bool remove(const char *name);

   static bool remove(const wchar_t *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class interprocess_tester;
   void dont_close_on_destruction();
   winapi_mutex_wrapper m_mtx_wrapper;
   windows_named_sync m_named_sync;

   class named_mut_callbacks : public windows_named_sync_interface
   {
      public:
      named_mut_callbacks(winapi_mutex_wrapper &mtx_wrapper)
         : m_mtx_wrapper(mtx_wrapper)
      {}

      virtual std::size_t get_data_size() const BOOST_OVERRIDE
      {  return 0u;   }

      virtual const void *buffer_with_init_data_to_file() BOOST_OVERRIDE
      {  return 0; }

      virtual const void *buffer_with_final_data_to_file() BOOST_OVERRIDE
      {  return 0; }

      virtual void *buffer_to_store_init_data_from_file() BOOST_OVERRIDE
      {  return 0; }

      virtual bool open(create_enum_t, const char *id_name) BOOST_OVERRIDE
      {
         std::string aux_str  = "Global\\bipc.mut.";
         aux_str += id_name;
         //
         permissions mut_perm;
         mut_perm.set_unrestricted();
         return m_mtx_wrapper.open_or_create(aux_str.c_str(), mut_perm);
      }

      virtual bool open(create_enum_t, const wchar_t *id_name) BOOST_OVERRIDE
      {
         std::wstring aux_str  = L"Global\\bipc.mut.";
         aux_str += id_name;
         //
         permissions mut_perm;
         mut_perm.set_unrestricted();
         return m_mtx_wrapper.open_or_create(aux_str.c_str(), mut_perm);
      }

      virtual void close() BOOST_OVERRIDE
      {
         m_mtx_wrapper.close();
      }

      virtual ~named_mut_callbacks() BOOST_OVERRIDE
      {}

      private:
      winapi_mutex_wrapper&     m_mtx_wrapper;
   };
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline winapi_named_mutex::~winapi_named_mutex()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.close(callbacks);
}

inline void winapi_named_mutex::dont_close_on_destruction()
{}

inline winapi_named_mutex::winapi_named_mutex
   (create_only_t, const char *name, const permissions &perm)
   : m_mtx_wrapper()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.open_or_create(DoCreate, name, perm, callbacks);
}

inline winapi_named_mutex::winapi_named_mutex
   (open_or_create_t, const char *name, const permissions &perm)
   : m_mtx_wrapper()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.open_or_create(DoOpenOrCreate, name, perm, callbacks);
}

inline winapi_named_mutex::winapi_named_mutex(open_only_t, const char *name)
   : m_mtx_wrapper()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.open_or_create(DoOpen, name, permissions(), callbacks);
}

inline winapi_named_mutex::winapi_named_mutex
   (create_only_t, const wchar_t *name, const permissions &perm)
   : m_mtx_wrapper()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.open_or_create(DoCreate, name, perm, callbacks);
}

inline winapi_named_mutex::winapi_named_mutex
   (open_or_create_t, const wchar_t *name, const permissions &perm)
   : m_mtx_wrapper()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.open_or_create(DoOpenOrCreate, name, perm, callbacks);
}

inline winapi_named_mutex::winapi_named_mutex(open_only_t, const wchar_t *name)
   : m_mtx_wrapper()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.open_or_create(DoOpen, name, permissions(), callbacks);
}

inline void winapi_named_mutex::unlock()
{
   m_mtx_wrapper.unlock();
}

inline void winapi_named_mutex::lock()
{
   m_mtx_wrapper.lock();
}

inline bool winapi_named_mutex::try_lock()
{
   return m_mtx_wrapper.try_lock();
}

template<class TimePoint>
inline bool winapi_named_mutex::timed_lock(const TimePoint &abs_time)
{
   return m_mtx_wrapper.timed_lock(abs_time);
}

inline bool winapi_named_mutex::remove(const char *name)
{
   return windows_named_sync::remove(name);
}

inline bool winapi_named_mutex::remove(const wchar_t *name)
{
   return windows_named_sync::remove(name);
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_MUTEX_HPP
/* named_mutex.hpp
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
*/
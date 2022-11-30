//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/win32_api.hpp>
#include <boost/interprocess/detail/windows_intermodule_singleton.hpp>
#include <boost/interprocess/sync/windows/sync_utils.hpp>
#include <boost/interprocess/sync/windows/winapi_mutex_wrapper.hpp>
#include <boost/interprocess/exceptions.hpp>


namespace boost {
namespace interprocess {
namespace ipcdetail {

class winapi_mutex
{
   winapi_mutex(const winapi_mutex &);
   winapi_mutex &operator=(const winapi_mutex &);
   public:

   winapi_mutex();
   ~winapi_mutex();

   void lock();
   bool try_lock();
   template<class TimePoint> bool timed_lock(const TimePoint &abs_time);

   template<class TimePoint> bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   template<class Duration>  bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(duration_to_ustime(dur)); }

   void unlock();
   void take_ownership(){};

   private:
   const sync_id id_;
};

inline winapi_mutex::winapi_mutex()
   : id_()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //Create mutex with the initial count
   bool open_or_created;
   (void)handles.obtain_mutex(this->id_, this, &open_or_created);
   //The mutex must be created, never opened
   BOOST_ASSERT(open_or_created);
   BOOST_ASSERT(open_or_created && winapi::get_last_error() != winapi::error_already_exists);
   (void)open_or_created;
}

inline winapi_mutex::~winapi_mutex()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   handles.destroy_handle(this->id_, this);
}

inline void winapi_mutex::lock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_, this));
   mut.lock();
}

inline bool winapi_mutex::try_lock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_, this));
   return mut.try_lock();
}

template<class TimePoint>
inline bool winapi_mutex::timed_lock(const TimePoint &abs_time)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_, this));
   return mut.timed_lock(abs_time);
}

inline void winapi_mutex::unlock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_, this));
   return mut.unlock();
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_MUTEX_HPP

/* mutex.hpp
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
*/
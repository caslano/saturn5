//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_SEMAPHORE_HPP

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
#include <boost/interprocess/sync/windows/winapi_semaphore_wrapper.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/assert.hpp>


namespace boost {
namespace interprocess {
namespace ipcdetail {

class winapi_semaphore
{
   winapi_semaphore(const winapi_semaphore &);
   winapi_semaphore &operator=(const winapi_semaphore &);
   public:

   winapi_semaphore(unsigned int initialCount);
   ~winapi_semaphore();

   void post(unsigned int release_count = 1);
   void wait();
   bool try_wait();
   template<class TimePoint> bool timed_wait(const TimePoint &abs_time);

   private:
   const sync_id id_;
   const unsigned initial_count_;
};

inline winapi_semaphore::winapi_semaphore(unsigned int initialCount)
   : id_(), initial_count_(initialCount)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //Force smeaphore creation with the initial count
   bool open_or_created;
   handles.obtain_semaphore(this->id_, this, initialCount, &open_or_created);
   //The semaphore must be created, never opened
   BOOST_ASSERT(open_or_created);
   BOOST_ASSERT(open_or_created && winapi::get_last_error() != winapi::error_already_exists);
   (void)open_or_created;
}

inline winapi_semaphore::~winapi_semaphore()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   handles.destroy_handle(this->id_, this);
}

inline void winapi_semaphore::wait()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_semaphore_functions sem(handles.obtain_semaphore(this->id_, this, initial_count_));
   sem.wait();
}

inline bool winapi_semaphore::try_wait()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_semaphore_functions sem(handles.obtain_semaphore(this->id_, this, initial_count_));
   return sem.try_wait();
}

template<class TimePoint>
inline bool winapi_semaphore::timed_wait(const TimePoint &abs_time)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_semaphore_functions sem(handles.obtain_semaphore(this->id_, this, initial_count_));
   return sem.timed_wait(abs_time);
}

inline void winapi_semaphore::post(unsigned release_count)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   winapi_semaphore_functions sem(handles.obtain_semaphore(this->id_, this, initial_count_));
   sem.post(static_cast<long>(release_count));
}


}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_SEMAPHORE_HPP

/* semaphore.hpp
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
*/
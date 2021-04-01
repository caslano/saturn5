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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/detail/win32_api.hpp>
#include <boost/interprocess/detail/windows_intermodule_singleton.hpp>
#include <boost/interprocess/sync/windows/sync_utils.hpp>
#include <boost/interprocess/sync/windows/winapi_mutex_wrapper.hpp>
#include <boost/interprocess/exceptions.hpp>


namespace boost {
namespace interprocess {
namespace ipcdetail {

class windows_mutex
{
   windows_mutex(const windows_mutex &);
   windows_mutex &operator=(const windows_mutex &);
   public:

   windows_mutex();
   ~windows_mutex();

   void lock();
   bool try_lock();
   bool timed_lock(const boost::posix_time::ptime &abs_time);
   void unlock();
   void take_ownership(){};

   private:
   const sync_id id_;
};

inline windows_mutex::windows_mutex()
   : id_(this)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //Create mutex with the initial count
   bool open_or_created;
   (void)handles.obtain_mutex(this->id_, &open_or_created);
   //The mutex must be created, never opened
   BOOST_ASSERT(open_or_created);
   BOOST_ASSERT(open_or_created && winapi::get_last_error() != winapi::error_already_exists);
   (void)open_or_created;
}

inline windows_mutex::~windows_mutex()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   handles.destroy_handle(this->id_);
}

inline void windows_mutex::lock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   mut.lock();
}

inline bool windows_mutex::try_lock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   return mut.try_lock();
}

inline bool windows_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   return mut.timed_lock(abs_time);
}

inline void windows_mutex::unlock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   return mut.unlock();
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_MUTEX_HPP

/* mutex.hpp
aRCgOQpMEhVdPOopmCyVgLW+R102wWLzd6aDf/YeZL6RkslSHVmY93Gu1J0IT+R1DD/iL3XPpdT0MOy+zWgeMbz7paAp+D1iylDeJAiTT/8JHAD+OGKTdg2Q71wJWgMJdep9Y1bOSj3A0/RWdDdj2iePpFOh51Qn1aBOgV3w4/nNPYPTqJw/73VkDeKHnmUgPVDQ161JUFesSrV9Xzj9RitnBfjlife5/34EG0qljZd8d41IWgKI7wBm4jJPROKZzzKbJiDPf269OG5HOfx4ZQrBGjRZYuXaO59YMfkJNi0o783desrrY01+Uh0TsrfmUrC2rWlxzbyVJKnFNegGkjldQFQTVgHc4MltzjtyII+Lc/7V0VGY1R9QTgHXpI8JS9bLfHs48gvpX3REd/G6Otx9qUWQtC3fsFMKeP6ngaltnDmSKKTiQNU37OcfAxr6ok4DvFYDjxU+ZMw2xSwrIqtv5TN1Orp56xkvEXxsmOOdtIY2PH0qsY5PEJA20TyjHJJ4mTycw1h7gnKo2vnyCTZQuGNxgCVEl+v4W4dcFGjp21TuChey+e/Twg==
*/
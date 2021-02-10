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
c/rm5etO5/3Ltz+dv3n5Ez3603lnMPj36eB/6/qX16xKubIs95M2I85cm5DeZGEb3Xb42DO/4ZsGLQ8NZ3PLdht+iWfN50df+3408qXmPhx/u1gHGPfn85Yfr9ya04KcZqMd0U2qylT3FDlrvnh+FNLo+J/nR4GWxy/Ozl5keTJ50QyUC5UV6Bc6eP00J72387mhT5afd4Z3+fXqsi8O+Xx3cTfp3dGxoNNg/dkv9UGztYlL7DFxe19MfWJNvbmyffRZaKIsI7bp0e+nnZPNhAmOxohflnARD+ZQMUbFZKc7ZMspG6Ye6w2c4I2CghlmIfTjNAOhWd45B8UyzrIUWxsKpsw56MdxBkKzvHMOisUqlus3B1AwRkE8z/GcgTBnOQgHg7bgAgjNMi95uGELy4bbtRBtoVi6YtAo86wKRTVAsSRLCxpltkYxq3L4PKBSDs8QZlaOx3yolMMYwswqGAvy+OY1ZCsYCQINs23rYeJxjQKBgllv3dgf7UA/5ggQqJdz9kGxnNEf0CurfRX7UwToxxz5AfVyzj4oljPqA3rl3PLEEwjHiA+ol3X2wWzlHO0BDXMufFCMJdIDouUXDTdqkSgP6JWiFxTKGeEBvVJsKiiUM7oDeqX6NaBR7sgOKJb6SA+Nckd11Fux
*/
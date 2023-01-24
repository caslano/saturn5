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
I396w2C1cISGbzWm1lsqcPNKovzqc/q2v1CPzjwg6nfV5iPq4AHyOlHpROZ1uuFeF/j+fS/0FXbeCbWud6fseB1+5/sHsrPeIcob/wPZuf/vP/F/1Z5ruDiYudv8u/Xcx3BMS9S9rQZguZZCJfemOxXrMJbBWnekm/T246G4vvqi4+dBWYdMb0Z9mZJ2158tow35Px5Lo5HzLHFfDb/4rOE7fKFTSG0NJcz5YIPOiKxvA/JWWO8UL2qICJoHcm/Apqfr6y3lluOCqCD21r3uV5tc1sfCx9MH05cMYk0nI4/Crhc6tvLrSpYQ/d64SQr+YokKP4TIlyDWwjmi+efCysJfENqQUFf7+YOT0dyxbgRVtCoETUQ7uLYcq4pFn/SXwkpY8Kl2HDXD+FeJuH1H0Opiuelya9rmiMAc1NUksG5YrOaXf17rfT1Zz05s3yfDL96s6vx89+opMj+UJvzZy4gjpNqH6b4kuHkQQs8mOhxmsuOnKULyo5i8I7c7rYv8468q5jc9vSr0OZHmPhZQuR9dodYWIcBE8huehBBUkMAzfRbvufAU0u+P5wIkCUiXm+8WplPCDqo4774zXyLFGnioXJT2dnwZfd7fnjJrxSpl4992CHRXWkYef1zF9vPuTF46P61k0o2on8zZ0zekuh/1pVd1NBA+NVzvkHTgCxOwJAqpHQhDdi535175uhCujhxSaupgGHCeIZF0
*/
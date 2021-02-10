 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINAPI_WRAPPER_COMMON_HPP
#define BOOST_INTERPROCESS_DETAIL_WINAPI_WRAPPER_COMMON_HPP

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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/errors.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <limits>

namespace boost {
namespace interprocess {
namespace ipcdetail {

inline bool winapi_wrapper_timed_wait_for_single_object(void *handle, const boost::posix_time::ptime &abs_time);
 
inline void winapi_wrapper_wait_for_single_object(void *handle)
{
   winapi_wrapper_timed_wait_for_single_object(handle, boost::posix_time::pos_infin);
}

inline bool winapi_wrapper_try_wait_for_single_object(void *handle)
{
   return winapi_wrapper_timed_wait_for_single_object(handle, boost::posix_time::min_date_time);
}

inline bool winapi_wrapper_timed_wait_for_single_object(void *handle, const boost::posix_time::ptime &abs_time)
{
   const boost::posix_time::ptime cur_time = microsec_clock::universal_time();
   //Windows uses relative wait times so check for negative waits
   //and implement as 0 wait to allow try-semantics as POSIX mandates.
   unsigned long time = 0u;
   if (abs_time == boost::posix_time::pos_infin){
      time = winapi::infinite_time;
   }
   else if(abs_time > cur_time){
      time = (abs_time - cur_time).total_milliseconds();
   }

   unsigned long ret = winapi::wait_for_single_object(handle, time);
   if(ret == winapi::wait_object_0){
      return true;
   }
   else if(ret == winapi::wait_timeout){
      return false;
   }
   else if(ret == winapi::wait_abandoned){ //Special case for orphaned mutexes
      winapi::release_mutex(handle);
      throw interprocess_exception(owner_dead_error);
   }
   else{
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINAPI_WRAPPER_COMMON_HPP

/* winapi_wrapper_common.hpp
rmDtXzEiTY54PGD7UKsDNQlXGWkFZrblBTeoBu6KcC5ccDdFCTTF6XhrFl9DBG8DoZOgOaFwyLuDVQNpB9D0hFUm5VNUSaOW+yzZO5Km6F4fWy9UO925qk8tvDallq9a+ny5K2KI6cy6eu2OzCri6b6HgmaWRrSfgVPyFFWY/90PQoPnhsSCdAuvHvKOIGqKq07LrbCyZj30TLms73twMl92TsMV7hLmOarue6hTMcHtRK4U2DRsdaw1uJlHGsCkjJ5JQ86EUohcaXl7Hn+DMM9lpTR4bkgsSLfw6iHvCKKmuOq03Aora9bzn2kH3DUkVd86+ZrhWurPg92KkjWq9fzVs+TOVyFTXE8VDHlwZvolpuh/hXkzvxSfRu+XYrLY/FJsEq1fysSh8ksxFBG/lE0P9UvZ1eR+KZ0WcpYNzi2RyuaXYjPZ/VJlEFn8UnYevV+Kpg37pQjKKr8USRf0S+lULX4phiLil7LpoX4pu5rcLwVqCf1Suqh+vxQaM+yX0kT0+aXk8d7KL1UGkcUvxeWx+qX4NHq/lJFF6ZfiqGJ+Kasm7pdiKCJ+Ka0euoPGvw8qi8zql+JzMfxS5VDZ/FIMJotfiqiv8EtR1JV+KZo27JfSKtv8UhxVzC9l1cT9UgxFxC8F64n9UtrI
*/
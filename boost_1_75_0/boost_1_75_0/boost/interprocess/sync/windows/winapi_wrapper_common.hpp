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
1s0aPhUnBCrFQknCW+InLqurPRkUhlaDQ9ZEvJ/LSpQYPWO80X7zxs1gcpP6Y0Z8bG7idGPWUONtuBdy3ku+5VH5kH7DfKlk2BtgBeWa0mMZ6/l6uXRrU4PXpcfjVaW/i7CnsjhgvhoOmN4onHJpriuqcW2vG+yct2VtzF7eG256ZSBzvXWQjJ/RTTaois2Lq4/U34s1xBHlUxW6KMpvxTCeqghzbiYUTUbE7xXwF+Mr4UkO9Ds5LimYN3vB+oNYCGchGJdfhQUk8cBkwAlHcuQPDPvVB9jbtC01Q//a+5fEomjSzo/ae+quwUwoCRoIootf5P/Mz2XNP1Cm9eYrz/ecNBBy29/M9Cl+swQc0kCsTx17rsbWShYQIQYQNnnQV24JHBDjya1THg+rjY5s8oL/vPqLy1X5TjlXWvHOx99jp4GQoBe4dRWgHFWy/TO1zTPq/N0QBInbviK5pDZKVEYFqEGzIkVVWSk9w4Cxo3QCBs1fcPGvFRRbnyafCixeq93NF4b9mUOntU6ckUmYLASZiBvYzrQxXX3gdOkKCIXaxQX2Vtmsn0z191U0zN/tvgEgWmk9kdAkY/HT+OHA/b7KBpDYPN8J/YvsC8Ni6wIfB2n30czTr+LMSIedEmeQd/8BQmAmNBsaCU3vlYVZ3bmbRCqtm6aTtm4hiT5K/pE9FSs6S+aI/uzI5648dyogu+466cpUuKB8li3c
*/
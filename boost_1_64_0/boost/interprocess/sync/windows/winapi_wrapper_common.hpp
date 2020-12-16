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
LxBtq6nzma0198Shb0+0vgPQ/7fS171In8aHTX3PbK35cBz6kja89voOpu+pRfr0DZj6ntlacyAOfQPR+r6D6Xt8cVR9xfT17A7pe2ZrzZ7dzvX17B7YutlK1yNLonRl2paZup7ZWnNZHLqW7R7Yuhnxadea+y6JzccLRZtr6hr/WnOFoueDuXbrr6RV118HoMwiTu36676lsbouFm2uqWv8a83+OHT1R+s6AOXVStddl8bqeoloc01d419r7lJ0/WGe3foradX11wFIV8SpXWveclmsrpeKttbUNf615p44dO2J1nUA0hVxateaG5bF6noRBDls6hrfWvNhRc/aXLs1WNKqa7ADkKaIU7vWvLwiVs9lon019YxvrTkQh56BaD0HID2j9Twp7Jk8cD6D9L6BrH0J6X0Gxe8baIb0DbTomUOBMTc/+bvzvjDniTufea5u4HwD6X33vPM+g6x8A9VLfVNPDvn7umVrrn8ta9zd/o9uykE7AvAkffV7lb//TMOw46fv7Z7/2tnPvoE7BwaL9z2/WnnW7uonsrZmH0oq/OvjL/znfAzpfVfF73vIzscQj8/J+fI+4BOgDfDvl/D3G8BloTseeT+l+OYCjCZvPaaEBb6JfoQagEN8feQr1fCNJd844JHAExS+APlGavh2JQX5dgOPAIZ+kq86dAcdcCX5MgHLyfch8m0ELga+HXgU8IeBxwO3A88E3gT8AeCtwLOBNwNfzWfTHoxniEa+Guq1CrgQ2Ee9ZgB6yHc++VIAE8l3OfmuABbvrwQ+D/gqhT9A/nM1/JXkX0n+a4DPAb7etCvgI9Z27aJ9Pkq73qfoW23Dt518d5GvU7UT+cZo+OZT3gXA4t1CNd+Q7ywN3xLyXQJcCnyZmm9s5CwlH8KUcp5NvurQ3S/AN2jyzTrqt575xs98czPzTRPzSTPwfOBbgBcAtwJfz2fKx7tU9Pnm/ZTvA8w35ZRvkaAl3yTypQFmka+W8vmA3cCrgT3A9cC5wGuAJ/KZ+QgJY5UPgSnHJOaj85gPJyv5sLzLOh9OI/908l/AfDhT0aed/Bdq9Cmin7KhwMLexUyv4awnhgHP5DPtyrsQ8E1j17Non1FMv7PD6YHMbs3nJt8g8uWYfAAbvnPJN5F8k9RyZMNXSL4h5CtSy5EN39XkqyTfSoWvz4ZvHvnmk2+Bwhew4buUfJeRb5nCV3qvNd9M8l1IvosUvop7rcvF48xPe1kuPqOku9+G7yHyPUy+Tyh8XTZy/ppy/oZyHlftacP3PPn2k+8F1Z42fE+Q70ny7VPteZ813yPk6ybfJ1V72vC5k5mvk5mvgUN87TZ8P2V8P2N8P1fi67HhS2Z8LsaXosR31Ibv+4zvCOP7gRKfZ6d1uv+e6X6C6f4Htf2z4fsm+V4h3yGFr8KG7y/k+yv5/qbmTxu+I+T7Afl+qObPndZ2eYt8/2D9eEptN234fky+18j3U7XdtJHzo+S7l3Lep/B5PmbNdyf5tpGvQ00HG76XyPcl8n1ZTQcbvs+R71nyPaemgw3fh8i3kXy3qelgw+cn383ka1L4eshXqOv3JrHfC1wAPD5Jacds+HLJl0e+fLV+seErI99k8k1Ry9H91nzDyFdCvuFq+2fDdx35riffDWq9ZMO3iHyLybdE4fPb8F1BvivJt1xtN234PkC+2eQrV+uz+63TfR/T/Smm+9NqP8SG75Pke5R8j5GvEhAg33TyZQCWku9PkCsJ+CTwYOC/AHuB30pifQM8BvhN4DLgvwNP43eGz31A+vC/wvBfZvhfY/ivMPyDDP8bDP+bDP8V1c4PWNv597TzCdr5j6qdbfheJN9L5PuyWk5s+D5Lvh4=
*/